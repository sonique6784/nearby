// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "presence/implementation/ldt.h"

#include <openssl/aes.h>

#include <optional>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "presence/implementation/np_ldt.h"

namespace nearby {
namespace presence {

namespace {
template <class T>
T FromStringView(absl::string_view data) {
  T result{
      .bytes = {0},
  };
  memcpy(result.bytes, data.data(),
         std::min(sizeof(result.bytes), data.size()));
  return result;
}

struct AesContext {
  AES_KEY encryption_key;
  AES_KEY decryption_key;
};

NpLdtAesCipherHandle AesCreateCipher(NpLdtAes128Key key) {
  AesContext* ctx = new AesContext();
  AES_set_encrypt_key(key.bytes, 128, &ctx->encryption_key);
  AES_set_decrypt_key(key.bytes, 128, &ctx->decryption_key);
  // The caller takes ownership and they must call `AesCloseCipher` eventually.
  return ctx;
}

int32_t AesCloseCipher(NpLdtAesCipherHandle handle) {
  AesContext* ctx = reinterpret_cast<AesContext*>(handle);
  free(ctx);
  return 0;
}

void AesEncrypt(NpLdtAesCipherHandle handle, NpLdtAesBlock* block) {
  AesContext* ctx = reinterpret_cast<AesContext*>(handle);
  AES_encrypt(block->bytes, block->bytes, &ctx->encryption_key);
}

void AesDecrypt(NpLdtAesCipherHandle handle, NpLdtAesBlock* block) {
  AesContext* ctx = reinterpret_cast<AesContext*>(handle);
  AES_decrypt(block->bytes, block->bytes, &ctx->decryption_key);
}

}  // namespace

absl::StatusOr<LdtEncryptor> LdtEncryptor::Create(
    absl::string_view key_seed, absl::string_view known_hmac) {
  NpLdtAesConfig ldt_aes_config = {.create_cipher = AesCreateCipher,
                                   .close_cipher = AesCloseCipher,
                                   .encrypt = AesEncrypt,
                                   .decrypt = AesDecrypt};
  NpLdtKeySeed ldt_key_seed = {.bytes = {0}};
  memcpy(ldt_key_seed.bytes, key_seed.data(),
         std::min(sizeof(ldt_key_seed.bytes), key_seed.size()));
  NpMetadataKeyHmac metadata_key_hmac = {.bytes = {0}};
  memcpy(metadata_key_hmac.bytes, known_hmac.data(),
         std::min(sizeof(metadata_key_hmac.bytes), known_hmac.size()));
  NpLdtHandle handle =
      NpLdtCreate(ldt_aes_config, ldt_key_seed, metadata_key_hmac);
  if (handle == nullptr) {
    return absl::UnavailableError("Failed to create LDT encryptor");
  }

  return LdtEncryptor(handle);
}

absl::StatusOr<std::string> LdtEncryptor::Encrypt(absl::string_view data,
                                                  absl::string_view salt) {
  std::string encrypted = std::string(data);
  NP_LDT_RESULT result =
      NpLdtEncrypt(ldt_handle_, reinterpret_cast<uint8_t*>(encrypted.data()),
                   encrypted.size(), FromStringView<NpLdtSalt>(salt));
  if (result == NP_LDT_SUCCESS) {
    return encrypted;
  }
  return absl::InternalError(
      absl::StrFormat("LDT encryption failed, errorcode %d", result));
}

absl::StatusOr<std::string> LdtEncryptor::DecryptAndVerify(
    absl::string_view data, absl::string_view salt) {
  std::string encrypted = std::string(data);
  NP_LDT_RESULT result = NpLdtDecryptAndVerify(
      ldt_handle_, reinterpret_cast<uint8_t*>(encrypted.data()),
      encrypted.size(), FromStringView<NpLdtSalt>(salt));
  if (result == NP_LDT_SUCCESS) {
    return encrypted;
  }
  return absl::InternalError(
      absl::StrFormat("LDT encryption failed, errorcode %d", result));
}

}  // namespace presence
}  // namespace nearby

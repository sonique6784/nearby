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

#ifndef THIRD_PARTY_NEARBY_PRESENCE_IMPLEMENTATION_LDT_H_
#define THIRD_PARTY_NEARBY_PRESENCE_IMPLEMENTATION_LDT_H_

#include <string>
#include <utility>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "presence/implementation/np_ldt.h"

namespace nearby {
namespace presence {

class LdtEncryptor {
 public:
  LdtEncryptor(const LdtEncryptor&) = delete;
  LdtEncryptor(LdtEncryptor&& other)
      : ldt_handle_(std::move(other.ldt_handle_)) {}
  LdtEncryptor& operator=(const LdtEncryptor&&) = delete;
  LdtEncryptor& operator=(LdtEncryptor&& other) {
    ldt_handle_ = std::move(other.ldt_handle_);
    return *this;
  }
  ~LdtEncryptor() {
    if (ldt_handle_ != nullptr) {
      NpLdtClose(ldt_handle_);
    }
  }
  static absl::StatusOr<LdtEncryptor> Create(absl::string_view key_seed,
                                             absl::string_view known_hmac);

  absl::StatusOr<std::string> Encrypt(absl::string_view data,
                                      absl::string_view salt);

  absl::StatusOr<std::string> DecryptAndVerify(absl::string_view data,
                                               absl::string_view salt);

 private:
  explicit LdtEncryptor(NpLdtHandle ldt_handle) : ldt_handle_(ldt_handle) {}
  NpLdtHandle ldt_handle_;
};

}  // namespace presence
}  // namespace nearby

#endif  // THIRD_PARTY_NEARBY_PRESENCE_IMPLEMENTATION_LDT_H_

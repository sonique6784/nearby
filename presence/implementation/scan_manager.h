// Copyright 2020 Google LLC
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

#ifndef THIRD_PARTY_NEARBY_PRESENCE_IMPLEMENTATION_SCAN_MANAGER_H_
#define THIRD_PARTY_NEARBY_PRESENCE_IMPLEMENTATION_SCAN_MANAGER_H_

#include <cstdint>
#include <memory>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/functional/any_invocable.h"
#include "presence/data_types.h"
#include "presence/implementation/credential_manager.h"
#include "presence/implementation/mediums/ble.h"
#include "presence/implementation/mediums/mediums.h"
#include "presence/presence_device.h"
#include "presence/scan_request.h"

namespace nearby {
namespace presence {

struct BleDeviceFoundCallback {
  /**
   * Callback for ScanManager to call when a device of interest to this client
   * is discovered.
   */
  absl::AnyInvocable<void(PresenceDevice)> device_found_cb;
};

/*
 * The instance of ScanManager is owned by {@code ServiceControllerImpl}.
 * Helping service controller to manage scan requests and callbacks.
 */
class ScanManager {
 public:
  ScanManager(Mediums& mediums, CredentialManager& credential_manager) {
    mediums_ = &mediums, credential_manager_ = &credential_manager;
  }
  ~ScanManager() = default;

  std::unique_ptr<ScanSession> StartScan(
      ScanRequest scan_request, BleDeviceFoundCallback device_found_callback,
      ScanningCallback cb) ABSL_LOCKS_EXCLUDED(mutex_);
  // Test only.
  // Reference: go/totw/135#augmenting-the-public-api-for-tests
  int ScanningCallbacksLengthForTest() ABSL_LOCKS_EXCLUDED(mutex_) {
    return scanning_callbacks_.size();
  }
  uint64_t FirstScanningId() ABSL_LOCKS_EXCLUDED(mutex_) {
    return scanning_callbacks_.begin()->first;
  }
  Status NotifyFoundBle(uint64_t id, PresenceDevice pd);

 private:
  mutable absl::Mutex mutex_;
  Mediums* mediums_;
  CredentialManager* credential_manager_;
  absl::flat_hash_map<uint64_t, BleDeviceFoundCallback> scanning_callbacks_;
};

}  // namespace presence
}  // namespace nearby

#endif  // THIRD_PARTY_NEARBY_PRESENCE_IMPLEMENTATION_SCAN_MANAGER_H_

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

#include "presence/implementation/scan_manager.h"

#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/random/random.h"
#include "absl/random/uniform_int_distribution.h"
#include "internal/platform/implementation/ble_v2.h"
#include "presence/data_types.h"
#include "presence/implementation/mediums/ble.h"
#include "presence/presence_device.h"

namespace {
using BleAdvertisementData =
    ::location::nearby::api::ble_v2::BleAdvertisementData;
using BlePeripheral = ::location::nearby::api::ble_v2::BlePeripheral;
using BleOperationStatus = ::location::nearby::api::ble_v2::BleOperationStatus;
using ScanningSession =
    ::location::nearby::api::ble_v2::BleMedium::ScanningSession;
}  // namespace

namespace nearby {
namespace presence {

std::unique_ptr<ScanSession> ScanManager::StartScan(
    ScanRequest scan_request, BleDeviceFoundCallback device_found_callback,
    ScanningCallback cb) {
  absl::BitGen gen;
  uint64_t id = absl::uniform_int_distribution<uint64_t>(0, UINT64_MAX)(gen);
  ScanningCallback callback = ScanningCallback{
      .start_scanning_result = std::move(cb.start_scanning_result),
      .advertisement_found_cb =
          [advert_found_cb = std::move(cb.advertisement_found_cb), this, id](
              BlePeripheral& peripheral, BleAdvertisementData data) {
            NotifyFoundBle(id, PresenceDevice());
            advert_found_cb(peripheral, data);
          }};
  std::unique_ptr<ScanningSession> scanning_session =
      mediums_->GetBle().StartScanning(scan_request, callback);
  auto modified_scanning_session = std::make_unique<ScanSession>(ScanSession{
      .stop_scan_callback = [scanning_session_cb =
                                 std::move(scanning_session->stop_scanning),
                             this, id]() {
        absl::MutexLock lock(&mutex_);
        if (scanning_callbacks_.find(id) == scanning_callbacks_.end()) {
          return Status{.value = Status::Value::kError};
        }
        scanning_callbacks_.erase(id);
        BleOperationStatus status = scanning_session_cb();
        if (status == BleOperationStatus::kFailed ||
            status == BleOperationStatus::kUnknown) {
          return Status{.value = Status::Value::kError};
        } else {
          return Status{.value = Status::Value::kSuccess};
        }
      }});
  absl::MutexLock lock(&mutex_);
  scanning_callbacks_.emplace(id, std::move(device_found_callback));
  return modified_scanning_session;
}

Status ScanManager::NotifyFoundBle(uint64_t id, PresenceDevice pd) {
  absl::MutexLock lock(&mutex_);
  auto it = scanning_callbacks_.find(id);
  if (it == scanning_callbacks_.end()) {
    return Status{.value = Status::Value::kError};
  }
  it->second.device_found_cb(pd);
  return Status{.value = Status::Value::kSuccess};
}

}  // namespace presence
}  // namespace nearby

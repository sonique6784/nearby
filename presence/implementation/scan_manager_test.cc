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

#include <math.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"
#include "absl/random/random.h"
#include "internal/platform/bluetooth_adapter.h"
#include "internal/platform/count_down_latch.h"
#include "internal/platform/medium_environment.h"
#include "presence/implementation/advertisement_factory.h"
#include "presence/implementation/credential_manager_impl.h"
#include "presence/implementation/mediums/ble.h"
#include "presence/implementation/mediums/mediums.h"

namespace nearby {
namespace presence {
namespace {

using BleOperationStatus = location::nearby::api::ble_v2::BleOperationStatus;

constexpr absl::string_view kAdvertisementString = "\x0a\x0b\x0c\x0d";

class ScanManagerTest : public testing::Test {
 protected:
  void SetUp() override {
    env_.Stop();
    env_.Start();
  }
  void TearDown() override { env_.Stop(); }
  std::vector<nearby::internal::IdentityType> identity_types_ = {
      nearby::internal::IdentityType::IDENTITY_TYPE_TRUSTED,
  };
  std::vector<DataElement> extended_properties_ = {
      DataElement{DataElement::kTxPowerFieldType, "-10"}};
  std::vector<absl::variant<PresenceScanFilter, LegacyPresenceScanFilter> >
      filters_ = {PresenceScanFilter{
          .scan_type = ScanType::kPresenceScan,
          .extended_properties = extended_properties_,
      }};
  ScanRequest scan_request_ = {
      .account_name = "Test-Name",
      .identity_types = identity_types_,
      .scan_filters = filters_,
      .use_ble = true,
      .scan_type = ScanType::kPresenceScan,
      .power_mode = PowerMode::kBalanced,
      .scan_only_when_screen_on = true,
  };
  CredentialManagerImpl credential_manager_;
  location::nearby::MediumEnvironment& env_ = {
      location::nearby::MediumEnvironment::Instance()};
  location::nearby::ByteArray advertisement_bytes_ =
      location::nearby::ByteArray{std::string(kAdvertisementString)};
  BleAdvertisementData data_ = {
      .is_extended_advertisement = false,
      .service_data = {{kPresenceServiceUuid, advertisement_bytes_}},
  };
  location::nearby::api::ble_v2::AdvertiseParameters params_ = {
      .tx_power_level = TxPowerLevel::kHigh,
      .is_connectable = true,
  };
  location::nearby::CountDownLatch start_latch_{1};
  location::nearby::CountDownLatch found_latch_{1};
};

TEST_F(ScanManagerTest, CanStartThenStopScanning) {
  // Needs to be run in env context so env can register the medium
  Mediums mediums;
  ScanManager manager = {mediums, credential_manager_};
  ScanningCallback scanning_callback = ScanningCallback{
      .start_scanning_result =
          [this](BleOperationStatus status) {
            if (status == BleOperationStatus::kSucceeded) {
              start_latch_.CountDown();
            }
          },
  };
  BleDeviceFoundCallback device_callback = BleDeviceFoundCallback{
      .device_found_cb =
          [this](PresenceDevice pd) {
            found_latch_.CountDown();
            return BleOperationStatus::kSucceeded;
          },
  };
  // Set up advertiser
  location::nearby::BluetoothAdapter adapter2;
  location::nearby::BleV2Medium ble2{adapter2};
  ble2.StartAdvertising(data_, params_);

  // Start scanning
  std::unique_ptr<ScanSession> scan_session = manager.StartScan(
      scan_request_, std::move(device_callback), std::move(scanning_callback));

  EXPECT_EQ(manager.ScanningCallbacksLengthForTest(), 1);
  EXPECT_TRUE(start_latch_.Await(absl::Milliseconds(500)).result());
  EXPECT_TRUE(found_latch_.Await(absl::Milliseconds(1500)).result());

  Status stop_scanning_status = scan_session->stop_scan_callback();
  EXPECT_TRUE(stop_scanning_status.Ok());
  EXPECT_EQ(manager.ScanningCallbacksLengthForTest(), 0);
}

TEST_F(ScanManagerTest, CannotStopScanTwice) {
  // Needs to be run in env context so env can register the medium
  Mediums mediums;
  ScanManager manager = {mediums, credential_manager_};
  ScanningCallback scanning_callback = ScanningCallback{
      .start_scanning_result =
          [this](BleOperationStatus status) {
            if (status == BleOperationStatus::kSucceeded) {
              start_latch_.CountDown();
            }
          },
  };
  BleDeviceFoundCallback device_callback = BleDeviceFoundCallback{
      .device_found_cb =
          [](PresenceDevice pd) { return BleOperationStatus::kSucceeded; },
  };

  auto scan_session = manager.StartScan(
      scan_request_, std::move(device_callback), std::move(scanning_callback));
  NEARBY_LOGS(INFO) << "Start scan";
  EXPECT_TRUE(start_latch_.Await(absl::Milliseconds(1000)).result());
  NEARBY_LOGS(INFO) << "Stop scan";
  Status stop_scanning_status = scan_session->stop_scan_callback();
  EXPECT_TRUE(stop_scanning_status.Ok());
  NEARBY_LOGS(INFO) << "Stop scan again";
  Status stop_scanning_status_nop = scan_session->stop_scan_callback();
  EXPECT_FALSE(stop_scanning_status_nop.Ok());
}

TEST_F(ScanManagerTest, CannotNotifyAfterStop) {
  // Needs to be run in env context so env can register the medium
  Mediums mediums;
  ScanManager manager = {mediums, credential_manager_};
  ScanningCallback scanning_callback = ScanningCallback{
      .start_scanning_result =
          [this](BleOperationStatus status) {
            if (status == BleOperationStatus::kSucceeded) {
              start_latch_.CountDown();
            }
          },
  };
  BleDeviceFoundCallback device_callback = BleDeviceFoundCallback{
      .device_found_cb =
          [this](PresenceDevice pd) {
            found_latch_.CountDown();
            return BleOperationStatus::kSucceeded;
          },
  };

  std::unique_ptr<ScanSession> scan_session = manager.StartScan(
      scan_request_, std::move(device_callback), std::move(scanning_callback));
  EXPECT_EQ(manager.ScanningCallbacksLengthForTest(), 1);
  uint64_t id = manager.FirstScanningId();
  // EXPECT_TRUE(start_latch.Await(absl::Milliseconds(1000)).result());
  Status stop_scanning_status = scan_session->stop_scan_callback();
  EXPECT_TRUE(stop_scanning_status.Ok());
  Status notified = manager.NotifyFoundBle(id, PresenceDevice());
  EXPECT_FALSE(notified.Ok());
}

}  // namespace
}  // namespace presence
}  // namespace nearby

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

#include "internal/platform/wifi_direct.h"
#include "internal/platform/wifi_hotspot.h"

#include <string>

#include "gmock/gmock.h"
#include "protobuf-matchers/protocol-buffer-matchers.h"
#include "gtest/gtest.h"
#include "absl/time/clock.h"
#include "internal/platform/medium_environment.h"
#include "internal/platform/count_down_latch.h"
#include "internal/platform/logging.h"
#include "internal/platform/wifi_hotspot_credential.h"

namespace location {
namespace nearby {
namespace {

TEST(WifiDirectMediumTest, ConstructorDestructorWorks) {
  WifiDirectMedium wifi_direct_a;
  WifiDirectMedium wifi_direct_b;

  if (wifi_direct_a.IsValid() && wifi_direct_b.IsValid()) {
    // Make sure we can create 2 distinct mediums.
    EXPECT_NE(&wifi_direct_a.GetImpl(), &wifi_direct_b.GetImpl());
  }
  // TODO(b/254500127): Add test coverage for wifi_direct.cc
}

TEST(WifiDirectMediumTest, CanConnectToService) {
  CancellationFlag flag;
  WifiDirectMedium wifi_direct_a;
  WifiDirectMedium wifi_direct_b;

  // TODO(b/254500127): Add test coverage for wifi_direct.cc
}

TEST(WifiDirectMediumTest, CanSartWifiDirectGO) {
  WifiDirectMedium wifi_direct;

  // TODO(b/254500127): Add test coverage for wifi_direct.cc
}

}  // namespace
}  // namespace nearby
}  // namespace location

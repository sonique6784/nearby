#include "core/internal/bluetooth_bwu_handler.h"

#include "core/internal/bluetooth_endpoint_channel.h"
#include "core/internal/client_proxy.h"
#include "core/internal/offline_frames.h"
#include "absl/functional/bind_front.h"

// Manages the Bluetooth-specific methods needed to upgrade an {@link
// EndpointChannel}.

namespace location {
namespace nearby {
namespace connections {

BluetoothBwuHandler::BluetoothBwuHandler(
    Mediums& mediums, EndpointChannelManager& channel_manager,
    BwuNotifications notifications)
    : BaseBwuHandler(channel_manager, std::move(notifications)),
      mediums_(mediums) {}

void BluetoothBwuHandler::Revert() {
  for (const std::string& service_id : active_service_ids_) {
    bluetooth_medium_.StopAcceptingConnections(service_id);
  }
  active_service_ids_.clear();
  NEARBY_LOG(INFO,
             "BluetoothBwuHandler successfully reverted all Bluetooth state.");
}

// Accept Connection Callback.
// Notifies that the remote party called BluetoothClassic::Connect()
// for this socket.
void BluetoothBwuHandler::OnIncomingBluetoothConnection(
    ClientProxy* client, const std::string& service_id,
    BluetoothSocket socket) {
  auto channel =
      absl::make_unique<BluetoothEndpointChannel>(service_id, socket);
  std::unique_ptr<IncomingSocketConnection> connection{
      new IncomingSocketConnection{
          .socket =
              std::make_unique<BluetoothIncomingSocket>(service_id, socket),
          .channel = std::move(channel),
      }};
  bwu_notifications_.incoming_connection_cb(client, std::move(connection));
}

// Called by BWU initiator. BT Medium is set up, and BWU request is prepared,
// with necessary info (service_id, MAC address) for remote party to perform
// discovery.
ByteArray BluetoothBwuHandler::InitializeUpgradedMediumForEndpoint(
    ClientProxy* client, const std::string& service_id,
    const std::string& endpoint_id) {
  std::string upgrade_service_id = Utils::WrapUpgradeServiceId(service_id);

  std::string mac_address = bluetooth_medium_.GetMacAddress();
  if (mac_address.empty()) {
    return {};
  }

  if (!bluetooth_medium_.IsAcceptingConnections(upgrade_service_id)) {
    if (!bluetooth_medium_.StartAcceptingConnections(
            upgrade_service_id,
            {
                .accepted_cb = absl::bind_front(
                    &BluetoothBwuHandler::OnIncomingBluetoothConnection, this,
                    client, service_id),
            })) {
      return {};
    }
  }
  // cache service ID to revert
  active_service_ids_.emplace(upgrade_service_id);

  return parser::ForBwuBluetoothPathAvailable(upgrade_service_id, mac_address);
}

// Called by BWU target. Retrieves a new medium info from incoming message,
// and establishes connection over BT using this info.
// Returns a channel ready to exchange data or nullptr on error.
std::unique_ptr<EndpointChannel>
BluetoothBwuHandler::CreateUpgradedEndpointChannel(
    ClientProxy* client, const std::string& service_id,
    const std::string& endpoint_id, const UpgradePathInfo& upgrade_path_info) {
  const UpgradePathInfo::BluetoothCredentials& bluetooth_credentials =
      upgrade_path_info.bluetooth_credentials();
  if (!bluetooth_credentials.has_service_name() ||
      !bluetooth_credentials.has_mac_address()) {
    return nullptr;
  }

  const std::string& service_name = bluetooth_credentials.service_name();
  const std::string& mac_address = bluetooth_credentials.mac_address();

  BluetoothDevice device = bluetooth_medium_.GetRemoteDevice(mac_address);
  if (!device.IsValid()) {
    return nullptr;
  }

  BluetoothSocket socket = bluetooth_medium_.Connect(device, service_name);
  if (!socket.IsValid()) {
    return nullptr;
  }

  auto channel =
      std::make_unique<BluetoothEndpointChannel>(service_name, socket);
  if (channel == nullptr) {
    socket.Close();
    return nullptr;
  }

  return channel;
}

}  // namespace connections
}  // namespace nearby
}  // namespace location

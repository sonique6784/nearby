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

import NearbyCoreAdapter

/// TODO(bourdakos@): Documentation.
public class Discoverer {

  /// TODO(bourdakos@): Documentation.
  public weak var delegate: DiscovererDelegate?

  let connectionManager: ConnectionManager

  /// TODO(bourdakos@): Documentation.
  public init(connectionManager: ConnectionManager) {
    self.connectionManager = connectionManager
  }

  /// TODO(bourdakos@): Documentation.
  public func startDiscovery() {
    let options = GNCDiscoveryOptions(strategy: connectionManager.strategy)
    GNCCoreAdapter.shared.startDiscovery(
      asService: connectionManager.serviceID, options: options, delegate: self)
  }

  /// TODO(bourdakos@): Documentation.
  public func stopDiscovery() {
    GNCCoreAdapter.shared.stopDiscovery()
  }

  /// TODO(bourdakos@): Documentation.
  public func requestConnection(
    toEndpoint endpointID: String, withEndpointInfo endpointInfo: Data? = nil
  ) {
    let options = GNCConnectionOptions()
    GNCCoreAdapter.shared.requestConnection(
      toEndpoint: endpointID, endpointInfo: endpointInfo ?? connectionManager.endpointInfo,
      options: options, delegate: self)
  }

  deinit {
    stopDiscovery()
  }
}

extension Discoverer: GNCConnectionDelegate {

  public func connected(
    toEndpoint endpointID: String, withEndpointInfo info: Data, authenticationToken: String
  ) {
    connectionManager.queue.async { [weak self] in
      guard let connectionManager = self?.connectionManager else { return }
      connectionManager.delegate?.connectionManager(
        connectionManager, endpoint: endpointID, didChange: .connecting)
      connectionManager.delegate?.connectionManager(
        connectionManager, didReceiveVerificationCode: authenticationToken, fromEndpoint: endpointID
      ) { accept in
        if !accept {
          GNCCoreAdapter.shared.rejectConnectionRequest(fromEndpoint: endpointID)
          return
        }
        GNCCoreAdapter.shared.acceptConnectionRequest(
          fromEndpoint: endpointID, delegate: connectionManager)
      }
    }
  }

  public func acceptedConnection(toEndpoint endpointID: String) {
    connectionManager.queue.async { [weak self] in
      guard let connectionManager = self?.connectionManager else { return }
      connectionManager.delegate?.connectionManager(
        connectionManager, endpoint: endpointID, didChange: .connected)
    }
  }

  public func rejectedConnection(toEndpoint endpointID: String, with status: GNCStatus) {
    connectionManager.queue.async { [weak self] in
      guard let connectionManager = self?.connectionManager else { return }
      connectionManager.delegate?.connectionManager(
        connectionManager, endpoint: endpointID, didChange: .rejected)
    }
  }

  public func disconnected(fromEndpoint endpointID: String) {
    connectionManager.queue.async { [weak self] in
      guard let connectionManager = self?.connectionManager else { return }
      connectionManager.delegate?.connectionManager(
        connectionManager, endpoint: endpointID, didChange: .disconnected)
    }
  }
}

extension Discoverer: GNCDiscoveryDelegate {

  public func foundEndpoint(_ endpointID: String, withEndpointInfo info: Data) {
    connectionManager.queue.async { [weak self] in
      guard let self = self else { return }
      self.delegate?.discoverer(self, foundEndpoint: endpointID, withEndpointInfo: info)
    }
  }

  public func lostEndpoint(_ endpointID: String) {
    connectionManager.queue.async { [weak self] in
      guard let self = self else { return }
      self.delegate?.discoverer(self, lostEndpoint: endpointID)
    }
  }
}

/// The `DiscovererDelegate` protocol defines methods that a `Discoverer` object’s delegate can implement to handle discovery-related events.
///
/// Delegate methods are executed on the `.main` queue by default, but a specific `DispatchQueue` on which to call the delegate methods can be passed to `ConnectionManager`.
public protocol DiscovererDelegate: AnyObject {

  /// Called when a nearby endpoint is found.
  ///
  /// - Parameters:
  ///   - discoverer: The discoverer object that found the nearby endpoint.
  ///   - endpointID: The unique ID of the endpoint that was found.
  ///   - info: An arbitrary piece of data received from the nearby endpoint. This can be used to provide further information to the user about the nature of the invitation.
  ///
  /// The endpoint ID provided to this delegate method can be used to request a connection with the nearby endpoint.
  func discoverer(
    _ discoverer: Discoverer, foundEndpoint endpointID: String, withEndpointInfo info: Data)

  /// Called when a nearby endpoint is lost.
  ///
  /// - Parameters:
  ///   - discoverer: The discoverer object that lost the nearby endpoint.
  ///   - endpointID: The unique ID of the nearby endpoint that was lost.
  ///
  /// This callback informs your app that connection requests can no longer be sent to an endpoint, and that your app should remove that endpoint from its user interface.
  ///
  /// - Important:
  /// Because there is a delay between when a discovered endpoint disapears and when Nearby Connections detects that it has left, the fact that your app has not yet received a disappearance callback does not guarantee that it can communicate with the endpoint successfully.
  func discoverer(_ discoverer: Discoverer, lostEndpoint endpointID: String)
}

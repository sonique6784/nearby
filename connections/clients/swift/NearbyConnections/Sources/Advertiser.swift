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
public class Advertiser {

  /// TODO(bourdakos@): Documentation.
  public weak var delegate: AdvertiserDelegate?

  let connectionManager: ConnectionManager

  /// TODO(bourdakos@): Documentation.
  public init(connectionManager: ConnectionManager) {
    self.connectionManager = connectionManager
  }

  /// TODO(bourdakos@): Documentation.
  public func startAdvertising() {
    let options = GNCAdvertisingOptions(strategy: connectionManager.strategy)
    GNCCoreAdapter.shared.startAdvertising(
      asService: serviceId, endpointInfo: connectionManager.endpointInfo, options: options,
      delegate: self)
  }

  /// TODO(bourdakos@): Documentation.
  public func stopAdvertising() {
    GNCCoreAdapter.shared.stopAdvertising()
  }

  deinit {
    stopAdvertising()
  }
}

extension Advertiser: GNCConnectionDelegate {

  public func connected(
    toEndpoint endpointID: String, withEndpointInfo info: Data, authenticationToken: String
  ) {
    connectionManager.queue.async { [weak self] in
      guard let self = self else { return }
      var hasAcceptedVerification = false
      var hasAcceptedConnectionRequest = false
      self.connectionManager.delegate?.connectionManager(
        self.connectionManager, endpoint: endpointID, didChange: .connecting)
      self.connectionManager.delegate?.connectionManager(
        self.connectionManager, didReceiveVerificationCode: authenticationToken,
        fromEndpoint: endpointID
      ) { accept in
        if !accept {
          GNCCoreAdapter.shared.rejectConnectionRequest(fromEndpoint: endpointID)
          return
        }
        hasAcceptedVerification = true
        if hasAcceptedVerification && hasAcceptedConnectionRequest {
          GNCCoreAdapter.shared.acceptConnectionRequest(
            fromEndpoint: endpointID, delegate: self.connectionManager)
        }
      }
      self.delegate?.advertiser(
        self, didReceiveConnectionRequestFromEndpoint: endpointID, withEndpointInfo: info
      ) { accept in
        if !accept {
          GNCCoreAdapter.shared.rejectConnectionRequest(fromEndpoint: endpointID)
          return
        }
        hasAcceptedConnectionRequest = true
        if hasAcceptedVerification && hasAcceptedConnectionRequest {
          GNCCoreAdapter.shared.acceptConnectionRequest(
            fromEndpoint: endpointID, delegate: self.connectionManager)
        }
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

/// The `AdvertiserDelegate` protocol defines methods that an `Advertiser` object’s delegate can implement to handle advertising-related events.
///
/// Delegate methods are executed on the `.main` queue by default, but a specific `DispatchQueue` on which to call the delegate methods can be passed to `ConnectionManager`.
public protocol AdvertiserDelegate: AnyObject {

  /// Called when a connection request is received from a nearby endpoint.
  ///
  /// - Parameters:
  ///   - advertiser: The advertiser object that received a connection request.
  ///   - endpointID: The endpoint ID of the nearby enpoint that requested the connection.
  ///   - info: An arbitrary piece of data received from the nearby endpoint. This can be used to provide further information to the user about the nature of the invitation.
  ///   - connectionRequestHandler: A block that your code must call to indicate whether the advertiser should accept or decline the connection request.
  ///
  /// - Important:
  /// Accepting a connection request will not yet establish a connection that allows data transference. The connection must first be verified by both parties via the `ConnectionManagerDelegate`, before data can flow freely.
  func advertiser(
    _ advertiser: Advertiser, didReceiveConnectionRequestFromEndpoint endpointID: String,
    withEndpointInfo info: Data, connectionRequestHandler: @escaping (Bool) -> Void)
}

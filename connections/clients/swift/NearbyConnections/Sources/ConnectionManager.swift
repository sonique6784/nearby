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

public enum ConnectionState: Int {
  case disconnected = 0
  case rejected = 1
  case connecting = 2
  case connected = 3
}

public enum Strategy {
  case cluster
  case star
  case pointToPoint

  // idk how to just export this directly...
  var objc: NearbyCoreAdapter.Strategy {
    switch self {
    case .cluster: return .cluster
    case .star: return .star
    case .pointToPoint: return .pointToPoint
    }
  }
}

/// TODO(bourdakos@): Documentation.
public class ConnectionManager {

  /// TODO(bourdakos@): Documentation.
  public weak var delegate: ConnectionManagerDelegate?

  let endpointInfo: Data
  let serviceID: String
  let strategy: NearbyCoreAdapter.Strategy
  let queue: DispatchQueue

  private var pendingFileTransfers: [Int64: [String: Progress]] = [:]

  /// TODO(bourdakos@): Documentation.
  public init(
    endpointInfo: Data, serviceID: String, strategy: Strategy, queue: DispatchQueue = .main
  ) {
    self.endpointInfo = endpointInfo
    self.serviceID = serviceID
    self.strategy = strategy.objc
    self.queue = queue
  }

  /// TODO(bourdakos@): Documentation.
  public func send(
    _ data: Data, withPayloadID payloadID: Int64? = nil, toEndpoints endpointIDs: [String]
  ) {
    if let payloadID = payloadID {
      GNCCoreAdapter.shared.send(
        GNCBytesPayload(data: data, identifier: payloadID), toEndpoints: endpointIDs)
    } else {
      GNCCoreAdapter.shared.send(GNCBytesPayload(data: data), toEndpoints: endpointIDs)
    }
  }

  /// TODO(bourdakos@): Documentation.
  public func send(
    _ stream: InputStream, withPayloadID payloadID: Int64? = nil, toEndpoints endpointIDs: [String]
  ) {
    if let payloadID = payloadID {
      GNCCoreAdapter.shared.send(
        GNCStreamPayload(stream: stream, identifier: payloadID), toEndpoints: endpointIDs)
    } else {
      GNCCoreAdapter.shared.send(GNCStreamPayload(stream: stream), toEndpoints: endpointIDs)
    }
  }

  /// TODO(bourdakos@): Documentation.
  public func sendResource(
    at resourceURL: URL, withName resourceName: String? = nil,
    withPayloadID payloadID: Int64? = nil, toEndpoints endpointIDs: [String],
    withCompletionHandler completionHandler: ((Error?) -> Void)? = nil
  ) -> Progress {
    // TODO(bourdakos@): add resourceName as another file payload option.
    let payload: GNCFilePayload
    if let payloadID = payloadID {
      payload = GNCFilePayload(fileURL: resourceURL, identifier: payloadID)
    } else {
      payload = GNCFilePayload(fileURL: resourceURL)
    }

    GNCCoreAdapter.shared.send(payload, toEndpoints: endpointIDs)

    // TODO(bourdakos@): This doesn't need any unit changes, because it's determined by children. Just delete this comment when other progresses are updated.
    let progress = Progress()
    for endpointID in endpointIDs {
      let progressChild = Progress()
      pendingFileTransfers[payload.identifier]?[endpointID] = progressChild
      // TODO(bourdakos@): Get file size from payload
      progress.addChild(progressChild, withPendingUnitCount: 123)
    }
    return progress
  }

  /// TODO(bourdakos@): Documentation.
  public func cancelPayload(with payloadID: Int64) {
    GNCCoreAdapter.shared.cancelPayload(payloadID)
  }

  /// TODO(bourdakos@): Documentation.
  public func disconnect(from endpointID: String) {
    GNCCoreAdapter.shared.disconnect(fromEndpoint: endpointID)
  }
}

extension ConnectionManager: GNCPayloadDelegate {

  public func receivedPayload(_ payload: GNCPayload, fromEndpoint endpointID: String) {
    queue.async { [weak self] in
      guard let self = self else { return }
      if let bytesPayload = payload as? GNCBytesPayload {
        self.delegate?.connectionManager(
          self, didReceive: bytesPayload.data, fromEndpoint: endpointID)
      }
      if let streamPayload = payload as? GNCStreamPayload {
        self.delegate?.connectionManager(
          self, didReceive: streamPayload.stream, fromEndpoint: endpointID)
      }
      if let filePayload = payload as? GNCFilePayload {
        // TODO(bourdakos@): the file payload object should expose total size so we can initialize progress with total count.
        let progress = Progress()
        self.pendingFileTransfers[filePayload.identifier]?[endpointID] = progress
        self.delegate?.connectionManager(
          self, didStartReceivingResourceWithName: filePayload.fileURL.path,
          fromEndpoint: endpointID, with: progress)
      }
    }
  }

  public func receivedProgressUpdate(
    forPayload payloadID: Int64, with status: GNCPayloadStatus, fromEndpoint endpointID: String,
    bytesTransfered: Int64, totalBytes: Int64
  ) {
    //        DispatchQueue.main.async { [weak self] in
    //            guard let weakSelf = self else {
    //                return
    //            }
    // TODO(bourdakos@): delete total unit count when we can set it from GNCFilePayload directly.
    // does this need to happen on same queue?
    pendingFileTransfers[payloadID]?[endpointID]?.totalUnitCount = totalBytes
    pendingFileTransfers[payloadID]?[endpointID]?.completedUnitCount = bytesTransfered

    // TODO(bourdakos@): Add didFinishReceivingResourceWithName delegete call and call the completion handler for sendResource.
    // TODO(bourdakos@): Handle cancel status somehow. call cancel on progress object for file transfers. What does this look like for the progress tree?
    // TODO(bourdakos@): Errors for files can be handled with the completion handler and didFinishReceivingResourceWithName
    // TODO(bourdakos@): Errors and cancels from streams should be able to handle themselves?
    // TODO(bourdakos@): Not sure what to do about errors/cancels from bytes?
    //        }
  }
}

/// The `ConnectionManagerDelegate` protocol defines methods that a `ConnectionManager`  object’s delegate can implement to handle connection-related events.
///
/// Delegate methods are executed on the `.main` queue by default, but a specific `DispatchQueue` on which to call the delegate methods can be passed to `ConnectionManager`.
public protocol ConnectionManagerDelegate: AnyObject {

  /// Called to validate the verification code generated for the pair of endpoints.
  ///
  /// - Parameters:
  ///   - connectionManager: The connection manager object through which the verification code was received.
  ///   - verificationCode: An identical token given to both endpoints.
  ///   - endpointID: The endpoint ID of the nearby endpoint that needs verification.
  ///   - verificationHandler: Your app should call this handler with a value of `true` if the nearby endpoint should be trusted, or `false` otherwise.
  ///
  /// Your app should confirm whether you connected to the correct endpoint. Typically this involves showing the verification code on both devices and having the users manually compare and confirm; however, this is only required if you desire a secure connection between the devices. Upon confirmation, your app should call the provided `verificationHandler` block, passing either `true` (to trust the nearby endpoint) or `false` (to reject it).
  ///
  /// - Important:
  /// The Nearby Connections framework makes no attempt to validate the verification code in any way. If your delegate does not implement this method, all verification codes are accepted automatically.
  func connectionManager(
    _ connectionManager: ConnectionManager, didReceiveVerificationCode verificationCode: String,
    fromEndpoint endpointID: String, verificationHandler: @escaping (Bool) -> Void)

  /// Indicates that a `Data` object has been received from a nearby endpoint.
  ///
  /// - Parameters:
  ///   - connectionManager: The connection manager object through which the data was received.
  ///   - data: An object containing the received data.
  ///   - endpointID: The endpoint ID of the sender.
  func connectionManager(
    _ connectionManager: ConnectionManager, didReceive data: Data, fromEndpoint endpointID: String)

  /// Called when a nearby endpoint opens a byte stream connection to the local endpoint.
  ///
  /// - Parameters:
  ///   - connectionManager: The connection manager object through which the byte stream was received.
  ///   - stream: An `InputStream` object that represents the local endpoint for the byte stream.
  ///   - endpointID: The endpoint ID of the originator of the stream.
  func connectionManager(
    _ connectionManager: ConnectionManager, didReceive stream: InputStream,
    fromEndpoint endpointID: String)

  /// TODO(bourdakos@): Documentation.
  func connectionManager(
    _ connectionManager: ConnectionManager, didStartReceivingResourceWithName resourceName: String,
    fromEndpoint endpointID: String, with progress: Progress)

  /// TODO(bourdakos@): Documentation.
  func connectionManager(
    _ connectionManager: ConnectionManager, didFinishReceivingResourceWithName resourceName: String,
    fromEndpoint endpointID: String, at localURL: URL?, withError error: Error?)

  /// TODO(bourdakos@): Documentation.
  func connectionManager(
    _ connectionManager: ConnectionManager, endpoint endpointID: String,
    didChange state: ConnectionState)
}

extension ConnectionManagerDelegate {
  public func connectionManager(
    _ connectionManager: ConnectionManager, didReceiveVerificationCode verificationCode: String,
    fromEndpoint endpointID: String, verificationHandler: @escaping (Bool) -> Void
  ) {
    verificationHandler(true)
  }
}

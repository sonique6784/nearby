// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210930.14

#pragma once
#ifndef WINRT_Windows_Media_Core_2_H
#define WINRT_Windows_Media_Core_2_H
#include "winrt/impl/Windows.ApplicationModel.AppService.2.h"
#include "winrt/impl/Windows.Foundation.2.h"
#include "winrt/impl/Windows.Foundation.Collections.2.h"
#include "winrt/impl/Windows.Graphics.DirectX.Direct3D11.2.h"
#include "winrt/impl/Windows.Graphics.Imaging.2.h"
#include "winrt/impl/Windows.Media.2.h"
#include "winrt/impl/Windows.Media.Capture.Frames.2.h"
#include "winrt/impl/Windows.Media.Effects.2.h"
#include "winrt/impl/Windows.Media.MediaProperties.2.h"
#include "winrt/impl/Windows.Media.Playback.2.h"
#include "winrt/impl/Windows.Media.Streaming.Adaptive.2.h"
#include "winrt/impl/Windows.Networking.BackgroundTransfer.2.h"
#include "winrt/impl/Windows.Storage.2.h"
#include "winrt/impl/Windows.Storage.Streams.2.h"
#include "winrt/impl/Windows.Media.Core.1.h"
WINRT_EXPORT namespace winrt::Windows::Media::Core
{
    struct MseTimeRange
    {
        winrt::Windows::Foundation::TimeSpan Start;
        winrt::Windows::Foundation::TimeSpan End;
    };
    inline bool operator==(MseTimeRange const& left, MseTimeRange const& right) noexcept
    {
        return left.Start == right.Start && left.End == right.End;
    }
    inline bool operator!=(MseTimeRange const& left, MseTimeRange const& right) noexcept
    {
        return !(left == right);
    }
    struct TimedTextDouble
    {
        double Value;
        winrt::Windows::Media::Core::TimedTextUnit Unit;
    };
    inline bool operator==(TimedTextDouble const& left, TimedTextDouble const& right) noexcept
    {
        return left.Value == right.Value && left.Unit == right.Unit;
    }
    inline bool operator!=(TimedTextDouble const& left, TimedTextDouble const& right) noexcept
    {
        return !(left == right);
    }
    struct TimedTextPadding
    {
        double Before;
        double After;
        double Start;
        double End;
        winrt::Windows::Media::Core::TimedTextUnit Unit;
    };
    inline bool operator==(TimedTextPadding const& left, TimedTextPadding const& right) noexcept
    {
        return left.Before == right.Before && left.After == right.After && left.Start == right.Start && left.End == right.End && left.Unit == right.Unit;
    }
    inline bool operator!=(TimedTextPadding const& left, TimedTextPadding const& right) noexcept
    {
        return !(left == right);
    }
    struct TimedTextPoint
    {
        double X;
        double Y;
        winrt::Windows::Media::Core::TimedTextUnit Unit;
    };
    inline bool operator==(TimedTextPoint const& left, TimedTextPoint const& right) noexcept
    {
        return left.X == right.X && left.Y == right.Y && left.Unit == right.Unit;
    }
    inline bool operator!=(TimedTextPoint const& left, TimedTextPoint const& right) noexcept
    {
        return !(left == right);
    }
    struct TimedTextSize
    {
        double Height;
        double Width;
        winrt::Windows::Media::Core::TimedTextUnit Unit;
    };
    inline bool operator==(TimedTextSize const& left, TimedTextSize const& right) noexcept
    {
        return left.Height == right.Height && left.Width == right.Width && left.Unit == right.Unit;
    }
    inline bool operator!=(TimedTextSize const& left, TimedTextSize const& right) noexcept
    {
        return !(left == right);
    }
    struct __declspec(empty_bases) AudioStreamDescriptor : winrt::Windows::Media::Core::IAudioStreamDescriptor,
        impl::require<AudioStreamDescriptor, winrt::Windows::Media::Core::IAudioStreamDescriptor2, winrt::Windows::Media::Core::IMediaStreamDescriptor2, winrt::Windows::Media::Core::IAudioStreamDescriptor3>
    {
        AudioStreamDescriptor(std::nullptr_t) noexcept {}
        AudioStreamDescriptor(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IAudioStreamDescriptor(ptr, take_ownership_from_abi) {}
        explicit AudioStreamDescriptor(winrt::Windows::Media::MediaProperties::AudioEncodingProperties const& encodingProperties);
    };
    struct __declspec(empty_bases) AudioTrack : winrt::Windows::Media::Core::IMediaTrack,
        impl::require<AudioTrack, winrt::Windows::Media::Core::IAudioTrack>
    {
        AudioTrack(std::nullptr_t) noexcept {}
        AudioTrack(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaTrack(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) AudioTrackOpenFailedEventArgs : winrt::Windows::Media::Core::IAudioTrackOpenFailedEventArgs
    {
        AudioTrackOpenFailedEventArgs(std::nullptr_t) noexcept {}
        AudioTrackOpenFailedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IAudioTrackOpenFailedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) AudioTrackSupportInfo : winrt::Windows::Media::Core::IAudioTrackSupportInfo
    {
        AudioTrackSupportInfo(std::nullptr_t) noexcept {}
        AudioTrackSupportInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IAudioTrackSupportInfo(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) ChapterCue : winrt::Windows::Media::Core::IChapterCue
    {
        ChapterCue(std::nullptr_t) noexcept {}
        ChapterCue(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IChapterCue(ptr, take_ownership_from_abi) {}
        ChapterCue();
    };
    struct __declspec(empty_bases) CodecInfo : winrt::Windows::Media::Core::ICodecInfo
    {
        CodecInfo(std::nullptr_t) noexcept {}
        CodecInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ICodecInfo(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) CodecQuery : winrt::Windows::Media::Core::ICodecQuery
    {
        CodecQuery(std::nullptr_t) noexcept {}
        CodecQuery(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ICodecQuery(ptr, take_ownership_from_abi) {}
        CodecQuery();
    };
    struct CodecSubtypes
    {
        CodecSubtypes() = delete;
        [[nodiscard]] static auto VideoFormatDV25();
        [[nodiscard]] static auto VideoFormatDV50();
        [[nodiscard]] static auto VideoFormatDvc();
        [[nodiscard]] static auto VideoFormatDvh1();
        [[nodiscard]] static auto VideoFormatDvhD();
        [[nodiscard]] static auto VideoFormatDvsd();
        [[nodiscard]] static auto VideoFormatDvsl();
        [[nodiscard]] static auto VideoFormatH263();
        [[nodiscard]] static auto VideoFormatH264();
        [[nodiscard]] static auto VideoFormatH265();
        [[nodiscard]] static auto VideoFormatH264ES();
        [[nodiscard]] static auto VideoFormatHevc();
        [[nodiscard]] static auto VideoFormatHevcES();
        [[nodiscard]] static auto VideoFormatM4S2();
        [[nodiscard]] static auto VideoFormatMjpg();
        [[nodiscard]] static auto VideoFormatMP43();
        [[nodiscard]] static auto VideoFormatMP4S();
        [[nodiscard]] static auto VideoFormatMP4V();
        [[nodiscard]] static auto VideoFormatMpeg2();
        [[nodiscard]] static auto VideoFormatVP80();
        [[nodiscard]] static auto VideoFormatVP90();
        [[nodiscard]] static auto VideoFormatMpg1();
        [[nodiscard]] static auto VideoFormatMss1();
        [[nodiscard]] static auto VideoFormatMss2();
        [[nodiscard]] static auto VideoFormatWmv1();
        [[nodiscard]] static auto VideoFormatWmv2();
        [[nodiscard]] static auto VideoFormatWmv3();
        [[nodiscard]] static auto VideoFormatWvc1();
        [[nodiscard]] static auto VideoFormat420O();
        [[nodiscard]] static auto AudioFormatAac();
        [[nodiscard]] static auto AudioFormatAdts();
        [[nodiscard]] static auto AudioFormatAlac();
        [[nodiscard]] static auto AudioFormatAmrNB();
        [[nodiscard]] static auto AudioFormatAmrWB();
        [[nodiscard]] static auto AudioFormatAmrWP();
        [[nodiscard]] static auto AudioFormatDolbyAC3();
        [[nodiscard]] static auto AudioFormatDolbyAC3Spdif();
        [[nodiscard]] static auto AudioFormatDolbyDDPlus();
        [[nodiscard]] static auto AudioFormatDrm();
        [[nodiscard]] static auto AudioFormatDts();
        [[nodiscard]] static auto AudioFormatFlac();
        [[nodiscard]] static auto AudioFormatFloat();
        [[nodiscard]] static auto AudioFormatMP3();
        [[nodiscard]] static auto AudioFormatMPeg();
        [[nodiscard]] static auto AudioFormatMsp1();
        [[nodiscard]] static auto AudioFormatOpus();
        [[nodiscard]] static auto AudioFormatPcm();
        [[nodiscard]] static auto AudioFormatWmaSpdif();
        [[nodiscard]] static auto AudioFormatWMAudioLossless();
        [[nodiscard]] static auto AudioFormatWMAudioV8();
        [[nodiscard]] static auto AudioFormatWMAudioV9();
    };
    struct __declspec(empty_bases) DataCue : winrt::Windows::Media::Core::IDataCue,
        impl::require<DataCue, winrt::Windows::Media::Core::IDataCue2>
    {
        DataCue(std::nullptr_t) noexcept {}
        DataCue(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IDataCue(ptr, take_ownership_from_abi) {}
        DataCue();
    };
    struct __declspec(empty_bases) FaceDetectedEventArgs : winrt::Windows::Media::Core::IFaceDetectedEventArgs
    {
        FaceDetectedEventArgs(std::nullptr_t) noexcept {}
        FaceDetectedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IFaceDetectedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) FaceDetectionEffect : winrt::Windows::Media::Core::IFaceDetectionEffect
    {
        FaceDetectionEffect(std::nullptr_t) noexcept {}
        FaceDetectionEffect(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IFaceDetectionEffect(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) FaceDetectionEffectDefinition : winrt::Windows::Media::Effects::IVideoEffectDefinition,
        impl::require<FaceDetectionEffectDefinition, winrt::Windows::Media::Core::IFaceDetectionEffectDefinition>
    {
        FaceDetectionEffectDefinition(std::nullptr_t) noexcept {}
        FaceDetectionEffectDefinition(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Effects::IVideoEffectDefinition(ptr, take_ownership_from_abi) {}
        FaceDetectionEffectDefinition();
    };
    struct __declspec(empty_bases) FaceDetectionEffectFrame : winrt::Windows::Media::Core::IFaceDetectionEffectFrame
    {
        FaceDetectionEffectFrame(std::nullptr_t) noexcept {}
        FaceDetectionEffectFrame(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IFaceDetectionEffectFrame(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) HighDynamicRangeControl : winrt::Windows::Media::Core::IHighDynamicRangeControl
    {
        HighDynamicRangeControl(std::nullptr_t) noexcept {}
        HighDynamicRangeControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IHighDynamicRangeControl(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) HighDynamicRangeOutput : winrt::Windows::Media::Core::IHighDynamicRangeOutput
    {
        HighDynamicRangeOutput(std::nullptr_t) noexcept {}
        HighDynamicRangeOutput(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IHighDynamicRangeOutput(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) ImageCue : winrt::Windows::Media::Core::IImageCue
    {
        ImageCue(std::nullptr_t) noexcept {}
        ImageCue(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IImageCue(ptr, take_ownership_from_abi) {}
        ImageCue();
    };
    struct __declspec(empty_bases) InitializeMediaStreamSourceRequestedEventArgs : winrt::Windows::Media::Core::IInitializeMediaStreamSourceRequestedEventArgs
    {
        InitializeMediaStreamSourceRequestedEventArgs(std::nullptr_t) noexcept {}
        InitializeMediaStreamSourceRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IInitializeMediaStreamSourceRequestedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct LowLightFusion
    {
        LowLightFusion() = delete;
        [[nodiscard]] static auto SupportedBitmapPixelFormats();
        [[nodiscard]] static auto MaxSupportedFrameCount();
        static auto FuseAsync(param::async_iterable<winrt::Windows::Graphics::Imaging::SoftwareBitmap> const& frameSet);
    };
    struct __declspec(empty_bases) LowLightFusionResult : winrt::Windows::Media::Core::ILowLightFusionResult,
        impl::require<LowLightFusionResult, winrt::Windows::Foundation::IClosable>
    {
        LowLightFusionResult(std::nullptr_t) noexcept {}
        LowLightFusionResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ILowLightFusionResult(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaBinder : winrt::Windows::Media::Core::IMediaBinder
    {
        MediaBinder(std::nullptr_t) noexcept {}
        MediaBinder(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaBinder(ptr, take_ownership_from_abi) {}
        MediaBinder();
    };
    struct __declspec(empty_bases) MediaBindingEventArgs : winrt::Windows::Media::Core::IMediaBindingEventArgs,
        impl::require<MediaBindingEventArgs, winrt::Windows::Media::Core::IMediaBindingEventArgs2, winrt::Windows::Media::Core::IMediaBindingEventArgs3>
    {
        MediaBindingEventArgs(std::nullptr_t) noexcept {}
        MediaBindingEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaBindingEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaCueEventArgs : winrt::Windows::Media::Core::IMediaCueEventArgs
    {
        MediaCueEventArgs(std::nullptr_t) noexcept {}
        MediaCueEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaCueEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaSource : winrt::Windows::Media::Core::IMediaSource2,
        impl::require<MediaSource, winrt::Windows::Media::Core::IMediaSource3, winrt::Windows::Media::Core::IMediaSource4, winrt::Windows::Media::Core::IMediaSource5>
    {
        MediaSource(std::nullptr_t) noexcept {}
        MediaSource(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaSource2(ptr, take_ownership_from_abi) {}
        static auto CreateFromAdaptiveMediaSource(winrt::Windows::Media::Streaming::Adaptive::AdaptiveMediaSource const& mediaSource);
        static auto CreateFromMediaStreamSource(winrt::Windows::Media::Core::MediaStreamSource const& mediaSource);
        static auto CreateFromMseStreamSource(winrt::Windows::Media::Core::MseStreamSource const& mediaSource);
        static auto CreateFromIMediaSource(winrt::Windows::Media::Core::IMediaSource const& mediaSource);
        static auto CreateFromStorageFile(winrt::Windows::Storage::IStorageFile const& file);
        static auto CreateFromStream(winrt::Windows::Storage::Streams::IRandomAccessStream const& stream, param::hstring const& contentType);
        static auto CreateFromStreamReference(winrt::Windows::Storage::Streams::IRandomAccessStreamReference const& stream, param::hstring const& contentType);
        static auto CreateFromUri(winrt::Windows::Foundation::Uri const& uri);
        static auto CreateFromMediaBinder(winrt::Windows::Media::Core::MediaBinder const& binder);
        static auto CreateFromMediaFrameSource(winrt::Windows::Media::Capture::Frames::MediaFrameSource const& frameSource);
        static auto CreateFromDownloadOperation(winrt::Windows::Networking::BackgroundTransfer::DownloadOperation const& downloadOperation);
    };
    struct __declspec(empty_bases) MediaSourceAppServiceConnection : winrt::Windows::Media::Core::IMediaSourceAppServiceConnection
    {
        MediaSourceAppServiceConnection(std::nullptr_t) noexcept {}
        MediaSourceAppServiceConnection(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaSourceAppServiceConnection(ptr, take_ownership_from_abi) {}
        explicit MediaSourceAppServiceConnection(winrt::Windows::ApplicationModel::AppService::AppServiceConnection const& appServiceConnection);
    };
    struct __declspec(empty_bases) MediaSourceError : winrt::Windows::Media::Core::IMediaSourceError
    {
        MediaSourceError(std::nullptr_t) noexcept {}
        MediaSourceError(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaSourceError(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaSourceOpenOperationCompletedEventArgs : winrt::Windows::Media::Core::IMediaSourceOpenOperationCompletedEventArgs
    {
        MediaSourceOpenOperationCompletedEventArgs(std::nullptr_t) noexcept {}
        MediaSourceOpenOperationCompletedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaSourceOpenOperationCompletedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaSourceStateChangedEventArgs : winrt::Windows::Media::Core::IMediaSourceStateChangedEventArgs
    {
        MediaSourceStateChangedEventArgs(std::nullptr_t) noexcept {}
        MediaSourceStateChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaSourceStateChangedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSample : winrt::Windows::Media::Core::IMediaStreamSample,
        impl::require<MediaStreamSample, winrt::Windows::Media::Core::IMediaStreamSample2>
    {
        MediaStreamSample(std::nullptr_t) noexcept {}
        MediaStreamSample(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSample(ptr, take_ownership_from_abi) {}
        static auto CreateFromBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer, winrt::Windows::Foundation::TimeSpan const& timestamp);
        static auto CreateFromStreamAsync(winrt::Windows::Storage::Streams::IInputStream const& stream, uint32_t count, winrt::Windows::Foundation::TimeSpan const& timestamp);
        static auto CreateFromDirect3D11Surface(winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface const& surface, winrt::Windows::Foundation::TimeSpan const& timestamp);
    };
    struct __declspec(empty_bases) MediaStreamSamplePropertySet : winrt::Windows::Foundation::Collections::IMap<winrt::guid, winrt::Windows::Foundation::IInspectable>
    {
        MediaStreamSamplePropertySet(std::nullptr_t) noexcept {}
        MediaStreamSamplePropertySet(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::Collections::IMap<winrt::guid, winrt::Windows::Foundation::IInspectable>(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSampleProtectionProperties : winrt::Windows::Media::Core::IMediaStreamSampleProtectionProperties
    {
        MediaStreamSampleProtectionProperties(std::nullptr_t) noexcept {}
        MediaStreamSampleProtectionProperties(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSampleProtectionProperties(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSource : winrt::Windows::Media::Core::IMediaStreamSource,
        impl::require<MediaStreamSource, winrt::Windows::Media::Core::IMediaStreamSource2, winrt::Windows::Media::Core::IMediaStreamSource3, winrt::Windows::Media::Core::IMediaStreamSource4>
    {
        MediaStreamSource(std::nullptr_t) noexcept {}
        MediaStreamSource(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSource(ptr, take_ownership_from_abi) {}
        explicit MediaStreamSource(winrt::Windows::Media::Core::IMediaStreamDescriptor const& descriptor);
        MediaStreamSource(winrt::Windows::Media::Core::IMediaStreamDescriptor const& descriptor, winrt::Windows::Media::Core::IMediaStreamDescriptor const& descriptor2);
    };
    struct __declspec(empty_bases) MediaStreamSourceClosedEventArgs : winrt::Windows::Media::Core::IMediaStreamSourceClosedEventArgs
    {
        MediaStreamSourceClosedEventArgs(std::nullptr_t) noexcept {}
        MediaStreamSourceClosedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceClosedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceClosedRequest : winrt::Windows::Media::Core::IMediaStreamSourceClosedRequest
    {
        MediaStreamSourceClosedRequest(std::nullptr_t) noexcept {}
        MediaStreamSourceClosedRequest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceClosedRequest(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceSampleRenderedEventArgs : winrt::Windows::Media::Core::IMediaStreamSourceSampleRenderedEventArgs
    {
        MediaStreamSourceSampleRenderedEventArgs(std::nullptr_t) noexcept {}
        MediaStreamSourceSampleRenderedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceSampleRenderedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceSampleRequest : winrt::Windows::Media::Core::IMediaStreamSourceSampleRequest
    {
        MediaStreamSourceSampleRequest(std::nullptr_t) noexcept {}
        MediaStreamSourceSampleRequest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceSampleRequest(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceSampleRequestDeferral : winrt::Windows::Media::Core::IMediaStreamSourceSampleRequestDeferral
    {
        MediaStreamSourceSampleRequestDeferral(std::nullptr_t) noexcept {}
        MediaStreamSourceSampleRequestDeferral(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceSampleRequestDeferral(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceSampleRequestedEventArgs : winrt::Windows::Media::Core::IMediaStreamSourceSampleRequestedEventArgs
    {
        MediaStreamSourceSampleRequestedEventArgs(std::nullptr_t) noexcept {}
        MediaStreamSourceSampleRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceSampleRequestedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceStartingEventArgs : winrt::Windows::Media::Core::IMediaStreamSourceStartingEventArgs
    {
        MediaStreamSourceStartingEventArgs(std::nullptr_t) noexcept {}
        MediaStreamSourceStartingEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceStartingEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceStartingRequest : winrt::Windows::Media::Core::IMediaStreamSourceStartingRequest
    {
        MediaStreamSourceStartingRequest(std::nullptr_t) noexcept {}
        MediaStreamSourceStartingRequest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceStartingRequest(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceStartingRequestDeferral : winrt::Windows::Media::Core::IMediaStreamSourceStartingRequestDeferral
    {
        MediaStreamSourceStartingRequestDeferral(std::nullptr_t) noexcept {}
        MediaStreamSourceStartingRequestDeferral(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceStartingRequestDeferral(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceSwitchStreamsRequest : winrt::Windows::Media::Core::IMediaStreamSourceSwitchStreamsRequest
    {
        MediaStreamSourceSwitchStreamsRequest(std::nullptr_t) noexcept {}
        MediaStreamSourceSwitchStreamsRequest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceSwitchStreamsRequest(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceSwitchStreamsRequestDeferral : winrt::Windows::Media::Core::IMediaStreamSourceSwitchStreamsRequestDeferral
    {
        MediaStreamSourceSwitchStreamsRequestDeferral(std::nullptr_t) noexcept {}
        MediaStreamSourceSwitchStreamsRequestDeferral(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceSwitchStreamsRequestDeferral(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MediaStreamSourceSwitchStreamsRequestedEventArgs : winrt::Windows::Media::Core::IMediaStreamSourceSwitchStreamsRequestedEventArgs
    {
        MediaStreamSourceSwitchStreamsRequestedEventArgs(std::nullptr_t) noexcept {}
        MediaStreamSourceSwitchStreamsRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamSourceSwitchStreamsRequestedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MseSourceBuffer : winrt::Windows::Media::Core::IMseSourceBuffer
    {
        MseSourceBuffer(std::nullptr_t) noexcept {}
        MseSourceBuffer(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMseSourceBuffer(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MseSourceBufferList : winrt::Windows::Media::Core::IMseSourceBufferList
    {
        MseSourceBufferList(std::nullptr_t) noexcept {}
        MseSourceBufferList(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMseSourceBufferList(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) MseStreamSource : winrt::Windows::Media::Core::IMseStreamSource,
        impl::require<MseStreamSource, winrt::Windows::Media::Core::IMseStreamSource2>
    {
        MseStreamSource(std::nullptr_t) noexcept {}
        MseStreamSource(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMseStreamSource(ptr, take_ownership_from_abi) {}
        MseStreamSource();
        static auto IsContentTypeSupported(param::hstring const& contentType);
    };
    struct __declspec(empty_bases) SceneAnalysisEffect : winrt::Windows::Media::Core::ISceneAnalysisEffect
    {
        SceneAnalysisEffect(std::nullptr_t) noexcept {}
        SceneAnalysisEffect(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ISceneAnalysisEffect(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) SceneAnalysisEffectDefinition : winrt::Windows::Media::Effects::IVideoEffectDefinition
    {
        SceneAnalysisEffectDefinition(std::nullptr_t) noexcept {}
        SceneAnalysisEffectDefinition(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Effects::IVideoEffectDefinition(ptr, take_ownership_from_abi) {}
        SceneAnalysisEffectDefinition();
    };
    struct __declspec(empty_bases) SceneAnalysisEffectFrame : winrt::Windows::Media::Core::ISceneAnalysisEffectFrame,
        impl::require<SceneAnalysisEffectFrame, winrt::Windows::Media::Core::ISceneAnalysisEffectFrame2>
    {
        SceneAnalysisEffectFrame(std::nullptr_t) noexcept {}
        SceneAnalysisEffectFrame(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ISceneAnalysisEffectFrame(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) SceneAnalyzedEventArgs : winrt::Windows::Media::Core::ISceneAnalyzedEventArgs
    {
        SceneAnalyzedEventArgs(std::nullptr_t) noexcept {}
        SceneAnalyzedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ISceneAnalyzedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) SpeechCue : winrt::Windows::Media::Core::ISpeechCue
    {
        SpeechCue(std::nullptr_t) noexcept {}
        SpeechCue(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ISpeechCue(ptr, take_ownership_from_abi) {}
        SpeechCue();
    };
    struct __declspec(empty_bases) TimedMetadataStreamDescriptor : winrt::Windows::Media::Core::IMediaStreamDescriptor,
        impl::require<TimedMetadataStreamDescriptor, winrt::Windows::Media::Core::ITimedMetadataStreamDescriptor, winrt::Windows::Media::Core::IMediaStreamDescriptor2>
    {
        TimedMetadataStreamDescriptor(std::nullptr_t) noexcept {}
        TimedMetadataStreamDescriptor(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaStreamDescriptor(ptr, take_ownership_from_abi) {}
        explicit TimedMetadataStreamDescriptor(winrt::Windows::Media::MediaProperties::TimedMetadataEncodingProperties const& encodingProperties);
    };
    struct __declspec(empty_bases) TimedMetadataTrack : winrt::Windows::Media::Core::ITimedMetadataTrack,
        impl::require<TimedMetadataTrack, winrt::Windows::Media::Core::ITimedMetadataTrack2>
    {
        TimedMetadataTrack(std::nullptr_t) noexcept {}
        TimedMetadataTrack(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedMetadataTrack(ptr, take_ownership_from_abi) {}
        TimedMetadataTrack(param::hstring const& id, param::hstring const& language, winrt::Windows::Media::Core::TimedMetadataKind const& kind);
    };
    struct __declspec(empty_bases) TimedMetadataTrackError : winrt::Windows::Media::Core::ITimedMetadataTrackError
    {
        TimedMetadataTrackError(std::nullptr_t) noexcept {}
        TimedMetadataTrackError(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedMetadataTrackError(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) TimedMetadataTrackFailedEventArgs : winrt::Windows::Media::Core::ITimedMetadataTrackFailedEventArgs
    {
        TimedMetadataTrackFailedEventArgs(std::nullptr_t) noexcept {}
        TimedMetadataTrackFailedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedMetadataTrackFailedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) TimedTextBouten : winrt::Windows::Media::Core::ITimedTextBouten
    {
        TimedTextBouten(std::nullptr_t) noexcept {}
        TimedTextBouten(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextBouten(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) TimedTextCue : winrt::Windows::Media::Core::ITimedTextCue
    {
        TimedTextCue(std::nullptr_t) noexcept {}
        TimedTextCue(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextCue(ptr, take_ownership_from_abi) {}
        TimedTextCue();
    };
    struct __declspec(empty_bases) TimedTextLine : winrt::Windows::Media::Core::ITimedTextLine
    {
        TimedTextLine(std::nullptr_t) noexcept {}
        TimedTextLine(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextLine(ptr, take_ownership_from_abi) {}
        TimedTextLine();
    };
    struct __declspec(empty_bases) TimedTextRegion : winrt::Windows::Media::Core::ITimedTextRegion
    {
        TimedTextRegion(std::nullptr_t) noexcept {}
        TimedTextRegion(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextRegion(ptr, take_ownership_from_abi) {}
        TimedTextRegion();
    };
    struct __declspec(empty_bases) TimedTextRuby : winrt::Windows::Media::Core::ITimedTextRuby
    {
        TimedTextRuby(std::nullptr_t) noexcept {}
        TimedTextRuby(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextRuby(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) TimedTextSource : winrt::Windows::Media::Core::ITimedTextSource
    {
        TimedTextSource(std::nullptr_t) noexcept {}
        TimedTextSource(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextSource(ptr, take_ownership_from_abi) {}
        static auto CreateFromStream(winrt::Windows::Storage::Streams::IRandomAccessStream const& stream);
        static auto CreateFromUri(winrt::Windows::Foundation::Uri const& uri);
        static auto CreateFromStream(winrt::Windows::Storage::Streams::IRandomAccessStream const& stream, param::hstring const& defaultLanguage);
        static auto CreateFromUri(winrt::Windows::Foundation::Uri const& uri, param::hstring const& defaultLanguage);
        static auto CreateFromStreamWithIndex(winrt::Windows::Storage::Streams::IRandomAccessStream const& stream, winrt::Windows::Storage::Streams::IRandomAccessStream const& indexStream);
        static auto CreateFromUriWithIndex(winrt::Windows::Foundation::Uri const& uri, winrt::Windows::Foundation::Uri const& indexUri);
        static auto CreateFromStreamWithIndex(winrt::Windows::Storage::Streams::IRandomAccessStream const& stream, winrt::Windows::Storage::Streams::IRandomAccessStream const& indexStream, param::hstring const& defaultLanguage);
        static auto CreateFromUriWithIndex(winrt::Windows::Foundation::Uri const& uri, winrt::Windows::Foundation::Uri const& indexUri, param::hstring const& defaultLanguage);
    };
    struct __declspec(empty_bases) TimedTextSourceResolveResultEventArgs : winrt::Windows::Media::Core::ITimedTextSourceResolveResultEventArgs
    {
        TimedTextSourceResolveResultEventArgs(std::nullptr_t) noexcept {}
        TimedTextSourceResolveResultEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextSourceResolveResultEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) TimedTextStyle : winrt::Windows::Media::Core::ITimedTextStyle,
        impl::require<TimedTextStyle, winrt::Windows::Media::Core::ITimedTextStyle2, winrt::Windows::Media::Core::ITimedTextStyle3>
    {
        TimedTextStyle(std::nullptr_t) noexcept {}
        TimedTextStyle(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextStyle(ptr, take_ownership_from_abi) {}
        TimedTextStyle();
    };
    struct __declspec(empty_bases) TimedTextSubformat : winrt::Windows::Media::Core::ITimedTextSubformat
    {
        TimedTextSubformat(std::nullptr_t) noexcept {}
        TimedTextSubformat(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::ITimedTextSubformat(ptr, take_ownership_from_abi) {}
        TimedTextSubformat();
    };
    struct __declspec(empty_bases) VideoStabilizationEffect : winrt::Windows::Media::Core::IVideoStabilizationEffect
    {
        VideoStabilizationEffect(std::nullptr_t) noexcept {}
        VideoStabilizationEffect(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IVideoStabilizationEffect(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) VideoStabilizationEffectDefinition : winrt::Windows::Media::Effects::IVideoEffectDefinition
    {
        VideoStabilizationEffectDefinition(std::nullptr_t) noexcept {}
        VideoStabilizationEffectDefinition(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Effects::IVideoEffectDefinition(ptr, take_ownership_from_abi) {}
        VideoStabilizationEffectDefinition();
    };
    struct __declspec(empty_bases) VideoStabilizationEffectEnabledChangedEventArgs : winrt::Windows::Media::Core::IVideoStabilizationEffectEnabledChangedEventArgs
    {
        VideoStabilizationEffectEnabledChangedEventArgs(std::nullptr_t) noexcept {}
        VideoStabilizationEffectEnabledChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IVideoStabilizationEffectEnabledChangedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) VideoStreamDescriptor : winrt::Windows::Media::Core::IVideoStreamDescriptor,
        impl::require<VideoStreamDescriptor, winrt::Windows::Media::Core::IMediaStreamDescriptor2, winrt::Windows::Media::Core::IVideoStreamDescriptor2>
    {
        VideoStreamDescriptor(std::nullptr_t) noexcept {}
        VideoStreamDescriptor(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IVideoStreamDescriptor(ptr, take_ownership_from_abi) {}
        explicit VideoStreamDescriptor(winrt::Windows::Media::MediaProperties::VideoEncodingProperties const& encodingProperties);
    };
    struct __declspec(empty_bases) VideoTrack : winrt::Windows::Media::Core::IMediaTrack,
        impl::require<VideoTrack, winrt::Windows::Media::Core::IVideoTrack>
    {
        VideoTrack(std::nullptr_t) noexcept {}
        VideoTrack(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IMediaTrack(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) VideoTrackOpenFailedEventArgs : winrt::Windows::Media::Core::IVideoTrackOpenFailedEventArgs
    {
        VideoTrackOpenFailedEventArgs(std::nullptr_t) noexcept {}
        VideoTrackOpenFailedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IVideoTrackOpenFailedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) VideoTrackSupportInfo : winrt::Windows::Media::Core::IVideoTrackSupportInfo
    {
        VideoTrackSupportInfo(std::nullptr_t) noexcept {}
        VideoTrackSupportInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Core::IVideoTrackSupportInfo(ptr, take_ownership_from_abi) {}
    };
}
#endif

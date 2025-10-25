/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_MEDIAERROR_HPP
#define BB_MULTIMEDIA_MEDIAERROR_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile MediaError.hpp <bb/multimedia/MediaError>
 *
 * @brief The @c %MediaError class provides definitions for a number of media
 * error codes that can occur.
 *
 * @details The media error codes are one-to-one mappings to the
 * mm-renderer error codes (@c mm/renderer/types.h).
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/General"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT MediaError
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents possible media errors that can occur.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief No error has occurred.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief An unexpected internal error.
         *
         * @since BlackBerry 10.0.0
         */
        Internal = 1,

        /*!
         * @brief An invalid parameter.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidParameter = 2,

        /*!
         * @brief An illegal operation given the context state.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidState = 3,

        /*!
         * @brief An unrecognized input or output type or an out-of-range speed setting.
         *
         * @since BlackBerry 10.0.0
         */
        UnsupportedValue = 4,

        /*!
         * @brief A data format not recognized by any plugin.
         *
         * @since BlackBerry 10.0.0
         */
        UnsupportedMediaType = 5,

        /*!
         * @brief The file is DRM-protected.
         *
         * @since BlackBerry 10.0.0
         */
        DrmProtected = 6,

        /*!
         * @brief An illegal operation.
         *
         * @since BlackBerry 10.0.0
         */
        UnsupportedOperation = 7,

        /*!
         * @brief An I/O error at the source.
         *
         * @since BlackBerry 10.0.0
         */
        Read = 8,

        /*!
         * @brief An I/O error at the sink.
         *
         * @since BlackBerry 10.0.0
         */
        Write = 9,

        /*!
         * @brief Cannot open the source.
         *
         * @since BlackBerry 10.0.0
         */
        SourceUnavailable = 10,

        /*!
         * @brief Found corrupt data on the DVD.
         *
         * @since BlackBerry 10.0.0
         */
        ResourceCorrupted = 11,

        /*!
         * @brief Cannot open the sink (possibly because no plugin recognizes it).
         *
         * @since BlackBerry 10.0.0
         */
        OutputUnavailable = 12,

        /*!
         * @brief Insufficient memory to perform the requested operation.
         *
         * @since BlackBerry 10.0.0
         */
        OutOfMemory = 13,

        /*!
         * @brief A required resource such as an encoder or an output feed is presently unavailable.
         *
         * @since BlackBerry 10.0.0
         */
        ResourceUnavailable = 14,

        /*!
         * @brief The client has insufficient digital permissions to play the file.
         *
         * @since BlackBerry 10.0.0
         */
        DrmNoRights = 15,

        /*!
         * @brief The DRM data store is corrupted.
         *
         * @since BlackBerry 10.0.0
         */
        DrmCorruptedDataStore = 16,

        /*!
         * @brief A DRM output protection mismatch on an unspecified output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmOutputRestricted = 17,

        /*!
         * @brief A DRM output protection mismatch on an HDMI output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmHdmiOutputRestricted = 18,

        /*!
         * @brief A DRM output protection mismatch on a DISPLAYPORT output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmDisplayPortOutputRestricted = 19,

        /*!
         * @brief A DRM output protection mismatch on a DVI output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmDviOutputRestricted = 20,

        /*!
         * @brief A DRM output protection mismatch on a video ANALOG output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmAnalogVideoOutputRestricted = 21,

        /*!
         * @brief A DRM output protection mismatch on an audio ANALOG output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmAnalogAudioOutputRestricted = 22,

        /*!
         * @brief A DRM output protection mismatch on a TOSLINK output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmToslinkOutputRestricted = 23,

        /*!
         * @brief A DRM output protection mismatch on an S/PDIF output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmSpdifOutputRestricted = 24,

        /*!
         * @brief A DRM output protection mismatch on a BLUETOOTH output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmBluetoothOutputRestricted = 25,

        /*!
         * @brief A DRM output protection mismatch on a WIRELESSHD output.
         *
         * @since BlackBerry 10.0.0
         */
        DrmWirelessHdOutputRestricted = 26,

        /*!
         * @brief A DRM output protection mismatch on a WIFIDIRECT output.
         *
         * @since BlackBerry 10.3.0
         */
        DrmWifiDirectOutputRestricted = 27,

        /*!
         * @brief A license for the DRM file was found but has expired,
         * either because the play count has been depleted or the end time
         * has passed.
         *
         * @since BlackBerry 10.2.0
         */
        DrmExpiredLicense = 31,

        /*!
         * @brief A playback permission error (e.g., user prohibition,
         * region mismatch).
         *
         * @since BlackBerry 10.2.0
         */
        Permission = 32,

        /*!
         * @brief Playback interrupted by a failed API call.  This error code
         *  is used for an event but never returned as the error code from an API call.
         *
         * @since BlackBerry 10.3.0
         */
        CommandFailed = 33
    };

private:
    /*! @cond PRIVATE */
    MediaError();
    ~MediaError();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::MediaError)

#endif /* BB_MULTIMEDIA_MEDIAERROR_HPP */

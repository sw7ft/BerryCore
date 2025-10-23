/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_EQUALIZERPRESET_HPP
#define BB_MULTIMEDIA_EQUALIZERPRESET_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile EqualizerPreset.hpp <bb/multimedia/EqualizerPreset>
 *
 * @brief Represents the media player equilizer presets.
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.1
 */
class BB_MULTIMEDIA_EXPORT EqualizerPreset
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the media player equilizer preset.
     *
     * @since BlackBerry 10.3.1
     */
    enum Type {

        /*!
         *
         * @enum Type
         *
         * @brief Indicates that no equalizer preset will be used and no equalizer processing will be done.
         *
         * @since BlackBerry 10.3.1
         */
        Off = 0,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Airplane equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Airplane = 1,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Bass Boost equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        BassBoost = 2,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Treble Boost equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        TrebleBoost = 3,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Voice Boost equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        VoiceBoost = 4,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Bass Lower equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        BassLower = 5,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Treble Lower equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        TrebleLower = 6,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Voice Lower equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        VoiceLower = 7,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Acoustic equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Acoustic = 8,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Dance equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Dance = 9,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Electronic equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Electronic = 10,

        /*!
         * @enum Type
         *
         * @brief Indicates that the HipHop equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        HipHop = 11,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Jazz equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Jazz = 12,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Lounge equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Lounge = 13,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Piano equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Piano = 14,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Rhythm and Blues equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        RhythmAndBlues = 15,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Rock equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        Rock = 16,

        /*!
         * @enum Type
         *
         * @brief Indicates that the Spoken Word equalizer preset will be used.
         *
         * @since BlackBerry 10.3.1
         */
        SpokenWord = 17
    };

private:
    /*! @cond PRIVATE */
    EqualizerPreset();
    ~EqualizerPreset();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::EqualizerPreset)

#endif /* BB_MULTIMEDIA_EQUALIZERPRESET_HPP */

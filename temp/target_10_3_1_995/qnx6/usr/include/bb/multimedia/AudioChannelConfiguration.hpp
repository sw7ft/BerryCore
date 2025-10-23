/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_AUDIOCHANNELCONFIGURATION_HPP
#define BB_MULTIMEDIA_AUDIOCHANNELCONFIGURATION_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile AudioChannelConfiguration.hpp <bb/multimedia/AudioChannelConfiguration>
 *
 *
 * @brief Represents audio channel configuration.
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
class BB_MULTIMEDIA_EXPORT AudioChannelConfiguration
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the audio output options for a media player.
     *
     * @since BlackBerry 10.3.1
     */
    enum Type
    {
        /*!
         * @brief Represents default audio channel configuration.
         *
         * @since BlackBerry 10.3.1
         */
        Default = 0,

        /*!
         * @brief Represents monophonic audio channel configuration.
         *
         * @since BlackBerry 10.3.1
         */
        Mono = 1,

        /*!
         * @brief Represents stereophonic audio channel configuration.
         *
         * @since BlackBerry 10.3.1
         */
        Stereo = 2,
    };

private:
    /*! @cond PRIVATE */
    AudioChannelConfiguration();
    ~AudioChannelConfiguration();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::AudioChannelConfiguration)

#endif /* BB_MULTIMEDIA_AUDIOCHANNELCONFIGURATION_HPP */


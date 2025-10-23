/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_VIDEOOUTPUT_HPP
#define BB_MULTIMEDIA_VIDEOOUTPUT_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile VideoOutput.hpp <bb/multimedia/VideoOutput>
 *
 * @brief Represents the various video output devices.
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT VideoOutput
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the video output options for a media player.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief No video output device is to be attached.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief Video output will be directed to the device screen.
         *
         * @since BlackBerry 10.0.0
         */
        PrimaryDisplay = 1,

        /*!
         * @brief Video output will be directed to the secondary display.
         *
         * @since BlackBerry 10.0.0
         */
        SecondaryDisplay = 2

    };

private:
    /*! @cond PRIVATE */
    VideoOutput();
    ~VideoOutput();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::VideoOutput)

#endif /* BB_MULTIMEDIA_VIDEOOUTPUT_HPP */

/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_DEVICEMODE_HPP
#define BB_MULTIMEDIA_DEVICEMODE_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile DeviceMode.hpp <bb/multimedia/DeviceMode>
 *
 * @brief Represents the device mode of media player or recorder.
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
class BB_MULTIMEDIA_EXPORT DeviceMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief  Represents the device mode of media player or recorder.
     *
     * @since BlackBerry 10.3.1
     */
    enum Type
    {
        /*!
         * @brief Indicates that the media device is in playback mode.
         *
         * @since BlackBerry 10.3.1
         */
        Playback = 0,

        /*!
         * @brief Indicates that the media device is in capture mode.
         *
         * @since BlackBerry 10.3.1
         */
        Capture = 1,
    };

private:
    /*! @cond PRIVATE */
    DeviceMode();
    ~DeviceMode();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::DeviceMode)

#endif /* BB_MULTIMEDIA_DEVICEMODE_HPP */

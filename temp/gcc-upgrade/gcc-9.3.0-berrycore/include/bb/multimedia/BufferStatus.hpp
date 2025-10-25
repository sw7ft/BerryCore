/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_BUFFERSTATUS_HPP
#define BB_MULTIMEDIA_BUFFERSTATUS_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile BufferStatus.hpp <bb/multimedia/BufferStatus>
 *
 * @brief Represents the current buffer status of the media player.
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
class BB_MULTIMEDIA_EXPORT BufferStatus
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the current buffer status of the media player.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates that the buffer is idle and not being filled.
         *
         * @since BlackBerry 10.0.0
         */
        Idle = 0,

        /*!
         * @brief Indicates that the buffer is being filled, and that no playback is occurring.
         *
         * @since BlackBerry 10.0.0
         */
        Buffering = 1,

        /*!
         * @brief Indicates that the buffer is being filled, and that playback is occurring.
         *
         * @since BlackBerry 10.0.0
         */
        Playing = 2,
    };

private:
    /*! @cond PRIVATE */
    BufferStatus();
    ~BufferStatus();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::BufferStatus)

#endif /* BB_MULTIMEDIA_BUFFERSTATUS_HPP */

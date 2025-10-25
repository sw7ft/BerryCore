/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_MEDIAKEYNOTIFICATION_HPP
#define BB_MULTIMEDIA_MEDIAKEYNOTIFICATION_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile MediaKeyNotification.hpp <bb/multimedia/MediaKeyNotification>
 *
 * @brief Represents a hardware media key notification type used with
 * @c MediaKeyWatcher.
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/General"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.1.0
 */
class BB_MULTIMEDIA_EXPORT MediaKeyNotification
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the media key notification types.
     *
     * @since BlackBerry 10.1.0
     */
    enum Type
    {
        /*!
         * @brief Indicates notification takes place when the key is released.
         *
         * @since BlackBerry 10.1.0
         */
        Clicked = 0,

        /*!
         * @brief Indicates notification takes place on the key press threshold.
         *
         * @since BlackBerry 10.1.0
         */
        Threshold = 1,
    };

private:
    /*! @cond PRIVATE */
    MediaKeyNotification();
    ~MediaKeyNotification();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::MediaKeyNotification)

#endif /* BB_MULTIMEDIA_MEDIAKEYNOTIFICATION_HPP */


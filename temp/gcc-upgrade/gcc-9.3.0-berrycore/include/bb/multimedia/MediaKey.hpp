/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_MEDIAKEY_HPP
#define BB_MULTIMEDIA_MEDIAKEY_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile MediaKey.hpp <bb/multimedia/MediaKey>
 *
 *
 * @brief Represents a hardware media key used with @c MediaKeyWatcher.
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
class BB_MULTIMEDIA_EXPORT MediaKey
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents a hardware media key.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Represents no set media button.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief Represents the fast forward hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        FastForward = 1,

        /*!
         * @brief Represents the pause hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        Pause = 2,

        /*!
         * @brief Represents the play hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        Play = 3,

        /*!
         * @brief Represents the dual play/pause hardware toggle button.
         *
         * @since BlackBerry 10.0.0
         */
        PlayPause = 4,

        /*!
         * @brief Represents the rewind hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        Rewind = 5,

        /*!
         * @brief Represents the stop hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        Stop = 6,

        /*!
         * @brief Represents the volume down hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        VolumeDown = 7,

        /*!
         * @brief Represents the volume up hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        VolumeUp = 8,

        /*!
         * @brief Represents the previous track hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        Previous = 9,

        /*!
         * @brief Represents the next track hardware button.
         *
         * @since BlackBerry 10.0.0
         */
        Next = 10,
    };

private:
    /*! @cond PRIVATE */
    MediaKey();
    ~MediaKey();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::MediaKey)

#endif /* BB_MULTIMEDIA_MEDIAKEY_HPP */

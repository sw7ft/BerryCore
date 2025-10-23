/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_SHUFFLEMODE_HPP
#define BB_MULTIMEDIA_SHUFFLEMODE_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile ShuffleMode.hpp <bb/multimedia/ShuffleMode>
 *
 * @brief Represents the various shuffle modes.
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_MULTIMEDIA_EXPORT ShuffleMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the various shuffle modes.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type {

        /*!
         * @brief Indicates that the shuffle feature is not supported.
         *
         * @since BlackBerry 10.3.0
         */
        Unsupported = 0,

        /*!
         * @brief Indicates that no shuffling has taken place.
         *
         * @since BlackBerry 10.3.0
         */
        Off = 1,

        /*!
         * @brief Indicates that all tracks have been shuffled.
         *
         * @since BlackBerry 10.3.0
         */
        All = 2,
    };

private:
    /*! @cond PRIVATE */
    ShuffleMode();
    ~ShuffleMode();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::ShuffleMode)

#endif /* BB_MULTIMEDIA_SHUFFLEMODE_HPP */

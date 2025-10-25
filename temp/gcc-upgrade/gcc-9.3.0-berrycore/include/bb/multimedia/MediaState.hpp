/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_MEDIASTATE_HPP
#define BB_MULTIMEDIA_MEDIASTATE_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile MediaState.hpp <bb/multimedia/MediaState>
 *
 * @brief Represents the possible media playback and recording states.
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
class BB_MULTIMEDIA_EXPORT MediaState
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the possible media playback and recording states.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief All media resources have not been acquired.
         *
         * @since BlackBerry 10.0.0
         */
        Unprepared = 0,

        /*!
         * @brief All media resources have been acquired.
         *
         * @since BlackBerry 10.0.0
         */
        Prepared = 1,

        /*!
         * @brief Media is actively progressing.
         *
         * @since BlackBerry 10.0.0
         */
        Started = 2,

        /*!
         * @brief Media progress is interrupted and will resume from its current position.
         *
         * @since BlackBerry 10.0.0
         */
        Paused = 3,

        /*!
         * @brief Media progress is stopped.
         *
         * @since BlackBerry 10.0.0
         */
        Stopped = 4,
    };

private:
    /*! @cond PRIVATE */
    MediaState();
    ~MediaState();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::MediaState)

#endif /* BB_MULTIMEDIA_MEDIASTATE_HPP */

/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_PRIORITYLEVEL_HPP
#define BB_MULTIMEDIA_PRIORITYLEVEL_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile PriorityLevel.hpp <bb/multimedia/PriorityLevel>
 *
 * @brief Represents a connection priority level
 *
 * @details The priority level indicates whether the connection can be
 * preempted/acquired by other connections. The following is indicating
 * the preempting/acquiring rules for two connections depending on priority
 * level, where conneciton A has already acquired and connection B is
 * trying to acquire nowplaying service.
 * A-low, B-low. A is revoked.
 * A-low, B-high. A is preempted.
 * A-high, B-low. B fails to acquire.
 * A-high, B-high. A is preempted.
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
class BB_MULTIMEDIA_EXPORT PriorityLevel
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the connection priority level
     *
     * @since BlackBerry 10.3.0
     */
    enum Type
    {
        /*!
         * @brief Indicates the lowest priority level. All low
         * priority processes can be preempted by higher priority processes.
         * Processes with the same priority level cannot preempt one another.
         *
         * @since BlackBerry 10.3.0
         */
        Low = 0,

        /*!
         * @brief Indicates highest priority level.
         *
         * @since BlackBerry 10.3.0
         */
        High = 1,
    };

private:
    /*! @cond PRIVATE */
    PriorityLevel();
    ~PriorityLevel();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::PriorityLevel)

#endif /* BB_MULTIMEDIA_PRIORITYLEVEL_HPP */

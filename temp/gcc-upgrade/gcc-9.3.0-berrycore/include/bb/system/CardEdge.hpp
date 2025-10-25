/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_CARDEDGE_HPP
#define BB_SYSTEM_CARDEDGE_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile CardEdge.hpp <bb/system/CardEdge>
 *
 * @brief Values describing the edges of the device.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT CardEdge
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Values describing the edges of the device.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        
        /*!
         * @brief The edge type was not specified.
         *
         * @since BlackBerry 10.0.0
         */
        Unspecified = 0,
        
        /*!
         *  @brief The top of the device.
         *
         * @since BlackBerry 10.0.0
         */
        Top = 1,

        /*!
         * @brief The bottom of the device.
         *
         * @since BlackBerry 10.0.0
         */
        Bottom = 2,

        /*!
         * @brief The left side of the device.
         *
         * @since BlackBerry 10.0.0
         */
        Left = 3,

        /*!
         * @brief The right side of the device.
         *
         * @since BlackBerry 10.0.0
         */
        Right = 4,
    };

private:
//!@cond PRIVATE
    CardEdge();
    ~CardEdge();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::CardEdge)
#endif // BB_SYSTEM_CARDEDGE_HPP

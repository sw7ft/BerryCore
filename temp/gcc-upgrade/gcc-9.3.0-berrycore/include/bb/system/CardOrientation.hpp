/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_CARDORIENTATION_HPP
#define BB_SYSTEM_CARDORIENTATION_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile CardOrientation.hpp <bb/system/CardOrientation>
 *
 * @brief The list of device orientations.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT CardOrientation
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The list of device orientations.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        
        /*!
         * @brief The orientation is not known.
         *
         * @since BlackBerry 10.0.0
         */
        Unspecified = 0,
        
        /*!
         * @brief The device is in a portrait orientation.
         *
         * @since BlackBerry 10.0.0
         */
        Portrait = 1,

        /*!
         * @brief The device is in a landscape orientation.
         *
         * @since BlackBerry 10.0.0
         */
        Landscape = 2,
    };

private:
//!@cond PRIVATE
    CardOrientation();
    ~CardOrientation();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::CardOrientation)
#endif // BB_SYSTEM_CARDORIENTATION_HPP

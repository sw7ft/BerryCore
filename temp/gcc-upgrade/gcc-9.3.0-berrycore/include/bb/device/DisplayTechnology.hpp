/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_DISPLAYTECHNOLOGY_HPP
#define BB_DEVICE_DISPLAYTECHNOLOGY_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile DisplayTechnology.hpp <bb/device/DisplayTechnology>
 *
 * @brief The set of possible display technologies.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.1.0
 */
class BB_DEVICE_EXPORT DisplayTechnology
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible display technologies.
     *
     * @since BlackBerry 10.1.0
     */
    enum Type
    {
        /*!
         * @brief The display technology could not be determined.
         *
         * @since BlackBerry 10.1.0
         */
        Unknown     = 0,

        /*!
         * @brief All active and passive matrix LCDs.
         *
         * @since BlackBerry 10.1.0
         */
        Lcd         = 1,

        /*!
         * @brief Organic LED/OEL displays.
         *
         * @since BlackBerry 10.1.0
         */
        Oled        = 2,

        /*!
         * @brief All monochrome and standard tricolor CRTs.
         *
         * @since BlackBerry 10.1.0
         */
        Crt         = 3,

        /*!
         * @brief All PDP types including DC and AC plasma displays.
         *
         * @since BlackBerry 10.1.0
         */
        Plasma      = 4,

        /*!
         * @brief Inorganic LED displays.
         *
         * @since BlackBerry 10.1.0
         */
        Led         = 5
    };

private:
//!@cond PRIVATE
    DisplayTechnology();
    ~DisplayTechnology();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::DisplayTechnology)
#endif // BB_DEVICE_DISPLAYTECHNOLOGY_HPP

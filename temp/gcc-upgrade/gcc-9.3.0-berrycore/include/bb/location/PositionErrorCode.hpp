/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_LOCATION_POSITIONERRORCODE_HPP
#define BB_LOCATION_POSITIONERRORCODE_HPP

#include <bb/location/Global>

#include <QObject>
#include <QMetaType>

namespace bb
{
namespace location
{

/*!
 * @headerfile PositionErrorCode.hpp <bb/location/PositionErrorCode>
 *
 * @brief Error codes returned by the Location Manager in the event of a location request timeout.
 *
 * @details The Location Manager returns these codes in the event of difficulty while try to get a
 * position fix. There are two types of codes, warning and fatal. A warning code indicates that
 * position updates have stopped but that the Location Manager will automatically resume updates
 * if conditions change. A fatal code indicates that position updates have stopped and the Location
 * Manager has abandoned the location request(s).
 *
 *  @xmlonly
 *  <apigrouping group="Location/Positioning and Geocoding"/>
 *  <library name="QtLocationSubset"/>
 *  @endxmlonly
 */
class BB_LOCATION_EXPORT PositionErrorCode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Error codes returned by the Location Manager in the event of a location request timeout.
     */
    enum Type {
        /*!
         * @brief No error.
         */
        None = 0x00000,

        /*!
         * @brief Location services are disabled.
         */
        FatalDisabled = 0x00001,

        /*!
         * @brief There is no last known position on the device.
         */
        FatalNoLastKnownPosition = 0x00002,

        /*!
         * @brief There are insufficient available location technology providers to process your request.
         */
        FatalInsufficientProviders = 0x00003,

        /*!
         * @brief One or more of the request parameters are invalid.
         */
        FatalInvalidRequest = 0x00004,

        /*!
         * @brief An unknown service error has occurred.
         */
        FatalUnknown = 0x00005,

        /*!
         * @brief The app does not have permission to access location services, that is, the @c access_location_services permission must be set in
         * the app's bar-descriptor.xml, and the user must allow the app to have this permission.
         */
        FatalPermission = 0x00006,

        /*!
         * @brief A timeout has occurred while processing your request. The request will continue until your location is obtained.
         */
        WarnTimeout = 0x10000,

        /*!
         * @brief The location fix has been lost due to insufficient coverage. The request will continue until your location is reacquired.
         */
        WarnLostTracking = 0x10001,

        /*!
         * @brief The device is stationary. No further updates until the device resumes movement. This code is encountered only if the stationaryDetection
         * property of the QtLocationSubset::QGeoPositionInfoSource class is set to true.
         */
        WarnStationary = 0x10002,

    };

private:
//!@cond PRIVATE
    PositionErrorCode();
    ~PositionErrorCode();
//!@endcond PRIVATE
};

} // namespace location
} // namespace bb

Q_DECLARE_METATYPE(bb::location::PositionErrorCode::Type)

#endif // BB_LOCATION_POSITIONERRORCODE_HPP

/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PLACES_SELECTEDPLACE_HPP
#define BB_CASCADES_PLACES_SELECTEDPLACE_HPP

/*!
 * @file SelectedPlace.hpp
 *
 * @since BlackBerry 10.0.0
 */

#include <bb/cascades/places/Global>
#include <bb/cascades/places/SelectedPlaceImageType>

#include <QtDeclarative/QtDeclarative>
#include <QUrl>
#include <QString>

namespace bb
{
namespace cascades
{
namespace places
{

class SelectedPlacePrivate;

/*!
 * @class SelectedPlace
 *
 * @brief An object returned by @c PlacePicker.
 *
 * @details @c SelectedPlace contains
 * the value of the place object that the user selected, which comes from
 * the places database or the results of an online search.
 *
 * @headerfile SelectedPlace.hpp <bb/cascades/places/SelectedPlace>
 *
 * @xmlonly
 * <apigrouping group="Location/Places"/>
 * <library name="bbcascadesplaces"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PLACES_EXPORT SelectedPlace : public QObject
{
    Q_OBJECT

    /*!
     * @brief Indicates whether the selected place is a physical location or not.
     *
     * @details A Boolean value of @c true indicates the place has latitude and longitude coordinates,
     * @c false indicates the selected location is not a physical location.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool isPhysicalLocation READ isPhysicalLocation CONSTANT FINAL);

    /*!
     * @brief Represents the system identifier of the selected place.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int placeId READ id CONSTANT FINAL);

    /*!
     * @brief Represents user-defined place name if available.
     *
     * @details By default, the user defined place name is
     * the same as the alternative name for point of interest (POI) and contact.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString name READ name CONSTANT FINAL);

    /*!
     * @brief Represents the place's alternative name if available.
     *
     * @details The value of this property is the official name of the selected
     * place such as the name of a business, POI, or a contact obtained from a search.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString alternativeName READ alternativeName CONSTANT FINAL);

    /*!
     * @brief Represents the place's description if available.
     *
     * @details This is a short description of the place.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString description READ description CONSTANT FINAL);

    /*!
     * @brief Represents the place's street address if available.
     *
     * @details If the place is a physical location, this property is the street
     * address. If this information is not available (for example the selected place is a city),
     * the value of this property is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString street READ street CONSTANT FINAL);

    /*!
     * @brief Represents the place's city name if available.
     *
     * @details This property is the city name of the selected place. If this
     * information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString city READ city CONSTANT FINAL);

    /*!
     * @brief Represents the place's region name such as State or Province if available.
     *
     * @details The value of this property is the state or
     * province name of the place. If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString region READ region CONSTANT FINAL);

    /*!
     * @brief Represents the place's country name if available.
     *
     * @details The value of this property is the country name of the place.
     * If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString country READ country CONSTANT FINAL);

    /*!
     * @brief Represents the place's ISO 3166 alpha 3 country code if available.
     *
     * @details The value of this property is the three-letter code established
     * by the ISO 3166 Alpha 3 standard that uniquely represents the country.
     * If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString isoAlpha3CountryCode READ isoAlpha3CountryCode CONSTANT FINAL);

    /*!
     * @brief Represents the place's ISO 3166 alpha 2 country code if available.
     *
     * @details The value of this property is the two-letter code established
     * by the ISO 3166 Alpha 2 standard that uniquely represents the country.
     * If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString isoAlpha2CountryCode READ isoAlpha2CountryCode CONSTANT FINAL);

    /*!
     * @brief Represents the place's postal code if available.
     *
     * @details The value of this property is the postal code of the place.
     * If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString postal READ postal CONSTANT FINAL);

    /*!
     * @brief Represents the complete address label if available.
     *
     * @details The value of this property is a fully formatted address
     * in accordance to local address standards. If the place is not a physical place, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString addressLabel READ addressLabel CONSTANT FINAL);

    /*!
     * @brief Represents the place's main phone number if available.
     *
     * @details The value of this property is the main phone number
     * of the place. If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString phone READ phone CONSTANT FINAL);

    /*!
     * @brief Represents the place's secondary phone number if available.
     *
     * @details The value of this property is the secondary
     * phone number of the place. If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString secondaryPhone READ secondaryPhone CONSTANT FINAL);

    /*!
     * @brief Represents the place's fax number if available.
     *
     * @details The value of this property is the fax number of the place.
     * If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString fax READ fax CONSTANT FINAL);

    /*!
     * @brief Represents the place's email address if available.
     *
     * @details The value of this property is the email address
     * associated with the place. If this information is not available, the value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString email READ email CONSTANT FINAL);

    /*!
     * @brief Represents the place's web site URL if available.
     *
     * @details The value of this property is the web site of the place.
     * If this information is not available, this method returns an empty object.
     * To correctly represent a clickable URL to the user, please use the
     * @c QUrl::toEncoded() function instead of @c QUrl::toString().
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl url READ url CONSTANT FINAL);

    /*!
     * @brief Represents the place's rating if available.
     *
     * @details If a place is a business, the value is its rating. If the rating
     * information is not available, the value is a quiet NaN. Rating range is TBD.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double rating READ rating CONSTANT FINAL);

    /*!
     * @brief Represents the place's map link URL if available.
     *
     * @details The value of this property is the map URL of the place.
     * If this information is not available, the value is an empty object.
     * To correctly represent a clickable URL to the user, please use the
     * @c QUrl::toEncoded() function instead of @c QUrl::toString().
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl mapURL READ mapURL CONSTANT FINAL);

    /*!
     * @brief Represents the place's map image if available.
     *
     * @details The value of this property is the static image of the place.
     * Inside the @c QVariant it is a @c bb::cascades::Image class object set by @c QVariant::fromValue(). If this information
     * is not available (for example, this place is not a physical location or the location of this place
     * is out of map data coverage), this value is an empty object.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant image READ image CONSTANT FINAL);

    /*!
     * @brief Represents the place's latitude coordinate if available.
     *
     * @details The value of this property is the latitude coordinate
     * of the place. If the place is not a physical location, this value is a quiet NaN.
     * You can use <code>if (!isNaN(var.latitude))</code> to check if the value is valid or not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double latitude READ latitude CONSTANT FINAL);

    /*!
     * @brief Represents the place's longitude coordinate if available.
     *
     * @details The value of this property is the longitude coordinate
     * of the place. If the place is not a physical location, this value is a quiet NaN.
     * You can use <code>if (!isNaN(var.longitude))</code> to check if the value is valid or not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double longitude READ longitude CONSTANT FINAL);

    /*!
     * @brief Represents the place's altitude if available.
     *
     * @details The value of this property is the altitude
     * of the place. If the place is not a physical location or altitude information is not available,
     * this value is a quiet NaN.
     * You can use <code>if (!isNaN(var.altitude))</code> to check if the value is valid or not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double altitude READ altitude CONSTANT FINAL);

    /*!
     * @brief Represents the accuracy of the place's latitude and longitude data.
     *
     * @details This property is valid only if the latitude and
     * longitude data are available and their accuracy data is available. If the place is not
     * a physical location, or accuracy data is not available, this value is a quiet NaN.
     * You can use <code>if (!isNaN(var.horizontalAccuracy))</code> to check if the value is valid or not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double horizontalAccuracy READ horizontalAccuracy CONSTANT FINAL);

    /*!
     * @brief Represents accuracy of the place's altitude data.
     *
     * @details This property is valid only if the altitude is available and its
     * accuracy data is available. If the place is not a physical location, or accuracy
     * data is not available, this value is a quiet NaN.
     * You can use <code>if (!isNaN(var.verticalAccuracy))</code> to check if the value is valid or not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double verticalAccuracy READ verticalAccuracy CONSTANT FINAL);

public:
    /*!
     * @brief Default destructor
     *
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SelectedPlace();

public:

    /*!
     * @brief Indicates whether the selected place is a physical location or not.
     *
     * @return @c true indicates the place has latitude and longitude coordinates,
     * @c false indicates the selected location is not a physical location.
     *
     *
     * @since BlackBerry 10.0.0
     */
    bool isPhysicalLocation() const;

    /*!
     * @brief Returns the system identifier of the selected place.
     *
     * @return int The system identifier of the selected place.
     *
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;

    /*!
     * @brief Returns the user-defined place name if available.
     *
     * @details By default, the user defined place name is
     * the same as the alternative name for point of interest (POI) and contact.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Returns the place's alternative name if available.
     *
     * @details This method returns the official name of the selected place such as
     * the name of a business, POI, or a contact obtained from a search.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString alternativeName() const;

    /*!
     * @brief Returns the place's description if available.
     *
     * @details This method returns the short description of the place.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString description() const;

    /*!
     * @brief Returns the place's street address if available.
     *
     * @details If the place is a physical location, this method returns the street
     * address. If this information is not available (for example, the selected place is a city),
     * this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString street() const;

    /*!
     * @brief Returns the place's city name if available.
     *
     * @details This method returns the city name of the selected place. If this
     * information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString city() const;

    /*!
     * @brief Returns the place's region name such as State or Province if
     * available.
     *
     * @details This method returns the state or province name of the place. If this
     * information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString region() const;

    /*!
     * @brief Returns the place's country name if available.
     *
     * @details This method returns the country name of the place. If this information
     * is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString country() const;

    /*!
     * @brief Returns the place's ISO 3166 alpha 3 country code if available.
     *
     * @details This method returns the three-letter code established by the
     * ISO 3166 Alpha 3 standard that uniquely represents the country. If
     * this information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.2.0
     */
    QString isoAlpha3CountryCode() const;

    /*!
     * @brief Returns the place's ISO 3166 alpha 2 country code if available.
     *
     * @details This method returns the two-letter code established by the
     * ISO 3166 Alpha 2 standard that uniquely represents the country. If
     * this information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.2.0
     */
    QString isoAlpha2CountryCode() const;

    /*!
     * @brief Returns the place's postal code if available.
     *
     * @details This method returns the postal code of the place. If this information
     * is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString postal() const;

    /*!
     * @brief Returns the complete address label if available.
     *
     * @details This method returns a fully formatted address in accordance to local
     * address standards. If the place is not a physical place, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString addressLabel() const;

    /*!
     * @brief Returns the place's main phone number if available.
     *
     * @details This method returns the main phone number of the place. If this
     * information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString phone() const;

    /*!
     * @brief Returns the place's secondary phone number if available.
     *
     * @details This method returns the secondary phone number of the place. If this
     * information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString secondaryPhone() const;

    /*!
     * @brief Returns the place's fax number if available.
     *
     * @details This method returns the fax number of the place. If this
     * information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString fax() const;

    /*!
     * @brief Returns the place's email address if available.
     *
     * @details This method returns the email address associated with the place. If
     * this information is not available, this method returns an empty string.
     *
     * @return QString
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString email() const;

    /*!
     * @brief Returns the place's web site URL if available.
     *
     * @details This method returns the web site of the place. If this information
     * is not available, this method returns an empty object.
     * To correctly represent a clickable URL to the user, please use the
     * @c QUrl::toEncoded() function instead of @c QUrl::toString().
     *
     * @return QUrl
     *
     *
     * @since BlackBerry 10.0.0
     */
    QUrl url() const;

    /*!
     * @brief Returns the place's rating if available.
     *
     * @details If a place is a business, this method returns its rating. If the rating
     * information is not available, this method returns a quiet NaN. Rating range is TBD.
     *
     * @return double
     *
     * @see @c POIAuxiliaryData
     *
     * @since BlackBerry 10.0.0
     */
    double rating() const;

    /*!
     * @brief Returns the place's map link URL if available.
     *
     * @details This method returns the map URL of the place. If this information
     * is not available, this method returns an empty object.
     * To correctly represent a clickable URL to the user, please use the
     * @c QUrl::toEncoded() function instead of @c QUrl::toString().
     *
     * @return QUrl
     *
     *
     * @since BlackBerry 10.0.0
     */
    QUrl mapURL() const;

    /*!
     * @brief Returns the place's map image if available, and its type.
     *
     * @details This method returns binary data of a static image of the place. If this information
     * is not available (for example, the place is not a physical location or the location of this place
     * is out of map data coverage), this method returns an empty object.
     * This method is also used for JSON encoding.
     *
     * @warning This is a blocking function that may require network access and should
     * not be used on the event thread. To retrieve the image asynchronously, use the
     * @c MapImageGenerator class.
     *
     * @param[out] imageType SelectedPlaceImageType.
     *
     * @return QByteArray
     *
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray getRawImage(SelectedPlaceImageType::Type& imageType) const;

    /*!
     * @brief Returns the place's map image if available.
     *
     * @details This method returns the static image of the place. Inside the
     * @c QVariant is a @c bb::cascades::Image class object set by @c QVariant::fromValue().
     * If this information is not available (i.e. not a physical location, location
     * is out of map data coverage), this method returns an empty object.
     *
     * @warning This is a blocking function that may require network access and should
     * not be used on the event thread. To retrieve the image asynchronously, use the
     * @c MapImageGenerator class.
     *
     * @return QVariant
     *
     * @since BlackBerry 10.0.0
     */
    QVariant image() const;

    /*!
     * @brief Returns the place's latitude coordinate if available.
     *
     * @details This method returns the latitude coordinate of the place, in decimal degrees. If the
     * place is not a physical location, this method returns a quiet NaN.
     *
     * @return double
     *
     *
     * @since BlackBerry 10.0.0
     */
    double latitude() const;

    /*!
     * @brief Returns the place's longitude coordinate if available.
     *
     * @details This method returns the longitude coordinate of the place, in decimal degrees. If the
     * place is not a physical location, this method returns a quiet NaN.
     *
     * @return double
     *
     *
     * @since BlackBerry 10.0.0
     */
    double longitude() const;

    /*!
     * @brief Returns the place's altitude relative to sea level, in meters, if available.
     *
     * @details This method returns the altitude of the place, relative to sea level, in meters.
     * If the place is not a physical location, or altitude data is not available, this method
     * returns a quiet NaN.
     *
     * @return double
     *
     *
     * @since BlackBerry 10.0.0
     */
    double altitude() const;

    /*!
     * @brief Returns the accuracy of the place's latitude and longitude data.
     *
     * @details This value is valid only if
     * latitude and longitude data are available and their accuracy data is available.
     *
     * The method returns the accuracy of place's latitude and longitude in meters.
     * If the place is not a physical location, or accuracy data is not available,
     * this method returns a quiet NaN.
     *
     * @return double
     *
     *
     * @since BlackBerry 10.0.0
     */
    double horizontalAccuracy() const;

    /*!
     * @brief Returns the accuracy of the place's altitude data.
     *
     * @details This value is valid only if
     * altitude data is available and its accuracy data is available.
     *
     * The method returns the accuracy of place's altitude in meters.
     * If the place is not a physical location, or accuracy data is not available,
     * this method returns a quiet NaN.
     *
     * @return double
     *
     *
     * @since BlackBerry 10.0.0
     */
    double verticalAccuracy() const;

private:
    /*!
     * @brief constructor
     *
     * @since BlackBerry 10.0.0
     */
    explicit SelectedPlace(QObject *parent = 0);

    Q_DISABLE_COPY(SelectedPlace)
    Q_DECLARE_PRIVATE(SelectedPlace)

    QScopedPointer<SelectedPlacePrivate> d_ptr;

};

} // namespace places
} // namespace cascades
} // namespace bb

/*!
 * @brief Make the type visible to the meta object system.
 *
 * @since BlackBerry 10.0.0
 */
QML_DECLARE_TYPE(bb::cascades::places::SelectedPlace);

#endif // BB_CASCADES_PLACES_SELECTEDPLACE_HPP

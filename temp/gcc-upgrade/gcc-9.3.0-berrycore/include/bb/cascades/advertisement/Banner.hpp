/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_ADVERTISEMENT_BANNER_HPP
#define BB_CASCADES_ADVERTISEMENT_BANNER_HPP

#include <bb/cascades/advertisement/Global>
#include <bb/cascades/Color>
#include <bb/cascades/CustomControl>

namespace bb {
namespace cascades {
namespace advertisement {

class BannerPrivate;
/*!
 *
 * @brief The Banner class is a Custom control that allows users to create and add ad banners to a screen.
 *
 * A Banner consists of a unique zone id that is assigned to you for your application by Research In Motion.
 * Your application sends the zoneId parameter to the Advertising Service mediation layer with each ad request.
 * After the mediation layer receives an ad request, the server evaluates the request based on the statistics
 * that are associated with the zone ID, sends the request to the appropriate ad network, and returns an ad to
 * your application. One zoneId can be used with multiple Banner objects in your application.
 *
 * You can also define the frequency at which the application makes ad requests, and a placeholder image for the
 * display area.
 *
 * You can specify the size of the ads using the width and height properties.
 *
 * By default, when an application loads a new ad or transitions between ads, the application displays a black
 * transition effect that makes the ads appear to fade in or fade out. You can turn off the transition effect by
 * setting the transitionsEnabled property to false.
 *
 * @code
 * transitionsEnabled : false
 * @endcode
 *
 * When a BlackBerry device user selects an ad, the application displays a blue border around the ad. You can change
 * the color of the border by setting borderColor property to a color that is supported by the @c Color class.
 * For example, to change the border color to red, you can set:
 *
 * @code 
 * borderColor: Color.RED 
 * @endcode
 *
 * You can also specify a placeholder image to display when an application is waiting to receive an ad from an ad
 * network. You can provide a URL to your own placeholder image. By default, a transparent placeholder image with a
 * border is displayed.
 *
 * @xmlonly
 * <qml>
 * <class register="yes"/>
 * </qml>
 * <apigrouping group="Platform/Ad service"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 *
 */
class BB_CASCADES_ADVERTISEMENT_EXPORT Banner: public bb::cascades::CustomControl
{
    Q_OBJECT

    /*!
     * @brief The zone id of the publisher site.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( int zoneId READ zoneId WRITE setZoneId NOTIFY zoneIdChanged FINAL )

    /*!
     * @brief The frequency that the @c %Banner object makes requests for new ads (optional).
     *
     * The default value is 60 seconds and any value less than 60 seconds defaults to 60 seconds
     * as this is the minimum frequency that is supported.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( unsigned int refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged FINAL )

    /*!
     * @brief A URL to the placeholder image for the ad banner to be displayed when an ad banner isn't loaded.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QUrl placeHolderURL READ placeHolderURL WRITE setPlaceHolderURL NOTIFY placeHolderURLChanged FINAL )

    /*!
     * @brief Sets the color of the background for the display area of an ad banner.
     *     
     * The default color is <code>Color.White</code>.
     * You can change the color to any color that is supported by @c %Color class.
     *
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::Color"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QVariant backgroundColor READ backgroundColor WRITE setBackgroundColorQML NOTIFY backgroundColorChanged FINAL )

    /*!
     * @brief Turns on or turns off the ad transition effect.
     *
     * The ad transition effect makes ads appear to fade in or fade out when a new ad
     * is loading or ads are changing. By default, the transition effect is set to true.
     * To turn off the transition effect, set @c transitionsEnabled to @c False.
     *
     * @code
     * transitionsEnabled : False
     * @endcode
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bool transitionsEnabled READ isTransitionsEnabled WRITE setTransitionsEnabled NOTIFY transitionsEnabledChanged FINAL)

    /*!
     * @brief Sets the border thickness of the display area for an Ad banner.
     *
     * @xmlonly
     * <qml>
     * <property name="borderWidth"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( unsigned int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged FINAL )

    /*!
     * @brief Sets the color of the focus border for the display area of an ad banner.
     *
     * The default color for the focus border is <code>Color.Blue</code>.
     * You can change the color of the focus border to any color supported by the @c Color class.
     *
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::Color"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QVariant borderColor READ borderColor WRITE setBorderColorQML NOTIFY borderColorChanged FINAL )

public:
    /*!
     * @brief Constructs a Banner and adds it to a parent container.
     *
     * Specifying the parent container is optional.
     *
     * Here is a QML sample demonstrating the use of a %Banner.
     * @code
     * import bb.cascades.advertising 1.0
     *
     * Container {
     *     Banner {
     *         zoneId: 12345
     *         preferredWidth: 728; preferredHeight: 90
     *         placeHolderURL: "asset:///images/myLogo.png"
     *     }
     * }
     * @endcode
     *
     * @param container The parent container is an optional parameter that defaults to @c 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    Banner(bb::cascades::Container *container = 0);
    virtual ~Banner();

    /*!
     * @brief Returns the zoneId for the banner.
     *
     * @return The zone id of the publisher site.
     *
     * @since BlackBerry 10.0.0
     */
    int zoneId() const;

    /*!
     * @brief Sets the zoneId of the banner.
     *
     * @param zoneId Zone id of the publisher site.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setZoneId(int zoneId);

    /*!
     * @brief Returns the refresh rate of the banner.
     *
     * @return Returns the frequency that the @c %Banner object makes requests for new ads (optional).
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int refreshRate() const;

    /*!
     * @brief Sets the frequency (in seconds) of the Banner refresh.
     *
     * @param frequency The refresh interval (in seconds) between banner requests.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setRefreshRate(unsigned int frequency);

    /*!
     * @brief Returns a URL to the placeholder image for the ad banner to be displayed when an ad banner isn't loaded.
     *
     * @return Returns a URL to the placeHolder image.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl placeHolderURL() const;

    /*!
     * @brief Sets the URL to the placeholder image for the ad banner to be displayed when an ad banner isn't loaded.
     *
     * @param url The URL to the placeholder image.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setPlaceHolderURL(const QUrl &url);

    /*!
     * @brief Returns the color of the background for the display area of an ad banner.
     *
     * @return Returns the background color of the banner display area.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant backgroundColor() const;

    /*!
     * @brief Sets the color of the background for the display area of an ad banner.
     *
     * @param color The color of the background of the banner display area.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setBackgroundColor(const bb::cascades::Color &color);

    /*!
     * @brief Determines whether the transition effect is enabled.
     *
     * @return Returns @c true if the transition effect is enabled, and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isTransitionsEnabled() const;

    /*!
     * @brief Sets ad transition effect to ON if @c true, and OFF if @c false.
     *
     * @param transitionsEnabled Sets ad transition effect.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setTransitionsEnabled(bool transitionsEnabled);

    /*!
     * @brief Returns the border thickness of the display area for an Ad banner.
     *
     * @return Returns the border thickness of the banner display area.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int borderWidth() const;

    /*!
     * @brief Sets the border thickness of the ad banner display area.
     *
     * @param borderWidth The border thickness of the banner display area.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setBorderWidth(unsigned int borderWidth);

    /*!
     * @brief Returns the color of the focus border for the display area of an ad banner.
     *
     * @return Returns the color of the focus border on the banner display area.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant borderColor() const;

    /*!
     * @brief Sets the color of the focus border for the display area of an ad banner.
     *
     * @param borderColor The color of the focus on the banner display area.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setBorderColor(const bb::cascades::Color &borderColor);

    Q_SIGNALS:
    /*!
     * @brief Emitted when zoneId of the banner changes.
     *
     * @since BlackBerry 10.0.0
     */
    void zoneIdChanged();

    /*!
     * @brief Emitted when refresh rate of the banner changes.
     *
     * @since BlackBerry 10.0.0
     */
    void refreshRateChanged();

    /*!
     * @brief Emitted when the placeholder url of the banner changes.
     *
     * @since BlackBerry 10.0.0
     */
    void placeHolderURLChanged();

    /*!
     * @brief Emitted when background color of the banner changes.
     *
     * @since BlackBerry 10.0.0
     */
    void backgroundColorChanged();

    /*!
     * @brief Emitted when transitionEnabled setting of the banner changes.
     *
     * @since BlackBerry 10.0.0
     */
    void transitionsEnabledChanged();

    /*!
     * @brief Emitted when border width of the banner changes.
     *
     * @since BlackBerry 10.0.0
     */
    void borderWidthChanged();

    /*!
     * @brief Emitted when border color of the banner changes.
     *
     * @since BlackBerry 10.0.0
     */
    void borderColorChanged();


private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE (Banner);
    Q_DISABLE_COPY (Banner);
    BannerPrivate * const d_ptr;
    /*!
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::Color"/>
     * </qml>
     * @endxmlonly
     */
    Q_SLOT void setBackgroundColorQML(const QVariant &color);
    /*!
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::Color"/>
     * </qml>
     * @endxmlonly
     */
    Q_SLOT void setBorderColorQML(const QVariant &borderColor);
//!@endcond
};

} // namespace advertisement
} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::advertisement::Banner)

#endif // BB_CASCADES_ADVERTISEMENT_BANNER_HPP

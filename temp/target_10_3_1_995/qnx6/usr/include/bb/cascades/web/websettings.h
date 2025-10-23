/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_websettings_h
#define cascades_websettings_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/color.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
  namespace cascades {

    class WebSettingsPrivate;

   /*!
    * @brief Settings for the @c WebView control.
    *
    * Each @c WebView instance has an associated @c WebSettings instance,
    * which can be referenced by reading the @c WebView @c settings property.
    * You should never have any reason to create an instance of this class yourself.
    * This class has to be a @c QObject derivative in order to be accessible from QML.
    *
    *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT WebSettings : public QObject
    {
        Q_OBJECT

       /*!
        * @brief Specifies a default font size (in CSS pixels) to use when none is present in the HTML.
        *
        * The default is 16.
        *
        * @see devicePixelRatio
        * @see textAutosizingEnabled
        * @see defaultFontSizeFollowsSystemFontSize
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(int defaultFontSize
                   READ defaultFontSize
                   WRITE setDefaultFontSize
                   RESET resetDefaultFontSize FINAL)

        /*!
         * @brief Specifies that the default font size should follow the system font size.
         *
         * Any value set using the @c defaultFontSize property will be ignored while this setting is true.
         *
         * If your web content uses relative font sizes, like em or %, enabling this setting will allow the
         * user to control the font size of your content using the system font size setting.
         *
         * Please note that the @c textAutosizingEnabled feature already accounts for system font size, so
         * it's not recommended to have both defaultFontSizeFollowsSystemFontSize and @c textAutosizingEnabled
         * simultaneously set to true.
         *
         * The default is false.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool defaultFontSizeFollowsSystemFontSize
                   READ defaultFontSizeFollowsSystemFontSize
                   WRITE setDefaultFontSizeFollowsSystemFontSize
                   RESET resetDefaultFontSizeFollowsSystemFontSize FINAL)

       /*!
        * @brief Indicates whether the execution of JavaScript should be enabled in the main frame of the webpage.
        *
        * The default is true.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool javaScriptEnabled
                   READ isJavaScriptEnabled
                   WRITE setJavaScriptEnabled
                   RESET resetJavaScriptEnabled FINAL)

       /*!
        * @brief Specifies whether images should be loaded automatically.
        *
        * The default is true.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool imageDownloadingEnabled
                   READ isImageDownloadingEnabled
                   WRITE setImageDownloadingEnabled
                   RESET resetImageDownloadingEnabled FINAL)

       /*!
        * @brief Specifies a minimum font size in CSS pixels.
        *
        * The default is 8.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(int minimumFontSize
                   READ minimumFontSize
                   WRITE setMinimumFontSize
                   RESET resetMinimumFontSize FINAL)

       /*!
        * @brief Specifies a @c userAgent string to be used instead of the device default @c userAgent.
        *
        * The default is the same as the @c userAgent employed by the BlackBerry Browser;
        * it depends on the form factor and operating system version present on the device.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QString userAgent
                   READ userAgent
                   WRITE setUserAgent FINAL)

       /*!
        * @brief Specifies a default override CSS file location.
        *
        * The default is an empty URL, which indicates that there is no user style sheet.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl userStyleSheetLocation
                   READ userStyleSheetLocation
                   WRITE setUserStyleSheetLocation
                   RESET resetUserStyleSheetLocation FINAL)

       /*!
        * @brief Indicates whether the execution of JavaScript should be enabled in the main frame of the webpage.
        *
        * The default is false. The @c WebInspector is specifically for debugging and should
        * never be enabled in released software.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool webInspectorEnabled
                   READ isWebInspectorEnabled
                   WRITE setWebInspectorEnabled
                   RESET resetWebInspectorEnabled FINAL)

       /*!
        * @brief Specifies whether the content should be zoomed out to fit the screen upon loading.
        *
        * The default is true.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool zoomToFitEnabled
                   READ isZoomToFitEnabled
                   WRITE setZoomToFitEnabled
                   RESET resetZoomToFitEnabled FINAL)

       /*!
        * @brief Specifies whether a post-processor should run over loaded content to highlight any
        * @c activeText segments and connect them to the Invocation Framework.
        *
        * This processing takes place immediately after any document load completes; it is expensive.
        *
        * The default is false.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool activeTextEnabled
                   READ isActiveTextEnabled
                   WRITE setActiveTextEnabled
                   RESET resetActiveTextEnabled FINAL)

       /*!
        * @brief Exposes all of the arguments of the HTML Meta Viewport Tag. This map can be
        * assigned a series of key value pairs from the following sets:
        *
        * The following case-sensitive strings are accepted as keys:
        * { "initial-scale", "minimum-scale", "maximum-scale", "width", "height", "user-scalable" }
        *
        * The "initial-scale" is a multiplier applied in addition to the @c devicePixelRatio.
        *
        * The following case-sensitive strings are accepted for all viewport values
        * though not all of them are necessarily useful for each property:
        * { "auto", "desktop-width", "device-width", "device-height" }
        *
        * In addition, any non-negative floating point values are also acceptable.
        *
        * To set a common type of meta viewport tag that requests that the
        * content be laid out to the screen width in the current orientation, and zoomed 1:1, use this:
        *
        * The default is an empty map which indicates no user specified viewport
        * meta tag should be used.
        *
        * @snippet tad/examples/controls/webview/assets/main.qml webviewsettingsviewport_qml1
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QVariantMap viewport
                   READ viewportArguments
                   WRITE setViewportArguments
                   RESET resetViewportArguments FINAL)

        /*!
         * @brief Sets the background color of the webpage.
         * If you wish to enable controls behind the @c WebView to appear through
         * the webpage, you must set a non-opaque color.
         *
         * The default is opaque white.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant background
                   READ background
                   WRITE setBackgroundQML
                   RESET resetBackground FINAL)

       /*!
        * @brief Specifies whether binary "WebFonts" should be loaded automatically.
        *
        * The default is true.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool binaryFontDownloadingEnabled
                   READ isBinaryFontDownloadingEnabled
                   WRITE setBinaryFontDownloadingEnabled
                   RESET resetBinaryFontDownloadingEnabled FINAL)

        /*!
         * @brief Specifies whether network cookies should be enabled.
         *
         * The default is true.
         *
         * @since BlackBerry 10.0.0
         */
         Q_PROPERTY(bool cookiesEnabled
                    READ areCookiesEnabled
                    WRITE setCookiesEnabled
                    RESET resetCookiesEnabled FINAL)

        /*!
         * @brief Specifies custom HTTP headers that will be added to every outgoing network request
         *
         * Each key value pair in the map will be converted to UTF8 strings and added to outgoing
         * requests as "<key>: <value>".
         *
         * The following code example will add a "Pragma: no-cache" header to every outgoing
         * request:
         * @snippet tad/examples/controls/webview/assets/main.qml webviewsettingscustomhttp_qml1
         *
         * The default is an empty map, i.e. no custom HTTP headers.
         *
         * @since BlackBerry 10.0.0
         */
         Q_PROPERTY(QVariantMap customHttpHeaders
                    READ customHttpHeaders
                    WRITE setCustomHttpHeaders
                    RESET resetCustomHttpHeaders FINAL)

       /*!
        * @brief Specifies the default scaling factor.
        *
        * The @c devicePixelRatio is the ratio between physical pixels and device-independent pixels (CSS pixels) on the device.
        *
        * Increasing @c devicePixelRatio will zoom in the content and decreasing it will zoom out the content.
        *
        * Beyond the devicePixelRatio, which scales the very CSS pixels of the webpage, the web content can also be
        * scaled due to @c zoomToFitEnabled being set to true. An "initial-scale" viewport argument present on the web
        * page or injected using the @c viewport property can also influence scaling. The "initial-scale" is a
        * multiplier applied in addition to the devicePixelRatio.
        *
        * There are two approaches to scaling your web content.
        *
        * Use the default devicePixelRatio to optimize for a mix of desktop and mobile web content. Typically, the default
        * value is appropriate for loading existing web content from the world wide web. At the default devicePixelRatio,
        * a font size of ~16 CSS pixels is pleasant to read. The user may adjust the system font size setting if they prefer
        * bigger or smaller text, and the @c textAutosizingEnabled feature (enabled by default) takes the system font size
        * setting into account when adjusting font size for improved readability.
        * Enabling @c defaultFontSizeFollowsSystemFontSize is not recommended in this scenario.
        *
        * Use a devicePixelRatio of 1.0 and tailor your web content to fit the standard screen width of BlackBerry 10
        * devices. Typically, a value of 1.0 is used when the web content is created specifically for BlackBerry 10 devices.
        * At this devicePixelRatio, a font size of ~40 CSS pixels is pleasant to read, but you can enable
        * @c defaultFontSizeFollowsSystemFontSize to have the default font size be adjusted to exactly match the system
        * font size setting. When using a devicePixelRatio of 1.0, @c defaultFontSizeFollowsSystemFontSize is recommended
        * over the @c textAutosizingEnabled feature. The text autosizing algorithm can't properly adjust font sizes without
        * an accurate devicePixelRatio value.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(double devicePixelRatio
                   READ devicePixelRatio
                   WRITE setDevicePixelRatio
                   RESET resetDevicePixelRatio FINAL)

       /*!
        * @brief Specifies whether known credentials can be automatically submitted with HTTP requests.
        *
        * The default is false, setting this to @c true can reduce the number of times the user is prompted for credentials.
        *
        * @since BlackBerry 10.1.0
        *
        * @deprecated BlackBerry 10.3.1 The web browser engine always enables
        * auto fill of credentials, the value of the @c credentialAutoFillEnabled setting is ignored.
        */
        Q_PROPERTY(bool credentialAutoFillEnabled
                   READ isCredentialAutoFillEnabled
                   WRITE setCredentialAutoFillEnabled
                   RESET resetCredentialAutoFillEnabled FINAL)

       /*!
        * @brief Specifies whether known form fields can be automatically filled out on the user's behalf.
        *
        * The default is false, setting to true can reduce the amount of input the user needs to type.
        *
        * @since BlackBerry 10.1.0
        */
        Q_PROPERTY(bool formAutoFillEnabled
                   READ isFormAutoFillEnabled
                   WRITE setFormAutoFillEnabled
                   RESET resetFormAutoFillEnabled FINAL)

       /*!
        * @brief Sets the default character encoding fallback for when no encoding information is available.
        *
        * The default is ISO-8859-1.
        *
        * @since BlackBerry 10.1.0
        */
        Q_PROPERTY(QString defaultTextCodecName
                   READ defaultTextCodecName
                   WRITE setDefaultTextCodecName
                   RESET resetDefaultTextCodecName FINAL)

       /*!
        * @brief Specifies whether text will have its font size automatically adjusted for improved readability.
        *
        * Web content designed for desktop web browsers can contain text too small to be readable when
        * the column of text is zoomed to fit the screen width. Text autosizing improves the situation by
        * adjusting font size of text depending on column width and the screen's pixel density (DPI).
        * If the user has changed the system font size setting, the effects of the text autosizing algorithm
        * will be attenuated (if system font size is smaller than the default setting) or magnified (if the
        * system font size is greater) to accommodate the user's setting.
        *
        * This means that the text autosizing feature already accounts for system font size, so it's not
        * recommended to have both @c defaultFontSizeFollowsSystemFontSize and textAutosizingEnabled
        * simultaneously set to true.
        *
        * To determine the scaling required, the text autosizing algorithm depends on the @c devicePixelRatio,
        * so autosizing works best if devicePixelRatio is left at it's default value. Setting devicePixelRatio
        * to 1.0 effectively disables autosizing.
        *
        * The default is true.
        *
        * @since BlackBerry 10.2.0
        */
        Q_PROPERTY(bool textAutosizingEnabled
                   READ isTextAutosizingEnabled
                   WRITE setTextAutosizingEnabled
                   RESET resetTextAutosizingEnabled REVISION 2 FINAL)

       /*!
        * @brief Specifies whether spatial navigation is used to interact with the @c WebView when using a trackpad
        *
        * This property changes the @c WebView behaviour for navigation with trackpad and similar input.
        *
        * Normally, when the @c WebView has navigation focus, the trackpad controls a mouse pointer for maximum
        * compatibility with web content.
        *
        * When spatial navigation is enabled, instead of a mouse pointer a highlight is displayed which can be used
        * to focus and interact with certain elements on the web page using the trackpad.
        *
        * Spatial navigation is disabled by default, because web content may need to be modified to support spatial
        * navigation well. For web content that has been tested or optimized to work well with spatial navigation, it
        * can be preferable to use spatial navigation rather than the mouse pointer emulation.
        *
        * @since BlackBerry 10.3.1
        */
        Q_PROPERTY(bool spatialNavigationEnabled
                   READ isSpatialNavigationEnabled
                   WRITE setSpatialNavigationEnabled
                   RESET resetSpatialNavigationEnabled REVISION 4 FINAL)

    public:

        /*!
         * @brief Gets the default font size for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        int defaultFontSize() const;

        /*!
         * @brief Sets the default font size for the @c WebView.
         *
         * @param size A default font size in CSS pixels.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDefaultFontSize(int size);

        /*!
         * @brief Resets the default font size to its default value of 16.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDefaultFontSize();

        /*!
         * @brief Gets whether the default font size follows the system font size.
         *
         * @since BlackBerry 10.0.0
         */
        bool defaultFontSizeFollowsSystemFontSize() const;

        /*!
         * @brief Sets whether the default font size follows the system font size.
         *
         * @param follows Set @c true to enable this feature, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDefaultFontSizeFollowsSystemFontSize(bool follows);

        /*!
         * @brief Resets whether the default font size follows the system font size to the default value of @c false.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDefaultFontSizeFollowsSystemFontSize();

        /*!
         * @brief Gets whether or not JavaScript is enabled for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        bool isJavaScriptEnabled() const;

        /*!
         * @brief Set whether JavaScript will be enabled on the @c WebView.
         *
         * @note This setting takes effect when the webpage is reloaded.
         *
         * @param enabled Set @c true to enable JavaScript, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setJavaScriptEnabled(bool enabled);

        /*!
         * @brief Resets @c javaScriptEnabled to its default value of @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetJavaScriptEnabled();

        /*!
         * @brief Gets whether or not image downloading is enabled for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        bool isImageDownloadingEnabled() const;

        /*!
         * @brief Sets whether images will be downloaded by the @c WebView.
         *
         * @param enabled Set @c true to enable image downloading, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setImageDownloadingEnabled(bool enabled);

        /*!
         * @brief Resets @c imageDownloadingEnabled to its default value of @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetImageDownloadingEnabled();

        /*!
         * @brief Gets the minimum font size for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        int minimumFontSize() const;

        /*!
         * @brief Sets the @c WebView minimum font size.
         *
         * @param size A minimum font size in CSS pixels.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMinimumFontSize(int size);

        /*!
         * @brief Resets the minimum font size to its default value of 8.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMinimumFontSize();

        /*!
         * @brief Gets the @c userAgent used by the @c WebView for outgoing HTTP Requests.
         *
         * @since BlackBerry 10.0.0
         */
        QString userAgent() const;

        /*!
         * @brief Sets a @c userAgent string to use instead of the default @c userAgent.
         *
         * @param userAgent A new user agent string to use with outgoing HTTP requests.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setUserAgent(const QString& userAgent);

        /*!
         * @brief Gets the @c userStyleSheetLocation for the @c WebView.
         * An empty @c QUrl indicates no user stylesheet is in use.
         *
         * @since BlackBerry 10.0.0
         */
        QUrl userStyleSheetLocation() const;

        /*!
         * @brief Sets a location for a default CSS file.
         *
         * @param location A URL to a file containing default CSS.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setUserStyleSheetLocation(const QUrl& location);

        /*!
         * @brief Resets the user style sheet to its default value of an empty URL.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetUserStyleSheetLocation();

        /*!
         * @brief Gets whether or not the @c WebInspector is enabled for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        bool isWebInspectorEnabled() const;

        /*!
         * @brief Sets the @c WebInspector on or off.
         *
         * @param enabled Set @c true to enable the @c WebInspector, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setWebInspectorEnabled(bool enabled);

        /*!
         * @brief Resets the web inspector to being disabled.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetWebInspectorEnabled();

        /*!
         * @brief Gets whether or not zoom to fit after loading is enabled for the @c WebView.
         *
         * Any zooming done due to this setting is a multiplier applied in addition to the @c devicePixelRatio.
         * Viewport arguments present on the webpage or injected using the @c viewport property will
         * override this setting and prevent zooming to fit.
         *
         * @since BlackBerry 10.0.0
         */
        bool isZoomToFitEnabled() const;

        /*!
         * @brief Sets zoom to fit behaviour for the @c WebView.
         *
         * @param enabled Set @c true to enable zoom to fit on load, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setZoomToFitEnabled(bool enabled);

        /*!
         * @brief Resets zoom to fit enabled to @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetZoomToFitEnabled();

        /*!
         * @brief Gets whether or not active text matching after loading is enabled for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        bool isActiveTextEnabled() const;

        /*!
         * @brief Sets @c activeText parsing enabled.
         *
         * @param enabled Set @c true to enable active text matching, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setActiveTextEnabled(bool enabled);

        /*!
         * @brief Resets active text matching to false.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetActiveTextEnabled();

        /*!
         * @brief Gets a map of user viewport arguments for the @c WebView.
         * An empty map indicates no user viewport arguments are in use.
         *
         * @since BlackBerry 10.0.0
         */
        QVariantMap viewportArguments() const;

        /*!
         * @brief Sets a map of meta viewport arguments.
         *
         * @param arguments A @c QVariantMap of viewport arguments to be used if none is specified in the HTML.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setViewportArguments(const QVariantMap& arguments);

        /*!
         * @brief Resets the user viewport arguments to an empty map.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetViewportArguments();

        /*!
         * @brief Gets the background of this @c WebView.
         * The @c QVariant returned wraps around a @c bb::cascades::Paint instance.
         *
         * @since BlackBerry 10.0.0
         */
        QVariant background() const;

        /*!
         * @brief Sets a @c bb::cascades::Paint& background for this @c WebView.
         *
         * Presently only @c ColorPaint is supported. Other @c Paints will be ignored.
         * A non-opaque color can be used to allow controls behind this @c WebView to be visible.
         *
         * The default background is opaque white.
         *
         * @note This setting takes effect when the webpage is reloaded.
         *
         * @param paint A @c ColorPaint to be used as a background for this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setBackground(const bb::cascades::Paint& paint);

        /*!
         * @brief Resets the background to opaque white.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetBackground();

        /*!
         * @brief Gets whether or not @c WebFont downloading is enabled for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        bool isBinaryFontDownloadingEnabled() const;

        /*!
         * @brief Sets whether or not WebFonts should be downloaded.
         *
         * @param enabled Set @c true to enable downloading of web fonts, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setBinaryFontDownloadingEnabled(bool enabled);

        /*!
         * @brief Resets binary font downloading to @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetBinaryFontDownloadingEnabled();

        /*!
         * @brief Gets whether or not cookies are enabled for the @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        bool areCookiesEnabled() const;

        /*!
         * @brief Sets whether or not cookies should be enabled.
         *
         * @param enabled Set @c true to enable cookies, @c false to disable.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setCookiesEnabled(bool enabled);

        /*!
         * @brief Resets cookies enabled to @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetCookiesEnabled();

        /*!
         * @brief Gets a map of custom HTTP headers that will be added to every outgoing network request.
         * An empty map indicates no custom HTTP headers are in use.
         *
         * @return A map where each key value pair corresponds to an HTTP header.
         *
         * @since BlackBerry 10.0.0
         */
        QVariantMap customHttpHeaders() const;

        /*!
         * @brief Sets a map of custom HTTP headers to be added to every outgoing network request.
         *
         * @param httpHeaders A @c QVariantMap where each key value pair corresponds to an HTTP header.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setCustomHttpHeaders(const QVariantMap& httpHeaders);

        /*!
         * @brief Resets the custom HTTP headers to an empty map.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetCustomHttpHeaders();

        /*!
         * @brief Gets device pixel ratio.
         *
         * @since BlackBerry 10.0.0
         */
        double devicePixelRatio() const;

        /*!
         * @brief Sets device pixel ratio.
         *
         * @param ratio A pixel ratio.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDevicePixelRatio(double ratio);

        /*!
         * @brief Resets device pixel ratio to default value.
         *
         * Default value is the ratio between physical pixels and dips on the device.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDevicePixelRatio();

        /*!
         * @brief Gets whether or not credentials are automatically filled if available.
         *
         * @since BlackBerry 10.1.0
         *
         * @deprecated BlackBerry 10.3.1 The web browser engine always enables auto fill of credentials.
         */
        bool isCredentialAutoFillEnabled() const;

        /*!
         * @brief Sets whether or not credentials are automatically filled if available.
         *
         * @param enabled Set true to enable credential auto fill.
         *
         * @since BlackBerry 10.1.0
         *
         * @deprecated BlackBerry 10.3.1 The web browser engine always enables
         * auto fill of credentials, the value of the @c credentialAutoFillEnabled setting is ignored.
         */
        Q_SLOT void setCredentialAutoFillEnabled(bool enabled);

        /*!
         * @brief Resets credential auto fill to default.
         *
         * @since BlackBerry 10.1.0
         *
         * @deprecated BlackBerry 10.3.1
         */
        Q_SLOT void resetCredentialAutoFillEnabled();

        /*!
         * @brief Gets whether or not forms are automatically filled if available.
         *
         * @since BlackBerry 10.1.0
         */
        bool isFormAutoFillEnabled() const;

        /*!
         * @brief Sets whether or not forms are automatically filled if available.
         *
         * @param enabled Set @c true to enable form auto fill.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setFormAutoFillEnabled(bool enabled);

        /*!
         * @brief Resets form auto fill to default.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetFormAutoFillEnabled();

        /*!
         * @brief Gets the default character encoding.
         *
         * @since BlackBerry 10.1.0
         */
        QString defaultTextCodecName() const;

        /*!
         * @brief Sets a default character encoding.
         *
         * @param codec The encoding to be used when no other encoding information is available.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setDefaultTextCodecName(const QString& codec);

        /*!
         * @brief Resets back to default encoding of ISO-8859-1.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetDefaultTextCodecName();

        /*!
         * @brief Gets whether or not font sizes are automatically increased to make text legible.
         *
         * @since BlackBerry 10.2.0
         */
        bool isTextAutosizingEnabled() const;

        /*!
         * @brief Sets whether or not font sizes are automatically increased to make text legible.
         *
         * @param enabled Set @c true to enable text autosizing, @c false to disable.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_SLOT void setTextAutosizingEnabled(bool enabled);

        /*!
         * @brief Resets back to the default, which is to enable text autosizing.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_SLOT void resetTextAutosizingEnabled();

        /*!
         * @brief Indicates whether spatial navigation is used instead of mouse pointer emulation for trackpad interaction.
         *
         * @since BlackBerry 10.3.1
         */
        bool isSpatialNavigationEnabled() const;

        /*!
         * @brief Sets whether spatial navigation is used instead of mouse pointer emulation for trackpad interaction.
         *
         * @param enabled Set @c true to enable spatial navigation, @c false to disable.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void setSpatialNavigationEnabled(bool enabled);

        /*!
         * @brief Resets back to the default, which is to disable spatial navigation
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void resetSpatialNavigationEnabled();

        /*! @cond PRIVATE */
        WebSettings(WebSettingsPrivate &dd);
        ~WebSettings();
       /*! @endcond */

    Q_SIGNALS:

        /*!
         * @brief Emitted when the default font size changes.
         *
         * @param newDefaultFontSize The new default font size.
         *
         * @since BlackBerry 10.0.0
         */
        void defaultFontSizeChanged(int newDefaultFontSize);

        /*!
         * @brief Emitted when the default font size starts or stops following the system font size.
         *
         * @param newDefaultFontSizeFollowsSystemFontSize The new value of the setting.
         *
         * @since BlackBerry 10.0.0
         */
        void defaultFontSizeFollowsSystemFontSizeChanged(bool newDefaultFontSizeFollowsSystemFontSize);

        /*!
         * @brief Emitted when JavaScript enabled changes.
         *
         * @param enabled Whether JavaScript is enabled or not.
         *
         * @since BlackBerry 10.0.0
         */
        void javaScriptEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when image downloading enabled changes.
         *
         * @param enabled Whether image downloading is enabled or not.
         *
         * @since BlackBerry 10.0.0
         */
        void imageDownloadingEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when the minimum font size changes.
         *
         * @param newMinimumFontSize The new minimum font size.
         *
         * @since BlackBerry 10.0.0
         */
        void minimumFontSizeChanged(int newMinimumFontSize);

        /*!
         * @brief Emitted when the user agent string changes.
         *
         * @param newUserAgent The new user agent string.
         *
         * @since BlackBerry 10.0.0
         */
        void userAgentChanged(QString newUserAgent);

        /*!
         * @brief Emitted when the user style sheet location changes.
         *
         * @param newUserStyleSheetLocation The new user style sheet location.
         *
         * @since BlackBerry 10.0.0
         */
        void userStyleSheetLocationChanged(QUrl newUserStyleSheetLocation);

        /*!
         * @brief Emitted when web inspector enabled changes.
         *
         * @param enabled Whether the web inspector is enabled or disabled.
         *
         * @since BlackBerry 10.0.0
         */
        void webInspectorEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when zoom to fit enabled changes.
         *
         * @param enabled Whether zoom to fit is enabled or disabled.
         *
         * @since BlackBerry 10.0.0
         */
        void zoomToFitEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when active text matching enabled changes.
         *
         * @param enabled Whether active text matching is enabled or disabled.
         *
         * @since BlackBerry 10.0.0
         */
        bool activeTextEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when the map of user viewport arguments changes.
         *
         * @param newViewportArguments The new map of user viewport arguments.
         *
         * @since BlackBerry 10.0.0
         */
        void viewportArgumentsChanged(const QVariantMap& newViewportArguments);

        /*!
         * @brief Emitted when the background setting changes.
         *
         * The newBackground @c QVariant provided wraps a @c bb::cascades::Paint instance.
         *
         * @param newBackground The new background
         *
         * @since BlackBerry 10.0.0
         */
        void backgroundChanged(const QVariant& newBackground);

        /*!
         * @brief Emitted when web font downloading enabled changed.
         *
         * @param enabled Whether web font downloading is enabled or disabled.
         *
         * @since BlackBerry 10.0.0
         */
        void binaryFontDownloadingEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when cookies enabled changed.
         *
         * @param enabled Whether cookies are enabled or disabled.
         *
         * @since BlackBerry 10.0.0
         */
        void cookiesEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when the custom HTTP headers change.
         *
         * @param newCustomHttpHeaders The new custom HTTP headers.
         *
         * @since BlackBerry 10.0.0
         */
        void customHttpHeadersChanged(const QVariantMap& newCustomHttpHeaders);

        /*!
         * @brief Emitted when the device pixel ratio changes.
         *
         * @param newDevicePixelRatio The new device pixel ratio.
         *
         * @since BlackBerry 10.0.0
         */
        void devicePixelRatioChanged(double newDevicePixelRatio);

        /*!
         * @brief Emitted when credential auto fill changes.
         *
         * @param enabled Whether credential auto fill is enabled.
         *
         * @since BlackBerry 10.1.0
         *
         * @deprecated BlackBerry 10.3.1
         */
        void credentialAutoFillEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when form auto fill changes.
         *
         * @param enabled Whether form auto fill is enabled.
         *
         * @since BlackBerry 10.1.0
         */
        void formAutoFillEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when the default character encoding changes.
         *
         * @param codec The new default character encoding.
         *
         * @since BlackBerry 10.1.0
         */
        void defaultTextCodecNameChanged(const QString& codec);

        /*!
         * @brief Emitted when text autosizing changes.
         *
         * @param enabled Whether text autosizing is enabled.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        void textAutosizingEnabledChanged(bool enabled);

        /*!
         * @brief Emitted when spatial navigation is enabled or disabled
         *
         * @param enabled Whether spatial navigation is enabled.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        void spatialNavigationEnabledChanged(bool enabled);

    private:
       /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebSettings)
        Q_DISABLE_COPY(WebSettings)

        void setBackgroundQML(const QVariant& background);

        WebSettingsPrivate* const d_ptr;
       /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::WebSettings)

#endif	/* cascades_websettings_h */

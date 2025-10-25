/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webstorage_h
#define cascades_webstorage_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
  namespace cascades {

    class WebCookieJar;
    class WebStoragePrivate;

   /*!
    * @brief Utilities for accessing the storage for a @c WebView control.
    *
    * Each @c WebView instance has an associated @c WebStorage
    * which can be referenced by reading the @c WebView @c storage property.
    * You should never have any reason to create an instance of this class yourself.
    *
    * Note: Some storage is process wide and not tied an individual @c WebView.
    * For example, clearing cookies on one @c WebView will clear the cookies for all
    * other @c WebViews running inside the same process.
    *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT WebStorage : public QObject
    {
        Q_OBJECT

        /*!
         * @brief A jar (database) containing web cookies.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::WebCookieJar* cookieJar READ cookieJar CONSTANT)

    public:
        /*!
         * @brief Returns the cookie jar.
         *
         * @see @c WebCookieJar.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::WebCookieJar* cookieJar() const;

    public Q_SLOTS:

        /*!
         * @brief Clears all data stored by this @c WebView.
         *
         * This is analogous to calling @c clearAutofillData(), @c clearCache(),
         * @c clearCookies(), @c clearCredentials(), @c clearLocalStorage(),
         * @c clearWebFileSystem() and @c clearSslSiteExceptions().
         *
         * @since BlackBerry 10.0.0
         */
        void clear();

        /*!
         * @brief Clears the form AutoFill data accumulated in this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearAutofillData();

        /*!
         * @brief Clears the cache accumulated by this @c WebView.
         *
         * Also clears the cached site exceptions. Note that before BlackBerry 10 OS version 10.2.1, it was not possible for the user
         * to add site exceptions, loading over untrusted connections was not allowed at all.
         *
         * @since BlackBerry 10.0.0
         */
        void clearCache();

        /*!
         * @brief Clears the cookie database stored for this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearCookies();

        /*!
         * @brief Clears the login credentials accumulated in this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearCredentials();

        /*!
         * @brief Clears any databases kept by this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearDatabases();

        /*!
         * @brief Clears the local storage for this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearLocalStorage();

        /*!
         * @brief Clears the web file system for this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearWebFileSystem();

        /*!
         * @brief Clears all site exceptions added by the user when encountering untrusted HTTPS/SSL connections.
         *
         * If an untrusted connection is encountered while loading a web page, for example due to an expired SSL
         * certificate, the user is given the option to add a "site exception" and continue loading anyway. Until that
         * site exception is removed, that particular web page will load without warning.
         *
         * Call this method to clear all site exceptions.
         *
         * Note that while this API is introduced to QML in bb.cascades version 1.3, it's possible to clear all site
         * exceptions (among other things cleared) in earlier versions of the Cascades framework by calling clear() or
         * clearCache(). Note that before BlackBerry 10 OS version 10.2.1, it was not possible for the user to add site exceptions,
         * loading over untrusted connections was not allowed at all. If your QML code targets both versions newer and
         * older than bb.cascades 1.3, it makes sense to call clear() or clearCache() instead of clearSslSiteExceptions()
         * in order to be able to deploy the same QML to all devices.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        void clearSslSiteExceptions();

        /*!
         * @brief Clears all geolocation permissions granted by the user to web sites that make use of location services.
         *
         * Content loaded in @c WebView can make use of location services. Please note that you must set the
         * "access_location_services" permission in your bar-descriptor.xml file in order to use this functionality, and the
         * user must enable device-wide "Location Services" in the Settings application. In addition, the user will be
         * prompted whether to allow use of location services on a site by site basis. The permissions are persisted, but
         * can be cleared by calling this method.
         *
         * Call this method to clear all geolocation permissions.
         *
         * Starting with BlackBerry 10.3, calling @c clear() also clears all geolocation permissions. In previous
         * versions of BlackBerry 10 OS, geolocation permissions were not persisted, so there was nothing to clear.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        void clearGeolocationPermissions();

    public:

        /*! @cond PRIVATE */
        WebStorage(WebStoragePrivate &dd);
        virtual ~WebStorage();
       /*! @endcond */

    private:
       /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebStorage)
        Q_DISABLE_COPY(WebStorage)

        WebStoragePrivate* const d_ptr;
       /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::WebStorage)

#endif	/* cascades_webstorage_h */

/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webcookiejar_h
#define cascades_webcookiejar_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

    class WebCookieJarPrivate;

   /*!
    * @brief The cookie database for the @c WebView control.
    *
    * The @c WebView uses network protocols such as HTTP, which store "cookies" to
    * maintain some persistent information across requests.
    *
    * The same cookie database is shared among all @c WebView controls running in
    * the same process, so the changes made using methods in this class will
    * affect all @c WebViews.
    *
    * This class uses strings to represent cookies. The strings are formatted
    * according to the RFC 6265 specification, found at http://tools.ietf.org/html/rfc6265.
    *
    * Use @c WebStorage::cookieJar() to obtain an instance of this
    * class. Use @c WebSettings::setCookiesEnabled(bool) to enable
    * or disable cookies. Use @c WebStorage::clearCookies() to clear
    * the cookie database.
    *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT WebCookieJar : public QObject
    {
        Q_OBJECT

    public:
        /*!
         * @brief Retrieves all cookies whose domain and path match the provided URL.
         *
         * These are the cookies that would be included when @c WebView sends a network
         * request to the provided URL.
         *
         * Each cookie is defined by a string that contains a name/value pair following
         * the RFC 6265 specification.
         *
         * @param url Cookies with domain and path that match this URL will be fetched.
         *
         * @returns A list of strings, each string representing a cookie.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QStringList cookiesForUrl(const QUrl& url) const;

        /*!
         * @brief Adds the cookies provided in the list to the cookie database.
         *
         * If a cookie with the same name and domain+path as one of the cookies
         * provided already exists, it will be replaced.
         *
         * If no domain and/or path is provided in a cookie, the domain and/or path
         * will be inferred from the provided URL.
         *
         * Each cookie is defined by a string that must follow the RFC 6265
         * specification.
         *
         * @param url Will be used to infer domain and path if not specified in a cookie.
         * @param cookies A list of cookies to add or replace.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void setCookiesFromUrl(const QUrl& url, const QStringList& cookies);

    public:
        /*! @cond PRIVATE */
        WebCookieJar(WebCookieJarPrivate &dd);
       /*! @endcond */

    private:
       /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebCookieJar)
        Q_DISABLE_COPY(WebCookieJar)

        WebCookieJarPrivate* const d_ptr;
       /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::WebCookieJar)

#endif	/* cascades_webcookiejar_h */

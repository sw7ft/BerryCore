/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webresourcerequestfilter_h
#define cascades_webresourcerequestfilter_h

#include <bb/cascades/bbcascades_global.h>

#include <QString>
#include <QUrl>

namespace bb {
  namespace cascades {

    class WebResourceRequest;

    /*!
     * @brief A class that exposes control over the networking layer of a @c WebPage.
     *
     * This interface is designed to be implemented and provided
     * by a consumer seeking advanced control over resource requests coming
     * from the @c WebPage.
     *
     * If an implementation of the class is instantiated and provided via
     * @c WebPage::setNetworkResourceRequestFilter(WebResourceRequestFilter*),
     * all resource requests can be intercepted in the following sequence:
     *
     * 1. @c filterResourceRequest() (and then if @c FilterAction is set to @c Filter, the following:)
     * 2. @c filterResourceOpened()
     * 3. @c filterResourceHeader() (once per HTTP Header)
     * 4. @c filterResourceData()
     * 5. @c filterResourceDone()
     *
     * @see @c WebView::setResourceRequestFilter()
     *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT WebResourceRequestFilter
    {
    public:
        virtual ~WebResourceRequestFilter();

        /*!
         * @brief The action the @c WebPage should take for a @c Resource request.
         *
         * @since BlackBerry 10.0.0
         */
        enum FilterAction {
            Accept,       ///< Treat this request normally.
            Deny,         ///< Abandon the request completely.
            Substitute,   ///< This implementation of @c WebResourceRequestFilter will perform the request.
            Filter,       ///< This implementation of @c WebResourceRequestFilter would like callbacks throughout the request.
        };

        /*!
         * @brief The purpose of the @c Resource Request.
         *
         * @since BlackBerry 10.0.0
         */
        enum RequestPurpose {
            Unknown,        ///< Nothing is known about the purpose.
            MainFrame,
            Subframe,
            Subresource,    ///< An unknown subresource. Known subresources are below.
            XmlHttpRequest, ///< AJAX
            Worker,         ///< HTML5 JavaScript worker communication.
            SharedWorker,
            FileDownload,   ///< An explicit file download to be saved to the device file system.
            StyleSheet,
            Script,
            Font,
            Image,
            Object,
            Media,
        };

        /*!
         * @brief Suggests how this @c WebResourceRequestFilter would like this request to proceed.
         *
         * The life cycle of the provided @c WebResourceRequest object depends on the action taken.
         * @c Accept and @c Deny actions will result in the request being deleted immediately after the
         * @c filterResourceRequest() returns, unless the application developer has called @c setParent()
         * on the request. In that case, ownership is transferred to the application.
         *
         * In the @c Substitute case, an application developer should use @c setParent() to take ownership
         * of the request, and then call the following methods after the @c filterResourceRequest
         * returns to provide the data for the request.
         *
         * 1. request->notifyOpen()
         * 2. request->notifyHeaderReceived() // 0 or more times
         * 3. request->notifyDataReceived() // 0 or more times
         * 4. request->notifyDone()
         * 5. request->deleteLater() // Recommended method of cleanup.
         *
         * In the @c Filter case, the request's lifetime will continue until the @c filterNotifyDone() method
         * returns, at which point it will be deleted if @c setParent has not been called.
         *
         * In the @c Substitute and @c Filter cases the request and the @c WebPage can be independently deleted.
         * It is safe to call @c deleteLater() on the request when it is no longer needed as an optimization.
         * This includes destroying a request after, for example, a particular @c notifyHeaderReceived
         * occurs when the application no longer needs any more callbacks for this request.
         *
         * @param request An object representing this request.
         * @param purpose A hint as to the purpose of this request.
         * @return @c FilterAction indicating how this request should be handled.
         *      Accept     - Treat the request normally. No further calls will be made for this request.
         *      Deny       - Cancel this request. Whatever resource will not be loaded.
         *      Substitute - Call methods on the WebResourceRequest object to inject headers and data
         *      Filter     - Call back to this WebResourceRequestFilter and allow the implementation
         *                   to tweak the request on the fly. The following four methods will be called.
         *
         * @since BlackBerry 10.0.0
         */
        virtual FilterAction filterResourceRequest(WebResourceRequest* request, RequestPurpose purpose) = 0;

        /*!
         * @brief Allows the implementation to intercept a network error and opt to
         * prevent showing the user the error.
         *
         * Called before filterResourceOpened if the network returned an error.
         *
         * @param status The error code of the request.
         * @param url The originally requested URL.
         * @param message The error message provided.
         * @return true to preventDefault, thus handling the error.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool filterResourceError(int status, const QUrl& url, const QString& message) = 0;

        /*!
         * @brief Allows the implementation to adjust the status and message for the request.
         *
         * Called for a given request when the FilterAction was set to Filter.
         *
         * @param request An object representing this request.
         * @param status The HTTP status code. It can be modified here.
         * @param message The HTTP status message. It can be modified here.
         * @return true to preventDefault and abandon the request.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool filterResourceOpened(WebResourceRequest* request, int& status, QString& message) = 0;

        /*!
         * @brief Allows the implementation to adjust each HTTP header.
         *
         * Called for a given request when the FilterAction was set to Filter.
         *
         * @param request An identifier for this request.
         * @param key The key part of an HTTP header. It can be modified here.
         * @param value The value part of an HTTP header. It can be modified here.
         * @return true to preventDefault and discard this header completely.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool filterResourceHeader(WebResourceRequest* request, QString& key, QString& value) = 0;

        /*!
         * @brief Allows the implementation to actually modify the incoming data.
         *
         * Called for a given request when the FilterAction was set to Filter.
         *
         * @param request An object representing this request.
         * @param data If modified, a deep copy will be made behind the scenes,
         *        so this method is only heavy if it is used to modify the data.
         * @return true to preventDefault and discard this data completely.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool filterResourceData(WebResourceRequest* request, QByteArray& data) = 0;

        /*!
         * Allows the implementation to intercept the resource closed notification.
         *
         * Called for a given request when the FilterAction was set to Filter.
         *
         * @param request An object representing this request.
         * @return true to preventDefault and prevent the resource from closing.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool filterResourceDone(WebResourceRequest* request) = 0;

    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webresourcerequestfilter_h

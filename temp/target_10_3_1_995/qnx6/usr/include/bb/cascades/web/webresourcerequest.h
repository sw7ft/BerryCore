/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webresourcerequest_h
#define cascades_webresourcerequest_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

namespace bb {
  namespace cascades {

    class WebPagePrivate;
    class WebResourceRequestPrivate;

    /*!
     * @brief A resource being requested by a @c WebView.
     *
     * The class provides you with the URL for the resource request.
     *
     * For advanced use cases, the @c WebResourceRequestFilter can chose to substitute
     * a response to the request, thus bypassing the network stack. In that case, the implementation
     * must call @c notifyOpen() exactly once, @c notifyHeaderReceived() any amount of times,
     * @c notifyDataRecieved() any amount of times and finally @c notifyDone() exactly once.
     *
     * @see @c WebResourceRequestFilter.
     *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT WebResourceRequest : public QObject
    {
        Q_OBJECT

        /*!
         * @brief The URL of the resource requested.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl url READ url FINAL)

    public:
        /*! @brief Constructs a @c WebResourceRequest.
         *
         * @since BlackBerry 10.0.0
         */
        explicit WebResourceRequest(WebResourceRequestPrivate* dd_ptr, QObject* parent = 0);
        virtual ~WebResourceRequest();

       /*!
        * @brief Returns the URL of the resource requested.
        *
        * @since BlackBerry 10.0.0
        */
        QUrl url() const;

       /*!
        * @brief Returns the referrer of the resource requested.
        *
        * Note: Due to an unfortunate misspelling in the original specification,
        * the referrer is actually misspelled "Referer" in HTTP headers.
        *
        * @since BlackBerry 10.0.0
        */
        QUrl referrer() const;

       /*!
        * @brief Returns the body of the request.
        *
        * The only time this will not be empty is when called during @c filterResourceRequest(),
        * and even then it will likely be empty unless the request is a @c FormSubmission.
        * Once the @c FilterAction is returned, the body is no longer available. Calling
        * this method after that time is guaranteed to return an empty @c QByteArray().
        *
        * The @c QByteArray returned is created using @c QByteArray::fromRawData to reduce the
        * initial memory cost, however this means that the @c QByteArray is not guaranteed to be
        * valid after @c filterResourceRequest returns. The body should be copied to
        * another @c QByteArray object if it is needed after that time.
        *
        * @since BlackBerry 10.0.0
        */
        QByteArray body() const;

    public Q_SLOTS:
       /*!
        * @brief Provides a response for this request, indicating status code and message.
        *
        * This can be called by a @c WebResourceRequestFilter implementation that
        * has returned @c WebResourceRequestFilter::Substitute from
        * @c WebResourceRequestFilter::filterResourceRequest().
        *
        * @param statusCode The HTTP status code.
        * @param message A message.
        *
        * @since BlackBerry 10.0.0
        */
        void notifyOpen(int statusCode, const QString& message);

        /*!
         * @brief Provides a response for this request, indicating status code and message.
         *
         * This can be called by a @c WebResourceRequestFilter implementation that
         * has returned @c WebResourceRequestFilter::Substitute from
         * @c WebResourceRequestFilter::filterResourceRequest().
         *
         * @param key The key for this header.
         * @param value The value for this header.
         *
         * @since BlackBerry 10.0.0
         */
        void notifyHeaderReceived(const QString& key, const QString& value);

        /*!
         * @brief Provides a response for this request, indicating status code and message.
         *
         * This can be called by a @c WebResourceRequestFilter implementation that
         * has returned @c WebResourceRequestFilter::Substitute from
         * @c WebResourceRequestFilter::filterResourceRequest().
         *
         * @param data The data.
         *
         * @since BlackBerry 10.0.0
         */
        void notifyDataReceived(const QByteArray& data);

        /*!
         * @brief Notifies the browser engine that the @c WebResourceRequestFilter implementation is done substituting this request.
         *
         * This can be called by a @c WebResourceRequestFilter implementation that
         * has returned @c WebResourceRequestFilter::Substitute from
         * @c WebResourceRequestFilter::filterResourceRequest().
         *
         * Call this after providing all headers and data for the request.
         *
         * @since BlackBerry 10.0.0
         */
        void notifyDone();

    private:
       friend class WebPagePrivate;

       /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebResourceRequest)
        Q_DISABLE_COPY(WebResourceRequest)

        WebResourceRequestPrivate* const d_ptr;
       /*! @endcond */
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webresourcerequest_h

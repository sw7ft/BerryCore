/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_webloadrequest_h
#define cascades_webloadrequest_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/webview.h>
#include <bb/cascades/web/webloadstatus.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace bb {
  namespace cascades {

    class WebLoadRequestPrivate;

    /*!
     * @brief A utility class for the @c loadingChanged() signal.
     *
     * This class contains information about a requested load of a webpage,
     * such as the URL and current loading status (started, finished, failed).
     *
     *
     * Here's a simple QML example demonstrating the use of a @c %WebLoadRequest:
     * @snippet tad/examples/controls/webview/assets/main.qml webviewmisc_qml1
     *
     * @see @c WebView::loadingChanged().
     *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT WebLoadRequest : public QObject
    {
        Q_OBJECT


       /*!
        * @brief The URL of the load request.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl url READ url)

       /*!
        * @brief The current status of the ongoing load.
        *
        * @see bb::cascades::WebLoadStatus::Type.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::WebLoadStatus::Type status READ status)

    public:

       /*!
        * @brief Constructs a @c WebLoadRequest from a URL, status, and optional parent.
        *
        * @c WebLoadRequests are created internally and passed as a parameter to the
        * @c WebView::loadingChanged() signal.
        *
        * @see @c WebView::loadingChanged().
        *
        *
        *
        * @since BlackBerry 10.0.0
        */
        explicit WebLoadRequest(const QUrl& url, bb::cascades::WebLoadStatus::Type status, QObject* parent = 0);
        ~WebLoadRequest();

        QUrl url() const; ///< @copydoc bb::cascades::WebLoadRequest#url
        bb::cascades::WebLoadStatus::Type status() const; ///< @copydoc bb::cascades::WebLoadRequest#status

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebLoadRequest)
        Q_DISABLE_COPY(WebLoadRequest)

        WebLoadRequestPrivate* const d_ptr;
        /*! @endcond */
    };

  } // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::WebLoadRequest)

#endif // cascades_webloadrequest_h

/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_webnavigationrequest_h
#define cascades_webnavigationrequest_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/webview.h>
#include <bb/cascades/web/webnavigationrequestaction.h>
#include <bb/cascades/web/webnavigationtype.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace bb {
  namespace cascades {

    class WebNavigationRequestPrivate;

    /*!
     * @brief A utility class for the @c WebView::navigationRequested() signal.
     *
     * This class contains information about the requested navigation, such as URL and navigation type,
     * and it is possible to decide the response action to the request by
     * setting the action property. You can also call @c WebNavigationRequest::ignore() to reject the
     * request.
     *
     * Here's a simple QML example demonstrating the use of a @c %WebNavigationRequest:
     * @snippet tad/examples/controls/webview/assets/main.qml webviewmisc_qml2
     *
     * @see @c WebView::navigationRequested().
     *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT WebNavigationRequest : public QObject
    {
        Q_OBJECT

       /*!
        * @brief The URL of the navigation request.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl url READ url CONSTANT FINAL)

       /*!
        * @brief The response action to the navigation request.
        *
        * This will default to @c WebNavigationRequestAction::Accept, which means that the navigation
        * will proceed if nothing is changed.
        * To block the navigation request, change this to @c WebNavigationRequestAction::Ignore.
        *
        * @see @c WebNavigationRequestAction
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::WebNavigationRequestAction::Type action READ action WRITE setAction NOTIFY actionChanged FINAL)

       /*!
        * @brief The type of navigation that caused this navigation request.
        *
        * @see @c WebNavigationType
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::WebNavigationType::Type navigationType READ navigationType CONSTANT FINAL)

    public:

       /*!
        * @brief Constructs a @c WebNavigationRequest from a URL, status, and optional parent.
        *
        * @c WebLoadRequests are created internally and passed as a parameter to the
        * @c WebView::navigationRequested() signal.
        *
        * @see @c WebView::navigationRequested().
        *
        *
        *
        * @since BlackBerry 10.0.0
        */
        explicit WebNavigationRequest(const QUrl& url, bb::cascades::WebNavigationType::Type navigationType, QObject* parent = 0);
        ~WebNavigationRequest();

        QUrl url() const; ///< @copydoc bb::cascades::WebNavigationRequest#url

        bb::cascades::WebNavigationType::Type navigationType() const; ///< @copydoc bb::cascades::WebNavigationRequest#navigationType

        bb::cascades::WebNavigationRequestAction::Type action() const; ///< @copydoc bb::cascades::WebNavigationRequest#action
        void setAction(bb::cascades::WebNavigationRequestAction::Type action); ///< @copydoc bb::cascades::WebNavigationRequest#action

       /*!
        * @brief Accepts the navigation request.
        *
        * Equivalent to @c setAction(WebNavigationRequestAction::Accept).
        *
        * @since BlackBerry 10.0.0
        */
        void accept();

        /*!
         * @brief Ignores the navigation request.
         *
         * Equivalent to @c setAction(WebNavigationRequestAction::Ignore).
         *
         * @since BlackBerry 10.0.0
         */
        void ignore();

    Q_SIGNALS:

       /*!
        * @brief Emitted when the action on this request has changed.
        *
        * @param action The new value of the action.
        *
        * @see @c WebNavigationRequestAction::Type.
        *
        * @since BlackBerry 10.0.0
        */
        void actionChanged(bb::cascades::WebNavigationRequestAction::Type action);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebNavigationRequest)
        Q_DISABLE_COPY(WebNavigationRequest)

        WebNavigationRequestPrivate* const d_ptr;
        /*! @endcond */
    };

  } // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::WebNavigationRequest)

#endif // cascades_webnavigationrequest_h

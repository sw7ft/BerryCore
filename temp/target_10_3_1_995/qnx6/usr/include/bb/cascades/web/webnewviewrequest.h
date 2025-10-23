/* Copyright (C) 2014 Research In Motion Limited.  */

#ifndef cascades_webnewviewrequest_h
#define cascades_webnewviewrequest_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/webview.h>

#include <QtCore/QObject>

namespace bb {
  namespace cascades {

    class WebNewViewRequestPrivate;

    /*!
     * @brief A utility class for the @c WebView::newViewRequested() signal.
     *
     * This class contains information about the request, such as whether it's a possibly
     * unwanted "popup", and it is possible to honor the request by calling the @c openIn
     * method in a slot connected to @c WebView::newViewRequested().
     *
     * To prevent opening a new view, for example if the @c isPopup flag is set, return
     * without calling @c openIn in your slot.
     *
     * @see @c WebView::newViewRequested().
     *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT WebNewViewRequest : public QObject
    {
        Q_OBJECT

        /*!
         * @brief Whether this request is a possibly unwanted "popup".
         *
         * A new view request is considered a "popup" if it was not initiated by user action. Web pages
         * can abuse the JavaScript window.open() mechanism to show advertisements and other unsolicited
         * content. If window.open() was not called as a consequence of user action, the popup property is
         * true. Otherwise it's false.
         *
         * If the isPopup flag is set to true, you may want to ignore the request. The problem is that some
         * popups may be vital for the correct function of a web page. If your application is written to show
         * a specific web page that depends on unsolicited popups, you may want to allow popups always.
         *
         * An example of a more intricate way to deal with popups is to have a setting for popup blocking
         * in your application's settings UI, perhaps with a notification displayed when a popup is
         * blocked to allow the user to recover by changing the setting and reloading the page in case the
         * popup is essential to the web page functionality.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bool popup READ isPopup CONSTANT FINAL)

    public:

        /*!
         * @brief Constructs a @c WebNewViewRequest
         *
         * @c WebNewViewRequests are created internally and passed as a parameter to the
         * @c WebView::newViewRequested() signal.
         *
         * @see @c WebView::newViewRequested().
         *
         * @since BlackBerry 10.3.0
         */
        explicit WebNewViewRequest(WebNewViewRequestPrivate& dd, QObject* parent = 0);
        ~WebNewViewRequest();

        /*!
         * @brief Whether this request is a possibly unwanted "popup".
         *
         * @since BlackBerry 10.3.0
         */
        bool isPopup() const;

        /*!
         * @brief Accepts the new view request and opens the request in the WebView provided.
         *
         * @param view The WebView or WebPage to open the request in.
         *
         * @since BlackBerry 10.3.0
         */
        Q_INVOKABLE void openIn(QObject* view);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebNewViewRequest)
        Q_DISABLE_COPY(WebNewViewRequest)

        WebNewViewRequestPrivate* const d_ptr;
        /*! @endcond */
    };

  } // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::WebNewViewRequest)

#endif // cascades_webnewviewrequest_h

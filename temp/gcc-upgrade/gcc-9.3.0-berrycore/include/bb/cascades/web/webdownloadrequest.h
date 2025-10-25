/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webdownloadrequest_h
#define cascades_webdownloadrequest_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/web/webloadstatus.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace bb {
  namespace cascades {

    class WebDownloadRequestPrivate;

    /*!
     * @brief A request to download a file.
     *
     * The @c WebDownloadRequest class is used with @c WebPage::download() to
     * download a file to the local file system. You must ensure that the device
     * has a working network connection before trying to download a file.
     *
     * Specify the URL to download using @c url. Specify the location to 
     * download the file to using @c absoluteFilePath. The path must be an 
     * absolute path, including file name and extension. For example, 
     * "/accounts/1000/shared/downloads/mydownload.myextension". 
     * If the @c absoluteFilePath is empty, a file picker will be shown and the 
     * user can pick a location and file name.
     *
     * @c WebDownloadRequest is normally used from C++ in advanced use cases, 
     * but here is an example of using @c WebDownloadRequest in QML. 
     *
     * @snippet tad/examples/controls/webdownloadrequest/assets/main.qml webdownloadrequest_qml1
     * 
     * This example assumes that you've registered both @c WebPage and 
     * @c WebDownloadRequest with QML. To register these classes with QML, 
     * add the following lines to your C++ main program:
     *
     * @snippet tad/examples/controls/webdownloadrequest/src/webdownloadrequest.cpp webdownloadrequest1     
     *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT WebDownloadRequest : public QObject {
        Q_OBJECT

        /*!
         * @brief The URL to download.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl url READ url WRITE qmlSetUrl FINAL)

        /*!
         * @brief The path to download the file to.
         *
         * The path must be an absolute path, including file name and extension.
         * For example, "/accounts/1000/shared/downloads/mydownload.myextension". 
         * If the @c absoluteFilePath is empty, a file picker will be shown and
         * the user can pick a location and file name.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString absoluteFilePath READ absoluteFilePath WRITE setAbsoluteFilePath NOTIFY absoluteFilePathChanged FINAL)

        /*!
         * @brief The download status.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::WebLoadStatus::Type status READ status NOTIFY statusChanged FINAL)

    public:

        /*!
         * @brief Used for QML support only.
         *
         * @since BlackBerry 10.0.0
         */
        WebDownloadRequest();

        /*!
         * @brief Constructs a new @c WebDownloadRequest for the provided URL.
         *
         * @param url The URL to download.
         * @param parent Optional parent for this object.
         *
         * @since BlackBerry 10.0.0
         */
        explicit WebDownloadRequest(const QUrl& url, QObject* parent = 0);
        virtual ~WebDownloadRequest();

        /*!
         * @brief Retrieves the URL to download in this @c WebDownloadRequest.
         *
         * @return url The URL to download.
         *
         * @since BlackBerry 10.0.0
         */
        QUrl url() const;

        /*!
         * @brief Retrieves the path to save the downloaded file to.
         *
         * @return The path to save the downloaded file to.
         *
         * @since BlackBerry 10.0.0
         */
        QString absoluteFilePath() const;

        /*!
         * @brief Retrieves the current status of this @c WebDownloadRequest.
         *
         * @return The current download status.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::WebLoadStatus::Type status() const;

    public Q_SLOTS:
        /*!
         * @brief Sets the path to save the downloaded file to.
         *
         * @param absoluteFilePath The new path.
         *
         * @since BlackBerry 10.0.0
         */
        void setAbsoluteFilePath(const QString& absoluteFilePath);

    Q_SIGNALS:
        /*!
         * @brief Emitted when download starts.
         *
         * @since BlackBerry 10.0.0
         */
        void started();

        /*!
         * @brief Emitted when download finishes and the download was successful.
         *
         * @since BlackBerry 10.0.0
         */
        void succeeded();

        /*!
         * @brief Emitted when download finishes because the download failed.
         *
         * @since BlackBerry 10.0.0
         */
        void failed();

        /*!
         * @brief Emitted when the path to download the file to changes.
         *
         * @param newAbsoluteFilePath The new path.
         *
         * @since BlackBerry 10.0.0
         */
        void absoluteFilePathChanged(const QString& newAbsoluteFilePath);

        /*!
         * @brief Emitted when the download status changes.
         *
         * @param newStatus The new status.
         *
         * @since BlackBerry 10.0.0
         */
        void statusChanged(WebLoadStatus::Type newStatus);

    private:
       /*! @cond PRIVATE */
        void qmlSetUrl(const QUrl&);

        Q_DECLARE_PRIVATE(WebDownloadRequest)
        Q_DISABLE_COPY(WebDownloadRequest)

        WebDownloadRequestPrivate* const d_ptr;
       /*! @endcond */
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webdownloadrequest_h

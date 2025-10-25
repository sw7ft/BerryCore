/*!
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_developmentsupport_h
#define cascades_developmentsupport_h

#include <bb/cascades/BaseObject>

namespace bb {
    namespace cascades {

    class DevelopmentSupportPrivate;

    /*!
     *
     * @brief Provides a signal for receiving live QML updates from the Momentics IDE for BlackBerry.
     *
     * @details This class makes it faster to work with a QML-based UI because QML updates
     * can be sent to the running application to greatly improve development turnaround time.
     *
     * When QML assets are changed and updated in the Momentics IDE, the @c assetsChanged()
     * signal is emitted. The application can capture this signal and respond by
     * refreshing the QML scene graph. All updated QML files in the application
     * assets folder are sent to the device.
     *
     * To use this feature, you must enable sending QML files to a device. In the Momentics IDE,
     * in %Window > Preferences > BlackBerry, select <b>Send QML files to device on save</b>,
     * the application must be built in debug mode and the development support must be installed
     * in valid application instance.
     *
     * @code
     * DevelopmentSupport::install(bb::cascades::Application::instance());
     * @endcode
     *
     * @xmlonly
     *     <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT DevelopmentSupport : public BaseObject {
        Q_OBJECT

    public:

        /*!
         * @brief Constructs a @c %DevelopmentSupport.
         *
         * @since BlackBerry 10.2.0
         */
        explicit DevelopmentSupport(QObject *parent=0);

        virtual ~DevelopmentSupport();

        /*!
         * @brief Installs development support to the Cascades application instance.
         *
         * The Cascades Application object takes ownership of the @c %DevelopmentSupport object that is created.
         *
         * @return A pointer to the @c %DevelopmentSupport instance that is created.
         *
         * @since BlackBerry 10.3.1
         */
        static DevelopmentSupport* install()
        {
#ifdef QT_DEBUG
            return DevelopmentSupport::install_helper();
#else
            return 0;
#endif
        }
    Q_SIGNALS:

        /*!
         * @brief Emitted when updated QML assets have been uploaded from Momentics.
         *
         * @param mainQmlFile The QML file set as main file from Momentics.
         *
         * @since BlackBerry 10.2.0
         */
        void assetsChanged(const QUrl & mainQmlFile);
    private:
        static DevelopmentSupport* install_helper();
    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(DevelopmentSupport)
        Q_DISABLE_COPY(DevelopmentSupport)
        /*! @endcond */

    };

    }
}

#endif /* cascades_developmentsupport_h */

/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_window_h
#define cascades_window_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QString>
#include <QVariant>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/BaseObject>
#include <bb/cascades/WindowState>
#include <bb/cascades/ScreenIdleMode>

#include <screen/screen.h>

namespace bb {
    namespace cascades {

    class WindowPrivate;

    /*!
     * @brief Provides access to native window properties and state.
     *
     * The @c %Window for the application is accessible through the @c Application::mainWindow property.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Window : public BaseObject
    {
    private:
        Q_OBJECT

        /*!
         * @brief Property specifying the window handle for this window.
         *
         * The value of this property can be safely converted to @c screen_window_t type.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant handle READ handleQml CONSTANT FINAL)

        /*!
         * @brief Property specifying the window group for this window.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString groupId READ groupId CONSTANT FINAL)

        /*!
         * @brief Property indicating the state of the window
         *
         * A stateChanged() signal is emitted when the value of this property changes.
         *
         * In addition a posted() signal is emitted when window changes its
         * state to WindowState::Posted.
         *
         * The default value is @c WindowState::Created.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::WindowState::Type state READ state NOTIFY stateChanged FINAL)

        /*!
         * @brief Property indicating the idle behavior of the screen when this window is displayed.
         *
         * The window may allow either the normal idle behavior with @c ScreenIdleMode::Normal, or
         * it can prevent idle behavior with @c ScreenIdleMode::KeepAwake.
         *
         * The default value is @c ScreenIdleMode::Normal.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ScreenIdleMode::Type screenIdleMode READ screenIdleMode WRITE setScreenIdleMode NOTIFY screenIdleModeChanged FINAL )

    public:
        /*!
         * @brief Destroys the window object.
         *
         * Does not affect the represented native window.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Window();

        /*!
         * @brief Returns the window handle for this window.
         *
         * @return A window handle (can be casted to screen_window_t type)
         *
         * @since BlackBerry 10.0.0
         */
        screen_window_t handle() const;

        /*!
         * @brief Returns the window group for this window.
         *
         * @return A string representing window group
         *
         * @since BlackBerry 10.0.0
         */
        QString groupId() const;

        /*!
         * Returns the state of the window.
         *
         * @return The state of the window
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::WindowState::Type state() const;

        /*!
         * @brief Returns the current mode the window is using to control the
         * idle behavior of the screen.
         *
         * Typically, this is to leave the behavior unchanged with @c ScreenIdleMode::Normal.
         *
         * @return The value of the current idle mode behavior. The returned value will be either
         *         @c ScreenIdleMode::Normal or @c ScreenIdleMode::KeepAwake.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ScreenIdleMode::Type screenIdleMode() const;

    public Q_SLOTS:
        /*!
         * @brief Controls the idle behavior of the screen when this window is displayed.
         *
         * Typically the idle behavior is to fade the display, but this may also include
         * other behaviors like locking the device.
         *
         * @param newScreenIdleMode The idle behavior to use when this window is displayed.  Must be one
         * of @c ScreenIdleMode::Normal, or @c ScreenIdleMode::KeepAwake.
         *
         *
         * @since BlackBerry 10.0.0
         */
        void setScreenIdleMode( bb::cascades::ScreenIdleMode::Type newScreenIdleMode );

    Q_SIGNALS:

        /*!
         * Emitted when the window state becomes WindowState::Posted.
         *
         * After this signal is emitted it is safe to use @c %Window's @c groupId and
         * @c handle with the APIs which require the window to be posted (such as for use
         * with Cards).
         *
         * @since BlackBerry 10.0.0
         */
        void posted();

        /*!
         * Emitted when the state of the window changes
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c state instead of @c newState).
         *
         * @param newState the new state of the window
         *
         * @since BlackBerry 10.0.0
         */
        void stateChanged(bb::cascades::WindowState::Type newState);

        /*!
         * Emitted when the idle mode behavior is changed.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c screenIdleMode instead of @c newScreenIdleMode).
         *
         * @param newScreenIdleMode The new idle behavior for the screen when this window is displayed.
         *
         * @since BlackBerry 10.0.0
         */
        void screenIdleModeChanged(bb::cascades::ScreenIdleMode::Type newScreenIdleMode );

    private:
        /*! @cond PRIVATE */
        explicit Window();
        QVariant handleQml() const;

        Q_DECLARE_PRIVATE(Window)
        Q_DISABLE_COPY(Window)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Window)

#endif

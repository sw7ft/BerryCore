/* Copyright (C) 2011 - 2014 BlackBerry Limited. All rights reserved. */

#ifndef cascades_application_h
#define cascades_application_h

#include "bbcascades_global.h"

#include <bb/Application>

namespace bb {
  namespace cascades {

    class ApplicationPrivate;
    class AbstractPane;
    class AbstractCover;
    class Menu;
    class Window;
    class ThemeSupport;

    /*!
     * 
     * @brief The class provides an event loop and handles application's menu scene, and main window.
     *
     * Cascades applications must use this class and not @c QCoreApplication or @c QApplication.
     *
     * The @c %Application class provides an event loop and an event delivery
     * mechanism for Cascades applications as well as providing the
     * following properties:
     * - #scene : specifies the @c AbstractPane to be used as the scene for the main application window
     * - #cover : specifies the @c AbstractCover to be used when the application is in cover mode (also known as an Active frame)
     * - #menu : application @c Menu accessible by the user by the swipe from the top of the screen.
     * - #menuEnabled : whether the application @c %Menu is enabled (it can be set to @c true even
     *   when menu isn't set so that it will provide the user with visual feedback that there's
     *   no menu)
     * - #mainWindow : provides access to an object representing applications's main @c Window
     * - #themeSupport : provides access to the theme used in the application
     *
     * Cascades applications are not expected to subclass this class but instead instantiate it and
     * invoke Application::exec() method to start the event loop.
     * Creating Cascades controls and other ui elements is only supported after an instance of
     * Application has been created. It must be created on the application's main thread.
     *
     * An example of simple application:
     * @code
     * #include <bb::cascades::Application>
     * #include <bb::cascades::Button>
     * #include <bb::cascades::Page>
     * 
     * using bb::cascades;
     *
     * int main(int argc, char **argv) {
     *     Application app(argc, argv);
     *
     *     Page *page = Page::create()
     *         .content(Button::create("Hello, World!"));
     *     app.setScene(page);
     *
     *     return app.exec();
     * }
     * @endcode
     *
     * Here's an example of an equivalent QML-based application. Note that the document loading
     * error checking is omitted (see @c QmlDocument for proper error checking).
     *
     * @code
     * // hello.qml file
     *
     * Page {
     *     Button { text: "Hello, World!" }
     * }
     * @endcode
     *
     * @code
     * // hello.cpp file
     *
     * #include <bb::cascades::Application>
     * #include <bb::cascades::QmlDocument>
     * #include <bb::cascades::Page>
     * 
     * using bb::cascades;
     *
     * int main(int argc, char **argv) {
     *     Application app(argc, argv);
     *
     *     QmlDocument *qml = QmlDocument::create(&app, "hello.qml");
     *     Page *page = qml->createRootObject<Page>();
     *     app.setScene(page);
     *
     *     return app.exec();
     * }
     * @endcode
     *
     * The @c Application instance is exposed to QML as a context property called "Application".
     * 
     * Here's an example of accessing the Application instance from QML:
     *
     * @code
     * Button {
     *     text: (Application.menuEnabled ? "Disable" : "Enable") 
     *             + " Application Menu"
     *     onClicked: Application.menuEnabled = !Application.menuEnabled;
     * }
     * @endcode 
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * <qml>
     * <class contextProperty="Application" />
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Application : public bb::Application {
    private:
        Q_OBJECT

        /*!
         * @brief The scene of the application.
         * 
         * The scene is displayed on the main window of the application.
         *
         * A sceneChanged() signal is emitted when this property is changed.
         *
         * The default value of this property is @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::AbstractPane* scene READ scene WRITE setScene RESET resetScene
                   NOTIFY sceneChanged FINAL);

        /*!
         * @brief The cover of the application.
         * 
         * The cover of the app is displayed on the Home screen when a user
         * minimizes the app by swiping up from the bottom of the screen. These minimized covers
         * are also referred to as Active frames.
         *
         * You can define your app's cover by using a @c SceneCover.
         * The default cover will take a screenshot of the whole application and scale it down
         * to cover mode.
         *
         * A @c coverChanged() signal is emitted when this property is changed.
         *
         * The default value of this property is @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::AbstractCover* cover READ cover WRITE setCover RESET resetCover
                   NOTIFY coverChanged FINAL);

        /*!
         * @brief The menu of the application displayed on the main window.
         *
         * A @c menuChanged() signal is emitted when this property is changed.
         *
         * The default value of this property is @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::Menu* menu READ menu WRITE setMenu RESET resetMenu
                   NOTIFY menuChanged FINAL);

        /*!
         * @brief The menu of the application displayed on the main window.
         * 
         * An application will typically disable the @c %Menu to avoid conflicts with
         * application behavior (such as the rubber band behavior of a ListView).
         * 
         * When the @c %Menu is disabled, it will be completely hidden and there will be no
         * rubber band animation indicating to the user that the swipe-down was successful.
         *
         * If the property is set to @c false while the @c %Menu is showing, it will be closed.
         *
         * A @c menuEnabledChanged() signal is emitted when this property changes.
         *
         * The default value of this property is @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool menuEnabled READ isMenuEnabled WRITE setMenuEnabled RESET resetMenuEnabled
                   NOTIFY menuEnabledChanged FINAL);

        /*!
         * @brief Provides access to the main @c Window of the application.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::Window* mainWindow READ mainWindow CONSTANT FINAL);
      
        /*!
         * @brief Provides access to @c ThemeSupport, which is used to retrieve theme related information,
         *
         * @c %ThemeSupport contains information about the application such as the color scheme
         * used for controls.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ThemeSupport* themeSupport READ themeSupport CONSTANT FINAL);

    public:

        /*!
         * @brief Constructs an @c Application object.
         *
         * @since BlackBerry 10.0.0
         */
        Application(int &argc, char **argv);

        /*!
         * @brief Destructs this @c Application object.
         *
         * The scene and menu are also destroyed if owned by the @c Application object.
         *
         * @since BlackBerry 10.0.0
         */
        ~Application();

        /*! @cond PRIVATE  */
        /*!
         * Overridden function from QCoreApplication
         *
         * @sa {QCoreApplication::notify}
         *
         */
        virtual bool notify(QObject *receiver, QEvent *event);
        /* @endcond */

        /*!
         * @brief Sets the root @c Pane for the application.
         *
         * The @c %Application object takes ownership of the passed @c pane unless
         * it already has a parent.
         *
         * If the replaced scene (if one was set) is owned by the @c %Application
         * it will be deleted, if not its ownership doesn't change. If it
         * already has another parent the caller MUST ensure that setScene(0)
         * is called before the scene object is deleted.
         *
         * @param scene The pane to be used as a scene or @c 0 to remove current scene.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setScene(bb::cascades::AbstractPane* scene);

        /*!
         * @brief Sets the cover to be used when the application is in cover mode.
         *
         * The @c %Application object takes ownership of the passed @c AbstractCover unless
         * it already has a parent.
         *
         * The default cover will take a screenshot of the whole application and scale it down
         * to cover mode.
         *
         * If the replaced cover (if one was set) is owned by the @c %Application
         * it will be deleted, if not its ownership doesn't change. If it
         * already has another parent the caller MUST ensure that setCover(0)
         * is called before the cover object is deleted.
         *
         * @param cover The cover to be used or @c 0 to remove current cover.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setCover(bb::cascades::AbstractCover* cover);

        /*!
         * @brief Returns the scene associated with the main window.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return pane serving as the scene for the main window or @c 0 if scene wasn't set.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::AbstractPane *scene() const;

        /*!
         * @brief Returns the cover used when the application is in cover mode.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The cover for this application or @c 0 if cover wasn't set.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::AbstractCover *cover() const;

        /*!
         * @brief Sets the value of @c #scene property to the default value which is @c 0.
         *
         * The replaced scene (if one was set) remains owned by its owner.
         *
         * If the replaced scene (if one was set) is owned by the @c %Application
         * it will be deleted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetScene();

        /*!
         * @brief Sets the value of @c #cover property to the default value which is @c 0.
         *
         * The replaced cover (if one was set) remains owned by its owner.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetCover();

        /*!
         * @brief Sets the application Menu
         *
         * The application will take ownership of the @c Menu if it doesn't have
         * a parent.
         *
         * If the replaced menu (if one was set) is owned by the application
         * it will be deleted, otherwise its ownership doesn't change.
         *
         * @param menu The new menu or @c 0 to remove the menu.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMenu(bb::cascades::Menu* menu);

        /*!
         * @brief Returns the @c Menu of the application.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The current application menu or @c 0 if one wasn't set.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::Menu* menu() const;

        /*!
         * @brief Sets the value of @c #menu property to the default value which is @c 0.
         *
         * The replaced menu (if one was set) remains owned by its owner.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMenu();

        /*!
         * @brief Enables or disables the @c Menu.
         *
         * An application will typically disable the @c %Menu to avoid conflicts with
         * application behavior (such as the rubber band behavior of a @c ListView).
         *
         * When the @c %Menu is disabled, it will be completely hidden and there will be no
         * rubber band animation indicating to the user that the swipe-down was successful.
         * If the enabled property is set to @c false while the @c %Menu is showing, it will
         * be closed.
         *
         * @param enabled If @c true the @c %Menu should be enabled, if @c false the @c %Menu
         * should be disabled.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMenuEnabled(bool enabled);

        /*!
         * @brief Returns whether the @c %Menu is enabled or not.
         *
         * @return @c true if the @c %Menu is enabled, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isMenuEnabled() const;

        /*!
         * @brief Sets the value of @c #menuEnabled property to the default value which is @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetMenuEnabled();

        /*!
         * @brief Retrieves this application's main window.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The application's main window.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::Window * mainWindow() const;

        /*!
         * @brief Retrieves the @c %ThemeSupport object.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The application's ThemeSupport object.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ThemeSupport* themeSupport() const;

        /*!
         * @brief Retrieves a resolved asset path, given a file name.
         *
         * Assets stored according to design unit selector principles
         * can be resolved with this method, which is useful when
         * developing c++ applications.
         *
         * @param url The filename to resolve.
         * @return A QString holding the full path to the file.
         *
         * @since BlackBerry 10.3.0
         */
        QString resolveAssetPath(const QUrl &url);

        /*!
         * @brief Retrieves the application instance.
         *
         * The application must be instantiated first or @c 0 will be returned with
         * a warning printout.
         *
         * @return A pointer to the @c pplication instance or @c 0 if the @c Application
         * has not been instantiated.
         *
         * @since BlackBerry 10.0.0
         */
        static Application  *instance();

    Q_SIGNALS:

        /*!
         * @brief Emitted when the menu is changed.
         *
         * @param menu A new menu or @c 0 if one was removed.
         *
         * @since BlackBerry 10.0.0
         */
        void menuChanged(bb::cascades::Menu *menu);

        /*!
         * @brief Emitted when the main window's scene is changed.
         *
         * @param scene A new scene or @c 0 if one was removed.
         *
         * @since BlackBerry 10.0.0
         */
        void sceneChanged(bb::cascades::AbstractPane *scene);

        /*!
         * @brief Emitted when the cover for this application is changed.
         *
         * @param cover A new cover or @c 0 if one was removed.
         *
         * @since BlackBerry 10.0.0
         */
        void coverChanged(bb::cascades::AbstractCover *cover);

        /*!
         * @brief Emitted when the @c #menuEnabled property changed.
         *
         * @param menuEnabledChanged @c true if the menu was enabled, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        void menuEnabledChanged(bool menuEnabledChanged);

    private:
        /*! @cond PRIVATE  */
        ApplicationPrivate  * const d_ptr;
        Q_DECLARE_PRIVATE(Application);
        /*! @endcond  */
    };

  } // namespace Cascades
}
#endif // ifndef cascades_application_h

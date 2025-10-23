/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef BB_CASCADES_FOREIGNWINDOWCONTROL_H
#define BB_CASCADES_FOREIGNWINDOWCONTROL_H

#include <QString>
#include <QRectF>
#include <QVariant>

#include <screen/screen.h>

#include <bb/cascades/bbcascades_global.h>


#include <bb/cascades/Control>
#include <bb/cascades/WindowProperty>
#include <bb/cascades/InputType>

namespace bb {
namespace cascades {
    
class ForeignWindowControlPrivate;
class Container;

/*!
 * 
 * @brief Allows for embedding a window from the Screen Graphics Subsystem (Screen window) 
 * into the Cascades scene graph.
 *
 * @image html foreignwindow_diagram.png A diagram explaining how @c %ForeignWindowControl works.
 *
 * @note This is an advanced control that requires an understanding of the Screen API. Please see 
 * <a href="http://developer.blackberry.com/native/documentation/bb10/com.qnx.doc.screen/topic/manual/cscreen_api_components.html">
 * Screen API Developer's guide</a> before using this control.
 * 
 * The @c %ForeignWindowControl is used for embedding a window from the Screen Graphics Subsystem 
 * (Screen window) into the Cascades scene graph. You must specify the @c windowId and/or @c windowHandle, 
 * as well as the @c windowGroup, if it differs from the main window group, in order for the 
 * @c %ForeignWindowControl to bind to a Screen window. When a Screen window matching the specified
 * @c windowId or @c windowHandle is attached to the window group matching @c windowGroup, 
 * @c %ForeignWindowControl will automatically bind to it and its @c boundToWindow property will be 
 * set to @c true. Once the @c %ForeignWindowControl is bound to a Screen window, it will update the
 * properties of the Screen window as specified by @c updatedProperties. You can specify to update Screen
 * window properties such as size and position, so the Screen window stays in sync with the position and size
 * of @c %ForeignWindowControl on the scene.
 *
 * <h4>%Window group</h4>
 *
 * In order to be displayed, a Screen window needs to join a window group in the main Cascades window group 
 * hierarchy (either the main group or one of subgroups). The main Cascades window group ID can be obtained 
 * from the main application @c Window through @c Application::instance()->mainWindow()->groupId().
 *
 * <h4>Unbind and rebind</h4>
 *
 * To unbind the @c %ForeignWindowControl from the Screen window, you can call @c unbindFromWindow().
 * The control will be unbound from the Screen window and its @c #boundToWindow property will be set to
 * @c false and @c windowHandle will be set to @c 0. 
 *
 * You can also rebind %ForeignWindowControl to another Screen window in two ways:
 * - You can change the @c windowId, then, when another Screen window matching that 
 * @c windowId or @c windowHandle is attached to a window group matching @c windowGroup, 
 * @c %ForeignWindowControl will be bound to that Screen window. 
 *
 * - Or, you can call @c bindToWindow() method with the new parameters.
 *
 * You cannot create a new Screen context, then a Screen window from that context, then assign 
 * that handle to @c windowHandle. The Screen window must join the main Cascades window group after 
 * the @c %ForeignWindowControl creation, since it must be part of the Cascades Screen context. 
 * So, to rebind another Screen window to @c %ForeignWindowControl, the Screen window must be part 
 * of the main Cascades window group and bound to another or the same @c %ForeignWindowControl.
 * 
 * <h4>Size and layout</h4>
 *
 * You can use @c preferredWidth and @c preferredHeight, and/or @c minWidth, @c minHeight, @c maxWidth,
 * @c maxHeight dimension properties to set the dimensions of the @c %ForeignWindowControl.
 *
 * UI controls placed on top of the @c %ForeignWindowControl in the scene will be rendered overlapping the
 * contents of the @c %ForeignWindowControl. This allows you to display a UI on top of the @c %ForeignWindowControl.
 * UI controls placed underneath the @c %ForeignWindowControl will be completely obscured by the contents 
 * of the @c %ForeignWindowControl.
 *
 * <h4>Signals</h4>
 *
 * Once a Screen window matching the @c windowId and/or @c windowHandle is attached to the window group 
 * matching @c windowGroup, a @c windowAttached() signal is emitted. If @c %ForeignWindowControl was 
 * created after the Screen window was attached to the window group, then the signal will not be emitted.
 *
 * <h4>Z-order</h4>
 *
 * From an implementation view, @c %ForeignWindowControl "punches a hole" in the Cascades UI to allow
 * content of @c %ForeignWindowControl or underneath the Cascades UI to be seen. This implies that the
 * Screen window should be placed below Cascades main window, specifically, having a lower Z-order. 
 * The Z-order on a Screen window is set by the @c SCREEN_PROPERTY_ZORDER window attribute.
 * 
 * Cascades main window has a Z-order of @c 0, so @c %ForeignWindowControl Z-order should be negative. 
 * However, you can set the Z-order to a positive number, but this will make the Screen window to appear
 * on top of the Cascades main window. Screen windows that lay on top of the Cascades main window intercept
 * the input events for the covered area using BPS events.
 *
 * @warning The current implementation has the following limitations:
 * - Setting the @c VisualNode::opacity attribute on this control or its parents have no effect on the 
 * control (However, @c VisualNode::visible does work, and can be used for hiding @c %ForeignWindowControl)
 * - While @c %ForeignWindowControl can be arbitrarily transformed, the bound Screen window can only
 * be positioned as an axis-aligned rectangle. Applying transformations, such as
 * rotation or scaling, may result in rendering artifacts.
 *
 * Here's an example of how to create a Screen window and a @c %ForeignWindowControl in C++:
 * 
 * @code
 * class HelloCascadesApp: public QObject
 * {
 *     Q_OBJECT
 * public slots:
 *     void onWindowAttached(screen_window_t handle,
 *                           const QString &group,
 *                           const QString &id);
 * public:
 *     HelloCascadesApp();
 * private:
 *     void createForeignWindow(const QString &group,
 *                              const QString &id, 
 *                              int width, int height);
 * };
 *
 * void HelloCascadesApp::onWindowAttached(screen_window_t handle,
 *                                         const QString &group,
 *                                         const QString &id)
 * {
 *     // This signal will only be emitted when window with
 *     // specified handle is attached;
 *     // application change attached window's properties;
 *     // no need to call bindToWindow() because it will be done
 *     // automatically in this case
 * }
 * 
 * void HelloCascadesApp::createForeignWindow(const QString &group,
 *                                            const QString &id,
 *                                            int width, int height)
 * {
 *     QByteArray groupArr = group.toAscii();
 *     QByteArray idArr = id.toAscii();
 *     
 *     Q_ASSERT(width > 0 && height > 0);
 *
 *     screen_context_t screen_ctx;
 *     screen_create_context(&screen_ctx, SCREEN_APPLICATION_CONTEXT);
 *     
 *     screen_window_t screen_win;
 *     screen_create_window_type(&screen_win, screen_ctx,
 *                               SCREEN_CHILD_WINDOW);
 *     screen_join_window_group(screen_win, groupArr.constData());
 *     screen_set_window_property_cv(screen_win,
 *                                   SCREEN_PROPERTY_ID_STRING,
 *                                   idArr.length(),
 *                                   idArr.constData());
 *     
 *     int vis = 1;
 *     screen_set_window_property_iv(screen_win,
 *                                   SCREEN_PROPERTY_VISIBLE, &vis);
 *     
 *     int color = 0xff0000ff;
 *     screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_COLOR,
 *                                   &color);
 *     
 *     int rect[4] = { 0, 0, 1, 1 };
 *     screen_set_window_property_iv(screen_win,
 *                                   SCREEN_PROPERTY_BUFFER_SIZE,
 *                                   rect+2);
 *     int dims[2] = { width, height };
 *     screen_set_window_property_iv(screen_win,
 *                                   SCREEN_PROPERTY_SOURCE_SIZE,
 *                                   dims);
 *     
 *     int z = -5; // use negative Z order so that the window
 *                 // appears under the main window
 *     screen_set_window_property_iv(screen_win, 
 *                                   SCREEN_PROPERTY_ZORDER, &z);
 *     
 *     int pos[2] = { -rect[2], -rect[3] };
 *     screen_set_window_property_iv(screen_win,
 *                                   SCREEN_PROPERTY_SOURCE_POSITION,
 *                                   pos);
 *     
 *     screen_buffer_t screen_buf;
 *     screen_create_window_buffers(screen_win, 1);
 *     screen_get_window_property_pv(screen_win,
 *                                   SCREEN_PROPERTY_RENDER_BUFFERS,
 *                                   (void **)&screen_buf);
 *     screen_post_window(screen_win, screen_buf, 1, rect, 0);
 *
 *     // note: no resource cleanup or error handling in the
 *     // sample code
 * }
 * 
 * HelloCascadesApp::HelloCascadesApp()
 * {
 *     const int WIN_W = 300;
 *     const int WIN_H = 300;
 *     // this will be the window id we'll set to the
 *     // libscreen window
 *     QString windowId("HelloCascadesAppID");
 *
 *     // create a foreign window control and specify the same windowId
 *     // as the one that will be set on the created libscreen window;
 *     // windowGroup is initialized to the main window group id so no need
 *     // to specify it
 *     ForeignWindowControl *pFW = ForeignWindowControl::create()
 *         .windowId(windowId)
 *         .preferredSize(WIN_W, WIN_H);
 *
 *     Container *pContainer = Container::create()
 *         .background(Color::Red)
 *         .layout(AbsoluteLayout::create())
 *         .add(Button::create()
 *             .text("Overlapped by ForeignWindowControl")
 *             .preferredWidth(350))
 *         .add(pFW)
 *         .add(Button::create()
 *             .text("Overlapping ForeignWindowControl")
 *             .ty(250)
 *             .preferredWidth(350));
 *
 *     QObject::connect(pFW, 
 *                      SIGNAL(windowAttached(screen_window_t,QString,QString)),
 *                      this,
 *                      SLOT(onWindowAttached(screen_window_t,QString,QString)));
 *
 *     createForeignWindow(pFW->windowGroup(), pFW->windowId(), WIN_W, WIN_H);
 *
 *     Application::instance()->setScene(Page::create().content(pContainer));
 * }
 * @endcode
 *
 * Here's a QML code sample that shows you how to create a Screen window and @c %ForeignWindowControl.
 * Let's assume that there's a service called @c %ViewFinder, which is exposed as a context property.
 * @c Viewfinder has a @c createWindow() method that creates and attaches a Screen window 
 * with the window group and ID that are passed in as parameters.
 *
 * @code
 * import bb.cascades 1.0
 * Page {
 *     Container {
 *         Button {
 *             text: "Create ViewFinder"
 *             // gets disabled once ForeignWindowControl is bound to a window
 *             enabled: !viewWindow.boundToWindow
 *             onClicked: {
 *                 // create a foreign window with current the dimensions of
 *                 // the ForeignWindowControl
 *                 ViewFinder.createWindow(viewWindow.windowGroup,
 *                                         viewWindow.windowId,
 *                                         handler.layoutFrame.width,
 *                                         handler.layoutFrame.height);
 *             }
 *         }
 *         ForeignWindowControl {
 *             id: viewWindow
 *
 *             windowId: "MyWindowId" // the window id to bind to
 *
 *             // override the default properties to update window's size and position only
 *             updatedProperties: WindowProperty.Size | WindowProperty.Position
 *
 *             visible: boundToWindow // becomes visible once bound to a window
 *
 *             preferredWidth: 400
 *             preferredHeight: 400
 *
 *             attachedObjects: [
 *                 // layout handler to track control dimensions
 *                 LayoutUpdateHandler {
 *                     id: handler
 *                 }
 *             ]
 *         }
 *     }
 * }
 * @endcode
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * @endxmlonly
 *
 * @xmlonly
 * <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ForeignWindowControl : public Control
{
private:
    Q_OBJECT

    /*!
     * @brief The Screen window handle this control is or will be bound to.
     *
     * This property corresponds to @c SCREEN_PROPERTY_WINDOW from the Screen API. A given Screen 
     * window is bound to @c %ForeignWindowControl when a Screen window with a handle matching this 
     * property joins the window group matching @c windowGroup.
     * 
     * The @c QVariant value of this property can be safely converted to @c screen_window_t type.
     *
     * If this property is specified, the Screen window must be attached to the main Cascades window group
     * and Screen window handle must have come from another or the same @c %ForeignWindowControl, since 
     * it has to bound to the Cascades Screen Graphics Subsystem context (Screen context) and not the 
     * Screen context created by the application.
     *
     * If the windowId is specified, this property should correspond to the same Screen window as the handle.
     *
     * @note Specifying this property alone, without @c windowGroup, is
     * not sufficient for binding the control. Both the @c windowGroup and @c windowHandle 
     * properties must be specified to bind to a Screen window to @c %ForeignWindowControl assuming the 
     * @c windowId, if specified, matches the Screen window.
     *
     * Changing this property after the control is already bound will unbind the Screen window from 
     * @c %ForeignWindowControl. When this happens, the @c boundToWindow property is set @c false and 
     * the @c %ForeignWindowControl will remain unbound until a Screen window matching new parameters 
     * is attached or @c bindToWindow() is called to bind to a window manually.
     *
     * A @c windowHandleChanged() signal is emitted when this property changes.
     *
     * The default value of this property is @c 0.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant windowHandle
               READ windowHandleQml WRITE setWindowHandleQml NOTIFY windowHandleChanged FINAL)

    /*!
     * @brief The window group that a Screen window must join in order to be
     * bound to @c %ForeignWindowControl.
     *
     * This property corresponds to @c SCREEN_PROPERTY_GROUP from the Screen API.
     * Only when Screen windows are attached to the window group matching this property
     * and also matching the @c windowId or @c windowHandle results in the @c windowAttached()
     * signal being emitted.
     *
     * @note Specifying this property alone, without @c windowId or @c windowHandle, is
     * not sufficient for binding the control. Both the @c windowGroup and @c windowId and/or 
     * @c windowHandle properties must be specified to bind to a Screen window to @c %ForeignWindowControl.
     *
     * Changing this property after the control is already bound will unbind the Screen window from 
     * @c %ForeignWindowControl. When this happens, the @c boundToWindow property is set @c false and 
     * the @c %ForeignWindowControl will remain unbound until a Screen window matching a new set of 
     * parameters is attached or @c bindToWindow() is called to bind to a Screen window manually.
     *
     * A @c windowGroupChanged() signal is emitted when this property changes.
     *
     * The default value of this property is the main Cascades window group
     * @sa Application::mainWindow
     * @sa Window
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString windowGroup
               READ windowGroup WRITE setWindowGroup NOTIFY windowGroupChanged FINAL)

    /*!
     * @brief The window ID of a Screen window that @c %ForeignWindowControl 
     * is or will be bound to.
     * 
     * The application must specify this property in order for the control to be bound to a Screen window 
     * attached to group specified by @c windowGroup property.
     *
     * This property corresponds to @c SCREEN_PROPERTY_ID_STRING of Screen API. If this property is set, only a 
     * Screen window with a matching window ID that is part of the window group specified by @c windowGroup 
     * will result in @c windowAttached() signal being emitted and control being bound to the window.
     *
     * @note Specifying this property alone, without a @c windowGroup, is not sufficient for binding the control.
     * Both the @c windowGroup and @c windowId properties must be specified to bind to a Screen window to 
     * @c %ForeignWindowControl.
     *
     * Changing this property after the control is already bound will unbind the Screen window from 
     * @c %ForeignWindowControl. When this happens, the @c boundToWindow property is set @c false and the 
     * @c %ForeignWindowControl will remain unbound until a Screen window matching a new set of parameters 
     * is attached or @c bindToWindow() is called to bind to a Screen window manually.
     *
     * A @c windowIdChanged() signal is emitted when this property changes.
     *
     * The default value of this property is @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString windowId READ windowId WRITE setWindowId NOTIFY windowIdChanged FINAL)

    /*!
     * @brief Indicates whether this control is currently bound to a Screen window
     * 
     * This property will be @c true after the control has been either explicitly 
     * (by calling @c bindToWindow()) or automatically (if a matching window was
     * attached) bound to a Screen window, @c false otherwise.
     *
     * An @c boundToWindowChanged() signal is emitted when this property changes.
     *
     * The default value of this property is @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool boundToWindow READ isBoundToWindow NOTIFY boundToWindowChanged FINAL)

    /*!
     * @brief The Screen window's properties to automatically update.
     * 
     * If this property is set to a value other than @c WindowProperty::None, the control will automatically
     * update the specified properties of the bound Screen window.
     *
     * Here is the list of possible window properties and their effects:
     *
     * - @c WindowProperty::None - Value signifying that no property of the bound Screen window
     *   should be updated. This value should be used exclusively, not in combination with any others.
     *
     * - @c WindowProperty::Position - Specifies that @c SCREEN_PROPERTY_POSITION 
     *   property of the Screen window should be updated to match the position of the @c %ForeignWindowControl.
     *
     * - @c WindowProperty::Size - Specifies that @c SCREEN_PROPERTY_SIZE property
     *   of the Screen window should be updated to match the dimensions of the @c %ForeignWindowControl.
     *
     * - @c WindowProperty::SourceSize - Specifies that @c SCREEN_PROPERTY_SOURCE_SIZE
     *   property of the Screen window should be updated to the dimensions of the @c %ForeignWindowControl. 
     *   This effectively means that Screen window's content will always be presented at 1:1 ratio.
     *
     * - @c WindowProperty::Visible - Specifies that @c SCREEN_PROPERTY_VISIBLE property 
     *   of the Screen window should be updated to match the @c VisualNode::visible property 
     *   of the @c %ForeignWindowControl. 
     *
     *   @note Visibility inherited by parent controls of @c %ForeignWindowControl are not set on 
     *   @c %ForeignWindowControl, or the Screen window @c SCREEN_PROPERTY_VISIBLE property. Only 
     *   @c %ForeignWindowControl::Visible property is bound to the Screen window @c SCREEN_PROPERTY_VISIBLE
     *   property.
     *
     * You can combine property flags using a bitwise OR. For example, @c WindowProperty::Size | @c WindowProperty::Position
     * specifies that @c %ForeignWindowControl will update @c SCREEN_PROPERTY_SIZE and @c SCREEN_PROPERTY_POSITION properties
     * of Screen window to correspond to changes in the size or position of @c %ForeignWindowControl. Note that you cannot 
     * use @c WindowProperty::None in combination with any other flags, that flag is to be used by itself only.
     *
     * An @c %updatedPropertiesChanged() signal is emitted when this property changes.
     * 
     * The default value of this property is a combination of @c %WindowProperty flags:
     * (@c WindowProperty::Position | @c WindowProperty::Size | @c WindowProperty::SourceSize) which
     * means that @c %ForeignWindowControl will update @c SCREEN_PROPERTY_SIZE, @c SCREEN_PROPERTY_SOURCE_SIZE
     * and @c SCREEN_PROPERTY_POSITION properties of the Screen window.
     *
     * @see WindowProperty
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::WindowProperty::Types updatedProperties
               READ updatedProperties
               WRITE setUpdatedProperties
               NOTIFY updatedPropertiesChanged 
               RESET resetUpdatedProperties
               FINAL)

    /*!
     * This property is depricated - use forwardedInputTypes instead
     *
     * @brief Indicates whether the control should receive Cascades key events when it is in focus (Control::focused is true) 
     * or whether raw Screen key input should be forwarded to the Screen window bound to this control.
     *
     * If the property is set to @c true, when @c %ForeignWindowControl has focus, keyboard input events will be forwarded 
     * to the Screen window that is bound to @c %ForeignWindowControl. Specifically, the @c %ForeignWindowControl will receive 
     * the keyboard focus in the Cascades main window group. See @c SCREEN_PROPERTY_KEYBOARD_FOCUS in 
     * <a href="http://developer.blackberry.com/native/reference/bb10/screen_libref/topic/screen_8h_1Screen_Property_Types.html">Screen property types</a>
     * for more information. When @c %ForeignWindowControl loses focus, the key input focus will be transferred to Cascades main
     * window or another ForeignWindowControl component if one is in focus and has requested key input forwarding.
     *
     * If this property is set to @c false, the @c %ForeignWindowControl will be receiving keyboard input like any Cascades 
     * control does when it is in focus.
     *
     * @note In order for @c %ForeignWindowControl to be able to receive key input focus, it must be attached to the Cascades 
     * main window group.
     *
     * A @c keyInputForwardingEnabledChanged() signal is emitted when this property changes.
     *
     * The default value of this property is @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool keyInputForwardingEnabled
               READ isKeyInputForwardingEnabled
               WRITE setKeyInputForwardingEnabled
               RESET resetKeyInputForwardingEnabled
               NOTIFY keyInputForwardingEnabledChanged FINAL)

    /*!
     * @brief Indicates which input types should be forwarded to the bound window
     * when the foreign window control is in focus.
     *
     * For each type that is specified, Cascades will yield focus from it's
     * main window sessions. This will in turn shift that focus to the bound
     * window. For these types, Cascades will no longer handle any such events
     * until the foreign window control has lost focus.
     *
     * Here is an example on how to specify input types:
     *
     * @code
     * int typesToForward = 0;
     * typesToForward |= InputType::Keyboard; // I want keyboard input
     * typesToForward |= InputType::Joystick // I also want jog input
     * pForeignWindowControl->setForwardedInputTypes(typesToForward);
     * @endcode
     *
     * A @c forwardedInputTypesChanged() signal is emitted when this property changes.
     *
     * The default behavior is that no input is forwarded to the control.
     *
     * @since BlackBerry 10.3.1
     * @see bb::cascades::InputType
     */
    Q_PROPERTY(int forwardedInputTypes
               READ forwardedInputTypes
               WRITE setForwardedInputTypes
               RESET resetForwardedInputTypes
               NOTIFY forwardedInputTypesChanged REVISION 4 FINAL)

public:
    /*!
     * @brief Constructs a @c %ForeignWindowControl and specifies the parent container.
     * The ownership of the control is transferred to the parent, if a parent is specified.
     *
     * @param parent The parent container or @c 0. This parameter is optional. 
     * The default is @c 0 if you don't specify a parent.
     *
     * @since BlackBerry 10.0.0
     */
    explicit ForeignWindowControl(Container * parent = 0);
  
    /*!
     * @brief Destructor.
     *
     * @note Destroying a @c %ForeignWindowControl has no effect on the Screen window it
     * is bound to.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ForeignWindowControl();

    /*!
     * @brief Returns the window handle the @c %ForeignWindowControl is or will be bound to.
     *
     * @return A window handle of type @c screen_window_t.
     *
     * @since BlackBerry 10.0.0
     */
    screen_window_t windowHandle() const;

    /*!
     * @brief Returns the window group the @c %ForeignWindowControl is or will be bound to.
     *
     * @return A @c QString representing window group.
     *
     * @since BlackBerry 10.0.0
     */
    QString windowGroup() const;

    /*!
     * @brief Returns window ID the @c %ForeignWindowControl is or will be bound to.
     *
     * @return A @c QString representing window ID.
     *
     * @since BlackBerry 10.0.0
     */
    QString windowId() const;
    
    /*!
     * @brief Indicates whether the @c %ForeignWindowControl has been bound to an attached window.
     *
     * @return @c true if the control has been bound to a window, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isBoundToWindow() const;

    /*!
     * @brief Returns the properties which the @c %ForeignWindowControl will automatically update
     * on the Screen window it is bound to.
     *
     * @return A set of flags representing the properties @c %ForeignWindowControl will update, or
     * @c WindowProperty::None if no properties are to be updated.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::WindowProperty::Types updatedProperties() const;

    /*!
     * @brief Indicates whether a Screen window bound to the @c %ForeignWindowControl will receive key input events,
     * or @c %ForeignWindowControl will receive Cascades key input events.
     *
     * @return @c true if the bound Screen window will receive key input events,
     * @c false if the control will receive Cascades key input events.
     *
     * @since BlackBerry 10.0.0
     */
    bool isKeyInputForwardingEnabled() const;

    /*!
     * @brief Indicates which input events should be forwarded to the bound
     * screen window when the foreign window control is in focus.
     *
     * @return The values which will be forwarded.
     *
     * @since BlackBerry 10.3.1
     * @see bb::cascades::InputType
     */
	Q_REVISION(4)
    int forwardedInputTypes() const;

    /*!
     * @brief Sets the window group that the @c %ForeignWindowControl is or will be bound to.
     *
     * Changing this property while the @c %ForeignWindowControl is bound to a Screen window
     * will unbind from the Screen window from @c %ForeignWindowControl.
     *
     * @param windowGroup A @c QString representing window group.
     *
     * @since BlackBerry 10.0.0
     */
    void setWindowGroup(const QString &windowGroup);

    /*!
     * @brief Sets the window ID that the @c %ForeignWindowControl is or will be bound to.
     *
     * Changing this property while the @c %ForeignWindowControl is bound to a Screen window
     * will unbind from the Screen window from @c %ForeignWindowControl.
     *
     * @param windowId A @c QString representing window group.
     *
     * @since BlackBerry 10.0.0
     */
    void setWindowId(const QString &windowId);

    /*!
     * @brief Sets the window handle that the @c %ForeignWindowControl is or will be bound to.
     *
     * Changing this property while the @c %ForeignWindowControl is bound to a Screen window
     * will unbind from the Screen window from @c %ForeignWindowControl.
     *
     * @param handle A window handle of type @c screen_window_t.
     *
     * @since BlackBerry 10.0.0
     */
    void setWindowHandle(screen_window_t handle);

    /*!
     * @brief Sets the properties the @c %ForeignWindowControl will update on the Screen window it is
     * bound to.
     *
     * Example: Setting @c updatedProperties to only update @c WindowProperty::Size and
     * @c WindowProperty::Position but not @c WindowProperty::SourceSize.
     * @code
     * pForeignWindow->setUpdatedProperties( 
     *      WindowProperty::Size | WindowProperty::Position);
     * @endcode
     *
     * @param updatedProperties The flags representing properties to be updated by the @c %ForeignWindowControl
     * on the Screen window it is bound to, or @c WindowProperty::None if no properties are to be updated.
     *
     * @since BlackBerry 10.0.0
     */
    void setUpdatedProperties(bb::cascades::WindowProperty::Types updatedProperties);

    /*!
     * @brief Sets key input event state to whether the @c %ForeignWindowControl should receive Cascades 
     * key input events when in focus or the bound Screen window should receive key input events when in focus.
     *
     * @param keyInputForwardingEnabled If @c true, @c %ForeignWindowControl will receive key input events
     * when in focus. If @c false, the bound Screen window will receive key input events
     * and the control will not receive any Cascades key input events.
     *
     * @since BlackBerry 10.0.0
     */
    void setKeyInputForwardingEnabled(bool keyInputForwardingEnabled);

    /*!
     * @brief sets which input events should be forwarded to the bound
     * screen window when the foreign window control is in focus.
     *
     * @param inputTypes The values which will be forwarded.
     *
     * @since BlackBerry 10.3.1
     * @see bb::cascades::InputType
     */
	Q_REVISION(4)
    void setForwardedInputTypes(int inputTypes);

    /*!
     * @brief Sets the value of @c updatedProperties property to its default value which is
     * a combination of @c %WindowProperty flags: 
     * @code
     * WindowProperty::Position | WindowProperty::Size | WindowProperty::SourceSize
     * @endcode
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetUpdatedProperties();

    /*!
     * @brief Sets the value @c keyInputForwardingEnabled property to its default value which is
     * @c true.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetKeyInputForwardingEnabled();

    /*!
     * @brief Resets which input events should be forwarded to the bound
     * screen window when the foreign window control is in focus.
     *
     * The default value is no events.
     *
     * @since BlackBerry 10.3.1
     */
	Q_REVISION(4)
    Q_SLOT void resetForwardedInputTypes();

    /*!
     * @brief Binds this @c %ForeignWindowControl with a Screen window specified by the arguments.
     *
     * After this call, @c %ForeignWindowControl will start updating associated Screen window's 
     * size, position, and source size to match those of @c %ForeignWindowControl so that the 
     * window always matches @c %ForeignWindowControl position and dimensions.
     *
     * The ID, group, and handle properties of the @c %ForeignWindowControl will be updated to
     * reflect the attached Screen window's parameters.
     *
     * This method should be called only after the Screen window was attached to the group,
     * which means either from a slot function connected to the @c windowAttached() signal, or
     * after the @c windowAttached() signal is emitted. Calling this method before the Screen window is
     * attached won't bind the Screen window to ForeignWindowControl properly, since 
     * @c %ForeignWindowControl will try to manipulate the Screen window which hasn't been attached yet.
     *
     * Calling this method after the @c %ForeignWindowControl was already bound to a Screen window 
     * will unbind it, and set the @c boundToWindow property to @c false. Then, @c %ForeignWindowControl will be bound
     * to the new Screen window specified in the arguments, and @c boundToWindow property set back to @c true. 
     * You can call this method after @c %ForeignWindowControl was already previously bound to an attached window
     * either explicitly with @c bindToWindow() during attachment phase or automatically if window ID and/or handle were 
     * specified and a matching window was attached.
     *
     * @param windowHandle A window handle of the child Screen window associated with Cascades Screen context
     * (part of the Cascades main window group) for @c %ForeignWindowControl to be bound to.
     * @param windowGroup A @c QString representing the window group.
     * @param windowId A @c QString representing the ID of the window.
     *
     * @xmlonly
     * <qml>
     * <param name="windowHandle" type="QVariant"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    void bindToWindow(screen_window_t windowHandle,
                      const QString &windowGroup,
                      const QString &windowId);
 
    /*!
     * @brief Unbinds @c %ForeignWindowControl from the Screen window it is currently
     * bound to.
     *
     * If @c %ForeignWindowControl is bound to a Screen window and @c #boundToWindow property is
     * @c true, calling this method will unbind the currently bound Screen window. It will also stop updating the 
     * bound Screen window properties, and stop forwarding key input events to
     * the Screen window if configured to do. The control will not receive a 
     * @c windowDetached() signal if the previously bound Screen window detaches from
     * the window group after calling this method.
     *
     * The @c #boundToWindow property of the control will be set to @c false and
     * @c windowHandle property will be set to 0.
     *
     * If later, a window matching current @c windowGroup
     * and @c windowId properties is attached, @c %ForeignWindowControl will bind to that
     * Screen window.
     *
     * If the control isn't bound to a Screen window and @c #boundToWindow property is
     * @c false, calling this method has no effect.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void unbindFromWindow();

    /*!
     * @brief Opens the Context Menu showing the actions currently set on the @c %ForeignWindowControl.
     * 
     * If the @c %ForeignWindowControl is disabled or has visibility set to @c false,
     * this function call does nothing.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void showContextMenu();

Q_SIGNALS:
    /*!
     * @brief Emitted when a Screen window matching this Screen window parameters (ID and handle
     * if specified) is attached to the specified group.
     *
     * This signal is emitted only when a Screen window matching the specified
     * by the @c #windowId and @c #windowGroup properties
     * is attached to the group specified by @c #windowGroup property.
     * The control will be automatically bound to the attached Screen window.
     *
     * @param windowHandle A window handle of the child Screen window which was attached to the window group.
     * This handle must associated with the Cascades Screen context.
     * @param windowGroup A @c QString representing the window group which this Screen window has joined.
     * @param windowId A @c QString representing the ID of the window if the window had 
     * it set; @c QString::null otherwise.
     *
     * @xmlonly
     * <qml>
     * <param name="windowHandle" type="QVariant"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    void windowAttached(screen_window_t windowHandle,
                        const QString &windowGroup,
                        const QString &windowId);
    
    /*! @cond PRIVATE */
    /*!
     * @copydoc windowAttached(screen_window_t, const QString&, const QString&)
     */
    void windowAttached(const QVariant &windowHandle,
                        const QString &windowGroup,
                        const QString &windowId);
    /*! @endcond */
    
    /*!
     * @brief Emitted when a attached Screen window closes down and it is removed from the group.
     * 
     * This signal is emitted when the attached Screen window is closed.
     *
     * The handle in @c windowHandle property is not valid when
     * this signal is emitted since the window has already been destroyed.
     *
     * After the control emits this signal the @c windowHandle property will be
     * reset to the default value of @c 0 and the @c boundToWindow property will
     * be set to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    void windowDetached();

    /*!
     * @brief Emitted when the Screen window handle of this control is changed.
     *
     * @param windowHandle A new Screen window handle.
     * @xmlonly
     * <qml>
     * <param name="windowHandle" type="QVariant"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    void windowHandleChanged(screen_window_t windowHandle);

    /*! @cond PRIVATE */
    void windowHandleChanged(const QVariant & windowHandle);
    /*! @endcond */

    /*!
     * @brief Emitted when the window group of this control is changed.
     *
     * @param windowGroup A @c QString representing new window group.
     *
     * @since BlackBerry 10.0.0
     */
    void windowGroupChanged(const QString& windowGroup);

    /*!
     * @brief Emitted when the window id of this control is changed.
     *
     * @param windowId A @c QString representing new window ID.
     *
     * @since BlackBerry 10.0.0
     */
    void windowIdChanged(const QString& windowId);

    /*!
     * @brief Emitted when @c %ForeignWindowControl becomes bound to a window.
     *
     * @param boundToWindow Indicates whether the window is bound or not, @c true if @c %ForeignWindowControl is
     * bound to a Screen window, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void boundToWindowChanged(bool boundToWindow);

    /*!
     * @brief Emitted when the @c #updatedProperties property changes
     *
     * @note Due to a workaround for a Qt Core issue with accessing enums from QML,
     * the argument of this signal doesn't follow naming convention for signals in
     * which the signal arguments are typically named to match the associated property's name.
     * Use the object's property to access current property value instead of the signal argument
     * to avoid runtime errors (for example, use @c updatedProperties instead of @c newUpdatedProperties).
     *
     * @param newUpdatedProperties The flags representing the properties to be updated
     * or @c WindowProperty::None if none should be updated.
     *
     * @since BlackBerry 10.0.0
     */
    void updatedPropertiesChanged(bb::cascades::WindowProperty::Types newUpdatedProperties);
    
    /*!
     * @brief Emitted when the @c #keyInputForwardingEnabled property changes
     *
     * @param keyInputForwardingEnabled If @c true, key input events are to be 
     * forwarded to the bound Screen window. If @c false, @c %ForeignWindowControl 
     * should receive key input from Cascades.
     *
     * @since BlackBerry 10.0.0
     */
    void keyInputForwardingEnabledChanged(bool keyInputForwardingEnabled);

    /*!
     * @brief Emitted when the @c #forwardedInputTypes property changes.
     *
     * @param inputTypes The values that will be forwarded to the bound screen
     * window
     *
     * @since BlackBerry 10.3.1
     * @see bb::cascades::InputType
     */
	Q_REVISION(4)
    void forwardedInputTypesChanged(int inputTypes);

    /*!
     * @brief Emitted when either the position or the dimensions of the @c %ForeignWindowControl changes.
     *
     * This signal can be used for cases where you need to respond to layout and animation
     * system changes in the position and size of the @c %ForeignWindowControl. You can also
     * use this signal to update the content displayed by the Screen window, or even for positioning
     * and resizing the Screen window to match the @c %ForeignWindowControl on the screen, in case 
     * automatic updating of the window properties is not desired.
     *
     * The signal is be emitted irrespective of whether the control is
     * bound to a Screen window or not.
     *
     * @param frame A @c QRectF object representing the control frame in parent window's
     * coordinate system.
     *
     * @since BlackBerry 10.0.0
     */
    void controlFrameChanged(const QRectF & frame);

protected:
    /*! @cond PRIVATE */
    Q_INVOKABLE void bindToWindow(const QVariant &windowHandle,
                                  const QString &windowGroup,
                                  const QString &windowId);
    /*! @endcond */

private:
    /*! @cond PRIVATE */


    QVariant windowHandleQml() const;
    void setWindowHandleQml(const QVariant & handle);

    Q_DECLARE_PRIVATE(ForeignWindowControl)
    Q_DISABLE_COPY(ForeignWindowControl)
    
    typedef ForeignWindowControl ThisClass;
    typedef Control BaseClass;
    /*! @endcond */

public:
    /*!
     * @brief A builder template for constructing a @c %ForeignWindowControl.
     *
     * See @c ForeignWindowControl::create() for getting a concrete Builder for
     * constructing a @c %ForeignWindowControl.
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>
    class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
    {
    protected:
        /*! @cond PRIVATE */
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        /*! @endcond */
    public:

        /*!
         * @copydoc bb::cascades::ForeignWindowControl::setWindowId(const QString &windowId)
         */
        BuilderType& windowId(const QString& windowId) {
            this->instance().setWindowId(windowId);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::ForeignWindowControl::setWindowGroup(const QString&)
         */
        BuilderType& windowGroup(const QString& windowGroup) {
            this->instance().setWindowGroup(windowGroup);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::ForeignWindowControl::setWindowHandle(screen_window_t)
         */
        BuilderType& windowHandle(screen_window_t handle) {
            this->instance().setWindowHandle(handle);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::ForeignWindowControl::setUpdatedProperties(bb::cascades::WindowProperty::Types)
         */
        BuilderType& updatedProperties(bb::cascades::WindowProperty::Types updatedProperties) {
            this->instance().setUpdatedProperties(updatedProperties);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::ForeignWindowControl::setKeyInputForwardingEnabled(bool)
         */
        BuilderType& keyInputForwardingEnabled(bool keyInputForwardingEnabled) {
            this->instance().setKeyInputForwardingEnabled(keyInputForwardingEnabled);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::ForeignWindowControl::setForwardedInputTypes(int)
         */
        BuilderType& forwardedInputTypes(int inputTypes) {
            this->instance().setForwardedInputTypes(inputTypes);
            return this->builder();
        }

    };

    /*!
     * @brief A concrete builder class used to construct a foreign window control.
     *
     * See @c ForeignWindowControl::create() for more information about using the builder.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, ForeignWindowControl>
    {
     public:
        /*! @cond PRIVATE */
        Builder() : TBuilder<Builder, ForeignWindowControl>(new ForeignWindowControl()) {}
        /*! @endcond */
     };

    /*!
     * @brief Constructs a builder used to construct a @c %ForeignWindowControl.
     *
     * @code
     * ForeignWindowControl *pForeignWindow = ForeignWindowControl::create()
     *     .windowId("MyWindow")
     *     .updatedProperties(WindowProperty::Size | WindowProperty::Position);
     * @endcode
     *
     * @return A builder used to construct a @c %ForeignWindowControl.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create()
    {
        return Builder();
    }
};

}
}

QML_DECLARE_TYPE(bb::cascades::ForeignWindowControl)

#endif

/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_orientationsupport_h
#define cascades_orientationsupport_h

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

#include <QtCore/QScopedPointer>

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/core/uiorientation.h>
#include <bb/cascades/core/supporteddisplayorientation.h>
#include <bb/cascades/core/displaydirection.h>

namespace bb {
    namespace cascades {

    class OrientationSupportPrivate;

    /*! 
     * @brief Provides support for display and UI orientation changes.
     * 
     * @details Using this class you can specify the supported display orientations, force display
     * orientation changes, make changes in response to device orientation changes, and track
     * a device's display direction.
     * 
     * @c %OrientationSupport includes the following properties:
     *
     * - @c supportedDisplayOrientation: Specifies the display orientations that the application supports
     *   or forces a particular orientation (if the current orientation doesn't match the specified orientation). 
     *   This property restricts the values that @c orientation and @c displayDirection properties can have.
     *   The property is initialized based on the Orientation property set in the application manifest
     *   (see below for details). Note: This property is read only for applications launched as cards,
     *   and property value is initialized to @c SupportedDisplayOrientation::All since parent application
     *   controls the orientation.
     * - @c orientation: A read-only property that specifies the current orientation of the UI: either
     *   @c UIOrientation::Portrait or @c UIOrientation::Landscape.
     *   The application can listen to changes to this property in order to respond to orientation 
     *   changes, if specific actions must be performed when the orientation changes (for example, changing 
     *   the contents of the scene when the orientation changes from landscape to portrait).
     *   The application has the opportunity to perform actions both before and after the orientation change occurs.
     * - @c displayDirection: A read-only property that represents the current @c DisplayDirection.
     *   The display direction is the angle between device's natural orientation (with BlackBerry logo pointing up)
     *   and the device's current direction. The natural display direction is represented by
     *   DisplayDirection::North (0 degrees).
     *   The value of this property may change even if value of @c orientation doesn't. For example if the
     *   device is rotated 180 degrees, in this case orientation doesn't not change but direction does, to
     *   reflect where the top of the device is pointing.
     * 
     * <h2>Setting the orientation</h2>
     *
     * You can set the orientation properties for an app on the %Application tab in the bar-descriptor.xml file.
     * The value of the %Orientation property is used to initialize the @c supportedDisplayOrientation property when the app starts.
     * This value defines the initial orientation and direction the application
     * will be started in, as well as whether the application reorients itself as the user physically
     * rotates the device.
     *
     * Applications that are intended to respond to a physical rotation must ensure that they have
     * the correct value for the @c %Orientation property in the bar-descriptor.xml file for the app.
     * 
     * <h3>Portrait and landscape</h3>
     * If the application is designed to reorient for both @c UIOrientation::Portrait and @c UIOrientation::Landscape,
     * the value should be set to @c "Auto-orient". Using this setting, the application will
     * be initialized to match the current device orientation when it's started, and will continue
     * to follow the device orientation as user rotates the device.
     * The @c supportedDisplayOrientation property will be initialized to @c SupportedDisplayOrientation::All on
     * application start up.
     *
     * <h3>Portrait only</h3>
     * If the application is designed to support only @c UIOrientation::Portrait, the value should be set to @c "Portrait". This
     * setting is often used in applications that feature long, vertical lists.
     * Using this setting, the application will be initialized in the @c UIOrientation::Portrait orientation and will only follow device
     * rotations if they correspond to the @c UIOrientation::Portrait orientation.
     * The @c supportedDisplayOrientation property will be initialized to @c SupportedDisplayOrientation::DisplayPortrait on
     * application start up.
     *
     * <h3>Landscape only</h3>
     * If the application is designed to support only @c UIOrientation::Landscape, the value should be set to @c "Landscape". This
     * setting is often used in games that require a wide screen.
     * Using this setting, the application will be initialized in the @c UIOrientation::Landscape orientation and will only follow
     * device rotations if they correspond to the @c UIOrientation::Landscape orientation.
     * The @c supportedDisplayOrientation property will be initialized to @c SupportedDisplayOrientation::DisplayLandscape on
     * application start up.
     *
     * <h3>Default</h3>
     * If the application is designed to only support the natural device orientation (for example, portrait for
     * a phone or landscape for a tablet) the value should be left as @c "Default". Using the default setting means that
     * the application may start in different orientations on different devices.
     * The @c supportedDisplayOrientation property will be initialized to the value corresponding to
     * the native display orientation for the device (either @c SupportedDisplayOrientation::DisplayPortrait
     * or @c SupportedDisplayOrientation::DisplayLandscape) on application start up.
     * 
     * <h2>Programmatically setting the orientation</h2>
     *
     * Irrespective of setting the @c %Orientation in the application's bar-descriptor, applications can programmatically request a
     * specific orientation (@c SupportedDisplayOrientation::DisplayPortrait, 
     * @c SupportedDisplayOrientation::DisplayLandscape or @c SupportedDisplayOrientation::DeviceNorth), 
     * or direction (@c DisplayDirection::East, @c DisplayDirection::West, @c DisplayDirection::North 
     * or @c DisplayDirection::South), or lock the current orientation
     * (@c SuportedDisplayOrientation::CurrentLocked).
     *
     * @note Because of a current platform limitation, if the @c Orientation value in the bar-descriptor is set to anything
     * other than @c "Auto-orient", programmatically setting the @c supportedDisplayOrientation to
     * @c SupportedDisplayOrientation::All will result in the device only responding to rotations that
     * don't result in a change from portrait to landscape, or vice versa. In these cases, the application
     * is only notified of 180 degree rotations. If the application needs to respond to all device
     * rotations, make sure to set the @c Orientation property to @c "Auto-orient", and if required, restrict
     * the rotations programmatically using the @c supportedDisplayOrientation property.
     *
     * <h2>Orientation handling</h2>
     * 
     * When the orientation of the device (or the @c supportedDisplayOrientation property) changes, there are
     * a series of property changes and emitted signals that occur. In order to create the best user experience,
     * it's important to understand these changes so that you can respond to them promptly and appropriately.
     *
     * - When the @c supportedDisplayOrientation property changes, the @c supportedDisplayOrientationChanged
     *   signal is emitted (if changed by the application). This step only occurs when the application changes
     *   the @c supportedDisplayOrientation property. This signal is not emitted if the orientation changes
     *   in response to the user physically rotating the device.
     * - When the @c displayDirection property is about to change in response to rotation,
     *   the displayDirectionAboutToChange() signal is emitted.
     *   This signal is emitted even if it is a 180 degree rotation (no orientation change).
     *   The signal is emitted before the actual UI rotation takes place, so the application has a
     *   chance to update the UI before the rotation begins.
     *   This signal is also the last chance the application has to opt out of an orientation change by setting
     *   the @c supportedDisplayOrientation property to a value that's incompatible with the upcoming orientation
     *   change (for example, @c SupportedDisplayOrientation::CurrentLocked).
     * - When the @c displayDirection property changes, the @c displayDirectionChanged signal is emitted.
     *   At this moment, the orientation change is imminent. From this point on, updates to the scene will be visible
     *   by the user only after the rotation occurs.
     * - When an orientation change is about to happen (in other words, a rotation that is not 180 degrees), 
     *   the @c orientationAboutToChange signal is emitted.
     *   At this point, the application can update the UI to fit the new orientation. After this signal is handled, the
     *   actual visual rotation occurs. At the end of the rotation effect, the new scene that is set during this
     *   signal is shown. Most applications should listen for this signal, as it's usually the best opportunity to set up the
     *   scene for the new orientation.
     * - After an orientation change occurs (not a 180 degree rotation), the @c orientation
     *   property changes, and the @c orientationChanged signal is emitted. At this point, the application
     *   can make additional (usually more significant, or time consuming) changes to the scene in the new orientation.
     * - At the end of a rotation or orientation change, the rotationCompleted() signal is emitted. It is the last signal emitted
     *   after any rotation occurs (meaning either direction and/or orientation has changed).
     *   Applications can use this signal to perform activities that need to happen after either
     *   the direction or the orientation change has completed.
     *
     * <h3>Orientation handling for square displays</h3>
     *
     * If the width and height of the device's display are equal (i.e. the display is square) the relationship between 
     * the @c supportedDisplayOrientation and @c orientation behaves as follows.
     *
     * - SupportedDisplayOrientation::DisplayLandscape becomes UIOrientation::Landscape
     *   (no further changes to the display rotation)
     *
     * - SupportedDisplayOrientation::DisplayPortrait becomes UIOrientation::Portrait
     *   (no further changes to the display rotation)
     *
     * - SupportedDisplayOrientation::All becomes whichever orientation is current, the default being
     *   UIOrientation::Portrait (no further changes to the display rotation)
     * 
     * - SupportedDisplayOrientation::CurrentLocked becomes whichever orientation is current, the default
     *   being UIOrientation::Portrait (no further changes to the display rotation)
     *
     * - SupportedDisplayOrientation::DeviceNorth becomes UIOrientation::Portrait (no further changes
     *   to display orientation
*     
     * <h3>Orientation handling with Cards</h3>
     *
     * For invocation cards that are invoked by an application,
     * the @c supportedDisplayOrientation property is read-only and automatically
     * defaults to @c SupportedDisplayOrientation::All. This is because the parent application is always in charge
     * of how orientation changes are handled. Card applications must still be ready to respond to orientation
     * changes though. All orientation-related signals will be fired just like they are for non-Card applications.
     *
     * <h2>Examples</h2>
     *
     * @warning @c OrientationSupport::instance() must be handled on the application thread or a runtime error will occur.
     *
     * <h3>C++</h3>
     * The following sample demonstrates how to initiate and respond to orientation changes
     * from C++. The code below assumes that @c OrientationTest has @c clicked(), @c onOrientationAboutToChange(),
     * and @c onOrientationChanged() slots.
     *
     * This example also assumes that application has the Orientation property set to @c "Auto-orient" on the %Application
     * tab of the bar-descriptor.xml file.
     *
     * @code
     * OrientationTest()
     * {
     *     Button *button = Button::create().text("Toggle Orientation");
     *     QObject::connect(button, SIGNAL(clicked()), this, SLOT(clicked()));
     * 
     *     m_labelUI = Label::create();
     * 
     *     QObject::connect(
     *         OrientationSupport::instance(), 
     *         SIGNAL(displayDirectionAboutToChange(bb::cascades::DisplayDirection::Type,
     *                                              bb::cascades::UIOrientation::Type)),
     *         this, 
     *         SLOT(onDisplayDirectionAboutToChange(bb::cascades::DisplayDirection::Type,
     *                                              bb::cascades::UIOrientation::Type)));
     * 
     *     QObject::connect(
     *         OrientationSupport::instance(), 
     *         SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)),
     *         this, 
     *         SLOT(onOrientationAboutToChange(bb::cascades::UIOrientation::Type)));
     * 
     *     // ... add controls to a container, set scene etc
     * }
     * 
     * void OrientationTest::clicked()
     * {
     *     OrientationSupport *support = OrientationSupport::instance();
     *     if (support->orientation() == UIOrientation::Portrait) {
     *         support->setSupportedDisplayOrientation(
     *                 SupportedDisplayOrientation::DisplayLandscape);
     *     } else {
     *         support->setSupportedDisplayOrientation(
     *                 SupportedDisplayOrientation::DisplayPortrait);
     *     }
     * }
     * 
     * void OrientationTest::onDisplayDirectionAboutToChange(
     *         DisplayDirection::Type direction,
     *         UIOrientation::Type orientation)
     * {
     *     // The label will have the text during orientation transition effect.
     *     m_labelUI->setText("Rotating, Weee!");
     * }
     *
     * void OrientationTest::onOrientationAboutToChange(UIOrientation::Type orientation)
     * {
     *     // The label will have this text once the orientation transition is complete.
     *     m_labelUI->setText(orientation == UIOrientation::Landscape ?
     *         "Orientation: Landscape!" : "Orientation: Portrait!");
     * }
     * 
     * @endcode
     *
     * <h3>QML</h3>
     * Here's how to control and respond to orientation changes in QML.
     * This example assumes that the application has the Orientation property set to @c "Auto-orient" in
     * the %Application tab of the bar-descriptor.xml file.
     *
     * @code
     * Container {
     *     Button {
     *         text: "Change Orientation"
     *         onClicked: {
     *             if (OrientationSupport.orientation == UIOrientation.Portrait) {
     *                 OrientationSupport.supportedDisplayOrientation =
     *                     SupportedDisplayOrientation.DisplayLandscape;
     *             } else {
     *                 OrientationSupport.supportedDisplayOrientation =
     *                     SupportedDisplayOrientation.DisplayPortrait;
     *             }
     *         }
     *     }
     *     Label {
     *         id: label
     *         text: "Current UI Orientation: " + (handler.orientation ==
     *                 UIOrientation.Landscape ? "Landscape" : "Portrait")
     *     }
     *     attachedObjects: [
     *         OrientationHandler {
     *             id: handler
     *             onDisplayDirectionAboutToChange: {
     *                 // Set UI to be shown during rotation effect.
     *                 label.text = "Rotating, Weeee!"
     *             }
     *             onOrientationAboutToChange: {
     *                 // Setup the scene for the new orientation.
     *                 if (orientation == UIOrientation.Portrait) {
     *                     // Make some UI changes related to portrait.
     *                 } else if (orientation == UIOrientation.Landscape) {
     *                     // Make some UI changes related to landscape.
     *                 }
     *                 if (displayDirection == DisplayDirection.North) {
     *                     // Do something specific to this device display direction.
     *                 }
     *             }
     *             onOrientationChanged: {
     *                 // Any additional changes to be performed after the orientation
     *                 // change has occurred.
     *             }
     *             onDisplayDirectionChanged: {
     *                 // Can perform actions based on the direction of the display.
     *             }
     *             onRotationCompleted: {
     *                 // Can perform actions after either direction or orientation
     *                 // change has been completed.
     *                 label.text =
     *                     "Current UI Orientation: " + (handler.orientation ==
     *                          UIOrientation.Landscape ? "Landscape" : "Portrait")
     *             }
     *         }        
     *     ]
     * }
     * @endcode
     *
     * @xmlonly
     * <qml>
     *     <class contextProperty="OrientationSupport"/>
     * </qml>
     * @endxmlonly
     *
     * @xmlonly
     *     <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT OrientationSupport : public QObject
    {
    private:
        Q_OBJECT
    /*!
     * @brief Display orientations supported by the application.
     *
     * @details The application can use this property to declare which display orientation it supports, as well
     * as control the current orientation.
     *
     * If the value of this property doesn't match the current orientation, the orientation 
     * will be changed to reflect the supported display orientation.
     *
     * If the current supported display orientation doesn't conflict with UI orientation
     * (like if device was rotated from one landscape orientation to another landscape
     * orientation, 180 degrees) the orientation property will not be changed.
     *
     * Under certain conditions (such as orientation change is already in progress or
     * if application is not active), the setting of the property may fail in which case the
     * property will remain unchanged. 
     *
     * The initialized orientation is based on the @c Orientation value set in the application's
     * bar-descriptor.xml file, unless the application is launched as a @c Card.
     *  
     * @note For applications launched as cards this property is read only, and the property value
     * defaults to @c SupportedDisplayOrientation::All since the parent application controls the orientation.
     *
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY(bb::cascades::SupportedDisplayOrientation::Type supportedDisplayOrientation 
                READ supportedDisplayOrientation 
                WRITE setSupportedDisplayOrientation 
                RESET resetSupportedDisplayOrientation
                NOTIFY supportedDisplayOrientationChanged FINAL)

    /*!
     * @brief The orientation of the user interface.
     *
     * @details This is a read-only property which reflects current display orientation. Its value depends on
     * the current device direction and the value of the @c supportedDisplayOrientation property.
     * 
     * When this property changes, the @c orientationAboutToChange() and orientationChanged() signals
     * are emitted. When @c orientationAboutToChange() is emitted, the app can update the UI for the new orientation.
     * When @c orientationChanged() is emitted, the application can update the UI again if needed (in case the previous
     * UI change was intermediate).
     *
     * The default value depends on devices' physical display orientation and the value of
     * @c supportedDisplayOrientation property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::UIOrientation::Type orientation
               READ orientation
               NOTIFY orientationChanged FINAL)

    /*!
     * @brief The direction of the display as indicated by the direction that the top of the device display is pointing.
     * 
     * @details This is a read-only property which reflects the current display direction. Its value depends on
     * current device direction and the value of the @c supportedDisplayOrientation property. The
     * direction will only reflect supported display orientations.
     *
     * This property is useful if application needs to know the exact direction the display
     * is pointing to as opposed to just whether it is in landscape or portrait orientation.
     *
     * The value of this property changes before the application receives the
     * @c orientationAboutToChange() signal so the new value will be returned if this property is read
     * when the @c orientationAboutToChange() signal is handled.
     * 
     * A @c displayDirectionAboutToChange() signal is emitted before this property changes.
     * When the orientation changes,  it emits the @c displayDirectionChanged() signal.
     * 
     * The default value depends on the device's physical display direction and the value of
     * the @c supportedDisplayOrientation property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::DisplayDirection::Type displayDirection
               READ displayDirection
               NOTIFY displayDirectionChanged FINAL)

    Q_SIGNALS:

    /*!    
     * @brief Emitted when supported display orientation changes.
     * 
     * @param displayOrientation The new supported device orientation.
     *
     * @since BlackBerry 10.0.0
     */
    void supportedDisplayOrientationChanged(bb::cascades::SupportedDisplayOrientation::Type displayOrientation);

    /*!    
     * @brief Emitted when the UI orientation is about to change in response to a device rotation or a change in the supported
     * device orientation.
     * 
     * @param orientation The new UI orientation.
     *
     * @since BlackBerry 10.0.0
     */
    void orientationAboutToChange(bb::cascades::UIOrientation::Type orientation);

    /*!    
     * @brief Emitted when the UI orientation is changed in response to a device rotation or a change in the supported
     * device orientation.
     * 
     * @details This signal will not be emitted on 180 degree direction changes since
     * the actual orientation does not change in this case. 
     *
     * @param orientation The new UI orientation.
     *
     * @since BlackBerry 10.0.0
     */
    void orientationChanged(bb::cascades::UIOrientation::Type orientation);

    /*!    
     * @brief Emitted when the display direction is changed in response to a device rotation or a change 
     * in the supported device orientation.
     *
     * @param displayDirection The display direction.
     *
     * @since BlackBerry 10.0.0
     */
    void displayDirectionChanged(bb::cascades::DisplayDirection::Type displayDirection);

    /*!    
     * @brief Emitted when display direction is about to change in response to a device rotation or
     * a change in the supported device orientation.
     *
     * @details The application can use this signal to perform activities before the rotation
     * occurs or to prevent the orientation change from taking place.
     *
     * For the best user experience, it's important to respond to this signal quickly
     * (within 300ms total or so for all handlers combined).
     *
     * The application can delay the orientation change (for example to make sure application's 
     * animations have completed) by pausing the current rotation and resuming it later
     * after the UI was updated.
     *
     * @note The value of @c orientation parameter might be the same as the
     * current orientation in instances that the screen is about to be rotated 180 degrees.
     *
     * This example assumes that the application has the Orientation property set to @c "Auto-orient" in
     * %Application tab of the bar-descriptor.xml file.
     *
     * @code
     * App::App() :
     *     m_pendingDirection(OrientationSupport::instance()->displayDirection())
     * {
     *    // m_label = ...
     *    // Setup the scene and so on.
     * }
     *
     * // A slot connected to OrientationSupport::displayDirectionAboutToChange() signal
     * void App::onDisplayDirectionAboutToChange(DisplayDirection::Type displayDirection,
     *                                           UIOrientation::Type orientation)
     * {
     *     // We only want to delay the rotation when user initially rotates the device.
     *     if (m_pendingDirection != displayDirection) {
     *         // User rotated the device, let's pause the rotation; hide the label
     *         // And then resume rotaton.
     *
     *         m_pendingDirection = displayDirection;
     *
     *         OrientationSupport::instance()->
     *             setSupportedDisplayOrientation(
     *                     SupportedDisplayOrientation::CurrentLocked);
     *
     *         // Update the UI here, for example.
     *         // Move the label off the screen during rotation.
     *         m_label->setTranslation(-100, -100);
     *     
     *         // Give animations a chance to complete before resuming rotation.
     *         // Set a timer for 200ms.
     *         QTimer::singleShot(200, this, SLOT(unlock()));
     *     }
     * }
     * // A slot invoked by the timer.
     * void App::unlock() {
     *     // Unlock orientation changes; this will cause the screen to rotate
     *     // According to device's physical orientation in space which will match
     *     // m_pendingDirection set in the onDisplayDirectionAboutToChange() slot.
     *     OrientationSupport::instance()->
     *         setSupportedDisplayOrientation(SupportedDisplayOrientation::All);
     *     // Also application can call OrientationSupport::requestDisplayDirection() to
     *     // rotate to specific direction, if needed.
     * }
     * @endcode
     *
     * The application can also prevent the orientation from occuring by changing
     * the @c supportedDisplayOrientation property when handling this signal:
     *
     * @code
     * OrientationHandler {
     *     onDisplayDirectionAboutToChange: {
     *         // Prevent orientation change from happening for certain
     *         // directions.
     *         if (displayDirection == DisplayDirection.West) {
     *             OrientationSupport.supportedDisplayOrientation =
     *                 SupportedDisplayOrientation.CurrentLocked
     *         }
     *     }
     * }
     * @endcode
     *
     * @param displayDirection The display direction.
     * @param orientation The new UI orientation.
     *
     * @since BlackBerry 10.0.0
     */
    void displayDirectionAboutToChange(bb::cascades::DisplayDirection::Type displayDirection,
                                       bb::cascades::UIOrientation::Type orientation);

    /*!
     * @brief Emitted when all orientation change-related activities have been completed.
     *
     * @details This signal is emitted at the end of sequence of events caused by direction or
     * orientation changes (unlike @c orientationChanged() which is only emitted when orientation
     * has changed, which is not the case when device is rotated 180 degrees).
     *
     * @since BlackBerry 10.0.0
     */
    void rotationCompleted();

    public:
    
    /*!    
     * @brief Returns an instance of @c OrientationSupport associated with this application.
     *
     * The returned instance is owned by the application and ownership is not transferred to the caller.
     *
     * @warning This method must be called on the application thread or a runtime error will occur.
     *
     * @return The @c OrientationSupport instance.
     *
     * @since BlackBerry 10.0.0
     */
    static bb::cascades::OrientationSupport *instance();

    /*!
     * @brief Returns the current value of @c supportedDisplayOrientation property.
     * 
     * @return Returns currently set supported orientation.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::SupportedDisplayOrientation::Type supportedDisplayOrientation() const;

    /*!
     * @brief Sets the new supported display orientation.
     *
     * @details If current UI orientation doesn't match the new display orientation, orientation 
     * will be changed to satisfy the new supported display orientation.
     *
     * Under certain conditions (such as the orientation change is already in progress, or
     * the application is not active), the setting of this property may fail, in which case, the
     * property will remain unchanged.
     *
     * @note Since the @c supportedDisplayOrientation property is read-only for applications
     * launched as Cards, calling this method for such applications has no effect.
     *
     * @param displayOrientation new supported display orientation.
     *
     * @since BlackBerry 10.0.0
     */
    void setSupportedDisplayOrientation(bb::cascades::SupportedDisplayOrientation::Type displayOrientation);

    /*!
     * @brief Sets the supported display orientation to the default value specified in applications' bar-descriptor.xml file.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetSupportedDisplayOrientation();

    /*!
     * @brief Returns the current value of the @c orientation property.
     * 
     * @return The current UI orientation.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::UIOrientation::Type orientation() const;

    /*!
     * @brief Returns the current value of @c displayDirection property.
     * 
     * @return The current display direction.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::DisplayDirection::Type displayDirection() const;

    /*!
     * @brief Requests a display direction change to the specified @c displayDirection.
     *
     * @details The display direction change will only occur if the specified @c displayDirection
     * does not conflict with the current @c supportedDisplayOrientation.
     *
     * @warning Do not use the return value of this function. It is DEPRECATED and might be removed in
     * the next major release. Instead check if the property @c displayDirection changed as a result
     * of this call.
     *
     * In case the request succeeded, the display direction and orientation will change (the latter 
     * only if direction change is not 180 degrees) sequence will be initiated.
     *
     * The request may fail if the direction is not supported on the device, if the display direction 
     * change was attempted during an orientation change sequence, if the application is a Card, or 
     * if application is not active.
     *
     * This method is invokable from QML.
     *
     * This example assumes that application has the Orientation property set to @c "Auto-orient" in
     * the Application tab of the bar-descriptor.xml file.
     *
     * @code
     * import bb.cascades 1.0
     * 
     * Page {
     *     Container {
     *         Button {
     *             text: "Rotate To Top"
     *             onClicked: {
     *                 OrientationSupport.requestDisplayDirection(DisplayDirection.North);
     *             }
     *         }
     *         Button {
     *             text: "Rotate To Left"
     *             onClicked: {
     *                 OrientationSupport.requestDisplayDirection(DisplayDirection.West);
     *             }
     *         }
     *         Button {
     *             text: "Rotate To Right"
     *             onClicked: {
     *                 OrientationSupport.requestDisplayDirection(DisplayDirection.East);
     *             }
     *         }
     *     }
     * }
     * @endcode
     *
     * @return Do not use the return value, it is DEPRECATED! Instead check if the property
     * @c displayDirection changed as a result of this call.
     *
     * @since BlackBerry 10.0.0
     */
    bool requestDisplayDirection(bb::cascades::DisplayDirection::Type displayDirection);

    /*! @cond PRIVATE */
    virtual ~OrientationSupport();
    /*! @endcond */

    protected:
    /*!
     * @brief Requests display direction change to the specified @c displayDirection.
     *
     * The display direction change will only occur if specified @c displayDirection
     * does not conflict with current @c supportedDisplayOrientation.
     *
     * @warning Do not use the return value of this function. It is DEPRECATED and might be removed in
     * the next major release. Instead check if the property @c displayDirection changed as a result
     * of this call.
     *
     * In case the request succeeded, the display direction and orientation will change (the latter 
     * only if direction change is not 180 degrees) sequence will be initiated.
     *
     * The request may fail if the direction is not supported on the device, if the display direction 
     * change was attempted during an orientation change sequence, if the application is a Card, or 
     * if application is not active.
     * 
     * This method is invokable from QML.
     *
     * This example assumes that application has Orientation property set to @c "Auto-orient" in
     * Application tab of the manifest editor.
     *
     * @code
     * import bb.cascades 1.0
     * 
     * Page {
     *     Container {
     *         Button {
     *             text: "Rotate To Top"
     *             onClicked: {
     *                 OrientationSupport.requestDisplayDirection(DisplayDirection.North);
     *             }
     *         }
     *         Button {
     *             text: "Rotate To Left"
     *             onClicked: {
     *                 OrientationSupport.requestDisplayDirection(DisplayDirection.West);
     *             }
     *         }
     *         Button {
     *             text: "Rotate To Right"
     *             onClicked: {
     *                 OrientationSupport.requestDisplayDirection(DisplayDirection.East);
     *             }
     *         }
     *     }
     * }
     * @endcode
     *
     * @return Do not use the return value, it is DEPRECATED! Instead check if the property
     * @c displayDirection changed as a result of this call.
     *
     * @xmlonly
     * <qml>
     *     <param name="displayDirection" type="bb::cascades::DisplayDirection::Type"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE bool requestDisplayDirection(int displayDirection);

    private:
        /*! @cond PRIVATE */
        QScopedPointer<OrientationSupportPrivate> d_ptr;
        Q_DECLARE_PRIVATE(OrientationSupport)
        Q_DISABLE_COPY(OrientationSupport)

        OrientationSupport();
        virtual void connectNotify(const char* signal);
        /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::OrientationSupport)

#endif /* cascades_orientationsupport_h */


/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_DISPLAYINFO_HPP
#define BB_DEVICE_DISPLAYINFO_HPP

#include <bb/device/DisplayAspectType>
#include <bb/device/DisplayTechnology>
#include <bb/device/Global>

#include <QObject>
#include <QScopedPointer>
#include <QSize>
#include <QSizeF>
#include <QVariant>

namespace bb
{
namespace device
{
class DisplayInfoPrivate;

/*!
 * @headerfile DisplayInfo.hpp <bb/device/DisplayInfo>
 *
 *
 * @brief The @c DisplayInfo API enables applications to determine properties of the
 *        built-in physical displays, and any externally connected physical displays.
 *        These properties include the display size and resolution, the ID and name,
 *        and the aspect and attached state.
 *
 * @details Two physical displays are explicitly recognized: A primary, built-in
 *          display and a secondary, externally connected display.
 *          Other internal or external displays that may exist are also supported by
 *          this API but only if their screen display IDs are known. An external
 *          display can be thought of as a display port on the device. The port may
 *          or may not have a physical display attached to it at any given time. The
 *          @c DisplayInfo class not only facilitates accessing display parameters
 *          but also enables monitoring the display state, such as when a physical
 *          display is attached or disconnected (@c attachedChanged()).
 *
 * @note A @c DisplayInfo instance should not be moved to another thread, and must be
 *       deleted on the thread in which it was created.
 *
 * If only the primary display is of interest, instantiate a @c DisplayInfo object
 * and query it for parameters:
 * @code
    bb::device::DisplayInfo display;
    qDebug() << "display id is " << display.displayId();
    qDebug() << "display name is " << display.displayName();
    qDebug() << "display size is " << display.pixelSize().width() << ", "
             << display.pixelSize().height();
 * @endcode
 *
 * Example of how to use DisplayInfo in QML (since BlackBerry 10.3.0):
 *
 * @code
 *  import bb.cascades 1.3
 *  import bb.device 1.3
 *  ...
 *  Container {
 *     preferredHeight: displayInfo.pixelSize.height
 *     preferredWidth: displayInfo.pixelSize.width
 *  }
 *  ...
 *  attachedObjects: [
 *      DisplayInfo {
 *          id: displayInfo
 *      }
 *  ]
 * @endcode
 *
 * @note If you are using QML, you can create a @c DisplayInfo instance only for the primary display.
 *
 * The following example shows how to monitor the secondary display:
 * @code
    int secondaryDisplayId = bb::device::DisplayInfo::secondaryDisplayId();
    qDebug() << "secondary display Id is " << secondaryDisplayId;

    // Construct the DisplayInfo object for the secondary display, and set its parent
    // to some "mainApp" so it will take care of the destruction.
    bb::device::DisplayInfo* secondaryDisplayInfo = new bb::device::DisplayInfo(secondaryDisplayId, &mainApp);

    // The display parameters are interesting if a physical display is attached.
    if ( secondaryDisplayInfo->isAttached() ) {
        qDebug() << "secondary display name is "
                 << secondaryDisplayInfo->displayName();
        qDebug() << "secondary display size is "
                 << secondaryDisplayInfo->pixelSize().width()
                 << ", " << secondaryDisplayInfo->pixelSize().height();
    }

    // Connect the "mainApp's" slot to the secondary display's attachedChanged()
    // signal in order to be notified when the attached state changes.
    QObject::connect(secondaryDisplayInfo, SIGNAL(attachedChanged(bool)),
                     &mainApp, SLOT(secondaryDisplayAttachedChanged(bool)));
 * @endcode
 *
 * @note There is a slight performance impact when a @c DisplayInfo instance is
 * created, thus creating multiple instances of the class is not recommended.
 * 
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT DisplayInfo : public QObject
{
    Q_OBJECT

    /*!
     * @brief The id associated with this @c DisplayInfo instance, usually either
     *        @c primaryDisplayId(), or @c secondaryDisplayId().
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( int displayId READ displayId CONSTANT FINAL );

    /*!
     * @brief The name of the display, as defined by the QNX Screen and Windowing
     *        API.
     *
     * @details If this @c DisplayInfo instance represents an external display that
     *          has been disconnected, the name is blank.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString displayName READ displayName CONSTANT FINAL );

    /*!
     * @brief The size (width and height) of the display measured in pixels.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QSize pixelSize READ pixelSize NOTIFY pixelSizeChanged FINAL );

    /*!
     * @brief The horizontal and vertical resolution of the display measured in mm.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QSizeF physicalSize READ physicalSize CONSTANT FINAL );

    /*!
     * @brief The horizontal and vertical resolution of the display measured in
     *        pixels per meter.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QSizeF resolution READ resolution NOTIFY pixelSizeChanged FINAL );

    /*!
     * @brief The aspect of the display describes the shape of the rectangular region
     *        that defines the display area.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::device::DisplayAspectType::Type aspectType READ aspectType CONSTANT FINAL );

    /*!
     * @brief Indicates if there is a display physically attached to the device for
     *        this @c DisplayInfo instance.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bool attached READ isAttached NOTIFY attachedChanged FINAL );

    /*!
     * @brief Indicates if this @c DisplayInfo supports a physical display that can
     *        be attached and disconnected.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bool detachable READ isDetachable CONSTANT FINAL );

    /*!
     * @brief The type of technology this display is using.
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY( bb::device::DisplayTechnology::Type displayTechnology READ displayTechnology CONSTANT FINAL REVISION 1 );

    /*!
     * @brief Indicates if this display is connected via a wireless protocol or not.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool wireless READ isWireless CONSTANT FINAL REVISION 2);

public:
    /*!
     * @brief Creates a @c DisplayInfo object which represents the primary display.
     *
     * @param parent If not 0, the supplied parent is responsible for deleting this
     *               instance.
     *
     *
     * @since BlackBerry 10.0.0
     */
    explicit DisplayInfo( QObject * parent = 0 );

    /*!
     * @brief Creates a @c DisplayInfo object which represents the display that was
     *        specified by its screen display ID.
     *
     * @details This corresponds to the display ID described in the QNX Screen and
     *          Windowing API. The screen display IDs of the primary and secondary
     *          displays can be determined from the static methods
     *          @c primaryDisplayId() and @c secondaryDisplayId() respectively. Other
     *          displays that may exist are also supported if their screen display
     *          IDs are known.
     *
     * @param displayId The screen display ID of the display.
     * @param parent The @c QObject to be set as the parent of this instance. If
     *               @c parent is 0, then no parent is set.
     *
     * @since BlackBerry 10.0.0
     */
    explicit DisplayInfo( int displayId, QObject * parent = 0 );

    /*!
     * @brief Destroys a @c DisplayInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~DisplayInfo();

    /*!
     * @brief Provides the display ID for the primary display.
     *
     * @details The primary display is the device's internal display. If there is
     *          more than one internal display, the primary display is arbitrarily,
     *          but consistently, determined.
     *
     * @return Returns the ID of the primary display if successful, and -1 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    static int primaryDisplayId();

    /*!
     * @brief Provides the display ID for the secondary display.
     *
     * @details The secondary display is a display that is external to the device,
     *          and connected by a fixed port that exists on the device. If there is
     *          more than one external display, then the secondary display is
     *          arbitrarily, but consistently, determined.
     *
     * @return Returns the ID of the secondary display if successful, and -1
     *         otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    static int secondaryDisplayId();

    /*!
     * @brief Provides the ID of the display represented by the @c DisplayInfo
     *        instance.
     *
     * @details This corresponds to the display ID described in the QNX Screen and
     *          Windowing API.
     *
     * @return Returns the display ID if successful, and -1 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    int displayId() const;

    /*!
     * @brief Provides the name of the display represented by the @c DisplayInfo
     *        instance.
     *
     * @details This corresponds to the display name described in the QNX Screen and
     *          Windowing API. The display name may contain identifying information
     *          such as display model and make. If an external display is not
     *          attached ( see @c isAttached() ) then the name is returned is an
     *          empty string.
     *
     * @return Returns the display name (truncated to 128 characters) if successful,
     *         but if the object is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QString displayName() const;

    /*!
     * @brief Provides the size (width and height) of the display measured in pixels.
     *
     * @details The size is always provided with respect to the display's natural
     *          orientation. For the device's internal display this is typically the
     *          orientation for which the physical buttons/trackpads, etc. and
     *          branding appear to be upright. If an external display is not attached
     *          (see @c isAttached()) then the width and height are considered to
     *          have values of 0.
     *
     *          It is possible for a display to dynamically change its pixel size, a
     *          notification of this pixel size change can be detected by connecting
     *          to the @c pixelSizeChanged() signal.
     *
     * @return Returns the @c QSize variable containing the size of the display in
     *         pixels. Returns @c QSize(0,0) if the display is not attached. If this
     *         object is invalid, then the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QSize pixelSize() const;

    /*!
     * @brief Provides the size (width and height) of the display measured in
     *        millimeters.
     *
     *        The size of the display is always provided with respect to the its
     *        natural orientation. For the device's internal display this is
     *        typically the orientation for which the physical buttons/trackpads,
     *        etc. and branding appear upright. The physical size may not be
     *        discoverable for all displays, in which case the width and height are
     *        considered to be 0.0. If an external display is not attached
     *        (see @c isAttached()) then the width and height are also considered to
     *        be 0.0.
     *
     * @return Returns a @c QSizeF variable containing the size of the display in
     *         millimeters. Returns @c QSizeF(0.0f,0.0f) if the physical size could
     *         not be determined. If this object is invalid, then the return value is
     *         undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QSizeF physicalSize() const;

    /*!
     * @brief Provides the horizontal and vertical resolution of the display measured
     *        in pixels per meter.
     *
     * @details The resolution is always provided with respect to the display's
     *          natural orientation. For the device's internal display, this is
     *          typically the orientation for which the physical buttons/trackpads,
     *          etc., and branding appear to be upright. The resolution is calculated
     *          from the ratio of the pixel size to the physical size. Note that the
     *          accuracy is limited by the physical size, which is known to the
     *          nearest millimeter. Since the physical size may not be detectable for
     *          all displays, the resolution cannot always be determined. In such
     *          cases, the horizontal and vertical resolution are considered to be
     *          0.0. If an external display is not attached (see @c isAttached()),
     *          then the horizontal and vertical resolution are also considered to be
     *          0.0.
     *
     *          It is possible for a display to dynamically change its pixel size, a
     *          notification of this pixel size change can be detected by connecting
     *          to the @c pixelSizeChanged() signal.
     *
     * @return Returns a @c QSizeF variable containing the resolution of the display
     *         in pixels per meter. Returns @c QSizeF(0.0f,0.0f) if the resolution
     *         could not be determined. If this object is invalid, then the return
     *         value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QSizeF resolution() const;

    /*!
     * @brief Provides the display's aspect with respect to the display's natural
     *        orientation.
     *
     * @details For the device's internal display, this is typically the orientation
     *          for which physical the buttons/trackpads, etc., and branding appear
     *          to be upright. A display's aspect can be
     *          @c DisplayAspectType::Landscape (for width > height),
     *          @c DisplayAspectType::Portrait (for width < height), or
     *          @c DisplayAspectType::Square (for width = height). If an external
     *          display is not attached (see @c isAttached()), then the aspect is
     *          considered to be @c DisplayAspectType::Square.
     *
     * @return Returns the display's aspect. If this object is invalid, then the
     *         return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::DisplayAspectType::Type aspectType() const;

    /*!
     * @brief Indicates if there is a display physically attached to the device for
     *        this @c DisplayInfo instance.
     *
     * @details An external display can be thought of as a display port. The port
     *          always exists but a physical display may or may not be attached. The
     *          secondary display is an external display. The signal
     *          @c attachedChanged() can be connected to monitor when a physical
     *          display is attached and disconnected.
     *
     * @return Returns the @c true if a physical display is attached to the device,
     *         and @c false otherwise. If this object is invalid, then the return
     *         value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    bool isAttached() const;

    /*!
     * @brief Indicates if this @c DisplayInfo supports a physical display that can
     *        be attached and disconnected.
     *
     * @details This defines an external display.
     *
     * @return Returns @c true if the @c DisplayInfo is detachable (hence external),
     *         and @c false otherwise. If this object is invalid, then the return
     *         value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    bool isDetachable() const;

    /*!
     * @brief Indicates if this @c DisplayInfo object is valid.
     *
     * @details To be valid, the current @c DisplayInfo object must have been given a
     *          recognized display ID in its constructor.     *
     *          A @c DisplayInfo object is invalid only if the display ID is not
     *          recognized. A @c DisplayInfo object that represents a detachable
     *          display that is not currently attached to the device is still
     *          considered to be valid but not attached.
     *
     * @return Returns @c true if this @c DisplayInfo object is valid, and @c false
     *         otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief The type of technology this display is using.
     *
     * @return One of @c bb::device::DisplayTechnology::Type.
     *
     * @since BlackBerry 10.1.0
     */
    bb::device::DisplayTechnology::Type displayTechnology() const;

    /*!
     * @brief Indicates if the current display is connected via a wireless protocol or not.
     *
     * @return @c true if the connection is wireless, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isWireless() const;

Q_SIGNALS:
    /*!
     * @brief Indicates that the attached state of a physical display has changed.
     *
     * @param attached @c true if a physical display was attached, @c false if a
     *                 physical display was not attached.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void attachedChanged(bool attached);

    /*!
     * @brief Indicates that the size in pixels of a display that is currently
     *        attached has changed.
     *
     * @param pixelSize The new size in pixels of the display.
     *
     * @ingroup Signals
     *
     * @note In QML, only the @c pixelSize.width and @c pixelSize.height values can
     *       be accessed.
     *
     * @since BlackBerry 10.0.0
     */
    void pixelSizeChanged( QSize pixelSize );

protected:
//!@cond PRIVATE
    Q_SIGNAL void pixelSizeChanged( QVariant pixelSize );
//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(DisplayInfo)
    Q_DISABLE_COPY(DisplayInfo)

    QScopedPointer<DisplayInfoPrivate> d_ptr;
//!@endcond
};

} // namespace device
} // namespace bb

#endif // BB_DEVICE_DISPLAYINFO_HPP

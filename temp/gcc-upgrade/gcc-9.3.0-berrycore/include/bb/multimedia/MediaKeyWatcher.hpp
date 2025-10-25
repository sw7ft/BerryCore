/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_MEDIAKEYWATCHER_HPP
#define BB_MULTIMEDIA_MEDIAKEYWATCHER_HPP

#include <bb/multimedia/Global>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaKey>
#include <bb/multimedia/MediaKeyNotification>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

class MediaKeyWatcherPrivate;

/*!
 * @headerfile MediaKeyWatcher.hpp <bb/multimedia/MediaKeyWatcher>
 *
 * @brief Represents a hardware media key and provides notification.
 *
 * @details If two @c %MediaKeyWatcher objects reference the
 * same @c MediaKey then the last one to connect the signal will receive the
 * notification until all the slots are disconnected from that signal.
 * A short press is defined as being less than 600ms in duration and a
 * long press is 600ms or greater in duration.
 *
 * There are two different notification types for this media key watcher.
 * @c MediaKeyNotification::Clicked is the default and results in the
 * respective press signals to be called when the hardware media key is
 * released. @c MediaKeyNotification::Threshold causes a press to be signaled
 * once the earliest connected signal threshold is reached (0ms for
 * @c shortPress() and 600ms for @c longPress()). If both @c shortPress() and
 * @c longPress() are connected, only the @c shortPress() signal will be emitted.
 *
 * When all slots are disconnected from a signal, notification is returned to
 * the last @c %MediaKeyWatcher object that is connected to the signal of the same
 * media key. Otherwise the default action from now playing is triggered. QML users
 * can use a %ComponentDefinition to dynamically allocate a %MediaKeyWatcher when
 * needed and destroy it when the button no longer needs to be watched. It is up
 * to the developer to ensure a key is only watched when needed otherwise, as is
 * the case with volume keys, core functionality could be affected for other
 * applications.
 *
 * C++ example:
 *
 * @code
       MediaKeyWatcher keyWatcher(MediaKey::VolumeUp);
       ...
       QObject::connect(&keyWatcher, SIGNAL(longPress(bb::multimedia::MediaKey::Type)), this, SLOT(onLongPress()));
       QObject::connect(&keyWatcher, SIGNAL(shortPress(bb::multimedia::MediaKey::Type)), this, SLOT(onShortPress()));
 * @endcode
 *
 * QML example:
 *
 * @code
    import bb.multimedia 1.0
    ...
    attachedObjects: [
      MediaKeyWatcher {
          id: keyWatcher
          key: MediaKey.VolumeUp

          onLongPress: {
            // do something
          }

          onShortPress: {
            // do something
          }
      }
    ]
 * @endcode
 *
 * @xmlonly
 * <qml>
 *     <class abstract="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/General"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT MediaKeyWatcher : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents any of the media button types.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::MediaKey::Type key READ key)

    /*!
     * @brief Represents a media key notification for this media key watcher.
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY(bb::multimedia::MediaKeyNotification::Type notification READ notification WRITE setNotification)

public:

    /*!
     * @brief Constructs a @c MediaKey object.
     *
     * @details Create and associates a @c MediaKey with a specific media
     * button.
     *
     * @param key The @c MediaKey::Type to watch.
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MediaKeyWatcher(bb::multimedia::MediaKey::Type key, QObject *parent = 0);

    /*!
     * @brief Constructs a @c MediaKey object.
     *
     * @details Create and associates a @c MediaKey with @c MediaKey::None.
     *
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MediaKeyWatcher(QObject *parent = 0);

    /*!
     * @brief @c %MediaKeyWatcher class destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MediaKeyWatcher();

    /*!
     * @brief Provides the @c MediaKey associated with this watcher.
     *
     * @return The media type that's providing notifications.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaKey::Type key() const;

    /*!
     * @brief Provides the @c MediaKeyNotification associated with this key
     * watcher.
     *
     * @return The media key notification type.
     *
     * @since BlackBerry 10.1.0
     */
    bb::multimedia::MediaKeyNotification::Type notification() const;

public Q_SLOTS:

    /*!
     * @brief Used to set the media key notification type.
     *
     * @details When the notification type @c MediaKeyNotification::Clicked is
     * set, the media key signals will not be emitted until the hardware key has been
     * released. For @c MediaKeyWatcher::Threshold, the media key signal will
     * be emitted as soon as the press threshold has been reached for the given
     * length. In this case, the press signal will only occur for the earliest
     * connected signal.
     *
     * @param notification The media key notification type to use.
     *
     * @since BlackBerry 10.1.0
     */
    void setNotification(bb::multimedia::MediaKeyNotification::Type notification);

Q_SIGNALS:

    /*!
     * @brief Emitted for a media key long press.
     *
     * @details This signal is emitted when the associated media button has been
     * pressed for more than 600ms.
     *
     * @param key The media key that was long pressed.
     *
     * @since BlackBerry 10.0.0
     */
    void longPress(bb::multimedia::MediaKey::Type key);

/*! @cond PRIVATE */
    /*!
     * @brief Deprecated
     *
     * @details Will signal the same time as @c longPress.
     *
     * @ingroup Signals
     */
    void mediumPress(bb::multimedia::MediaKey::Type key) BB_MULTIMEDIA_DEPRECATED;
/*! @endcond */

    /*!
     * @brief Emitted when the notification type has changed.
     *
     * @param notification The new notification type.
     *
     * @since BlackBerry 10.1.0
     */
    void notificationChanged(bb::multimedia::MediaKeyNotification::Type notification);

    /*!
     * @brief Emitted for a media key short press.
     *
     * @details This signal is emitted when the associated media button is
     * pressed for less than 600ms.
     *
     * @param key The media key that was short pressed.
     *
     * @since BlackBerry 10.1.0
     */
    void shortPress(bb::multimedia::MediaKey::Type key);

protected:
    /*! @cond PRIVATE */
    virtual void connectNotify(const char * signal);
    virtual void disconnectNotify(const char *signal);

    void setKey(bb::multimedia::MediaKey::Type key);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    MediaKeyWatcherPrivate *d_ptr;
    Q_DECLARE_PRIVATE(MediaKeyWatcher)
    Q_DISABLE_COPY(MediaKeyWatcher)
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::MediaKeyWatcher)

#endif /* BB_MULTIMEDIA_MEDIAKEYWATCHER_HPP */

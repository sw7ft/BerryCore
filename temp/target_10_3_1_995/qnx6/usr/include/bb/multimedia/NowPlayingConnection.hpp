/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_NOWPLAYINGCONNECTION_HPP
#define BB_MULTIMEDIA_NOWPLAYINGCONNECTION_HPP

#include <bb/multimedia/DeviceMode>
#include <bb/multimedia/Global>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaState>
#include <bb/multimedia/MetaData>
#include <bb/multimedia/OverlayStyle>
#include <bb/multimedia/PriorityLevel>
#include <bb/multimedia/RepeatMode>
#include <bb/multimedia/ShuffleMode>

#include <QtDeclarative/QtDeclarative>
#include <QObject>
#include <QVariantMap>

namespace bb
{
namespace multimedia
{

class NowPlayingConnectionPrivate;

/*!
 * @headerfile NowPlayingConnection.hpp <bb/multimedia/NowPlayingConnection>
 *
 *
 * @brief Provides exclusive system access to media notification areas.
 *
 * @details The @c %NowPlayingConnection class provides exclusive system access
 * to the media information area that describe the media that is currently active
 * on the device. This class also provides a means to receive media
 * control event notifications.
 *
 * A now playing example in C++:
 *
 * @code
        NowPlayingConnection np("myConnection", this);
        QVariantMap metadata;

        metadata[MetaData::Title] = "Sample Track";
        metadata[MetaData::Artist] = "Sample Artist";
        metadata[MetaData::Album] = "Sample Album";

        np->setMetaData(metadata);

        np->setIconUrl(
            QUrl("file://%1/app/native/assets/artwork.png")
            .arg(QDir::currentPath()));
 * @endcode
 *
 * The service must be acquired before playing. A service that is playing will
 * automatically revoke any other connected user.
 *
 * @code
       np->acquire();
 * @endcode
 *
 * Once the @c acquired() signal is received, it is possible to send
 * the media data:
 *
 * @code
        // Represents 2min duration in milliseconds.
        np->setDuration(120000);

        // Represents the starting position.
        np->setPosition(0);

        // Notifies of the playing media state.
        np->setMediaState(bb::multimedia::MediaState::Started);
 * @endcode
 *
 * Acquired signals can be used in calls to @c next(), @c previous(),
 * @c play(), @c pause(), and @c stop(). Upon receiving a signal, the
 * user must call the function that is most appropriate for their media.
 *
 * Once a @c revoked() signal has been received, playback of the media
 * must be stopped and all media resources must be released. For example,
 * an audio recorder that receives a @c revoked() signal must give up its
 * access to the microphone, which could allow another process to use it.
 *
 * The @c controllerActive property provides notification to indicate that
 * one or more controllers are attached to the service that is currently
 * acquired. The controllers require regular status updates to function
 * accurately. This means that even if an application is in standby mode,
 * regular status messages should continue to be sent to it.
 *
 * With no @c audioManagerHandle specified, the now playing service will
 * automatically call @c play() when no longer preempted. If an
 * @c audioManagerHandle is specified, the now playing service will only call
 * @c play() if the audio routing has not changed to a more public device
 * while preempted.
 *
 * A now playing example in QML:
 *
 * @code
      import bb.multimedia 1.0
      ...
      attachedObjects: [
          NowPlayingConnection {
              id: nowplaying

              connectionName: "myConnection"
              iconUrl: "asset:///artwork.png"

              onAcquired: {
                var metadata = { "track": "MyTrack", "artist" : "MyArtist" };

                nowplaying.duration = 120000; // 2min in milliseconds
                nowplaying.position = 0;

                nowplaying.mediaState = MediaState.Started;

                nowplaying.setMetaData(metadata);
              }

              onPause: {
                mymedia.pause();
              }

              onPlay: {
                mymedia.play();
              }

              onRevoked: {
                mymedia.stop();
              }
          }
      ]
      ...
      onMyMediaWantsToPlay: {
          nowplaying.acquire();
      }
      ...
      onMyMediaPaused: {
          nowplaying.mediaState = MediaState.Paused;
      }
      ...
      onMyMediaPositionChanged: {
          nowplaying.position = ms;
      }
      ...
      onMyMediaNoLongerWantsToPlay: {
          nowplaying.revoke();
      }
      ...
      onMyMediaTrackHasChanged: {
          nowplaying.trackChange();
      }
 * @endcode
 *
 * @xmlonly
 * <qml>
 *     <class abstract="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT NowPlayingConnection : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents a flag indicating if the now playing connection has
     * been acquired.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool acquired READ isAcquired NOTIFY acquired FINAL)

    /*!
     * @brief Represents the handle of an externally managed audio manager.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant audioManagerHandle READ audioManagerHandleQml WRITE setAudioManagerHandleQml NOTIFY audioManagerHandleChanged FINAL)

    /*!
     * @brief Represents the connection name registered with the now playing
     * service.
     *
     * NOTE: This property can only be set during object construction.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString connectionName READ connectionName)

    /*!
     * @brief Represents a flag that indicates if one or more controllers are
     * active on an acquired connection.
     *
     * @details Active controllers can be internal or external to an application,
     * and require regular status updates.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool controllerActive READ isControllerActive NOTIFY controllerActiveChanged FINAL)

    /*!
     * @brief Represents the duration of the player in milliseconds.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant duration READ durationQml WRITE setDurationQml NOTIFY durationChanged FINAL)

    /*!
     * @brief Represents the path to an icon that should be displayed in the
     * notification area.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl iconUrl READ iconUrl WRITE setIconUrl NOTIFY iconUrlChanged FINAL)

    /*!
     * @brief Represents the connection name of the last now playing connection
     * to revoke this connection.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString lastRevokingConnectionName READ lastRevokingConnectionName NOTIFY revoked FINAL)

    /*!
     * @brief Represents the process ID of the last now playing connection to
     * revoke this connection.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant lastRevokingConnectionPid READ lastRevokingConnectionPidQml NOTIFY revoked FINAL)

    /*!
     * @brief Represents a flag indicating if the next button should be enabled
     * when using @c OverlayStyle::Fancy.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool nextEnabled READ isNextEnabled WRITE setNextEnabled NOTIFY nextEnabledChanged)

    /*!
     * @brief Represents the media state of the connection that is currently
     * playing.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::MediaState::Type mediaState READ mediaState WRITE setMediaState NOTIFY mediaStateChanged FINAL)

    /*!
     * @brief Represents the overlay style to use when displaying now playing
     * metadata.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::OverlayStyle::Type overlayStyle READ overlayStyle WRITE setOverlayStyle NOTIFY overlayStyleChanged FINAL)

    /*!
     * @brief Represents the current position of the player in milliseconds.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant position READ positionQml WRITE setPositionQml NOTIFY positionChanged FINAL)

    /*!
     * @brief Deprecated
     *
     * @details Represents a flag indicating the preemptable state of the
     * connection.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool preemptable READ isPreemptable WRITE setPreemptable NOTIFY preemptableChanged FINAL)

    /*!
     * @brief Represents a flag indicating if the connection is preempted or
     * not by a higher priority connection.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool preempted READ isPreempted FINAL)

    /*!
     * @brief Represents a flag indicating if the previous button should be
     * enabled when using @c OverlayStyle::Fancy.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool previousEnabled READ isPreviousEnabled WRITE setPreviousEnabled NOTIFY previousEnabledChanged)

    /*!
     * @brief Represents priority level of the connection.
     *
     * @details The priority level indicates whether the connection can be
     * preempted/acquired/revoked by other connections.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::multimedia::PriorityLevel::Type priorityLevel READ priorityLevel)

    /*!
     * @brief Represent the device mode for the now playing connection.
     *
     * @details A now playing connection that has a device mode of
     * @c DeviceMode::Capture will not be paused by screening incoming calls
     * until the call it taken.
     *
     * NOTE: This property can only be set during object construction.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY(bb::multimedia::DeviceMode::Type deviceMode READ deviceMode)

    /*!
     * @brief Represents the current repeat mode for the player.
     *
     * @details The repeat mode of the player can be @c RepeatMode::None,
     * @c RepeatMode::Track, or @c RepeatMode::All. The default is
     * @c RepeatMode::Unsupported.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::multimedia::RepeatMode::Type repeatMode READ repeatMode WRITE setRepeatMode NOTIFY repeatModeChanged FINAL)

    /*!
     * @brief Represents the current shuffle mode for the player.
     *
     * @details The shuffle mode of the player can be @c ShuffleMode::Off,
     * or @c ShuffleMode::All. The default is @c ShuffleMode::Unsupported.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::multimedia::ShuffleMode::Type shuffleMode READ shuffleMode WRITE setShuffleMode NOTIFY shuffleModeChanged FINAL)

public:

    /*!
     * @brief @c %NowPlayingConnection class constructor.
     *
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.0.0
     */
    explicit NowPlayingConnection(QObject *parent = 0);

    /*!
     * @brief @c %NowPlayingConnection class constructor.
     *
     * @param connectionName The name to use to identify with the platform now
     * playing service.
     * connection in relation to other connections.
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.0.0
     */
    explicit NowPlayingConnection(const QString &connectionName, QObject *parent = 0);

    /*!
     * @brief @c %NowPlayingConnection class constructor.
     *
     * @param connectionName The name to use to identify with the platform now
     * playing service.
     * @param priorityLevel The priority level determining the behavior of the
     * connection in relation to other connections.
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.3.0
     */
    NowPlayingConnection(const QString &connectionName, bb::multimedia::PriorityLevel::Type priorityLevel, QObject *parent = 0);

    /*!
     * @brief @c %NowPlayingConnection class constructor.
     *
     * @param connectionName The name to use to identify with the platform now
     * playing service.
     * @param priorityLevel The priority level determining the behavior of the
     * connection in relation to other connections.
     * @param deviceMode The device mode of the now playing media device.
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.3.1
     */
    NowPlayingConnection(const QString &connectionName, bb::multimedia::PriorityLevel::Type priorityLevel, bb::multimedia::DeviceMode::Type deviceMode, QObject *parent = 0);

    /*!
     * @brief @c %NowPlayingConnection class destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~NowPlayingConnection();

    /*!
     * @brief Returns the handle of an externally managed audio manager.
     *
     * @return Returns the handle of an externally managed audio manager or
     * zero if not set.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int audioManagerHandle() const;

    /*!
     * @brief Used to return the name of the now playing connection.
     *
     * @return Returns the name of the now playing connection visible to the
     * now playing service.
     *
     * @since BlackBerry 10.0.0
     */
    QString connectionName() const;

    /*!
     * @brief Used to return the device mode of the now playing connection.
     *
     * @return Returns the device mode of the now playing connection.
     *
     * @since BlackBerry 10.3.1
     */
    bb::multimedia::DeviceMode::Type deviceMode() const;

    /*!
     * @brief Used to determine the track duration.
     *
     * @return Returns a number representing the duration in milliseconds of
     * the track being played.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int duration() const;

    /*!
     * @brief Used to return the icon path.
     *
     * @return Returns the URL path of an icon that will used in the
     * notification area.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl iconUrl() const;

    /*!
     * @brief Used to determine if a particular @c %NowPlayingConnection
     * instance has successfully acquired the connection.
     *
     * @return Returns @c true when the connection has been acquired, and @c false
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isAcquired() const;

    /*!
     * @brief Determines if one or more controllers are active on the service
     * that is currently acquired.
     *
     * @details Active controllers can be internal or external to an application,
     * and require regular status updates.
     *
     * @return Returns @c true when one or more controllers are active, and @c false
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isControllerActive() const;

    /*!
     * @brief A flag to indicate if the Next button is enabled.
     *
     * @return Returns @c true if the Next button is enabled on overlays using
     * the @c OverlayStyle::Fancy property, and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isNextEnabled() const;

    /*!
     * @brief A flag to indicate if the current connection has been
     * preempted by a higher priority connection or not.
     *
     * @details If this connection is not acquired, the function will return @c false.
     *
     * @return Returns @c true if the connection is currently preempted,
     * and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPreempted() const;

    /*!
     * @brief A flag to indicate if an acquired connection is preemptable
     * or not by another now playing connection. Deprecated.
     *
     * @details The method was deprecated because setting this flag in
     * @c setPreemptable to @c false would not stop another high level
     * priority connection from acquiring the resources. Therefore this
     * method gives invalid results.
     *
     * The method was replaced by Priority Level approach. See @c PriorityLevel
     * property documentation for details.
     *
     * @return Returns @c true if the connection is preemptable, and @c false
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPreemptable() const BB_MULTIMEDIA_DEPRECATED;

    /*!
     * @brief A flag to indicate if the Previous button is enabled.
     *
     * @return Returns @c true if the Previous button is enabled on overlays using
     * the @c OverlayStyle::Fancy property, and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPreviousEnabled() const;

    /*!
     * @brief Used to return the name of the connection that last revoked
     * this now playing connection.
     *
     * @return Returns the name of a now playing connection.
     *
     * @since BlackBerry 10.0.0
     */
    QString lastRevokingConnectionName() const;

    /*!
     * @brief Used to return the process ID of the connection that last revoked
     * this now playing connection.
     *
     * @return Returns the process ID of a now playing connection. If never
     * revoked, a PID of zero is returned.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int lastRevokingConnectionPid() const;

    /*!
     * @brief Used to determine the overlay style to use for displaying
     * now playing metadata.
     *
     * @return Returns the connection overlay style set with @c
     * setOverlayStyle.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::OverlayStyle::Type overlayStyle() const;

    /*!
     * @brief Used to determine the now playing connection state.
     *
     * @return Returns the current connection state, which can be stopped, playing,
     * or paused.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaState::Type mediaState() const;

    /*!
     * @brief Used to determine the track position.
     *
     * @return Returns a number representing the current playback position
     * in milliseconds of the track being played.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int position() const;

    /*!
     * @brief Sets the handle of an externally managed audio manager.
     *
     * @details Changing this property will allow the now playing service
     * to perform targeted auto resume functionality using the specified
     * audio manager handle. Setting an audio manager handle of zero
     * will reset to no registered audio manager.  The original owner of the
     * audio manager handle is responsible for releasing it.
     *
     * @param audioManagerHandle The audio manager handle to use.
     *
     * @return Returns the last recording error.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setAudioManagerHandle(unsigned int audioManagerHandle);

    /*!
     * @brief Returns the connection priority level
     *
     * @details Can be used for defining if any other connection can
     * acquire now playing service from this connection.
     * See @c PriorityLevel documentation for details.
     *
     * @since BlackBerry 10.3.0
     */
    bb::multimedia::PriorityLevel::Type priorityLevel() const;

    /*!
     * @brief Retrieves the current player repeat mode as set by a call
     * from @c setRepeatMode().
     *
     * @return Returns the current player repeat mode.
     *
     * @since BlackBerry 10.3.0
     */
    bb::multimedia::RepeatMode::Type repeatMode() const;

    /*!
     * @brief Retrieves the current player shuffle mode as set by a call
     * from @c setShuffleMode().
     *
     * @return Returns the current player shuffle mode.
     *
     * @since BlackBerry 10.3.0
     */
    bb::multimedia::ShuffleMode::Type shuffleMode() const;

public Q_SLOTS:

    /*!
     * @brief Used to request exclusive access to the now playing service.
     *
     * @details Access will be granted based on priority level of connection A, already acquired,
     * and connection B, trying to acquire nowplaying service.
     * See @c PriorityLevel documentation for details.
     *
     * @return Returns a media error that occurred calling this function or @c
     * MediaError::None if the call completed successfully.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type acquire();

    /*!
     * @brief Used to revoke this connection if acquired.
     *
     * @details If this connection is acquired, it will result in the @c
     * revoked() signal being emitted. If the connection is not acquired, no
     * action will be taken on the object.
     *
     * @return Returns a media error that occurred calling this function or @c
     * MediaError::None if the call completed successfully.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type revoke();

    /*!
     * @brief Used to set the number representing the duration
     * (in milliseconds) of the track being played.
     *
     * @param duration The duration of the current track.
     *
     * @since BlackBerry 10.0.0
     */
    void setDuration(unsigned int duration);

    /*!
     * @brief Used to set the URL to an icon that can be displayed in a
     * now playing notification area.
     *
     * @details This could be the album artwork or an icon representing the
     * application owning the connection.
     *
     * @param url The URL to an image to representing the current now playing
     * track.
     *
     * @since BlackBerry 10.0.0
     */
    void setIconUrl(const QUrl &url);

    /*!
     * @brief Used to notify the now playing connection of the current playback
     * state.
     *
     * @param state The current playback state, which can be playing, stopped, or
     * paused.
     *
     * @since BlackBerry 10.0.0
     */
    void setMediaState(bb::multimedia::MediaState::Type state);

    /*!
     * @brief Used to notify the now playing connection of the metadata
     * associated with the current media source.
     *
     * @param metadata An object containing the metadata associated with
     * the connection that is currently playing.
     *
     * @since BlackBerry 10.0.0
     */
    void setMetaData(const QVariantMap &metadata);

    /*!
     * @brief Used to set whether or not the Next button should be
     * enabled on overlays.
     *
     * @details When enabled, this flag makes the Next button usable while the
     * @c overlayStyle property is set to @c OverlayStyle::Fancy. This flag is
     * ignored when the @c overlayStyle property is set to
     * @c OverlayStyle::Plain.
     *
     * @param nextEnabled If @c true the Next button should be enabled, if @c false
     * the Next button should not be enabled.
     *
     * @since BlackBerry 10.0.0
     */
    void setNextEnabled(bool nextEnabled);

    /*!
     * @brief Used to set the overlay style to use for currently playing
     * metadata.
     *
     * @details The default is @c OverlayStyle::Plain.
     *
     * @param overlayStyle The overlay style to set on the @c
     * %NowPlayingConnection.
     *
     * @since BlackBerry 10.0.0
     */
    void setOverlayStyle(bb::multimedia::OverlayStyle::Type overlayStyle);

    /*!
     * @brief Used to set a number representing the current playback
     * position (in milliseconds) of the track being played.
     *
     * @param position The position of the current track.
     *
     * @since BlackBerry 10.0.0
     */
    void setPosition(unsigned int position);

    /*!
     * @brief Deprecated
     *
     * @details When disabled, no other connection can acquire the now
     * playing service from this acquired connection. If a preemptable
     * connection is currently acquired, it will be paused until this
     * connection revokes itself.
     *
     * The method was replaced by Priority Level approach. See @c PriorityLevel
     * property documentation for details.
     *
     * @param preemptable If @c true an acquired connection is preemptible, if
     * @c false an acquired connection is not preemptible.
     *
     * @since BlackBerry 10.0.0
     */
    void setPreemptable(bool preemptable) BB_MULTIMEDIA_DEPRECATED;

    /*!
     * @brief Used to set whether or not the Previous button should be
     * enabled on overlays.
     *
     * @details When enabled, the Previous button will be usable when
     * using @c OverlayStyle::Fancy. For @c OverlayStyle::Plain this
     * flag is ignored.
     *
     * @param previousEnabled If @c true the Previous button should be enabled, if
     * @c false the Previous button should not be enabled.
     *
     * @since BlackBerry 10.0.0
     */
    void setPreviousEnabled(bool previousEnabled);

    /*!
     * @brief Used to set the value of the repeat mode for the player.
     *
     * @details This function sets the repeat mode for the player. Any active
     * controller will be notified of the current mode.
     *
     * @param repeatMode The specified repeat mode. The value can be @c RepeatMode::None,
     * @c RepeatMode::Track, or @c RepeatMode::All.
     *
     * @since BlackBerry 10.3.0
     */
    void setRepeatMode(bb::multimedia::RepeatMode::Type repeatMode);

    /*!
     * @brief Used to set the value of the shuffle mode for the player.
     *
     * @details This function sets the shuffle mode for the player. Any active
     * controller will be notified of the current mode.
     *
     * @param shuffleMode The specified repeat mode. The value can be @c ShuffleMode::None,
     * or @c ShuffleMode::All.
     *
     * @since BlackBerry 10.3.0
     */
    void setShuffleMode(bb::multimedia::ShuffleMode::Type shuffleMode);

    /*!
     * @brief Used to delimit tracks with the now playing service.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type trackChange();

Q_SIGNALS:

    /*!
     * @brief This signal is emitted when the now playing service has been
     * successfully acquired.
     *
     * @since BlackBerry 10.0.0
     */
    void acquired();

    /*!
     * @brief This signal is emitted when the externally managed audio
     * manager has changed.
     *
     * @param audioManagerHandle The audio manager handle.
     *
     * @since BlackBerry 10.0.0
     */
    void audioManagerHandleChanged(unsigned int audioManagerHandle);
    /*! @cond PRIVATE */
    void audioManagerHandleChanged(const QVariant &audioManagerHandle);
    /*! @endcond */

    /*!
     * @brief This signal is emitted in response to controller activity on
     * the connection.
     *
     * @param controllerActive If @c true one or more controllers are active on the
     * now playing service, if @c false no controllers are active on the now playing
     * service.
     *
     * @since BlackBerry 10.0.0
     */
    void controllerActiveChanged(bool controllerActive);

    /*!
     * @brief This signal is emitted when the duration value changes.
     *
     * @param duration The duration of the current track.
     *
     * @since BlackBerry 10.0.0
     */
    void durationChanged(unsigned int duration);
    /*! @cond PRIVATE */
    void durationChanged(const QVariant &duration);
    /*! @endcond */

    /*!
     * @brief This signal is emitted on notification that a forward
     * command has been received.
     *
     * @since BlackBerry 10.0.0
     */
    void forward();

    /*!
     * @brief This signal is emitted when the icon URL value changes.
     *
     * @param url The current icon location.
     *
     * @since BlackBerry 10.0.0
     */
    void iconUrlChanged(const QUrl &url);

    /*!
     * @brief This signal is emitted when the media state changes.
     *
     * @param mediaState The current media state being associated with
     * the now playing connection.
     *
     * @since BlackBerry 10.0.0
     */
    void mediaStateChanged(bb::multimedia::MediaState::Type mediaState);

    /*!
     * @brief This signal is emitted when the metadata changes.
     *
     * @param metadata The updated metadata associated with the now playing
     * connection.
     *
     * @since BlackBerry 10.0.0
     */
    void metaDataChanged(const QVariantMap &metadata);

    /*!
     * @brief This signal is emitted on notification that a next track command
     * has been received.
     *
     * @since BlackBerry 10.0.0
     */
    void next();

    /*!
     * @brief This signal is emitted when @c setNextEnabled() is called.
     *
     * @param nextEnabled A flag to indicate that the enabled flag has been
     * toggled.
     *
     * @since BlackBerry 10.0.0
     */
    void nextEnabledChanged(bool nextEnabled);

    /*!
     * @brief This signal is emitted when the overlay style has been changed.
     *
     * @param overlayStyle The current overlay style.
     *
     * @since BlackBerry 10.0.0
     */
    void overlayStyleChanged(bb::multimedia::OverlayStyle::Type overlayStyle);

    /*!
     * @brief This signal is emitted on notification that a pause track command
     * has been received.
     *
     * @since BlackBerry 10.0.0
     */
    void pause();

    /*!
     * @brief This signal is emitted on notification that a play track command
     * has been received.
     *
     * @since BlackBerry 10.0.0
     */
    void play();

    /*!
     * @brief This signal is emitted when the position value changes.
     *
     * @param position The position of the current track.
     *
     * @since BlackBerry 10.0.0
     */
    void positionChanged(unsigned int position);
    /*! @cond PRIVATE */
    void positionChanged(const QVariant &position);
    /*! @endcond */

    /*!
     * @brief Deprecated
     *
     * @details This signal is emitted when the preemptable value changes.
     *
     * The method was replaced by Priority Level approach. See @c PriorityLevel
     * property documentation for details.
     *
     * @param preemptable A flag indicating if the connection is preemptable
     * or not.
     *
     * @since BlackBerry 10.0.0
     */
    void preemptableChanged(bool preemptable) BB_MULTIMEDIA_DEPRECATED;

    /*!
     * @brief This signal is emitted on notification that a previous track
     * command has been received.
     *
     * @since BlackBerry 10.0.0
     */
    void previous();

    /*!
     * @brief This signal is emitted when @c setPreviousEnabled() is called.
     *
     * @param previousEnabled A flag to indicate that the enabled flag has been
     * toggled.
     *
     * @since BlackBerry 10.0.0
     */
    void previousEnabledChanged(bool previousEnabled);

    /*!
     * @brief This signal is emitted on notification that a toggle repeat
     * command has been received.
     *
     * @since BlackBerry 10.3.0
     */
    void repeat();

    /*!
     * @brief This signal is emitted on notification that a specific repeat
     * command has been received.
     *
     * @param repeatMode The requested repeat value the player should try
     * and change to.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    void repeatRequest(bb::multimedia::RepeatMode::Type repeatMode);

    /*!
     * @brief This signal is emitted when the player repeat value has changed.
     *
     * @param repeatMode The new repeat value that the player has changed to.
     *
     * @since BlackBerry 10.3.0
     */
    void repeatModeChanged(bb::multimedia::RepeatMode::Type repeatMode);

    /*!
     * @brief This signal is emitted on notification that the connection has
     * lost its exclusive access.
     *
     * @since BlackBerry 10.0.0
     */
    void revoked();

    /*!
     * @brief This signal is emitted on notification that a rewind command has
     * been received.
     *
     * @since BlackBerry 10.0.0
     */
    void rewind();

    /*!
     * @brief This signal is emitted on notification that a shuffle command
     * has been received.
     *
     * @since BlackBerry 10.3.0
     */
    void shuffle();

    /*!
     * @brief This signal is emitted on notification that a shuffle command
     * has been received.
     *
     * @param shuffleMode The requested shuffle value the player should try
     * and change to.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    void shuffleRequest(bb::multimedia::ShuffleMode::Type shuffleMode);

    /*!
     * @brief This signal is emitted when the player shuffle value has changed.
     *
     * @param shuffleMode The new shuffle value that the player has changed to.
     *
     * @since BlackBerry 10.3.0
     */
    void shuffleModeChanged(bb::multimedia::ShuffleMode::Type shuffleMode);

    /*!
     * @brief This signal is emitted on notification that a stop track command
     * has been received.
     *
     * @since BlackBerry 10.0.0
     */
    void stop();

protected:
    /*! @cond PRIVATE */
    void setConnectionName(const QString &connectionName);
    void setDeviceMode(bb::multimedia::DeviceMode::Type deviceMode);
    void setPriorityLevel(bb::multimedia::PriorityLevel::Type level);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    NowPlayingConnectionPrivate * const d_ptr;
    Q_DISABLE_COPY(NowPlayingConnection)
    Q_DECLARE_PRIVATE(NowPlayingConnection)

    QVariant audioManagerHandleQml() const;
    QVariant durationQml() const;
    QVariant lastRevokingConnectionPidQml() const;
    QVariant positionQml() const;
    void setAudioManagerHandleQml(const QVariant &handle);
    void setDurationQml(const QVariant &durationQml);
    void setPositionQml(const QVariant &positionQml);
    /*! @endcond */
};

}; // namespace multimedia
}; // namespace bb

QML_DECLARE_TYPE(bb::multimedia::NowPlayingConnection)

#endif /* BB_MULTIMEDIA_NOWPLAYINGCONNECTION_HPP */

/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_MEDIAPLAYER_HPP
#define BB_MULTIMEDIA_MEDIAPLAYER_HPP

#include <bb/multimedia/AudioOutput>
#include <bb/multimedia/BufferStatus>
#include <bb/multimedia/DeviceMode>
#include <bb/multimedia/EqualizerPreset>
#include <bb/multimedia/Global>
#include <bb/multimedia/MetaData>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaState>
#include <bb/multimedia/RepeatMode>
#include <bb/multimedia/VideoOutput>

#include <QtDeclarative/QtDeclarative>
#include <QRect>
#include <QSize>
#include <QObject>
#include <QUrl>
#include <QVariantMap>

namespace bb
{
namespace multimedia
{

class MediaPlayerPrivate;

/*!
 * @headerfile MediaPlayer.hpp <bb/multimedia/MediaPlayer>
 *
 * @brief The @c %MediaPlayer class provides the ability to control media playback.
 *
 * @details This class is used by applications to control the playback of media
 * sources. Creating multiple instances of this class allows you to play
 * up to eight media sources at the same time. Depending on the media source some
 * blocking methods could take longer to return. The specific blocking methods are
 * indicated.
 *
 * A playback example in C++:
 *
 * @code
        bb::multimedia::MediaPlayer mp(this);
        mp.setSourceUrl(QUrl("asset:///media.mp3"));

    On user events...

        void onPlay() {
            mp.play(); // automatically prepares
        }

        void onStop() {
            mp.stop();
        }

 * @endcode
 *
 * A playback example in QML:
 *
 * @code
    import bb.multimedia 1.0
    // ...

    Page {
        Container {
            // ...

            attachedObjects: [
                MediaPlayer {
                    id: player
                    sourceUrl: "asset:///media.mp4"

                    // Set these properties for video
                    videoOutput: VideoOutput.PrimaryDisplay
                    windowId: fwcVideoSurface.windowId

                    onMediaStateChanged: {
                        switch (player.mediaState) {
                            case MediaState.Unprepared:
                                break;
                            case MediaState.Prepared:
                                break;
                            // ...
                        }
                    }
                }
            ]


            ForeignWindowControl {
                id: fwcVideoSurface
                windowId: "myVideoSurface"
                visible: boundToWindow

                updatedProperties: WindowProperty.Size |
                                   WindowProperty.Position |
                                   WindowProperty.Visible
            }

            // ...

            Button {
                id: btnPlay
                text: "Play"
                onClicked: {
                    if (player.play() != MediaError.None) {
                        // Your error handling code here.
                    }
                }
            }

            Button {
                id: btnStop
                text: "Stop"
                onClicked: {
                    player.stop();
                }
            }

            Button {
                id: btnReset
                text: "Reset"
                onClicked: {
                    player.reset();
                }
            }
        }
    }
 * @endcode
 *
 * @permissions The application does not need any permission to play audio
 * from its sandbox but would need the @c access_shared permission in order
 * to access the shared content areas on the device.
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT MediaPlayer : public QObject
{
    Q_OBJECT

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
     * @brief Represents the audio output for the media source. The audio
     * output can be @c AudioOutput::None or @c AudioOutput::Default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::AudioOutput::Type audioOutput READ audioOutput WRITE setAudioOutput NOTIFY audioOutputChanged FINAL)

    /*!
     * @brief Represents the auto pause status of the player.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool autoPause READ autoPause WRITE setAutoPause NOTIFY autoPauseChanged FINAL)

    /*!
     * @brief Represents the current buffer status.
     *
     * @details The buffer status can be @c BufferStatus::Idle, @c BufferStatus::Buffering,
     * or @c BufferStatus::Playing.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::BufferStatus::Type bufferStatus READ bufferStatus NOTIFY bufferStatusChanged FINAL)

    /*!
     * @brief Represents the closed caption enabled flag.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY(bool closedCaptionEnabled READ closedCaptionEnabled WRITE setClosedCaptionEnabled NOTIFY closedCaptionEnabledChanged REVISION 4 FINAL)

    /*!
     * @brief Represents the closed caption index being used for the current track.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(QVariant closedCaptionIndex READ closedCaptionIndex WRITE setClosedCaptionIndexQml NOTIFY closedCaptionIndexChanged FINAL)

    /*!
     * @brief Represents the window ID to use when creating the closed caption
     * screen.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(QString closedCaptionWindowId READ closedCaptionWindowId WRITE setClosedCaptionWindowId NOTIFY closedCaptionWindowIdChanged FINAL)

    /*!
     * @brief Represents the device mode of the player.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY(bb::multimedia::DeviceMode::Type deviceMode READ deviceMode REVISION 4 CONSTANT FINAL)

    /*!
     * @brief Represents the length of time of the current track, when
     * available.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant duration READ durationQml NOTIFY durationChanged FINAL)

    /*!
     * @brief Represents the current equalizer preset value.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY(bb::multimedia::EqualizerPreset::Type equalizerPreset READ equalizerPreset WRITE setEqualizerPreset NOTIFY equalizerPresetChanged REVISION 4 FINAL)

    /*!
     * @brief Represents the last runtime error code notified from
     * the @c error() signal.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::MediaError::Type mediaError READ mediaError NOTIFY error FINAL)

    /*!
     * @brief Represents the current media state.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::MediaState::Type mediaState READ mediaState NOTIFY mediaStateChanged FINAL)

    /*!
     * @brief Represents the metadata associated with the current
     * track.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariantMap metaData READ metaData NOTIFY metaDataChanged FINAL)

    /*!
     * @brief Represents the position in milliseconds of the active
     * track.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant position READ positionQml NOTIFY positionChanged FINAL)

    /*!
     * @brief Represents the current repeat mode for the player.
     *
     * @details The repeat mode of the player can be @c RepeatMode::None,
     * @c RepeatMode::Track, or @c RepeatMode::All.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::RepeatMode::Type repeatMode READ repeatMode WRITE setRepeatMode NOTIFY repeatModeChanged FINAL)

    /*!
     * @brief Represents the current seek status for the current track.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool seekable READ isSeekable NOTIFY seekableChanged)

    /*!
     * @brief Represents the URL of the current media source.
     *
     * @details This media source is guaranteed to be valid when the player has
     * successfully acquired the necessary resources to play it. Otherwise, the
     * acquisition of media resources by the player will fail.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl sourceUrl READ sourceUrl WRITE setSourceUrl NOTIFY sourceUrlChanged FINAL)

    /*!
     * @brief Represents the playback speed of the track that is currently
     * playing.
     *
     * @details All speed values are relative to a value of 1.0, which is
     * considered normal playback speed. A value of zero means the player is
     * paused. Positive speed values play forward and negative speed values
     * play in reverse.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)

    /*!
     * @brief Represents the requested amount of time in milliseconds between
     * regular status updates.
     *
     * @details Generally this setting is applied to position and buffering
     * updates. If a track change occurs within the interval, it is still signaled
     * immediately.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant statusInterval READ statusIntervalQml WRITE setStatusIntervalQml NOTIFY statusIntervalChanged FINAL)

    /*!
     * @brief Represents the current track number in the playlist.
     *
     * @details The value of track is always 1 in the case of a single file playback.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant track READ track NOTIFY trackChanged FINAL)

    /*!
     * @brief Represents the total number of seekable tracks in the
     * player.
     *
     * @xmlonly
     * <qml>
     *     <variant type="unsigned int"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant trackCount READ trackCount NOTIFY trackCountChanged FINAL)

    /*!
     * @brief Represents the video height and width dimensions of
     * the media source.
     *
     * @details This value is available as soon as playback begins.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QSize videoDimensions READ videoDimensions NOTIFY videoDimensionsChanged FINAL)

    /*!
     * @brief Represents the video output device for the media source.
     *
     * @details The video output device can be @c VideoOutput::None,
     * @c VideoOutput::PrimaryDisplay, or @c VideoOutput::SecondaryDisplay.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::multimedia::VideoOutput::Type videoOutput READ videoOutput WRITE setVideoOutput NOTIFY videoOutputChanged FINAL)

    /*!
     * @brief Represents the player channel volume.
     */
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged FINAL)

    /*!
     * @brief Represents the screen window group ID to use when creating the
     * video surface.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString windowGroupId READ windowGroupId WRITE setWindowGroupId NOTIFY windowGroupIdChanged FINAL)

    /*!
     * @brief Represents the window ID to use when creating the video screen.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString windowId READ windowId WRITE setWindowId NOTIFY windowIdChanged FINAL)

public:

    /*!
     * @brief @c %MediaPlayer class constructor.
     *
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MediaPlayer(
            QObject *parent = 0);

    /*!
     * @brief @c %MediaPlayer class destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MediaPlayer();

    /*!
     * @brief Returns the handle of an externally managed audio manager.
     *
     * @return Returns the handle of an externally managed audio manager or
     * zero if managed internally.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int audioManagerHandle() const;

    /*!
     * @brief Returns the audio output used for audio playback.
     *
     * @details The values for audio output can either be @c AudioOutput::Default or
     * @c AudioOutput::None.
     *
     * @return Returns the current audio output.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::AudioOutput::Type audioOutput() const;

    /*!
     * @brief Provides the auto pause status of the player.
     *
     * @details When auto pause is enabled, the platform will be allowed to
     * automatically pause the player under some circumstances. In the case
     * where playback is occurring over a headset, and the headset is removed,
     * playback will be paused rather than continuing over the speaker.
     *
     * @return Returns @c true if auto pause is enabled, and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool autoPause() const;

    /*!
     * @brief Returns the current buffer status.
     *
     * @details The buffer status can be @c BufferStatus::Idle, @c BufferStatus::Buffering,
     * or @c BufferStatus::Playing.
     *
     * @return Returns the current buffer status.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::BufferStatus::Type bufferStatus() const;

    /*!
     * @brief Provides the closed caption rendering status.
     *
     * @details When enabled the platform will perform closed caption rendering.
     *
     * @return Returns @c true if closed caption rendering is enabled, and
     * @c false otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    bool closedCaptionEnabled() const;

    /*!
     * @brief Retrieves the current closed caption index.
     *
     * @details Returns the closed caption index being used on the current
     * track.
     *
     * @since BlackBerry 10.3.0
     */
    unsigned int closedCaptionIndex() const;

    /*!
     * @brief Retrieves the closed caption url at the given track.
     *
     * @return Returns the closed caption url being used on the specified
     * track. If no caption url is set this method returns an empty QUrl.
     *
     * @since BlackBerry 10.3.0
     */
    Q_INVOKABLE
    QUrl closedCaptionUrl(unsigned int track) const;

    /*!
     * @brief Retrieves the window ID of the closed caption screen.
     *
     * @return Returns the window ID of the screen used for closed caption
     * rendering. The screen window is created during preparation if this
     * property is set and the @c videoOutput is not @c VideoOutput::None.
     * The window ID set using @c setClosedCaptionWindowId() will be returned
     * regardless of state.
     *
     * @since BlackBerry 10.3.0
     */
    QString closedCaptionWindowId() const;

    /*!
     * @brief Retrieves the device mode for the player.
     *
     * @return @c DeviceMode::Playback
     *
     * @since BlackBerry 10.3.1
     */
    bb::multimedia::DeviceMode::Type deviceMode() const;

    /*!
     * @brief Provides the duration of a currently prepared track.
     *
     * @details The duration of the current track is available once
     * @c prepare() has been called, and the player has successfully
     * acquired the resources to play the current track. The duration
     * of the current track is no longer available when @c stop() has been
     * called. In any other case, a duration of zero is returned.
     *
     * @return Returns the duration in milliseconds of the current track,
     * and zero otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int duration() const;

    /*!
     * @brief Used to retrieve the current equalizer preset value.
     *
     * @returns The current equalizer preset value.
     *
     * @since BlackBerry 10.3.1
     */
    bb::multimedia::EqualizerPreset::Type equalizerPreset() const;

    /*!
     * @brief Provides the seek status of the current track.
     *
     * @details If playback for the current track has the ability to
     * seek to an arbitrary location, this function will return true.
     * Otherwise tracks are not seekable by default. When the track
     * is seekable, the @c seekableChanged() signal is emitted.
     *
     * @return Returns @c true if the track is seekable, and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isSeekable() const;

    /*!
     * @brief Used to retrieve the last recording error.
     *
     * @details If the @c error() signal has been emitted, this
     * property will return the last error type, otherwise
     * @c MediaError::None is returned. This property is
     * automatically reset to @c MediaError::None when
     * recording starts.
     *
     * @return Returns the last playback media error.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type mediaError() const;

    /*!
     * @brief Used to determine the current media state.
     *
     * @details If @c prepare() has not been called or the recording has
     * been stopped, @c MediaState::Unprepared will be returned. If actively
     * recording, @c MediaState::Started will be returned. If paused,
     * @c MediaState::Paused will be returned.
     *
     * @return Returns the current media state.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaState::Type mediaState() const;

    /*!
     * @brief Used to retrieve the metadata for the track that is currently
     * playing.
     *
     * @return Returns the metadata for the track that is currently playing.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap metaData() const;

    /*!
     * @brief Provides the playback position of the current track.
     *
     * @details The playback position of the current track changes while the
     * player is playing, or after a successful call to the @c seekTime() or
     * @c seekPercent() functions. A value of zero is returned when the player
     * has not yet acquired the resources to play the media source, or after
     * it has been stopped by a call to the @c stop() function.
     *
     * @return Returns the playback position in milliseconds of the current
     * track.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int position() const;

    /*!
     * @brief Retrieves the current playback repeat mode as set by a call
     * from @c setRepeatMode().
     *
     * @return Returns the current playback repeat mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::RepeatMode::Type repeatMode() const;

    /*!
     * @brief Sets the handle of an externally managed audio manager.
     *
     * @details Changing this property while the player is prepared will cause
     * the audio management to switch seamlessly to the new audio manager. The
     * original owner of the audio manager handle is responsible for releasing it.
     *
     * @param audioManagerHandle The audio manager handle to use.
     *
     * @return Returns the last playback media error.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setAudioManagerHandle(unsigned int audioManagerHandle);

    /*!
     * @brief Retrieves the source URL for the player as set by a call from
     * @c setSourceUrl().
     *
     * @return Returns the source URL for the player.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl sourceUrl() const;

    /*!
     * @brief Retrieves the current playback speed as set by a call from @c
     * setSpeed().
     *
     * @return Returns the current playback speed, as described by
     * @c setSpeed().
     *
     * @since BlackBerry 10.0.0
     */
    double speed() const;

    /*!
     * @brief Represents the requested amount of time in milliseconds between
     * regular status updates.
     *
     * @details Generally this setting is applied to position and buffering
     * updates. If a track change occurs within the interval, it is still
     * signaled immediately. By default the requested update status interval is 1000
     * milliseconds.
     *
     * @return Returns the current requested status interval in milliseconds, as
     * described by @c setStatusInterval().
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int statusInterval() const;

    /*!
     * @brief Returns the current track in a playlist.
     *
     * @details Single track playback will have a value of 1, otherwise
     * the track number of the current track in the playlist is returned.
     *
     * @return Returns the current player track number.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int track() const;

    /*!
     * @brief Retrieves the number of tracks available to the player.
     *
     * @details This value can be used to specify a playlist file rather
     * than a single track as the media source for the player. This function
     * returns 1 when a single track is specified as the media source.
     *
     * @return Returns the number of tracks available to the player.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int trackCount() const;

    /*!
     * @brief Retrieves the video dimensions for the current track when
     * available.
     *
     * @return Returns the video dimensions when available.
     *
     * @since BlackBerry 10.0.0
     */
    QSize videoDimensions() const;

    /*!
     * @brief Retrieves the video output of the screen used for video rendering.
     *
     * @details The screen window is created during preparation if the @c videoOutput
     * is set to either @c VideoOutput::PrimaryDisplay or
     * @c VideoOutput::SecondaryDisplay. If the value for @c videoOutput is set
     * to @c VideoOutput::None then the screen will be destroyed. The window ID
     * set using @c setWindowId() is returned.
     *
     * @return Returns the current video output.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::VideoOutput::Type videoOutput() const;

    /*!
     * @brief Retrieves the channel volume for this instance of the player.
     *
     * @return Returns the current volume in the range of 0.0 to 1.0.
     */
    double volume() const;

    /*!
     * @brief Retrieves the window group ID of the video screen.
     *
     * @return Returns the window group ID of the screen used for video
     * rendering. The screen window is created during preparation if the
     * @c windowId property is set and the @c videoOutput is not
     * @c VideoOutput::None. The window group ID set using @c setWindowGroupId()
     * will be returned regardless of state.
     *
     * @since BlackBerry 10.0.0
     */
    QString windowGroupId() const;

    /*!
     * @brief Retrieves the window ID of the video screen.
     *
     * @return Returns the window ID of the screen used for video rendering.
     * The screen window is created during preparation if this property is set
     * and the @c videoOutput is not @c VideoOutput::None. The window ID set
     * using @c setWindowId() will be returned regardless of state.
     *
     * @since BlackBerry 10.0.0
     */
    QString windowId() const;

public Q_SLOTS:

   /*!
     * @brief Moves playback to the next track in the playlist.
     *
     * @details If the media source is a playlist, this function will move to
     * the next track. On success it will result in a @c trackChanged()
     * signal.
     *
     * If the media source is not a playlist then calling this function
     * does nothing.
     *
     * This method call is blocking.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
    *
    * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type nextTrack();

   /*!
     * @brief Pauses a currently playing track.
     *
     * @details This function is equivalent to calling @c setSpeed(0.0). On
     * success a @c mediaStateChanged signal will be emitted with a
     * @c MediaState:Paused value. Call @c play() or @c setSpeed()
     * with a non-zero value to restart playback.
     *
     * Calling this function while playback is already paused does nothing.
     *
     * This method call is blocking.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
    *
    * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type pause();

    /*!
     * @brief Starts playback of a track.
     *
     * @details This function will start playback of a track. If
     * the player is paused it will be resumed. If the player is stopped it
     * will restart from the beginning. Successful playback will emit a
     * @c mediaStateChanged() signal with a @c MediaState::Started value.
     * If the player is in the @c MediaState.Unprepared state internally
     * @c prepare() will be called. In this case a @c mediaStateChanged()
     * signal is emitted twice, once with a value of @c MediaState.Prepared
     * and next @c MediaState.Started.
     *
     * This method call is blocking.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type play();

    /*!
     * @brief Acquires resources necessary for playback without playing the
     * track.
     *
     * @details This process will move the player into the stopped state.
	 * Calling this function will attempt to acquire all the resources needed
	 * for playback. If successful the @c mediaStateChanged signal will be
	 * emitted with a value of @c MediaState.Prepared.
	 *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type prepare();

    /*!
     * @brief Moves playback to the previous track in the playlist.
     *
     * @details If the media source is a playlist, this function will move to the
     * previous track. On success it will result in a @c trackChanged() signal.
     *
     * If the media source is not a playlist then calling this function does
     * nothing.
     *
     * This method call is blocking.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type previousTrack();

    /*!
     * @brief Frees all resources previously acquired for playback.
     *
     * @details Calling this function has no effect if the player is
     * already in the unprepared state. Otherwise all acquired
     * resources are freed, stopping the player if needed, and the state
     * is moved to unprepared.
     *
     * This method call is blocking.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type reset();

    /*!
     * @brief Seeks to the track and position nearest to the given time.
     *
     * @details This function will seek to the specified track and attempt to
     * also seek to the given position. On success the @c trackChanged() signal will
     * be emitted if the track is different than the current track, and the
     * @c positionChanged() signal will be emitted with the new location.
     *
      * This method call is blocking.
     *
     * @param track The one-based index of the track to seek to.
     * @param position The position in milliseconds to attempt to seek to.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type seek(unsigned int track, unsigned int position);

    /*!
     * @brief Seeks to the position nearest to the given time.
     *
     * @details This function will attempt to seek to the given position. On
     * success the @c positionChanged() signal will be emitted with the new location.
     *
     * This method call is blocking.
     *
     * @param position The position in milliseconds to attempt to seek to.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type seekTime(unsigned int position);

    /*!
     * @brief Seeks to the position nearest to the given duration percentage.
     *
     * @details This function will attempt to seek to the given duration
     * percentage. On success the @c positionChanged() signal will be emitted with
     * the new location, or an @c error() signal is emitted.
     *
     * This method call is blocking.
     *
     * @param percentage The percentage of duration to attempt to seek to.
     * Valid values are 0.0 to 1.0.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type seekPercent(double percentage);

    /*!
     * @brief Changes the current track to the specified index.
     *
     * @details This function will cause the player to seek to the specified
     * track and will result in a @c trackChanged() signal.
     *
     * This method call is blocking.
     *
     * @param track The one-based index of the track to seek to.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type seekTrack(unsigned int track);

    /*!
     * @brief Used to set the audio output for the player.
     *
     * @details This function sets the audio output for the player. This can be
     * either @c AudioOutput::Default or @c AudioOutput::None.
     *
     * @param audioOutput The specified audio output type.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setAudioOutput(bb::multimedia::AudioOutput::Type audioOutput);

    /*!
     * @brief Used to set the auto pause functionality for the player.
     *
     * @details This function enables or disables the auto pause functionality of
     * the player. If enabled, the platform will be allowed to auto pause playback.
     * In the case where playback is occuring over a headset, and the headset is
     * removed, playback will be paused rather than continuing over the
     * speaker.
     *
     * @param autoPause If @c true auto pause is enabled, if @c false auto pause is
     * disabled.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setAutoPause(bool autoPause);

    /*!
     * @brief Sets the closed caption rendering flag.
     *
     * @details This function sets the closed caption rendering flag. When
     * the closed caption window information is provided this flag will
     * toggle the platform rendering that displays the closed caption
     * information.
     *
     * @param enabled if @c true closed caption rendering is enabled, if
     * @c false closed caption rendering is disabled.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.1
     */
    bb::multimedia::MediaError::Type setClosedCaptionEnabled(bool enabled);

    /*!
     * @brief Sets the index for source embedded closed captioning.
     *
     * @details This function sets the closed caption index for a track. This
     * selection will determine what closed caption stream is used for display
     * on the closed caption window. If @c setClosedCaptionUrl() has been
     * previously set for the specified track calls to this method will have
     * no effect.
     *
     * @param index The url of the closed caption file to use during playback.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.0
     */
    bb::multimedia::MediaError::Type setClosedCaptionIndex(unsigned int index);

    /*!
     * @brief Sets the url for a closed caption file to used for playback.
     *
     * @details This function sets the closed caption url for the specified
     * track. This must be set before the preparing the media source to enable
     * the use of an external closed caption files. Changing the closed caption
     * url for a track actively playing will immediately take affect.
     *
     * If the media source happens to be a playlist this method is limited to
     * only change the closed caption url for the first track.
     *
     * @param track The track to apply the closed caption url for.
     * @param url The url of the closed caption file to use during playback.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.0
     */
    bb::multimedia::MediaError::Type setClosedCaptionUrl(unsigned int track, const QUrl &url);

    /*!
     * @brief Sets the closed caption window ID to use when the video output
     * device is set to either primary or secondary.
     *
     * @details This function sets the closed caption window ID to use when
     * the player creates a screen to use for the video surface.
     *
     * @param closedCaptionWindowId The screen window ID name to use.
     *
     * @since BlackBerry 10.3.0
     */
    void setClosedCaptionWindowId(const QString &closedCaptionWindowId);

    /*!
     * @brief Used to set the value of the equalizer preset.
     *
     * @details The equalizer preset value is used to tune the audio
     * experience for the type of audio being played. If a preset is
     * set against an audio output that does not support presets,
     * there will be no equalizer preset in effect on the audio
     * device.
     *
     * @param equalizerPreset The specified equalizer preset.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     *  @since BlackBerry 10.3.1
     */
    bb::multimedia::MediaError::Type setEqualizerPreset(bb::multimedia::EqualizerPreset::Type equalizerPreset);

    /*!
     * @brief Used to set the value of the repeat mode for the player.
     *
     * @details This function sets the repeat mode for the player. When set to track,
     * the player will continuously play and repeat the current track. When set to
     * all, the player will play all tracks in a playlist, then repeat the
     * entire playlist once all tracks have been played. When set to none, no
     * repetition will occur.
     *
     * @param repeatMode The specified repeat mode. The value can be @c RepeatMode::None,
     * @c RepeatMode::Track, or @c RepeatMode::All.
     *
     * @return Returns @c MediaError::None on success, @c MediaError::UnsupportedValue on
     * trying to set @c MediaPlayer::Unsupported, otherwise a specific media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setRepeatMode(bb::multimedia::RepeatMode::Type repeatMode);

    /*!
     * @brief Sets the URI to be used as the media source.
     *
     * @details This function sets the media source for the player. The URL can
     * point to a single track, or a playlist. If the player has acquired the
     * resources to play the media source and this value is empty, then the
     * player will stop and release any resources that it currently holds.
     *
     * This method call is blocking.
     *
     * @param url A URL string pointing to a track or a playlist to use as a
     * media source.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setSourceUrl(const QUrl &url);

    /*!
     * @brief Sets the playback speed of the player.
     *
     * @details Normal playback speed is 1.0, and it is the default
     * speed when the player is prepared. The player is prepared when it
     * has acquired the necessary resources to play the media source.
     *
     * Setting this value to 0.0 is equivalent to pausing playback
     * and will emit the @c mediaStateChanged() signal with a
     * @c MediaState::Paused value.
     *
     * Conversely, if this call successfully changes the playback
     * speed from 0.0 to a non-zero speed, then the player will move
     * from paused to playing and the @c mediaStateChanged() signal
     * will be emitted with a @c MediaState::Started value.
     *
     * Any value between 0.0 and 1.0 is slow-forward playback and
     * values above 1.0 will result in fast-forward playback corresponding
     * to the value. For example, a value of 0.5 will playback at half
     * speed, and a value of 2.0 will result in twice normal playback speed.
     *
     * Negative values result in reverse playback, if supported by the media
     * source. If reverse playback is not supported, calling this function
     * with a negative value will have no effect.
     *
     * If this call successfully changes the playback speed, even when the
     * player is effectively stopped or started as a result of the call, the
     * @c speedChanged() signal is always emitted by the player.
     *
     * A call to @c setSpeed() when the player is prepared or stopped
     * will result in playback at the new speed once @c play() is called.
     * If the speed is set to 0.0 when stopped then a call to @c play()
     * will immediately transition the player to the paused state, and
     * will emit the @c mediaStateChanged() signal with a @c MediaState::Paused value.
     *
     * This method call is blocking.
     *
     * @param speed The playback speed.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setSpeed(double speed);

    /*!
     * @brief Represents the requested amount of time in milliseconds between
     * regular status update.
     *
     * @details Generally this setting is applied to position and buffering
     * updates. If a track change occurs within the interval, it is still signaled
     * immediately.
     *
     * @param statusInterval The requested status interval in milliseconds.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setStatusInterval(unsigned int statusInterval);

    /*!
     * @brief Sets the video output device to be used for playback.
     *
     * @details This function sets the video output on a player. If the player
     * is prepared and the video output is being set to or from none, the player
     * will be unprepared. It is up to the user to call @c prepare() or @c play().
     * Switching between primary and secondary video outputs on a prepared
     * player does not interrupt playback since the video device is
     * already acquired.
     *
     * @param videoOutput The video output device to be used.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setVideoOutput(bb::multimedia::VideoOutput::Type videoOutput);

    /*!
     * @brief Sets the video source rectangle to be used for display on
     * the video surface.
     *
     * @details The values for this rectangle must be less than or equal
     * to the video dimensions. By default the value of this rectangle is
     * equal to the video dimensions. The values of this rectangle can be
     * used to simulate zooming into a video.
     *
     * @param x The X coordinate of the video rectangle.
     * @param y the Y coordinate of the video rectangle.
     * @param width The width of the video source rectangle.
     * @param height The height of the video source rectange.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setVideoSourceRect(int x, int y, unsigned int width, unsigned int height);

    /*!
     * @brief Sets the player channel volume to the given percentage.
     *
     * @details The channel volume is different than the master volume,
     * which is controlled independently by the platform audio manager.
     *
     * @param volume The percentage of volume to set.
     * Valid values are 0.0 to 1.0.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     */
    bb::multimedia::MediaError::Type setVolume(double volume);

    /*!
     * @brief Sets the window group ID to use when the video output device is
     * set to either primary or secondary.
     *
     * @details This function sets the window group ID to use when the player
     * creates a screen to use for the video surface.
     *
     * @param windowGroupId The screen window group ID name to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setWindowGroupId(const QString &windowGroupId);

    /*!
     * @brief Sets the window ID to use when the video output device is
     * set to either primary or secondary.
     *
     * @details This function sets the window ID to use when the player
     * creates a screen to use for the video surface.
     *
     * @param windowId The screen window ID name to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setWindowId(const QString &windowId);

    /*!
     * @brief Stops the player and moves to the stopped state.
     *
     * @details This function will move the player into the stopped state.
     * Calling @c play() will result in the media commencing playing back
     * from the start. This function will result in the @c stopped() signal
     * being emitted. The @c stopped() signal indicates that the player
     * is in the stopped state.
     *
     * This method call is blocking.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type stop();

Q_SIGNALS:

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
     * @brief This signal is emitted when the audio output has changed.
     *
     * @details In response to @c setAudioOutput() this signal will be
     * emitted to notify of the change.
     *
     * @param audioOutput The current audio output.
     *
     * @since BlackBerry 10.0.0
     */
    void audioOutputChanged(bb::multimedia::AudioOutput::Type audioOutput);

    /*!
     * @brief This signal is emitted when the audio pause property has changed.
     *
     * @param autoPause The current auto pause property value.
     *
     * @since BlackBerry 10.0.0
     */
    void autoPauseChanged(bool autoPause);

    /*!
     * @brief This signal is emitted when the player is buffering.
     *
     * @details When the player is buffering, this signal will be emitted
     * indicating what percentage of the buffer has been filled. The
     * player will still be in the playing state.
     *
     * @param percentage The percentage of the buffer filled (0 - 1.0).
     *
     * @since BlackBerry 10.0.0
     */
    void buffering(double percentage);

    /*!
     * @brief This signal is emitted when the player buffer status has
     * changed.
     *
     * @details The values for this signal can be @c BufferStatus::Idle,
     * @c BufferStatus::Buffering, or @c BufferStatus::Playing.
     *
     * @param bufferStatus The current buffer status.
     *
     * @since BlackBerry 10.0.0
     */
    void bufferStatusChanged(bb::multimedia::BufferStatus::Type bufferStatus);

    /*!
     * @brief This signal is emitted when the closed caption rendering flag
     * has been changed.
     *
     * @details In response to @c setClosedCaptionEnabled() this signal will
     * be emitted to notify of the change.
     */
    Q_REVISION(4)
    void closedCaptionEnabledChanged(bool enabled);

    /*!
     * @brief This signal is emitted when the closed caption index has changed.
     *
     * @details In response to @c setClosedCaptionIndex() this signal will
     * be emitted to notify of the change.
     *
     * @param closedCaptionIndex The new closed caption index being used for the the track.
     *
     * @since BlackBerry 10.3.0
     */
    void closedCaptionIndexChanged(unsigned int closedCaptionIndex);
    /*! @cond PRIVATE */
    void closedCaptionIndexChanged(const QVariant &closedCaptionIndex);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when the closed caption index has changed.
     *
     * @details In repsonse to @c setClosedCaptionIndex() this signal will
     * be emitted to notify of the change.
     *
     * @param track The track which received the new closed caption url.
     * @param closedCaptionUrl The new closed caption url being used for the
     * the track.
     *
     * @since BlackBerry 10.3.0
     */
    void closedCaptionUrlChanged(unsigned int track, const QUrl &closedCaptionUrl);
    /*! @cond PRIVATE */
    void closedCaptionUrlChanged(const QVariant &track, const QUrl &closedCaptionUrl);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when the closed caption window ID has
     * changed.
     *
     * @details In response to @c setClosedCaptionWindowId() this signal will
     * be emitted to notify of the change.
     *
     * @param closedCaptionWindowId The new window ID to use for the video output.
     *
     * @since BlackBerry 10.3.0
     */
    void closedCaptionWindowIdChanged(const QString &closedCaptionWindowId);

    /*!
     * @brief This signal is emitted when the track duration is known.
     *
     * @details Retrieving the duration of some tracks may not be known
     * when the track is changed. This signal will notify of the duration
     * when available.
     *
     * @param duration The total duration of the track in milliseconds.
     *
     * @since BlackBerry 10.0.0
     */
    void durationChanged(unsigned int duration);
    /*! @cond PRIVATE */
    void durationChanged(const QVariant &duration);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when an error occurs during any operation
     * on the @c %MediaPlayer().
     *
     * @details When an error occurs during playback, this signal is emitted
     * with the error code, as well as the position in the recording where the
     * error occurred.
     *
     * @param mediaError The playback media error.
     * @param position The position of the player when the error occurred.
     *
     * @since BlackBerry 10.0.0
     */
    void error(bb::multimedia::MediaError::Type mediaError, unsigned int position);
    /*! @cond PRIVATE */
    void error(bb::multimedia::MediaError::Type mediaError, const QVariant &position);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when the equalizer preset of the media
     * has been changed.
     *
     * @param equalizerPreset The current equalizer preset.
     *
     * @since BlackBerry 10.3.1
     */
    Q_REVISION(4)
    void equalizerPresetChanged(bb::multimedia::EqualizerPreset::Type equalizerPreset);

    /*!
     * @brief This signal is emitted when the state of the media has
     * been changed.
     *
     * @param mediaState The current media state.
     *
     * @since BlackBerry 10.0.0
     */
    void mediaStateChanged(bb::multimedia::MediaState::Type mediaState);

    /*!
     * @brief This signal is emitted when the metadata has been parsed.
     *
     * @param metaData The parsed metadata.
     *
     * @since BlackBerry 10.0.0
     */
    void metaDataChanged(const QVariantMap &metaData);

    /*!
     * @brief This signal is emitted when all tracks have completed playback.
     *
     * @since BlackBerry 10.0.0
     */
    void playbackCompleted();

    /*!
     * @brief This signal is emitted when the track playback position has
     * changed.
     *
     * @details This signal will be emitted approximately once per second in
     * response to a call to @c seek() or when normal status updates occur.
     *
     * @param position The current track playback position in milliseconds.
     *
     * @since BlackBerry 10.0.0
     */
    void positionChanged(unsigned int position);
    /*! @cond PRIVATE */
    void positionChanged(const QVariant &position);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when the player repeat value has changed.
     *
     * @details Possible values:
     * - @c RepeatMode::All repeats the entire playlist.
     * - @c RepeatMode::Track repeat the current playlist track.
     * - @c RepeatMode::None does not repeat anything.
     *
     * @param repeatMode The new repeat value that the player has changed to.
     *
     * @since BlackBerry 10.0.0
	 */
	void repeatModeChanged(bb::multimedia::RepeatMode::Type repeatMode);

    /*!
     * @brief This signal is emitted when the known seek ability of a track
     * changes.
     *
     * @param seekable If @c true the position of the current track is seekable, if
     * @c false the position of the current track is not seekable.
     *
     * @since BlackBerry 10.0.0
     */
    void seekableChanged(bool seekable);

    /*!
     * @brief This signal is emitted when the player media source has been
     * changed.
     *
     * @details This signal is emitted when the media source for the player
     * has been changed in response to a call to @c setSource().
     *
     * @param sourceUrl The source URL for the player.
     *
     * @since BlackBerry 10.0.0
    */
    void sourceUrlChanged(const QUrl &sourceUrl);

    /*!
     * @brief This signal is emitted when the track playback speed has been
     * changed.
     *
     * @details This signal is emitted in response to a call to @c setSpeed()
     * or @c pause() while the player is in the playing state. This signal is
     * also emitted in response to a call to @c play() while the player is
     * in the paused state.
     *
     * @param speed The playback speed relative to normal playback of 1.0.
     *
     * @since BlackBerry 10.0.0
     */
    void speedChanged(double speed);

    /*!
     * @brief This signal is emitted when the requested status interval has
     * been changed.
     *
     * @details This signal is emitted in response to a call to
     * @c setStatusInterval().
     *
     * @param statusInterval The requested status interval in milliseconds.
     *
     * @since BlackBerry 10.0.0
     */
    void statusIntervalChanged(unsigned int statusInterval);
    /*! @cond PRIVATE */
    void statusIntervalChanged(const QVariant &statusInterval);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when the track has changed.
     *
     * @details This signal is emitted when the player has acquired the necessary
     * resources for playback, and the track has changed.
     *
     * @param track The current track index.
     *
     * @since BlackBerry 10.0.0
     */
    void trackChanged(unsigned int track);
    /*! @cond PRIVATE */
    void trackChanged(const QVariant &track);
    /*! @endcond */

	/*!
     * @brief This signal is emitted when the track count has changed.
     *
     * @details This signal is emitted when the player has acquired the necessary
     * resources for playback, and the track count has changed.
     *
     * @param trackCount The number of tracks available to the player.
     *
     * @since BlackBerry 10.0.0
     */
    void trackCountChanged(unsigned int trackCount);
    /*! @cond PRIVATE */
    void trackCountChanged(const QVariant &trackCount);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when the video dimensions have changed.
     *
     * @details This signal is emitted once the player has determined the
     * dimensions of the video component or they have changed.
     *
     * @param videoDimensions A size object containing both the video height
     * and width.
     *
     * @since BlackBerry 10.0.0
     */
    void videoDimensionsChanged(const QSize &videoDimensions);

    /*!
     * @brief This signal is emitted when the video output has changed.
     *
     * @details In response to @c setVideoOutput() this signal will be
     * emitted to notify of the change.
     *
     * @param videoOutput The current video output.
     *
     * @since BlackBerry 10.0.0
     */
    void videoOutputChanged(bb::multimedia::VideoOutput::Type videoOutput);

    /*!
     * @brief This signal is emitted when the player channel volume has been
     * changed.
     *
     * @details This signal is emitted in response to a call to @c setVolume().
     *
     * @param volume The player channel volume in range of 0.0 to 1.0.
     */
    void volumeChanged(double volume);

    /*!
     * @brief This signal is emitted when the window group ID has changed.
     *
     * @details In response to @c setWindowGroupId() this signal will be
     * emitted to notify of the change.
     *
     * @param windowGroupId The new window group ID to use for the video output.
     *
     * @since BlackBerry 10.0.0
     */
    void windowGroupIdChanged(const QString &windowGroupId);

    /*!
     * @brief This signal is emitted when the window ID has changed.
     *
     * @details In response to @c setWindowId() this signal will be
     * emitted to notify of the change.
     *
     * @param windowId The new window ID to use for the video output.
     *
     * @since BlackBerry 10.0.0
     */
    void windowIdChanged(const QString &windowId);

private:
    /*! @cond PRIVATE */
    MediaPlayerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(MediaPlayer)
    Q_DISABLE_COPY(MediaPlayer)

    QVariant audioManagerHandleQml() const;
    QVariant closedCaptionIndexQml() const;
    QVariant durationQml() const;
    QVariant positionQml() const;
    QVariant statusIntervalQml() const;
    QVariant trackCountQml() const;
    QVariant trackQml() const;

    void setAudioManagerHandleQml(const QVariant &handleQml);
    void setClosedCaptionIndexQml(const QVariant &indexQml);
    void setStatusIntervalQml(const QVariant &statusIntervalQml);
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::MediaPlayer)

#endif /* BB_MULTIMEDIA_MEDIAPLAYER_HPP */

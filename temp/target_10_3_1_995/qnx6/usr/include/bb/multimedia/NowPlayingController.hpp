/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_NOWPLAYINGCONTROLLER_HPP
#define BB_MULTIMEDIA_NOWPLAYINGCONTROLLER_HPP

#include <bb/multimedia/Global>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaState>
#include <bb/multimedia/MetaData>
#include <bb/multimedia/OverlayStyle>
#include <bb/multimedia/RepeatMode>
#include <bb/multimedia/ShuffleMode>

#include <QtDeclarative/QtDeclarative>
#include <QObject>
#include <QVariantMap>

namespace bb
{
namespace multimedia
{

class NowPlayingControllerPrivate;

/*!
 * @headerfile NowPlayingController.hpp <bb/multimedia/NowPlayingController>
 *
 *
 * @brief Provides system access to media controlling features.
 *
 * @details The @c %NowPlayingController class provides the ability to control media
 * which has been acquired using @c %NowPlayingConnection. Provides notification
 * of the current position, duration, state and meta data of the active media.
 *
 * A now playing sample in C++:
 *
 * @code
        // create controller object
        NowPlayingController *npc = new NowPlayingController(this);

        QVariantMap metadata;

        // get metadata for the currently being played track
        metadata = npc->metaData();

        // extract metadata values
        m_title = metadata[MetaData::Title];
        m_artist = metadata[MetaData::Artist];
        m_album = metadata[MetaData::Album];

        ...

        // start playing track
        npc->play();
        // set volume to 50% of maximum value
        npc->setVolume(0.5);

 * @endcode
 *
 * Controlling methods can be used to set volume (mute included), play, pause,
 * stop media playing, skip to the next or return to the previous track,
 * fast forward and rewind.
 *
 * A now playing sample in QML:
 *
 * @code
    import bb.cascades 1.0
    import bb.multimedia 1.2   // import the multimedia library for access to the NowPlayingController

    Page {
        Container {
            layout: StackLayout  {
                orientation: LayoutOrientation.TopToBottom
            }
            topPadding:40

            attachedObjects: [
                // Create a NowPlayingController object
                NowPlayingController {
                    id: nowPlayingController

                    // handle various events sent by the NowPlayingController and update the controls
                    onDurationChanged: {
                        length.text = duration;
                    }

                    onNextEnabledChanged: {
                        next.enabled = nextEnabled;
                    }

                    onPreviousEnabledChanged: {
                        prev.enabled = previousEnabled;
                    }

                    onMediaStateChanged: {
                        playState.text = mediaState;
                    }

                    onMetaDataChanged: {
                        artist.text = metaData["artist"];
                        album.text  = metaData["album"];
                        title.text  = metaData["title"];
                    }

                    onPositionChanged: {
                        currentPosition.text = nowPlayingController.position;
                    }

                    onIconUrlChanged: {
                        albumArt.imageSource = nowPlayingController.iconUrl
                    };

            }

            ]

            ImageView {
                id: albumArt
                imageSource: "asset:///artwork.png"
                preferredHeight: 320
                minHeight:320
                minWidth:320
                scalingMethod: ScalingMethod.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Top
            }

            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "Artist:"
                }
                Label {
                    id: artist
                    text: ""
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "Album:"
            }
                Label {
                    id: album
                    text: ""
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "Title:"
                }
                Label {
                    id: title
                    text: ""
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "Duration (ms):"
                }
                Label {
                    id: length
                    text: ""
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "Position (ms):"
                }
                Label {
                    id: currentPosition
                    text: ""
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    id: volUp
                    text: "Vol Up"
                    onClicked: {
                        nowPlayingController.volumeUp();
                    }
                }

                Button {
                    id: volDown
                    text: "Vol Down"
                    onClicked: {
                        nowPlayingController.volumeDown();
                    }
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    id: play
                    text: "Play"
                    onClicked: {
                        nowPlayingController.play();
                    }
                }
                Button {
                    id: pause
                    text: "Pause"
                    onClicked: {
                        nowPlayingController.pause();
                    }
                }
                Button {
                    id: playPause
                    text: "PlayPause"
                    onClicked: {
                        nowPlayingController.playPause();
                    }
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Button {
                    id: prev
                    text: "Previous"
                    onClicked: {
                        nowPlayingController.previous();
                    }
                }
                Button {
                    id: next
                    text: "Next"
                    onClicked: {
                        nowPlayingController.next();
                    }
                }
            }
            Container {
                topPadding: 10
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "Play State:"
                }
                Label {
                    id: playState
                    text: ""
                }
            }
        }
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
 * @since BlackBerry 10.2.0
 */
class BB_MULTIMEDIA_EXPORT NowPlayingController
 : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents duration of track being played in milliseconds.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QVariant duration READ durationQml NOTIFY durationChanged FINAL)

    /*!
     * @brief Represents a flag if more tacks are availalble.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool nextEnabled READ isNextEnabled NOTIFY nextEnabledChanged)

    /*!
     * @brief Represents a flag if preceeding tracks are available.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool previousEnabled READ isPreviousEnabled NOTIFY previousEnabledChanged)

    /*!
     * @brief Represents a value of the media play state.
     *
     * @details Out of all MediaState values there should be only three:
     * Stopped, Paused, and Started.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::multimedia::MediaState::Type mediaState READ mediaState NOTIFY mediaStateChanged FINAL)

    /*!
     * @brief Represents metadata of the track being played
     *
     * @details The metadata is presented as QVariableMap.
     * Use bb::multimedia::MetaData strings to extract required fields.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QVariantMap metaData READ metaData NOTIFY metaDataChanged FINAL)

    /*!
     * @brief Represents the current position, in milliseconds, of the track being played.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QVariant position READ positionQml NOTIFY positionChanged FINAL)

    /*!
     * @brief Represents the current album art location Uri.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QUrl iconUrl READ iconUrl NOTIFY iconUrlChanged FINAL)

    /*!
     * @brief Represents the current repeat mode for an active player.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::multimedia::RepeatMode::Type repeatMode READ repeatMode NOTIFY repeatModeChanged);

    /*!
     * @brief Represents the current shuffle mode for an active player.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::multimedia::ShuffleMode::Type shuffleMode READ shuffleMode NOTIFY shuffleModeChanged);

public:

    /*!
     * @brief @c %NowPlayingController class constructor.
     *
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.2.0
     */
    explicit NowPlayingController(QObject *parent = 0);

    /*!
     * @brief @c %NowPlayingController class destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~NowPlayingController();

    /*!
     * @brief Used to determine the track duration.
     *
     * @return Returns a number representing the duration in milliseconds of
     * the track being played.
     *
     * @since BlackBerry 10.2.0
     */
    unsigned int duration() const;

    /*!
     * @brief Used to determine the track position.
     *
     * @return Returns a number representing the current playback position
     * in milliseconds of the track being played.
     *
     * @since BlackBerry 10.2.0
     */
    unsigned int position() const;

    /*!
     * @brief Used to get a flag indicating if there are more tracks available.
     *
     * @return boolean. Returns @c true when enabled, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isNextEnabled() const;

    /*!
     * @brief Used to get a flag indicating if any preceding track available.
     *
     * @return boolean. Returns @c true when enabled, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isPreviousEnabled() const;

    /*!
     * @brief Used to determine the metadata of the track being played.
     *
     * @return Returns an object containing the metadata associated with
     * the connection that is currently playing.
     *
     * @since BlackBerry 10.2.0
     */
    QVariantMap metaData() const;

    /*!
     * @brief Used to determine the current state of media player.
     *
     * @return Returns state of the player - started, paused, stopped.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaState::Type mediaState() const;

    /*!
     * @brief Used to determine the album art uri.
     *
     * @return Returns album art uri.
     *
     * @since BlackBerry 10.2.0
     */
    QUrl iconUrl() const;

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
     * @brief This method causes the content that is currently playing to advance
     * its playing position. This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type forward();

    /*!
     * @brief This method is used to set the value of mute to On or Off.
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @param muted Boolean value to represent the required mute state.
     * This value is set to @c true for mute, and to @c false to cancel mute.
     *
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type setMute(bool muted);

    /*!
     * @brief This method sends @c next commmand for advancing playback to the next track.
     *
     * @details If the media source is a playlist, this function will move to the
     * next track.
     *
     * If the media source is not a playlist then calling this function does
     * nothing.
     *
     * Regrdless of the flag 'NextEnabled' the command is passed on successfully
     * and in case if 'NextEnabled' flag is set to @c false the command is ignored.
     *
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type next();

    /*!
     * @brief This method sends @c previous command for returning playback to the previous track.
     *
     * @details If the media source is a playlist, this function will move to the
     * previous track.
     *
     * Regrdless of the flag 'PreviousEnabled' the command is passed on successfully
     * and in case if 'PreviousEnabled' flag is set to @c false the command is ignored.
     *
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type previous();

    /*!
     * @brief This method sends @c play command to begin playback of selected track.
     *
     * @details This function will start playback of a track. Successful playback
     * may emit a @c mediaStateChanged signal with state value set to @c started.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type play();

    /*!
     * @brief This method sends @c playPause command to toggle playback from play mode to pause mode, or vice versa.
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type playPause();

    /*!
     * @brief This method sends @c pause command to pause the playback of the current track.
     *
     * @details On success a @c mediaStateChanged signal may be emitted with value @c paused.
     * Call @c play() to restart playback.
     *
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type pause();

    /*!
     * @brief This method causes the content that is currently playing to
     * toggle repeat modes. This command has no effect if the player has not
     * been acquired or if the player does not support the command.
     *
     * @details If a player handled the repeat notification it will result in a
     * @c repeatModeChanged() signal.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.0
     */
    bb::multimedia::MediaError::Type repeat();

    /*!
     * @brief This method causes the content that is currently playing to
     * change the repeat mode. This command has no effect if the player has not
     * been acquired or if the player does not support the command.
     *
     * @details If a player handled the repeat notification it will result in a
     * @c repeatModeChanged() signal.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    bb::multimedia::MediaError::Type repeat(bb::multimedia::RepeatMode::Type repeatMode);

    /*!
     * @brief This method causes the content that is currently playing to move its playing
     * position backwards. This command has no effect if the player has not been acquired or
     * if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type rewind();

    /*!
     * @brief This method causes the content that is currently playing to
     * toggle shuffle modes. This command has no effect if the player has not
     * been acquired or if the player does not support the command.
     *
     * @details If a player handled the shuffle notification it will result in a
     * @c shuffleModeChanged() signal.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.0
     */
    bb::multimedia::MediaError::Type shuffle();

    /*!
     * @brief This method causes the content that is currently playing to
     * change the shuffle mode. This command has no effect if the player has not
     * been acquired or if the player does not support the command.
     *
     * @details If a player handled the shuffle notification it will result in a
     * @c shuffleModeChanged() signal.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    bb::multimedia::MediaError::Type shuffle(bb::multimedia::ShuffleMode::Type shuffleMode);

    /*!
     * @brief This method sends @c stop command to terminate the playback or recording of the current track.
     *
     * @details This function will move the player into the stopped state.
     * Calling @c play() will result in the media commencing playing back
     * from the start. This function may result in the @c mediaStateChanged signal
     * being emitted with value @c stopped.
     *
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type stop();

    /*!
     * @brief This method increases volume level by one step.
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type volumeUp();

    /*!
     * @brief This method reduces volume level by one step.
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type volumeDown();

    /*!
     * @brief This method sets the volume method to the given value.
     * This command has no effect if the player has not been acquired
     * or if the player does not support the command.
     *
     * @param value Any value between 0.0 and 1.0 where 0.0 represents no volume at all,
     * and 1.0 represents the maximum volume possible
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::multimedia::MediaError::Type setVolume(double value);

Q_SIGNALS:

    /*!
     * @brief This signal is emitted to indicate a change in the duration of the track.
     *
     * @details Retrieving the duration of some tracks may not be known
     * when the track is changed. This signal will notify of the duration
     * when available.
     *
     * @param duration The value for duration expressed in milliseconds.
     *
     * @since BlackBerry 10.2.0
     */
    void durationChanged(unsigned int duration);
    /*! @cond PRIVATE */
    void durationChanged(const QVariant &duration);
    /*! @endcond */

    /*!
     * @brief This signal is emitted to indicate a change of the album art Uri.
     *
     * @param iconUrl
     *
     * @since BlackBerry 10.2.0
     */
    void iconUrlChanged(const QUrl &iconUrl);

    /*!
     * @brief This signal is emitted to indicate a change in the playback state.
     *
     * @param mediaState New media state - started, paused, or stopped
     *
     * @since BlackBerry 10.2.0
     */
    void mediaStateChanged(bb::multimedia::MediaState::Type mediaState);

    /*!
     * @brief This signal is emitted to indicate that new metadata is available.
     *
     * @param metaData Object containing map of string values for the metadata.
     *
     * @since BlackBerry 10.2.0
     */
    void metaDataChanged(const QVariantMap &metaData);

    /*!
     * @brief This signal is emitted to indicate a change in the position
     * of the track that is currently playing.
     *
     * @details This signal will be emitted approximately once per second
     * or when normal status updates occur.
     *
     * @param position The value of the current track's position expressed in milliseconds.
     *
     * @since BlackBerry 10.2.0
     */
    void positionChanged(unsigned int position);
    /*! @cond PRIVATE */
    void positionChanged(const QVariant &position);
    /*! @endcond */

    /*!
     * @brief This signal is emitted on notification that flag indicating
     * availability of the next track has changed.
     *
     * @param nextEnabled This value is @c true when next track is available, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void nextEnabledChanged(bool nextEnabled);

    /*!
     * @brief This signal is emitted on notification that flag indicating
     * availability of the preceding track has changed.
     *
     * @param prevEnabled This value is @c true when preceding track is available, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void previousEnabledChanged(bool prevEnabled);

    /*!
     * @brief This signal is emitted when the player repeat value has changed.
     *
     * @param repeatMode The new repeat value that the player has changed to.
     *
     * @since BlackBerry 10.3.0
     */
    void repeatModeChanged(bb::multimedia::RepeatMode::Type repeatMode);

    /*!
     * @brief This signal is emitted to indicate that the track currently playing has changed.
     *
     * @details This is a light notification for delimiting tracks, which could be
     * used for performance reasons instead of @c metaDataChanged().
     *
     * @since BlackBerry 10.2.0
     */
    void trackChanged();

    /*!
     * @brief This signal is emitted when the player shuffle value has changed.
     *
     * @param repeatMode The new shuffle value that the player has changed to.
     *
     * @since BlackBerry 10.3.0
     */
    void shuffleModeChanged(bb::multimedia::ShuffleMode::Type shuffleMode);

protected:
    /*! @cond PRIVATE */
    virtual void connectNotify(const char * signal);
    virtual void disconnectNotify(const char *signal);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    NowPlayingControllerPrivate * const d_ptr;
    Q_DISABLE_COPY(NowPlayingController)
    Q_DECLARE_PRIVATE(NowPlayingController);

    QVariant durationQml() const;
    QVariant positionQml() const;
    /*! @endcond */
};

}; // namespace multimedia
}; // namespace bb

QML_DECLARE_TYPE(bb::multimedia::NowPlayingController)

#endif /* BB_MULTIMEDIA_NOWPLAYINGCONTROLLER_HPP */

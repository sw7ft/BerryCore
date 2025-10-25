/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_AUDIORECORDER_HPP
#define BB_MULTIMEDIA_AUDIORECORDER_HPP

#include <bb/multimedia/AudioChannelConfiguration>
#include <bb/multimedia/DeviceMode>
#include <bb/multimedia/Global>
#include <bb/multimedia/MediaError>
#include <bb/multimedia/MediaState>

#include <QtDeclarative/QtDeclarative>
#include <QObject>
#include <QUrl>

namespace bb
{
namespace multimedia
{

class AudioRecorderPrivate;

/*!
 * @headerfile AudioRecorder.hpp <bb/multimedia/AudioRecorder>
 *
 * @brief The @c %AudioRecorder class provides the ability to record audio.
 *
 * A recording example in C++:
 *
 * @code
        bb::multimedia::AudioRecorder recorder;
        recorder.setOutputUrl("file:///accounts/1000/shared/voice/recording.m4a");
        recorder.record();
        ...
        recorder.reset();
 * @endcode
 *
 * A recording example in QML:
 *
 * @code
    import bb.multimedia 1.0
    // ...

    Page {
        Container {
            // ...
            attachedObjects: [
                AudioRecorder {
                    id: audioRecorder
                    outputUrl: "file:///accounts/1000/shared/voice/recording.m4a"
                }
            ]

            Button {
                id: btnRecord
                text: "Record"
                onClicked: {
                    audioRecorder.record();
                }
            }

            Button {
                id: btnStopRecord
                text: "Stop Recording"
                onClicked: {
                    audioRecorder.reset();
                }
            }
        }
    }
 * @endcode
 *
 * @permissions The application must have the @c record_audio permission to
 * access the microphone on the device. No other special permission is needed
 * to record to a file in the application sandbox. Recording to the shared
 * content area on the device would require the @c access_shared permission.
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/Audio"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT AudioRecorder : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the audio channel configuration.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY(bb::multimedia::AudioChannelConfiguration::Type audioChannelConfiguration READ audioChannelConfiguration WRITE setAudioChannelConfiguration NOTIFY audioChannelConfigurationChanged REVISION 4 FINAL)

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
     * @brief Represents the device mode of the recorder.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY(bb::multimedia::DeviceMode::Type deviceMode READ deviceMode REVISION 4 CONSTANT FINAL)

    /*!
     * @brief Represents the length of the audio recording.
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
     * @brief Represents the last runtime error code that was emitted
     * from the @c error() signal.
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
     * @brief Represents the output URL that will be used to store
     * the audio recording.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl outputUrl READ outputUrl WRITE setOutputUrl)

    /*!
     * @brief Represents the requested amount of time in milliseconds between
     * regular status updates. Generally this setting is applied to duration
     * signals.
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

public:

    /*!
     * @brief @c %AudioRecorder class constructor.
     *
     * @param parent An optional parameter to specify the parent of this
     * @c QObject.
     *
     * @since BlackBerry 10.0.0
     */
    explicit AudioRecorder(
            QObject *parent = 0);

    /*!
     * @brief @c %AudioRecorder class destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~AudioRecorder();

    /*!
     * @brief Returns the audio channel configuration.
     *
     * @return Returns the audio channel configuration value.
     *
     * @since BlackBerry 10.3.1
     */
    bb::multimedia::AudioChannelConfiguration::Type audioChannelConfiguration() const;

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
     * @brief Retrieves the device mode for the recorder.
     *
     * @return @c DeviceMode::Capture
     *
     * @since BlackBerry 10.3.1
     */
    bb::multimedia::DeviceMode::Type deviceMode() const;

    /*!
     * @brief Provides the duration of the current recording.
     *
     * @details The duration is available once @c prepare() has been
     * successfully called. The duration is no longer available once
     * @c stop() has been called. In any other case, a duration of zero
     * is returned.
     *
     * @return Returns the duration of the current recording in milliseconds
     * once determined, and zero otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int duration() const;

    /*!
     * @brief Used to retrieve the last recording error.
     *
     * @details If the @c error() signal has been emitted, this
     * property will return the last error type, otherwise
     * @c MediaError::None is returned. This property is
     * automatically reset to @c MediaError::None when
     * recording starts.
     *
     * @return Returns the last recording error.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type mediaError() const;

    /*!
     * @brief Used to determine the current media state.
     *
     * @details @c MediaState::Unprepared is returned when @c prepare() has not
     * been called, or if the recording has been stopped. When recording,
     * @c MediaState::Started is returned. When paused, @c MediaState::Paused
     * is returned.
     *
     * @return Returns the current media state.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaState::Type mediaState() const;

    /*!
     * @brief Retrieves the output URL.
     *
     * @details This function retrieves the URL, as an absolute path, for the
     * output of the recorder. An empty @c QUrl is returned when @c setOutputUrl()
     * has not been called.
     *
     * @return Returns the URL, as an absolute path, for the output of the
     * recording, or an empty @c QUrl if @c setOutputUrl() has not been called.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl outputUrl() const;

    /*!
     * @brief Sets the handle of an externally managed audio manager.
     *
     * @details Changing this property while the recorder is prepared will
     * cause the player to unprepare. Setting an audio manager handle of zero
     * will reset to the default audio manager.  The original owner of the
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
     * @brief Represents the requested amount of time in milliseconds between
     * regular status updates.
     *
     * @details Generally this setting is applied to @c duration updates.
     * By default the requested update status interval is 1000 milliseconds.
     *
     * @return Returns the current requested status interval in milliseconds, as
     * described by @c setStatusInterval().
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int statusInterval() const;

public Q_SLOTS:

    /*!
     * @brief Pauses the recording.
     *
     * @details On success, a @c paused() signal is emitted. Call @c record()
     * to restart recording.
     *
     * Calling this function while recording is already paused does nothing.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type pause();

    /*!
     * @brief Starts recording to the output.
     *
     * @details This function will start the recording. The recorder will acquire
     * the necessary resources for recording, and emit a @c prepared()
     * signal. A @c recording() signal is emitted while recording.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type record();

    /*!
     * @brief Acquires the necessary resources for recording without recording
     * the track.
     *
     * @details This process will move the recorder into the prepared state.
     * A @c mediaStateChanged signal with a parameter value of
     * for the recording.
     * If the recorder is already prepared, this call does nothing.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type prepare();

    /*!
     * @brief Releases any resources that are currently held by the recorder,
     * and moves the recorder into the unprepared state.
     *
     * @details This function will release all resources held by the recorder,
     * and result in a @c mediaStateChanged() signal being emitted notifying
     * of the unprepared state. This signal indicates that the recorder is no
     * longer in possession of the resources required to record.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type reset();

    /*!
     * @brief Sets audio channel configuration to use for recording.
     *
     * @details If recording is active when this configuration is set the
     * current recording will stop. When @c record() is called again the
     * new audio channel configuration will be used.
     *
     * @param audioChannelConfiguration The requested audio channel configuration
     * to use.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.3.1
     */
    bb::multimedia::MediaError::Type setAudioChannelConfiguration(bb::multimedia::AudioChannelConfiguration::Type audioChannelConfiguration);

    /*!
     * @brief Used to set the output location for the recording.
     *
     * @details The @c QUrl should point to the location of a local file. This
     * function must be called before calling the @c prepare() function.
     *
     * @param url The output location of the audio recording.
     *
     * @since BlackBerry 10.0.0
     */
    void setOutputUrl(const QUrl &url);

    /*!
     * @brief Sets the requested amount of time in milliseconds between regular
     * status updates.
     *
     * Generally this setting is applied to @c duration signals.
     *
     * @param statusInterval The requested status interval in milliseconds.
     *
     * @return Returns @c MediaError::None on success, otherwise a specific
     * media error code.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::MediaError::Type setStatusInterval(unsigned int statusInterval);

Q_SIGNALS:

    /*!
     * @brief This signal is emitted when the audio channel configuration value
     * is changed.
     *
     * @param audioChannelConfiguration The requested audio channel configuration
     * to use.
     *
     * @since BlackBerry 10.3.1
     */
    Q_REVISION(4)
    void audioChannelConfigurationChanged(bb::multimedia::AudioChannelConfiguration::Type audioChannelConfiguration);

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
     * @brief This signal is emitted when the track duration is known.
     *
     * @details When a track is changed, the duration of that track is not
     * known immediately. This signal is emitted when the duration of the
     * tracks is available.
     *
     * @param duration The duration of the track in milliseconds.
     *
     * @since BlackBerry 10.0.0
     */
    void durationChanged(unsigned int duration);
    /*! @cond PRIVATE */
    void durationChanged(const QVariant &duration);
    /*! @endcond */

    /*!
     * @brief This signal is emitted when an error occurs during any operation
     * on the @c %AudioRecorder.
     *
     * @details When an error occurs during a recording, this signal is emitted
     * with the error code, as well as the position in the recording where the
     * error occurred.
     *
     * @param mediaError The recording media error.
     * @param position The position of the recorder where the error occurred.
     *
     * @since BlackBerry 10.0.0
     */
    void error(bb::multimedia::MediaError::Type mediaError, unsigned int position);
    /*! @cond PRIVATE */
    void error(bb::multimedia::MediaError::Type mediaError, const QVariant &position);
    /*! @endcond */

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
     * @brief This signal is emitted when the level of content being recorded
     * changes.
     *
     * @details This is a percentage of the total volume available to the
     * recording. For example, if the sound input to the microphone is
     * loud while recording, then this value will be high. If the sound
     * input to the microphone is quiet while recording, then this value
     * will be low.
     *
     * @param percentage The sound input volume expressed as a value between
     * 0.0 and 1.0 where 0.0 is silent and 1.0 is the maximum sound input.
     *
     * @since BlackBerry 10.0.0
     */
    void recordingLevelChanged(double percentage);

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

private:
    /*! @cond PRIVATE */
    AudioRecorderPrivate *d_ptr;
    Q_DECLARE_PRIVATE(AudioRecorder)
    Q_DISABLE_COPY(AudioRecorder)

    QVariant audioManagerHandleQml() const;
    QVariant durationQml() const;
    QVariant statusIntervalQml() const;
    void setAudioManagerHandleQml(const QVariant &handle);
    void setStatusIntervalQml(const QVariant &statusIntervalQml);
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::AudioRecorder)

#endif /* BB_MULTIMEDIA_AUDIORECORDER_HPP */

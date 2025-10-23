/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_SYSTEMSOUND_HPP
#define BB_MULTIMEDIA_SYSTEMSOUND_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

class SystemSoundPrivate;

/*!
 * @headerfile SystemSound.hpp <bb/multimedia/SystemSound>
 *
 *
 * @brief The @c %SystemSound class provides access to play system-defined sounds.
 *
 * @details This class is targeted at GUI applications that wish to play asynchronous sounds
 * as the platform does (for example, a camera 'shutter' sound when a picture is taken with the
 * device camera).
 *
 * A static @c play() function is provided to asynchronously play a system-defined sound file.
 *
 * @code
       bb::multimedia::SystemSound::play(bb::multimedia::SystemSound::CameraShutterEvent);
 * @endcode
 *
 * Use this function when a single 'one-off' sound is needed, such as an alert when presenting an
 * informational dialog. In this case the sound is automatically prepared and played.
 *
 * Secondly, a @c %SystemSound instance can be created to play a sound several times repeatedly.
 *
 * @code
       SystemSound keypress(bb::multimedia::SystemSound::InputKeypress);
       keypress.play();
       keypress.play(); // again
 * @endcode
 *
 * Thirdly, a @c %SystemSound instance can be used from QML.
 *
 * @code
    import bb.multimedia 1.0
    // ...

    Page {
        Container {
            // ...

            attachedObjects: [
                SystemSound {
                    id: systemSound
                    sound: SystemSound.CameraShutterEvent;
                }
            ]

            Button {
                text: "Play Camera Shutter Sound"
                onClicked: {
                    systemSound.play();
                }
            }
        }
    }
 * @endcode
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
class BB_MULTIMEDIA_EXPORT SystemSound : public QObject {

    Q_OBJECT

    Q_ENUMS(Type)

    /*!
	 * @brief Represents any of the enumerated sound types.
	 *
	 * @details This property allows the user to change the system sound played
     * when @c play() is called.
     *
     * @since BlackBerry 10.0.0
	 */
    Q_PROPERTY(bb::multimedia::SystemSound::Type sound READ sound WRITE setSound FINAL)

public:

    /*!
     * @enum Type
     *
     * @brief Represents various platform system sounds.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Default sound state when no sound has been set.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief Battery alarm sound.
         *
         * @since BlackBerry 10.0.0
         */
        BatteryAlarm = 1,

        /*!
         * @brief Browser startup sound.
         *
         * @since BlackBerry 10.0.0
         */
        BrowserStartEvent = 2,

        /*!
         * @brief Camera shutter sound when taking a still photograph.
         *
         * @since BlackBerry 10.0.0
         */
        CameraShutterEvent = 3,

        /*!
         * @brief Device has been locked sound.
         *
         * @since BlackBerry 10.0.0
         */
        DeviceLockEvent = 4,

        /*!
         * @brief Device has been unlocked sound.
         *
         * @since BlackBerry 10.0.0
         */
        DeviceUnlockEvent = 5,

        /*!
         * @brief Device has been tethered with another device sound.
         *
         * @since BlackBerry 10.0.0
         */
        DeviceTetherEvent = 6,

        /*!
         * @brief Device has been untethered with another device sound.
         *
         * @since BlackBerry 10.0.0
         */
        DeviceUntetherEvent = 7,

        /*!
         * @brief General notification dialog sound.
         *
         * @since BlackBerry 10.0.0
         */
        GeneralNotification = 8,

        /*!
         * @brief A Virtual Keyboard key press sound.
         *
         * @since BlackBerry 10.0.0
         */
        InputKeypress = 9,

        /*!
         * @brief Start of a recording sound.
         *
         * @since BlackBerry 10.0.0
         */
        RecordingStartEvent = 10,

        /*!
         * @brief End of a recording sound.
         *
         * @since BlackBerry 10.0.0
         */
        RecordingStopEvent = 11,

        /*!
         * @brief BlackBerry Bridge notification sound.
         *
         * @since BlackBerry 10.0.0
         */
        SapphireNotification = 12,

        /*!
         * @brief The sound played when master volume is changed.
         *
         * @since BlackBerry 10.0.0
         */
        SystemMasterVolumeReference = 13,

        /*!
         * @brief Incoming video call notification sound.
         *
         * @since BlackBerry 10.0.0
         */
        VideoCallEvent = 14,

        /*!
         * @brief Outgoing video call notification sound.
         *
         * @since BlackBerry 10.0.0
         */
        VideoCallOutgoingEvent = 15,

        /*!
         * @brief Camera burst sound when taking multiple still photographs.
         *
         * @since BlackBerry 10.0.0
         */
        CameraBurstEvent = 16,
    };

    /*!
	 * @brief Constructs a new @c %SystemSound object to play a system-defined sound.
	 *
	 * @details The @c sound parameter is one of the @c SystemSound::Type enum values. An example
	 * of a system-defined sound is the sound heard when a system notification dialog appears.
	 *
	 * @param sound A @c SystemSound::Type enum value denoting the sound to play.
	 *
	 * @param parent An optional parameter to specify the parent of this @c QObject.
     *
     * @since BlackBerry 10.0.0
	 */
	explicit SystemSound(bb::multimedia::SystemSound::Type sound, QObject *parent = 0);

	/*!
     * @brief Constructs a new @c %SystemSound object.
     *
     * @details The sound to be played defaults to the None sound. Unless a different @c sound
     * property is specified, calls to @c play() do nothing.
     *
     * @param parent An optional parameter to specify the parent of this @c QObject.
	 *
	 * @since BlackBerry 10.0.0
     */
    explicit SystemSound(QObject *parent = 0);

    /*!
     * @brief @c %SystemSound destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SystemSound();

    /*!
	 * @brief Plays the default system-defined sound specified by the given
	 * @c SystemSound::Type value.
	 *
	 * @param sound A @c SystemSound::Type enum value denoting the sound to play.
     *
     * @since BlackBerry 10.0.0
	 */
	static void play(const bb::multimedia::SystemSound::Type sound);

    /*!
     * @brief Associates a new sound.
     *
     * @param sound A @c SystemSound::Type enum value denoting the sound to play.
     *
     * @return @c true if the new sound was set and loaded, @c false otherwise
     *
     * @since BlackBerry 10.0.0
     */
    bool setSound(bb::multimedia::SystemSound::Type sound);

    /*!
     * @brief Retrieves the sound that's associated with this object.
     *
     * @return The sound associated with this object.
     *
     * @since BlackBerry 10.0.0
     */
    bb::multimedia::SystemSound::Type sound() const;

public Q_SLOTS:

    /*!
     * @brief Plays the default system-defined sound specified by the given
     * @c SystemSound::Type value.
     *
     * @since BlackBerry 10.0.0
     */
    void play();

private:
    /*! @cond PRIVATE */
    SystemSoundPrivate *d_ptr;
    Q_DECLARE_PRIVATE(SystemSound)
    Q_DISABLE_COPY(SystemSound)
    /*! @endcond */
};

} // multimedia
} // bb

QML_DECLARE_TYPE(bb::multimedia::SystemSound)

#endif /* BB_MULTIMEDIA_SYSTEMSOUND_HPP */

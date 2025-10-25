/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_keyevent_h
#define cascades_keyevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>

#include <bb/cascades/core/event.h>
#include <bb/cascades/core/keymodifier.h>

namespace bb {
    namespace cascades {

    class KeyEventPrivate;

    /*! 
     * @brief An event indicating that a key has been pressed or released.
     *
     * The event provides the key that generated the event and 
     * press/release information ( @c keycap, @c key, @c pressed, @c duration properties).
     * It also provides information about modifiers that were pressed
     * along with the key ( @c altPressed, @c shiftPressed, @c ctrlPressed properties).
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.1.0
     */
    class BBCASCADES_EXPORT KeyEvent : public Event {
        Q_OBJECT

        /*!
         * @brief A static code corresponding to each physical key on the keyboard.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(int keycap READ keycap FINAL CONSTANT)
        /*!
         * @brief An integer corresponding to the unicode of the key being pressed.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(int key READ key FINAL CONSTANT)
        /*!
         * @brief The unicode character of the key pressed to generate the event.
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(QString unicode READ unicode REVISION 2 FINAL CONSTANT)
        /*!
         * @brief The length of time in milliseconds that the key has been held down.
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(int duration READ duration REVISION 2 FINAL CONSTANT)
        /*!
         * @brief A Boolean expression indicating whether the key was pressed or released.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bool pressed READ isPressed FINAL CONSTANT)
        /*!
         * @brief A Boolean expression indicating whether the Alt modifier key was pressed while the key was pressed.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bool altPressed READ isAltPressed FINAL CONSTANT)
        /*!
         * @brief A Boolean expression indicating whether the Shift modifier key was pressed while the key was pressed.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bool shiftPressed READ isShiftPressed FINAL CONSTANT)
        /*!
         * @brief A Boolean expression indicating whether the Control modifier key was pressed while the key was pressed.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bool ctrlPressed READ isCtrlPressed FINAL CONSTANT)

    public:
        /*!
         * @brief Constructs a key event.
         *
         * @param key The key pressed to generate the event.
         * @param isPressed @c true if the user is pressing the key, @c false if the user is releasing the key.
         * @param isAltPressed @c true if the alt modifier key was pressed during the event, @c false otherwise.
         * @param isShiftPressed @c true if the shift modifier key was pressed during the event, @c false otherwise.
         * @param isCtrlPressed @c true if the ctrl modifier key was pressed during the event, @c false otherwise.
         * @deprecated Use @c KeyEvent(int keycap, int key, bool isPressed, bool isAltPressed, bool isShiftPressed, bool isCtrlPressed, int duration) instead.
         *
         * @since BlackBerry 10.1.0
         */
        KeyEvent(int key, bool isPressed, bool isAltPressed, bool isShiftPressed, bool isCtrlPressed);

        /*!
         * @brief Constructs a key event.
         *
         * @param keycap The keycap value for the key pressed to generate the event.
         * @param key The key pressed to generate the event.
         * @param isPressed @c true if the user is pressing the key, @c false if the user is releasing the key.
         * @param isAltPressed @c true if the alt modifier key was pressed during the event, @c false otherwise.
         * @param isShiftPressed @c true if the shift modifier key was pressed during the event, @c false otherwise.
         * @param isCtrlPressed @c true if the ctrl modifier key was pressed during the event, @c false otherwise.
         * @deprecated Use @c KeyEvent(int keycap, int key, bool isPressed, bool isAltPressed, bool isShiftPressed, bool isCtrlPressed, int duration) instead.
         *
         * @since BlackBerry 10.1.0
         */
        KeyEvent(int keycap, int key, bool isPressed, bool isAltPressed, bool isShiftPressed, bool isCtrlPressed);

        /*!
         * @brief Constructs a key event.
         *
         * @param keycap The keycap value for the key pressed to generate the event.
         * @param key The key pressed to generate the event.
         * @param isPressed @c true if the user is pressing the key, @c false if the user is releasing the key.
         * @param isAltPressed @c true if the alt modifier key was pressed during the event, @c false otherwise.
         * @param isShiftPressed @c true if the shift modifier key was pressed during the event, @c false otherwise.
         * @param isCtrlPressed @c true if the ctrl modifier key was pressed during the event, @c false otherwise.
         * @param duration the length of time in milliseconds that the key has been held down.
         *
         * @since BlackBerry 10.2.0
         */
        KeyEvent(int keycap, int key, bool isPressed, bool isAltPressed, bool isShiftPressed, bool isCtrlPressed, int duration);

        /*!
         * @brief Destructs the event.
         *
         * @since BlackBerry 10.1.0
         */
        virtual ~KeyEvent();

        /*!
         * @brief Retrieves the keycap value for the key pressed to generate the event.
         *
         * @return The keycap value for the key pressed to generate the event. It is a static code for each key on the keyboard.
         *
         * @since BlackBerry 10.1.0
         */
        int keycap() const;

        /*!
         * @brief Retrieves the key pressed to generate the event which reflects the modifiers pressed and keypad variant.
         *
         * @return The key pressed to generate the event.
         *
         * @since BlackBerry 10.1.0
         */
        int key() const;

       /*!
         * @brief Retrieves the unicode value of the key pressed to generate the event.
         *
         * @return The unicode value of the key pressed to generate the event.
         */
        QString unicode() const;

        /*!
         * @brief Retrieves the length of time in milliseconds that the key has been held in a pressed state.
         *
         * @return The length of time in milliseconds that the key has been held in a pressed state.
         */
        int duration() const;

        /*!
         * @brief Retrieves the press/release state of the key event.
         *
         * @return @c true if the user pressed the key, and @c false if the user released the key.
         *
         * @since BlackBerry 10.1.0
         */
        bool isPressed() const;

        /*!
         * @brief Retrieves the alt modifier key state during the event.
         *
         * @return @c true if the alt modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.1.0
         */
        bool isAltPressed() const;

        /*!
         * @brief Retrieves the shift modifier key state during the event.
         *
         * @return @c true if the shift modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.1.0
         */
        bool isShiftPressed() const;

        /*!
         * @brief Retrieves the ctrl modifier key state during the event.
         *
         * @return @c true if the ctrl modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.1.0
         */
        bool isCtrlPressed() const;

         /*!
         * @brief Converts keycap value to unicode symbol based on passed modifiers.
         * For example applying 'Shift' modifier to keycap 'a' gives 'A', applying
         * 'Alt' modifier to keycap 'a' gives '#' symbol. Conversion keycap 'a' to 'azerty'
         * keyboard layout returns 'q' and so on.
         *
         * @param modifiers The modifiers need be applied to capcode.

         * @return The unicode symbol based on keycap value with applied modifier.
         *
         * @since BlackBerry 10.2.0
         */
        Q_REVISION(2)
        Q_INVOKABLE QString toUnicode(bb::cascades::KeyModifier::Types modifiers) const;

        /*! @cond PRIVATE */
        Q_REVISION(2)
        Q_INVOKABLE QString toUnicode(int modifiers) const;
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(KeyEvent)
        Q_DISABLE_COPY(KeyEvent)
        /*! @endcond */
    };

    /* @brief Streams debug output about a @c KeyEvent to the @c QDebug stream object.
     *
     * @param deb The @c QDebug Stream.
     * @param keyEvent The @c KeyEvent to output debug information about.
     * 
     * @return The @c QDebug stream.
     *
     * @since BlackBerry 10.1.0
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const KeyEvent &keyEvent);

}
}

QML_DECLARE_TYPE(bb::cascades::KeyEvent)

#endif /* cascades_keyevent_h */

/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_a11ystate_h
#define cascades_a11ystate_h

#include <QObject>
#include <bb/cascades/bbcascades_global.h>

namespace bb
{
namespace cascades
{

/*!
 * @brief Represents different accessible states which specifies
 * the state of an accessible control through its accessibility
 * object.
 *
 * @see @c CustomA11yObject::state
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT A11yState {
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief Specifies the accessible control states for an accessibility object.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief The accessible control is currently the active window.
         *
         * Unless it has this state, the window is assumed to not be the
         * active window.
         *
         * @since BlackBerry 10.2.0
         */
        Active = 0,
        /*!
         * @brief The accessible control's appearance changes rapidly or
         * constantly.
         *
         * Unless it has this state, the accessible control is assumed to be not
         * animated.
         *
         * @since BlackBerry 10.2.0
         */
        Animated = 1,
        /*!
         * @brief The accessible control cannot accept input at this time.
         *
         * For example, a browser might be busy loading a page or a
         * form might be busy with a database query. Unless it has
         * this state, the accessible control is assumed to not be busy.
         *
         * @since BlackBerry 10.2.0
         */
        Busy = 2,
        /*!
         * @brief The accessible control is checkable.
         *
         * The standard checkable objects are check boxes, radio
         * buttons, check box menu items, radio menu items and toggle
         * buttons. Unless it has this state, the accessible control is
         * assumed to not be checkable. If the accessible control
         * has state @c bb::cascades::A11yState::Checkable, but
         * neither @c bb::cascades::A11yState::Checked
         * nor @c bb::cascades::A11yState::Mixed, it is assumed to be
         * unchecked.
         *
         * @since BlackBerry 10.2.0
         */
        Checkable = 3,
        /*!
         * @brief The accessible control's check box is checked (and must also
         * be @c bb::cascades::A11yState::Checkable).
         *
         * If the accessible control has state @c bb::cascades::A11yState::Checkable,
         * but neither @c bb::cascades::A11yState::Checked
         * nor @c bb::cascades::A11yState::Mixed, it is assumed to be
         * unchecked.
         *
         * @since BlackBerry 10.2.0
         */
        Checked = 4,
        /*!
         * @brief The accessible control is the default control for the focused
         * window.
         *
         * The default control is the control that is activated when some
         * common user input event (e.g., pressing the "Enter" key)
         * happens. Unless it has this state, the accessible control is assumed to
         * not be the default control.
         *
         * @since BlackBerry 10.2.0
         */
        DefaultControl = 5,
        /*!
         * @brief The accessible control is no longer usable in the framework and
         * making any method calls using this accessible control could result in
         * a crash or unexpected behavior.
         *
         * @since BlackBerry 10.2.0
         */
        Defunct = 6,
        /*!
         * @brief The accessible control is disabled (i.e. It's grayed out).
         *
         * The absence of this state implies the control is enabled. Do
         * not confuse this with @c bb::cascades::A11yState::ReadOnly.
         *
         * @since BlackBerry 10.2.0
         */
        Disabled = 7,
        /*!
         * @brief The accessible control can be expanded or collapsed, such as
         * with a progressive disclosure container or a tree node.
         *
         * Unless this state is present, it is assumed that the accessible control is
         * not expandable.
         *
         * @see bb::cascades::A11yState::Expanded
         *
         * @since BlackBerry 10.2.0
         */
        Expandable = 8,
        /*!
         * @brief The accessible control is expanded (and must also
         * be @c bb::cascades::A11yState::Expandable).
         *
         * Unless this state is present, it is assumed that the accessible control is
         * not expanded.
         *
         * @since BlackBerry 10.2.0
         */
        Expanded = 9,
        /*!
         * @brief The accessible control is on the active window and is ready to
         * receive keyboard focus.
         *
         * Unless this state is present, it is assumed that the accessible control is
         * not focusable.
         *
         * @see bb::cascades::A11yState::Focused
         *
         * @since BlackBerry 10.2.0
         */
        Focusable = 10,
        /*!
         * @brief The accessible control has the keyboard focus (and must also
         * be bb::cascades::A11yState::Focusable).
         *
         * Do not confuse focus with selection. Focus is the object that
         * will change with keyboard events, whereas selection is if the
         * object is selected, as in a list item being selected in a list.
         *
         * @see bb::cascades::A11yState::Focusable
         *
         * @since BlackBerry 10.2.0
         */
        Focused = 11,
        /*!
         * @brief Object displays a pop-up menu or window when invoked.
         *
         * @since BlackBerry 10.2.0
         */
        HasPopup = 12,
        /*!
         * @brief The accessible control is programmatically hidden.
         *
         * For example, menu items are programmatically hidden until a
         * user activates the menu. Unless this state is present, the
         * accessible control is not assumed to be programmatically hidden
         * (thought it might be @c bb::cascades::A11yState::OffScreen).
         *
         * @since BlackBerry 10.2.0
         */
        Hidden = 13,
        /*!
         * @brief The accessible control is showing an input validation failure,
         * as in a form entry field where the user typed something
         * invalid.
         *
         * Unless this state is present, the accessible control value is assumed
         * to be valid.
         *
         * @since BlackBerry 10.2.0
         */
        Invalid = 14,
        /*!
         * @brief The accessible control is minimized and represented by an icon.
         *
         * Unless it has this state, the accessible control is assumed to not be
         * iconified.
         *
         * @since BlackBerry 10.2.0
         */
        Iconified = 15,
        /*!
         * @brief The accessible control is @c bb::cascades::A11yState::Checkable, but it
         * is a three-state check whose state is currently not determined
         * (i.e. The check box is neither checked nor unchecked, and is
         * therefore in the third, or mixed, state).
         *
         * If the accessible control has state @c bb::cascades::A11yState::Checkable,
         * but neither @c bb::cascades::A11yState::Checked
         * nor @c bb::cascades::A11yState::Mixed, it is assumed to be
         * unchecked.
         *
         * @since BlackBerry 10.2.0
         */
        Mixed = 16,
        /*!
         * @brief The children of this accessible control are
         * all @c bb::cascades::A11yState::ManagedChild.
         *
         * This is a hint to the assistive technology that hanging onto
         * handles for the children of this accessible control is not supported. A
         * typical example is a list widget that reuses widget instances
         * to draw list items. In this case, there will typically be more list items
         * than there are widgets.
         *
         * @since BlackBerry 10.2.0
         */
        ManagesDescendants = 17,
        /*!
         * @brief Something must be done with this accessible control before the
         * user can interact with objects in another window.
         *
         * Unless this state is present, it is assumed that the accessible control is
         * not modal.
         *
         * @since BlackBerry 10.2.0
         */
        Modal = 18,
        /*!
         * @brief The accessible control can contain multiple lines of text, as in
         * a text entry field where the user can enter comments.
         *
         * Unless it is present, it is assumed that this accessible control can only
         * show a single line of text.
         *
         * @since BlackBerry 10.2.0
         */
        MultiLine = 19,
        /*!
         * @brief The accessible control allows more than one child to be selected
         * at a time.
         *
         * The presence of this state implies (and does not require) that
         * the accessible control also is @c bb::cascades::A11yState::Selectable.
         *
         * @since BlackBerry 10.2.0
         */
        MultiSelectable = 20,
        /*!
         * @brief The accessible control is clipped or scrolled out of view, but
         * not @c bb::cascades::A11yState::Hidden
         *
         * Unless it is @c bb::cascades::A11yState::OffScreen
         * or @c bb::cascades::A11yState::Hidden, the accessible control is assumed to be
         * showing on the screen.
         *
         * @since BlackBerry 10.2.0
         */
        OffScreen = 21,
        /*!
         * @brief The accessible control is laid out horizontally (as in a scroll
         * bar or slider).
         *
         * If neither this state nor @c bb::cascades::A11yState::OrientationVertical are
         * present, it is not assumed that the accessible control can distinguish
         * between horizontal and vertical layout.
         *
         * @since BlackBerry 10.2.0
         */
        OrientationHorizontal = 22,
        /*!
         * @brief The accessible control is laid out vertically (as in a scroll
         * bar or slider).
         *
         * If neither this state nor @c bb::cascades::A11yState::OrientationHorizontal are
         * present, it is not assumed that the accessible control can distinguish
         * between horizontal and vertical layout.
         *
         * @since BlackBerry 10.2.0
         */
        OrientationVertical = 23,
        /*!
         * @brief The accessible control is fixed at a certain location.
         *
         * One example is a browser tab that when pinned cannot be moved
         * until unpinned. Another example is a movable or floating object
         * that when pinned remains in its pinned location until being
         * unpinned.
         *
         * @since BlackBerry 10.2.0
         */
        Pinned = 24,
        /*!
         * @brief The accessible control cannot be edited, as in the content on a
         * web page.
         *
         * The @c bb::cascades::A11yState::ReadOnly state is typically used on text
         * areas that are navigable and allow selection/copying, but which
         * do not allow the user to make changes. Accessibility (A11y) objects that do not
         * have this state are assumed to be interactive objects.
         *
         * @since BlackBerry 10.2.0
         */
        ReadOnly = 25,
        /*!
         * @brief The accessible control requires user input or interaction, such as
         * a field in a form.
         *
         * Unless this state is present, it is assumed that interaction is
         * not required.
         *
         * @since BlackBerry 10.2.0
         */
        Required = 26,
        /*!
         * @brief The accessible control allows its children to be selected.
         *
         * Unless this state is present, it is assumed that the accessible control does
         * not allow its children to be selected.
         *
         * @see bb::cascades::A11yState::MultiSelectable
         * @see bb::cascades::A11yState::Selected
         *
         * @since BlackBerry 10.2.0
         */
        Selectable = 27,
        /*!
         * @brief The text of the accessible control is selectable.
         *
         * @note This is different from @c bb::cascades::A11yState::Selectable, which
         * indicates the children are selectable.
         *
         * @since BlackBerry 10.2.0
         */
        SelectableText = 28,
        /*!
         * @brief The accessible control is the child of an accessible control that allows
         * its children to be selected, and that this child is one of those
         * children that has been selected.
         *
         * @see bb::cascades::A11yState::Selectable
         *
         * @since BlackBerry 10.2.0
         */
        Selected = 29,
        /*!
         * @brief The accessible control supports auto completion.
         *
         * Unless this state is present, it is assumed that the accessible control does
         * not support auto completion.
         *
         * @since BlackBerry 10.2.0
         */
        SupportsAutocompletion = 30,
        /*!
         * @brief The accessible control is not guaranteed to live beyond the
         * current event.
         *
         * This is a hint to the assistive technology that hanging onto
         * handles for the children of accessibility (A11y) objects
         * that @c bb::cascades::A11yState::ManagesDescendants is not supported. A
         * typical example is a list widget that reuses widget instances
         * to draw list items. In this case, there will typically be far more list items
         * than there are widgets.
         *
         * @since BlackBerry 10.2.0
         */
        ManagedChild = 31,
        /*!
         * @brief The accessible control is displaying text that has been
         * truncated visually, such as with ellipses.
         *
         * Unless this state is present, the accessible control's text is assumed
         * to not be truncated.
         *
         * @since BlackBerry 10.2.0
         */
        Truncated = 32,
        /*!
         * @brief The object is a hyper link that has been visited
         * (previously clicked) by a user.
         *
         * @since BlackBerry 10.2.0
         */
        Visited = 33,
        /*!
         * @brief The object is a password-protected edit control.
         *
         * This state is used to indicate that a text entry field
         * will mask the input when the user types. This should only
         * be present when the masking feature is enabled on the
         * text entry field.
         *
         * @since BlackBerry 10.2.0
         */
        PasswordProtected = 34
    };

private:
    /*! @cond PRIVATE */
    A11yState();
    ~A11yState();
    /*! @endcond */
};

}
}
 
#endif // cascades_a11ystate_h

/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_a11ystateholder_h
#define cascades_a11ystateholder_h

#include <bb/cascades/bbcascades_global.h>
 
#include <bb/cascades/BaseObject>
#include <bb/cascades/A11yState>

namespace bb
{
namespace cascades
{

class CustomA11yObject;
class A11yStateHolderPrivate;

/*!
 * @brief Holds the state of an accessibility object.
 * The state is represented by the properties of this object.
 *
 * @see @c CustomA11yObject::state
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT A11yStateHolder : public BaseObject {
    Q_OBJECT

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Active state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool active READ isActive WRITE setActive RESET resetActive NOTIFY activeChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Animated state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated RESET resetAnimated NOTIFY animatedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Busy state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool busy READ isBusy WRITE setBusy RESET resetBusy NOTIFY busyChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Checkable state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool checkable READ isCheckable WRITE setCheckable RESET resetCheckable NOTIFY checkableChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Checked state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked RESET resetChecked NOTIFY checkedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::DefaultControl state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool defaultControl READ isDefaultControl WRITE setDefaultControl RESET resetDefaultControl NOTIFY defaultControlChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Defunct state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool defunct READ isDefunct WRITE setDefunct RESET resetDefunct NOTIFY defunctChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Disabled state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool disabled READ isDisabled WRITE setDisabled RESET resetDisabled NOTIFY disabledChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Expandable state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool expandable READ isExpandable WRITE setExpandable RESET resetExpandable NOTIFY expandableChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Expanded state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded RESET resetExpanded NOTIFY expandedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Focusable state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool focusable READ isFocusable WRITE setFocusable RESET resetFocusable NOTIFY focusableChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Focused state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool focused READ isFocused WRITE setFocused RESET resetFocused NOTIFY focusedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Haspopup state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool hasPopup READ hasPopup WRITE setHasPopup RESET resetHasPopup NOTIFY hasPopupChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Hidden state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool hidden READ isHidden WRITE setHidden RESET resetHidden NOTIFY hiddenChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Invalid state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool invalid READ isInvalid WRITE setInvalid RESET resetInvalid NOTIFY invalidChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Iconified state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool iconified READ isIconified WRITE setIconified RESET resetIconified NOTIFY iconifiedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Mixed state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool mixed READ isMixed WRITE setMixed RESET resetMixed NOTIFY mixedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::ManagesDescendants state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool managesDescendants READ managesDescendants WRITE setManagesDescendants RESET resetManagesDescendants NOTIFY managesDescendantsChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Modal state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool modal READ isModal WRITE setModal RESET resetModal NOTIFY modalChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::MultiLine state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool multiLine READ isMultiLine WRITE setMultiLine RESET resetMultiLine NOTIFY multiLineChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::MultiSelectable state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool multiSelectable READ isMultiSelectable WRITE setMultiSelectable RESET resetMultiSelectable NOTIFY multiSelectableChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::OffScreen state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool offScreen READ isOffScreen WRITE setOffScreen RESET resetOffScreen NOTIFY offScreenChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::OrientationHorizontal state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool orientationHorizontal READ isOrientationHorizontal WRITE setOrientationHorizontal RESET resetOrientationHorizontal NOTIFY orientationHorizontalChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::OrientationVertical state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool orientationVertical READ isOrientationVertical WRITE setOrientationVertical RESET resetOrientationVertical NOTIFY orientationVerticalChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Pinned state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool pinned READ isPinned WRITE setPinned RESET resetPinned NOTIFY pinnedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::ReadOnly state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly RESET resetReadOnly NOTIFY readOnlyChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Required state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool required READ isRequired WRITE setRequired RESET resetRequired NOTIFY requiredChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Selectable state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool selectable READ isSelectable WRITE setSelectable RESET resetSelectable NOTIFY selectableChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::SelectableText state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool selectableText READ isSelectableText WRITE setSelectableText RESET resetSelectableText NOTIFY selectableTextChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Selected state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected RESET resetSelected NOTIFY selectedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::SupportsAutocompletion state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool supportsAutocompletion READ supportsAutocompletion WRITE setSupportsAutocompletion RESET resetSupportsAutocompletion NOTIFY supportsAutocompletionChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::ManagedChild state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool managedChild READ isManagedChild WRITE setManagedChild RESET resetManagedChild NOTIFY managedChildChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Truncated state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool truncated READ isTruncated WRITE setTruncated RESET resetTruncated NOTIFY truncatedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::Visited state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool visited READ isVisited WRITE setVisited RESET resetVisited NOTIFY visitedChanged FINAL);

    /*!
     * @brief Specifies whether the accessible object is currently in the @c A11yState::PasswordProtected state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool passwordProtected READ isPasswordProtected WRITE setPasswordProtected RESET resetPasswordProtected NOTIFY passwordProtectedChanged FINAL);


public:
    /*!
     * @brief Sets the specified state of the accessible control.
     *
     * @param state The state type to set.
     * @param value The new value for the state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void setState(bb::cascades::A11yState::Type state, bool value);


    /*!
     * @brief Indicates whether a particular state is set.
     *
     * @param state The type of the state to get.
     *
     * @return @c true if the state is set, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isStateSet(bb::cascades::A11yState::Type state) const;

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Active state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Active state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isActive() const;

    /*!
     * @brief Sets the @c A11yState::Active state of the accessible object.
     *
     * @param active If @c true the accessible object is in @c A11yState::Active state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setActive(bool active);

    /*!
     * @brief Resets the @c A11yState::Active state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetActive();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Animated state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Animated state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isAnimated() const;

    /*!
     * @brief Sets the @c A11yState::Animated state of the accessible object.
     *
     * @param animated If @c true the accessible object is in @c A11yState::Animated state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setAnimated(bool animated);

    /*!
     * @brief Resets the @c A11yState::Animated state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetAnimated();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Busy state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Busy state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isBusy() const;

    /*!
     * @brief Sets the @c A11yState::Busy state of the accessible object.
     *
     * @param busy If @c true the accessible object is in @c A11yState::Busy state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setBusy(bool busy);

    /*!
     * @brief Resets the @c A11yState::Busy state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetBusy();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Checkable state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Checkable state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isCheckable() const;

    /*!
     * @brief Sets the @c A11yState::Checkable state of the accessible object.
     *
     * @param checkable If @c true the accessible object is in @c A11yState::Checkable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setCheckable(bool checkable);

    /*!
     * @brief Resets the @c A11yState::Checkable state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetCheckable();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Checked state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Checked state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isChecked() const;

    /*!
     * @brief Sets the @c A11yState::Checked state of the accessible object.
     *
     * @param checked If @c true the accessible object is in @c A11yState::Checked state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setChecked(bool checked);

    /*!
     * @brief Resets the @c A11yState::Checked state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetChecked();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::DefaultControl state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::DefaultControl state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isDefaultControl() const;

    /*!
     * @brief Sets the @c A11yState::DefaultControl state of the accessible object.
     *
     * @param defaultControl If @c true the accessible object is in @c A11yState::DefaultControl state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setDefaultControl(bool defaultControl);

    /*!
     * @brief Resets the @c A11yState::DefaultControl state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetDefaultControl();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Defunct state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Defunct state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isDefunct() const;

    /*!
     * @brief Sets the @c A11yState::Defunct state of the accessible object.
     *
     * @param defunct If @c true the accessible object is in @c A11yState::Defunct state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setDefunct(bool defunct);

    /*!
     * @brief Resets the @c A11yState::Defunct state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetDefunct();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Disabled state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Disabled state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isDisabled() const;

    /*!
     * @brief Sets the @c A11yState::Disabled state of the accessible object.
     *
     * @param disabled If @c true the accessible object is in @c A11yState::Disabled state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setDisabled(bool disabled);

    /*!
     * @brief Resets the @c A11yState::Disabled state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetDisabled();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Expandable state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Expandable state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isExpandable() const;

    /*!
     * @brief Sets the @c A11yState::Expandable state of the accessible object.
     *
     * @param expandable If @c true the accessible object is in @c A11yState::Expandable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setExpandable(bool expandable);

    /*!
     * @brief Resets the @c A11yState::Expandable state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetExpandable();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Expanded state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Expanded state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isExpanded() const;

    /*!
     * @brief Sets the @c A11yState::Expanded state of the accessible object.
     *
     * @param expanded If @c true the accessible object is in @c A11yState::Expanded state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setExpanded(bool expanded);

    /*!
     * @brief Resets the @c A11yState::Expanded state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetExpanded();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Focusable state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Focusable state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isFocusable() const;

    /*!
     * @brief Sets the @c A11yState::Focusable state of the accessible object.
     *
     * @param focusable If @c true the accessible object is in @c A11yState::Focusable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setFocusable(bool focusable);

    /*!
     * @brief Resets the @c A11yState::Focusable state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetFocusable();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Focused state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Focused state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isFocused() const;

    /*!
     * @brief Sets the @c A11yState::Focused state of the accessible object.
     *
     * @param focused If @c true the accessible object is in @c A11yState::Focused state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setFocused(bool focused);

    /*!
     * @brief Resets the @c A11yState::Focused state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetFocused();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::HasPopup state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::HasPopup state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool hasPopup() const;

    /*!
     * @brief Sets the @c A11yState::HasPopup state of the accessible object.
     *
     * @param hasPopup If @c true the accessible object is in @c A11yState::HasPopup state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setHasPopup(bool hasPopup);

    /*!
     * @brief Resets the @c A11yState::HasPopup state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetHasPopup();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Hidden state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Hidden state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isHidden() const;

    /*!
     * @brief Sets the @c A11yState::Hidden state of the accessible object.
     *
     * @param hidden If @c true the accessible object is in @c A11yState::Hidden state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setHidden(bool hidden);

    /*!
     * @brief Resets the @c A11yState::Hidden state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetHidden();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Invalid state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Invalid state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isInvalid() const;

    /*!
     * @brief Sets the @c A11yState::Invalid state of the accessible object.
     *
     * @param invalid If @c true the accessible object is in @c A11yState::Invalid state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setInvalid(bool invalid);

    /*!
     * @brief Resets the @c A11yState::Invalid state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetInvalid();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Iconified state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Iconified state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isIconified() const;

    /*!
     * @brief Sets the @c A11yState::Iconified state of the accessible object.
     *
     * @param iconified If @c true the accessible object is in @c A11yState::Iconified state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setIconified(bool iconified);

    /*!
     * @brief Resets the @c A11yState::Iconified state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetIconified();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Mixed state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Mixed state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isMixed() const;

    /*!
     * @brief Sets the @c A11yState::Mixed state of the accessible object.
     *
     * @param mixed If @c true the accessible object is in @c A11yState::Mixed state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setMixed(bool mixed);

    /*!
     * @brief Resets the @c A11yState::Mixed state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetMixed();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::ManagesDescendants state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::ManagesDescendants state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool managesDescendants() const;

    /*!
     * @brief Sets the @c A11yState::ManagesDescendants state of the accessible object.
     *
     * @param managesDescendants If @c true the accessible object is in @c A11yState::ManagesDescendants state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setManagesDescendants(bool managesDescendants);

    /*!
     * @brief Resets the @c A11yState::ManagesDescendants state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetManagesDescendants();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Modal state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Modal state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isModal() const;

    /*!
     * @brief Sets the @c A11yState::Modal state of the accessible object.
     *
     * @param modal If @c true the accessible object is in @c A11yState::Modal state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setModal(bool modal);

    /*!
     * @brief Resets the @c A11yState::Modal state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetModal();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::MultiLine state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::MultiLine state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isMultiLine() const;

    /*!
     * @brief Sets the @c A11yState::MultiLine state of the accessible object.
     *
     * @param multiLine If @c true the accessible object is in @c A11yState::MultiLine state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setMultiLine(bool multiLine);

    /*!
     * @brief Resets the @c A11yState::MultiLine state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetMultiLine();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::MultiSelectable state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::MultiSelectable state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isMultiSelectable() const;

    /*!
     * @brief Sets the @c A11yState::MultiSelectable state of the accessible object.
     *
     * @param multiSelectable If @c true the accessible object is in @c A11yState::MultiSelectable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setMultiSelectable(bool multiSelectable);

    /*!
     * @brief Resets the @c A11yState::MultiSelectable state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetMultiSelectable();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::OffScreen state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::OffScreen state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isOffScreen() const;

    /*!
     * @brief Sets the @c A11yState::OffScreen state of the accessible object.
     *
     * @param offScreen If @c true the accessible object is in @c A11yState::OffScreen state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setOffScreen(bool offScreen);

    /*!
     * @brief Resets the @c A11yState::OffScreen state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetOffScreen();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::OrientationHorizontal state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::OrientationHorizontal state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isOrientationHorizontal() const;

    /*!
     * @brief Sets the @c A11yState::OrientationHorizontal state of the accessible object.
     *
     * @param orientationHorizontal If @c true the accessible object is in @c A11yState::OrientationHorizontal state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setOrientationHorizontal(bool orientationHorizontal);

    /*!
     * @brief Resets the @c A11yState::OrientationHorizontal state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetOrientationHorizontal();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::OrientationVertical state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::OrientationVertical state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isOrientationVertical() const;

    /*!
     * @brief Sets the @c A11yState::OrientationVertical state of the accessible object.
     *
     * @param orientationVertical If @c true the accessible object is in @c A11yState::OrientationVertical state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setOrientationVertical(bool orientationVertical);

    /*!
     * @brief Resets the @c A11yState::OrientationVertical state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetOrientationVertical();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Pinned state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Pinned state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isPinned() const;

    /*!
     * @brief Sets the @c A11yState::Pinned state of the accessible object.
     *
     * @param pinned If @c true the accessible object is in @c A11yState::Pinned state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setPinned(bool pinned);

    /*!
     * @brief Resets the @c A11yState::Pinned state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetPinned();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::ReadOnly state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::ReadOnly state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isReadOnly() const;

    /*!
     * @brief Sets the @c A11yState::ReadOnly state of the accessible object.
     *
     * @param readOnly If @c true the accessible object is in @c A11yState::ReadOnly state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setReadOnly(bool readOnly);

    /*!
     * @brief Resets the @c A11yState::ReadOnly state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetReadOnly();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Required state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Required state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isRequired() const;

    /*!
     * @brief Sets the @c A11yState::Required state of the accessible object.
     *
     * @param required If @c true the accessible object is in @c A11yState::Required state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setRequired(bool required);

    /*!
     * @brief Resets the @c A11yState::Required state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetRequired();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Selectable state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Selectable state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isSelectable() const;

    /*!
     * @brief Sets the @c A11yState::Selectable state of the accessible object.
     *
     * @param selectable If @c true the accessible object is in @c A11yState::Selectable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setSelectable(bool selectable);

    /*!
     * @brief Resets the @c A11yState::Selectable state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetSelectable();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::SelectableText state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::SelectableText state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isSelectableText() const;

    /*!
     * @brief Sets the @c A11yState::SelectableText state of the accessible object.
     *
     * @param selectableText If @c true the accessible object is in @c A11yState::SelectableText state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setSelectableText(bool selectableText);

    /*!
     * @brief Resets the @c A11yState::SelectableText state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetSelectableText();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Selected state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Selected state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isSelected() const;

    /*!
     * @brief Sets the @c A11yState::Selected state of the accessible object.
     *
     * @param selected If @c true the accessible object is in @c A11yState::Selected state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setSelected(bool selected);

    /*!
     * @brief Resets the @c A11yState::Selected state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetSelected();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::SupportsAutocompletion state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::SupportsAutocompletion state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool supportsAutocompletion() const;

    /*!
     * @brief Sets the @c A11yState::SupportsAutocompletion state of the accessible object.
     *
     * @param supportsAutocompletion If @c true the accessible object is in @c A11yState::SupportsAutocompletion state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setSupportsAutocompletion(bool supportsAutocompletion);

    /*!
     * @brief Resets the @c A11yState::SupportsAutocompletion state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetSupportsAutocompletion();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::ManagedChild state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::ManagedChild state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isManagedChild() const;

    /*!
     * @brief Sets the @c A11yState::ManagedChild state of the accessible object.
     *
     * @param managedChild If @c true the accessible object is in @c A11yState::ManagedChild state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setManagedChild(bool managedChild);

    /*!
     * @brief Resets the @c A11yState::ManagedChild state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetManagedChild();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Truncated state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Truncated state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isTruncated() const;

    /*!
     * @brief Sets the @c A11yState::Truncated state of the accessible object.
     *
     * @param truncated If @c true the accessible object is in @c A11yState::Truncated state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setTruncated(bool truncated);

    /*!
     * @brief Resets the @c A11yState::Truncated state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetTruncated();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::Visited state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::Visited state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isVisited() const;

    /*!
     * @brief Sets the @c A11yState::Visited state of the accessible object.
     *
     * @param visited If @c true the accessible object is in @c A11yState::Visited state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setVisited(bool visited);

    /*!
     * @brief Resets the @c A11yState::Visited state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetVisited();

    /*!
     * @brief Indicates whether the object is in the @c A11yState::PasswordProtected state, or not.
     *
     * @return @c true if the accessible object is in @c A11yState::PasswordProtected state, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isPasswordProtected() const;

    /*!
     * @brief Sets the @c A11yState::PasswordProtected state of the accessible object.
     *
     * @param passwordProtected If @c true the accessible object is in @c A11yState::PasswordProtected state,
     * and if @c false the accessible object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setPasswordProtected(bool passwordProtected);

    /*!
     * @brief Resets the @c A11yState::PasswordProtected state of the accessible object to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetPasswordProtected();


Q_SIGNALS:

    /*!
     * @brief Emitted whenever a state of the accessible object changes.
     *
     * @param state The type of the state that has changed.
     * @param value If @c true the accessible object's state defined by @c state is currently set,
     * and if @c false the accessible object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void stateChanged(bb::cascades::A11yState::Type state, bool value); 

    /*!
     * @brief Emitted when the @c A11yState::Active state of the accessible object changes.
     *
     * @param active If @c true the accessible object is in @c Active state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void activeChanged(bool active); 

    /*!
     * @brief Emitted when the @c A11yState::Animated state of the accessible object changes.
     *
     * @param animated If @c true the accessible object is in @c Animated state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void animatedChanged(bool animated); 

    /*!
     * @brief Emitted when the @c A11yState::Busy state of the accessible object changes.
     *
     * @param busy If @c true the accessible object is in @c A11yState::Busy state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void busyChanged(bool busy); 

    /*!
     * @brief Emitted when the @c A11yState::Checkable state of the accessible object changes.
     *
     * @param checkable If @c true the accessible object is in @c A11yState::Checkable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void checkableChanged(bool checkable); 

    /*!
     * @brief Emitted when the @c A11yState::Checked state of the accessible object changes.
     *
     * @param checked If @c true the accessible object is in @c A11yState::Checked state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void checkedChanged(bool checked); 

    /*!
     * @brief Emitted when the @c A11yState::DefaultControl state of the accessible object changes.
     *
     * @param defaultControl If @c true the accessible object is in @c A11yState::DefaultControl state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void defaultControlChanged(bool defaultControl);

    /*!
     * @brief Emitted when the @c A11yState::Defunct state of the accessible object changes.
     *
     * @param defunct If @c true the accessible object is in @c A11yState::Defunct state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void defunctChanged(bool defunct); 

    /*!
     * @brief Emitted when the @c A11yState::Disabled state of the accessible object changes.
     *
     * @param disabled If @c true the accessible object is in @c A11yState::Disabled state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void disabledChanged(bool disabled); 

    /*!
     * @brief Emitted when the @c A11yState::Expandable state of the accessible object changes.
     *
     * @param expandable If @c true the accessible object is in @c A11yState::Expandable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void expandableChanged(bool expandable); 

    /*!
     * @brief Emitted when the @c A11yState::Expanded state of the accessible object changes.
     *
     * @param expanded If @c true the accessible object is in @c A11yState::Expanded state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void expandedChanged(bool expanded); 

    /*!
     * @brief Emitted when the @c A11yState::Focusable state of the accessible object changes.
     *
     * @param focusable If @c true the accessible object is in @c A11yState::Focusable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void focusableChanged(bool focusable); 

    /*!
     * @brief Emitted when the @c A11yState::Focused state of the accessible object changes.
     *
     * @param focused If @c true the accessible object is in @c A11yState::Focused state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void focusedChanged(bool focused); 

    /*!
     * @brief Emitted when the @c A11yState::HasPopup state of the accessible object changes.
     *
     * @param hasPopup If @c true the accessible object is in @c A11yState::HasPopup state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void hasPopupChanged(bool hasPopup); 

    /*!
     * @brief Emitted when the @c A11yState::Hidden state of the accessible object changes.
     *
     * @param hidden If @c true the accessible object is in @c A11yState::Hidden state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void hiddenChanged(bool hidden); 

    /*!
     * @brief Emitted when the @c A11yState::Invalid state of the accessible object changes.
     *
     * @param invalid If @c true the accessible object is in @c A11yState::Invalid state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void invalidChanged(bool invalid); 

    /*!
     * @brief Emitted when the @c A11yState::Iconified state of the accessible object changes.
     *
     * @param iconified If @c true the accessible object is in @c A11yState::Iconified state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void iconifiedChanged(bool iconified); 

    /*!
     * @brief Emitted when the @c A11yState::Mixed state of the accessible object changes.
     *
     * @param mixed If @c true the accessible object is in @c A11yState::Mixed state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void mixedChanged(bool mixed); 

    /*!
     * @brief Emitted when the @c A11yState::ManagesDescendants state of the accessible object changes.
     *
     * @param managesDescendants If @c true the accessible object is in @c A11yState::ManagesDescendants state,
     * and if @c false the accessible object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void managesDescendantsChanged(bool managesDescendants); 

    /*!
     * @brief Emitted when the @c A11yState::Modal state of the accessible object changes.
     *
     * @param modal If @c true the accessible object is in @c A11yState::Modal state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void modalChanged(bool modal); 

    /*!
     * @brief Emitted when the @c A11yState::Multiline state of the accessible object changes.
     *
     * @param multiLine If @c true the accessible object is in @c A11yState::Multiline state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void multiLineChanged(bool multiLine); 

    /*!
     * @brief Emitted when the @c A11yState::MultiSelectable state of the accessible object changes.
     *
     * @param multiSelectable If @c true the accessible object is in @c A11yState::MultiSelectable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void multiSelectableChanged(bool multiSelectable); 

    /*!
     * @brief Emitted when the @c A11yState::Offscreen state of the accessible object changes.
     *
     * @param offScreen If @c true the accessible object is in @c A11yState::Offscreen state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void offScreenChanged(bool offScreen); 

    /*!
     * @brief Emitted when the @c A11yState::OrientationHorizontal state of the accessible object changes.
     *
     * @param orientationHorizontal If @c true the accessible object is in @c A11yState::OrientationHorizontal state,
     * and if @c false the accessible object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void orientationHorizontalChanged(bool orientationHorizontal); 

    /*!
     * @brief Emitted when the @c A11yState::OrientationVertical state of the accessible object changes.
     *
     * @param orientationVertical If @c true the accessible object is in @c A11yState::OrientationVertical state,
     * and if @c false the accessible object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void orientationVerticalChanged(bool orientationVertical); 

    /*!
     * @brief Emitted when the @c A11yState::Pinned state of the accessible object changes.
     *
     * @param pinned If @c true the accessible object is in @c A11yState::Pinned state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void pinnedChanged(bool pinned); 

    /*!
     * @brief Emitted when the @c A11yState::ReadOnly state of the accessible object changes.
     *
     * @param readOnly If @c true the accessible object is in @c A11yState::ReadOnly state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void readOnlyChanged(bool readOnly); 

    /*!
     * @brief Emitted when the @c A11yState::Required state of the accessible object changes.
     *
     * @param required If @c true the accessible object is in @c A11yState::Required state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void requiredChanged(bool required); 

    /*!
     * @brief Emitted when the @c A11yState::Selectable state of the accessible object changes.
     *
     * @param selectable If @c true the accessible object is in @c A11yState::Selectable state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void selectableChanged(bool selectable); 

    /*!
     * @brief Emitted when the @c A11yState::SelectableText state of the accessible object changes.
     *
     * @param selectableText If @c true the accessible object is in @c A11yState::SelectableText state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void selectableTextChanged(bool selectableText); 

    /*!
     * @brief Emitted when the @c A11yState::Selected state of the accessible object changes.
     *
     * @param selected If @c true the accessible object is in @c A11yState::Selected state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void selectedChanged(bool selected); 

    /*!
     * @brief Emitted when the @c A11yState::SupportsAutocompletion state of the accessible object changes.
     *
     * @param supportsAutocompletion If @c true the accessible object is in @c A11yState::SupportsAutocompletion state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void supportsAutocompletionChanged(bool supportsAutocompletion); 

    /*!
     * @brief Emitted when the @c A11yState::ManagedChild state of the accessible object changes.
     *
     * @param managedChild If @c true the accessible object is in @c A11yState::ManagedChild state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void managedChildChanged(bool managedChild);

    /*!
     * @brief Emitted when the @c A11yState::Truncated state of the accessible object changes.
     *
     * @param truncated If @c true the accessible object is in @c A11yState::Truncated state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void truncatedChanged(bool truncated); 

    /*!
     * @brief Emitted when the @c A11yState::Visited state of the accessible object changes.
     *
     * @param visited If @c true the accessible object is in @c A11yState::Visited state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void visitedChanged(bool visited); 

    /*!
     * @brief Emitted when the @c A11yState::PasswordProtected state of the accessible object changes.
     *
     * @param passwordProtected If @c true the accessible object is in @c A11yState::PasswordProtected state, and if @c false the accessible
     * object is not in this state.
     *
     * @since BlackBerry 10.2.0
     */
    void passwordProtectedChanged(bool passwordProtected);


protected:
    /*! @cond PRIVATE */
    explicit A11yStateHolder(CustomA11yObject *parent = 0);
    virtual ~A11yStateHolder();
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(A11yStateHolder)
    Q_DISABLE_COPY(A11yStateHolder)
    /*! @endcond */
};


}
}
 
QML_DECLARE_TYPE(bb::cascades::A11yStateHolder)
 
#endif // cascades_a11ystateholder_h

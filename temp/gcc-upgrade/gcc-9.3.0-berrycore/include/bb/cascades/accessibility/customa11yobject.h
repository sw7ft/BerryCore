/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef bb_cascades_customa11yobject_h
#define bb_cascades_customa11yobject_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/UIObject>
#include <bb/cascades/A11yRole>
#include <bb/cascades/A11yState>
#include <bb/cascades/A11yStateHolder>
#include <bb/cascades/AbstractA11yObject>
#include <bb/cascades/AbstractA11ySpecialization>

namespace bb
{
namespace cascades
{

class CustomA11yObjectPrivate;

/*!
 * @brief Accessibility object that can be used to implement custom accessibility behavior.
 *
 * CustomA11yObject exposes an accessibility API similar to
 * the ones defined by WAI-ARIA. It can be used to make custom controls accessible,
 * or make compositions of built-in controls behave in a custom way (from an
 * accessibility point of view).
 *
 * Contrary to the base class AbstractA11yObject, on a CustomA11yObject
 * you can set the role. Each role defines a set of specialization contracts
 * that the accessibility object is expected to support.
 *
 * CustomA11yObject is expected to represent the state of the accessible control
 * using #state property.
 *
 *
 * Typically most controls will implement at least ComponentA11ySpecialization by
 * responding to activation requests sent by the ComponentA11ySpecialization::activate()
 * signal, and optionally support highlighting by responding to the ComponentA11ySpecialization::highlighted()
 * signal.
 *
 * Some controls may implement other specializations matching their roles.
 *
 * For example, if a control's role is set to A11yRole::Slider, the framework expects that accessibility 
 * object to support ValueA11ySpecialization, which allows assistive technology to extract minimum,
 * maximum and current values from the control, as well as change the value.
 *
 * QML usage:
 * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml4
 *
 * @see bb::cascades::Control::accessibility
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT CustomA11yObject : public AbstractA11yObject {
    Q_OBJECT

    /*!
     * @brief The role of an accessible control.
     *
     * Describes the role of an accessible control, e.g. "Button", "Check box", "Text" etc.
     * This is a init-time only property, once initialized during object creation the role
     * cannot be changed.
     *
     * The default value for this property is @c bb::cascades::A11yRole::Undefined.
     *
     * @see bb::cascades::Control::accessibility
     * @see bb::cascades::A11yRole
     *
     * @xmlonly
     * <qml>
     *     <property writable="init-only"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::A11yRole::Type role READ role WRITE setRole FINAL)

    /*!
     * @brief The extended role of an accessible control.
     *
     * This property can be used to set an extended role of an accessible control. An assistive
     * technology can choose to support more roles than defined in the @c A11yRole enumeration,
     * in the form of a free text extended role name. That extended role can then be used in a
     * Cascades application by setting the role to A11yRole.Extended, and set this property to
     * the extended role name.
     *
     * This is a init-time only property, once initialized during object creation the role
     * can't be changed.
     *
     * The default value for this property is the empty string.
     *
     * @see bb::cascades::CustomA11yObject::role
     *
     * @xmlonly
     * <qml>
     * <property writable="init-only"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(QString extendedRole READ extendedRole WRITE setExtendedRole REVISION 3 FINAL)

    /*!
     * @brief The state of an accessible control.
     *
     * Describes the state of an accessible control, e.g. Disabled, Busy, Checked etc.
     *
     * QML usage:
     * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml3
     * @see bb::cascades::Control::accessibility
     * @see bb::cascades::A11yState
     *
     * @since BlackBerry 10.2.0
     *
     * @xmlonly
     * <qml>
     *     <property groupedProperty="yes"/>
     * </qml>
     * @endxmlonly
     */
    Q_PROPERTY(bb::cascades::A11yStateHolder* state READ state CONSTANT FINAL)

    /*!
     * @brief A QDeclarativeListProperty object that contains the list of specializations
     * supported by this accessibility object.
     *
     * @note You are only allowed to add one specialization object per type. If more than one
     * specialization object of the same type is added, only the first specialization object 
     * is used, the rest are ignored.
     *
     * QML usage:
     * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml2
     *
     * @see bb::cascades::ValueA11ySpecialization
     *
     * @xmlonly
     * <qml>
     *     <property name="specializations" listType="bb::cascades::accessibility::AbstractA11ySpecialization" defaultProperty="yes"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractA11ySpecialization> specializations READ specializations FINAL)
    Q_CLASSINFO("DefaultProperty", "specializations")

public:

    /*!
     * @brief Creates a CustomA11yObject with @c role bb::cascades::A11yRole::Undefined.
     *
     * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you do not specify a parent.
     *
     * @since BlackBerry 10.2.0
     */
    explicit CustomA11yObject(UIObject *parent = 0);

    /*!
     * @brief Creates a CustomA11yObject with the supplied role.
     *
     * @param role The role that the accessibility object should assume.
     * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you do not specify a parent.
     *
     * @since BlackBerry 10.2.0
     */
    explicit CustomA11yObject(bb::cascades::A11yRole::Type role, UIObject *parent = 0);

    /*!
     * @brief Creates a CustomA11yObject with the supplied extended role.
     *
     * @c role will be set to A11yRole::Extended.
     *
     * @param extendedRole The name of the extended role that the accessibility object should assume.
     * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you do not specify a parent.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    explicit CustomA11yObject(const QString &extendedRole, UIObject *parent = 0);

    /*!
     * @brief Destructs this accessibility object.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~CustomA11yObject();

    /*!
     * @brief Retrieves the accessibility @c #state of the control.
     *
     * @return The accessibility state of the control.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::A11yStateHolder *state() const;

    /*!
     * @brief Adds an @c AbstractA11ySpecialization to the accessibility object.
     * 
     * The accessibility object takes ownership of the @c %AbstractA11ySpecialization object, since 
     * @c %AbstractA11ySpecialization objects should not typically be shared. 
     * If the @c %AbstractA11ySpecialization is @c 0 or it already belongs to the accessibility object, 
     * the specialization set is not added. Once completed, the @c specializationAdded()
     * signal is emitted.
     *
     * @note You are only allowed to add one specialization object per type. If more than one
     * specialization object of the same type is added, only the first specialization object 
     * is used, the rest are ignored.
     *
     * @see @c CustomA11yObject::specializations
     *
     * @param specialization The @c %AbstractA11ySpecialization to add to the @c %CustomA11yObject
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void addSpecialization(bb::cascades::AbstractA11ySpecialization *specialization);

    /*!
     * @brief Removes an @c %AbstractA11ySpecialization from the accessibility object.
     *
     * Once the @c %AbstractA11ySpecialization is removed, the accessibility object no longer references it, but it is still 
     * owned by the accessibility object. It is up to the application to either delete the removed 
     * @c %AbstractA11ySpecialization, transfer its ownership (by setting its parent) to another object or leave 
     * it as a child of the accessibility object (in which case it will be deleted with the accessibility object).
     *
     * Once completed, the @c specializationRemoved() signal is emitted.
     *
     * @see @c CustomA11yObject::specializations
     *
     * @param specialization The specialization to remove.
     *
     * @return @c true if the @c AbstractA11ySpecialization was owned by the @c %CustomA11yObject, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool removeSpecialization(bb::cascades::AbstractA11ySpecialization *specialization);

    /*!
     * @brief Retrieves the number of @c %AbstractA11ySpecialization objects.
     *
     * @see @c CustomA11yObject::specializations
     *
     * @return The number of @c %AbstractA11ySpecialization objects.
     *
     * @since BlackBerry 10.2.0
     */
    int specializationCount() const;

    /*!
     * @brief Retrieves an @c %AbstractA11ySpecialization at a specified index.
     *
     * Ownership of the @c %AbstractA11ySpecialization object remains with 
     * the accessibility object.
     *
     * @see @c CustomA11yObject::specializations
     *
     * @param index The index of the @c %AbstractA11ySpecialization.
     *
     * @return The requested @c %AbstractA11ySpecialization if the index was valid, and @c 0 otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::AbstractA11ySpecialization* specializationAt(int index) const;

    /*!
     * @brief Removes all @c AbstractA11ySpecialization objects from the accessibility object 
     * and deletes them.
     *
     * Once completed, the @c specializationRemoved() signal is emitted with @c 0 as its parameter.
     *
     * @see @c CustomA11yObject::specializations
     *
     * @since BlackBerry 10.2.0
     */
    void removeAllSpecializations();

    /*!
     * @brief Retrieves the value of the @c extendedRole property.
     *
     * @return The name of the extended role the accessible object assumes.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(3)
    QString extendedRole() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when an @c AbstractA11ySpecialization has been added to the Control.
     *
     * @param specialization The @c %AbstractA11ySpecialization that has been added.
     *
     * @since BlackBerry 10.2.0
     */
    void specializationAdded(bb::cascades::AbstractA11ySpecialization *specialization);

    /*!
     * @brief Emitted when an @c AbstractA11ySpecialization has been removed from the @c control.
     *
     * @param specialization The @c %AbstractA11ySpecialization that has been removed. @c 0 if emitted 
     * by @c removeAllSpecializations().
     *
     * @since BlackBerry 10.2.0
     */
    void specializationRemoved(bb::cascades::AbstractA11ySpecialization *specialization);

private:
    /*! @cond PRIVATE */
    void setRole(bb::cascades::A11yRole::Type role);
    void setExtendedRole(const QString &extendedRole);
    QDeclarativeListProperty<bb::cascades::AbstractA11ySpecialization> specializations();

    Q_DECLARE_PRIVATE(CustomA11yObject)
    Q_DISABLE_COPY(CustomA11yObject)
    /*! @endcond */
};

}
}

QML_DECLARE_TYPE(bb::cascades::CustomA11yObject)

#endif    // bb_cascades_customa11yobject_h

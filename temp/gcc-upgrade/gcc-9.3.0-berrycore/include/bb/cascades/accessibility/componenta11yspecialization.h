/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef bb_cascades_componenta11yspecialization_h
#define bb_cascades_componenta11yspecialization_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/AbstractA11ySpecialization>
#include <bb/cascades/A11yComponentActivationEvent>

namespace bb {
namespace cascades {

class UIObject;
class ComponentA11ySpecializationPrivate;

/*!
 * @brief Class defining a "component" accessibility specialization.
 *
 * Accessibility (A11y) APIs which support output to the display should support the
 * "component" specialization.
 *
 * QML usage:
 * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml6
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT ComponentA11ySpecialization : public AbstractA11ySpecialization {
    Q_OBJECT

public:

    /*!
     * @brief Creates a ComponentA11ySpecialization with @c role bb::cascades::A11yRole::Undefined.
     *
     * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you do not specify a parent.
     *
     * @since BlackBerry 10.2.0
     */
    explicit ComponentA11ySpecialization(UIObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~ComponentA11ySpecialization();

    Q_SIGNALS:

    /*!
     * Emitted when the control is expected to perform activation.
     *
     * If the activation event is handled, then @c event.consume() must be called.
     *
     * @param event Event that holds the type of activation, and that can be consumed.
     *
     * @since BlackBerry 10.2.0
     */
    void activationRequested(bb::cascades::A11yComponentActivationEvent *event);

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(ComponentA11ySpecialization)
    Q_DISABLE_COPY(ComponentA11ySpecialization)
    /*! @endcond */

};

}
}

QML_DECLARE_TYPE(bb::cascades::ComponentA11ySpecialization)

#endif // bb_cascades_componenta11yspecialization_h

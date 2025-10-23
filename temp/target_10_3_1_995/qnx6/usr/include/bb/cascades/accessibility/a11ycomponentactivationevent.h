/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_a11ycomponentactivationevent_h
#define cascades_a11ycomponentactivationevent_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/BaseObject>
#include <bb/cascades/A11yComponentActivationType>

namespace bb
{
namespace cascades
{

class A11yComponentActivationEventPrivate;

/*!
 * @brief Represents an activation event from an assistive technology.
 *
 * @see @c ComponentA11ySpecialization
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT A11yComponentActivationEvent : public BaseObject {
    Q_OBJECT
    Q_ENUMS(Type)

    /*!
     * @brief Specifies the type of activation performed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::A11yComponentActivationType::Type type READ type CONSTANT FINAL);

    /*!
     * @brief Specifies whether this event was consumed (handled) or not.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool consumed READ isConsumed FINAL);

    public:
    /*!
     * @brief Creates a new event.
     *
     * @param parent The parent that owns this event.
     * @param type The type of activation performed.
     *
     * @since BlackBerry 10.2.0
     */
    explicit A11yComponentActivationEvent(bb::cascades::A11yComponentActivationType::Type type, QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~A11yComponentActivationEvent();

    /*!
     * @brief Retrieves the @c #type property of this activation event.
     *
     * @return The type of activation performed.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::A11yComponentActivationType::Type type() const;

    /*!
     * @brief Retrieves the @c #consumed property of this activation event.
     *
     * @return @c true if this activation event was consumed, and @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isConsumed() const;

    /*!
     * @brief Consumes the activation event.
     *
     * If the activation event is handled the handler must call this function to mark the event as consumed.
     * Calling this function will set the @c #consumed property to @c true.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void consume();

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(A11yComponentActivationEvent);
    Q_DISABLE_COPY(A11yComponentActivationEvent);
    /*! @endcond */
};

}
}

#endif // cascades_a11ycomponentactivationevent_h


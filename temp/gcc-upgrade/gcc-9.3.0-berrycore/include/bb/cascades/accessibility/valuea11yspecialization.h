/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef bb_cascades_valuea11yspecialization_h
#define bb_cascades_valuea11yspecialization_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/AbstractA11ySpecialization>
#include <bb/cascades/A11yValueAdjustmentType>

#include <QString>

namespace bb
{
namespace cascades
{

class UIObject;
class ValueA11ySpecializationPrivate;

/*!
 * @brief Class defining a "Value" accessibility specialization.
 *
 * This specialization is typically implemented by objects that present some sort of bounded value,
 * such as a progress bar or a slider.
 *
 * This class does not enforce the contract for the minimum, maximum and value values.
 * Those values must be directly enforced by the application.
 *
 * QML usage:
 * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml2
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT ValueA11ySpecialization : public AbstractA11ySpecialization {
    Q_OBJECT

    /*!
     * @brief The current value.
     *
     * The default value is the same as @c minValue.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(float value READ value WRITE setValue RESET resetValue NOTIFY valueChanged FINAL)

     /*!
      * @brief The property representing the minimum value of the @c value property.
      *
      * The default @c minValue for a value is @c 0.0.
      *
      * @since BlackBerry 10.2.0
      */
    Q_PROPERTY(float minValue READ minValue WRITE setMinValue RESET resetMinValue NOTIFY minValueChanged FINAL)

     /*!
      * @brief The property representing the maximum value of the @c value property.
      *
      * The default @c maxValue for a value is @c 0.0.
      *
      * @since BlackBerry 10.2.0
      */
    Q_PROPERTY(float maxValue READ maxValue WRITE setMaxValue RESET resetMaxValue NOTIFY maxValueChanged FINAL)

    /*!
     * @brief The textual representation of the value of @c #value property.
     *
     * This property holds textual human readable representation of the value of the @c #value
     * property. For example, for a slider representing percentage from @c 0 to @c 100 it could be set to
     * "50%" using a @c value of @c 50.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString valueText READ valueText WRITE setValueText RESET resetValueText NOTIFY valueTextChanged FINAL)

    /*!
     * @brief The textual representation of the value of @c #minValue property.
     *
     * This property holds textual human readable representation of the value of the @c #minValue
     * property. For example, for a slider controlling transparency as a percentage from @c 0 to @c 100
     * it could be set to "Fully Opaque".
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString minValueText READ minValueText WRITE setMinValueText RESET resetMinValueText NOTIFY minValueTextChanged FINAL)

    /*!
     * @brief The textual representation of the value of @c #maxValue property.
     *
     * This property holds textual human readable representation of the value of the @c #maxValue
     * property. For example, for a slider controlling transparency as a percentage from @c 0 to @c 100
     * it could be set to "Fully Transparent".
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString maxValueText READ maxValueText WRITE setMaxValueText RESET resetMaxValueText NOTIFY maxValueTextChanged FINAL)

public:

    /*!
     * @brief Creates a ValueA11ySpecialization with @c role bb::cascades::A11yRole::Undefined.
     *
     * @param parent The parent object, or @c 0. This parameter is optional. The default is @c 0 if you do not specify a parent.
     *
     * @since BlackBerry 10.2.0
     */
    explicit ValueA11ySpecialization(UIObject *parent = 0);

    /*!
     * @brief Destructs this accessibility object.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~ValueA11ySpecialization();

    /*!
     * @brief Retrieves the current value.
     *
     * @since BlackBerry 10.2.0
     *
     * @return The current value for the @c #value property.
     */
    float value() const;
    
    /*!
     * @brief Sets the current value.
     *
     * If you provide a number outside the
     * defined range, the value is restricted to the range.
     *
     * @param value The value.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setValue(float value);
    
    /*!
     * @brief Resets the current value to the default value.
     *
     * The default value is the same as @c minValue. 
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetValue();

    /*!
     * @brief Retrieves the @c #minValue.
     *
     * @return The minimum value for @c #value property.
     *
     * @since BlackBerry 10.2.0
     */
    float minValue() const;

    /*!
     * @brief Sets the @c #minValue.
     *
     * @param minValue The new minimum value for @c #value property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setMinValue(float minValue);

    /*!
     * @brief Resets the @c #minValue to the default value of @c 0.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetMinValue();

    /*!
     * @brief Retrieves the @c #maxValue of the control.
     *
     * @return The maximum value for the @c #value property.
     *
     * @since BlackBerry 10.2.0
     */
    float maxValue() const;

    /*!
     * @brief Sets the @c #maxValue.
     *
     * @param maxValue The new maximum value for @c #value property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setMaxValue(float maxValue);

    /*!
     * @brief Resets the @c #maxValue to the default value of @c 0.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetMaxValue();

    /*!
     * @brief Retrieves the current value of @c valueText property.
     *
     * @return The current value text.
     *
     * @since BlackBerry 10.2.0
     */
    QString valueText() const;
    
    /*!
     * @brief Sets the value for @c valueText property.
     *
     * @param valueText The new value text.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setValueText(const QString &valueText);

    /*!
     * @brief Resets the value text to the default value, an empty QString.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetValueText();

    /*!
     * @brief Retrieves the current value of @c minValueText property.
     *
     * @return The current textual representation of @c #minValue.
     *
     * @since BlackBerry 10.2.0
     */
    QString minValueText() const;
    
    /*!
     * @brief Sets the value for @c minValueText property.
     *
     * @param minValueText The new textual representation of @c #minValue.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setMinValueText(const QString &minValueText);

    /*!
     * @brief Resets the textual representation of @c #minValue to the default value, an empty QString.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetMinValueText();

    /*!
     * @brief Retrieves the current value of @c maxValueText property.
     *
     * @return The current textual representation of @c #maxValue.
     *
     * @since BlackBerry 10.2.0
     */
    QString maxValueText() const;

    /*!
     * @brief Sets the value for @c maxValueText property.
     *
     * @param maxValueText The new textual representation of @c #maxValue.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setMaxValueText(const QString &maxValueText);

    /*!
     * @brief Resets the textual representation of @c #maxValue to the default value, an empty QString.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetMaxValueText();

    Q_SIGNALS:

    /*!
     * @brief Emitted when the value adjustment is requested from the object by
     * the accessibility (a11y) framework.
     *
     * The value of @c adjustType will correspond to @c A11yValueAdjustmentType::Type values.
     *
     * QML usage:
     * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml5
     *
     * @param adjustType The type of the requested adjustment.
     *
     * @see bb::cascades::A11yValueAdjustmentType
     *
     * @since BlackBerry 10.2.0
     */
    void valueAdjustmentRequested(bb::cascades::A11yValueAdjustmentType::Type adjustType);

    /*! @cond PRIVATE */
    /*!
     * @copydoc valueAdjustmentRequested(bb::cascades::A11yValueAdjustmentType)
     */
    void valueAdjustmentRequested(int adjustType);
    /*! @endcond */

    /*!
     * @brief Emitted when the value set is requested from the object by
     * the accessibility (a11y) framework.
     *
     * QML usage:
     * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml5
     *
     * @param value The value requested to be set.
     *
     * @since BlackBerry 10.2.0
     */
    void valueSetRequested(float value);

    /*!
     * @brief Emitted when the value changes.
     *
     * @param value The current value.
     *
     * @since BlackBerry 10.2.0
     */
    void valueChanged(float value);

    /*!
     * @brief Emitted when the @c #minValue changes.
     *
     * @param minValue The new minimum value for the @c #value property.
     *
     * @since BlackBerry 10.2.0
     */
    void minValueChanged(float minValue);

    /*!
     * @brief Emitted when the @c #maxValue changes.
     *
     * @param maxValue The new maximum value for the @c #value property.
     *
     * @since BlackBerry 10.2.0
     */
    void maxValueChanged(float maxValue);

    /*!
     * @brief Emitted when the @c #valueText changes.
     *
     * @param valueText The new value for the @c #valueText property.
     *
     * @since BlackBerry 10.2.0
     */
    void valueTextChanged(const QString &valueText);

    /*!
     * @brief Emitted when the @c #minValueText changes.
     *
     * @param minValueText The new value for the @c #minValueText property.
     *
     * @since BlackBerry 10.2.0
     */
    void minValueTextChanged(const QString &minValueText);

    /*!
     * @brief Emitted when the @c #maxValueText changes.
     *
     * @param maxValueText The new value for the @c #maxValueText property.
     *
     * @since BlackBerry 10.2.0
     */
    void maxValueTextChanged(const QString &maxValueText);

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(ValueA11ySpecialization)
    Q_DISABLE_COPY(ValueA11ySpecialization)
    /*! @endcond */

};

}
}

QML_DECLARE_TYPE(bb::cascades::ValueA11ySpecialization)

#endif // bb_cascades_valuea11yspecialization_h

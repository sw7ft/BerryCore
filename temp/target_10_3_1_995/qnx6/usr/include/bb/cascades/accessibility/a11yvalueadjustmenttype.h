/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_a11yvalueadjustmenttype_h
#define cascades_a11yvalueadjustmenttype_h

#include <QObject>
#include <bb/cascades/bbcascades_global.h>

namespace bb
{
namespace cascades
{

/*!
 * @brief Represents different ways a value can be adjusted
 *
 * @see @c ValueA11ySpecialization
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT A11yValueAdjustmentType {
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The type of values that can be retrieved or set.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief The minimum value.
         *
         * For values where there is no minimum, NAN will be used and can
         * be checked using @c isnan from math.h.
         *
         * @since BlackBerry 10.2.0
         */
        Minimum = 0,
        /*!
         * @brief The current value.
         *
         * For indeterminate values, NAN will be used and can be checked
         * using @c isnan from math.h.
         *
         * @since BlackBerry 10.2.0
         */
        Current = 1,
        /*!
         * @brief The maximum value.
         *
         * For values where there is no maximum, NAN will be used and can
         * be checked using @c isnan from @c math.h.
         *
         * @since BlackBerry 10.2.0
         */
        Maximum = 2,
        /*!
         * @brief The single step value increment.
         *
         * For values where there is no increment, NAN will be used and
         * can be checked using @c isnan from @c math.h.
         *
         * @since BlackBerry 10.2.0
         */
        SingleStepAdd = 3,
        /*!
         * @brief The single step value decrement.
         *
         * For values where there is no decrement, NAN will be used and
         * can be checked using @c isnan from @c math.h.
         *
         * @since BlackBerry 10.2.0
         */
        SingleStepSubtract = 4,
        /*!
         * @brief The page step value increment.
         *
         * For values where there is no increment, NAN will be used and
         * can be checked using @c isnan from @c math.h.
         *
         * @since BlackBerry 10.2.0
         */
        PageStepAdd = 5,
        /*!
         * @brief The page step value decrement.
         *
         * For values where there is no decrement, NAN will be used and
         * can be checked using @c isnan from @c math.h.
         *
         * @since BlackBerry 10.2.0
         */
        PageStepSubtract = 6
    };

private:
    /*! @cond PRIVATE */
    A11yValueAdjustmentType();
    ~A11yValueAdjustmentType();
    /*! @endcond */
};

}
}

#endif // cascades_a11yvalueadjustmenttype_h

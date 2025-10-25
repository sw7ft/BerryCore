/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef BB_CASCADES_PICKER_KIND_H
#define BB_CASCADES_PICKER_KIND_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QMetaObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief A class representing different kinds of @c Picker controls.
 *
 * The @c Expandable state displays the picker with a title and description
 * which can be set within the @c Picker.
 * The @c List state displays the picker without a header and always expanded.
 *
 * @xmlonly
 * <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.1.0
 */
class BBCASCADES_EXPORT PickerKind {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies the different kinds of pickers.
    *
    * @since BlackBerry 10.1.0
    */
    enum Type {
       /*!
        * @brief The default picker, which is determined by the system.
        *
        * @since BlackBerry 10.1.0
        */
        Default = 0,

       /*!
        * @brief A picker that appears as a list.
        *
        * @since BlackBerry 10.1.0
        */
        List = 1,

       /*!
        * @brief A picker that is expandable.
        *
        * @since BlackBerry 10.1.0
        */
        Expandable = 2
    };

private:
    /*! \cond PRIVATE */
    PickerKind();
    ~PickerKind();
    /*! \endcond */
};

}
}

#endif // BB_CASCADES_PICKER_KIND_H

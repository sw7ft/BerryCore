/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef bb_cascades_labeltextfitmode_h
#define bb_cascades_labeltextfitmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief A set of configurations that specify the text fit behavior to use with the @c Label control.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT LabelTextFitMode {
    Q_GADGET
    Q_ENUMS (Type)
public:
   /*!
    * @brief Specifies the text fit mode for text in the @c Label.
    *
    * @since BlackBerry 10.2.0
    */
    enum Type {
        /*!
         * @brief Let the framework decide the text fit mode.
         *
         *
         * @since BlackBerry 10.2.0
         */
        Default = 0,
        /*!
         * @brief No active auto fitting, but constraints such as min/max
         *        font size still apply if they are specified.
         *
         *
         * @since BlackBerry 10.2.0
         */
        Standard = 1,
        /*!
         * @brief Fit the text exactly within the bounds of the
         *        control.
         *
         * @since BlackBerry 10.2.0
         */
        FitToBounds = 2
    };
};

}
}

#endif // bb_cascades_labeltextfitmode_h

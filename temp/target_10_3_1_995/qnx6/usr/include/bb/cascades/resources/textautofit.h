/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef bb_cascades_textautofit_h
#define bb_cascades_textautofit_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief A set of configurations that specify dynamic font size behaviour to use with the @c TextField control.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextAutoFit {
    Q_GADGET
    Q_ENUMS (Type)
public:
   /*!
    * @brief Specifies the auto-fit mode for text in the @c TextField.
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {
        /*!
         * @brief Let the framework decide the auto-fit mode.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Default = 0,
        /*!
         * @brief Disable auto-fit, text will not be scaled.
         *
         *
         * @since BlackBerry 10.0.0
         */
        None = 1,
        /*!
         * @brief Scale text to fit exactly within bounds.
         *
         *
         * @since BlackBerry 10.0.0
         */
        FitToBounds = 2
    };
};

}
}

#endif // bb_cascades_textautofit_h

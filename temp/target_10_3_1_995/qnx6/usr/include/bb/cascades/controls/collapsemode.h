/*
 * Copyright (C) 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_COLLAPSE_MODE_H
#define BB_CASCADES_COLLAPSE_MODE_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QMetaObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief Enumerations for controlling how an @c ExpandableView collapses.
 *
 * The supported modes of an @c %ExpandableView include @c %Default, @c %None, @c %UserCollapse.
 *
 * The default mode is @c CollapseMethod::Default.
 *
 * @xmlonly
 * <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BBCASCADES_EXPORT CollapseMode {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies the different collapse modes of an @c ExpandableView.
    *
    * @since BlackBerry 10.3.0
    */
    enum Type {
       /*!
        * @brief Cascades determines the collapse mode for the @c %ExpandableView based on the content.
        *
        * @since BlackBerry 10.3.0
        */
        Default = 0,

       /*!
        * @brief The @c %ExpandableView cannot be collapsed after it is expanded.
        *
        * @since BlackBerry 10.3.0
        */
        None = 1,

       /*!
        * @brief The @c %ExpandableView can be explicitly collapsed when a user taps the collapse button.
        *
        * @since BlackBerry 10.3.0
        */
        UserCollapse = 2
    };

private:
    /*! \cond PRIVATE */
    CollapseMode();
    ~CollapseMode();
    /*! \endcond */
};

}
}

#endif // BB_CASCADES_COLLAPSE_MODE_H

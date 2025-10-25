/*
 * Copyright (C) 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_EXPAND_MODE_H
#define BB_CASCADES_EXPAND_MODE_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QMetaObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief Enumerations for controlling how an @c %ExpandableView expands.
 *
 * The supported modes of an @c %ExpandableView include @c %Default, @c %AutoExpand, @c %UserExpand
 * The default mode is @c ExpandMode::Default.
 *
 * @xmlonly
 * <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BBCASCADES_EXPORT ExpandMode {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies the expand mode of an @c ExpandableView.
    *
    * @since BlackBerry 10.3.0
    */
    enum Type {
       /*!
        * @brief The framework determines expand mode for the @c %ExpandableView based on its content.
        *
        * @since BlackBerry 10.3.0
        */
        Default = 0,

       /*!
        * @brief When the @c %AutoExpand mode is set,
        * a user cannot interact with the visible content in an @c %ExpandableView when it is collapsed.
        *
        * @since BlackBerry 10.3.0
        */
        AutoExpand = 1,

       /*!
        * @brief When the @c %UserExpand mode is set,
        * a user can interact with the visible content in an @c %ExpandableView when it is collapsed.
        *
        * @since BlackBerry 10.3.0
        */
        UserExpand = 2
    };

private:
    /*! \cond PRIVATE */
    ExpandMode();
    ~ExpandMode();
    /*! \endcond */
};

}
}

#endif // BB_CASCADES_EXPAND_MODE_H

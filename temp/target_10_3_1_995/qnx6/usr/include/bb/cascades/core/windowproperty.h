/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef BB_CASCADES_WINDOWPROPERTY_H
#define BB_CASCADES_WINDOWPROPERTY_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QMetaObject>
#include <QFlags>

namespace bb {
namespace cascades {

/*!
 * @brief A class representing window properties and their combinations.
 * 
 * This class represents different @c libscreen window properties and their
 * combinations.
 *
 * @see ForeignWindowControl::updatedProperties
 *
 * @xmlonly
 *     <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT WindowProperty {
    Q_GADGET
    Q_ENUMS(Type)
    Q_FLAGS(Types)

public:

   /*!
    * @brief Specifies different kinds of window properties.
    *
    * @xmlonly
    * <qml>
    *     <enum flagsType="bb::cascades::WindowProperty::Types"/>
    * </qml>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {

        /*!
         * @brief Value not corresponding to any window property.
         *
         * @since BlackBerry 10.0.0
         */
        None        = (0 << 0),

        /*! 
         * @brief Corresponds to @c SCREEN_PROPERTY_POSITION property of the window.
         *
         * @since BlackBerry 10.0.0
         */
        Position    = (1 << 0),

        /*!
         * @brief Corresponds to @c SCREEN_PROPERTY_SIZE property of the window.
         *
         * @since BlackBerry 10.0.0
         */
        Size        = (1 << 1),

        /*!
         * @brief Corresponds to @c SCREEN_PROPERTY_SOURCE_SIZE property of the window.
         *
         * @since BlackBerry 10.0.0
         */
        SourceSize  = (1 << 2),

        /*!
         * @brief Corresponds to @c SCREEN_PROPERTY_VISIBLE property of the window.
         *
         * @since BlackBerry 10.0.0
         */
        Visible     = (1 << 3)
    };

    /*!
     * @brief Defines combinations of window properties.
     *
     * @since BlackBerry 10.0.0
     */
    Q_DECLARE_FLAGS(Types, Type);

private:
    /*! @cond PRIVATE */
    WindowProperty();
    virtual ~WindowProperty();
    /*! @endcond */
};

/*! @cond PRIVATE */
Q_DECLARE_OPERATORS_FOR_FLAGS(WindowProperty::Types)
/*! @endcond */

}
}

#endif // BB_CASCADES_WINDOWPROPERTY_H

/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_scrollposition_h
#define cascades_scrollposition_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents different scroll positions used in a list.
 *
 * @xmlonly
 * <apigrouping group="User interface/List"/>
 * <qml>
 * <class register="enum-only"/>
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ScrollPosition {
private:
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief Available scroll positions
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Specifies the beginning of the list.
         *
         * @since BlackBerry 10.0.0
         */
        Beginning = 0,
        /*!
         * @brief Specifies the end of the list.
         *
         * @since BlackBerry 10.0.0
         */
        End = 1
    };
private:
    ScrollPosition();
    ~ScrollPosition();
};

}
}

#endif // cascades_scrollposition_h


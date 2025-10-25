/* Copyright (c) 2012 BlackBerry. All rights reserved. */

#ifndef cascades_touchpropagation_h
#define cascades_touchpropagation_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * @brief Enumeration for specifying the touch propagation mode for a node and it's subtree.
 *
 * @see VisualNode::setTouchPropagationMode()
 *
 * @xmlonly
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TouchPropagationMode {
    Q_GADGET
    Q_ENUMS (Type)
public:

    /*!
     * @brief Enumeration for specifying touch propagation mode for a node and it's subtree.
     *
     * @see VisualNode::setTouchPropagationMode()
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*! @brief Full touch event propagation.
         *
         * @since BlackBerry 10.0.0
         */
        Full,
        /*! @brief No touch event propagation.
         *
         * @since BlackBerry 10.0.0
         */
        None,
        /*! @brief Skip node but propagate in sub tree.
         *
         * @since BlackBerry 10.0.0
         */
        PassThrough
    };

private:
    /*! @cond PRIVATE */
    TouchPropagationMode();
    ~TouchPropagationMode();
    /*! @endcond */
};
}
}

#endif     // cascades_touchpropagation_h

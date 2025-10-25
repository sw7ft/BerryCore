/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_touchtype_h
#define cascades_touchtype_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {
    
    /*!
     * @brief Represents different touch types.
     *
     * Touch types describe different stages of a touch interaction.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT TouchType
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)
        
    public:
        /*!
         * @brief The touch types.
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
            /*!
             * @brief Occurs when the user touches the screen.
             *
             * @since BlackBerry 10.0.0
             */
            Down,
            /*!
             * @brief Occurs when the user moves a finger on the screen.
             *
             * @since BlackBerry 10.0.0
             */
            Move,
            /*!
             * @brief Occurs when the user releases a finger.
             *
             * @since BlackBerry 10.0.0
             */
            Up,
            /*!
             * @brief Occurs when an interaction is canceled.
             *
             * For example when a containing control, such as a @c ListView, takes over the interaction
             * and starts to scroll.
             *
             * Cancel can be sent even when no other touch events
             * has been received.
             *
             * @since BlackBerry 10.0.0
             */
            Cancel
        };
        
    private:
        /*! @cond PRIVATE */
        TouchType();
        ~TouchType();
        /*! @endcond */
    };
    
}
}

#endif /* cascades_touchtype_h */

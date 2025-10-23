/*!
 * @copyright
 * Copyright Research In Motion Limited, 2014
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_navigationeventtype_h
#define cascades_navigationeventtype_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents different navigation event types.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT NavigationEventType
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)

    public:
        /*!
         * @brief The navigation event types.
         *
         * @since BlackBerry 10.3.1
         */
        enum Type {
            /*!
             * @brief Occurs when the user navigates to the left.
             *
             * @since BlackBerry 10.3.1
             */
            Left,
            /*!
             * @brief Occurs when the user navigates to the right.
             *
             * @since BlackBerry 10.3.1
             */
            Right,
            /*!
             * @brief Occurs when the user navigates up.
             *
             * @since BlackBerry 10.3.1
             */
            Up,
            /*!
             * @brief Occurs when the user navigates down.
             *
             * @since BlackBerry 10.3.1
             */
            Down,
            /*!
             * @brief Occurs when an interaction is canceled.
             *
             * For example, this can occur when a containing control, such as a @c ListView, takes over the interaction
             * and starts to scroll itself.
             *
             * Cancel can be sent even when no other events have been received.
             *
             * @since BlackBerry 10.3.1
             */
            Cancel
         };

    private:
        /*! @cond PRIVATE */
        NavigationEventType();
        ~NavigationEventType();
        /*! @endcond */
    };
}
}

#endif /* cascades_navigationeventtype_h */

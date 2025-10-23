/*!
 * @copyright
 * Copyright Research In Motion Limited, 2014
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_trackpadeventtype_h
#define cascades_trackpadeventtype_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents different trackpad event types.
     *
     * Trackpad event types describe different stages of trackpad interaction.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT TrackpadEventType
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)

    public:
        /*!
         * @brief The trackpad event types.
         *
         * @since BlackBerry 10.3.1
         */
        enum Type {
            /*!
             * @brief Occurs when the user starts interacting with the trackpad.
             *
             * @since BlackBerry 10.3.1
             */
            Begin,
            /*!
             * @brief Occurs when the user moves a finger on the trackpad.
             *
             * @since BlackBerry 10.3.1
             */
            Move,
            /*!
             * @brief Occurs when the user stops interacting with the trackpad.
             *
             * @since BlackBerry 10.3.1
             */
            End,
            /*!
             * @brief Occurs when the user presses the trackpad.
             *
             * @since BlackBerry 10.3.1
             */
            Press,
            /*!
             * @brief Occurs when the user releases the trackpad.
             *
             * @since BlackBerry 10.3.1
             */
            Release,
            /*!
             * @brief Occurs when an interaction is canceled.
             *
             * For example when a containing control, such as a @c ListView, takes over the interaction
             * and starts to scroll.
             *
             * Cancel can be sent even when no other events
             * has been received.
             *
             * @since BlackBerry 10.3.1
             */
            Cancel
        };

    private:
        /*! @cond PRIVATE */
        TrackpadEventType();
        ~TrackpadEventType();
        /*! @endcond */
    };


}
}

#endif /* cascades_trackpadeventtype_h */

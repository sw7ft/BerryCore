/*!
 * @copyright
 * Copyright Research In Motion Limited, 2014
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_consumetrackpadevent_h
#define cascades_consumetrackpadevent_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents different trackpad event types to be consumed.
     *
     * Use this class to specify what types of trackpad events should be consumed
     * by the @c TrackpadHandler.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT ConsumeTrackpadEvent
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)
        Q_FLAGS (Types)

    public:
        /*!
         * @brief The trackpad event types to be consumed.
         *
         * @since BlackBerry 10.3.1
         */
        enum Type {
            /*!
             * @brief Don't consume any event. This is the default.
             *
             * @since BlackBerry 10.3.1
             */
            None = (0 << 0),

            /*!
             * @brief Consumes the events in the left direction.
             *
             * @since BlackBerry 10.3.1
             */
            Left = (1 << 0),

            /*!
             * @brief Consumes the events in the right direction.
             *
             * @since BlackBerry 10.3.1
             */
            Right = (1 << 1),

            /*!
             * @brief Consumes the events in the up direction.
             *
             * @since BlackBerry 10.3.1
             */
            Up = (1 << 2),

            /*!
             * @brief Consumes the events in the down direction.
             *
             * @since BlackBerry 10.3.1
             */
            Down = (1 << 3),

            /*!
             * @brief Consumes the events in both left and right directions.
             *
             * @since BlackBerry 10.3.1
             */
            Horizontal = (Left | Right),

            /*!
             * @brief Consumes the events in both up and down directions.
             *
             * @since BlackBerry 10.3.1
             */
            Vertical = (Up | Down),

            /*!
             * @brief Consumes the press events.
             *
             * @since BlackBerry 10.3.1
             */
            Press = (1 << 4),

            /*!
             * @brief Consumes the release events.
             *
             * @since BlackBerry 10.3.1
             */
            Release = (1 << 5),

            /*!
             * @brief Consumes all the events.
             *
             * @since BlackBerry 10.3.1
             */
            Any = (Horizontal | Vertical | Press | Release)

        };

     /*!
      * @brief Defines the combinations of trackpad event types to be consumed.
      *
      * This flag overrides the default @c ConsumeTrackpadEvent for a control.
      *
      * @see bb::cascades::ConsumeTrackpadEvent::Type
      *
      * @since BlackBerry 10.3.1
      */
      Q_DECLARE_FLAGS(Types, Type);

    private:
        /*! @cond PRIVATE */
        ConsumeTrackpadEvent();
        ~ConsumeTrackpadEvent();
        /*! @endcond */
    };

    /*! @cond PRIVATE */
    Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::ConsumeTrackpadEvent::Types)
    /*! @endcond */
}
}

#endif /* cascades_consumetrackpadevent_h */

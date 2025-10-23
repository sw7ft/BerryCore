/*!
 * @copyright
 * Copyright Research In Motion Limited, 2014
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_consumenavigationevent_h
#define cascades_consumenavigationevent_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents different navigation event types to be consumed.
     *
     * Use this class to specify what types of navigation events should be consumed
     * by the @c NavigationHandler.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT ConsumeNavigationEvent
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)
        Q_FLAGS (Types)

    public:
        /*!
         * @brief The navigation event types.
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
             * @brief Consumes the events that occur in the left direction.
             *
             * @since BlackBerry 10.3.1
             */
            Left = (1 << 0),

            /*!
             * @brief Consumes the events that occur in the right direction.
             *
             * @since BlackBerry 10.3.1
             */
            Right = (1 << 1),

            /*!
             * @brief Consumes the events that occur in the up direction.
             *
             * @since BlackBerry 10.3.1
             */
            Up = (1 << 2),

            /*!
             * @brief Consumes the events that occur in the down direction.
             *
             * @since BlackBerry 10.3.1
             */
            Down = (1 << 3),

            /*!
             * @brief Consumes the events that occur in both the left and right directions.
             *
             * @since BlackBerry 10.3.1
             */
            Horizontal = (Left | Right),

            /*!
             * @brief Consumes the events that occur in both the up and down directions.
             *
             * @since BlackBerry 10.3.1
             */
            Vertical = (Up | Down),

            /*!
             * @brief Consumes all the events that occur.
             *
             * @since BlackBerry 10.3.1
             */
            Any = (Horizontal | Vertical)

        };

     /*!
      * @brief Defines combinations of trackpad event types to be consumed.
      *
      * This flag overrides the default @c ConsumeNavigationEvent for a control.
      *
      * @see bb::cascades::ConsumeNavigationEvent::Type
      *
      * @since BlackBerry 10.3.1
      */
      Q_DECLARE_FLAGS(Types, Type);

    private:
        /*! @cond PRIVATE */
        ConsumeNavigationEvent();
        ~ConsumeNavigationEvent();
        /*! @endcond */
    };

    /*! @cond PRIVATE */
    Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::ConsumeNavigationEvent::Types)
    /*! @endcond */
}
}

#endif /* cascades_consumenavigationevent_h */

/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_flickmode_h
#define cascades_flickmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * 
    * @brief Represents different types of flick modes for a @c ListView.
    *
    * Flicking is a gesture used to scroll a @c ListView. The gesture involves a touch, drag, 
    * and release motion along the layout axis of the list.
    * For the flick behavior to be triggered, there must be sufficient speed in the motion of the gesture,
    * unless @c FlickMode::None is specified in which case flicking is disabled.
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT FlickMode
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
       /*!
        * @brief Represents the different types of flick modes.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type
        {
            /*! 
             * @brief The default flick gesture, which is currently set to Momentum.
             *
             * @since BlackBerry 10.0.0
             */ 
            Default = 0x0,
            /*!
             * @brief Flick gestures are disabled.
             *
             * @since BlackBerry 10.0.0
             */ 
            None = 0x1,
            /*! 
             * @brief A flick gesture along the layout axis generates a 
             * momentum scroll effect proportional to the speed of the 
             * flick gesture.
             *
             * @since BlackBerry 10.0.0
             */ 
            Momentum = 0x2,
            /*! 
             * @brief A flick gesture along the layout axis scrolls the @c ListView
             * a single item in the direction of the flick.
             *
             * When the flick occurs, the leading edge of the next item becomes aligned with the
             * top of the @c ListView.
             *
             * @note @c SingleItem is only supported for a @c ListView that uses a @c StackListLayout.
             *
             * @since BlackBerry 10.0.0
             */
            SingleItem = 0x3
        };

    private:
        FlickMode();
        ~FlickMode();
    };
  }
}

#endif // cascades_flickmode_h


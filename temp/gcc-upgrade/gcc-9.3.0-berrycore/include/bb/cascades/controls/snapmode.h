/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_snapmode_h
#define cascades_snapmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * 
    * @brief Represents different types of snap modes for a @c ListView.
    *
    * Snapping is used in @c %ListView to align items to the borders of the
    * visible area of the @c %ListView.
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT SnapMode
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
       /*!
        * @brief Represents the different types of snap modes.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type
        {
            /*! @brief Let the framework decide the snap mode.
             *
             * @since BlackBerry 10.0.0
             */
            Default = 0x0,
            /*! @brief Snapping is disabled.
             *
             * @since BlackBerry 10.0.0
             */
            None = 0x1,
            /*!
             * @brief Align the leading edge of an item to the leading edge of 
             * the visible area of the @c ListView.
             *
             * In a top-to-bottom @c %ListView layout, the first visible item
             * in the list is aligned to and snaps to the top of the @c %ListView.
             * In a bottom-to-top layout, the last visible item in the list is
             * aligned to and snaps to the bottom of the @c %ListView, and so on.
             *
             * @since BlackBerry 10.0.0
             */
            LeadingEdge = 0x2
        };

    private:
        SnapMode();
        ~SnapMode();
    };
  }
}

#endif // cascades_snapmode_h


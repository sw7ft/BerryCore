/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_scrollmode_h
#define cascades_scrollmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * 
    * @brief  Represents different types of scrolling modes.
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT ScrollMode
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
       /*!
        * @brief Specifies the directions that a @c Container can be scrolled.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type
        {
            /*! @brief Scrolling is not allowed.
             *
             * @since BlackBerry 10.0.0
             */
            None = 0x0,
            /*! @brief Scrolling is allowed in the vertical direction.
             *
             * @since BlackBerry 10.0.0
             */
            Vertical = 0x1,
            /*! @brief Scrolling is allowed in the horizontal direction.
             *
             * @since BlackBerry 10.0.0
             */
            Horizontal = 0x2,
            /*! @brief Scrolling is allowed in both directions.
             *
             * @since BlackBerry 10.0.0
             */
            Both = Vertical | Horizontal
        };
        
    private:       
        ScrollMode();
        ~ScrollMode();
    };
  }
}

#endif // cascades_scrollmode_h


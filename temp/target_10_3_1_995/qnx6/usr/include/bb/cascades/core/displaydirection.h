/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_displaydirection_h
#define cascades_displaydirection_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents the display direction of the device's screen plane.
     *
     * The direction value is the angle between device's natural orientation 
     * (with the BlackBerry logo pointing up) and the display's current physical direction
     * (in counter clockwise direction).
     * The natural orientation of the device is @c DisplayDirection::North (0 degrees).
     *
     * @xmlonly
     *     <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT DisplayDirection {
    private:
        Q_GADGET
        Q_ENUMS(Type)
    public:
        /*!
         * @brief The display directions
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
            /*!
             * @brief The BlackBerry logo is upright.
             *
             * @since BlackBerry 10.0.0
             */
            North = 0,
    
            /*!
             * @brief The BlackBerry logo is sideways - the text runs upwards and the display is
             * rotated 90 degrees to the left.
             *
             * @since BlackBerry 10.0.0
             */
            East = 90,
            
            /*!
             * @brief The BlackBerry logo is upside down - the display is rotated upside down.
             *
             * @since BlackBerry 10.0.0
             */
            South = 180,
    
            /*!
             * @brief The BlackBerry logo is sideways - the text runs downwards, and the display
             * is rotated 270 degrees to the left
             *
             * @since BlackBerry 10.0.0
             */
            West = 270
        };
    private:
    /*! @cond PRIVATE */
        DisplayDirection();
        ~DisplayDirection();
    /*! @endcond */
    };

}
}

#endif /* cascades_displaydirection_h */

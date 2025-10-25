/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_uiorientation_h
#define cascades_uiorientation_h

#include <QtCore/QObject>

#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents the orientation of the UI.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT UIOrientation {
    private:
        Q_GADGET
        Q_ENUMS(Type)
    public:
        /*!
         * @brief The UI orientation.
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
            /*!
             * @brief UI orientation is portrait, which means that display's height is larger than width.
             *
             * @since BlackBerry 10.0.0
             */
            Portrait = 0,
            /*!
             * @brief UI orientation is landscape, which means that display's width is larger than height.
             *
             * @since BlackBerry 10.0.0
             */
            Landscape = 1
        };

    private:
    /*! @cond PRIVATE */
        UIOrientation();
        ~UIOrientation();
    /*! @endcond */
    };

}
}

#endif /* cascades_uiorientation_h */

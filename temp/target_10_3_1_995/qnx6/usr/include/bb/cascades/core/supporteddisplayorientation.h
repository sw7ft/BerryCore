/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_supporteddisplayorientation_h
#define cascades_supporteddisplayorientation_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents display orientations supported by the application.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT SupportedDisplayOrientation {
        Q_GADGET
        Q_ENUMS(Type)
    public:
        /*!
         * Enum representing display orientations supported by the application.
         * 
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
            /*!
             * @brief UI orientation changes are disabled; device orientation changes will not result in
             * UI orientation changes.
             *
             * @since BlackBerry 10.0.0
             */
            CurrentLocked = 0,
            /*!
             * @brief Application supports all display orientations; all device orientation changes will result in
             * corresponding UI orientation change.
             *
             * @since BlackBerry 10.0.0
             */
            All = 1,
            /*!
             * @brief Application only supports landscape display orientation; landscape device orientation changes
             * will result in UI orientation change to @c UIOrientation::Landscape
             *
             * @since BlackBerry 10.0.0
             */
            DisplayLandscape = 2,
            /*!
             * @brief Application only supports portrait display orientation; portrait device orientation changes
             * will result in UI orientation change to @c UIOrientation::Portrait
             *
             * @since BlackBerry 10.0.0
             */
            DisplayPortrait = 3,
            /*!
             * @brief Application only supports the device's "native" display orientation, with BlackBerry logo
             * pointing up; device orientation changes will not result in UI orientation changes.
             *
             * @since BlackBerry 10.0.0
             */ 
            DeviceNorth = 4
        };
    private:
    /*! @cond PRIVATE */
        SupportedDisplayOrientation();
        ~SupportedDisplayOrientation();
    /*! @endcond */
    };

}
}

#endif /* cascades_supporteddisplayorientation_h */

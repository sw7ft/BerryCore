/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_scalingmethod_h
#define cascades_scalingmethod_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

        /*!
         * 
         * @brief A set of methods that specify how an image should be scaled.
         *
         * Scaling methods are used when displaying an image within an @c ImageView.
         *
         * - AspectFit: fits the image inside assigned area while keeping the correct aspect ratio.
         * - AspectFill: stretches and crops the image to fill the entire assigned area while keeping the aspect ratio.
         * - Fill: stretches the image to fit assigned area.
         * - None: scale is unmodified and content is either cropped or centered.
         *
         * @image html scaling_methods.png "This image shows the different scaling methods."
         *
         * The assigned area of the @c %ImageView is determined by its size parameters.
         *
         * @xmlonly
         * <apigrouping group="User interface/Core controls"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */

        class BBCASCADES_EXPORT ScalingMethod {
            Q_GADGET
            Q_ENUMS (Type)
        public:
            /*!
             * @brief Definitions of the scaling methods.
             *
             * @since BlackBerry 10.0.0
             */
            enum Type {
                /*! @brief Fit the image inside assigned area while keeping the correct aspect ratio.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AspectFit = 0,
                /*! @brief Stretch and crop the image to fill the entire assigned area while keeping the aspect ratio.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AspectFill = 1,
                /*! @brief Stretch the image to fit assigned area.
                 *
                 * @since BlackBerry 10.0.0
                 */
                Fill = 2,
                /*! @brief Scale is 1.0f and content is either cropped or centered.
                 *
                 * @since BlackBerry 10.0.0
                 */
                None = 3,
            };

        private:
            /*! \cond PRIVATE */
            ScalingMethod();
            ~ScalingMethod();
            /*! \endcond */
        };
        
    }
}


#endif // cascades_scalingmethod_h

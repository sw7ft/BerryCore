/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_animationrepeatcount_h
#define cascades_animationrepeatcount_h

#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

        /*!
         * 
         * @brief Defines useful constants for animation repeat count.
         * 
         * This class includes constants that describe how many times an animation, defined by an
         * @c AbstractAnimation subclass, should repeat.
         * 
         * @xmlonly
         * <apigrouping group="User interface/Animations"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        class BBCASCADES_EXPORT AnimationRepeatCount {
        public:

            /*! 
             * @brief Convenience constant for animations that
             *        should repeat forever.
             *
             * @since BlackBerry 10.1.0
             */ 
            static const int Forever;
            
        private:
            /*! \cond PRIVATE */
            AnimationRepeatCount();
            ~AnimationRepeatCount();
            /*! \endcond */
        };
    }
}

#endif	/* cascades_animationrepeatcount_h */


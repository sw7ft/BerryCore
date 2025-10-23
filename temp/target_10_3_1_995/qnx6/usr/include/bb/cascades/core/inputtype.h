/*!
 * @copyright
 * Copyright Research In Motion Limited, 2014
 * Research In Motion Limited. All rights reserved.
 * Proprietary and confidential.
*/

#ifndef cascades_inputtype_h
#define cascades_inputtype_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT InputType
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)

    public:
        /*!
         * @brief The input types.
         *
         * @since BlackBerry 10.3.1
         */
        enum Type {
            None = 0,

            /*!
             * @brief Represents input from keyboard devices
             *
             * @since BlackBerry 10.3.1
             */
            Keyboard = (1 << 0),

            /*!
             * @brief Represents input from pointer devices (mouse etc)
             *
             * @since BlackBerry 10.3.1
             */
            Pointer = (1 << 1),

            /*!
             * @brief Represents input from joystick devices (including the
             *        trackpad on Classic devices)
             *
             * @since BlackBerry 10.3.1
             */
            Joystick = (1 << 2),

            /*!
             * @brief Represents input from touch devices
             *
             * @since BlackBerry 10.3.1
             */
            Touch = (1 << 3)
        };

    private:
        /*! @cond PRIVATE */
        InputType();
        ~InputType();
        /*! @endcond */
    };


}
}

#endif /* cascades_inputtype_h */

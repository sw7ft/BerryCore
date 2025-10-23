/*!
 * @copyright
 * Copyright Research In Motion Limited, 2014
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_inputsource_h
#define cascades_inputsource_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents the different input sources from which the event was generated from, e.g touch or trackpad.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT InputSource
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)

    public:
        /*!
         * @brief The input source types.
         *
         * @since BlackBerry 10.3.1
         */
        enum Type {
            /*!
             * @brief Occurs if the event was generated from touch.
             *
             * @since BlackBerry 10.3.1
             */
            Touch,
            /*!
             * @brief Occurs if the event was generated from trackpad.
             *
             * @since BlackBerry 10.3.1
             */
            Trackpad
        };

    private:
        /*! @cond PRIVATE */
        InputSource();
        ~InputSource();
        /*! @endcond */
    };


}
}

#endif /* cascades_inputsource_h */

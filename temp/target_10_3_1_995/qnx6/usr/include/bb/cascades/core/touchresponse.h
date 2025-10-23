/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_touchresponse_h
#define cascades_touchresponse_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * @brief Represents different touch responses used for event reactions.
 *
 * @see bb::cascades::TouchReaction
 *
 * @xmlonly
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TouchResponse {
    Q_GADGET
    Q_ENUMS (Type)
public:

    /*!
     * @brief Enumeration for specifying different touch responses.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*! @brief Starts tracking touch events until the next touch up.
         *
         * @since BlackBerry 10.0.0
         */
        StartTracking
    };

private:
    /*! @cond PRIVATE */
    TouchResponse();
    ~TouchResponse();
    /*! @endcond */
};

}
}

#endif //cascades_touchresponse_h

/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_propagationphase_h
#define cascades_propagationphase_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {
    
    /*!
     * @brief Represents different event propagation phases.
     *
     * @see @c bb::cascades::Event
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT PropagationPhase
    {
    private:
        Q_GADGET
        Q_ENUMS (Type)
        
    public:
        /*!
         * @brief The phases of event propagation.
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
            /*! 
             * @brief Used for events that does not propagate.
             *
             * @since BlackBerry 10.0.0
             */
            None,
            /*! 
             * @brief The capture phase starts at the root of node tree and continues
             * towards the target leaf node.
             *
             * @since BlackBerry 10.0.0
             */
            Capturing,
            /*! 
             * @brief A target is the intended recipient of the event.
             *
             * @since BlackBerry 10.0.0
             */
            AtTarget,
            /*! 
             * @brief The bubble phase starts at the target and continues towards the
             * root of the node tree.
             *
             * @since BlackBerry 10.0.0
             */
            Bubbling
        };

    private:
        PropagationPhase();
        ~PropagationPhase();
    };
    
}
}

#endif /* cascades_propagationphase_h */

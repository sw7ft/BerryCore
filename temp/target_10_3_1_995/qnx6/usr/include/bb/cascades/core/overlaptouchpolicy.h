/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_overlaptouchpolicy_h
#define cascades_overlaptouchpolicy_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

/*! 
 * @brief Specifies whether overlapped nodes receive touch interaction.
 *
 * Setting the overlap touch policy to @c allow does not guarantee
 * that touch events reach down to the overlapped node. The behavior
 * depends on the nature of the overlapping node.
 * If it is an interactive control, such as a @c Slider or @c Button, the
 * internal event handling may cause the overlapping control to consume
 * events, which prevents them from reaching the overlapped control.
 * Setting the overlap touch policy to @c allow is mostly suited for non-interactive
 * controls without internal event handling, such as a @c Container, a
 * @c Label, or an @c Image.
 *
 * @see VisualNode::setOverlapTouchPolicy()
 *
 * @xmlonly
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT OverlapTouchPolicy {
    Q_GADGET
    Q_ENUMS(Type)
public:

    /*!
     * @brief Enumeration for specifying whether overlapped nodes should be allowed to receive touch interaction.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
       /*!
        * @brief Prevent overlapped nodes from receiving touch interaction.
        *
        * @since BlackBerry 10.0.0
        */
        Deny,
       /*!
        * @brief Allow overlapped nodes to receive touch interaction.
        *
        * @since BlackBerry 10.0.0
        */
        Allow
    };

private:
    /*! @cond PRIVATE */
    OverlapTouchPolicy();
    ~OverlapTouchPolicy();
    /*! @endcond */
};
}
}

#endif // cascades_overlaptouch_h


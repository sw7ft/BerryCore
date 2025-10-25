/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_eventreaction_h
#define cascades_eventreaction_h

#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

class EventReactionPrivate;

/*!
 * @brief Abstract base class for all event reactions.
 *
 * @see TouchBehavior
 *
 * @xmlonly
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT EventReaction: public UIObject {
    Q_OBJECT

public:
    ~EventReaction();

protected:
    /*! @cond PRIVATE */
    EventReaction(EventReactionPrivate &_d_ptr);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(EventReaction)
    Q_DISABLE_COPY(EventReaction)
    /*! @endcond */
};

}
}

QML_DECLARE_TYPE(bb::cascades::EventReaction)

#endif //cascades_eventreaction_h

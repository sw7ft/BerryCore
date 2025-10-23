/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_gesturehandler_h
#define cascades_gesturehandler_h

#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

class GestureHandlerPrivate;

/*!
 * @brief A base class for all gesture handlers which can be used to react to various gestures.
 *
 * Existing gesture handlers:
 * - TapHandler, handles single tap gesture
 * - DoubleTapHandler, handles double tap gesture
 * - PinchHandler, handles pinch gesture
 * - LongPressHandler, handles long press gesture
 *
 * Example of how to connect a gesture handler to a visual node:
 *
 * @code
 * Container* pContainer = Container::create();
 *
 * LongPressHandler *pLongPressHandler = LongPressHandler::create()
 *     .onLongPressed(pMyObject, SLOT(onLongPressedHandler()));
 *
 * pContainer->addGestureHandler(pLongPressHandler);
 * @endcode
 *
 * Matching code in QML:
 *
 * @code
 * Container {
 *     gestureHandlers: [
 *         LongPressHandler {
 *             onLongPressed: {
 *                 console.log("LongPress at position " + event.x + ", " + event.y)
 *             }
 *         }
 *     ]
 * }
 * @endcode
 *
 * @see VisualNode::addGestureHandler()
 *
 * @xmlonly
 *     <apigrouping group="User interface/Events"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT GestureHandler : public UIObject {
    Q_OBJECT

public:
    virtual ~GestureHandler();

protected:
    /*! @cond PRIVATE */
    GestureHandler(GestureHandlerPrivate &_d_ptr, UIObject* parent = 0);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(GestureHandler)
    Q_DISABLE_COPY(GestureHandler)
    /*! @endcond */

public:
    /*! @cond PRIVATE */
    typedef UIObject BaseClass;
    /*! @endcond */

protected:
    /*!
     * @brief Builder for constructing GestureHandler objects
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>
    class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
    {
    protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
        {
        }
    };
};

}
}

QML_DECLARE_TYPE(bb::cascades::GestureHandler)

#endif /* cascades_gesturehandler_h */

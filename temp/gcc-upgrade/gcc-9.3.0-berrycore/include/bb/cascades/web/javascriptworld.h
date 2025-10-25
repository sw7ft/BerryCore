/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_javascriptworld_h
#define cascades_javascriptworld_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>

namespace bb {
  namespace cascades {

   /*!
    * @brief The execution environment in which calls to @c evaluateJavaScript
    * should run.
    *
    * @see @c evaluateJavaScript()
    *
    * @xmlonly
    * <qml>
    * <class register="enum-only"/>
    * </qml>
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT JavaScriptWorld
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:

        /*!
         * @brief The execution environment in which calls to
         * @c evaluateJavaScript should run.
         *
         * @since BlackBerry 10.0.0
         */
         enum Type {
              Normal,    ///< The world shared with scripts and data included by the page.
              Isolated,  ///< Another world which is isolated from the normal world.
         };
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_javascriptworld_h

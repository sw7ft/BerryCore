/* Copyright (c) 2013 BlackBerry. All rights reserved. */

#ifndef cascades_abstracteventhandler_h
#define cascades_abstracteventhandler_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
  namespace cascades {

    class AbstractEventHandlerPrivate;

    /*!
     * @brief The base class for event handlers.
     *
     * Only classes deriving from the @c %AbstractEventHandler class can be
     * added to @c %VisualNode::eventHandlers for event handling.
     *
     * @see VisualNode::eventHandlers
     *
     * @xmlonly
     * <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT AbstractEventHandler : public UIObject {
      Q_OBJECT

    public:
      /*!
       * @brief Destructs the event handler.
       *
       * @since BlackBerry 10.3.0
       */
      virtual ~AbstractEventHandler();

    protected:
      /*! @cond PRIVATE */
      AbstractEventHandler(AbstractEventHandlerPrivate &_d_ptr, UIObject* parent = 0);
      /*! @endcond */

    private:
      /*! @cond PRIVATE */
      Q_DECLARE_PRIVATE(AbstractEventHandler)
      Q_DISABLE_COPY(AbstractEventHandler)
      typedef UIObject BaseClass;
      /*! @endcond */

    protected:
      /*!
       * @brief A builder template for constructing an @c %AbstractEventHandler.
       *
       * @since BlackBerry 10.3.0
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

QML_DECLARE_TYPE(bb::cascades::AbstractEventHandler)

#endif /* cascades_abstracteventhandler_h */

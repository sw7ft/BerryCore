/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_abstracttextfilter_h
#define cascades_abstracttextfilter_h

#include <bb/cascades/core/baseobject.h>

namespace bb {
    namespace cascades {

      class AbstractTextFilterPrivate;

         /*!
         *
         * @brief The base class for all text filter subclasses.
         *
         * A text filter process the text entered or set on a text control
         * before it is presented.
         *
         * @see @c SingleLineTextFilter
         *
         * @c %SingleLineTextFilter also describes more how text filters
         * can be used.
         *
         * @since BlackBerry 10.0.0
         *
         * @xmlonly
         * <apigrouping group="User interface/Text"/>
         * @endxmlonly
         */
      class BBCASCADES_EXPORT AbstractTextFilter : public BaseObject {
          Q_OBJECT

      public:
        virtual ~AbstractTextFilter();


        /*! @cond PRIVATE */
      protected:
        AbstractTextFilter(AbstractTextFilterPrivate &_d_ptr, BaseObject *parent = 0);
        /*! @endcond */

      private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(AbstractTextFilter)
        Q_DISABLE_COPY(AbstractTextFilter)
        /*! @endcond */

      public:
        /*! @cond PRIVATE */
        typedef AbstractTextFilter ThisClass;
        typedef BaseObject BaseClass;
        /*! @endcond */

        /*!
        * @brief A builder template for constructing an AbstractTextFilter
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

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::AbstractTextFilter)
/*! @endcond */

#endif /* cascades_abstracttextfilter_h */

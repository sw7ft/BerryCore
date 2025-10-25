/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_singlelinetextfilter_h
#define cascades_singlelinetextfilter_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstracttextfilter.h>
#include <bb/cascades/core/baseobject.h>

namespace bb {
    namespace cascades {

        class SingleLineTextFilterPrivate;

        /*!
        * @brief A text filter that prevents line breaks from being added to text in a text control.
        *
        * If installed on a text control, a @c %SingleLineTextFilter prevents the document from having explicit line breaks.
        * Line breaks will be stripped away from content that is added to the document
        * through pasting, binding, editing or other mechanisms. If two words are separated
        * with a line break, the @c %SingleLineTextFilter will ensure that the word separation
        * is maintained, typically by inserting a white space. If the text doesn't fit on
        * one single line, the layout may still display the text on multiple lines if the
        * control allows for it. When this happens, automatic line breaks will be computed
        * because the @c %SingleLineTextFilter has removed all explicit line breaks.
        *
        * Creating a @c %TextArea with a @c %SingleLineTextFilter, using the builder pattern:
        * @code
        * TextArea *textArea = TextArea::create()
        *     .textFilter(SingleLineTextFilter::create())
        *     .text("This text\ncontains line\n breaks that 
        *           have been \nremoved by the filter.");
        * @endcode
        *
        * Setting the @c %SingleLineTextFilter on a @c %TextArea, in QML:
        * @code
        *    TextArea {
        *       textFilter: SingleLineTextFilter { }
        *       text: "This text\ncontains line\n breaks that 
        *              have been \nremoved by the filter."
        *
        *       onTextFilterChanged: {
        *         if(textFilter) {
        *            console.debug("A filter was added.");
        *         }
        *       }
        *    }
        * @endcode
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT SingleLineTextFilter : public AbstractTextFilter {
            Q_OBJECT

        public:
            /*!
            * @brief Constructs a @c %SingleLineTextFilter.
             *
             * @since BlackBerry 10.0.0
            */
            explicit SingleLineTextFilter(BaseObject *parent = 0);
            /*!
            * @brief Destructs the @c %SingleLineTextFilter.
             *
             * @since BlackBerry 10.0.0
            */
            virtual ~SingleLineTextFilter();

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(SingleLineTextFilter)
            Q_DISABLE_COPY(SingleLineTextFilter)
            /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef SingleLineTextFilter ThisClass;
        typedef AbstractTextFilter BaseClass;
        /*! @endcond */

        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }
        public:
        };

        class Builder : public TBuilder<Builder, SingleLineTextFilter>
        {
        public:
            Builder() : TBuilder<Builder, SingleLineTextFilter>(new SingleLineTextFilter())
            {
            }
        };

        static Builder create()
        {
            return Builder();
        }

    };
    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::SingleLineTextFilter)
/*! @endcond */

#endif /* cascades_singlelinetextfilter_h */

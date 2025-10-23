/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_contentsecurity_h
#define cascades_contentsecurity_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/system/SecurityPerimeter.hpp>
#include <bb/cascades/resources/abstractcontentsecurity.h>
#include <bb/cascades/core/baseobject.h>
//
namespace bb {
    namespace cascades {

        class ContentSecurityPrivate;

        /*!
        * @brief Allows for associating a control with a security perimeter.
        *
        * Hybrid applications can use this to set the security perimeter of the control.
        * This will allow the control to interact within the set perimeter of the system.
        *
        * @code
        * TextArea {
        *     content.flags: TextContentFlag.ActiveText
        *     text: "Enterprise Link: www.rim.com will open browser in work perimeter"
        *     attachedObjects: [
        *         ContentSecurity  {
        *             id: contentsecurity
        *             defaultPerimeter: SecurityPerimeter.Enterprise
        *         }
        *     ]
        * }
        * @endcode
        * @xmlonly
        * <apigrouping group="User interface/Resources"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT ContentSecurity : public AbstractContentSecurity {
            Q_OBJECT

        public:
            /*!
            * @brief Constructs a @c %ContentSecurity.
            *
            * @since BlackBerry 10.0.0
            */
            ContentSecurity(BaseObject *parent = 0);
            /*!
            * @brief Destructs the @c %ContentSecurity.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~ContentSecurity();

        /*!
        * @brief A read only property that indicates whether there is enterprise content.
        *
        * The default value is @c false.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool hasEnterpriseContent
            READ hasEnterpriseContent
            NOTIFY hasEnterpriseContentChanged
            FINAL);

        /*!
        * @brief A read only property that indicates if there is personal content.
        *
        * The default value is @c false.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool hasPersonalContent
            READ hasPersonalContent
            NOTIFY hasPersonalContentChanged
            FINAL);

        /*!
        * @brief A read only property that indicates if there is unknown content.
        *
        * The default value is @c false.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool hasUnknownContent 
            READ hasUnknownContent 
            NOTIFY hasUnknownContentChanged
            FINAL);

        /*!
        * @brief Indicates whether there is enterprise content.
        *
        * @return @c true if there is enterprise content, @c false otherwise. The default value is @c false.
        *
        * @since BlackBerry 10.0.0
        */
        bool hasEnterpriseContent();

        /*!
        * @brief Indicates whether there is personal content.
        *
        * @return @c true if there is personal content, @c false otherwise. The default value is @c false.
        *
        * @since BlackBerry 10.0.0
        */
        bool hasPersonalContent();

        /*!
        * @brief Indicates whether there is unknown content.
        *
        * @return @c true if there is unknown content, @c false otherwise. The default value is @c false.
        *
        * @since BlackBerry 10.0.0
        */
        bool hasUnknownContent();

Q_SIGNALS:
        /*!
        * @brief Emitted when the @c #hasEnterpriseContent property has changed.
        *
        * @param hasEnterpriseContent @c true if the content now contains enterprise content, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void hasEnterpriseContentChanged(bool hasEnterpriseContent);

        /*!
        * @brief Emitted when the @c #hasPersonalContent property has changed.
        *
        * @param hasPersonalContent @c true if the content now contains personal content, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void hasPersonalContentChanged(bool hasPersonalContent);

        /*!
        * @brief Emitted when the @c #hasUnknownContent property has changed.
        *
        * @param hasUnknownContent @c true if the content now contains unknown content, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void hasUnknownContentChanged(bool hasUnknownContent);

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(ContentSecurity)
                Q_DISABLE_COPY(ContentSecurity)
                /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef ContentSecurity ThisClass;
        typedef AbstractContentSecurity BaseClass;
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

        class Builder : public TBuilder<Builder, ContentSecurity>
        {
        public:
            Builder() : TBuilder<Builder, ContentSecurity>(new ContentSecurity())
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

QML_DECLARE_TYPE(bb::cascades::ContentSecurity)

#endif /* cascades_contentsecurity_h */

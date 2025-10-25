/* Copyright (C) 2012-2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_LABELAUTOSIZEPROPERTIES_H
#define BB_CASCADES_LABELAUTOSIZEPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/BaseObject>

namespace bb {
    namespace cascades {
        class LabelAutoSizePropertiesPrivate;
        
        /*!
         * @brief Represents the auto size properties of a Label
         *
         * The @c LabelAutoSizeProperties configures how the Label adapts its size to its content.
         *
         * @xmlonly
         * <apigrouping group="User interface/Text"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        class BBCASCADES_EXPORT LabelAutoSizeProperties : public BaseObject
        {
            Q_OBJECT
            
            /*!
             * @brief The maximum number of lines that the @c Label can expand to.  
             *
             * When this value is set, a @c Label will automatically expand its height
             * to accomodate additional text, up to the number of lines that the property specifies.
             * The size of the control will not automatically increase in size
             * past what is needed to show the specified number of lines.
             *
             * There are other mechanisms that can affect the size of the control as well (layout 
             * and explicit sizing using preferred size properties for instance). This 
             * property does not limit such mechanisms from extending the size of the control
             * past what is specified by this property.
             *
             * @note @c Label's @c multiline property must be set to @c true in order
             * to wrap the text on multiple lines.
             *
             * @code
                Label {
                    multiline: true
                    autoSize {
                        maxLineCount: 2
                    }
                }
             * @endcode
             *
             * The default value is @c -1
             *
             * @since BlackBerry 10.1.0
             */
            Q_PROPERTY(int maxLineCount
                       READ maxLineCount
                       WRITE setMaxLineCount
                       RESET resetMaxLineCount
                       NOTIFY maxLineCountChanged
                       FINAL)

        public:
            /*!
             * @brief Returns the maximum number of lines that the @c Label can expand to.
             *
             * @return The maximum number of lines that the label can expand to.
             *
             * @since BlackBerry 10.1.0
             */
            int maxLineCount() const;

            /*!
             * @brief Sets the maximum number of lines that the @c Label should auto size to.
             *
             * The value must be positive or it will be ignored.
             * Use restMaxLineCount() to reset the property to the default value.
             *
             * @param maxLineCount The new positive @c maxLineCount value
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void setMaxLineCount(int maxLineCount);

            /*!
             * @brief Resets @c maxLineCount to its default state.
             *
             * The default state is @c -1.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void resetMaxLineCount();

        Q_SIGNALS:
            /*!
             * @brief Emitted when the @c maxLineCount is changed.
             *
             * @param maxLineCount The new @c maxLineCount.
             *
             * @since BlackBerry 10.1.0
             */
            void maxLineCountChanged(int maxLineCount);

        protected:
            /*! @cond PRIVATE */
            LabelAutoSizeProperties(BaseObject *parent = 0);
            virtual ~LabelAutoSizeProperties();
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(LabelAutoSizeProperties)
            Q_DISABLE_COPY(LabelAutoSizeProperties)
            /*! @endcond */
        };
    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::LabelAutoSizeProperties)
/*! @endcond */

#endif // BB_CASCADES_LABELAUTOSIZEPROPERTIES_H

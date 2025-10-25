/* Copyright (C) 2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTAREAAUTOSIZEPROPERTIES_H
#define BB_CASCADES_TEXTAREAAUTOSIZEPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/BaseObject>

namespace bb {
namespace cascades {
    class TextAreaAutoSizePropertiesPrivate;

    /*!
     * @brief Represents the auto size properties of a TextArea.
     *
     * The @c TextAreaAutoSizeProperties configures how the @c TextArea adapts its size to its content.
     *
     * @xmlonly
     * <apigrouping group="User interface/Text"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT TextAreaAutoSizeProperties : public BaseObject
    {
        Q_OBJECT

        /*!
         * @brief The maximum number of visible lines that the @c TextArea can expand to.
         *
         * When this value is set, a @c TextArea will automatically expand its height
         * to accomodate additional text, up to the number of lines that the property specifies.
         * The size of the control will not automatically increase in size
         * past what is needed to show the specified number of lines.
         *
         * There are other mechanisms that can affect the size of the control as well (layout
         * and explicit sizing using preferred size properties for instance). This
         * property does not limit such mechanisms from extending the size of the control
         * past what is specified by this property.
         *
         * @code
         * TextArea {
         *     autoSize {
         *         maxLineCount: 2
         *     }
         * }
         * @endcode
         *
         * The default value is @c -1, meaning that the maximum line count is not set.
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(int maxLineCount
                   READ maxLineCount
                   WRITE setMaxLineCount
                   RESET resetMaxLineCount
                   NOTIFY maxLineCountChanged
                   FINAL)

    public:
        /*!
         * @brief Returns the maximum number of visible lines that the @c TextArea can expand to.
         *
         * @return The maximum number of lines that the @c TextArea can expand to, or @c -1 if no limit is set.
         *
         * @since BlackBerry 10.2.0
         */
        int maxLineCount() const;

        /*!
         * @brief Sets the maximum number of visible lines that the @c TextArea should auto size to.
         *
         * The value must be @c -1 or greater than @c 0, otherwise it will be ignored.
         * The value @c -1 is equivalent to calling @c resetMaxLineCount.
         *
         * @param maxLineCount The new @c maxLineCount value
         *
         * @since BlackBerry 10.2.0
         */
        Q_SLOT void setMaxLineCount(int maxLineCount);

        /*!
         * @brief Resets @c maxLineCount to its default state.
         *
         * The default state is @c -1.
         *
         * @since BlackBerry 10.2.0
         */
        Q_SLOT void resetMaxLineCount();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c maxLineCount is changed.
         *
         * @param maxLineCount The new @c maxLineCount, or @c -1 if the maximum line count has been reset.
         *
         * @since BlackBerry 10.2.0
         */
        void maxLineCountChanged(int maxLineCount);

    protected:
        /*! @cond PRIVATE */
        TextAreaAutoSizeProperties(BaseObject *parent = 0);
        virtual ~TextAreaAutoSizeProperties();
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TextAreaAutoSizeProperties)
        Q_DISABLE_COPY(TextAreaAutoSizeProperties)
        /*! @endcond */
    };

} // namespace cascades
} // namespace bb

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextAreaAutoSizeProperties)
/*! @endcond */

#endif // BB_CASCADES_TEXTAREAAUTOSIZEPROPERTIES_H

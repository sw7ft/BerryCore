/* Copyright (C) 2012-2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTEDITOR_H
#define BB_CASCADES_TEXTEDITOR_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <Qt/qobject.h>

namespace bb {
    namespace cascades {

        class TextEditorPrivate;

        /*!
        * @brief Use for text selection and editing.
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT TextEditor : public QObject
        {
            Q_OBJECT

                /*!
                * @brief Currently selected text
                *
                * The currently seleced text in plain text format.
                *
                 *
                 * @since BlackBerry 10.0.0
                */
                Q_PROPERTY(QString selectedText
                READ selectedText 
                NOTIFY selectedTextChanged 
                FINAL)

                /*!
                * @brief The cursor position. The default value is 0.
                         Setting a value less then zero or beyond the end of the document will result in clamping.
                         Setting the cursor position will reset the current selection.
                 *
                 * @since BlackBerry 10.0.0
                */
                Q_PROPERTY(int cursorPosition
                READ cursorPosition
                WRITE setCursorPosition
                RESET resetCursorPosition
                NOTIFY cursorPositionChanged                
                FINAL)

                /*!
                * @brief The position of the start of the selection range. The default value is 0.
                         Setting a value less then zero or beyond the end of the document will result in clamping.
                 *
                 * @since BlackBerry 10.0.0
                */
                Q_PROPERTY(int selectionStart
                READ selectionStart
                NOTIFY selectionStartChanged
                FINAL)

                /*!
                * @brief The position of the end of the selection range. The default value is 0.
                                            Setting a value less then zero or beyond the end of the document will result in clamping.
                 *
                 * @since BlackBerry 10.0.0
                */
                Q_PROPERTY(int selectionEnd
                READ selectionEnd
                NOTIFY selectionEndChanged
                FINAL)


        public:
            /*!
            * @brief Returns the currently selected text
            *
            * @return The currently selected text in plain text.
             *
             * @since BlackBerry 10.0.0
            */
            QString selectedText() const;

            /*!
            * @brief The cursor position. The default value is 0.
             *
             * @since BlackBerry 10.0.0
            */
            int cursorPosition() const;

            /*!
            * @brief The start of the selection range. The default value is 0.
             *
             * @since BlackBerry 10.0.0
            */
            int selectionStart() const;

            /*!
            * @brief The end of the selection range. The default value is 0.
             *
             * @since BlackBerry 10.0.0
            */
            int selectionEnd() const;

            /*!
            * @brief Insert text at the current position
            *
            * Inserts unformatted text at the current position, replaces any selection. 
            * The text will be formatted according to the format at the insertion point.
            *
            * @param text The text to insert
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void insertPlainText(QString text);

            /*!
            * @brief Set the selection
            *
            * Set the selection between start and end and places the cursor at the end position.
            * Setting end < start will result in undefined behaviour.             
            *
            * @param start Start position of selection
            *              Values less then zero or beyond the end of the document length will be clamped.
            *
            * @param end End position of selection
            *            Values less then zero or beyond the end of the document length will be clamped.
             *
             * @since BlackBerry 10.0.0
            */
            Q_INVOKABLE void setSelection(int start, int end);

            /*!
            * @brief Set the cursor position
            *
            * @param cursorPosition The new cursor position
            *                       Values less then zero or beyond the end of the document length will be clamped.
             *
             * @since BlackBerry 10.0.0
            */
            void setCursorPosition(int cursorPosition);

            /*!
            * @brief Resets the cursor position to its default value of 0
             *
             * @since BlackBerry 10.0.0
            */
            void resetCursorPosition();

        Q_SIGNALS:
            /*!
            * @brief Emitted when the selected text has changed.
            *
            * @param selectedText The new selected text.
             *
             * @since BlackBerry 10.0.0
            */
            void selectedTextChanged(QString selectedText);

            /*!
            * @brief Emitted when the cursor position has changed.
            *
            * @param cursorPosition The new cursor position.
             *
             * @since BlackBerry 10.0.0
            */
            void cursorPositionChanged(int cursorPosition);

            /*!
            * @brief Emitted when the start of the selection range has changed.
            *
            * @param selectionStart The new start of the selection.
             *
             * @since BlackBerry 10.0.0
            */
            void selectionStartChanged(int selectionStart);

            /*!
            * @brief Emitted when the end of the selection range has changed.
            *
            * @param selectionEnd The new end of the selection.
             *
             * @since BlackBerry 10.0.0
            */
            void selectionEndChanged(int selectionEnd);

        protected:
            /*! @cond PRIVATE */
            TextEditor(QObject *parent = 0);
            virtual ~TextEditor();
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(TextEditor)
            Q_DISABLE_COPY(TextEditor)
            TextEditorPrivate *d_ptr;
            /*! @endcond */
        };

    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextEditor)
/*! @endcond */

#endif // BB_CASCADES_TEXTEDITOR_H

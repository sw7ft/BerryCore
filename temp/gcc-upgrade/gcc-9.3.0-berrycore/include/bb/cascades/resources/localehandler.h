/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_localehandler_h
#define cascades_localehandler_h

#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/BaseObject>

namespace bb {
    namespace cascades {

        class LocaleHandlerPrivate;

        /*!
        * @brief Enables dynamic translation and locale updates in C++ and QML.
        *
        * When the language or locale of the device changes, this class is responsible
        * for dynamically updating text with any necessary changes. If you're using QML, this class
        * represents a more advanced approach to dynamic translation, since it enables you to
        * perform other tasks related to localization, such as updating images with localized images.
        * 
        * In a QML-defined UI, if you're only required to update text properties, the @c Retranslate class
        * represents a simpler way of providing dynamic updates.
        * 
        * Here's an example of how to connect the @c languageChanged() signal to a slot
        * where text language can be updated. Calling @c tr() will
        * update text with the translated text given that translation keys
        * are available for the given language.
        *
        * @code
        * void MyClass::init() {
        *   myTranslator = new QTranslator();
        *   myLocaleHandler = new LocaleHandler(this);
        *   QObject::connect(myLocaleHandler, SIGNAL(systemLanguageChanged()),
        *                    this, SLOT(onSystemLanguageChanged()));
        *   QObject::connect(myLocaleHandler, SIGNAL(languageChanged()),
        *                    this, SLOT(onLanguageChanged()));
        * }
        *
        * // Called when the system language is changed
        * void MyClass::onSystemLanguageChanged() {
        *   QLocale systemLocale;
        *   if (systemLocale.language() == QLocale::Swedish) {
        *       myTranslator->load("path/to/swedish/translator");
        *   } else if (systemLocale.language() == QLocale::English) {
        *       myTranslator->load("path/to/english/translator");
        *   } else {
        *       myTranslator->load("path/to/default/translator");
        *   }   
        *   QCoreApplication::instance()->installTranslator(myTranslator);
        * }
        *
        * // Called when new translators are installed
        * void MyClass::onLanguageChanged() {
        *   someLabel->setText(tr("translate me"));
        * }
        * @endcode
        *
        * Here's how to add a @c %LocaleHandler as an @c attachedObject to a label, in QML. The
        * @c languageChanged() signal is emitted 
        * when a translator is installed using the QCoreApplication::installTranslator() function.
        *
        * From the @c onLanguageChanged signal handler it is also possible to do more
        * advanced locale specific updates like changing images that depend on locale.
        *
        * @code
        * Label {
        *   id: localeHandlerLabel
        *   objectName: "localeHandlerLabel"
        *   text: qsTr("LocaleHandler")
        *
        *   attachedObjects: [
        *       LocaleHandler  {
        *           id: myLocaleHandler
        *           onLanguageChanged: {
        *               localeHandlerLabel.text = qsTr("LocaleHandler")
        *           }
        *       }
        *   ]
        * }
        * @endcode
        *
        * @xmlonly
        * <apigrouping group="User interface/Resources"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT LocaleHandler : public BaseObject {
            Q_OBJECT

        public:
            /*!
            * @brief Constructs a @c %LocaleHandler.
             *
             * @since BlackBerry 10.0.0
            */
            LocaleHandler(QObject *parent = 0);

            /*!
            * @brief The destructor of the @c %LocaleHandler.
             *
             * @since BlackBerry 10.0.0
            */
            virtual ~LocaleHandler();

Q_SIGNALS:
            /*!
            * @brief Emitted when the language or locale is changed.
            *
             *
             * @since BlackBerry 10.0.0
            */
            void localeOrLanguageChanged();

            /*!
            * @brief Emitted when the region locale is changed.  Applications should use this signal 
            * to handle regional formatting like currency and dates.
            *
             *
             * @since BlackBerry 10.0.0
            */
            void localeChanged();

            /*!
            * @brief Emitted when the language is changed and a new translator is available.  Applications 
            * should use this signal to retranslate strings in the UI.
            *
             *
             * @since BlackBerry 10.0.0
            */
            void languageChanged();

            /*!
            * @brief Emitted when the system language is changed.  Applications should use this signal
            * to load new translators for the application.
            *
             *
             * @since BlackBerry 10.0.0
            */
            void systemLanguageChanged();

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(LocaleHandler)
            Q_DISABLE_COPY(LocaleHandler)
            /*! @endcond */
        };

    }
}
QML_DECLARE_TYPE(bb::cascades::LocaleHandler)

#endif /* cascades_LocaleHandler_h */

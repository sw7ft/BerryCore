/*!
 * @copyright
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_uiconfig_h
#define cascades_uiconfig_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

    class UIConfigPrivate;
    class UIPalette;

    /*!
     * @brief Provides UI configuration properties for a @c UiObject.
     *
     * This class provides functions for converting design units into pixels
     * and for exposing the ui palette used within the current context.
     *
     * Design units are device-independent values that are converted into
     * explicit pixel values optimized for the screen density and resolution of a particular device.
     * Both the @c du() and @c sdu() methods convert a design unit into pixels, with the difference
     * being that @c sdu() rounds the value off to the nearest whole number.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT UIConfig : public QObject {
        Q_OBJECT

    public:
        /*!
         * @brief Provides access to the palette used in a @c UIObject.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bb::cascades::UIPalette* palette READ palette NOTIFY paletteChanged FINAL)

        /*!
         * @brief Specifies whether the UI should use the compact mode concept to define the appearance
         * of visual components.
         *
         * "Compact mode" is a design concept that specifies how components should appear on devices with 
         * less screen real estate. In this mode, vertical white space and non-essential decorations
         * are shrunk slightly to allow for a higher information density.
         *
         * The property is dynamic and can be influenced by changes from outside of the application.
         * Care needs to taken when visually aligning components that depend on this mode.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bool compact READ isCompact NOTIFY compactChanged FINAL)

        /*!
         * @brief A scale factor that depends on the information density context.
         *
         * The dynamic design factor is a modifier with the base of 1.0 that can be used to adapt UI dimensions 
         * when the information density changes. One way that information density changes is through
         * the system font (as the system font becomes smaller, information density rises).
         * 
         * If your app contains a lot of text, you might want other dimensions (margins, padding, and so on)
         * to change as the size of text changes. By updating other dimensions along with the text, your app is always making the
         * best use of the space that's available.
         *
         * Some controls, such as the @c StandardListItem, are automatically updated when the information density changes.
         * Other controls require that you update them yourself. To allow your app to update these controls as the information
         * density changes, you can add the information density factor to your existing @c du() and @c sdu() methods by
         * multiplying the design unit value with the @c dduFactor.
         *
         * Before:
         * @code
         * topPadding: ui.du(11.5)
         * @endcode
         * 
         * After:
         * @code
         * topPadding: ui.du(11.5 * ui.dduFactor)
         * @endcode
         *
         * You can also replace your existing @c du() and @c sdu() methods with @c ddu() and @c sddu() respectively, but
         * this approach requires that you connect to the @c dduFactorChanged() signal to monitor changes and update the
         * required values.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(float dduFactor READ dduFactor NOTIFY dduFactorChanged REVISION 4 FINAL)

        /*!
         * @brief Converts a design unit value into a pixel value.
         *
         * @param duValue The value to convert in design units.
         * @return The converted pixel value.
         *
         * @since BlackBerry 10.3.0
         */
        Q_INVOKABLE float du(float duValue) const;

        /*!
         * @brief Converts a design unit value into a pixel value, while rounding to the nearest whole pixel.
         *
         * @param sduValue The value to convert in design units.
         * @return The converted pixel value, rounded to the nearest whole pixel.
         *
         * @since BlackBerry 10.3.0
         */
        Q_INVOKABLE float sdu(float sduValue) const;

        /*!
         * @brief Converts a design unit value into a pixel value while taking the @c #dduFactor into account.
         *
         * The dynamic design unit conversion can be used instead of the @c du() equivalent. 
         * The only difference is that this function also takes the current @c #dduFactor into account.
         *
         * @param dduValue The value to convert in design units.
         * @return The converted pixel value.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_INVOKABLE float ddu(float dduValue) const;

        /*!
         * @brief Converts a design unit value into a pixel value while taking the @c #dduFactor into account and
         * rounding the result to the nearest whole pixel.
         *
         * The dynamic design unit conversion can be used instead of the @c sdu() equivalent. 
         * The only difference is that this function also takes the current @c #dduFactor into account.
         *
         * @param sdduValue The value to convert in design units.
         * @return The converted pixel value, rounded to the nearest whole pixel.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_INVOKABLE float sddu(float sdduValue) const;

        /*!
         * @brief Converts a pixel value to a pixel value.
         *
         * This method doesn't change the value of the measurement. It's simply used
         * as a way to explicitly show that the value is a pixel value.
         *
         * @note In future versions of Cascades, API changes may require
         * that pixel values are specified explicitly by using this method. Using this API reduces the
         * effort to adapt to those changes, and your code may be source
         * compatible with future versions.
         *
         * @param pxValue The value to convert in pixels.
         * @return The pixel value.
         *
         * @since BlackBerry 10.3.0
         */
        Q_INVOKABLE float px(float pxValue) const;

        /*!
         * @brief Returns the @c isCompact property of the UI context.
         *
         * @return A bool indicating whether the UI should be shown in compact mode.
         *
         * @since BlackBerry 10.3.0
         */
        bool isCompact() const;

        /*!
         * @brief Returns the @c #dduFactor property of the UI context.
         *
         * @return A float stating the information density factor.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        float dduFactor() const;

        /*!
         * @brief Retrieves the ui palette.
         *
         * @return The @c UIPalette used by the @c UIObject.
         *
         * @since BlackBerry 10.3.0
         */
        bb::cascades::UIPalette* palette() const;

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c UIPalette for this @c %UIObject has changed.
         *
         * Here's how to connect a slot to a button and listen for changes to its ui palette:
         *
         * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button7
         *
         * @param palette The new ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        void paletteChanged(const bb::cascades::UIPalette* palette);
      
        /*!
         * @brief Emitted after the @c isCompact of the UI has changed.
         *
         * @param isCompact The new compact mode for the UI.
         *
         * @since BlackBerry 10.3.0
         */
        void compactChanged( bool isCompact );
   
        /*!
         * @brief Emitted after the @c dduFactor of the UI has changed.
         *
         * @param dduFactor The new information density factor for the UI.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        void dduFactorChanged( float dduFactor );


    private:

        /*! @cond PRIVATE */
        QScopedPointer<UIConfigPrivate> d_ptr;
        Q_DECLARE_PRIVATE(UIConfig)
        Q_DISABLE_COPY(UIConfig)

        UIConfig(QObject* parent = 0);
        virtual ~UIConfig();

        /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::UIConfig)

#endif  /* cascades_uiconfig_h */


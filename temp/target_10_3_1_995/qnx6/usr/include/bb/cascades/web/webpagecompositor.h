/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webpagecompositor_h
#define cascades_webpagecompositor_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtCore/QRectF>
#include <QtCore/QSize>

namespace bb {
  namespace cascades {

    class WebPageCompositorPrivate;
    class WebPageTexture;

    /*!
     * @brief A class that composites the internal scene graph of a @c WebPage.
     *
     * The scene graph must be composited to a render target. Currently, an OpenGL texture can be used as the target.
     * The texture can then be used in custom OpenGL rendering code to render the webpage as part of an OpenGL scene.
     * See WebPageTexture for more information.
     *
     * In addition to the web content, injected user input events may cause the webpage to have overlays. These
     * include selection handles, fine cursor control handles, and other overlays. These can optionally be included in
     * the output of the @c WebPageCompositor.
     *
     * All operations on a @c WebPageCompositor are asynchronous, including rendering.
     *
     * The @c WebPageCompositor API is very similar to that of @c ScrollView. Since it is a @c Control,
     * the @c ScrollView has a size that it can use as a basis for @c contentScale and @c viewableArea calculations. The
     * @c WebPageCompositor is not part of a layout system that adjusts its size like controls do, instead it has a
     * viewport size that is set directly using @c setViewportSize(). The viewport size is used as a basis for
     * @c contentScale and @c viewableArea calculations, and is typically set to the same size as the @c WebPageTexture used as
     * the render target.
     *
     * The viewable area of the page can be composited to a texture by calling @c renderToTexture(). If you want
     * to include overlays in the rendering output, call @c renderToTexture(). Use @c scrollToPoint(), @c zoomToPoint(), and
     * @c zoomToRect() to manage the viewable area.
     *
     * When the webpage appearance changes, @c repaintRequested() is emitted. In a connected slot, the app should
     * call @c renderToTexture(). When rendering is done, the texture emits the @c WebPageTexture::textureChanged()
     * signal, which indicates that the texture is ready to be rendered using custom OpenGL code.
     *
     * An instance of @c WebPageEventHandler can be used to inject input events to the webpage, and
     * thus allow interaction with the web content. As a result of interaction, the webpage may request scrolling or
     * zooming to take place by emitting @c scrollRequested() and @c zoomRequested(). The app can animate these
     * transitions, or simply call @c scrollToPoint() or @c zoomToPoint() directly.
     *
     * This object can be created on any thread. However, the object has an affinity for the thread it was created on,
     * and may not be used on any other thread.
     *
     * @see @c WebPage, which represents a webpage that can be composited by this class.
     * @see @c WebPageTexture, which represents a texture that can be used as a render target when
     *      compositing.
     * @see @c WebPageEventHandler, which can be used to inject user input events to the webpage.
     *
     * Example of multi-threaded use:
     *
     * @snippet tad/examples/controls/webpagecompositor/src/mythread.h webpagecompositor1
     *
     * @snippet tad/examples/controls/webpagecompositor/src/mythread.cpp webpagecompositor2
     *
     * @snippet tad/examples/controls/webpagecompositor/src/main.cpp webpagecompositor3
     *
     * @c WebPageCompositor is normally used from C++, but here is an example of using @c WebPageCompositor in QML:
     *
     * @snippet tad/examples/controls/webpagecompositorqml/assets/main.qml webpagecompositorqml_qml1
     *
     * Add the following lines to the C++ main program to register @c WebPageCompositor:
     *
     * @snippet tad/examples/controls/webpagecompositorqml/src/webpagecompositorqml.cpp webpagecompositorqml1
     *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT WebPageCompositor : public QObject {
        Q_OBJECT

        /*!
         * @brief The size of the entire webpage.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QSize contentSize READ contentSize NOTIFY contentSizeChanged FINAL)

        /*!
         * @brief The size of the viewport.
         *
         * The viewport size is typically set to the same size as the @c WebPageTexture used as the render target.
         *
         * However, the actual size of the render target is decoupled from the logical viewport size used by the
         * @c WebPageCompositor in its calculations.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QSize viewportSize READ viewportSize WRITE setViewportSize NOTIFY viewportSizeChanged FINAL)

        /*!
         * @brief The scale used when rasterizing the webpage, to increase the detail level of text and vector graphics.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(double contentScale READ contentScale NOTIFY contentScaleChanged FINAL)

        /*!
         * @brief The area which is currently being shown in the viewport.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QRectF viewableArea READ viewableArea RESET resetViewableArea NOTIFY viewableAreaChanged FINAL)

        /*!
         * @brief A part of the webpage that should be kept visible, for example, due to text input.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QRectF regionOfInterest READ regionOfInterest NOTIFY regionOfInterestChanged FINAL)

    public:

        /*!
         * @brief Constructs a @c WebPageCompositor.
         *
         * The @c WebPageCompositor must be connected to a @c WebPage before any methods can be
         * called on it.
         *
         * @see @c connectToWebPage(const QString&).
         *
         * @param parent Optional parent for this object.
         *
         * @since BlackBerry 10.0.0
         */
        WebPageCompositor(QObject *parent = 0);

        virtual ~WebPageCompositor();

        /*!
         * @brief Renders part of the webpage to the entire texture based on the current viewable area.
         *
         * The texture will be cleared to the color specified by @c WebSettings::background() before
         * rendering.
         *
         * In addition to the web content, injected user input events may cause the webpage to have overlays. These
         * include selection handles, fine cursor control handles, and other overlays.
         *
         * If you want to render a thumbnail of the webpage, you can leave out the overlays.
         *
         * @param texture An instance of @c WebPageTexture representing the texture to use as render target.
         * @param includeOverlays Whether to include overlays.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void renderToTexture(bb::cascades::WebPageTexture* texture, bool includeOverlays = false);

        /*!
         * @brief Gets the size of the webpage.
         *
         * @return The size of the entire webpage.
         *
         * @since BlackBerry 10.0.0
         */
        QSize contentSize() const;

        /*!
         * @brief Gets the size of the viewport.
         *
         * @return The viewport size.
         *
         * @since BlackBerry 10.0.0
         */
        QSize viewportSize() const;

        /*!
         * @brief Gets the scale used when rasterizing the webpage, to increase the detail level of text and vector graphics.
         *
         * @return The scale used when rasterizing the webpage.
         *
         * @since BlackBerry 10.0.0
         */
        double contentScale() const;

        /*!
         * @brief Gets the viewable area of the webpage.
         *
         * @return The viewable area.
         *
         * @since BlackBerry 10.0.0
         */
        QRectF viewableArea() const;

        /*!
         * @brief Gets the area of the webpage that should be kept visible.
         *
         * For example, the region of interest changes during text input to indicate where text is
         * being inserted on the webpage, so the application can scroll the webpage to make the text visible.
         *
         * If there currently is no region of interest, an empty rectangle is returned.
         *
         * @return A part of the webpage that should be kept visible.
         *
         * @since BlackBerry 10.0.0
         */
        QRectF regionOfInterest() const;

    public Q_SLOTS:
        /*!
         * @brief Connects to a @c WebPage created on the main thread.
         *
         * @since BlackBerry 10.0.0
         */
        void connectToWebPage(const QString& uniqueId);

        /*!
         * @brief Sets the size of the viewport.
         *
         * The viewport size is typically set to the same size as the @c WebPageTexture used as the render target.
         *
         * @param size The new viewport size.
         *
         * @since BlackBerry 10.0.0
         */
        void setViewportSize(const QSize& size);

        /*!
         * @brief Resets the content scale to 1.0 and resets the viewable area to a rectangle located at 0, 0 and with
         *        a size equal to the viewport size.
         *
         * @since BlackBerry 10.0.0
         */
        void resetViewableArea();

        /*!
         * @brief Moves the viewable area to the specified position.
         *
         * @param x The new x coordinate of the viewable area.
         * @param y The new y coordinate of the viewable area.
         *
         * @since BlackBerry 10.0.0
         */
        void scrollToPoint(float x, float y);

        /*!
         * @brief Moves the center of the viewable area to the specified position, and adjusts the scale.
         *
         * If the scale changed, the size of the viewable area is updated accordingly.
         *
         * @param x The new x coordinate of the viewable area.
         * @param y The new y coordinate of the viewable area.
         * @param contentScale The new scale.
         *
         * @since BlackBerry 10.0.0
         */
        void zoomToPoint(float x, float y, double contentScale);

        /*!
         * @brief Sets the viewable area to the specified rectangle.
         *
         * If the size of the viewable area changed, the scale is updated accordingly.
         *
         * @param rect The new viewable area.
         *
         * @since BlackBerry 10.0.0
         */
        void zoomToRect(const QRectF& rect);

    Q_SIGNALS:
        /*!
         * @brief Emitted when successfully connected to a webpage.
         *
         * @since BlackBerry 10.0.0
         */
        void connectionSucceeded();

        /*!
         * @brief Emitted when connection failed.
         *
         * @since BlackBerry 10.0.0
         */
        void connectionFailed();

        /*!
         * @brief Emitted when the content size changes.
         *
         * @since BlackBerry 10.0.0
         */
        void contentSizeChanged(const QSize& newContentSize);

        /*!
         * @brief Emitted when the viewport size changes.
         *
         * @since BlackBerry 10.0.0
         */
        void viewportSizeChanged(const QSize& newViewportSize);

        /*!
         * @brief Emitted when the content scale changes.
         *
         * @since BlackBerry 10.0.0
         */
        void contentScaleChanged(double newContentScale);

        /*!
         * @brief Emitted when the viewable area changes.
         *
         * @since BlackBerry 10.0.0
         */
        void viewableAreaChanged(const QRectF& newViewableArea, double newContentScale);

        /*!
         * @brief Emitted when the region of interest changes.
         *
         * @since BlackBerry 10.0.0
         */
        void regionOfInterestChanged(const QRectF& newRegionOfInterest) const;

        /*!
         * @brief Emitted when the appearance of the webpage changes.
         *
         * A slot connected to this signal will typically call @c renderToTexture().
         *
         * @since BlackBerry 10.0.0
         */
        void repaintRequested();

        /*!
         * @brief Emitted when the webpage wants to scroll to a new position.
         *
         * This signal can be emitted due to interaction with the webpage, or JavaScript code executing on the webpage.
         *
         * You can perform a smooth animation to the new scroll position, or simply jump to the new position.
         *
         * @param x The new top left corner of the viewable area.
         * @param y The new top left corner of the viewable area.
         *
         * @since BlackBerry 10.0.0
         */
        void scrollRequested(float x, float y);

        /*!
         * @brief Emitted when the webpage wants to scroll to a new position.
         *
         * This signal can be emitted due to interaction with the webpage.
         *
         * You can perform a smooth animation to the new scroll position and scale, or simply jump there.
         *
         * @param x The new center of the viewable area.
         * @param y The new center of the viewable area.
         * @param contentScale The new content scale.
         *
         * @since BlackBerry 10.0.0
         */
        void zoomRequested(float x, float y, double contentScale);

    private:
        Q_DECLARE_PRIVATE(WebPageCompositor)
        Q_DISABLE_COPY(WebPageCompositor)

        WebPageCompositorPrivate* const d_ptr;
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webpagecompositor_h


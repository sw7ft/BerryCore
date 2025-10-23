/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webpagetexture_h
#define cascades_webpagetexture_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtCore/QSize>

namespace bb {
  namespace cascades {

    class WebPageTexturePrivate;

    /*!
     * @brief The texture that can be used as a render target when compositing the internal scene graph of a webpage.
     *
     * A @c WebPageTexture can be used as a render target when compositing the internal scene graph of a @c WebPage using a
     * @c WebPageCompositor. The texture can then be used in custom OpenGL rendering code to render the webpage as part
     * of an OpenGL scene.
     *
     * This object can be created on any thread. However, the object has an affinity for the thread it was created on,
     * and may not be used on any other thread.
     *
     * When calling the @c textureId() method on a @c WebPageTexture object, an OpenGL ES 2.0 capable EGL context must be
     * current.
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
	 */
    class BBCASCADES_EXPORT WebPageTexture : public QObject {
        Q_OBJECT

        /*!
         * @brief The size of the texture.
         *
         * @see @c WebPageTexture::size().
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged FINAL)

        /*!
         * @brief The ID of an OpenGL texture.
         *
         * @see @c WebPageTexture::textureId().
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(quint32 textureId READ textureId NOTIFY textureChanged FINAL)

    public:
        /*!
         * @brief Constructs a @c WebPageTexture object with the requested size.
         *
         * @param size The requested size of the texture.
         * @param parent Optional parent for this object.
         *
         *
         * @since BlackBerry 10.0.0
         */
        explicit WebPageTexture(const QSize& size, QObject* parent = 0);
        WebPageTexture();
        virtual ~WebPageTexture();

        /**
         * @brief Retrieves the texture size requested.
         *
         * The actual size of the texture may not be equal to the requested size due to GPU limitations.
         *
         * @return The size requested when constructing this @c WebPageTexture object.
         *
         * @since BlackBerry 10.0.0
         */
        QSize size() const;

        /*!
         * @brief Retrieves the ID of an OpenGL texture in the EGL context that is current on the calling thread.
         *
         * @note When calling this method, an OpenGL ES 2.0 capable EGL context must be current.
         *
         * This method will return 0 if there is no texture yet, or if called from another thread
         * than the thread that called @c WebPageCompositor::renderToTexture().
         *
         * Initially, the texture will have the following properties:
         * - GL_TEXTURE_MIN_FILTER: GL_LINEAR
         * - GL_TEXTURE_MAG_FILTER: GL_LINEAR
         * - GL_TEXTURE_WRAP_S: GL_CLAMP_TO_EDGE
         * - GL_TEXTURE_WRAP_T: GL_CLAMP_TO_EDGE
         *
         * @snippet tad/examples/controls/webpagecompositor/src/mythread.cpp webpagecompositor4
         *
         * @return The ID of the texture.
         *
         * @since BlackBerry 10.0.0
         */
        quint32 textureId() const;

    public Q_SLOTS:
        /*!
         * @brief Sets the requested size of the texture.
         *
         * @note This operation can be expensive, because a new texture is allocated internally.
         *
         * @param size The new size.
         *
         * @since BlackBerry 10.0.0
         */
        void setSize(const QSize& size);

    Q_SIGNALS:
        /*!
         * @brief Emitted when the texture ID or appearance of the texture changes.
         *
         * This signal is typically emitted after a call to @c WebPageCompositor::renderToTexture(), when
         * the asynchronous rendering completes.
         *
         * @since BlackBerry 10.0.0
         */
        void textureChanged();

        /*!
         * @brief Emitted when the size changes.
         *
         * @since BlackBerry 10.0.0
         */
        void sizeChanged(const QSize& newSize);

    private:
        Q_DECLARE_PRIVATE(WebPageTexture)
        Q_DISABLE_COPY(WebPageTexture)

        WebPageTexturePrivate* const d_ptr;
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webpagetexture_h


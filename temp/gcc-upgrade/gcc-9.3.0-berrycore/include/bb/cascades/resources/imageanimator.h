/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_imageanimator_h
#define cascades_imageanimator_h

#include <bb/cascades/BaseObject>
#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/image.h>
#include <bb/cascades/resources/imageanimatoranchor.h>
#include <bb/cascades/resources/imageanimatorseekmode.h>

namespace bb {
    namespace cascades {

        class ImageAnimatorPrivate;

        /*!
         * @brief A class that can be used to control the animation of an
         * animated image (typically a .gif animation).
         *
         * Here's how to use the image animator in C++:
         *
         * @code
         * ImageView *iv = new ImageView();
         * iv->setImageSource(QUrl("foo.gif"));
         * ImageAnimator *ic = new ImageAnimator();
         * ic->setAnimatedImage(iv->image()); // attach image
         * ic->setStarted(true);
         * @endcode
         *
         * Here's how to use the image animator from QML:
         *
         * @code
         * Container {
         *     ImageView {
         *         id: imageView
         *         imageSource: "foo.gif"
         *         attachedObjects: [
         *             ImageAnimator {
         *                 id: imageAnimator
         *                 animatedImage: imageView.image
         *                 started: true
         *             }
         *         ]
         *     }
         * }
         * @endcode
         *
         * @xmlonly
         * <qml>
         * <class register="yes"/>
         * </qml>
         * <apigrouping group="User interface/Resources"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT ImageAnimator : public BaseObject {
            Q_OBJECT

            /*!
             * @brief The image that the animator is currently controlling.
             *
             * @xmlonly
             * <qml>
             * <variant type="bb::cascades::Image"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(QVariant animatedImage READ animatedImageQml WRITE setAnimatedImageQml
                       RESET resetAnimatedImage NOTIFY animatedImageChanged FINAL)

            /*!
             * @brief Specifies whether the attached image should animate or not.
             *
             * Changing this property informs the attached image to start or stop playing, and
             * emits the @c startedChanged() signal. 
             *
             * Setting this property to @c true has the same effect as invoking @c play().
             * Setting it to @c false has the same effect as invoking @c stop() or 
             * @c stopAt(ImageAnimatorAnchor::CurrentFrame, ImageAnimatorSeekMode::Immediate).
             * Invoking @c play(), @c stop() or @c stopAt() will change this property immediately.
             *
             * When an @c ImageAnimator is created, this property will have the value @c false, which means 
             * that any image attached to an unaltered animator will pause.
             *
             * Due to the asynchronous nature of Cascades this property does not indicate
             * whether the attached image is currently animating or not, but rather, if the image has 
             * been informed that it @b should animate or not.
             * The @c %running property can be used to find out if the currently attached image is actually 
             * animating.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bool started READ isStarted WRITE setStarted
                       RESET resetStarted NOTIFY startedChanged FINAL)
            
            /*!
             * @brief A read-only property that specifies whether the attached image is currently 
             * animating or not.
             *
             * When this property is changed the @c runningChanged() signal will be emitted.
             *
             * Due to the asynchronous nature of Cascades, changing the @c %started property or 
             * invoking @c play(), @c stop() or @c stopAt() will not change this property immediately. This property will
             * only be changed after the image has actually stopped animating.
             *
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged FINAL)

            /*!
             * @brief Specifies whether the attached image should animate or not.
             *
             * This property is deprecated in favor of the @c #started property
             *
             * @deprecated Use the @c %started property instead
             * 
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bool playing READ isPlaying WRITE setPlaying
                       RESET resetPlaying NOTIFY playingChanged FINAL)

        public:
            /*!
             * @brief Constructs an @c ImageAnimator
             *
             * @param parent The parent of this object.
             *
             * @since BlackBerry 10.0.0
             */
            explicit ImageAnimator(QObject *parent = 0);

            virtual ~ImageAnimator();

            /*!
             * @brief Returns the currently attached image.
             *
             * If no image is attached a null image will be returned.
             *
             * @return The currently attached image, or a null image if no image is being animated.
             *
             * @since BlackBerry 10.0.0
             */
            bb::cascades::Image animatedImage() const;

            /*!
             * @brief Sets an image on the animator.
             *
             * When this function is called, the started state of the animator will be pushed to the image.
             * The running state of the image will be pushed to the animator.
             *
             * An image can only be attached to one animator. If the image was already attached 
             * to an animator when this method is called, the image is detached from the old animator 
             * and attached to this one. A null image will be attached to the old animator.
             * 
             * When attaching a new image to an animator, the old image does not lose the started 
             * state that was pushed to it by the animator, but you cannot control it any longer
             * with the animator.
             *
             * @param image to attach to the animator
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setAnimatedImage(const bb::cascades::Image& image);

            /*!
             * @brief Resets the attached image to a null image.
             *
             * This will detach the currently attached image and attach a null image to the animator.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetAnimatedImage();

            /*!
             * @brief Returns the started state of the animator.
             *
             * @return The started state of the animator.
             *
             * @since BlackBerry 10.0.0
             */
            bool isStarted() const;

            /*!
             * @brief Sets the started state of the animator.
             *
             * @param started If @c true the animation is started and if @c false the animation is stopped.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setStarted(bool started);
            
            /*!
             * @brief Stops the animation by resetting the started state to @c false.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetStarted();
            
            /*!
             * @brief Returns the running state of the animator.
             *
             * @return The running state of the animator.
             *
             * @since BlackBerry 10.0.0
             */
            bool isRunning() const;

            /*!
             * @brief Starts the animation of the attached image
             *
             * Calling this function has the same effect as calling @c setStarted(true).
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void start();

            /*!
             * @brief Stops the animation of the attached image.
             *
             * Calling this function has the same effect as calling @c setStarted(false).
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void stop();


            /*!
             * @brief Stops the animation of the attached image in a specified way.
             *
             * This function can be used to stop the animation of the attached image at specific 
             * points in the animation.
             *
             * How to use this function and how it relates to the @c %started and @c %running properties is
             * illustrated in the following examples:
             *
             * Example 1:
             *   -# Invoke <code>stopAt(ImageAnimatorAnchor::CurrentFrame, ImageAnimatorSeekMode::Immediate)</code> or
             *      invoke <code>stopAt(ImageAnimatorAnchor::CurrentFrame, ImageAnimatorSeekMode::Animate)</code> while animation is running.
             *   -# @c startedChanged(false) will be emitted immediately.
             *   -# Cascades will stop the animation as soon as possible on the frame the animation is currently on and then
             *      @c runningChanged(false) will be emitted.
             *
             * Example 2:
             *   -# Invoke <code>stopAt(ImageAnimatorAnchor::FirstFrame, ImageAnimatorSeekMode::Immediate)</code> while animation is running.
             *   -# @c startedChanged(false) will be emitted immediately.
             *   -# Cascades will stop the animation as soon as possible, jumping to the first frame of the image animation and then
             *      @c runningChanged(false) will be emitted.
             *
             * Example 3:
             *   -# Invoke <code>stopAt(ImageAnimatorAnchor::LastFrame, ImageAnimatorSeekMode::Immediate)</code> while animation is running.
             *   -# @c startedChanged(false) will be emitted immediately.
             *   -# Cascades will stop the animation as soon as possible, jumping to the first frame of the image animation and then
             *      @c runningChanged(false) will be emitted.
             *
             * Example 4:
             *   -# Invoke <code>stopAt(ImageAnimatorAnchor::FirstFrame, ImageAnimatorSeekMode::Animate)</code> while animation is running.
             *   -# @c startedChanged(false) will be emitted immediately.
             *   -# Cascades will continue to run the animation until the first frame is shown, at which point             
             *      @c runningChanged(false) will be emitted.
             
             * Example 5:
             *   -# Invoke <code>stopAt(ImageAnimatorAnchor::LastFrame, ImageAnimatorSeekMode::Animate)</code> while animation is running.
             *   -# @c startedChanged(false) will be emitted immediately.
             *   -# Cascades will continue to run the animation until the last frame is shown, at which point             
             *      @c runningChanged(false) will be emitted.
             *
             * Example 6:
             *   -# Invoke <code>stopAt(ImageAnimatorAnchor::FirstFrame, ImageAnimatorSeekMode::Animate)</code> while animation is not running
             *       and the first frame is not currently showing.
             *   -# Cascades will emit @c runningChanged(true), run the animation until the first frame is shown, at which point
             *      @c runningChanged(false) will be emitted. 
             *
             * Example 7:
             *   -# Invoke <code>stopAt(ImageAnimatorAnchor::LastFrame, ImageAnimatorSeekMode::Animate)</code> while animation is not running
             *      and the last frame is not currently showing.
             *   -# Cascades will emit @c runningChanged(true), run the animation until the last frame is shown, at which point
             *      @c runningChanged(false) will be emitted. 
             *
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void stopAt(bb::cascades::ImageAnimatorAnchor::Type anchor, 
                               bb::cascades::ImageAnimatorSeekMode::Type seekMode = bb::cascades::ImageAnimatorSeekMode::Default);
            
            /*!
             * @brief Returns the started state of the animator
             *
             * @deprecated in favor of @c isStarted()
             *
             * @return The started state of the animator.
             *
             * @since BlackBerry 10.0.0
             */
            bool isPlaying() const;

            /*!
             * @brief Sets the started state of the animator
             *
             * @deprecated in favor of @c setStarted()
             *
             * @param playing @c true to start the animation, @c false to stop it.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setPlaying(bool playing);

            /*!
             * @brief Resets the started state of the animator
             *
             * @deprecated in favor of resetStarted().
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetPlaying();
            
        Q_SIGNALS:

            /*!
             * @brief Emitted when the attached image changes.
             *
             * @param animatedImage The new Image that was attached to the animator
             *
             * @xmlonly
             * <qml>
             * <param name="animatedImage" type="QVariant"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.0.0
             */
            void animatedImageChanged(const bb::cascades::Image& animatedImage);

            /*!
             * @brief Emitted when the started state of the animator changes.
             * 
             * @param started The new started state of the animator.
             *
             * @since BlackBerry 10.0.0
             */
            void startedChanged(bool started);
            
            /*!
             * @brief Emitted when the running state of the animator changes.
             * 
             * @param running The new running state of the animator.
             *
             * @since BlackBerry 10.0.0
             */
            void runningChanged(bool running);
            
            /*!
             * @brief Emitted when the started state of the animator changes.
             * 
             * @deprecated in favor or startedChanged()
             *
             * @param playing The new started state of the animator.
             *
             * @since BlackBerry 10.0.0
             */
            void playingChanged(bool playing);

            /*! @cond PRIVATE */
            void animatedImageChanged(QVariant animatedImage);
            /*! @endcond */

        private:
            
            /*! \cond PRIVATE */

            /*!
             * @brief Returns the currently attached image.
             *
             * This is a private function needed by the QML. The returned QVariant is always an Image.
             *
             * @warning The app must not call this function, instead animatedImage() should be called.
             *
             * @return A QVariant containing the Image for the ImageAnimator or 0 if no image was set.
             */
            QVariant animatedImageQml() const;

            /*!
             * @brief Attach an image to the animator
             *
             * The QVariant image must be of Image. This is a private function
             * encapsulating setAnimatedImage() needed by the QML.
             *
             * @warning The app must not call this function, instead setAnimatedImage() should be called.
             *
             * @param image A QVariant container either the Image or QString name of the image to set for
             * the ImageAnimator
             */
            Q_SLOT void setAnimatedImageQml(const QVariant & image);

            Q_DECLARE_PRIVATE(ImageAnimator);
            Q_DISABLE_COPY(ImageAnimator);
            /*! \endcond */
        };

    }
}

QML_DECLARE_TYPE(bb::cascades::ImageAnimator)

#endif // cascades_imageanimator_h


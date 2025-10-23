/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_scenecover_h
#define cascades_scenecover_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/core/abstractcover.h>

namespace bb {
    namespace cascades {

    class Control;
    class SceneCoverPrivate;

    /*!
     * @brief Renders a non-interactive scene graph that is displayed when the application is in cover mode.
     *
     * @details The cover of the app is displayed on the Home screen when a user
     * minimizes the app by swiping up from the bottom of the screen. These minimized covers
     * are also referred to as Active frames.
     *
     * @image html active_frames.png
     *
     * One way to create a custom cover for an app is to inherit from @c %SceneCover. The content for a
     * a scene cover is provided through the @c content property which defines a root @c Control for the cover.
     * The content within the scene is non-interactive. Animations are also disabled within covers.
     *
     * Here's an example of how to inherit from @c SceneCover to create a custom cover called @c ActiveFrame.
     *
     * @code
     * #include "ActiveFrame.h"
     *
     * ActiveFrame::ActiveFrame() :
     *        SceneCover(this) {
     *
     *     qml = QmlDocument::create("asset:///active_frame_cover.qml").parent(this);
     *     mMainContainer = qml->createRootObject<Container>();
     *
     *     // Set the content of ActiveFrame
     *     setContent(mMainContainer);
     *   
     *     // Trigger the update slot
     *     update();
     *   
     *     // Another option is to initiate the update when the app moves
     *     // To the background. For example:
     *     // QObject::connect(Application::instance(),
     *     //         SIGNAL(thumbnail()), this, SLOT(update()));
     * }
     *
     * ActiveFrame::~ActiveFrame() {
     *
     * }
     *
     * void ActiveFrame::update() {
     *
     *     // ...Here's where you can update the cover...
     * }
     * @endcode
     *
     * To set the cover on that application, you retrieve an instance of the @c Application
     * and call @c setCover().
     *
     * @code
     * Application::instance()->setCover(new ActiveFrame());
     * @endcode
     *
     * @xmlonly
     * <qml>
     *     <apigrouping group="User interface/Core"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT SceneCover : public AbstractCover {
    private:
        Q_OBJECT

        /*!
         * @brief The root control for the scene cover.
         *
         * This is the root of the UI tree that will be rendered when the application is in
         * cover mode.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent NOTIFY contentChanged FINAL)

    public:
        /*!
         * @brief Creates the @c SceneCover.
         *
         * The ownership of the cover is transferred to the parent if one is specified.
         *
         * @param parent The parent object or @c 0. This parameter is optional and defaults
         * to @c 0 if not specified.
         *
         * @since BlackBerry 10.0.0
         */
        explicit SceneCover(QObject* parent = 0);

        /*!
         * @brief Destroys this @c SceneCover.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~SceneCover();

        /*!
         * @brief Returns the root control for the scene cover.
         *
         * Ownership of the @c Control object remains unchanged.
         *
         * @return The root control for the cover.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::Control* content() const;

        /*!
         * @brief Sets the root control for the scene cover.
         *
         * The @c SceneCover takes ownership of the root control object.
         *
         * @param content The new root control for the cover.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setContent(bb::cascades::Control* content);

        Q_SIGNALS:

        /*!
         * @brief Emitted when the root control of the scene cover changes.
         *
         * @param content The new root control for the cover.
         *
         * @since BlackBerry 10.0.0
         */
        void contentChanged(bb::cascades::Control* content);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(SceneCover)
        Q_DISABLE_COPY(SceneCover)
        /*! @endcond */

      // BUILDER ---------------------------------
    public:
        /*! @cond PRIVATE */
        typedef SceneCover ThisClass;  // The class in which scope we're currently inside
        typedef AbstractCover BaseClass; // References the class which ThisClass derives from
        /*! @endcond */

        /*!
         * \brief A builder template for constructing a SceneCover.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
            protected:
              TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
              }
            public:

              /*!
               * @brief Sets the root control for the scene cover.
               *
               * The SceneCover takes ownership of the root control object.
               *
               * @param content The new root control for the cover.
               *
               * @since BlackBerry 10.0.0
               */
              BuilderType& content(bb::cascades::Control* content) {
                this->instance().setContent(content);
                return this->builder();
              }
            };

            /*!
             * A builder template for constructing a SceneCover. To retrieve the builder, call
             * SceneCover::create().
             *
             * @since BlackBerry 10.0.0
             */
            class Builder : public TBuilder<Builder, SceneCover>
            {
            public:
              explicit Builder() : TBuilder<Builder, SceneCover>(new SceneCover()) {
              }
            };

            /*! Creates and returns a builder for constructing a SceneCover.
             *
             * Using the builder to create a SceneCover:
             * @code
             * SceneCover* pCover = SceneCover::create();
             * @endcode
             *
             * @return A builder used for constructing a SceneCover.
             *
             * @since BlackBerry 10.0.0
             */
            static Builder create() {
              return Builder();
            }
        };
    }
}

QML_DECLARE_TYPE(bb::cascades::SceneCover)

#endif //cascades_scenecover_h

/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
 */

#ifndef cascades_applicationviewcover_h
#define cascades_applicationviewcover_h

#include <bb/cascades/bbcascades_global.h>

#include <QRectF>

#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/core/abstractcover.h>

namespace bb {
    namespace cascades {
        
        class ApplicationViewCoverPrivate;

       /*! 
        * @brief Cover which displays a scaled down or cropped version of the app as cover.
        *
        * @see bb::cascades::Application::setCover(AbstractCover *)
        *
        * @xmlonly
        * <qml>
        *     <apigrouping group="User interface/Core"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT ApplicationViewCover : public AbstractCover {
        private:
            Q_OBJECT

            /*!
             * @brief The cover area rectangle in window coordinates that will be used as cover
             * for the application.
             *
             * A @c null rectangle is interpreted as "cover area should be selected by the framework" and
             * will use the same size as the cover image when displayed in navigator.
             *
             * Default is a @c null rectangle meaning the area is selected by the framework.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(QRectF coverArea READ coverArea WRITE setCoverArea RESET resetCoverArea NOTIFY coverAreaChanged FINAL)

        public:
            /*!
             * @brief Creates the @c ApplicationViewCover.
             *
             * The ownership of the cover is transferred to the parent if one is specified.
             *
             * @param parent The parent object, or @c 0. This parameter is optional and defaults
             * to @c 0 if not specified.
             *
             * @since BlackBerry 10.0.0
             */
            explicit ApplicationViewCover(QObject* parent = 0);
            
            /*!
             * @brief Destroys this @c ApplicationViewCover.
             *
             * @since BlackBerry 10.0.0
             */
            virtual ~ApplicationViewCover();

            /*!
             * @brief Returns the cover area rectangle in window coordinates that will be used as cover
             * for the application.
             *
             * @return The coverArea rectangle or a @c null rectangle if the area hasn't been set
             *
             * @since BlackBerry 10.0.0
             */
            QRectF coverArea() const;

            /*!
             * @brief Sets the cover area rectangle in window coordinates that will be used as cover for
             * the application.
             *
             * Passing @c null rectangle is equivalent to calling resetCover();
             *
             * @param coverArea The coverArea rectangle.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setCoverArea(const QRectF &coverArea);

            /*!
             * @brief Sets the cover area rectangle to the default value which is @c null
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetCoverArea();

        Q_SIGNALS:

            /*!
             * @brief Emitted when the cover area rectangle changes.
             *
             * @param coverArea The new cover area rectangle in window coordinates that will be used as 
             * cover for the application.
             *
             * @since BlackBerry 10.0.0
             */
            void coverAreaChanged(const QRectF &coverArea);

        private:
           /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(ApplicationViewCover)
            Q_DISABLE_COPY(ApplicationViewCover)
           /*! @endcond */

            // BUILDER ---------------------------------
          public:
            /*! @cond PRIVATE */
            typedef ApplicationViewCover ThisClass;  // The class in which scope we're currently inside
            typedef AbstractCover BaseClass; // References the class which ThisClass derives from
            /*! @endcond */

            /*!
             * \brief A builder template for constructing an ApplicationViewCover.
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
                 * @brief Sets the cover area rectangle in window coordinates that will be used as cover for
                 * the application.
                 *
                 * Passing @c null rectangle is equivalent to calling resetCover();
                 *
                 * @param coverArea The coverArea rectangle.
                 *
                 * @since BlackBerry 10.0.0
                 */
                BuilderType& coverArea(const QRectF &coverArea) {
                    this->instance().setCoverArea(coverArea);
                    return this->builder();
                }
           };

          /*!
           * A builder template for constructing a ApplicationViewCover. To retrieve the builder, call
           * ApplicationViewCover::create().
           *
           * @since BlackBerry 10.0.0
           */
           class Builder : public TBuilder<Builder, ApplicationViewCover>
           {
           public:
               explicit Builder() : TBuilder<Builder, ApplicationViewCover>(new ApplicationViewCover()) {
               }
           };

          /*! Creates and returns a builder for constructing an ApplicationViewCover.
           *
           * Using the builder to create an ApplicationViewCover:
           * @code
           * ApplicationViewCover* pCover = ApplicationViewCover::create();
           * @endcode
           *
           * @return A builder used for constructing an ApplicationViewCover.
           *
           * @since BlackBerry 10.0.0
           */
           static Builder create() {
               return Builder();
           }
        };
    }
}

QML_DECLARE_TYPE(bb::cascades::ApplicationViewCover)

#endif //cascades_applicationviewcover_h

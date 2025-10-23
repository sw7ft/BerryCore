/*!
 * Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_abstractcover_h
#define cascades_abstractcover_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

    class AbstractCoverPrivate;

    /*!
     * @brief Abstract base class for cover implementations.
     *
     * @details The cover of the app is displayed on the Home screen when a user
     * minimizes the app by swiping up from the bottom of the screen. These minimized covers
     * are also referred to as Active frames.
     *
     * See @c SceneCover for a concrete implementation that you can use to create your 
     * own cover.   
     *
     * @xmlonly
     * <qml>
     *     <apigrouping group="User interface/Core"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT AbstractCover : public UIObject {
    private:
        Q_OBJECT

        /*!
         * @brief Descriptive text that is shown under the cover in navigator.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL);

        /*!
         * @brief Size in pixels (if applicable) that this cover will use
         * when drawn to the screen.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QSize size READ size NOTIFY sizeChanged REVISION 3 FINAL);

    public:
        /*!
         * @brief Destroys this @c AbstractCover.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~AbstractCover();

        /*!
         * @brief Returns the description for the cover.
         *
         * @return The description for the cover.
         *
         * @since BlackBerry 10.0.0
         */
        QString description() const;

        /*!
         * @brief Returns the size of the cover.
         *
         * @return The size of the cover.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        QSize size() const;

        /*!
         * @brief Sets the description for the cover.
         *
         * @param description The new description for the cover.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDescription(const QString &description);

        Q_SIGNALS:

        /*!
         * @brief Emitted when the #description of the cover changes.
         *
         * @param description The new description for the cover.
         *
         * @since BlackBerry 10.0.0
         */
        void descriptionChanged(const QString &description);

        /*!
         * @brief Emitted when the #size of the cover changes.
         * This signal will typically be emitted once the cover
         * is added or removed from a @c MultiCover.
         *
         * @param size The new size of the cover.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        void sizeChanged(const QSize &size);

    protected:
        /*! @cond PRIVATE */
        explicit AbstractCover(AbstractCoverPrivate &_d_ptr, QObject* parent = 0);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(AbstractCover)
        Q_DISABLE_COPY(AbstractCover)
        /*! @endcond */

        // BUILDER ---------------------------------
    public:
        /*! @cond PRIVATE */
        typedef AbstractCover ThisClass;  // The class whose scope is currently in context.
        typedef UIObject BaseClass; // References the class from which ThisClass is derived.
        /*! @endcond */

        /*!
         * @brief A builder template for constructing an AbstractCover.
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
             * @brief Sets the description for the cover.
             *
             * @param description The new description for the cover.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& description(const QString &description) {
              this->instance().setDescription(description);
              return this->builder();
            }
        };

    };
    }
}

QML_DECLARE_TYPE(bb::cascades::AbstractCover)

#endif //cascades_abstractcover_h

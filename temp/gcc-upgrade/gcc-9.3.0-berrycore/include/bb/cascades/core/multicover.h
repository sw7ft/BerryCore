/*!
 * Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_multicover_h
#define cascades_multicover_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>
#include <bb/cascades/core/abstractcover.h>
#include <bb/cascades/core/coverdetaillevel.h>

namespace bb {
    namespace cascades {

    class MultiCoverPrivate;

    /*!
     * @brief A class that allows you to specify multiple sizes of covers.
     *
     * Here's an example of how to define multiple covers in C++.
     *
     * @snippet tad/examples/core/multicover/src/multicover.cpp multicover_cpp2
     *
     * And, here's how to define multiple covers in QML.
     *
     * @snippet tad/examples/core/multicover/assets/main.qml multicover_qml1
     *
     * See @c AbstractCover for more information about covers.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT MultiCover : public AbstractCover {
    private:
        Q_OBJECT

        /*!
         * @brief Covers set for this application.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractCover> covers READ covers FINAL)
        Q_CLASSINFO("DefaultProperty", "covers")

    public:
        /*!
         * @brief Creates the @c MultiCover.
         *
         * The ownership of the cover is transferred to the parent if one is specified.
         *
         * @param parent The parent object or @c 0. This parameter is optional and defaults
         * to @c 0 if not specified.
         *
         * @since BlackBerry 10.3.0
         */
        explicit MultiCover(QObject* parent = 0);

        /*!
         * @brief Destroys this @c MultiCover.
         *
         * @since BlackBerry 10.3.0
         */
        virtual ~MultiCover();

        /*!
         * @brief Returns a list of covers set on this @c MultiCover.
         *
         * @return a list of covers set.
         *
         * @since BlackBerry 10.3.0
         */
        QDeclarativeListProperty<bb::cascades::AbstractCover> covers();

        /*!
         * @brief Adds a cover to this @c MultiCover.
         * @note Adding multiple covers with the same level of detail is not
         * supported, and if it's done anyway cascades will use the first one
         * added to that level.
         *
         * @param cover The cover to be added.
         * @param level The detail level to be used for said cover.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void add(bb::cascades::AbstractCover* cover, bb::cascades::CoverDetailLevel::Type level);

        /*!
         * @brief Removes all covers from this @c MultiCover.
         * Removing all covers is currently only supported for instances of @c MultiCover
         * that is not set as the cover for the @c Application.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void removeAll();

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(MultiCover)
        Q_DISABLE_COPY(MultiCover)
        /*! @endcond */

        // BUILDER ---------------------------------
    public:
        /*! @cond PRIVATE */
        typedef MultiCover ThisClass;  // The class whose scope is currently in context.
        typedef AbstractCover BaseClass; // References the class from which ThisClass is derived.
        /*!
         * Workaround for the Qt bug that prevents our enums from being
         * function arguments in QML.
         */
        Q_INVOKABLE void add(bb::cascades::AbstractCover *cover, int level);
        /*! @endcond */

        /*!
         * @brief A builder template for constructing a MultiCover.
         *
         * @since BlackBerry 10.3.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }
        public:

            /*!
             * @brief Adds a cover to this @c MultiCover.
             *
             * @param cover The cover to be added.
             * @param level The detail level to be used for said cover.
             *
             * @since BlackBerry 10.3.0
             */
            BuilderType& add(bb::cascades::AbstractCover* cover, bb::cascades::CoverDetailLevel::Type level) {
                this->instance().add(cover, level);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a @c %MultiCover.
         *
         * See @c MultiCover::create() for getting a concrete builder for constructing a @c %MultiCover.
         *
         * @since BlackBerry 10.3.0
         */
        class Builder : public TBuilder<Builder, MultiCover>
        {
        public:
            explicit Builder() : TBuilder<Builder, MultiCover>(new MultiCover()) {
            }
        };

        /*! Creates and returns a builder for constructing a MultiCover.
         *
         * Using the builder to create a MultiCover:
         * @code
         * MultiCover* pCover = MultiCover::create();
         * @endcode
         *
         * @return A builder used for constructing a MultiCover.
         *
         * @since BlackBerry 10.3.0
         */
        static Builder create() {
            return Builder();
        }
    };
    }
}

QML_DECLARE_TYPE(bb::cascades::MultiCover)
#endif //cascades_multicover_h

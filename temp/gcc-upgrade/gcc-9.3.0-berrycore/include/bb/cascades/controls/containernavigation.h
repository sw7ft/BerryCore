/* Copyright (C) 2014 Research In Motion Limited.  */

#ifndef cascades_containernavigation_h
#define cascades_containernavigation_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/Navigation>
#include <bb/cascades/ChildrenNavigationBehavior>

namespace bb {
    namespace cascades {

        class ContainerNavigationPrivate;

   /*!    
    *
    * @brief Specifies how navigation behaves for the children of a container.
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.1
    */
        class BBCASCADES_EXPORT ContainerNavigation : public Navigation {
            Q_OBJECT

           /*!
            * @brief Describes the behavior when navigating the children of this control using the trackpad or similar input.
            *
            * The default @c childrenBehavior value is @c Default.
            *
            * @since BlackBerry 10.3.1
            */
            Q_PROPERTY(bb::cascades::ChildrenNavigationBehavior::Type childrenBehavior READ childrenBehavior WRITE setChildrenBehavior RESET resetChildrenBehavior NOTIFY childrenBehaviorChanged FINAL)

        public:
            virtual ~ContainerNavigation();

           /*!
            * @brief Gets the child navigation behavior for this control.
            *
            * @return The child navigation behavior when navigating with the trackpad or similar input.
            *
            * @since BlackBerry 10.3.1
            */
            bb::cascades::ChildrenNavigationBehavior::Type childrenBehavior() const;

           /*!
            * @brief Set the child navigation behavior when navigating the children of the control
            *        with trackpad or similar input.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void setChildrenBehavior(bb::cascades::ChildrenNavigationBehavior::Type childrenBehavior);

           /*!
            * @brief Resets the childrenBehavior property to its default value.
            *
            * @since BlackBerry 10.3.1
            */
            Q_SLOT void resetChildrenBehavior();

Q_SIGNALS:
           /*!
            * @brief Emitted when the childrenBehavior property has changed.
            *
            * @param newChildrenBehavior The child navigation behavior when navigating the children of the control.
            *
            * @since BlackBerry 10.3.1
            */
            void childrenBehaviorChanged(bb::cascades::ChildrenNavigationBehavior::Type newChildrenBehavior);

        protected:
            /*! @cond PRIVATE */
            ContainerNavigation(Control* parent = 0);
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(ContainerNavigation)
            Q_DISABLE_COPY(ContainerNavigation)
            /*! @endcond */
        };
    }
}

QML_DECLARE_TYPE(bb::cascades::ContainerNavigation)

#endif // cascades_containernavigation_h

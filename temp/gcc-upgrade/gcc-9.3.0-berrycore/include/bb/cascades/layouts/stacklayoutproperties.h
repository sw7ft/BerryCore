/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_stacklayoutproperties_h
#define cascades_stacklayoutproperties_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layoutproperties.h>


namespace bb {
    namespace cascades {

    class StackLayoutPropertiesPrivate;
    class Control;

    /*!
     * 
     * @brief @c LayoutProperties that are assigned to controls within a @c StackLayout.
     *
     * By using @c %StackLayoutProperties, you can specify a control's space quota. The space
     * quota determines what percentage of space the control should assume in relation to
     * its siblings.
     *
     * This class can only be used with children of a container that uses a @c %StackLayout. 
     * If you attempt to use this class with another type of @c Layout, it's ignored. 
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT StackLayoutProperties : public LayoutProperties {
    private:
        Q_OBJECT
        /*!
         * @brief Specifies how size in the orientation is divided between child controls.
         *
         * Controls with a negative @c spaceQuota are treated as preferred sized controls and are given the 
         * size requested by the controls itself. 
         * These controls are given priority over dynamic controls, i.e. controls with a @c spaceQuota larger than 0.
         * The space remaining in the orientation after the preferred sized controls have been given
         * space is divided amongst the dynamic controls using spaceQuota. The remaining space is
         * divided in accordance with each dynamic contol's spaceQuota divided by the sum of all the 
         * spaceQuotas.
         * Two controls with a @c spaceQuota of 1.0 will divide the remaining space equally amongst them,
         * whereas two controls with spaceQuotas of 1.0 and 3.0 will give the first control one quarter of the
         * remaining space and give the second control three quarters of the remaining space.
         *
         * The default value of this property is negative. A value of 0 is not allowed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float spaceQuota
                   READ spaceQuota
                   WRITE setSpaceQuota
                   RESET resetSpaceQuota
                   NOTIFY spaceQuotaChanged
                   FINAL)

    public:
        /*!
         * @brief Constructs a @c %StackLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
         */
        StackLayoutProperties();
        virtual ~StackLayoutProperties();

       /*!
        * @brief Returns the space quota for the control.
        *
        * @return The spaceQuota for the control.
        *
        * @since BlackBerry 10.0.0
        */                                    
        float spaceQuota() const;
       /*!
        * @brief Sets the space quota for the control.
        *
        * After the @c spaceQuota is set, the @c spaceQuotaChanged() signal is emitted.
        *
        * @param _spaceQuota The spaceQuota of the control.
        *
        * @since BlackBerry 10.0.0
        */                                    
        Q_SLOT void setSpaceQuota(float _spaceQuota);
       /*!
        * @brief Resets the space quota to its default.
        *
        * The default @c spaceQuota is a negative value.
        *
        * After the @c space quota is reset, the @c spaceQuotaChanged() signal is emitted.
        *
        * @since BlackBerry 10.0.0
        */                                           
        Q_SLOT void resetSpaceQuota();

Q_SIGNALS:
       /*!
        * @brief Emitted when the @c #spaceQuota property changes.
        * 
        * @param spaceQuota The new spaceQuota for the control.
        *
        * @since BlackBerry 10.0.0
        */                              
        void spaceQuotaChanged(float spaceQuota);

        /*! \cond PRIVATE */
    private:
        Q_DECLARE_PRIVATE(StackLayoutProperties)
        Q_DISABLE_COPY(StackLayoutProperties)
        /*! \endcond */

    public:
        /*! \cond PRIVATE */
        typedef StackLayoutProperties ThisClass;
        typedef LayoutProperties BaseClass;
        /*! \endcond */
        
        /*!         
         * @brief A template builder class for constructing a @c %StackLayoutProperties object.
         *
         * To retrieve the builder, call @c StackLayoutProperties::create().
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
             * @copydoc bb::cascades::StackLayoutProperties::setSpaceQuota(float)
             */
            BuilderType& spaceQuota(float _spaceQuota) {
                this->instance().setSpaceQuota(_spaceQuota);
                return this->builder();
            }
        };

       /*!        
        * @brief A concrete builder class for constructing a @c %StackLayoutProperties object.
        *
        * To retrieve the builder, call @c StackLayoutProperties::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, StackLayoutProperties> {
        public:
            Builder(QObject *parent, StackLayoutProperties *pInstance = new StackLayoutProperties()) : TBuilder<Builder, StackLayoutProperties>(pInstance) {
                if (!pInstance->parent())
                {
                    pInstance->setParent(parent);
                }
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing stack layout properties.
        *
        * Using the builder to create a @c %StackLayoutProperties object:
        * @code
        * StackLayoutProperties* layoutProperties = StackLayoutProperties::create()
        *         .spaceQuota(0.5);
        * @endcode
        *
        * @return A builder used for constructing a @c %StackLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
        */
        static Builder create(QObject *parent = 0) {
            return Builder(parent);
        }

        /*!
         * @brief Builds and sets the stack layout properties for a control.
         *
         * If the control already 
         * has @c %StackLayoutProperties set on it, the original layout properties remain as is. Otherwise, a new 
         * %StackLayoutProperties object is created and set as the layout properties for the control.
         *
         * Using the builder to set a control's @c %StackLayoutProperties:
         * @code
         * Label *pLabel = Label::create().text("Hello World!");
         * StackLayoutProperties::updateFor(pLabel).spaceQuota(2.0f);
         * @endcode
         *
         * @param targetControl The control to set the layout properties on.
         * @return A builder used for constructing a @c %StackLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder updateFor(Control *targetControl);

    }; // StackLayoutProperties
} // namespace cascades
} // namespace bb


QML_DECLARE_TYPE(bb::cascades::StackLayoutProperties)


#endif	// cascades_stacklayoutproperties_h


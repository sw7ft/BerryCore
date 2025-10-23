/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_absolutelayoutproperties_h
#define cascades_absolutelayoutproperties_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layoutproperties.h>


namespace bb {
    namespace cascades {

    class AbsoluteLayoutPropertiesPrivate;
    class Control;

    /*!
     * 
     * @brief @c LayoutProperties that can be assigned to controls in an @c AbsoluteLayout.
     *     
     * By using @c %AbsoluteLayoutProperties, you can provide specific X and Y coordinates
     * that are used to position a control within its parent container.
     *
     * This class can only be used for children of a container that uses an @c AbsoluteLayout.
     * If you attempt to use this class with another type of @c Layout, it's ignored.
     *
     * @xmlonly
     * <qml>
     * <class register="yes"/>
     * </qml>
     * @endxmlonly
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT AbsoluteLayoutProperties : public LayoutProperties {
    private:
        Q_OBJECT
        /*!
         * @brief The X coordinate for the control.
         *
         * The origin of the coordinate system in an absolute layout is
         * the top-left corner of the container. The default value is 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float positionX
                   READ positionX
                   WRITE setPositionX
                   RESET resetPositionX
                   NOTIFY positionXChanged FINAL)
        /*!
         * @brief The Y coordinate for the control.
         *
         * The origin of the coordinate system in an absolute layout is
         * the top-left corner of the container. The default value is 0.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float positionY
                   READ positionY
                   WRITE setPositionY
                   RESET resetPositionY
                   NOTIFY positionYChanged FINAL)

    public:
        /*!
         * @brief Constructs an @c %AbsoluteLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
         */
        AbsoluteLayoutProperties();
        virtual ~AbsoluteLayoutProperties();

        /*!
        * @brief Returns the X coordinate for the control.
        * 
        * @return The X coordinate for the control.
         *
         * @since BlackBerry 10.0.0
         */      
        float positionX() const;
        /*!
         * @brief Sets the X coordinate for the control.
         * 
         * After the X coordinate is set, the @c positionYChanged() signal is emitted.
         *
         * @param posX The X coordinate for the control.
         *
         * @since BlackBerry 10.0.0
         */      
        Q_SLOT void setPositionX(float posX);
        /*!
         * @brief Resets the X coordinate to its default.
         *
         * The default value is 0.0.
         *
         * After the X coordinate is reset, the @c positionYChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetPositionX();

        /*!
         * @brief Returns the Y coordinate for the control.
         * 
         * @return The Y coordinate for the control.
         *
         * @since BlackBerry 10.0.0
         */            
        float positionY() const;
        /*!
         * @brief Sets the Y coordinate for the control.
         *
         * After the Y coordinate is reset, the @c positionYChanged() signal is emitted.
         *
         * @param posY The Y coordinate for the control.
         *
         * @since BlackBerry 10.0.0
         */     
        Q_SLOT void setPositionY(float posY);
        /*!
         * @brief Resets the Y coordinate to its default.
         *
         * The default value is 0.0.
         *
         * After the Y coordinate is reset, the @c positionYChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */           
        Q_SLOT void resetPositionY();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c #positionX property changes.
         * 
         * @param positionX The new X coordinate.
         *
         * @since BlackBerry 10.0.0
         */      
        void positionXChanged(float positionX);
        /*!
         * @brief Emitted when the @c #positionY property changes.
         * 
         * @param positionY The new Y coordinate.       
         *
         * @since BlackBerry 10.0.0
         */            
        void positionYChanged(float positionY);

        /*! @cond PRIVATE */        
    private:
        Q_DECLARE_PRIVATE(AbsoluteLayoutProperties)
        Q_DISABLE_COPY(AbsoluteLayoutProperties)
        /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef AbsoluteLayoutProperties ThisClass;
        typedef LayoutProperties BaseClass;
        /*! @endcond */
        
        /*!         
         * @brief A template builder for constructing an @c %AbsoluteLayoutProperties object.
         *
         * To retrieve the builder, call @c AbsoluteLayoutProperties::create().
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
             * @copydoc bb::cascades::AbsoluteLayoutProperties::setPositionX(float)
             */
            BuilderType& x(float posX) {
                this->instance().setPositionX(posX);
                return this->builder();
            }
            /*!
             * @copydoc bb::cascades::AbsoluteLayoutProperties::setPositionY(float)
             */
            BuilderType& y(float posY) {
                this->instance().setPositionY(posY);
                return this->builder();
            }
          
            /*!
            * @brief Sets the X coordinate and Y coordinate for the control.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& position(float posX, float posY) {
              this->instance().setPositionX(posX);
              this->instance().setPositionY(posY);
              return this->builder();
            }
          
        };

       /*!        
        * @brief A builder for constructing an @c %AbsoluteLayoutProperties object.
        *
        * To retrieve the builder, call @c AbsoluteLayoutProperties::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, AbsoluteLayoutProperties> {
        public:
            Builder(QObject *parent, AbsoluteLayoutProperties *pInstance = new AbsoluteLayoutProperties()) : TBuilder<Builder, AbsoluteLayoutProperties>(pInstance) {
                if (!pInstance->parent())
                {
                    pInstance->setParent(parent);
                }
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing absolute layout properties.
        *
        * Using the builder to create an @c %AbsoluteLayoutProperties object:
        * @code
        * AbsoluteLayoutProperties* layoutProperties = AbsoluteLayoutProperties::create()
        *         .posX(100.0)
        *         .posY(150.0);
        * @endcode
        *
        * @return A builder used for constructing an @c %AbsoluteLayoutProperties object.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create(QObject *parent = 0) {
            return Builder(parent);
        }

        /*!
         * @brief Builds and sets the absolute layout properties for a control.
         *
         * If the control already has @c %AbsoluteLayoutProperties set on it, the
         * original layout properties remain as is. Otherwise, a new 
         * @c %AbsoluteLayoutProperties object is created and set as the layout properties for the control.
         *
         * Using the builder to set a control's @c %AbsoluteLayoutProperties:
         * @code
         * Label *pLabel = Label::create().text("Hello World!");
         * AbsoluteLayoutProperties::updateFor(pLabel).x(50.0f).y(25.0f);
         * @endcode
         *
         * @param targetControl The control to set the layout properties on.
         * @return A builder used for constructing an @c %AbsoluteLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder updateFor(Control *targetControl);

    }; // class AbsoluteLayoutProperties

} // namespace cascades
} // namespace bb


QML_DECLARE_TYPE(bb::cascades::AbsoluteLayoutProperties)


#endif	// cascades_absolutelayoutproperties_h


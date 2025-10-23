/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_container_h
#define cascades_container_h

#include <QVariant>
#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeListProperty>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/Control>
#include <bb/cascades/ContainerNavigation>

namespace bb {
    namespace cascades {

    class ContainerPrivate;
    class Layout;
    class Paint;
    class AbstractA11yObject;

   /*!
    *
    * @brief A container that can be used for grouping controls and other containers.
    *
    * Children within a container are arranged according to the type of @c Layout assigned
    * to its @c #layout property. The default @c layout is @c StackLayout, which dictates that
    * children are stacked in a column, from top to bottom. Other types of
    * layouts include @c DockLayout, @c AbsoluteLayout, and @c GridLayout.
    *
    * When you add a control to a container, it is added as the last child in the container.
    * If a container is removed from the scene, all of its children are removed as well.
    *
    * The size of the container behaves as follows:
    * - By default, the width and height are adjusted automatically to fit all the container's children.
    * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth, and @c Control::maxWidth properties.
    * - The height is adjustable using the @c Control::preferredHeight, @c Control::minHeight, and @c Control::maxHeight properties.
    *
    * @c %Container also has a @c #background property, which allows you to specify a @c Paint object
    * which represents some sort of fill. The default fill for a container is fully transparent.
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT Container : public Control
    {
        Q_OBJECT
       /*!
        * @brief The @c Layout for the container.
        *
        * How a container positions its children is determined by the type
        * of layout it has. By default, a container's layout is a c StackLayout, but you can also use
        * @c AbsoluteLayout, @c GridLayout, or @c DockLayout.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::Layout * layout READ layout WRITE setLayout RESET resetLayout NOTIFY layoutChanged FINAL)

       /*!
        * @brief A @c QDeclarativeListProperty object that contains a hierarchical list of the container's
        * children.
        *
        * @xmlonly
        * <qml>
        * <property name="controls" listType="bb::cascades::Control" defaultProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QDeclarativeListProperty<bb::cascades::Control> controls READ controls FINAL)

       /*!
        * @brief Indicates whether the container should clip its children to its boundaries.
        *
        * If @c true, the container should clip its children; if @c false, the container should not.
        * The default is true.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool clipContentToBounds READ clipContentToBounds WRITE setClipContentToBounds
                   RESET resetClipContentToBounds NOTIFY clipContentToBoundsChanged FINAL)

       /*!
        * @brief A @c Paint object that specifies the background fill for the container.
        *
        * The default is the
        * paint returned by @c SystemDefaults::Paints::containerBackground().
        *
        * @xmlonly
        * <qml>
        * <variant type="bb::cascades::Paint"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QVariant background READ background WRITE setBackgroundQML RESET resetBackground NOTIFY backgroundChanged FINAL)
        Q_CLASSINFO("DefaultProperty", "controls")

        /*!
         * @brief Defines this control's accessibility object used by assistive technologies for
         * people with disabilities or impairments, for example, visual impairment.
         *
         * This property overloads the @c Control::accessibility property.
         *
         * Unlike controls with built-in accessibility objects which can't be overridden, this class
         * allows overriding the default accessibility object with a custom one, typically a
         * @c CustomA11yObject
         *
         * The accessibility object is expected to be set once (for example when assistive technology
         * is enabled).
         *
         * QML usage:
         * @snippet tad/examples/accessibility/assets/main.qml accessibility_qml4
         *
         * C++ usage:
         * @snippet tad/examples/accessibility/src/AccessibilityExamples.cpp accessibility1
         *
         * The default value of this property is the default accessibility object for this class.
         *
         * @see CustomA11yObject
         * @since BlackBerry 10.2.0
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         */
        Q_PROPERTY(bb::cascades::AbstractA11yObject* accessibility READ accessibility WRITE setAccessibility RESET resetAccessibility NOTIFY accessibilityChanged REVISION 2 FINAL)

        /*!
         * @brief Defines the behavior for navigation with trackpad and similar input.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bb::cascades::ContainerNavigation* navigation READ navigation CONSTANT REVISION 4 FINAL)

    public:

       /*!
        * @brief Constructs a container and adds it to a parent container.
        *
        * Specifying the parent container is optional.
        *
        * @param parent The parent container; an optional parameter that defaults to @c 0 if not specified.
        *
        * @since BlackBerry 10.0.0
        */
        explicit Container(Container *parent = 0);

        virtual ~Container();

       /*!
        * @brief Adds a control to the container.
        *
        * New controls are added as the last child in the container.
        * The control that is passed must not be @c 0 or it will be ignored. If the control is
        * already a child of the container that it is being added to, the operation fails.
        * If the control is currently a child of another container, it
        * is removed as a child from that container, and ownership is transferred to the new container.
        *
        * @param control The control to be added; must not be @c 0.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void add(bb::cascades::Control *control);

       /*!
        * @brief Inserts a control at a specified index in the container.
        *
        * The control that is passed must
        * not be @c 0 or it will be ignored. If the control is already a child of the container that
        * it is being added to, the operation fails. If the control is currently a child of another container, it
        * is removed as a child from that container, and ownership is transferred to the new container.
        *
        * Note: The @c controlMoved() signal is not emitted when an @c insert() is performed.
        *
        * @param index The index where the control will be placed. If the index < 0 the
        * the control is inserted as the first child. If the index > the number
        * of children in the container it is added as the last child.
        * @param control The control to be inserted; must not be @c 0.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void insert(int index, bb::cascades::Control *control);

       /*!
        * @brief Removes a control from the container.
        *
        * When the control is removed, the container no longer references it, but it is still
        * owned by the container. It is up to the application to either delete the removed
        * control, transfer its ownership (by setting its parent) to another object or leave
        * it as a child of the container (in which case it will be deleted with the container).
        *
        * @param control The control to be removed; must not be @c 0.
        * @return @c true if the control was a child of the container, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bool remove(bb::cascades::Control *control);

       /*!
        * @brief Removes all of a container's controls and frees up their memory.
        *
        * The @c controlRemoved() signal will be emitted with @c 0 as its parameter.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void removeAll();

       /*!
        * @brief Replaces the control at the specified index with a new control.
        *
        * When the control is replaced, the container no longer references it, but it is still
        * owned by the container. It is up to the application to either delete the replaced
        * control, transfer its ownership (by setting its parent) to another object or leave
        * it as a child of the container (in which case it will be deleted with the container).
        *
        * The control that is passed must not be @c 0 or it will be ignored. If the control
        * is already a child of the container that it is being added to, the operation fails
        * and @c 0 is returned. If the control is currently a child of another container, it
        * is removed as a child from that container, and ownership is transferred to the new
        * container.
        *
        * @param index The index of the control to replace.
        * @param newControl The control that will be placed at the specified index.
        * @return The replaced control if the operation is successful, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bb::cascades::Control* replace(int index, bb::cascades::Control *newControl);

       /*!
        * @brief Swaps the positions of two controls at the specified indexes.
        *
        * If either of the indexes are outside the range of the container, the operation fails.
        * The @c controlMoved() signal will be emitted upon successful swap.
        *
        * @param indexA The index of the first control to be swapped; must be a value
        * within the bounds of the container.
        * @param indexB The index of the second control to be swapped; must be a value
        * within the bounds of the container.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void swap(int indexA, int indexB);

       /*!
        * @brief Returns a control at the specified index.
        *
        * When completed, ownership of the control remains with the container.
        *
        * @param index The index of the control.
        * @return The requested control if the index was valid, @c 0 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bb::cascades::Control* at(int index) const;

       /*!
        * @brief Returns the index of a control.
        *
        * If the control isn't a child of the container
        * or if the control is @c 0, @c -1 is returned.
        *
        * @param control The control to get the index from.
        * @return The index of the specified control if the control is valid, @c -1 otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int indexOf(bb::cascades::Control *control) const;

       /*!
        * @brief Returns the number of controls.
        *
        * @return The number of controls.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int count() const;

       /*!
        * @brief Returns the @c #layout for the container.
        *
        * When completed, ownership of the layout remains with the container.
        *
        * @return The container's layout, or @c 0 if there's no layout associated with the container.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::Layout* layout() const;

       /*!
        * @brief Sets a #layout on the container.
        *
        * When completed, ownership of the layout is assigned to the container.
        *
        * @param layout The layout to be set on the container.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setLayout(bb::cascades::Layout *layout);

       /*!
        * @brief Resets the #layout to the default layout.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetLayout();

       /*!
        * @brief Sets the #background for the container.
        *
        * Setting a @c null paint is equivalent to calling #resetBackground();
        *
        * Valid subclasses to use as paint:
        *
        * - ColorPaint
        * - ImagePaint
        *
        * @param paint The new background.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setBackground(const bb::cascades::Paint& paint);

       /*!
        * @brief Returns the current #background of the Container.
        *
        * Use @c QVariant::canConvert<Type T>() to find actual type, and then @c QVariant::value<Type T>()
        * to get the value.
        *
        * For example:
        *
        * @snippet tad/examples/controls/container/src/ContainerExamples.cpp container2
        *
        * @return The current background paint, wrapped in @c QVariant.
        *
        * @since BlackBerry 10.0.0
        */
        QVariant background() const;

       /*!
        * @brief Resets the container's #background to the default returned
        * by @c SystemDefaults::Paints::containerBackground().
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetBackground();

       /*!
        * @brief Sets the container's #clipContentToBounds property, which indicates whether the container
        * should clip its children to its boundaries.
        *
        * @param clip If @c true the container clips its children, and if @c false it doesn't.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setClipContentToBounds(bool clip);

       /*!
        * @brief Indicates whether the container clips its children to its boundaries.
        *
        * @return @c true if container clips children to its boundaries, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool clipContentToBounds() const;

       /*!
        * @brief Resets the container's #clipContentToBounds property to its default.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetClipContentToBounds();


       /*!
        * @brief Sets an accessibility object for this control.
        *
        * When completed, ownership of the accessibility object is assigned to the container.
        * If @c accessibility is null, the property is reset to the default value.
        *
        * @param accessibility The new accessibility object.
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_SLOT void setAccessibility(bb::cascades::AbstractA11yObject *accessibility);

       /*!
        * @brief Resets this control's accessibility property to the
        * default accessibility object.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        Q_SLOT void resetAccessibility();

        /*!
         * @brief Returns a @c ContainerNavigation object that specifies the behavior for navigation with trackpad and similar input.
         *
         * @return A @c ContainerNavigation object that specifies the behavior for navigation with trackpad and similar input.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        bb::cascades::ContainerNavigation* navigation() const;


    Q_SIGNALS:
        /*!
        * @brief Emitted when a control has been added to the container.
        *
        * @param control The control that has been added.
         *
         * @since BlackBerry 10.0.0
        */
        void controlAdded(bb::cascades::Control *control);

       /*!
        * @brief Emitted when a control has been replaced by another control.
        *
        * @param oldControl The control that has been replaced.
        * @param newControl The new control.
        *
        * @since BlackBerry 10.0.0
        */
        void controlReplaced(bb::cascades::Control *oldControl, bb::cascades::Control *newControl);


       /*!
        * @brief Emitted when a control has been removed from the container.
        *
        * @param control The control that has been removed. @c 0 if emitted by @c removeAll().
        *
        * @since BlackBerry 10.0.0
        */
        void controlRemoved(bb::cascades::Control *control);

       /*!
        * @brief Emitted when a control has been moved by calling @c swap().
        *
        * Note: The @c controlMoved() signal is not emitted when an @c insert() is performed.
        *
        * @param control The control that has been moved.
        * @param newIndex The new index of the control.
        *
        * @since BlackBerry 10.0.0
        */
        void controlMoved(bb::cascades::Control *control, int newIndex);

       /*!
        * @brief Emitted when a new @c #layout is set on the container.
        *
        * @param layout The new layout.
        *
        * @since BlackBerry 10.0.0
        */
        void layoutChanged(bb::cascades::Layout *layout);

       /*!
        * @brief Emitted when the @c #background has changed.
        *
        * @param background The new background.
        *
        * @xmlonly
        * <qml>
        * <param name="background" type="QVariant"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        void backgroundChanged(const bb::cascades::Paint& background);

       /*! @cond PRIVATE */
       /*!
        * @brief Emitted when the #background has changed.
        *
        * @param background The new background.
        */
        void backgroundChanged(QVariant background);
       /*! @endcond */

       /*!
        * @brief Emitted when the @c #clipContentToBounds property has changed.
        *
        * @param clipContentToBounds @c true if the container clips its children to its boundaries,
        * @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        void clipContentToBoundsChanged(bool clipContentToBounds);

       /*!
        * @brief Emitted when #accessibility property has changed.
        *
        * @param accessibility The new accessibility object or the default accessibility
        * object if the property was reset.
        *
        * @since BlackBerry 10.2.0
        */
        Q_REVISION(2)
        void accessibilityChanged(bb::cascades::AbstractA11yObject *accessibility);

    private:
       /*! @cond PRIVATE */
        QDeclarativeListProperty<bb::cascades::Control> controls();
        Q_SLOT void setBackgroundQML(QVariant paint);

        Q_DECLARE_PRIVATE(Container)
        Q_DISABLE_COPY(Container)
       /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef Container ThisClass;
        typedef Control BaseClass;
        /*! @endcond */

        /*!
         * @brief A template builder class for constructing a Container.
         *
         * To retrieve the builder, call Container::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }
        public:

           /*!
            * @copydoc bb::cascades::Container::add(bb::cascades::Control*)
            */
            BuilderType& add(Control *control)
            {
                this->instance().add(control);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::Container::setLayout(bb::cascades::Layout*)
            */
            BuilderType& layout(bb::cascades::Layout *layout)
            {
                this->instance().setLayout(layout);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::Container::setBackground(const bb::cascades::Paint&)
            */
            BuilderType& background(const bb::cascades::Paint &paint)
            {
                this->instance().setBackground(paint);
                return this->builder();
            }

           /*!
            * @copydoc bb::cascades::Container::setClipContentToBounds(bool)
            */
            BuilderType& clip(bool clip)
            {
                this->instance().setClipContentToBounds(clip);
                return this->builder();
            }
        };

       /*!
        * @brief A concrete builder class for constructing a @c Container.
        *
        * To retrieve the builder, call @c Container::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, Container>
        {
        public:
            Builder() : TBuilder<Builder, Container>(new Container())
            {
            }
        };

       /*!
        * @brief Creates and returns a builder for constructing a @c Container.
        *
        * Using the builder to create a container:
        *
        * @snippet tad/examples/controls/container/src/ContainerExamples.cpp container1
        *
        * @return A builder used for constructing a container.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create()
        {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Container)

#endif	/* cascades_container_h */


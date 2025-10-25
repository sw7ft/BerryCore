/* Copyright (c) 2013 BlackBerry. All rights reserved. */

#ifndef CASCADES_PICKER_H
#define CASCADES_PICKER_H

#include <bb/cascades/bbcascades_global.h>
#include <QObject>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/resources/scrollanimation.h>
#include <bb/cascades/controls/pickerkind.h>

namespace bb {
    namespace cascades {

    class DataModel;
    class PickerPrivate;
    class PickerProvider;

    /*!
     * @brief A control for selecting custom items such as text, images or colors.
     *
     * You can specify the type of picker using the @c #kind property.
     * The @c PickerKind::Expandable state displays the picker with a title and description
     * which can be set using the @c title and the @c description properties.
     * The @c PickerKind::List state displays the picker without a header and always expanded.
     *
     * In C++ code, @c VisualNode items are defined in @c PickerProvider.
     * <br>In QML code, @c VisualNode items can be defined in @c pickerItemComponents property.
     *
     * Each @c PickerItemComponent can access its data using the @c pickerItemData property.
     * @c pickerItemData is the @c QVariant returned by
     * @c DataModel::data() for this item, typically it is a @c QVariantMap.
     *
     * Here's how to create and set up a picker with two columns:
     *
     *
     * QML:
     *
     * @code
     * Picker {
     *     id: picker
     *     title: "Picker title"
     *
     *     rootIndexPath: []
     *     dataModel: XmlDataModel { source: "data.xml" }
     *
     *     pickerItemComponents: [
     *         PickerItemComponent {
     *             type: "item1"
     *
     *             content: Container {
     *                 background: Color.create(pickerItemData.background)
     *             }
     *         },
     *         PickerItemComponent {
     *             type: "item2"
     *
     *             content: Container {
     *                 Label {
     *                     text: pickerItemData.text
     *                     textStyle.color: Color.create(pickerItemData.color)
     *                 }
     *             }
     *         }
     *     ]
     *
     *     onSelectedValueChanged: {
     *         var index0 = picker.selectedIndex(0);
     *         var index1 = picker.selectedIndex(1);
     *         console.log("Selection: " + index0 + ", " + index1);
     *     }
     * }
     * @endcode
     *
     * @code
     * <model>
     *   <column loop="true" >
     *     <item1 background="#ff0000ff" />
     *     <item1 background="#ff00ff00" />
     *     <item1 background="#ffff0000" />
     *     <item1 background="#ff00ffff" />
     *   </column>
     *   <column colspan="2">
     *     <item2 text="Item 1" color="#ff888888" />
     *     <item2 text="Item 2" color="#ff0000ff" />
     *     <item2 text="Item 3" color="#ff00ff00" />
     *     <item2 text="Item 4" color="#ff00ffff" />
     *     <item2 text="Item 5" color="#ffff0000" />
     *     <item2 text="Item 6" color="#ffff00ff" />
     *     <item2 text="Item 7" color="#ffffff00" />
     *     <item2 text="Item 8" color="#ffffffff" />
     *   </column>
     * </model>
     * @endcode
     *
     * C++:
     *
     * @code
     * picker = Picker::create()
     *            .title("Select")
     *            .pickerItemProvider(new MyItemsProvider())
     *            .expanded(true)
     * @endcode
     *
     * @xmlonly
     * <qml>
     * <class abstract="yes" />
     * </qml>
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.1.0
     */

    class BBCASCADES_EXPORT Picker : public Control {
        Q_OBJECT
    public:
        /*!
         * @brief Constructs a @c Picker with a parent and @c PickerKind::Default kind.
         *
         * @param parent The parent container or @c 0. The parent is optional and will default to @c 0 if not specified.
         *
         * @since BlackBerry 10.1.0
         */
        explicit Picker(Control* parent = 0);

        /*!
         * @brief Constructs a @c Picker with a specified kind and a parent.
         *
         * @param kind The kind of the @c Picker.
         * @param parent The parent container or @c 0. The parent is optional and will default to @c 0 if not specified.
         *
         * @since BlackBerry 10.1.0
         */
        explicit Picker(PickerKind::Type kind, Control* parent = 0);

        /*!
         * @brief Destructs the @c Picker.
         *
         * @since BlackBerry 10.1.0
         */
        virtual ~Picker();

    public:
        /*!
         * @brief The title of the @c Picker.
         *
         * This text is always visible in the header, whether the @c %Picker is expanded or collapsed.
         * The default @c title is @c QString::null, indicating that no title text is set.
         *
         * The @c titleChanged() signal is emitted when the title of the @c %Picker control changes.
         *
         * @note This property has no effect if @c kind is set to @c PickerKind::List.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

        /*!
         * @brief The expanded state of the @c Picker.
         *
         * The @c expandedChanged() signal is emitted as soon as the state starts to change.
         *
         * The @c expanded state is @c true as soon as @c %Picker starts to expand, and @c false as soon as it starts to collapse.
         * The default state is @c false (collapsed).
         *
         * @note This property has no effect if @c kind is set to @c PickerKind::List.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded RESET resetExpanded NOTIFY expandedChanged FINAL)

        /*!
         * @brief The description of the @c Picker.
         *
         * This text is visible in the header when the @c %Picker is collapsed.
         * The default @c description is @c QString::null, indicating that no description text is set.
         *
         * The @c descriptionChanged() signal is emitted when the description of the @c %Picker control changes.
         *
         * @note This property has no effect if @c kind set to @c PickerKind::List.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QString description READ description WRITE setDescription RESET resetDescription NOTIFY descriptionChanged FINAL)

        /*!
         * @brief Provides @c VisualNode objects to be displayed as items in the @c Picker.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::PickerProvider* pickerItemProvider READ pickerItemProvider WRITE setPickerItemProvider FINAL)

        /*!
         * @brief Specifies which node in the connected @c DataModel this @c Picker should use as the root.
         *
         * The default value is an empty @c QVariantList, which means that the
         * root node of the @c %DataModel is used as root node by this @c %Picker.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QVariantList rootIndexPath READ rootIndexPath WRITE setRootIndexPath NOTIFY rootIndexPathChanged FINAL)

        /*!
         * @brief Specifies a @c DataModel to use as source for item data in this @c Picker.
         *
         * The default value is @c 0, which means that no model is used.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::DataModel *dataModel READ dataModel WRITE setDataModel NOTIFY dataModelChanged FINAL)

        /*!
         * @brief Specifies a value corresponding to the currently selected items in this @c Picker.
         *
         * The @c selectedValueChanged() signal is emitted when @c selectedValue changes.
         *
         * The @c %selectedValueChanging() signal is emitted immediately when
         * the column is scrolling and the currently focused item is changed.
         *
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QVariant selectedValue READ selectedValue NOTIFY selectedValueChanged FINAL)

        /*!
         * @brief Specifies the number of columns in the @c Picker.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QVariant columnCount READ columnCount NOTIFY columnCountChanged FINAL)

        /*!
         * @brief The kind of @c Picker to create.
         *
         * Possible values for this property are @c PickerKind::Default, @c PickerKind::List
         * and @c PickerKind::Expandable.
         * The default value is @c PickerKind::Default, which indicates that
         * system default picker should be used.
         *
         * The @c PickerKind::Expandable state displays the picker with a title and description
         * that can be set using the @c title and the @c description properties.
         * The @c PickerKind::List state displays the picker without a header and always expanded.
         *
         * @note This property can only be set once during the construction of the @c Picker.
         *
         * Here's an example of how to create and set up different kinds of pickers:
         *
         * QML:
         *
         * @code
         * // List picker
         * Picker {
         *     id: picker
         *     kind: PickerKind.List;
         *
         *     dataModel: XmlDataModel { source: "data.xml" }
         *
         *     pickerItemComponents: [
         *         PickerItemComponent {
         *             type: "item"
         *
         *             content: Container {
         *                 background: Color.create(pickerItemData.background)
         *             }
         *         }
         *     ]
         * }
         * @endcode
         *
         * C++:
         *
         * @code
         * // Expandable picker
         * picker = Picker::create(PickerKind::Expandable)
         *            .title("Select")
         *            .pickerItemProvider(new MyItemsProvider())
         *            .expanded(true)
         * @endcode
         *
         *
         * @xmlonly
         * <qml>
         * <property writable="init-only"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::PickerKind::Type kind READ kind WRITE setKind FINAL)

        /*!
         * @brief The preferred number of rows to display in the picker control.
         *
         * This property defines the preferred number of rows to be shown by the picker.
         * The actual number of rows may be more than the preferred value.
         *
         * Though the @c preferredRowCount can be any integer value, the picker will always show the nearest
         * supported value for the picker (either three or five depending on the device).
         * If the value is set to @c 0, the system default number of rows is used. The default value is three
         * rows on keyboard devices and five rows on all-touch devices.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(int preferredRowCount
              READ preferredRowCount
              WRITE setPreferredRowCount
              RESET resetPreferredRowCount
              NOTIFY preferredRowCountChanged
              FINAL)

        /*!
         * @brief Sets the @c PickerProvider for the @c Picker.
         *
         * The @c %PickerProvider provides @c VisualNode objects to be shown as items in the @c %Picker.
         *
         * @param pProvider A pointer specifying the PickerProvider set.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setPickerItemProvider(bb::cascades::PickerProvider *pProvider);

        /*!
         * @brief Returns the @c PickerProvider assigned to the @c Picker
         *
         * @return Returns the @c PickerProvider
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::PickerProvider* pickerItemProvider();

        /*!
        * @brief Returns the number of columns in the @c Picker.
        *
        * @return The @c columnCount of the @c %Picker.
         *
         * @since BlackBerry 10.1.0
        */
        int columnCount() const;

        /*!
         * @brief Returns the current title of this @c Picker.
         *
         * @return The current title.
         *
         * @since BlackBerry 10.1.0
         */
        QString title() const;

        /*!
         * @brief Sets the title of the @c Picker.
         *
         * The title is visible at all times, and is shown on the left side of the @c %Picker header.
         * The title is truncated if it is too long to fit within the available space.
         *
         * @param title The new title.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setTitle(const QString &title);

        /*!
         * @brief Resets the title to the default value, @c QString::null.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetTitle();

        /*!
         * @brief Returns the current description of this @c Picker.
         *
         * @return The current description.
         *
         * @since BlackBerry 10.1.0
         */
        QString description() const;

        /*!
         * @brief Sets the description of the @c Picker.
         *
         * The description is shown on the right side of the @c %Picker header.
         *
         * @param description The new description.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setDescription( const QString &description );

        /*!
         * @brief Resets the description to the default value (@c QString::null).
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetDescription();

        /*!
         * @brief Returns the @c expanded state for the @c Picker.
         *
         * @return @c true if the @c %Picker is expanded, @c false if the @c %Picker is collapsed.
         *
         * @since BlackBerry 10.1.0
         */
        bool isExpanded() const;

        /*!
         * @brief Sets the expanded state.
         *
         * In the case of a successful change, the @c expandedChanged() signal is emitted.
         *
         * @param expanded If @c true the @c Picker is expanded, and if @c false the
         * @c %Picker is collapsed.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setExpanded(bool expanded);

        /*!
         * @brief Resets the expanded state to @c false (collapsed).
         *
         * The @c expandedChanged() signal is emitted once reset.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetExpanded();

        /*!
         * @brief Gets the currently selected index for the column.
         *
         * @param column The column to get the selected index for.
         *
         * @since BlackBerry 10.1.0
         */
        Q_INVOKABLE int selectedIndex(int column);

        /*!
         * @brief Gets the value corresponding to the currently selected items in the picker.
         *
         * @return The value corresponding to the currently selected items in the picker
         *
         * @since BlackBerry 10.1.0
         */
        QVariant selectedValue();

        /*!
         * @brief Sets the current selection for the picker and a scroll animation to animate the change.
         *
         * @param column The column to set selection for.
         * @param row The selected row in column.
         * @param scrollAnimation The type of animation to be used when scrolling.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void select(int column, int row, bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default);

        /*!
         * @brief Resets the @c Picker to it's default state.
         * No internal components or states are kept between reset calls.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void reset();

        /*!
         * @brief Returns the @c kind for the @c Picker.
         *
         * @return The current kind of picker.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::PickerKind::Type kind() const;

        /*!
         * @brief Gets the preferred number of rows in the picker control.
         *
         * @return The number of rows.
         *
         * @since BlackBerry 10.1.0
         */
        int preferredRowCount() const;

        /*!
         * @brief Sets the preferred number of rows to display in the picker control.
         *
         * @param rowCount The number of rows.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setPreferredRowCount(int rowCount);

        /*!
         * @brief Resets the preferred number of rows in the @c Picker to it's default value. The default
         * value is three rows for keyboard devices and five rows for all-touch devices.
         *
         * @since BlackBerry 10.1.0
         *
         */
        Q_SLOT void resetPreferredRowCount();

        /*!
         * @brief Gets the root index path used by this @c Picker when referencing data in its @c DataModel.
         *
         * @return The root index path used by this @c %Picker.
         *
         * @see @c setRootIndexPath(), @c resetRootIndexPath()
         *
         * @since BlackBerry 10.1.0
         */
        QVariantList rootIndexPath() const;

        /*!
         * @brief Sets the root index path for this @c Picker to use when it references data in the @c DataModel.
         *
         * The default value is an empty @c QVariantList,
         * which causes this @c %Picker to reference the top level of its @c %DataModel.
         *
         * @param rootIndexPath The root index path to use.
         *
         * @see @c rootIndexPath(), @c resetRootIndexPath()
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setRootIndexPath(const QVariantList &rootIndexPath);

        /*!
         * @brief Resets the root index path to its default value.
         *
         * This causes the @c Picker to reference the top level of its @c %DataModel.
         *
         * @see @c setRootIndexPath(), @c rootIndexPath()
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetRootIndexPath();

        /*!
         * @brief Gets the @c DataModel assigned to this @c Picker.
         *
         * @return The @c DataModel assigned to this @c %Picker.
         *
         * @see setDataModel(), resetDataModel()
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::DataModel *dataModel() const;

        /*!
         * @brief Assigns a @c DataModel to this @c Picker.
         *
         * This @c %Picker will use the @c DataModel to populate itself with picker items.
         * If @c pDataModel has no parent, this @c %Picker takes ownership of it and
         * sets itself as parent to it (which means that @c %Picker deletes it
         * when @c %Picker is deleted). Any previously set @c %DataModel is
         * unaffected by this call, its parent won't change and it won't be
         * deleted as a result of calling @c setDataModel().
         *
         * @param pDataModel The @c %DataModel to assign to this @c %Picker.
         *
         * @see dataModel(), resetDataModel()
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setDataModel(bb::cascades::DataModel *pDataModel);

        /*!
         * @brief Resets the @c DataModel reference in this @c Picker, effectively leaving
         * the @c %Picker without an assigned @c %DataModel.
         *
         * @see setDataModel(), dataModel()
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetDataModel();

    Q_SIGNALS:
         /*!
         * @brief Emitted when the title of this @c Picker changes.
         *
         * @param title The new @c title.
          *
          * @since BlackBerry 10.1.0
         */
        void titleChanged(const QString& title);

        /*!
         * @brief Emitted when the @c expanded state has been changed.
         *
         * @param expanded The newly set @c expanded state
         *
         * @since BlackBerry 10.1.0
         */
        void expandedChanged(bool expanded);

         /*!
         * @brief Emitted when the description of this @c Picker changes.
         *
         * @param description The new @c description.
          *
          * @since BlackBerry 10.1.0
         */
        void descriptionChanged(const QString& description);

        /*!
         * @brief Emitted when @c selectedValue changes.
         *
         * @param selectedValue The value corresponding to the currently selected items in the @c Picker.
         *
         * @see @c selectedValueChanging()
         *
         * @since BlackBerry 10.1.0
         */
        void selectedValueChanged(const QVariant &selectedValue);

        /*!
         * @brief Emitted when @c selectedValue is changing but not confirmed yet.
         *
         * Emitted when column is scrolling and currently focused item is changed.
         *
         * @param selectedValue The value corresponding to the currently selecting items in the @c %Picker.
         *
         * @note There is no guarantee the signal is emitted for every value the @c Picker
         * passes through while scrolling. The signal is emitted for the final value together
         * with @c selectedValueChanged().
         *
         * @see @c selectedValueChanged()
         *
         * @since BlackBerry 10.1.0
         */
        void selectedValueChanging(const QVariant &selectedValue);

        /*!
         * @brief Emitted when the @c columnCount changes.
         *
         * @param columnCount The number of columns in the picker.
         *
         * @since BlackBerry 10.1.0
         */
        void columnCountChanged(int columnCount);

        /*!
         * @brief Emitted when the preferred number of rows changes.
         *
         * @param rowCount The new number of rows.
         *
         * @since BlackBerry 10.1.0
         */
        void preferredRowCountChanged(int rowCount);

        /*!
         * @brief Emitted when @c Picker::rootIndexPath has changed.
         *
         * @param rootIndexPath The new root index path.
         *
         * @since BlackBerry 10.1.0
         */
        void rootIndexPathChanged(const QVariantList &rootIndexPath);

        /*!
         * @brief Emitted when @c Picker::dataModel has changed.
         *
         * @param dataModel The new @c DataModel.
         *
         * @since BlackBerry 10.1.0
         */
        void dataModelChanged(bb::cascades::DataModel *dataModel);

    protected:
        /*! @cond PRIVATE */
        Picker(PickerPrivate &_d_ptr, Control *parent = 0);
        Picker(PickerPrivate &_d_ptr, PickerKind::Type kind, Control *parent = 0);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(Picker)
        Q_DISABLE_COPY(Picker)

        typedef Picker ThisClass;
        typedef Control BaseClass;

        void setKind(bb::cascades::PickerKind::Type kind);
        /*! @endcond */

    public:
        /*!
         * @brief A builder template for constructing a @c Picker object.
         *
         * To retrieve the builder, call @c Picker::create().
         *
         * @since BlackBerry 10.1.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }

        public:
            /*!
             * @brief Sets the description of this @c Picker.
             *
             * @param description The description of the @c %Picker.
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& description(const QString &description) {
                this->instance().setDescription(description);
                return this->builder();
            }

            /*!
             * @brief Sets the title for this @c Picker
             *
             * @param title The title of this @c %Picker.
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& title(const QString &title) {
                this->instance().setTitle(title);
                return this->builder();
            }

            /*!
             * @brief Sets the @c PickerProvider for this @c Picker
             *
             * @param pProvider The item provider for this @c %Picker.
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& pickerItemProvider(PickerProvider *pProvider) {
                this->instance().setPickerItemProvider(pProvider);
                return this->builder();
            }

            /*!
             * @brief Sets the expanded property for this @c Picker
             *
             * @param expanded Created expanded @c %Picker or not.
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& expanded(bool expanded) {
                this->instance().setExpanded(expanded);
                return this->builder();
            }

            /*!
             * @brief Sets the @c kind property for this @c Picker
             *
             * @param kind The kind of picker.
             * @deprecated Pass @c kind to the constructor instead
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& kind(bb::cascades::PickerKind::Type kind) {
                this->instance().setKind(kind);
                return this->builder();
            }

            /*!
            * @copydoc bb::cascades::Picker::setPreferredRowCount(int)
            */
            BuilderType& preferredRowCount(int rowCount) {
                this->instance().setPreferredRowCount(rowCount);
                return this->builder();
            }
        };

        /*!
        * @brief A builder for constructing a @c Picker object.
        *
        * To retrieve the builder, call @c Picker::create().
        *
        * @since BlackBerry 10.1.0
        */
        class Builder : public TBuilder<Builder, Picker>
        {
        public:
            explicit Builder() : TBuilder<Builder, Picker>(new Picker()) {}
            explicit Builder(PickerKind::Type kind) : TBuilder<Builder, Picker>(new Picker(kind, 0)) {}
        };


        /*!
        * @brief Creates and returns a builder for constructing a @c Picker object.
        *
        * @param kind Specifies the kind of this picker
        *
        * The following example uses the builder to create a @c %Picker object:
        *
        * @code
        * Picker::create(PickerKind::Expandable)
        *     .description("pick")
        *     .title("Title");
        * @endcode
        *
        * @return A builder used for constructing a @c Picker object.
         *
         * @since BlackBerry 10.1.0
        */
        static Builder create(PickerKind::Type kind) {
            return Builder(kind);
        }

        /*!
        * @brief Creates and returns a builder for constructing a @c Picker object with default @c kind.
        *
        * The following example uses the builder to create a @c %Picker object:
        *
        * @code
        * Picker::create()
        *     .description("pick")
        *     .title("Title");
        * @endcode
        *
        * @return A builder used for constructing a @c Picker object.
         *
         * @since BlackBerry 10.1.0
        */
        static Builder create() {
            return Builder(PickerKind::Default);
        }
    };

    } /* namespace cascades */
} /* namespace bb */

#endif /* CASCADES_PICKER_H */

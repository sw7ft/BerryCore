/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_xmldatamodel_h
#define cascades_xmldatamodel_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/databinding/datamodel.h>


namespace bb {
namespace cascades {

    class XmlDataModelPrivate;

    /*!
     * @brief A class that creates a static @c DataModel for @c ListView from an XML file.
     *
     * The @c %XmlDataModel is useful when prototyping a UI, since it allows a
     * complex model to be declared in an XML file without any C++ code being written.
     *
     * Each element in the XML file (except the mandatory root element) can be shown as
     * an item in the @c %ListView. XmlDataModel::data() returns a @c QVariantMap (wrapped in
     * a @c QVariant) containing the properties of the requested element/item.
     * XmlDataModel::itemType() returns the name of the requested element/item.
     * The model tree can be many levels deep, but @c %ListView typically
     * only shows items from the two first levels under its root item.
     *
     * Text written outside of tags in the XML file is ignored. Any values that
     * are to be used in list item visuals must be written as properties on tags.
     *
     * Example of an XML model with items on three levels (not counting the
     * mandatory root element):
     *
     * @code
     * <model>
     *   <header title="A">
     *     <contact name="Adam">
     *       <phone number="+4623894299" />
     *       <phone number="+4623929922" />
     *     </contact>
     *     <contact name="Annie">
     *       <phone number="+4654633667" />
     *       <email address="annie@rim.com" />
     *     </contact>
     *   </header>
     *   <header title="B">
     *     <contact name="Bert">
     *       <phone number="+465256467" />
     *       <phone number="+464746734" />
     *       <phone number="+468234892" />
     *     </contact>
     *   </header>
     * </model>
     * @endcode
     *
     * Example of how to use @c %XmlDataModel on a @c %ListView in QML:
     *
     * @code
     * ListView {
     *     dataModel: XmlDataModel { source: "model.xml" }
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="Data management/Data models"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT XmlDataModel : public DataModel {
        Q_OBJECT

        /*!
         * @brief The path to the source XML file.
         * 
         * In QML, the path is relative to the QML document in which this @c %XmlDataModel
         * is declared. When setting this property from C++, the path is instead relative
         * to the application assets folder.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged FINAL)

    public:
        /*!
        * @brief Constructs an empty @c %XmlDataModel with the specified parent.
        *
        * @param parent The data model owner, or @c 0. Optional and defaults to @c 0 if not
        * specified.
         *
         * @since BlackBerry 10.0.0
        */
        explicit XmlDataModel(QObject *parent = 0);

        /*!
         * @brief Destructs this @c %XmlDataModel.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~XmlDataModel();

        /*!
         * @brief Returns the number of children for the data item specified by @c indexPath.
         *
         * The root item is represented by an empty index path. This example shows
         * how to get the number of top level items (items having the root item
         * as parent) in a @c %XmlDataModel:
         *
         * @code
         * int numberOfHeaders = model->childCount(QVariantList());
         * @endcode
         *
         * @param indexPath The index path to the data item to get child count for.
         *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths)
         *        for more information.
         * 
         * @return The number of children. The return value for invalid index paths is undefined.
         *
         * @since BlackBerry 10.0.0
         */
        virtual int childCount(const QVariantList &indexPath);

        /*!
         * @brief Indicates whether the data item specified by @c indexPath
         * has children.
         *
         * @param indexPath The index path to the data item to query for children.
         *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths)
         *        for more information.
         * 
         * @return @c true if the data item has one or more children, @c false otherwise.
         * ListView never calls this function for its root node (but does call
         * childCount() for the root node), therefore the return-value for
         * an empty index path is undefined.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool hasChildren(const QVariantList &indexPath);

        /*!
        * @brief Returns a @c %QVariantMap containing the properties of the specified item.
        *
        * The ListView will pass on the data as a parameter to ListItemProvider::updateItem().
        * In QML the data is made available as @c %ListItem.data on the root node of
        * the list item visuals, and as @c %ListItemData in the context of the list item visuals.
        *
        * @param indexPath The index path to the item in the model.
        *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths)
        *        for more information.
        * 
        * @return A @c QVariantMap or @c QObject* (one of those inserted into
        * this model) wrapped in a @c QVariant, or @c QVariant::Invalid if the argument
        * indexPath is invalid.
         *
         * @since BlackBerry 10.0.0
        */
        virtual QVariant data(const QVariantList &indexPath);

        /*!
        * @brief Returns the type for the specified item.
        *
        * The type for each item is determined by the name of the corresponding tag in the XML file.
        *
        * @param indexPath The index path to the item in the model.
        *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths)
        *        for more information.
        * 
        * @return The name of the corresponding tag in the XML file.
         *
         * @since BlackBerry 10.0.0
        */
        virtual QString itemType(const QVariantList &indexPath);

        /*!
         * @brief Sets a new path to the source XML file.
         * 
         * The path is relative to the application assets folder.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSource(const QUrl &newSource);

        /*!
         * @brief Gets the current value of the @c #source property.
         * 
         * @return The current path to the source XML file.
         *
         * @since BlackBerry 10.0.0
         */
        QUrl source() const;

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c #source property changes.
         * 
         * @param source The new path of the source XML file.
         *
         * @since BlackBerry 10.0.0
         */
        void sourceChanged(QUrl source);

    private:
        /*! @cond PRIVATE */
        XmlDataModelPrivate* const d_ptr;
        Q_DECLARE_PRIVATE(XmlDataModel)
        Q_DISABLE_COPY(XmlDataModel)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::XmlDataModel)

#endif // cascades_xmldatamodel_h

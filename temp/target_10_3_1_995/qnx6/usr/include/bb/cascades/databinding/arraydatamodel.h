/* Copyright (C) 2011-2013 Research In Motion Limited.  */
#ifndef cascades_arraydatamodel_h
#define cascades_arraydatamodel_h

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/databinding/datamodel.h>


namespace bb {
namespace cascades {
  class ArrayDataModelPrivate;

  /*!
   * @brief Contains a list of @c QVariant values, typically for a @c ListView.
   *
   * The @c %ArrayDataModel is useful when you want to create a simple list of
   * items and manipulate the order manually.
   *
   * Items can be inserted or appended by passing a single @c QVariant item or a
   * list of @c QVariant items. Values can be removed, replaced and swapped within
   * bounds of the data model. When inserting a @c QVariant that contains a @c %QObject* 
   * that does not have any parent, the data model will claim ownership of the @c %QObject. 
   *
   * Example of how to use @c %ArrayDataModel on a @c %ListView in QML:
   *
   * @code
   * ListView {
   *     dataModel: ArrayDataModel {
   *         id: theDataModel
   *     }
   *     onCreationCompleted: {
   *         for ( var a = 0; a < 20; a++ ) {
   *             theDataModel.append("Item" + a);
   *         }
   *         theDataModel.append(["Appended 1", "Appended 2"]);
   *         theDataModel.removeAt(0);
   *         theDataModel.insert(0,["Prepended 1", "Prepended 2"]);
   *     }
   * }
   * @endcode
   *
   * <h2>Using an ArrayDataModel with a custom ListItemComponent</h2>
   *
   * If you use an @c %ArrayDataModel and want to use a custom @c %ListItemComponent in your
   * list, you need to keep in mind that @c ArrayDataModel::itemType() returns an empty 
   * string (""). To use a custom @c %ListItemComponent in your list, you can implement your own
   * @c %itemType function (either on your custom @c %ArrayDataModel or on the @c ListView 
   * itself), or set @c %item="" in your @c &ListItemComponent. For more information about how to
   * use a custom @c %ListItemComponent with an @c %ArrayDataModel, see "The default list 
   * visuals" section in @c ListView.
   *
   * @xmlonly
   * <apigrouping group="Data management/Data models"/>
   * @endxmlonly
   *
   * @since BlackBerry 10.0.0
   */
  class BBCASCADES_EXPORT ArrayDataModel : public DataModel {
    Q_OBJECT

  public:
    /*!
     * @brief Constructs an empty @c ArrayDataModel.
     *
     * @param parent The data model owner or @c 0. Optional and defaults to @c 0 if
     * not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit ArrayDataModel(QObject *parent = 0);

    /*!
     * @brief Constructs an @c ArrayDataModel using the specified @c QVariantList.
     * 
     * Ownership of the @c %QVariantList is transferred to the @c %ArrayDataModel.
     *
     * @param other The initial data to be used by the @c %ArrayDataModel.
     * @param parent The data model owner or @c 0. Optional and defaults to @c 0 if
     *               not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit ArrayDataModel(const QList<QVariant> &other, QObject *parent = 0);

    virtual ~ArrayDataModel();

    /*!
     * @copydoc DataModel::childCount(const QVariantList &)
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE virtual int childCount(const QVariantList &indexPath);

    /*!
     * @copydoc DataModel::hasChildren(const QVariantList &)
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE virtual bool hasChildren(const QVariantList &indexPath);

    /*!
     * @copydoc DataModel::itemType(const QVariantList &)
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE virtual QString itemType(const QVariantList &indexPath);

    /*!
     * @copydoc DataModel::data(const QVariantList &)
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE virtual QVariant data(const QVariantList &indexPath);

    /*!
     * @brief Inserts a list of values at the end of this model.
     *
     * @param values The values to be appended. Ownership of @c QObject
     *              items that don't have parents is transferred to this
     *              @c %ArrayDataModel.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void append(const QVariantList &values);

    /*!
     * @brief Inserts a single value at the end of this model.
     *
     * @param value The value to be appended. Ownership of @c QObject
     *              items that don't have parents is transferred to this
     *              @c %ArrayDataModel.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void append(const QVariant &value);

    /*!
     * @brief Removes all values from this model. QObjects owned by this model
     * are deleted.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void clear();

    /*!
     * @brief Searches this @c ArrayDataModel from the specified index position
     * from until the specified item is found.
     *
     * If no such item is found, -1 is returned.
     *
     * @param value The @c QVariant to search for.
     * @param from The index position to search from.
     *
     * @return The index position if a matching item was found, -1 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE int indexOf(const QVariant &value, int from = 0) const;

    /*!
     * @brief Inserts a list of @c QVariant values at the specified index
     * position @c i in this @c ArrayDataModel.
     *
     * If @c i is 0, the values are prepended to the list. If @c i is @c size(), the
     * values are appended to the list.
     *
     * @param i The position in this @c %ArrayDataModel to add the list of values.
     * @param values The list of @c %QVariant items to be inserted. Ownership
     *               of @c QObject items that don't have parents is transferred
     *               to this @c %ArrayDataModel.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void insert(int i, const QVariantList &values);

    /*!
     * @brief Inserts a single @c QVariant value at the specified index
     * position @c i in this @c ArrayDataModel.
     *
     * If @c i is 0, the value is prepended to the list. If @c i is @c size(), the
     * value is appended to the list.
     *
     * @param i The position in this @c %ArrayDataModel to add the value.
     * @param value The @c %QVariant value to be inserted. Ownership of @c QObject
     *              items that don't have parents is transferred to this
     *              @c %ArrayDataModel.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void insert(int i, const QVariant &value);

    /*!
     * @brief Indicates whether this @c ArrayDataModel is empty.
     *
     * @return @c true if the model holds no values, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isEmpty() const;

    /*!
     * @brief Moves the value at one index position to another index position.
     *
     * This function assumes that both the original position, @c from, and the
     * destination position, @c to, are at least 0 and less than @c size().
     * If any of the positions are out of range, calling this function has no effect.
     *
     * @param from The index position to move from.
     * @param to The index position to move to.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void move(int from, int to);

    /*!
     * @brief Removes the value at the specified index position @c i.
     *
     * The index @c i must be at least 0 and less than @c size(). If the
     * @c QObject at index position @c i is owned by this @c ArrayDataModel, the
     * object is deleted. If the index is out of range, calling this function has no 
     * effect.
     *
     * @param i The index of the value to be removed.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void removeAt(int i);

    /*!
     * @brief Replaces the value at the specified index position @c i with the
     * specified value.
     *
     * If the previous value at this position is owned by this @c ArrayDataModel,
     * the object is deleted.
     *
     * The index @c i must be at least 0 and less than @c size(). If the index is out
     * of range, this function has no effect.
     *
     * @param i The index of the value to be replaced.
     * @param value The replacement value. Ownership of @c QObject items that
     *              don't have parents is transferred to this @c %ArrayDataModel.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void replace(int i, const QVariant &value);

    /*!
     * @brief Returns the number of values in this @c ArrayDataModel.
     *
     * @return The number of values in this @c %ArrayDataModel.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE int size() const;

    /*!
     * @brief Exchanges the value at index position @c i with the value at index
     * position @c j.
     *
     * This function assumes that both @c i and @c j are at least 0 and less than
     * @c size(). If any of the indices are out of range, calling this function has
     * no effect.
     *
     * @param i The index of the first value.
     * @param j The index of the second value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void swap(int i, int j);

    /*!
     * @brief Returns the value at the specified index position @c i in this
     * @c ArrayDataModel.
     *
     * If index @c i is out of bounds (that is, if @c i is less than 0 or greater
     * than or equal to @c size()), this function returns an invalid @c QVariant.
     *
     * @param i The index of the value to be returned.
     *
     * @return The value at index position @c i.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QVariant value(int i) const;

    /*!
     * @brief Returns the value at the specified index position @c i in this
     * @c ArrayDataModel.
     *
     * If index @c i is out of bounds (that is, if @c i is less than 0 or greater
     * than or equal to @c size()), this function returns @c defaultValue.
     *
     * @param i The index of the value to be returned.
     * @param defaultValue The value to be returned if @c i is out of bounds.
     *
     * @return The value at index position @c i.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QVariant value(int i, const QVariant &defaultValue) const;


  private:
    /*! @cond PRIVATE */
    ArrayDataModelPrivate* const d_ptr;
    Q_DECLARE_PRIVATE(ArrayDataModel)
    Q_DISABLE_COPY(ArrayDataModel)
    /*! @endcond */

  };
  
} // cascades
} // bb

QML_DECLARE_TYPE(bb::cascades::ArrayDataModel)

#endif // cascades_arraydatamodel_h

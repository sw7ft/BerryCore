/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_DATAMANAGER_DATAMODELDECORATOR_HPP_
#define BB_CASCADES_DATAMANAGER_DATAMODELDECORATOR_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/DataModel>
#include <QScopedPointer>


namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataModelDecoratorPrivate;

/*!
 * @headerfile DataModelDecorator.hpp <bb/cascades/datamanager/DataModelDecorator>
 *
 * @brief @c DataModelDecorator is used to decorate the @c DataModel before it is used by @c ListView.
 *
 * This base class delegates all @c %DataModel method calls to the model being
 * decorated. It also connects the corresponding @c DataModel Q_SIGNALS to the model
 * being decorated.
 *
 * This class can be useful when reinterpreting data before being used by
 * @c %ListView. For example, the @c itemType() method can return custom types depending on the
 * contents of the data or the @c data() method can be used to add custom data columns based
 * on existing data.
 *
 * @c %DataModelDecorator is also used to insert data. The inserted data can be generated
 * from the existing data being decorated, or anything that does not have to be related
 * to the model being decorated.
 *
 * This class can serve the role of a View Model in the MVVM design pattern. See a description of MVVM
 * here: [Model View ViewModel](http://en.wikipedia.org/wiki/Model_View_ViewModel).
 *
 * Here is a QML example showing the usage of a @c %DataModelDecorator:
 *
 * @snippet libbbcascadesdatamanager/examples/DataModelDecorator/assets/DataModelDecoratorExamples.qml datamodeldecorator1
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT DataModelDecorator: public bb::cascades::DataModel
{
    Q_OBJECT

    /*!
     * @brief The model to be decorated.
     *
     * If the model has no parent, the @c DataModelDecorator takes ownership of it
     * and sets itself as parent to it. Any previously set @c DataModel is
     * unaffected by this call, its parent won't change and it won't be
     * deleted as a result of calling @c setModel().
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::DataModel *model READ model WRITE setModel NOTIFY modelChanged FINAL)

public:
    /*!
     * @brief Constructs a @c DataModelDecorator.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataModelDecorator(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataModelDecorator();

    /*!
     * @brief Calls the @c childCount() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the data item to get the child count for.
     *
     * @return The number of children. The return value for invalid index paths is undefined.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual int childCount(const QVariantList &indexPath);

    /*!
     * @brief Calls the @c hasChildren() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the data item to query for children.
     *
     * @return @c True if the data item has one or more children, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual bool hasChildren(const QVariantList &indexPath);

    /*!
     * @brief Calls the @c itemType() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the item in the model.
     *
     * @return A string identifying the type for this item.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QString itemType(const QVariantList &indexPath);

    /*!
     * @brief Calls the @c data() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the item in the model.
     *
     * @return The data for this item.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QVariant data(const QVariantList &indexPath);

    /*!
     * @brief Get the @c DataModel being decorated.
     *
     * @return The @c %DataModel being decorated.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::DataModel* model();

    /*!
     * @brief Set the @c DataModel being decorated.
     *
     * If the model has no parent, @c DataModelDecorator takes ownership of it
     * and sets itself as parent to it. Any previously set @c %DataModel is
     * unaffected by this call, its parent won't change, and it won't be
     * deleted as a result of calling @c setModel().
     *
     * @param model The @c %DataModel being decorated. Pointer must not be null.
     *
     * @since BlackBerry 10.2.0
     */
    void setModel(bb::cascades::DataModel *model);

    /*!
     * @brief Connect to the decorated model's @c itemAdded() signal and forward the signal.
     *
     * @param indexPath The path to the item in the model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemAdded(QVariantList indexPath);

    /*!
     * @brief Connect to the decorated model's @c itemUpdated() signal and forward the signal.
     *
     * @param indexPath The path to the item in the model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemUpdated(QVariantList indexPath);

    /*!
     * @brief Connect to the decorated model's @c itemRemoved() signal and forward the signal.
     *
     * @param indexPath The path to the item in the model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemRemoved(QVariantList indexPath);

    /*!
     * @brief Connect to the decorated model's @c itemsChanged() signal and forward the signal.
     *
     * Emitted when the model has changed in a way that would be inefficient
     * to describe with single instances of the other signals.
     *
     * No other signals (@c DataModel::itemAdded(), @c DataModel::itemUpdated(),
     * or @c DataModel::itemRemoved()) are emitted if this signal is emitted
     * when a change occurs in this @c DataModel.
     *
     * Here are some typical examples of when this signal is emitted:
     * - the data has been sorted (so that many items have changed places)
     * - the @c %DataModel has been cleared (all items have been removed)
     * - a batch of items has been added.
     *
     * If @c eChangeType is @c DataModelChangeType::Init, or if @c eChangeType
     * is @c DataModelChangeType::AddRemove and @c indexMapper is @c 0, a
     * @c ListView reacts to this signal by releasing all of the items in its cache.
     *
     * If @c eChangeType is @c AddRemove and an @c IndexMapper is provided, the
     * @c %ListView calls @c IndexMapper::newIndexPath() for each item in its cache.
     *
     * If @c eChangeType is @c DataModelChangeType::Update, a @c %ListView reacts to
     * this signal by calling @c DataModel::data() again for every item in its
     * cache.
     *
     * @param eChangeType The type of change.
     * @param indexMapper An index mapper that contains update information.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemsChanged(bb::cascades::DataModelChangeType::Type eChangeType = bb::cascades::DataModelChangeType::Init,
                QSharedPointer<bb::cascades::DataModel::IndexMapper> indexMapper =
                QSharedPointer<bb::cascades::DataModel::IndexMapper>(0));

Q_SIGNALS:
    /*!
     * @brief This signal is emitted when the @c DataModel being decorated has changed.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void modelChanged();

private:
    /*! @cond PRIVATE */
    QScopedPointer<DataModelDecoratorPrivate> const d_ptr;

    Q_DECLARE_PRIVATE(DataModelDecorator)
    Q_DISABLE_COPY(DataModelDecorator)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_DATAMODELDECORATOR_HPP_ */

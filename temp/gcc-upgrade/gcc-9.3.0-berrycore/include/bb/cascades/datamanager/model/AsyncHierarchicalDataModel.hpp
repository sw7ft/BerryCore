/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_ASYNCHIERARCHICALDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_ASYNCHIERARCHICALDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include  <bb/cascades/datamanager/AsyncDataModel>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class AsyncHierarchicalDataModelPrivate;

/*!
 * @headerfile AsyncHierarchicalDataModel.hpp <bb/cascades/datamanager/AsyncHierarchicalDataModel>
 *
 * @brief A data model that supports index paths with length greater than one.
 *
 * See the @c DataModel class description for a definition of index paths and how they are used.
 *
 * You need to provide a @c HeaderDataQuery in order to populate the @c DataModel.
 * A @c HeaderDescriptor is needed to specify the structure of the header data
 * returned by @c %HeaderDataQuery. This is done by extending this class and implementing
 * the pure virtual @c headerDescriptor() method of this class.
 *
 * @note The header data from the @c %HeaderDataQuery is cached in its full size
 * and used to refer to child data level (leaf) items. Only the data level items
 * are partially cached.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT AsyncHierarchicalDataModel : public AsyncDataModel
{
Q_OBJECT
public:
    /*!
     * @brief @c HeaderDescriptor is used to describe the header data
     * returned by the @c HeaderDataQuery.
     *
     * @xmlonly
     * <apigrouping group="Data Management/Large Data Sets"/>
     * <library name="bbcascadesdatamanager"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BB_CASCADES_DATAMANAGER_EXPORT HeaderDescriptor {
    public:
        /**
         * @brief Destructor.
         */
        virtual ~HeaderDescriptor();

        /*!
         * @brief The header child count of the index path.
         *
         * @param indexPath The index path.
         * @param headerData The header data used to get the child count of the
         * index path. Header data is returned from the @c HeaderDataQuery.
         *
         * @return The child count of the index path.
         *
         * @since BlackBerry 10.2.0
         */
        virtual int headerChildCount(const QVariantList &indexPath,
                                const QList<HeaderDataItem> &headerData) = 0;

        /*!
         * @brief The header data of the index path.
         *
         * @param indexPath The index path.
         * @param headerData The header data returned from the @c HeaderDataQuery.
         *
         * @return The header data of the index path.
         *
         * @since BlackBerry 10.2.0
         */
        virtual HeaderDataItem headerData(const QVariantList &indexPath,
                                const QList<HeaderDataItem> &headerData) = 0;
    };

    /*!
     * @brief Constructs a @c AsyncHierarchicalDataModel.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit AsyncHierarchicalDataModel(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~AsyncHierarchicalDataModel();

    /*!
     * @brief Get the header descriptor of the header @c DataModel.
     *
     * @return The header descriptor.
     *
     * @see HeaderContiguousCacheModel::HeaderDescriptor
     *
     * @since BlackBerry 10.2.0
     */
    virtual QSharedPointer<AsyncHierarchicalDataModel::HeaderDescriptor> headerDescriptor() const = 0;

protected:
    /*! @cond PRIVATE */
    AsyncHierarchicalDataModel(AsyncHierarchicalDataModelPrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(AsyncHierarchicalDataModel);
    Q_DISABLE_COPY(AsyncHierarchicalDataModel)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_ASYNCHIERARCHICALDATAMODEL_HPP_ */

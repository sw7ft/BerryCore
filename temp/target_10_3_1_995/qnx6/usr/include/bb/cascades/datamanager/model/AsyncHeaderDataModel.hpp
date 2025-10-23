/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_ASYNCHEADERDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_ASYNCHEADERDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include  <bb/cascades/datamanager/AsyncHierarchicalDataModel>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class AsyncHeaderDataModelPrivate;

/*!
 * @headerfile AsyncHeaderDataModel.hpp <bb/cascades/datamanager/AsyncHeaderDataModel>
 *
 * @brief A data model that supports index paths with length of two.
 *
 * This class is designed to use a @c HeaderDataQuery to retrieve top-level header items and a
 * @c DataQuery to retrieve detailed-level items.
 *
 * The header data is cached in full by the parent @c AsyncHierarchicalDataModel and
 * the detailed items are partially cached up to a specified cache size (default 200).
 *
 * Here is a QML example showing the usage of an AsyncHeaderDataModel:
 *
 * @snippet libbbcascadesdatamanager/examples/AsyncHeaderDataModel/assets/AsyncHeaderDataModelExamples.qml asyncheaderdatamodel1
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT AsyncHeaderDataModel : public AsyncHierarchicalDataModel
{
Q_OBJECT
public:
    /*!
     * @brief Constructs an @c AsyncHeaderDataModel.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit AsyncHeaderDataModel(QObject *parent = 0);

    /*!
     * Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~AsyncHeaderDataModel();

    /*!
     * @brief Returns the descriptor for the current header data.
     *
     * @return The header descriptor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QSharedPointer<AsyncHierarchicalDataModel::HeaderDescriptor> headerDescriptor() const;

protected:
    /*! @cond PRIVATE */
    AsyncHeaderDataModel(AsyncHeaderDataModelPrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(AsyncHeaderDataModel)
    Q_DISABLE_COPY(AsyncHeaderDataModel)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_ASYNCHEADERDATAMODEL_HPP_ */



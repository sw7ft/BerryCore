/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_HEADERDATAQUERY_HPP_
#define BB_CASCADES_DATAMANAGER_HEADERDATAQUERY_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataQuery>
#include <bb/cascades/datamanager/HeaderDataItem>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class HeaderDataQueryPrivate;

/*!
 * @headerfile HeaderDataQuery.hpp <bb/cascades/datamanager/HeaderDataQuery>
 *
 * @brief Retrieve data and header data for a particular view of a data source.
 *
 * To implement this class, you must decide how to handle error conditions. If there
 * are SQL or other expected or unexpected runtime errors, you must determine
 * which of these errors are catastrophic and which are recoverable.
 * See the @c DataQuery class description for error handling guidelines.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT HeaderDataQuery : public DataQuery
{
Q_OBJECT

public:
    /*!
     * @brief Constructs a @c HeaderDataQuery.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */

    explicit HeaderDataQuery(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~HeaderDataQuery();

    /*!
     * @brief Fetch the overall revision, total count, all header items, and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     *
     * For more information about error handling, see the @c DataQuery class description. A return of
     * @c false by this method should be preceded by the query emitting an error signal. This signal
     * should be handled at the application level, leading to some appropriate action.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param[out] revision The current revision of the data source. This pointer must not be null.
     * @param[out] totalCount The total number of items in the view. This pointer must not be null.
     * @param[out] results The requested items. This pointer must not be null.
     * @param[out] headerResults The header items of the query. This pointer must not be null.
     *
     * @return @c True if the data is successfully retrieved, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getHeaderData(int offset, int limit, DataRevision *revision,
            int *totalCount, QList<DataItem> *results,
            QList<HeaderDataItem> *headerResults) = 0;

protected:
    /*! @cond PRIVATE */
    HeaderDataQuery(HeaderDataQueryPrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(HeaderDataQuery)
    Q_DISABLE_COPY(HeaderDataQuery)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_HEADERDATAQUERY_HPP_ */

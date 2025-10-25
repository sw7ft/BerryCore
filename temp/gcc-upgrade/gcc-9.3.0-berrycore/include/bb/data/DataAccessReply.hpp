/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */


#ifndef BB_DATA_DATAACCESSREPLY_HPP
#define BB_DATA_DATAACCESSREPLY_HPP

#include <bb/data/DataAccessErrorType>
#include <bb/Global>
#include <QDebug>
#include <QSharedDataPointer>
#include <QMetaType>
#include <QString>
#include <QVariant>


namespace bb {
namespace data {

class DataAccessReplyPrivate;

/*!
 * @headerfile DataAccessReply.hpp <bb/data/DataAccessReply>
 *
 * @brief The reply from an asynchronous data access operation.
 *
 * Returns the results for AsyncDataAccess and SqlConnection.
 * See @c SqlConnection for a complete example including the
 * processing of the reply data.
 *
 * This is a Qt value object which supports implicit data sharing.
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC DataAccessReply {
public:
    /*!
     * @brief Constructs an empty @c DataAccessReply object.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessReply();

    /*!
     * @brief Copy constructor.
     *
     * @param other The @c DataAccessReply object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessReply(const DataAccessReply& other);

    /*!
     * @brief Assignment constructor.
     *
     * @param other The @c DataAccessReply object to assign from.
     * @return The constructed @c DataAccessReply instance.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessReply& operator=(const DataAccessReply& other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~DataAccessReply();

    /*!
     * @brief Indicates whether the database operation that's associated
     * with this reply ended with an error.
     *
     * @return @c true if an error occurred, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasError() const;

    /*!
     * @brief Returns the error type for the error that's associated with
     * this reply.
     *
     * The error type indicates what kind of error occurred. An example
     * of an error type is @c DataAccessErrorType::SourceNotFound, which
     * indicates that the source database, URL, or file was not found.
     *
     * @return The error type, or @c DataAccessErrorType::None if this
     * reply doesn't include an error.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessErrorType::Type errorType() const;

    /*!
     * @brief Returns the detailed error message for the error that's
     * associated with this reply.
     *
     * @return The detailed error message or empty string if no error.
     *
     * @since BlackBerry 10.0.0
     */
    QString errorMessage() const;

    /*!
     * @brief Returns the result of the data access operation.
     *
     * This result will typically be a set of row data for load operations
     * or a row count for save operations. If there are errors,
     * then no result is expected.
     *
     * @return The result for data access operation or empty QVariant of errors.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant result() const;

    /*!
     * @brief Returns the ID of this reply data.
     *
     * This ID can be used in reply handling code to identify the execution
     * request that matches this reply data.
     *
     * @return The ID that was specified with the execute request.
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;

    /*!
     * @brief Sets the ID for this reply.
     *
     * @param id The new ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setId(int id);

    /*!
     * @brief Sets the error type and detailed error message for this reply.
     *
     * @param errorType The new error type.
     * @param errorMessage The new detailed error message.
     *
     * @since BlackBerry 10.0.0
     */
    void setError(DataAccessErrorType::Type errorType, const QString& errorMessage);

    /*!
     * @brief Sets the result for this reply.
     *
     * @param result The new result.
     *
     * @since BlackBerry 10.0.0
     */
    void setResult(const QVariant& result);

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<DataAccessReplyPrivate> d;
    /*! @endcond */
};

}
}

Q_DECLARE_METATYPE(bb::data::DataAccessReply)

namespace bb {
namespace data {
    BB_DLL_PUBLIC QDebug operator<<(QDebug dbg, const DataAccessReply& reply);
}
}

#endif // BB_DATA_DATAACCESSREPLY_HPP

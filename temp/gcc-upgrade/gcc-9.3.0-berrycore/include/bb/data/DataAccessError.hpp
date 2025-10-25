/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DATA_DATAACCESSERROR_HPP
#define BB_DATA_DATAACCESSERROR_HPP

#include <bb/data/DataAccessErrorType>
#include <bb/Global>
#include <QDebug>
#include <QMetaType>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace data {

class DataAccessErrorPrivate;

/*!
 * @headerfile DataAccessError.hpp <bb/data/DataAccessError>
 *
 * @brief Represents an error from a @c DataAccess load or save operation.
 *
 * The @c DataAccessError class includes a detailed error message and error type
 * that results from a @c %DataAccess load or save operation.
 *
 * This is a Qt value object that supports implicit data sharing.
 *
 * @see SqlDataAccess, JsonDataAccess
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC DataAccessError {
public:

    /*!
     * @brief Constructs an empty @ c DataAccessError.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessError();

    /*!
     * @brief Copy constructor.
     *
     * @param other The @c DataAccessError to copy.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessError(const DataAccessError& other);

    /*!
     * @brief Assignment constructor.
     *
     * @param other The @c DataAccessError to assign from.
     * @return The constructed @c DataAccessError instance.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessError& operator=(const DataAccessError& other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~DataAccessError();

    /*!
      * @brief Returns the error type for this error.
      *
      * The error type indicates what kind of error occurred. An example
      * of an error type is @c DataAccessErrorType::SourceNotFound, which
      * indicates that the source database, URL, or file was not found.
      *
      * @return The error type.
     *
     * @since BlackBerry 10.0.0
      */
    DataAccessErrorType::Type errorType() const;

    /*!
      * @brief Returns the detailed error message for this error.
      *
      * @return The detailed error message.
     *
     * @since BlackBerry 10.0.0
      */
    QString errorMessage() const;

    /*!
     * @brief Sets the error type and detailed error message for this error.
     *
     * @param errorType The new error type.
     * @param errorMessage The new detailed error message.
     *
     * @since BlackBerry 10.0.0
     */
    void setError(DataAccessErrorType::Type errorType, const QString& errorMessage);

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<DataAccessErrorPrivate> d;
    /*! @endcond */
};
}
}

Q_DECLARE_METATYPE(bb::data::DataAccessError)

namespace bb {
namespace data {
    BB_DLL_PUBLIC QDebug operator<<(QDebug dbg, const DataAccessError& error);
}
}

#endif // BB_DATA_DATAACCESSERROR_HPP


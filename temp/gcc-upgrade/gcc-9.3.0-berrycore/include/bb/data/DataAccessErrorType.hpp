/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */


#ifndef BB_DATA_ACCESSERRORTYPE_HPP
#define BB_DATA_ACCESSERRORTYPE_HPP

#include <bb/Global>
#include <QObject>

namespace bb {
namespace data {

/*!
 * @headerfile DataAccessErrorType.hpp <bb/data/DataAccessErrorType>
 *
 * @brief Represents types of data access errors.
 *
 * The @c DataAccessErrorType class enumerates the types of data access errors
 * that can occur during a data load or save operation.
 *
 * Classes which use this include @c DataAccessError and @c DataAccessReply.
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC DataAccessErrorType {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief Represents types of data access errors.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        None = 0,               ///< No error occurred.
        SourceNotFound = 1,     ///< The source url or file was not defined, was not found or (for databases) could not be created.
        ConnectionFailure = 2,  ///< An error occurred with a remote connection or connecting to an existing database.
        OperationFailure = 3    ///< An error occurred performing the data operation.
    };

private:
    /*! @cond PRIVATE */
    DataAccessErrorType();
    ~DataAccessErrorType();
    /*! @endcond */
};

}
}

#endif // BB_DATA_ACCESSERRORTYPE_HPP


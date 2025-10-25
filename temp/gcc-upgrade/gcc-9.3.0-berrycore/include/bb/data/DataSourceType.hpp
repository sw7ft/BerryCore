/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */


#ifndef BB_DATA_SOURCETYPE_HPP
#define BB_DATA_SOURCETYPE_HPP

#include <bb/Global>
#include <QObject>

namespace bb {
namespace data {

/*!
 * @headerfile DataSourceType.hpp <bb/data/DataSourceType>
 *
 * @brief Represents data types that you can use with a @c DataSource.
 *
 * The @c DataSourceType class enumerates the types of data that you can
 * load or save using a @c %DataSource.
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC DataSourceType {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief Represents the data source types.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        Unknown = 0, ///< Data source type is unknown.
        Sql = 1,     ///< Data source type is SQL database.
        Json = 2,    ///< Data source type is JSON data.
        Xml = 3      ///< Data source type is XML data.
    };

private:
    /*! @cond PRIVATE */
    DataSourceType();
    ~DataSourceType();
    /*! @endcond */
};

}
}

#endif // BB_DATA_SOURCETYPE_HPP

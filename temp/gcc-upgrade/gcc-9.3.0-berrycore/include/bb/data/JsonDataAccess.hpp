/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DATA_JSONDATAACCESS_HPP
#define BB_DATA_JSONDATAACCESS_HPP

#include <bb/data/DataAccessError>
#include <bb/Global>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QVariant>

namespace bb {
namespace data {

class JsonDataAccessPrivate;

/*!
 * @headerfile JsonDataAccess.hpp <bb/data/JsonDataAccess>
 *
 * @brief Provides load and save operations for JSON data.
 *
 * The @c JsonDataAccess class converts data from JSON format to
 * Qt C++ value objects or from Qt C++ value objects to JSON format.
 * You can use this class to provide JSON data to a @c ListView to
 * display the data in your application.
 *
 * Load operations read and parse JSON (JavaScript Object
 * Notation) data coming from a file or memory buffer into a tree
 * of Qt value objects. Save operations convert Qt value objects
 * into JSON format, which are written to a file or returned in a
 * memory buffer.
 *
 * The topmost (root) JSON element must be either an array or an
 * object. See http://www.json.org/ for the JSON format description.
 *
 * The Qt value data must always be a @c QVariant that contains
 * either a @c QVariantList or @c QVariantMap.
 *
 * Both formats support unlimited nesting of hierarchical data.
 *
 * The JSON element types are mapped to Qt values as follows:
 * <pre>
 *    JSON Type         Qt Type
 *    ---------         -----------------
 *    null              empty QVariant
 *    int               QVariant(Int64)
 *    uint              QVariant(UInt64)
 *    real              QVariant(double)
 *    string            QVariant(const char*)
 *    boolean           QVariant(bool)
 *    array             QVariant(QVariantList)
 *    object            QVariant(QVariantMap)
 * </pre>
 *
 * <h2>Loading data</h2>
 *
 * Here's an example of how to load JSON data from a file (called contacts.json)
 * and insert the data into a data model. The data model is then used to provide
 * data for a @c %ListView.
 *
 * The contacts.json file contains the following JSON data:
 * @code
 * [
 * { "id":1, "firstname": "Mike", "lastname": "Chepesky", "title": "Sr. Editor",
 *   "image": "images/data/mike_chepesky.png", "active": true, "gender": "m" },
 * { "id":2, "firstname": "Westlee", "lastname": "Barichak", "title": "Talent Scout",
 *   "image": "images/data/westlee_barichak.png", "active": true, "gender": "m" },
 * ...
 * ]
 * @endcode
 *
 * C++:
 * @snippet libbbdata/examples/JsonDataAccess/src/JsonDataAccessExamples.cpp loadjson1
 *
 * QML:
 * @snippet libbbdata/examples/JsonDataAccess/assets/JsonDataAccessExamples.qml loadjson1
 *
 * <h2>Unicode</h2>
 *
 * JSON data, in general, is encoded in Unicode. The default encoding is UTF-8
 * but external data in UTF-16 formats can also be loaded and parsed. The
 * various load and save methods in this class will indicate what assumptions
 * and restrictions they have regarding decoding and encoding.
 *
 * @see bb::cascades::DataModel, bb::cascades::ListView
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC JsonDataAccess : public QObject {
    Q_OBJECT

public:
    /*!
     * @brief Constructs a @c JsonDataAccess object with the specified parent.
     *
     * If the specified parent is not 0, the ownership of this object will be transferred to
     * the parent.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    JsonDataAccess(QObject* parent = 0);

    /*!
     * @brief Virtual destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~JsonDataAccess();

    /*!
     * @brief Returns an error object for the most recent operation.
     *
     * @return DataAccessError with error type and error message.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessError error() const;

    /*!
     * @brief Returns indication of whether or not most recent operation
     * ended with an error.
     *
     * @return true if current error or false if none.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasError() const;

    /*!
     * @brief Loads JSON data from specified file and returns it as a hierarchy of Qt
     * value objects.
     *
     * The data returned is a @c QVariant with a type that matches the type of the root
     * JSON object (see table of types in the class description of @c JsonDataAccess).
     * Unless the data is a single primitive JSON value, the returned data will be either
     * a @c QVariantList (if root JSON node is array) or a @c QVariantMap (if root JSON
     * node is an object), cast as a @c QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * The file data can be encoded as UTF-8 (with or without byte-order-mark) or as
     * UTF-16 (must have a byte-order-mark to indicate little endian or big endian).
     *
     * @param filePath The path to the JSON file.
     * @return A @c QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant load(const QString& filePath);

    /*!
     * @brief Loads JSON data from the specified I/O device and returns it as a hierarchy
     * of Qt value objects.
     *
     * An I/O device is used to read or write data from various sources. A @c QIODevice can
     * represent several useful types, including @c QBuffer and @c QFile.
     *
     * The data returned is a @c QVariant with a type that matches the type of the root
     * JSON object (see the table of types in the class description of @c JsonDataAccess).
     * Unless the data is a single primitive JSON value, the returned data will be either
     * a @c QVariantList (if the root JSON node is an array) or a @c QVariantMap (if root
     * JSON node is an object), cast as a @c %QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * The input data can be encoded as UTF-8 (with or without byte-order-mark) or as
     * UTF-16 (must have a byte-order-mark to indicate little endian or big endian).
     *
     * @param ioDevice The I/O device that is used to read and write data.
     *
     * @return A @c QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant load(QIODevice* ioDevice);

    /*!
     * @brief Parses the specified JSON byte array buffer and returns it as a hierarchy
     * of Qt value objects.
     *
     * The data returned is a @c QVariant with a type that matches the type of the root
     * JSON object (see the table of types in the class description of @c JsonDataAccess).
     * Unless the data is a single primitive JSON value, the returned data will be either
     * a @c QVariantList (if the root JSON node is an array) or a @c QVariantMap (if root
     * JSON node is an object), cast as a @c %QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param buffer An in-memory byte array containing JSON data encoded as UTF-8.
     *
     * @return A @c QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant loadFromBuffer(const QByteArray& buffer);

    /*!
     * @brief Parses the specified JSON string buffer and returns it as a hierarchy of
     * Qt value objects.
     *
     * The data returned is a @c QVariant with a type that matches the type of the root
     * JSON object (see the table of types in the class description of @c JsonDataAccess).
     * Unless the data is a single primitive JSON value, the returned data will be either
     * a @c QVariantList (if the root JSON node is an array) or a @c QVariantMap (if root
     * JSON node is an object), cast as a @c %QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param buffer An in-memory string containing JSON unicode data.
     *
     * @return A @c QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant loadFromBuffer(const QString& buffer);

    /*!
     * @brief Saves JSON data to the specified file.
     *
     * The @c data parameter is a @c QVariant (see the table of types in the class
     * description of @c JsonDataAccess). Unless the data is a single primitive JSON value,
     * the data should be either a @c QVariantList (if the root JSON node is an array) or
     * a @c QVariantMap (if root JSON node is an object), cast as a @c %QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param data The data to be converted to JSON format.
     * @param filePath The path to the JSON file to be written as UTF-8 (with no byte-order-mark).
     *
     * @since BlackBerry 10.0.0
     */
    void save(const QVariant& data, const QString& filePath);

    /*!
     * @brief Saves JSON data to the specified I/O device.
     *
     * The @c data parameter is a @c QVariant (see the table of types in the class
     * description of @c JsonDataAccess). Unless the data is a single primitive JSON value,
     * the data should be either a @c QVariantList (if the root JSON node is an array) or
     * a @c QVariantMap (if root JSON node is an object), cast as a @c %QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * An I/O device is used to read or write data from various sources. A @c QIODevice can
     * represent several useful types, including @c QBuffer and @c QFile.
     *
     * @param data The data to be converted to JSON format.
     * @param ioDevice The I/O device that is used to write JSON data as UTF-8 (no byte order mark).
     *
     * @since BlackBerry 10.0.0
     */
    void save(const QVariant& data, QIODevice* ioDevice);

    /*!
     * @brief Saves JSON data to the specified @c QByteArray buffer.
     *
     * The @c data parameter is a @c QVariant (see the table of types in the class
     * description of @c JsonDataAccess). Unless the data is a single primitive JSON value,
     * the data should be either a @c QVariantList (if the root JSON node is an array) or
     * a @c QVariantMap (if root JSON node is an object), cast as a @c %QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param data The data to be converted to JSON format.
     * @param buffer An output parameter that is updated with JSON-formatted data in UTF-8 format.
     *
     * @since BlackBerry 10.0.0
     */
    void saveToBuffer(const QVariant& data, QByteArray* buffer);

    /*!
     * @brief Saves JSON data to the specified @c QString buffer.
     *
     * The @c data parameter is a @c QVariant (see the table of types in the class
     * description of @c JsonDataAccess). Unless the data is a single primitive JSON value,
     * the data should be either a @c QVariantList (if the root JSON node is an array) or
     * a @c QVariantMap (if root JSON node is an object), cast as a @c %QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param data The data to be converted to JSON format.
     * @param buffer An output parameter that is updated with JSON-formatted Unicode data.
     *
     * @since BlackBerry 10.0.0
     */
    void saveToBuffer(const QVariant& data, QString* buffer);

protected:
    /*! @cond PRIVATE */
    JsonDataAccessPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(JsonDataAccess)
    Q_DISABLE_COPY(JsonDataAccess)
    /*! @endcond */
};

} // namespace bb::data
}

#endif /* BB_DATA_JSONDATAACCESS_HPP */

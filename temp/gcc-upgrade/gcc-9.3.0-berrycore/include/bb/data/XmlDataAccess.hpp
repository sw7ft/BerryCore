/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DATA_XMLDATAACCESS_HPP
#define BB_DATA_XMLDATAACCESS_HPP

#include <bb/data/DataAccessError>
#include <bb/Global>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QVariant>

namespace bb {
namespace data {

class XmlDataAccessPrivate;

/*!
 * @headerfile XmlDataAccess.hpp <bb/data/XmlDataAccess>
 *
 * @brief Converts data from XML format to Qt C++ value objects
 * or from Qt C++ value objects to XML format.
 *
 * Load operations read and parse XML (Extensible Markup Language)
 * data coming from a file or memory buffer into a tree of Qt value
 * objects. Save operations convert Qt value objects into XML format
 * which are written to a file or returned in a memory buffer.
 *
 * NOTE: Save-to-XML has serious limitations described at the end
 * of this documentation in "Saving Qt data as XML".
 *
 * Both XML and Qt support unlimited nesting of hierarchical data.
 *
 * <h2>XML terminology</h2>
 *
 * <h3>Markup and Content</h3>
 *
 * The characters which make up an XML document are divided into
 * markup and content. All strings which constitute markup either
 * begin with the character \< and end with a \>, or begin with the
 * character & and end with a ;. Strings of characters which are
 * not markup are content.
 *
 * <h3>Tag</h3>
 *
 * A tag is a markup construct that begins with \< and ends with \>. Tags come
 * in three flavors:
 * - start-tags: for example, <code>\<section\></code>
 * - end-tags: for example, <code>\</section\></code>
 * - empty-element tags: for example, <code>\<line-break /\></code>
 *
 * <h3>Element</h3>
 *
 * An element is a logical document component either begins with a start-tag and ends
 * with a matching end-tag or consists only of an empty-element tag.
 * The characters between the start- and end-tags, if any, are the
 * element's content, and may contain markup, including other elements,
 * which are called child elements. An example of an element is
 * <code>\<Greeting\>Hello, world.\</Greeting\></code> (see hello world). Another example is
 * <code>\<line-break /\></code>.
 *
 * <h3>Attribute</h3>
 *
 * An attribute is a markup construct consisting of a name/value pair that exists within
 * a start-tag or an empty-element tag. In the example below the element
 * img has two attributes, src and alt:
 *
 * <pre>
 * \<img src="madonna.jpg" alt='Foligno Madonna, by Raphael' /\>.
 * </pre>
 *
 * <h2>Loading XML Data in Qt</h2>
 *
 * The XML data generally consists of name-value pairs stored in a hierarchy.
 * In all cases, except for the root element, the name will be used as the key
 * for an entry in the parent's map. So, XML name-value data is stored like
 * this in Qt:
 *
 * <pre>
 * parentMap["name"] = value
 * </pre>
 *
 * The XML value data is mapped to Qt values as follows:
 *
 * <pre>
 *    XML Type                          Qt Value
 *    ---------                         -----------------
 *    parent element (*)                QVariant(QVariantMap)
 *    repeating element                 QVariant(QVariantList)
 *    element with no children          QVariant(QString)
 *    attribute                         QVariant(QString)
 * </pre>
 *
 * The (*) element is considered a parent if it has any attributes or child elements.
 * Also, @c QVariantMap is defined as a @c QMap<QString, QVariant> and
 * @c QVariantList is defined as a @c QList<QVariant>.
 *
 * Two special map entries:
 *
 * -# For the root element a special entry is added to the top-level Qt map to
 *    record the root element name:
 * <pre>
 * topMap[".root"] = "<root-element-name>"
 * </pre>
 * -# A parent element which has character data will have that data stored as
 *    a special entry in the parent map:
 * <pre>
 * parentMap[".data"] = "<character-data>"
 * </pre>
 *
 * Here is an example to make the translation from XML to Qt clearer:
 *
 * contacts.xml
*
 * @code
 * <contacts version="1.0">
 *     <contact>
 *         <id>1</id>
 *         <title>Sr. Editor</title>
 *         <firstname>Mike</firstname>
 *         <lastname>Chepesky</lastname>
 *     </contact>
 *     <contact>
 *         <id>2</id>
 *         <title>Talent Scout</title>
 *         <firstname>Westlee</firstname>
 *         <lastname>Barichak</lastname>
 *         <phonenumber>+465256467</phonenumber>
 *         <phonenumber>+464746734</phonenumber>
 *         some additional character data
 *     </contact>
 *     ...
 * </contacts>
 * @endcode
 *
 * Qt data structure for contacts:
 *
 * <pre>
 * A. QVariant(QVariantMap) contains:
 *    map[".root"]       = QVariant("contacts")
 *    map["version"]     = QVariant("1.0")
 *    map["contact"]     = QVariant(QVariantList)[see B]
 * B. QVariant(QVariantList) contains:
 *    [0] = QVariant(QVariantMap)                [see C]
 *    [1] = QVariant(QVariantMap)                [see D]
 *    [2] ...
 * C. QVariant(QVariantMap) contains:
 *    map["id"]          = QVariant("1")
 *    map["firstname"]   = QVariant("Mike")
 *    map["lastname"]    = QVariant("Chepesky")
 *    map["title"]       = QVariant("Sr. Editor")
 * D. QVariant(QVariantMap) contains:
 *    map[".data"]       = QVariant("some additional character data")
 *    map["id"]          = QVariant("2")
 *    map["firstname"]   = QVariant("Westlee")
 *    map["lastname"]    = QVariant("Barichak")
 *    map["title"]       = QVariant("Talent Scout")
 *    map["phonenumber"] = QVariant(QVariantList)[see E]
 * E. QVariant(QVariantList) contains:
 *    [0] = QVariant("+465256467")
 *    [1] = QVariant("+464746734")
 * </pre>
 *
 * <h2>Loading data in C++</h2>
 *
 * Here's an example that shows how to load data in C++:
 *
 * @snippet libbbdata/examples/XmlDataAccess/src/XmlDataAccessExamples.cpp loadxml1
 *
 * <h2>Loading data in QML</h2>
 *
 * Here's an example that shows how to load data in QML (note that DataSource is
 * used for data loading from QML and that XmlDataAccess is being used internally
 * by DataSource to perform the XML parsing here):
 *
 * @snippet libbbdata/examples/XmlDataAccess/assets/XmlDataAccessExamples.qml loadxml1
 *
 * <h2>Saving Qt data as XML</h2>
 *
 * Note that the save-to-XML support in this version has some serious
 * limitations since the XML output is well-formed (based on the rules
 * of XML markup) but it is not necessarily valid since it does not
 * conform to any schema definition. In particular the choice of
 * whether to output character data as an attribute (name="value") or
 * as an element (\<name\>value\</name\>) is not under the developer's
 * control and is based on some simple but arbitrary rules.
 *
 * Other limitations due to there being no schema include:
 *  - No data type constraints (number, date, etc.) for character data.
 *  - The order of elements and attributes will not be preserved.
 *      - The order will be alphabetical, not the original xml order.
 *      - The order of repeating elements (contacts in example above) will
 *        be preserved.
 *
 * This makes the saving of data in XML format suitable for use as
 * temporary private storage of structured data. It will NOT be suitable
 * for communicating with an external system which expects valid XML based
 * on a published schema.
 *
 * <h2>Attribute versus element rules</h2>
 *
 * The {name, value} data is output as an XML attribute (name="value") if:
 * - The parent XML node already has character data
 * - OR the name is an XML namespace declaration like "xmlns:atom"
 *
 * Otherwise, the data is output as an XML element (\<name\>value\</name\>). As an
 * example of the first point, the data will be written as:
 *
 * @code
 * <aaa name="value">more character data</aaa>
 * @endcode
 *
 * Rather than written as:
 * @code
 * <aaa>
 *     more character data
 *     <name>value</name>
 * </aaa>
 * @endcode
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
class BB_DLL_PUBLIC XmlDataAccess : public QObject {
    Q_OBJECT

public:
    /*!
     * @brief Constructs a XmlDataAccess object with a parent.
     *
     * If not 0, the ownership of this object will be transfered to the parent.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    XmlDataAccess(QObject* parent = 0);

    /*!
     * @brief Virtual destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~XmlDataAccess();

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
     * @brief Load the XML data from file and return it as a hierarchy of Qt value objects.
     *
     * The queryPath only supports simple hierarchical paths and not XPATH expressions.
     *
     * The returned data is either a QVariantList or a QVariantMap cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param filePath The path to the XML file.
     * @param queryPath Optional path to node for the subset of xml to return [defaults to root node].
     * @return A QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant load(const QString& filePath, const QString& queryPath="");

    /*!
     * @brief Load the XML data from I/O device and return it as a hierarchy of Qt value objects.
     *
     * The queryPath only supports simple hierarchical paths and not XPATH expressions.
     *
     * The returned data is either a QVariantList or a QVariantMap cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param ioDevice Used to read or write data. QIODevice can represent a number of useful
     * types including QBuffer and QFile.
     * @param queryPath Optional path to node for the subset of xml to return [defaults to root node].
     * @return A QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant load(QIODevice* ioDevice, const QString& queryPath="");

    /*!
     * @brief Parse the XML byte array buffer and return it as a hierarchy of Qt value objects.
     *
     * The queryPath only supports simple hierarchical paths and not XPATH expressions.
     *
     * The returned data is either a QVariantList or a QVariantMap cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param buffer An in-memory byte array containing XML data.
     * @param queryPath Optional path to node for the subset of xml to return [defaults to root node].
     * @return A QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant loadFromBuffer(const QByteArray& buffer, const QString& queryPath="");

    /*!
     * @brief Parse the XML string buffer and return it as a hierarchy of Qt value objects.
     *
     * The queryPath only supports simple hierarchical paths and not XPATH expressions.
     *
     * The returned data is either a QVariantList or a QVariantMap cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param buffer An in-memory string containing XML data.
     * @param queryPath Optional path to node for the subset of xml to return [defaults to root node].
     * @return A QVariant containing a hierarchy of Qt value objects.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant loadFromBuffer(const QString& buffer, const QString& queryPath="");

    /*!
     * @brief Save the XML data to the file.
     *
     * The data parameter is a QVariant. See table of types in this class. Unless
     * the data is a single primitive value it should be either a QVariantList
     * (representing an XML array) or a QVariantMap (representing an XML object)
     * cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param data to be converted to XML format and saved to file.
     * @param filePath The path to the XML file.
     *
     * @since BlackBerry 10.0.0
     */
    void save(const QVariant& data, const QString& filePath);

    /*!
     * @brief Save the XML data to the I/O device.
     *
     * The data parameter is a QVariant. See table of types in this class. Unless
     * the data is a single primitive value it should be either a QVariantList
     * (representing an XML array) or a QVariantMap (representing an XML object)
     * cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param data to be converted to XML format and saved to file.
     * @param ioDevice Used to read or write data. QIODevice can represent a number of useful
     * types including QBuffer and QFile.
     *
     * @since BlackBerry 10.0.0
     */
    void save(const QVariant& data, QIODevice* ioDevice);

    /*!
     * @brief Save the XML data to the buffer parameter.
     *
     * The data parameter is a QVariant. See table of types in this class. Unless
     * the data is a single primitive value it should be either a QVariantList
     * (representing an XML array) or a QVariantMap (representing an XML object)
     * cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param data to be converted to XML format and saved to buffer.
     * @param buffer output parameter which is updated with XML-formatted data.
     *
     * @since BlackBerry 10.0.0
     */
    void saveToBuffer(const QVariant& data, QByteArray* buffer);

    /*!
     * @brief Save the XML data to the buffer parameter.
     *
     * The data parameter is a QVariant. See table of types in this class. Unless
     * the data is a single primitive value it should be either a QVariantList
     * (representing an XML array) or a QVariantMap (representing an XML object)
     * cast as a QVariant.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param data to be converted to XML format and saved to buffer.
     * @param buffer output parameter which is updated with XML-formatted data.
     *
     * @since BlackBerry 10.0.0
     */
    void saveToBuffer(const QVariant& data, QString* buffer);

protected:
    /*! @cond PRIVATE */
    XmlDataAccessPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(XmlDataAccess)
    Q_DISABLE_COPY(XmlDataAccess)
    /*! @endcond */
};

} // namespace bb::data
}

#endif /* BB_DATA_XMLDATAACCESS_HPP */

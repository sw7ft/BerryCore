/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DATA_DATASOURCE_HPP
#define BB_DATA_DATASOURCE_HPP

#include <bb/data/DataAccessErrorType>
#include <bb/data/DataSourceType>
#include <bb/Global>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace data {

class DataSourcePrivate;

/*!
 * @headerfile DataSource.hpp <bb/data/DataSource>
 *
 * @brief Provides access to data from an external data source.
 *
 * The @c DataSource class lets you access data from a local data source,
 * such as a JSON file, XML file or SQL database. It can also be used to
 * access remote JSON or XML data using an HTTP data source URL. You can use
 * this class in C++ code as well as QML, but it is specifically intended
 * to make it easier to load data in QML.
 *
 * Internally, this class makes use of classes such as JsonDataAccess, SqlDataAccess,
 * XmlDataAccess and QNetworkAccessManager to perform the work.
 *
 * The properties @c #source, @c #query, @c #type and @c #remote will allow the location
 * and the type of data to be specified and whether the source is remote or
 * local.
 *
 * For example, to load data from an SQL table into a list using a @c DataSource
 * in QML, follow these steps:
 * -# Start with an application containing QML code that defines a @c ListView within
 *    a @c Page, as well as a @c GroupDataModel that's associated with the @c %ListView.
 * -# In the QML source file:
 *    -# Add an import statement: "import bb.data 1.0"
 *    -# Add a @c %DataSource below the definition of your data model as an
 *       attached object.
 *    -# Add code in @c DataSource.onDataLoaded to connect the @c %DataSource to the
 *       data model.
 *    -# Trigger loading by calling @c DataSource.load() from
 *       @c Page.onCreationCompleted().
 *    -# Specify the fields to display in the list items by adding binding code
 *       in the @c %ListView.
 *
 * Here is an example of the QML code required:
 *
 * @snippet libbbdata/examples/DataSource/assets/DataSourceExamples.qml qmlexample1
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC DataSource : public QObject {
    Q_OBJECT

    /*!
     * @brief The path to the external data source.
     *
     * In QML, this path is relative to the QML document in which this @c DataSource
     * is declared. When setting this property from C++, this path is instead relative
     * to the application working directory.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged FINAL)

    /*!
     * @brief The query property contains an SQL query statement or an XML path.
     *
     * An SQL select could be something like: "select * from contacts"
     *
     * An XML path will identify a path to the subset of XML data which is of
     * interest. Only simple hierarchical paths are supported and not XPATH expressions.
     * For example, performing a load operation using a path such as
     * "/contacts/contact" will return the repeating list of \<contact\> elements
     * in XML such as this:
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
     *     </contact>
     *     ...
     * </contacts>
     * @endcode
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged FINAL)

    /*!
     * @brief The type of data source.
     *
     * The value of this property is usually inferred from the #query property
     * or the format of the data content associated with #source.
     *
     * Note that for remote data the type cannot be determined from the data
     * content until the data is loaded.
     *
     * The type is Xml if the query property contains a query path such as
     * "/contacts/contact" or the query path is empty but the source data
     * is in XML format.
     *
     * The type is Sql if the query property contains an SQL select statement.
     *
     * The type is Json if the source data is in JSON format.
     *
     * Otherwise, the type will be "Unknown" unless it is set using this
     * property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::data::DataSourceType::Type type READ type WRITE setType NOTIFY typeChanged FINAL)

    /*!
     * @brief If true the data is at a remote source otherwise it is local.
     *
     * The value of this property can usually be inferred from the #source. If
     * the source url scheme is "http" then remote is assumed. If remote the data
     * is loaded using network access.
     *
     * Otherwise, the value for remote will be false unless it is set using
     * this property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool remote READ remote WRITE setRemote NOTIFY remoteChanged FINAL)

public:

    /*!
     * @brief Constructs a @c DataSource object with the specified parent.
     *
     * If the parent is not 0, ownership of this object will be transferred to the parent.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    DataSource(QObject *parent = 0);

    /*!
     * @brief Virtual destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~DataSource();

    /*!
     * @brief Deprecated.
     *
     * Registers @c DataSource and related classes for use in QML.
     *
     * @deprecated No longer needed as a QML plugin is used to do the registration instead.
     *
     * @since BlackBerry 10.0.0
     */
    static void registerQmlTypes();

    /*!
     * @brief Gets the current value of the #source property.
     *
     * @return The current path to the external data source.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl source() const;

    /*!
     * @brief Sets a new path to the external data source.
     *
     * @param source The new path of the external data source.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setSource(const QUrl& source);

    /*!
     * @brief Gets the current value of the #query property.
     *
     * The query can be an SQL select or XML path. For XML only simple
     * hierarchical paths are supported and not XPATH expressions.
     *
     * @return The query to use with this data source.
     *
     * @since BlackBerry 10.0.0
     */
    QString query() const;

    /*!
     * @brief Sets a new query to use with this data source.
     *
     * @param query The new SQL select or XML path to use. For XML only
     * simple hierarchical paths are supported and not XPATH expressions.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setQuery(const QString& query);

    /*!
     * @brief Gets the current value of the #type property.
     *
     * @return The type of data for the data source based on the
     * @c DataSourceType::Type enumeration.
     *
     * @since BlackBerry 10.0.0
     */
    bb::data::DataSourceType::Type type() const;

    /*!
     * @brief Sets a new type to use with this SQL data source.
     *
     * Typically, the type is inferred from other information and
     * does not need to be explicitly set when you use this class.
     * See the #type property above for the rules.
     *
     * @param type The data source type.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setType(bb::data::DataSourceType::Type type);

    /*!
     * @brief Gets the current value of the #remote property.
     *
     * @return True if the data source is remote and false if it is local.
     *
     * @since BlackBerry 10.0.0
     */
    bool remote() const;

    /*!
     * @brief Sets a new value for the #remote property.
     *
     * Normally the remote value is inferred from the source url and
     * does not need to be explicitly set by the user of this class. See
     * the #remote property above for the rules.
     *
     * @param remote True if the data source is remote and false if it is local.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setRemote(bool remote);

    /*!
     * @brief Loads the data from the data source.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void load();

    /*!
     * @brief Abort the current load operation if a network download is in progress.
     *
     * This will not abort synchronous load operations such as loading from a local file.
     * If a load operation is aborted an error signal will be omitted.
     */
    Q_SLOT void abort();

Q_SIGNALS:
    /*!
     * @brief Emitted when the #source property changes.
     *
     * @param source The new path of the external data source.
     *
     * @since BlackBerry 10.0.0
     */
    void sourceChanged(QUrl source);

    /*! @cond PRIVATE */
    /*!
     * @brief Emitted when the #query property changes.
     *
     * NOTE: Do not connect to this signal as it is no longer emitted.
     *       Connect to the signal below instead.
     *
     * @param query The new query to use.
     */
    void queryChanged(QUrl query) BB_DEPRECATED;
    /*! @endcond */

    /*!
     * @brief Emitted when the #query property changes.
     *
     * @param query The new query to use.
     */
    void queryChanged(QString query);

    /*!
     * @brief Emitted when the #type property changes.
     *
     * @note Due to a workaround for a Qt Core issue with accessing enumerations from QML,
     * the argument of this signal doesn't follow naming convention for signals, in
     * which the signal arguments are typically named to match the associated property's
     * name. To avoid runtime errors, use the object's property to access current
     * property value instead of the signal argument (use @c type instead of @c newType).
     *
     * @param newType The new type to use.
     *
     * @since BlackBerry 10.0.0
     */
    void typeChanged(bb::data::DataSourceType::Type newType);

    /*!
     * @brief Emitted when the #remote property changes.
     *
     * @param remote The new value for remote property.
     *
     * @since BlackBerry 10.0.0
     */
    void remoteChanged(bool remote);

    /*!
     * @brief Emitted when new data is loaded.
     *
     * Depending on the type of data and how it's loaded,
     * the @c data passed by this signal can be either a @c QVariantList or
     * a @c QVariantMap.
     *
     * For SQL data, this signal always passes a @c QVariantList containing
     * a @c QVariantMap for each item.
     *
     * For JSON data, this signal passes either a @c QVariantList or a
     * @c QVariantMap depending on the top-most JSON type used in the input data
     * (@c QVariantList if it's an array, and @c QVariantMap if it's an object).
     *
     * For XML data, this signal passes either a @c QVariantList or a
     * @c QVariantMap depending on how the data is loaded, and the amount of
     * data:
     * - If you @b don't specify a @c queryPath, the
     * @c data will be a @c QVariantMap representing the entire document.
     * - If you @b do specify a @c queryPath, and
     * the path refers to a @b non-repeating XML element, the @c data will be
     * a @c QVariantMap containing the single item.
     * - If you @b do specify a @c queryPath, and
     * the path refers to a @b repeating XML element, the @c data will be
     * a @c QVariantList (if the actual data contains more than one repetition)
     * or a @c QVariantMap (if the actual data contains only one repetitiion).
     *
     * @param data The new data that was loaded.
     *
     * @since BlackBerry 10.0.0
     */
    void dataLoaded(const QVariant& data);

    /*!
     * @brief Emitted when data failed to load and generated an error.
     *
     * @param errorType The type of error that was generated.
     * @param errorMessage The detailed error message.
     *
     * @since BlackBerry 10.0.0
     */
    void error(bb::data::DataAccessErrorType::Type errorType, const QString& errorMessage);

    /*! @cond PRIVATE */
    /*!
     * @brief Emitted when data failed to load and generated an error (workaround).
     *
     * This version contains an integer version of @c errorType to work around a bug
     * in Qt 4.8 (Q_ENUMS defined in another class cannot be accessed by QML
     * if it's a signal parameter). This will be fixed in Qt 5.0.
     *
     * @param errorType The type of error that was generated.
     * @param errorMessage The detailed error message.
     */
    void error(int errorType, const QString& errorMessage);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    DataSourcePrivate* const d_ptr;
    Q_DECLARE_PRIVATE(DataSource)
    Q_DISABLE_COPY(DataSource)
    /*! @endcond */
};
}
}

QML_DECLARE_TYPE(bb::data::DataSource)

#endif // BB_DATA_DATASOURCE_HPP

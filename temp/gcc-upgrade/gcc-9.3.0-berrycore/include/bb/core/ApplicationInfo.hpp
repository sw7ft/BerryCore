/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_APPLICATIONINFO_HPP
#define BB_CORE_APPLICATIONINFO_HPP

#include <bb/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

class ApplicationInfoPrivate;

/*!
 * @headerfile ApplicationInfo.hpp <bb/ApplicationInfo>
 *
 * @brief The @c %ApplicationInfo class provides access to application metadata available in the BAR manifest of the package containing the application.
 *
 * @details Applications are packaged in BAR packages that are deployed on the device.
 * The BAR package contains metadata that describes the application as well as the package itself.
 * This class provides access to metadata that describes the application.
 * For metadata related to the package itself, including the unique identifier for this application, use @c bb::PackageInfo.
 *
 * @xmlonly
 * <apigrouping group="Platform/Info"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT ApplicationInfo : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the token assigned by the signing authority for the application contained in the package.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString signingHash READ signingHash CONSTANT FINAL)

    /*!
     * @brief Represents the token from the signing authority for the version of the packaged application.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString versionSigningHash READ versionSigningHash CONSTANT FINAL)

    /*!
     * @brief Represents the title of the application contained in the package.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString title READ title CONSTANT FINAL)

    /*!
     * @brief Represents the version of the application contained in the package.
     * @details The value adheres to the format n.n.n.n when n is [0-65535] and 0.0.0.0 is considered an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString version READ version CONSTANT FINAL)

    /*!
     * @brief Represents the description of the application contained in the package.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString description READ description CONSTANT FINAL)

public:
    /*!
     * @brief Initializes a new instance of the @c ApplicationInfo class.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit ApplicationInfo(QObject* parent = 0);

    /*!
     * @brief Destroys this instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ApplicationInfo();

    /*!
     * @brief Retrieves the value for the @c signingHash property.
     * @return The @c signingHash value.
     *
     * @since BlackBerry 10.0.0
     */
    QString signingHash() const;

    /*!
     * @brief Retrieves the value for the @c versionSigningHash property.
     * @return The @c versionSigningHash value.
     *
     * @since BlackBerry 10.0.0
     */
    QString versionSigningHash() const;

    /*!
     * @brief Retrieves the value for the @c title property.
     * @return The @c title value.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Retrieves the value for the @c version property.
     * @return The @c version value.
     *
     * @since BlackBerry 10.0.0
     */
    QString version() const;

    /*!
     * @brief Retrieves the value for the @c description property.
     * @return The @c description value.
     *
     * @since BlackBerry 10.0.0
     */
    QString description() const;

private:
//!@cond PRIVATE
    QScopedPointer<ApplicationInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(ApplicationInfo)
    Q_DISABLE_COPY(ApplicationInfo)
//!@endcond
};

} // namespace bb

QML_DECLARE_TYPE(bb::ApplicationInfo)
#endif // BB_CORE_APPLICATIONINFO_HPP

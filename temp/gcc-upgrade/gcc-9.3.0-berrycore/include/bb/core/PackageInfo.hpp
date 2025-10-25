/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PACKAGEINFO_HPP
#define BB_CORE_PACKAGEINFO_HPP

#include <bb/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>
#include <QVariantList>
#include <QList>
#include <QLocale>

namespace bb
{

class PackageInfoPrivate;

/**
 * @brief Alias for @c QList<QLocale>.
 *
 * @since BlackBerry 10.0.0
 */
typedef QList<QLocale> PackageLocaleList;

/*!
 * @headerfile PackageInfo.hpp <bb/PackageInfo>
 *
 * @brief The @c %PackageInfo class provides access to metadata related to the package containing the application.
 *
 * @details Package metadata is available in the BlackBerry Archive (BAR) manifest of this application.
 * The BAR manifest contains attributes set by the developer and the signing server.
 *
 * All properties available through this class are read-only and constant.
 *
 * To get the unique identifier that represents the package, use @c installId().
 *
 * @c bb::ApplicationInfo provides metadata for the application itself.
 *
 * @xmlonly
 * <apigrouping group="Platform/Info"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT PackageInfo : public QObject
{
    Q_OBJECT

    /*!
     * @brief Represents the unique token used by the system to identify the package when it is installed.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString installId READ installId CONSTANT FINAL)

    /*!
     * @brief Represents the token assigned by the signing authority for the package.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString signingHash READ signingHash CONSTANT FINAL)

    /*!
     * @brief Represents the token assigned by the signing authority for the package's version.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString versionSigningHash READ versionSigningHash CONSTANT FINAL)

    /*!
     * @brief Represents the token assigned by the signing authority for the author of the package.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString authorSigningHash READ authorSigningHash CONSTANT FINAL)

    /*!
     * @brief Represents the version of the specification that the package adheres to.
     * @details The value adheres to the format n.n when n is [0-65535] and 0.0 is considered an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString compatibilityVersion READ compatibilityVersion CONSTANT FINAL)

    /*!
     * @brief Represents the name of the package.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString name READ name CONSTANT FINAL)

    /*!
     * @brief Represents the package version.
     * @details The value adheres to the format n.n.n.n when n is [0-65535] and 0.0.0.0 considered an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString version READ version CONSTANT FINAL)

    /*!
     * @brief Represents the package author.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString author READ author CONSTANT FINAL)

    /*!
     * @brief Represents the locales the package metadata are localized in.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariantList locales READ localesQml CONSTANT FINAL)

    /*!
     * @brief Represents the minimum OS version that the package requires.
     * @details The value adheres to the format n.n.n.n when n is [0-65535] and 0.0.0.0 considered an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString systemDependency READ systemDependency CONSTANT FINAL)

    /*!
     * @brief Represents the package description.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString description READ description CONSTANT FINAL)

public:
    /*!
     * @brief Initializes a new instance of the @c %PackageInfo class.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit PackageInfo(QObject* parent = 0);

    /*!
     * @brief Destroys this instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PackageInfo();

    /*!
     * @brief Retrieves the unique token that represents the package on the device.
     *
     * @return The unique identifier for this package. An empty @c QString is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString installId() const;

    /*!
     * @brief Retrieves the package signing hash.
     *
     * @details This is a token assigned by the signing server.
     * @return The package hash. An empty @c QString is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString signingHash() const;

    /*!
     * @brief Retrieves the package version signing hash.
     *
     * @details This is a token assigned by the signing server.
     * @return The package version hash. An empty @c QString is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString versionSigningHash() const;

    /*!
     * @brief Retrieves the package author signing hash.
     *
     * @details This is a token assigned by the signing server.
     * @return The package author hash. An empty @c QString is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString authorSigningHash() const;

    /*!
     * @brief Retrieves the version of the BAR specification that the package was created against.
     *
     * @details The value returned adheres to the format [0-65535].[0-65535].
     * @return The version of the BAR specification that the package adheres to. 0.0 is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString compatibilityVersion() const;

    /*!
     * @brief Retrieves the codename specified by the package author for the package.
     *
     * @return The package codename. An empty @c QString is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the version of the package.
     *
     * @details The value returned adheres to the format [0-65535].[0-65535].[0-65535].[0-65535].
     * @return The package version. 0.0.0.0 is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString version() const;

    /*!
     * @brief Retrieves the author of the package.
     *
     * @return The package author. An empty @c QString is an invalid value.
     *
     * @since BlackBerry 10.0.0
     */
    QString author() const;

    /*!
     * @brief Retrieves the list of locales for which metadata is available.
     *
     * @details The value returned is a @c QList of @c QLocale instances.
     * @return The package locales.
     *
     * @since BlackBerry 10.0.0
     */
    bb::PackageLocaleList locales() const;

    /*!
     * @brief Retrieves the minimum system version that this package requires.
     *
     * @details The value returned adheres to the format [0-65535].[0-65535].[0-65535].[0-65535].
     * @return The package system dependency if available, otherwise 0.0.0.0.
     *
     * @since BlackBerry 10.0.0
     */
    QString systemDependency() const;

    /*!
     * @brief Retrieves the description of the package set by the package author.
     *
     * @return The package description if available, otherwise an empty @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    QString description() const;

protected:
//!@cond PRIVATE
    /*!
     * @brief Workaround to make locales available in QML.
     *
     * @note This is only meant as a workaround. This method should not be used by C++ code.
     * Instead, see locales().
     */
    QVariantList localesQml() const;
//!@endcond
private:
//!@cond PRIVATE
    QScopedPointer<PackageInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(PackageInfo)
    Q_DISABLE_COPY(PackageInfo)
//!@endcond
};

} // namespace bb

QML_DECLARE_TYPE(bb::PackageInfo)
Q_DECLARE_METATYPE(bb::PackageLocaleList)

#endif // BB_CORE_PACKAGEINFO_HPP

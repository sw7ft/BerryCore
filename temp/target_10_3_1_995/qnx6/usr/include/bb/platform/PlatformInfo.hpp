/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 *
 */

#ifndef BB_PLATFORM_PLATFORMINFO_HPP
#define BB_PLATFORM_PLATFORMINFO_HPP

#include <bb/platform/Global>

#include <QObject>
#include <QString>
#include <QScopedPointer>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {

class PlatformInfoPrivate;

/*!
 * @headerfile PlatformInfo.hpp <bb/platform/PlatformInfo>
 *
 * @brief Allows access to information about the platform.
 *
 * @xmlonly
 * <apigrouping group="Platform/Info"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT PlatformInfo: public QObject {
    Q_OBJECT

    /*!
     * @brief Retrieves the OS version of the platform.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString osVersion READ osVersion CONSTANT FINAL )

public:
    /*!
     * @brief Create an instance of the @c PlatformInfo class.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit PlatformInfo( QObject * parent = 0 );

    /*!
     * @brief Destroy this instance of the @c PlatformInfo class.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PlatformInfo();

    /*!
     * @brief Retrieves the OS version of the platform.
     *
     * @note It is left to the caller to interpret the meaning of the OS version string.
     *
     * @return @c QString containing the version. If the version could not be ascertained then "0.0.0.0" is returned.
     *
     * @since BlackBerry 10.0.0
     */
    QString osVersion() const;

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(PlatformInfo)
    Q_DISABLE_COPY(PlatformInfo)
    QScopedPointer<PlatformInfoPrivate> d_ptr;
//!@endcond
};

 
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::PlatformInfo)
#endif // BB_PLATFORM_PLATFORMINFO_HPP

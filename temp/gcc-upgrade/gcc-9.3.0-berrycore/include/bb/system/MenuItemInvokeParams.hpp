/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_MENUITEMINVOKEPARAMS_HPP
#define BB_SYSTEM_MENUITEMINVOKEPARAMS_HPP

#include <bb/system/Global>
#include <bb/system/InvokeTarget>
#include <bb/system/FileTransferMode>

#include <QScopedPointer>
#include <QString>
#include <QUrl>
#include <QVariantMap>

namespace bb
{
namespace system
{

class MenuItemInvokeParamsPrivate;

/*!
 * @headerfile MenuItemInvokeParams.hpp <bb/system/MenuItemInvokeParams>
 *
 * @brief The parameters required to invoke an action related to a @c MenuItem.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT MenuItemInvokeParams
{
public:
    /*!
     * @brief Creates a new @c MenuItemInvokeParams object.
     *
     * @since BlackBerry 10.0.0
     */
    MenuItemInvokeParams();

    /*!
     * @brief Creates a copy of an existing @c MenuItemInvokeParams object.
     *
     * @param other The source @c MenuItemInvokeParams object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    MenuItemInvokeParams(const MenuItemInvokeParams &other);

    /*!
     * @brief Destroys this @c MenuItemInvokeParams object.
     *
     * @since BlackBerry 10.0.0
     */
    ~MenuItemInvokeParams();

    /*!
     * @brief Copies the data from an existing @c MenuItemInvokeParams object to this object.
     *
     * @param other The source @c MenuItemInvokeParams object to copy.
     *
     * @return The @c MenuItemInvokeParams instance.
     *
     * @since BlackBerry 10.0.0
     */
    MenuItemInvokeParams& operator=(const MenuItemInvokeParams &other);

    /*!
     * @brief Returns the type of the target.
     *
     * @return The kind of process represented by the target. The value returned is
     *         valid only if the instance is valid (see @c isValid()).  See
     *         @c bb::system::InvokeTarget::Type for the list of possible targets.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTarget::Type type() const;

    /*!
     * @brief Returns the identity of the target (as stated in its BAR manifest).
     *
     * @details Use this value with @c bb::system::InvokeRequest::setTarget().
     *
     * @return The identity of the target, or an empty string if this instance
     *         is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QString target() const;

    /*!
     * @brief Returns the action to be performed by the target of the invocation
     * request.
     *
     * @return The action to be performed by the target, or an empty string if this instance
     *         is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QString action() const;

    /*!
     * @brief Returns the MIME type of the data to be acted on.
     *
     * @return The MIME type of the data, or the empty string if this instance
     *         is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Returns the URI that references the data to be passed into the
     * invocation request.
     *
     * @details If the URI is not present, then it is
     * assumed that any required data is passed in-band in the
     * invocation request.
     *
     * @return The URI of the invocation data, or a default (invalid) @c QUrl
     *         if this instance is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QUrl uri() const;

    /*!
     * @brief Returns the URI pattern of the target's filter that matched the URI in the query
     *
     * @details The URI pattern can be used when additional information about the invocation
     * target is needed.
     *
     * @return The URI pattern that matched, or a default (invalid) @c QUrl
     *         if this instance is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.2.0
     */
    QUrl uriMatch() const;

    /*!
     * @brief Returns the file transfer mode that will be applied to the
     * invocation.
     *
     * @details The file transfer mode will be applied if the scheme of the URI is @c "file:///" and
     * the path references a file that is not in the shared area. Note that the third forward slash in @c %file:///
     * represents the file path.
     *
     * @return the file transfer mode that will be applied to the invocation.  See @c bb::system::FileTransferMode
     * for the list of transfer modes.
     *
     * @since BlackBerry 10.0.0
     *
     */
    bb::system::FileTransferMode::Type fileTransferMode() const;

    /*!
     * @brief Returns the data that is to be sent to the target upon
     * invocation.
     *
     * @return The data to send to the target, or an empty @c QByteArray
     *         if this instance is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray data() const;

    /*!
     * @brief Returns the metadata associated with the invocation.
     *
     * @details Metadata is optional and can be included to pass additional information
     * to the target. It will be encoded as a JSON object and sent to the target.
     *
     * @return The metadata.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap metadata() const;

    /*!
     * @brief Returns the perimeter in which the action will be
     * invoked.
     *
     * @return The perimeter in which the action will be invoked.  See @c bb::system::SecurityPerimeter::Type
     * for the list of perimeters.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SecurityPerimeter::Type perimeter() const;

    /*!
     * @brief Indicates if this object contains
     * valid invocation data.
     *
     * @return @c true if this object is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
//!@cond PRIVATE
    QScopedPointer<MenuItemInvokeParamsPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(MenuItemInvokeParams)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKETARGET_HPP

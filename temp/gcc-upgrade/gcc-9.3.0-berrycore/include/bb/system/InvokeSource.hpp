/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKESOURCE_HPP
#define BB_SYSTEM_INVOKESOURCE_HPP

#include <bb/system/Global>

#include <QScopedPointer>
#include <QString>

namespace bb
{
namespace system
{

class InvokeSourcePrivate;

/*!
 * @headerfile InvokeSource.hpp <bb/system/InvokeSource>
 *
 * @brief The @c InvokeSource class represents the entity making an invocation request on a target.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeSource
{
public:

    /*!
     * @brief Creates a new @c InvokeSource object.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeSource();

    /*!
     * @brief Creates a copy of an existing @c InvokeSource object.
     *
     * @param other The source @c InvokeSource object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeSource(const InvokeSource &other);

    /*!
     * @brief Destroys this @c InvokeSource object.
     *
     * @since BlackBerry 10.0.0
     */
    ~InvokeSource();

    /*!
     * @brief Copies the data of an existing @c InvokeSource object to this object.
     *
     * @param other The source @c InvokeSource object to copy.
     *
     * @return The @c InvokeSource instance.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeSource& operator=(const InvokeSource &other);

    /*!
     * @brief Returns the primary group ID of the process making the invocation request.
     *
     * @return The group ID of the source process.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int groupId() const;

    /*!
     * @brief Returns the install ID assigned to the process making the request.
     *
     * @return The install ID of the source process.
     *
     * @since BlackBerry 10.0.0
     */
    QString installId() const;

private:
//!@cond PRIVATE
    QScopedPointer<InvokeSourcePrivate> const d_ptr;
    Q_DECLARE_PRIVATE(InvokeSource)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKESOURCE_HPP

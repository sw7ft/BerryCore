/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_STRINGVALIDATOR_HPP
#define BB_UTILITY_STRINGVALIDATOR_HPP

#include <bb/utility/Global>

#include <QObject>
#include <QScopedPointer>
#include <QStringList>

namespace bb
{
namespace utility
{

class StringValidatorPrivate;

/*!
 * @headerfile StringValidator.hpp <bb/utility/StringValidator>
 *
 * @brief Provides validation functions on supplied text.
 *
 * @details The @c %StringValidator class provides helper functions that can be
 * used to determine if a text string conforms to a specified format, or contains
 * a particular pattern or style. For example, you can determine whether a
 * string appears to be an email address.
 *
 * @xmlonly
 * <apigrouping group="Platform/Language"/>
 * <library name="bbutility"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.1.0
 */
class BB_UTILITY_EXPORT StringValidator : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Creates a new instance of the @c %StringValidator class.
     *
     * @param parent The parent of the instance.
     *
     * @since BlackBerry 10.1.0
     */
    explicit StringValidator(QObject *parent = 0);
    
    /*!
     * @brief Destroys this @c %StringValidator instance.
     *
     * @since BlackBerry 10.1.0
     */
    virtual ~StringValidator();

    /*!
     * @brief Determines if the specified text appears to be an email address.
     * 
     * @note This function uses RFC3522 as a guide for rules on validating an
     * email address.
     *
     * @param text The text to examine to determine if it could be an email address.
     *
     * @return @c true if the specified text seems to be an email address, @c false
     * otherwise.
     *
     * @since BlackBerry 10.1.0
     */
    Q_INVOKABLE static bool isEmailAddress( const QString &text );

private:
    Q_DISABLE_COPY(StringValidator)
    Q_DECLARE_PRIVATE(StringValidator)
    QScopedPointer<StringValidatorPrivate> d_ptr;
};

} // namespace utility
} // namespace bb

#endif // BB_UTILITY_STRINGVALIDATOR_HPP

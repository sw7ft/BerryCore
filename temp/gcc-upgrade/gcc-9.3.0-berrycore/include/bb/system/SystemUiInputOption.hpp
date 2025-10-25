/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIINPUTOPTINS_HPP
#define BB_SYSTEM_SYSTEMUIINPUTOPTINS_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiInputOption.hpp <bb/system/SystemUiInputOption>
 *
 * @brief A set of options for controlling text input in a @c SystemUiInputField.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT SystemUiInputOption
{
	Q_GADGET
	Q_ENUMS (Type);
	Q_FLAGS (Types);

public:

	/*!
     * @brief The options used to apply to the text entered in the input field.
     *
     * @since BlackBerry 10.2.0
     */
	enum Type {

		/*!
		 * @brief No options (default mode).
		 *
		 * @since BlackBerry 10.2.0
		 */
		None 			= 0x0,

		/*!
		 * @brief The first letter of a sentence is auto-capitalized.
		 *
		 * @since BlackBerry 10.2.0
		 */
		AutoCapitalize 	= 0x1,

		/*!
		 * @brief The input will be corrected automatically.
		 *
		 * @since BlackBerry 10.2.0
		 */
		AutoCorrect 	= 0x2,

		/*!
		 * @brief The input is checked for spelling errors.
		 *
		 * @since BlackBerry 10.2.0
		 */
		SpellCheck 		= 0x4
	};

	Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVATE
	SystemUiInputOption();
	~SystemUiInputOption();
//!@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SystemUiInputOption::Types)

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiInputOption)
#endif //BB_SYSTEM_SYSTEMUIINPUTOPTINS_HPP

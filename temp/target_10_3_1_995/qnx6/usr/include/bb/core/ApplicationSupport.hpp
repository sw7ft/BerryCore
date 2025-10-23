/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_APPLICATIONSUPPORT_HPP
#define BB_CORE_APPLICATIONSUPPORT_HPP

#include <bb/Global>

#include <QObject>
#include <QScopedPointer>

namespace bb
{

class ApplicationSupportPrivate;

/*!
 * @headerfile ApplicationSupport.hpp <bb/ApplicationSupport>
 *
 * @brief The @c %ApplicationSupport class encapsulates functionality from the @c Application class for
 * situations in which that class cannot be used.
 * 
 * @details The @c %ApplicationSupport class can be used by any application that uses the @c QApplication class,
 * which precludes the use of the @c %Application class. These applications may still find it
 * useful to have the following functionality available, so it is exposed in the @c %ApplicationSupport class as well.
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT ApplicationSupport : public QObject
{
    Q_OBJECT

public:

    /*!
     * @brief Create a new @c %ApplicationSupport object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit ApplicationSupport(QObject *parent = 0);

    /*!
     * @brief Destroys this @c %ApplicationSupport object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~ApplicationSupport();

    /*!
     * @brief Sets a prompt to appear when the user attempts to close the application.
     *
     * @details This function allows an application to prevent the user from closing the
     * application without warning. If the user tries to close the application, a dialog box
     * is displayed with the title and message specified. The dialog box will have 2 buttons:
     * "Cancel" and "Close". If the user selects "Close", the application will be closed.
     * If the user selects "Cancel", the dialog box will close and the application will continue running.
     *
     * Note that the save prompt for an application is stored persistently on the device. The last
     * call to this method or @c Application::setClosePrompt() determines the close prompt that will
     * be shown. The close prompt persists until @c clearClosePrompt() is called on the
     * @c %ApplicationSupport class or on any @c %Application object. Destroying the object that
     * set the close prompt does not clear the prompt.
     *
     * Note that all commas and double quotes are stripped from the title and message parameters
     * before they are displayed. These characters cannot be displayed correctly. If the
     * text also includes backslash characters ('\'), this process can introduce unexpected
     * white space characters like tabs ('\\t') and newlines ('\\n'). Since these whitespace
     * characters are allowed in the dialog box, they cannot be stripped.
     *
     * Escape characters can be used, but they may be awkward to specify. The string provided
     * to this method is in turn forwarded to the device's home screen process, which interprets
     * the string a second time, including any escape characters. This can require multiple
     * levels of escaping to produce the desired effect. For instance, to add a backslash ('\')
     * character to the close prompt, the string "\\\\" must be used. This provides the string
     * "\\" to this object. When this string is forwarded to the home screen, "\\" is interpreted
     * again to become '\'.
     *
     * @param title The title of the close prompt dialog box. This title replaces the current
     * close prompt title if it is already set.
     * @param message The message of the close prompt dialog box. This message replaces the
     * current close prompt message if it is already set.
     *
     * @return @c true if the close prompt was set, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    static bool setClosePrompt(const QString &title, const QString &message);
 
    /*!
     * @brief Clears the current close prompt.
     *
     * @details This function removes any close prompt that was set, regardless of whether it was set
     * using the @c setClosePrompt() method in the @c %ApplicationSupport class or in the
     * @c Application class. When the close prompt is cleared, no close prompt dialog box will
     * appear when the user tries to close the application, and the application will exit
     * normally.
     * 
     * If there is no current close prompt, this method has no effect.
     *
     * @return @c true if the close prompt was cleared, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    static bool clearClosePrompt();

private:
//!@cond PRIVATE
    QScopedPointer<ApplicationSupportPrivate> d_ptr;
    Q_DECLARE_PRIVATE(ApplicationSupport);
    Q_DISABLE_COPY(ApplicationSupport);
//!@endcond
};

} // namespace bb

#endif // BB_CORE_APPLICATIONSUPPORT_HPP

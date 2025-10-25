/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_CONTACT_HPP
#define BB_PLATFORM_BBM_CONTACT_HPP

#include <bb/platform/bbm/Global>
#include <bb/platform/bbm/UserStatus>

#include <QString>
#include <QSharedDataPointer>


namespace bb
{
namespace platform
{
namespace bbm
{

class ContactPrivate;


/*!
 * @headerfile Contact.hpp <bb/platform/bbm/Contact>
 *
 * @brief Represents a contact on the BBM Social Platform.
 *
 * @details Provides access to information about a specific BBM contact, such as
 * display name, status, or personal message, as well as the versions of the
 * BBM Social Platform, BBM version and the app that are running on the
 * contact's device. To access this information the application has to have
 * access allowed and the contact list has to been initialized and is valid.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 *
 */
class BB_PLATFORM_BBM_EXPORT Contact
{

public:

    /*!
     * @brief Creates a new @c Contact object.
     * @since BlackBerry 10.0.0
     */
    Contact();

    /*!
     * @ brief Copy constructor.
     *
     * @param contact The existing @c Contact object to copy.
     * @since BlackBerry 10.0.0
     */
    Contact(const Contact &contact);

    /**
     * Assignment operator
     *
     * @param contact The existing @c Contact object to copy.
     *
     * @return The @c Contact instance.
     * @since BlackBerry 10.0.0
     */
    Contact& operator=(const Contact &contact);

    /*!
     * @brief Destroys this @c Contact object.
     * @since BlackBerry 10.0.0
     */
    ~Contact();


    /*!
     * @brief Retrieves the version of your app that is running on a contact's
     * device.
     *
     * @return The version of the app that a contact is running.
     * @since BlackBerry 10.0.0
     */
    QString applicationVersion() const;

    /*!@cond PRIVATE
     * @brief Deprecated
     * @deprecated This method is deprecated. Do not use.
     * @see Contact::platformVersion()
     * @since BlackBerry 10.0.0
     */
    BB_PLATFORM_BBM_DEPRECATED int sdkVersion() const;
    //!@endcond PRIVATE

    /*!
     * @brief Retrieves the version of the BBM Social Platform that is running
     * on a contact's device.
     * @details The possible versions are:
     *    100 - the first release of the BBM Social Platform for BlackBerry
     *    10. Release date: January, 2013. Also, the first release of the BBM
     *    Social Platform for BlackBerry Device Software version 5,
     *    BlackBerry 6, and BlackBerry 7. Release date: October, 2011.
     *
     *    120 - release for BlackBerry Device Software version 5,
     *    BlackBerry 6, and BlackBerry 7. Release date: November, 2011.
     *
     *    130 - release for BlackBerry Device Software version 5, BlackBerry
     *    6, and BlackBerry 7. Release date: February, 2012.
     *
     * @return The version of the BBM Social Platform that is running on the
     * contact's device.
     * @since BlackBerry 10.0.0
     */
    int platformVersion() const;

    /*!
     * @brief Retrieve the version of BBM that is running on a contact's device.
     * @details Possible BBM versions are:
     * <ul>
     *    <li>0x0100 for BBM version 1.0 on devices running BlackBerry Device Software 5.0 or earlier</li>
     *    <li>0x0200 for BBM version 2.0 on devices running BlackBerry Device Software 5.0 or earlier</li>
     *    <li>0x0201 for BBM version 2.1 on devices running BlackBerry Device Software 5.0 or earlier</li>
     *    <li>0x0202 for BBM version 2.2 on devices running BlackBerry Device Software 5.0 or earlier</li>
     *    <li>0x0205 for BBM version 2.5 on devices running BlackBerry Device Software 5.0 or earlier</li>
     *    <li>0x0206 for BBM version 2.6 on devices running BlackBerry Device Software 5.0 or earlier</li>
     *    <li>0x0600 for BBM version 6.0 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
     *    <li>0x0601 for BBM version 6.1 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
     *    <li>0x0700 for BBM version 7.0 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
     *    <li>0x0a00 for BBM version 10.0 on devices running BlackBerry 10</li>
     *    <li>0x00 for unknown version</li>
     * </ul>
     *
     * @return int The version of BBM that is running on the contact's device. If the
     * version is not known, returns 0.
     * @since BlackBerry 10.2.0
     */
    int bbmVersion() const;

    /*!
     * @brief Retrieves the contact's BBM display name.
     * @return The contact's BBM display name.
     * @since BlackBerry 10.0.0
     */
  QString displayName() const;

    /*!
     * @brief Retrieves the contact's BBM personal message.
     * @return The contact's BBM personal message.
     * @since BlackBerry 10.0.0
     */
  QString personalMessage() const;

    /*!
     * @brief Retrieves the contact's BBM user status.
     * @return The contact's BBM user status.
     * @since BlackBerry 10.0.0
     */
  bb::platform::bbm::UserStatus::Type status() const;

    /*!
     * @brief Retrieves the contact's BBM status message.
     * @return The contact's BBM status message.
     * @since BlackBerry 10.0.0
     */
  QString statusMessage() const;

    /*!
     * @brief Retrieves the contact's @c ppId.
     *
     * The contact's @c ppId is the same across multiple instances of BBM (for
     * example, on a BlackBerry smartphone and a BlackBerry tablet), when the
     * user signs in with the same BlackBerry ID.
     *
     * @return The contact's @c ppId.
     * @since BlackBerry 10.0.0
     */
  QString ppId() const;

    /*!
     * @brief Retrieves the contact's @c handle.
     *
     * The @c handle is an identifier for a user on the BBM Social Platform
     * whose device is running BlackBerry 7 or earlier. It is provided for
     * backwards compatibility and should NOT be used as a persistent identifier
     * for a user. Use the @c ppId instead.
     *
     * The contact's @c handle is the same for each instance of BBM (for
     * example, on a BlackBerry smartphone and a BlackBerry tablet).
     *
     * @return The contact's @c handle.
     * @since BlackBerry 10.0.0
     */
  QString handle() const;


private:
    QSharedDataPointer<ContactPrivate> d_ptr;
    friend class ContactPrivate;
};

} /* namespace bbm */
} /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_CONTACT_HPP */

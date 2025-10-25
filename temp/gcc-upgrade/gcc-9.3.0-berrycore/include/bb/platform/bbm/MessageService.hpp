/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_MESSAGESERVICE_HPP
#define BB_PLATFORM_BBM_MESSAGESERVICE_HPP

#include <bb/platform/bbm/Global>
#include <bb/platform/bbm/Contact>

#include <QObject>
#include <QList>
#include <QScopedPointer>

namespace bb
{
namespace platform
{
namespace bbm
{

class MessageServicePrivate;

class Context;

/*!
 * @headerfile MessageService.hpp <bb/platform/bbm/MessageService>
 *
 * @brief Represents a class that provides a message service for the BBM Social Platform.
 *
 * @details MessageService is a class that provides access to message related services, such as download
 * invitations.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT MessageService : public QObject
{
    Q_OBJECT
public:
    /*!
     * @brief Creates a new MessageService object.
     *
     * @param context The @c Context object that provides access to the @c ContactsService. 
     * All contacts related to this service will be populated in this list. A @c Context object with
     * @c RegistrationState::Allowed is necessary for creation of the MessageService object.
     * @param parent The QObject parent of this MessageService object.
     * @since BlackBerry 10.0.0
     */
    MessageService(Context *context, QObject *parent = 0);

    /*!
     * @brief Destroys this MessageService object.
     * @since BlackBerry 10.0.0
     */
  virtual ~MessageService();


    /*!
     * @brief Invites BBM contacts of the current user to download your app.
     *
     * @details The Contact Picker will pop up to allow the user to select the contacts to invite.
     * Only the contacts who do not have the application installed will be displayed in the Contact Picker.
     *
     * @return true if successful, false otherwise.
     * @since BlackBerry 10.0.0
     */
  bool sendDownloadInvitation() const;

private:
    Q_DECLARE_PRIVATE(MessageService)
    Q_DISABLE_COPY(MessageService)
    QScopedPointer<MessageServicePrivate> d_ptr;


};

} /* namespace bbm */
} /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_MESSAGESERVICE_HPP */

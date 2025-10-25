/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_CONTACTSERVICE_HPP
#define BB_PLATFORM_BBM_CONTACTSERVICE_HPP

#include <bb/platform/bbm/Global>
#include <bb/platform/bbm/ImageType>

#include <QObject>
#include <QList>
#include <QScopedPointer>
#include <QString>

namespace bb
{
  namespace platform
  {
    namespace bbm
    {
      class Context;
      class Contact;
      class ContactServicePrivate;

      /*!
       * @headerfile ContactService.hpp <bb/platform/bbm/ContactService>
       *
       * @brief Provides services related to a user's BBM contacts.
       * @details Provides access to a user's BBM contact list. For example, you can retrieve
       * a list of all the contacts who have your app installed, compare contacts, or determine
       * the total number of contacts in the list. It also provides signals for changes
       * to the contact list.
       *
       * @since BlackBerry 10.0.0
       *
       * @xmlonly
       * <apigrouping group="App Integration/BBM"/>
       * library name="bbplatformbbm"/>
       * @endxmlonly
       */
      class  BB_PLATFORM_BBM_EXPORT ContactService: public QObject
      {
        Q_OBJECT
      public:
        /*!
         * @brief Creates a new @c ContactService object with the @c Context as the basis.
         *
         * @param context The basis for the @c ContactService object.
         * All contacts related to the application @c Context object will be populated in this list.
         * @param parent The @c QObject parent of this @c ContactService object.
         * @since BlackBerry 10.0.0
         */
        explicit ContactService(Context *context, QObject *parent = 0);


        /*!
         * @brief Destroys this @c ContactService object.
         * @since BlackBerry 10.0.0
         */
        virtual ~ContactService();

        /*!
         * @brief Checks whether the contact list has been initialized and is valid.
         *
         * @return true if the contact list has been initialized and is valid, false otherwise.
         * @since BlackBerry 10.0.0
         */
        bool isValid() const;

        /*!
         * @brief Checks whether the contact list already contains a contact with the same
         * handle as the specified contact.
         *
         * @param contact The contact to compare to.
         *
         * @return true if the contact exists, false otherwise.
         * @since BlackBerry 10.0.0
         */
        bool containsContact(const Contact &contact) const;

        /*!
         * @brief Retrieves the contact with the specified handle.
         *
         * @param handle The contact's handle.
         *
         * @return The contact associated with specified handle, empty @c Contact otherwise.
         * @since BlackBerry 10.0.0
         */
        Contact contact(const QString &handle) const;

        /*!
         * @brief Returns all the contacts that have your app installed.
         *
         * @return A @c QList<Contact> that contains the list of contacts.
         * @since BlackBerry 10.0.0
         */
        QList<Contact> contacts() const;

        /*!
         * @brief Returns the total number of contacts in this contact list.
         *
         * @return The count of contacts associated with the service.
         * @since BlackBerry 10.0.0
         */
        int contactCount() const;

        /*!
         * @brief Requests the display picture for the contact with the specified @c handle.
         * @details The signal @c displayPictureUpdated is emitted as an asynchronous response.
         *
         * @param handle The contact's handle.
         *
         * @return true if sending the request succeeds, false otherwise.
         * @since BlackBerry 10.0.0
         */
        bool requestDisplayPicture(const QString &handle) const;


        Q_SIGNALS:
        /*!
         * @brief Emitted when the @c ContactsService populates a contactlist, and the list data
         * has been updated. The @c ContactsService retrieves the contact list asynchronously.
         *
         * @since BlackBerry 10.0.0
         */
        void contactListUpdated();

        /*!
         * @brief Emitted when a contact's display picture is changed.
         *
         * @param handle The handle of the contact whose display picture changed.
         * @param imageType The MIME type of the new display picture. If an
         * invalid MIME type is provided by this contact, the behavior of
         * this method is undefined.
         * @param displayPicture The new display picture data.
         * @since BlackBerry 10.0.0
         */
        void displayPictureUpdated(const QString &handle, const bb::platform::bbm::ImageType::Type imageType, const QByteArray &displayPicture);

        /*!
         * @brief Emitted when a contact has been updated.
         * @param handle The handle of the contact that was updated.
         * @since BlackBerry 10.0.0
         */
        void contactUpdated(const QString &handle);

        /*!
         * @brief Emitted when a contact installs or unblocks the same application as that running on
         * the user's device. This notification is sent only if the same app is running on both the
         * user's and contact's devices. It cannot be sent across different BBM connected
         * applications.
         *
         * @param handle The handle of the contact who installed or unblocked the application.
         * @since BlackBerry 10.0.0
         */
        void applicationEnabled(const QString &handle);

        /*!
         * @brief Emitted when a contact uninstalls or blocks the same application as that running on
         * the user's device. This notification is sent only if the same app is running on both the
         * user's and contact's devices. It cannot be sent across different BBM connected
         * applications.
         *
         * @param handle The handle of the contact who uninstalled or blocked the application.
         * @since BlackBerry 10.0.0
         */
        void applicationDisabled(const QString &handle);


      private:
        Q_DECLARE_PRIVATE(ContactService)
        Q_DISABLE_COPY(ContactService)
        QScopedPointer<ContactServicePrivate> d_ptr;
      };

    } /* namespace bbm */
  } /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_CONTACTSERVICE_HPP */

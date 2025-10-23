
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_CALENDARFOLDER_HPP
#define BB_PIM_CALENDAR_CALENDARFOLDER_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class CalendarFolderPrivate;

/*!
 * @brief The @c CalendarFolder class represents a distinct calendar in the Calendar application.
 *
 * @details Calendar folders are containers for events. A calendar in the Calendar application is
 * represented by a @c %CalendarFolder object. This object includes information about the calendar,
 * including name, type, owner email address, and color.
 * 
 * When you create a @c CalendarEvent, you can specify the folder that you want to add the event to.
 * You can update an existing @c %CalendarFolder in the database by calling
 * @c CalendarService::updateFolder().
 * 
 * @see CalendarEvent, CalendarService
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT CalendarFolder {
public:

    /*!
     * @brief Constructs a new @c CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarFolder();

    /*!
     * @brief Destroys this @c CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    ~CalendarFolder();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c CalendarFolder containing exactly the
     * same values as the provided @c %CalendarFolder.
     *
     * @param other The @c %CalendarFolder to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarFolder(const CalendarFolder& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CalendarFolder
     * into this @c %CalendarFolder.
     *
     * @param other The @c %CalendarFolder from which to copy all values.
     *
     * @return A reference to this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    CalendarFolder& operator=(const CalendarFolder& other);

    /*!
     * @brief Retrieves the name of this @c CalendarFolder.
     *
     * @return The name of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the email address of the owner of this @c CalendarFolder.
     *
     * @return The email address of the owner of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    QString ownerEmail() const;

    /*!
     * @brief Retrieves the synchronization ID of this @c CalendarFolder.
     *
     * @details The synchronization ID is a token that's used for synchronization with
     * remote servers.
     *
     * @return The synchronization ID of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    QString syncId() const;

    /*!
     * @brief Retrieves the provider data for this @c CalendarFolder.
     *
     * @details The provider data is used for synchronization with remote servers.
     *
     * @return The provider data for this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    QString providerData() const;

    /*!
     * @brief Retrieves the account ID of this @c CalendarFolder.
     *
     * @return The account ID of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    AccountId accountId() const;

    /*!
     * @brief Retrieves the database ID of this @c CalendarFolder.
     *
     * @return The database ID of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    FolderId id() const;

    /*!
     * @brief Retrieves the parent folder ID of this @c CalendarFolder.
     *
     * @details This function returns the ID of this folder's parent folder (that is,
     * the folder that contains this folder).
     *
     * @return The parent folder ID of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    FolderId parentId() const;

    /*!
     * @brief Retrieves the color of this @c CalendarFolder.
     *
     * @details This function returns this folder's color, encoded as a 24-bit RGB
     * value.
     *
     * @return The color of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int color() const;

    /*!
     * @brief Retrieves the type of this @c CalendarFolder.
     *
     * @details The two possible values for the type of a calendar folder are 8 (default
     * calendar) and 13 (user calendar).
     *
     * @return The type of this @c %CalendarFolder.
     *
     * @since BlackBerry 10.0.0
     */
    int type() const;

    /*!
     * @brief Indicates whether this @c CalendarFolder is read-only.
     *
     * @return @c true if this @c %CalendarFolder is read-only, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isReadOnly() const;

    /*!
     * @brief Indicates whether this @c CalendarFolder has been marked as visible in 
     * the Calendar application.
     *
     * @return @c true if this @c %CalendarFolder has been marked as visible in the
     * Calendar application, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isVisible() const;


    /*!
     * @brief Sets the name of this @c CalendarFolder.
     *
     * @param name The new name.
     *
     * @since BlackBerry 10.0.0
     */
    void setName(const QString& name);

    /*!
     * @brief Sets the email address of the owner of this @c CalendarFolder.
     *
     * @param ownerEmail The new owner email address.
     *
     * @since BlackBerry 10.0.0
     */
    void setOwnerEmail(const QString& ownerEmail);

    /*!
     * @brief Sets the synchronization ID of this @c CalendarFolder.
     *
     * @param syncId The new synchronization ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setSyncId(const QString& syncId);

    /*!
     * @brief Sets the provider data for this @c CalendarFolder.
     *
     * @param providerData The new provider data.
     *
     * @since BlackBerry 10.0.0
     */
    void setProviderData(const QString& providerData);

    /*!
     * @brief Sets the account ID of this @c CalendarFolder.
     *
     * @param accountId The new account ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccountId(AccountId accountId);

    /*!
     * @brief Sets the folder ID of this @c CalendarFolder.
     *
     * @param id The new folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setId(FolderId id);

    /*!
     * @brief Sets the parent folder ID of this @c CalendarFolder.
     *
     * @param parentId The new parent folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setParentId(FolderId parentId);

    /*!
     * @brief Sets the color of this @c CalendarFolder.
     *
     * @param color The new color, encoded as a 24-bit RGB value.
     *
     * @since BlackBerry 10.0.0
     */
    void setColor(unsigned int color);

    /*!
     * @brief Sets the type of this @c CalendarEvent.
     *
     * @param type The new type.
     *
     * @since BlackBerry 10.0.0
     */
    void setType(int type);

    /*!
     * @brief Sets whether this @c CalendarFolder is read-only.
     *
     * @param readOnly If @c true this @c %CalendarFolder is read-only, if @c false this
     * @c %CalendarFolder is not read-only.
     *
     * @since BlackBerry 10.0.0
     */
    void setReadOnly(bool readOnly);

    /*!
     * @brief Sets whether this @c CalendarFolder is visible in the Calendar application.
     *
     * @param visible If @c true this @c %CalendarFolder is visible in the Calendar
     * application, if @c false this @c %CalendarFolder is not visible.
     *
     * @since BlackBerry 10.0.0
     */
    void setVisible(bool visible);

    /*!
     * @brief Indicates whether this @c CalendarFolder is valid.
     *
     * @details This function determines whether the attributes of this @c %CalendarFolder
     * object have acceptable values.
     *
     * @return @c true if this @c %CalendarFolder is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<CalendarFolderPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_CALENDARFOLDER_HPP


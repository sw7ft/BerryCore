
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_FOLDERKEY_HPP
#define BB_PIM_CALENDAR_FOLDERKEY_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace calendar {

class FolderKeyPrivate;

/*!
 * @brief The @c FolderKey class represents a database key for calendar folders.
 *
 * @details This class includes attributes (such as folder ID and account ID) that
 * uniquely identify a folder in the calendar database.
 * 
 * @c %FolderKey objects are used by the @c EventSearchParameters class, which itself
 * is used when you want to search for specific events in the calendar database. When
 * you call @c EventSearchParameters::folders(), a list of @c %FolderKey objects is
 * returned. Each object represents a particular folder to search in. You can call
 * @c EventSearchParameters::addFolder() or @c EventSearchParameters::setFolders() to
 * add or set folders to search in.
 * 
 * @see EventSearchParameters
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT FolderKey {
public:

    /*!
     * @brief Constructs a new @c FolderKey.
     *
     * @since BlackBerry 10.0.0
     */
    FolderKey();

    /*!
     * @brief Destroys this @c FolderKey.
     *
     * @since BlackBerry 10.0.0
     */
    ~FolderKey();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c FolderKey containing exactly the
     * same values as the provided @c %FolderKey.
     *
     * @param other The @c %FolderKey to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    FolderKey(const FolderKey& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c FolderKey
     * into this @c %FolderKey.
     *
     * @param other The @c %FolderKey from which to copy all values.
     *
     * @return A reference to this @c %FolderKey.
     *
     * @since BlackBerry 10.0.0
     */
    FolderKey& operator=(const FolderKey& other);

    /*!
     * @brief Retrieves the folder ID of this @c FolderKey.
     *
     * @details This function returns the identifier of the folder that's associated
     * with this @c %FolderKey.
     *
     * @return The folder ID of this @c %FolderKey.
     *
     * @since BlackBerry 10.0.0
     */
    FolderId folderId() const;

    /*!
     * @brief Retrieves the account ID of this @c FolderKey.
     *
     * @details This function returns the identifier of the account that's associated
     * with this @c %FolderKey in the database.
     *
     * @return The accont ID of this @c %FolderKey.
     *
     * @since BlackBerry 10.0.0
     */
    AccountId accountId() const;


    /*!
     * @brief Sets the folder ID of this @c FolderKey.
     *
     * @param folderId The new folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setFolderId(FolderId folderId);

    /*!
     * @brief Sets the account ID of this @c FolderKey.
     *
     * @param accountId The new account ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccountId(AccountId accountId);

    /*!
     * @brief Indicates whether this @c FolderKey is valid.
     *
     * @details This function determines whether the attributes of this @c %FolderKey
     * object have acceptable values.
     *
     * @return @c true if this @c %FolderKey is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<FolderKeyPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_FOLDERKEY_HPP


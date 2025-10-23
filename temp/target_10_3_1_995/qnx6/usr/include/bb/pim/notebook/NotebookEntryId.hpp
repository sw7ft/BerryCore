/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYID_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYID_HPP

#include <bb/pim/Global>

#include <bb/pim/account/Account>

#include <QDebug>
#include <QHash>
#include <QList>
#include <QMetaType>
#include <QSharedDataPointer>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookEntryIdPrivate;

typedef unsigned int NotebookEntryKey;

/*!
 * @headerfile NotebookEntryId.hpp <bb/pim/notebook/NotebookEntryId>
 *
 * @brief The @c NotebookEntryId class represents the unique ID of a @c NotebookEntry.
 *
 * @details A @c %NotebookEntryId consists of an @c AccountKey and a @c NotebookEntryKey.  A @c %NotebookEntryKey
 * is unique within an account, but not across accounts, and therefore an @c %AccountKey must also be provided to
 * ensure uniqueness across the system.
 *
 * A @c %NotebookEntry is automatically assigned a @c %NotebookEntryId when it is committed to persistence using
 * the @c NotebookService.  The @c %AccountKey is inherited from the parent @c Notebook of the @c %NotebookEntry,
 * and the @c %NotebookEntryKey is assigned by the database at commit time.
 *
 * @see NotebookEntry
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookEntryId
{

public:
    /*!
     * @brief Constructs a new @c NotebookEntryId with default values.
     *
     * @details A default-constructed @c %NotebookEntryId is considered invalid.
     *
     * @see isValid()
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryId();

    /*!
     * @brief Constructs a new @c NotebookEntryId with the provided account key and notebook entry key.
     *
     * @details The account key specifies the account that the @c NotebookEntry for this @c %NotebookEntryId
     * belongs to.  The notebook entry key uniquely identifies a @c %NotebookEntry within a particular account.
     *
     * @param accountKey The account key.
     * @param notebookEntryKey The notebook entry key.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryId(bb::pim::account::AccountKey accountKey, NotebookEntryKey notebookEntryKey);

    /*!
     * @brief Constructs a new @c NotebookEntryId from the provided @c QString.
     *
     * @details The @c notebookEntryId as a @c QString contains an account key and notebook entry key separated by a
     * ":".  The account key specifies the account that the @c NotebookEntry for this @c %NotebookEntryId
     * belongs to.  The notebook entry key uniquely identifies a @c %NotebookEntry within a particular account.
     * If a malformed @c %notebookEntryId string is provided, the @c %NotebookEntryId will be default-constructed
     * and considered invalid.
     *
     * @param notebookEntryId The notebook entry ID as a human-readable string.
     *
     * @see isValid(), toString()
     *
     * @since BlackBerry 10.0.0
     */
    explicit NotebookEntryId(const QString &notebookEntryId);

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c NotebookEntryId containing exactly the same values as the
     * provided @c %NotebookEntryId.
     *
     * @param other The @c %NotebookEntryId to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryId(const NotebookEntryId &other);

    /*!
     * @brief Destroys this @c NotebookEntryId.
     *
     * @since BlackBerry 10.0.0
     */
    ~NotebookEntryId();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c NotebookEntryId into this
     * @c %NotebookEntryId.
     *
     * @param other The @c %NotebookEntryId from which to copy all values.
     *
     * @return A reference to this @c %NotebookEntryId.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryId& operator=(const NotebookEntryId &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator determines if this @c NotebookEntryId has the same values as another
     * @c %NotebookEntryId.  This operator should be used on the IDs of two @c NotebookEntry objects
     * to determine whether they represent the same entity in the database.
     *
     * @param other The @c %NotebookEntryId from which to compare.
     *
     * @return @c true if the values are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const NotebookEntryId &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator determines if this @c NotebookEntryId has any different values from
     * another @c %NotebookEntryId.  This operator should be used on the IDs of two @c NotebookEntry
     * objects to determine whether they represent different entities in the database.
     *
     * @param other The @c %NotebookEntryId from which to compare.
     *
     * @return @c true if any of the values are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const NotebookEntryId &other) const;

    /*!
     * @brief Retrieves the account key for this @c NotebookEntryId.
     *
     * @details The account key determines which account the @c NotebookEntry for this @c %NotebookEntryId
     * belongs to.
     *
     * @return The account key for this @c %NotebookEntryId.
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::account::AccountKey accountKey() const;

    /*!
     * @brief Retrieves the notebook entry key for this @c NotebookEntryId.
     *
     * @details The notebook entry key uniquely identifies a @c NotebookEntry within a particular account.
     *
     * @return The notebook entry key for this @c %NotebookEntryId.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryKey notebookEntryKey() const;

    /*!
     * @brief Indicates whether this @c NotebookEntryId is valid.
     *
     * @details A default-constructed @c %NotebookEntryId is considered invalid.
     *
     * @return @c true if this @c %NotebookEntryId is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Returns the human-readable string representation of this @c NotebookEntryId.
     *
     * @details The account key and notebook entry key comprising the @c %NotebookEntryId is encoded
     * as a string separated with a colon in the format of "<accountKey>:<notebookKey>".
     *
     * @return The human-readable string representation of this @c %NotebookEntryId.
     *
     * @since BlackBerry 10.0.0
     */
    QString toString() const;

private:
    QSharedDataPointer<NotebookEntryIdPrivate> d_ptr;
};

/*!
 * @brief Stream operator.
 *
 * @details This operator writes a @c NotebookEntryId to a @c QDebug stream.
 *
 * @param stream The @c %QDebug stream to write to.
 * @param id The @c %NotebookEntryId to write.
 *
 * @return A reference to the stream.
 */
BB_PIM_EXPORT QDebug &operator<<(QDebug &stream, const NotebookEntryId &id);

} // namespace notebook
} // namespace pim
} // namespace bb

Q_DECLARE_METATYPE(bb::pim::notebook::NotebookEntryId)
Q_DECLARE_METATYPE(QList<bb::pim::notebook::NotebookEntryId>)

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYID_HPP */

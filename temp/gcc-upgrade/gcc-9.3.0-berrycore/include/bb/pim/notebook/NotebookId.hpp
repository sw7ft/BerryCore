/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKID_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKID_HPP

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

class NotebookIdPrivate;

typedef unsigned int NotebookKey;

/*!
 * @headerfile NotebookId.hpp <bb/pim/notebook/NotebookId>
 *
 * @brief The @c NotebookId class represents the unique ID of a @c Notebook.
 *
 * @details A @c %NotebookId consists of an @c AccountKey and a @c NotebookKey.  A @c %NotebookKey is unique within
 * an account, but not across accounts, and therefore an @c %AccountKey must also be provided to ensure uniqueness
 * across the system.
 *
 * A @c %Notebook is automatically assigned a @c %NotebookId when it is committed to persistence using the @c
 * NotebookService.  The @c %AccountKey is provided as an argument to the @c NotebookService::addNotebook()
 * function, and the @c %NotebookKey is assigned by the database at commit time.
 *
 * @see Notebook
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookId
{

public:
    /*!
     * @brief Constructs a new @c NotebookId with default values.
     *
     * @details A default-constructed @c %NotebookId is considered invalid.
     *
     * @see isValid()
     *
     * @since BlackBerry 10.0.0
     */
    NotebookId();

    /*!
     * @brief Constructs a new @c NotebookId with the provided account key and notebook key.
     *
     * @details The account key specifies the account that the @c Notebook for this @c %NotebookId belongs
     * to.  The notebook key uniquely identifies a @c %Notebook within a particular account.
     *
     * @param accountKey The account key.
     * @param notebookKey The notebook key.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookId(bb::pim::account::AccountKey accountKey, NotebookKey notebookKey);

    /*!
     * @brief Constructs a new @c NotebookId from the provided @c QString.
     *
     * @details The @c notebookId as a @c QString contains an account key and notebook key separated by a ":".
     * The account key specifies the account that the @c Notebook for this @c %NotebookId belongs
     * to.  The notebook key uniquely identifies a @c %Notebook within a particular account. If a malformed
     * @c %notebookId string is provided, the @c %NotebookId will be default-constructed and considered invalid.
     *
     * @param notebookId The notebook ID as a human-readable string.
     *
     * @see isValid(), toString()
     *
     * @since BlackBerry 10.0.0
     */
    explicit NotebookId(const QString &notebookId);

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c NotebookId containing exactly the same values as the
     * provided @c %NotebookId.
     *
     * @param other The @c %NotebookId to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookId(const NotebookId &other);

    /*!
     * @brief Destroys this @c NotebookId.
     *
     * @since BlackBerry 10.0.0
     */
    ~NotebookId();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c NotebookId into this @c %NotebookId.
     *
     * @param other The @c %NotebookId from which to copy all values.
     *
     * @return A reference to this @c %NotebookId.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookId& operator=(const NotebookId &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator determines if this @c NotebookId has the same values as another @c %NotebookId.
     * This operator should be used on the IDs of two @c Notebook objects to determine whether they represent
     * the same entity in the database.
     *
     * @param other The @c %NotebookId from which to compare.
     *
     * @return @c true if the values are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const NotebookId &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator determines if this @c NotebookId has any different values from another
     * @c %NotebookId.  This operator should be used on the IDs of two @c Notebook objects to determine whether
     * they represent different entities in the database.
     *
     * @param other The @c %NotebookId from which to compare.
     *
     * @return @c true if any of the values are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const NotebookId &other) const;

    /*!
     * @brief Retrieves the account key for this @c NotebookId.
     *
     * @details The account key determines which account the @c Notebook for this @c %NotebookId belongs to.
     *
     * @return The account key for this @c %NotebookId.
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::account::AccountKey accountKey() const;

    /*!
     * @brief Retrieves the notebook key for this @c NotebookId.
     *
     * @details The notebook key uniquely identifies a @c Notebook within a particular account.
     *
     * @return The notebook key for this @c %NotebookId.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookKey notebookKey() const;

    /*!
     * @brief Indicates whether this @c NotebookId is valid.
     *
     * @details A default-constructed @c %NotebookId is considered invalid.
     *
     * @return @c true if this @c %NotebookId is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Returns the human-readable string representation of the @c NotebookId.
     *
     * @details The account key and notebook key comprising the @c %NotebookId is encoded
     * as a string separated with a colon in the format of "<accountKey>:<notebookKey>".
     *
     * @return The human-readable string representation of this @c %NotebookId.
     *
     * @since BlackBerry 10.0.0
     */
    QString toString() const;

private:
    QSharedDataPointer<NotebookIdPrivate> d_ptr;
};

/*!
 * @brief Stream operator.
 *
 * @details This operator writes a @c NotebookId to a @c QDebug stream.
 *
 * @param stream The @c %QDebug stream to write to.
 * @param id The @c %NotebookId to write.
 *
 * @return A reference to the stream.
 */
BB_PIM_EXPORT QDebug &operator<<(QDebug &stream, const NotebookId &id);

} // namespace notebook
} // namespace pim
} // namespace bb

Q_DECLARE_METATYPE(bb::pim::notebook::NotebookId)
Q_DECLARE_METATYPE(QList<bb::pim::notebook::NotebookId>)

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKID_HPP */

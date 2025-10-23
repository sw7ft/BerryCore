/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYHEADER_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYHEADER_HPP

#include <bb/pim/Global>

#include <QSharedDataPointer>
#include <QMetaType>
#include <QString>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookEntryHeaderPrivate;

/*!
 * @headerfile NotebookEntryHeader.hpp <bb/pim/notebook/NotebookEntryHeader>
 *
 * @brief The @c NotebookEntryHeader class represents a header to be shown in a list of @c NotebookEntry objects.
 *
 * @details Each @c %NotebookEntryHeader contains a title and a count.
 * The title should be shown in the header of a @c ListView.
 * The count represents the number of Notebook Entries that should be shown in the section under the header.
 *
 * The headers can be retrieved using @c NotebookService::notebookEntryHeaders()
 *
 * @see NotebookService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PIM_EXPORT NotebookEntryHeader
{

public:

    /*!
     * @brief Constructs a new @c NotebookEntryHeader with default values.
     *
     * @since BlackBerry 10.2.0
     */
    NotebookEntryHeader();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c %NotebookEntryHeader containing exactly the same values as the provided
     * @c %NotebookEntryHeader.
     *
     * @param other The @c %NotebookEntryHeader to be copied.
     *
     * @since BlackBerry 10.2.0
     */
    NotebookEntryHeader(const NotebookEntryHeader &other);

    /*!
     * @brief Destroys this @c %NotebookEntryHeader.
     *
     * @since BlackBerry 10.2.0
     */
    ~NotebookEntryHeader();

    /*!
     * @brief Assignment operator.
     *
     * @details Copies all values from the provided @c NotebookEntryHeader into this @c %NotebookEntryHeader.
     *
     * @param other The @c %NotebookEntryHeader from which to copy all values.
     *
     * @return A reference to this @c %NotebookEntryHeader.
     *
     * @since BlackBerry 10.2.0
     */
    NotebookEntryHeader& operator=(const NotebookEntryHeader &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator indicates whether the provided @c NotebookEntryHeader contains the same title
     * and count as this @c %NotebookEntryHeader.
     *
     * @param other The @c %NotebookEntryHeader to compare to this one for equality of title and count.
     *
     * @return @c true if the provided @c %NotebookEntryHeader has the same title and count as this one,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator==(const NotebookEntryHeader &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator indicates whether the provided @c NotebookEntryHeader contains a different
     * title or count than this @c %NotebookEntryHeader.
     *
     * @param other The @c %NotebookEntryHeader to compare to this one for inequality of title or count.
     *
     * @return @c true if the provided @c %NotebookEntryHeader has a different title or count than this one,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator!=(const NotebookEntryHeader &other) const;

    /*!
     * @brief Determines whether or not this @c NotebookEntryHeader is valid.
     *
     * @details A default-constructed @c %NotebookEntryHeader is considered invalid until its title value is set.
     *
     * @return @c true if this @c %NotebookEntryHeader is valid, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isValid() const;

    /*!
     * @brief Determines whether or not this @c NotebookEntryHeader is empty.
     *
     * @details A @c %NotebookEntryHeader is considered empty if its title is empty.
     *
     * @return @c true if this @c %NotebookEntryHeader object's title is empty, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isEmpty() const;

    /*!
     * @brief Sets the title for this @c NotebookEntryHeader.
     *
     * @param title The new title for this @c %NotebookEntryHeader.
     *
     * @since BlackBerry 10.2.0
     */
    void setTitle(const QString &title);

    /*!
     * @brief Retrieves the title of this @c NotebookEntryHeader.
     *
     * @return The title of this @c %NotebookEntryHeader.
     *
     * @since BlackBerry 10.2.0
     */
    QString title() const;

    /*!
     * @brief Sets the count for this @c NotebookEntryHeader.
     *
     * @param count The new count for this @c %NotebookEntryHeader.
     *
     * @since BlackBerry 10.2.0
     */
    void setCount(int count);

    /*!
     * @brief Retrieves the count of this @c NotebookEntryHeader.
     *
     * @return The count of this @c %NotebookEntryHeader.
     *
     * @since BlackBerry 10.2.0
     */
    int count() const;

private:
    QSharedDataPointer<NotebookEntryHeaderPrivate> d_ptr;
};

} // namespace notebook
} // namespace pim
} // namespace bb

Q_DECLARE_METATYPE(bb::pim::notebook::NotebookEntryHeader)

#endif // BB_PIM_NOTEBOOK_NOTEBOOKENTRYHEADER_HPP

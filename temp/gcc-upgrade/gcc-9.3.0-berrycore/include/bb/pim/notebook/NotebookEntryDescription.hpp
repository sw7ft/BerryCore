/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYDESCRIPTION_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYDESCRIPTION_HPP

#include <bb/pim/Global>

#include <QSharedDataPointer>
#include <QString>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookEntryDescriptionPrivate;

/*!
 * @headerfile NotebookEntryDescription.hpp <bb/pim/notebook/NotebookEntryDescription>
 *
 * @brief A NotebookEntryDescription is the text content of a NotebookEntry along with its respective type.
 *
 * @details The type value of the NotebookEntryDescription indicates how the text should be displayed and edited.
 *
 * Example usage:
 * @code
 *   // Here's how to create an HTML description.
 *   NotebookEntryDescription description;
 *   description.setText( "This is an <B>HTML</B> description.",
 *                          NotebookEntryDescription::HTML );
 * @endcode
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
class BB_PIM_EXPORT NotebookEntryDescription
{
public:
    /*!
     * @brief An enumeration of supported description types.
     *
     * @details @c NotebookEntryDescription objects with a type other than @c #PLAIN_TEXT have special formatting.
     * See the class-level documentation for more details.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * Indicates that the description is stored as plaintext; implies no special formatting or behavior.
         *
         * @since BlackBerry 10.0.0
         */
        PLAIN_TEXT = 0,

        /*!
         * Indicates that the description is stored as HTML; implies HTML5 tags are used for formatting and resource embedding.
         *
         * @since BlackBerry 10.0.0
         */
        HTML = 1
    };

    /*!
     * @brief Constructs a new @c NotebookEntryDescription.
     *
     * @details A default-constructed @c %NotebookEntryDescription is considered invalid until its text value is set.
     *
     * @see isValid()
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryDescription();

    /*!
     * @brief Copy constructor.
     *
     * @details Constructs a @c NotebookEntryDescription containing exactly the same values as the provided
     * @c %NotebookEntryDescription.
     *
     * @param other The @c %NotebookEntryDescription to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryDescription(const NotebookEntryDescription &other);

    /*!
     * @brief Destroys this @c NotebookEntryDescription.
     *
     * @since BlackBerry 10.0.0
     */
    ~NotebookEntryDescription();

    /*!
     * @brief Assignment operator.
     *
     * @details Copies all values from the provided @c NotebookEntryDescription into this @c %NotebookEntryDescription.
     *
     * @param other The @c %NotebookEntryDescription from which to copy all values.
     *
     * @return A reference to this @c %NotebookEntryDescription.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryDescription& operator=(const NotebookEntryDescription &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator indicates whether the provided @c NotebookEntryDescription contains the same type
     * and text as this @c %NotebookEntryDescription.
     *
     * @param other The @c %NotebookEntryDescription to compare to this one for equality of type and text.
     *
     * @return @c true if the provided @c %NotebookEntryDescription has the same type and text as this one,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const NotebookEntryDescription &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator indicates whether the provided @c NotebookEntryDescription contains a different
     * type or text than this @c %NotebookEntryDescription.
     *
     * @param other The @c %NotebookEntryDescription to compare to this one for inequality of type or text.
     *
     * @return @c true if the provided @c %NotebookEntryDescription has a different type or text than this one,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const NotebookEntryDescription &other) const;

    /*!
     * @brief Determines whether or not this @c NotebookEntryDescription is valid.
     *
     * @details A default-constructed @c %NotebookEntryDescription is considered invalid until its text value is set.
     *
     * @return @c true if this @c %NotebookEntryDescription is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Determines whether or not this @c NotebookEntryDescription is empty.
     *
     * @details A @c %NotebookEntryDescription is considered empty if its text is empty.
     *
     * @return @c true if this @c %NotebookEntryDescription object's text is empty, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isEmpty() const;

    /*!
     * @brief Sets the text and type for this @c NotebookEntryDescription.
     *
     * @param text The new text for this @c %NotebookEntryDescription.
     * @param type The type of this @c %NotebookEntryDescription.
     *
     * @since BlackBerry 10.0.0
     */
    void setText(const QString &text, NotebookEntryDescription::Type type = PLAIN_TEXT);

    /*!
     * @brief Retrieves the text for this @c NotebookEntryDescription.
     *
     * @return The text for this @c %NotebookEntryDescription.
     *
     * @since BlackBerry 10.0.0
     */
    QString text() const;

    /*!
     * @brief Retrieves the type of this @c NotebookEntryDescription.
     *
     * @return The Type of this @c %NotebookEntryDescription.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryDescription::Type type() const;

    /*!
     * @brief Retrieves the text for this @c NotebookEntryDescription as plaintext.
     *
     * @details If this @c %NotebookEntryDescription object's type is @c #PLAIN_TEXT,
     * this function simply returns its text (as if @c text() had been invoked).  Otherwise, this function
     * returns a plaintext representation of this @c %NotebookEntryDescription object's text.
     *
     * @return A plaintext representation of this @c %NotebookEntryDescription object's text.
     *
     * @since BlackBerry 10.0.0
     */
    QString plainText() const;

private:
    QSharedDataPointer<NotebookEntryDescriptionPrivate> d_ptr;
    friend class NotebookEntryDescriptionPrivate;
};

} // namespace notebook
} // namespace pim
} // namespace bb

#endif // BB_PIM_NOTEBOOK_NOTEBOOKENTRYDESCRIPTION_HPP

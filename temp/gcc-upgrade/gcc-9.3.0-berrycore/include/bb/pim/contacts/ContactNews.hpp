/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTNEWS_HPP
#define BB_PIM_CONTACTS_CONTACTNEWS_HPP

#include <bb/pim/Global>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QSharedDataPointer>
#include <QUrl>

namespace bb {
namespace pim {
namespace contacts {

class ContactNewsPrivate;

/*!
 * @brief The @c ContactNews class represents online news for a contact.
 * 
 * @details You can use this class to represent an online article that's associated with a @c Contact. The article
 * can include information such as source, title, publish date, and URI. This class works with the
 * @c ContactEnhancementService class to provide associated news articles for enhanced contacts.
 * 
 * @see Contact, ContactEnhancementService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactNews
{
public:
    /*!
     * @brief Constructs a new @c ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    ContactNews();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactNews containing exactly the same values as the provided
     * @c %ContactNews.
     * 
     * @param copy The @c %ContactNews to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactNews(const ContactNews &copy);

    /*!
     * @brief Destroys this @c ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactNews();

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactNews into this @c %ContactNews.
     * 
     * @param operand The @c %ContactNews from which to copy all values.
     *
     * @return A @c %ContactNews with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactNews& operator=(const ContactNews &operand);
    
    /*!
     * @brief Retrieves the internal ID of this @c ContactNews.
     * 
     * @details The @c ContactEnhancementService retrieves news for a contact according to first name, last name,
     * and company name. It might include one or more news articles, and each article is assigned an internal ID.
     * 
     * @return The internal ID of this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QString id() const;

    /*!
     * @brief Retrieves the source of this @c ContactNews.
     * 
     * @return The source of this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QString articleSource() const;

    /*!
     * @brief Retrieves the contents of this @c ContactNews.
     * 
     * @return The contents of this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QString body() const;

    /*!
     * @brief Retrieves the title of this @c ContactNews.
     * 
     * @return The title of this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Retrieves the list of companies that are associated with this @c ContactNews.
     * 
     * @return The list of companies that are associated with this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList companies() const;

    /*!
     * @brief Retrieves the publish date of this @c ContactNews.
     * 
     * @return The publish date of this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime publishedAt() const;

    /*!
     * @brief Retrieves the URL of this @c ContactNews.
     * 
     * @return The URL of this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl uri() const;

    /*!
     * @brief Retrieves the type of this @c ContactNews.
     * 
     * @details For example, the article might have a type of "Press Release."
     * 
     * @return The type of this @c %ContactNews.
     *
     * @since BlackBerry 10.0.0
     */
    QString type() const;

private:
    QSharedDataPointer<ContactNewsPrivate> d_ptr;
    friend class ContactNewsPrivate;
};

} // contacts
} // pim
} // bb

#endif // BB_PIM_CONTACTS_CONTACTNEWS_HPP

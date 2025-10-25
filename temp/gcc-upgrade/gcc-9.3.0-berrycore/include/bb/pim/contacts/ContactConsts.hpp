/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTCONSTS_HPP
#define BB_PIM_CONTACTS_CONTACTCONSTS_HPP
#include <bb/pim/Global>
#include <QPair>
#include <QString>

namespace bb {
namespace pim {
namespace contacts {

typedef int AccountId;
typedef int ContactId;
typedef int GroupId;
typedef QString StatusId;

/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c AttributeKind class contains the possible attribute kinds for a contact.
 *
 * @details The kind specifies metadata about the type of an attribute. The kind is represented by the
 * @c AttributeKind::Type enumeration and can be values such as Name, Email, Phone, and so on.
 *
 * You can use the values in the @c %AttributeKind class in conjunction with values in the @c AttributeSubKind
 * class to precisely define the classification of attributes for a @c Contact. You use the @c ContactAttribute class
 * to represent a specific attribute.
 *
 * Note that the "Hidden" kind is useful for storing private application-specific data, if required.
 *
 * @see AttributeSubKind, Contact, ContactAttribute
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT AttributeKind
{
public:
    /*!
     * @brief An enumeration of possible attribute kinds for a contact.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates an invalid attribute kind.
         *
         * @since BlackBerry 10.0.0
         */
        Invalid = 0,
        /*!
         * Indicates the Phone attribute kind. This kind should be used with the Home, Other, and PhoneMobile
         * sub-kinds.
         *
         * @since BlackBerry 10.0.0
         */
        Phone = 1,
        /*!
         * Indicates the Fax attribute kind.
         *
         * @since BlackBerry 10.0.0
         */
        Fax = 2,
        /*!
         * Indicates the Pager attribute kind.
         *
         * @since BlackBerry 10.0.0
         */
        Pager = 3,
        /*!
         * Indicates the Email attribute kind.
         *
         * @since BlackBerry 10.0.0
         */
        Email = 4,
        /*!
         * Indicates the Website attribute kind. This kind can be used with sub-kinds such as Blog, Portfolio,
         * and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Website = 5,
        /*!
         * Indicates the Web feed attribute kind. This kind is used for RSS/Atom feeds, as opposed to websites,
         * which use the @c Website kind..
         *
         * @since BlackBerry 10.0.0
         */
        Feed = 6,
        /*!
         * Indicates the Profile attribute kind. This kind is used for social profiles like Facebook, Twitter,
         * and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Profile = 7,
        /*!
         * Indicates the Family members kind. This kind can be used with sub-kinds such as Spouse, Child, and so
         * on.
         *
         * @since BlackBerry 10.0.0
         */
        Family = 8,
        /*!
         * Indicates the Person attribute kind. This kind can be used with sub-kinds such as Manager, Assistant,
         * and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Person = 9,
        /*!
         * Indicates the Date attribute kind. This kind can be used with sub-kinds such as Birthday, Anniversary, and
         * so on.
         *
         * @since BlackBerry 10.0.0
         */
        Date = 10,
        /*!
         * Indicates the Group attribute kind. This kind should be used with the GroupDepartment sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        Group = 11,
        /*!
         * Indicates the Name attribute kind that's used to describe the contact. This kind can be used with sub-kinds
         * such as Title, NameSurname, NameGiven, NameMiddle, and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Name = 12,
        /*!
         * Indicates the StockSymbol attribute kind. This kind can be used with sub-kinds such as StockSymbolNyse,
         * StockSymbolNasdaq, and so on.
         *
         * @since BlackBerry 10.0.0
         */
        StockSymbol = 13,
        /*!
         * Indicates the Ranking attribute kind. This kind can be used with sub-kinds such as Klout, TrstRank, and so
         * on.
         *
         * @since BlackBerry 10.0.0
         */
        Ranking = 14,
        /*!
         * Indicates the OrganizationAffiliation attribute kind. This kind can be used with sub-kinds such as
         * OrganizationAffiliationName, OrganizationAffiliationTitle, StartDate, EndDate, and so on.
         *
         * @since BlackBerry 10.0.0
         */
        OrganizationAffiliation = 15,
        /*!
         * Indicates the Education attribute kind. This kind can be used with sub-kinds such as EducationInstitutionName,
         * StartDate, EndDate, and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Education = 16,
        /*!
         * Indicates the Note attribute kind. This kind is usually used with the Other sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        Note = 17,
        /*!
         * Indicates the InstantMessaging attribute kind. This kind can be used with sub-kinds such as InstantMessagingBbmPin.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessaging = 18,
        /*!
         * Indicates the VideoChat attribute kind. This kind can be used with the VideoChatBbPlaybook sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        VideoChat = 19,
        /*!
         * Indicates the Connection count attribute kind, which is used for different social providers. For example, this
         * kind might be used to indicate that a contact has 80 connections in LinkedIn.
         *
         * @since BlackBerry 10.0.0
         */
        ConnectionCount = 20,
        /*!
         * Indicates the Hidden attribute kind. This kind can be used for any information that you need. It's designed to add
         * hidden properties to a contact for applications to use.
         *
         * @since BlackBerry 10.0.0
         */
        Hidden = 21,
        /*!
         * Indicates the Biography attribute kind. This kind can be used with the BiographyFacebook, BiographyTwitter, and
         * BiographyLinkedIn sub-kinds.
         *
         * @since BlackBerry 10.0.0
         */
        Biography = 22,
        /*!
         * Indicates the Sound attribute kind. This kind is currently used with the SoundRingtone sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        Sound = 23,
        /*!
         * Indicates the Notification attribute kind. This kind is currently used with the Notification* sub-kinds.
         *
         * @since BlackBerry 10.0.0
         */
        Notification = 24,
        /*!
         * Indicates the MessageSound attribute kind. This kind is currently used with the MessageRingtone sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        MessageSound = 25,
        /*!
         * Indicates the MessageNotification attribute kind. This kind is currently used with the MessageNotification*
         * sub-kinds.
         *
         * @since BlackBerry 10.0.0
         */
        MessageNotification = 26,
        /*!
         * Indicates the SecureVoice attribute kind. This kind is currently used with the SecureVoice*
         * sub-kinds.
         *
         * @since BlackBerry 10.3.0
         */
        SecureVoice = 27
    };
};

/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c AttributeSubKind class contains the possible attribute sub-kinds for a contact.
 *
 * @details Similar to the kind of an attribute, the sub-kind refers to a sub-type of an attribute. The sub-kind is
 * represented by the @c AttributeSubKind::Type enumeration.For example, if the kind of attribute is a phone number, then
 * possible sub-kinds might be Work, Home, and so on. By using combinations of kinds and sub-kinds, you can specify a wide
 * range of attributes for contacts.
 *
 * You can add custom sub-kinds to this list. For more information, see the
 * @c ContactAttributeBuilder::determineAttributeSubKind() function.
 *
 * Any value that's not found in this list is considered a dynamic value. You shouldn't assume that its value is fixed across
 * process restarts.
 *
 * @see AttributeSubKind, Contact, ContactAttribute
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT AttributeSubKind {
public:
    /*!
     * @brief An enumeration of possible attribute sub-kinds for a contact.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates an invalid attribute sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        Invalid = 0,
        /*!
         * Indicates the Other sub-kind. This sub-kind can be used with certain kinds to more precisely define an
         * attribute, such as "Other Phone", "Other Email", "Other Postal Address", and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Other = 1,
        /*!
         * Indicates the Home sub-kind. This sub-kind can be used with certain kinds to more precisely define an
         * attribute, such as "Home Phone, "Home Email", "Home Postal Address", and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Home = 2,
        /*!
         * Indicates the Work sub-kind. This sub-kind can be used with certain kinds to more precisely define an
         * attribute, such as "Work Phone, "Work Email", and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Work = 3,
        /*!
         * Indicates the PhoneMobile sub-kind. This sub-kind is used to represent a mobile phone number.
         *
         * @since BlackBerry 10.0.0
         */
        PhoneMobile = 4,
        /*!
         * Indicates the FaxDirect sub-kind. This sub-kind is used to represent a direct fax number.
         *
         * @since BlackBerry 10.0.0
         */
        FaxDirect = 5,
        /*!
         * Indicates the Blog sub-kind works. This sub-kind is used in conjunction with the Website kind to represet
         * a blog page.
         *
         * @since BlackBerry 10.0.0
         */
        Blog = 6,
        /*!
         * Indicates the WebsiteResume sub-kind. This sub-kind is used to represent an online resume.
         *
         * @since BlackBerry 10.0.0
         */
        WebsiteResume = 7,
        /*!
         * Indicates the WebsitePortfolio sub-kind. This sub-kind is used to represent a personal portfolio.
         *
         * @since BlackBerry 10.0.0
         */
        WebsitePortfolio = 8,
        /*!
         * Indicates the WebsitePersonal sub-kind. This sub-kind is used to represent a personal website.
         *
         * @since BlackBerry 10.0.0
         */
        WebsitePersonal = 9,
        /*!
         * Indicates the WebsiteCompany sub-kind. This sub-kind is used to represent a company website.
         *
         * @since BlackBerry 10.0.0
         */
        WebsiteCompany = 10,
        /*!
         * Indicates the ProfileFacebook sub-kind. This sub-kind means that the attribute contains data pointing to a
         * public Facebook profile.
         *
         * @since BlackBerry 10.0.0
         */
        ProfileFacebook = 11,
        /*!
         * Indicates the ProfileTwitter sub-kind. This sub-kind means that the attribute contains data pointing to a
         * public Twitter profile.
         *
         * @since BlackBerry 10.0.0
         */
        ProfileTwitter = 12,
        /*!
         * Indicates the ProfileLinkedIn sub-kind. This sub-kind means that the attribute contains data pointing to a
         * public LinkedIn profile.
         *
         * @since BlackBerry 10.0.0
         */
        ProfileLinkedIn = 13,
        /*!
         * Indicates the ProfileGist sub-kind. This sub-kind means that the attribute contains data pointing to a Gist
         * profile page.
         *
         * @since BlackBerry 10.0.0
         */
        ProfileGist = 14,
        /*!
         * Indicates the ProfileTungle sub-kind. This sub-kind means that the attribute contains data pointing to a Tungle
         * profile page.
         *
         * @since BlackBerry 10.0.0
         */
        ProfileTungle = 15,
        /*!
         * Indicates the FamilySpouse sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        FamilySpouse = 16,
        /*!
         * Indicates the FamilyChild sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        FamilyChild = 17,
        /*!
         * Indicates the FamilyParent sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        FamilyParent = 18,
        /*!
         * Indicates the PersonManager sub-kind. This sub-kind means that the attribute contains data about this contact's
         * manager.
         *
         * @since BlackBerry 10.0.0
         */
        PersonManager = 19,
        /*!
         * Indicates the PersonAssistant sub-kind. This sub-kind means that the attribute contains data about this contact's
         * assistant.
         *
         * @since BlackBerry 10.0.0
         */
        PersonAssistant = 20,
        /*!
         * Indicates the DateBirthday sub-kind. This sub-kind is used to represent the contact's birthday.
         *
         * @since BlackBerry 10.0.0
         */
        DateBirthday = 21,
        /*!
         * Indicates the DateAnniversary sub-kind. This sub-kind is used to represent the contact's anniversary.
         *
         * @since BlackBerry 10.0.0
         */
        DateAnniversary = 22,
        /*!
         * Indicates the GroupDepartment sub-kind. This sub-kind is used to represent the contact's department.
         *
         * @since BlackBerry 10.0.0
         */
        GroupDepartment = 23,
        /*!
         * Indicates the NameGiven sub-kind. This sub-kind is used to represent a contact's given name.
         *
         * @since BlackBerry 10.0.0
         */
        NameGiven = 24,
        /*!
         * Indicates the NameSurname sub-kind. This sub-kind is used to represent a contact's surname.
         *
         * @since BlackBerry 10.0.0
         */
        NameSurname = 25,
        /*!
         * Indicates the Title sub-kind. This sub-kind is used with the Name and OrganizationAffiliation kinds to indicate
         * the title in each category, such as salutation ("Mr.", "Mrs.") or job title ("Software Developer").
         *
         * @since BlackBerry 10.0.0
         */
        Title = 26,
        /*!
         * Indicates the NameSuffix sub-kind. This sub-kind is used to represent a contact's suffix, such as "Jr."
         *
         * @since BlackBerry 10.0.0
         */
        NameSuffix = 27,
        /*!
         * Indicates the NameMiddle sub-kind. This sub-kind is used to represent a contact's middle name.
         *
         * @since BlackBerry 10.0.0
         */
        NameMiddle = 28,
        /*!
         * Indicates the NameNickname sub-kind. This sub-kind is used to represent a contact's nickname.
         *
         * @since BlackBerry 10.0.0
         */
        NameNickname = 29,
        /*!
         * Indicates the NameAlias sub-kind. This sub-kind is used to represent a contact's alias. It can be used with an
         * email alias as well.
         *
         * @since BlackBerry 10.0.0
         */
        NameAlias = 30,
        /*!
         * Indicates the NameDisplayName sub-kind. This sub-kind is used to represent a contact's display name.
         *
         * @since BlackBerry 10.0.0
         */
        NameDisplayName = 31,
        /*!
         * Indicates the NamePhoneticGiven sub-kind. This sub-kind is used to represent a contact's phonetic given name.
         *
         * @since BlackBerry 10.0.0
         */
        NamePhoneticGiven = 32,
        /*!
         * Indicates the NamePhoneticSurname sub-kind. This sub-kind is used to represent a contact's phonetic surname.
         *
         * @since BlackBerry 10.0.0
         */
        NamePhoneticSurname = 33,
        /*!
         * Indicates the StockSymbolNyse sub-kind. This sub-kind is used to represent the NYSE stock symbols.
         *
         * @since BlackBerry 10.0.0
         */
        StockSymbolNyse = 34,
        /*!
         * Indicates the StockSymbolNasdaq sub-kind. This sub-kind is used to represent the NASDAQ stock symbols.
         *
         * @since BlackBerry 10.0.0
         */
        StockSymbolNasdaq = 35,
        /*!
         * Indicates the StockSymbolTse sub-kind. This sub-kind is used to represent the TSE stock symbols.
         *
         * @since BlackBerry 10.0.0
         */
        StockSymbolTse = 36,
        /*!
         * Indicates the StockSymbolLse sub-kind. This sub-kind is used to represent the LSE stock symbols.
         *
         * @since BlackBerry 10.0.0
         */
        StockSymbolLse = 37,
        /*!
         * Indicates the StockSymbolTsx sub-kind. This sub-kind is used to represent the TSX stock symbols.
         *
         * @since BlackBerry 10.0.0
         */
        StockSymbolTsx = 38,
        /*!
         * Indicates the RankingKlout sub-kind. This sub-kind is used to represent the Klout score attribute.
         *
         * @since BlackBerry 10.0.0
         */
        RankingKlout = 39,
        /*!
         * Indicates the RankingTrstRank sub-kind. This sub-kind is used to represent the Trst reputation ranking.
         *
         * @since BlackBerry 10.0.0
         */
        RankingTrstRank = 40,
        /*!
         * Indicates the OrganizationAffiliationName sub-kind. This sub-kind is used to represent the company name.
         *
         * @since BlackBerry 10.0.0
         */
        OrganizationAffiliationName = 41,
        /*!
         * Indicates the OrganizationAffiliationPhoneticName sub-kind. This sub-kind is used to represent the phonetic
         * company name.
         *
         * @since BlackBerry 10.0.0
         */
        OrganizationAffiliationPhoneticName = 42,
        /*!
         * Indicates the OrganizationAffiliationTitle sub-kind. This sub-kind is used to represent the company title.
         *
         * @since BlackBerry 10.0.0
         */
        OrganizationAffiliationTitle = Title,
        /*!
         * Indicates the StartDate sub-kind. This sub-kind is used with kinds such as Education or OrganizationAffiliation to
         * represent the start date.
         *
         * @since BlackBerry 10.0.0
         */
        StartDate = 43,
        /*!
         * Indicates the EndDate sub-kind. This sub-kind is used with kinds such as Education or OrganizationAffiliation to
         * represent the end date.
         *
         * @since BlackBerry 10.0.0
         */
        EndDate = 44,
        /*!
         * Indicates the OrganizationAffiliationDetails sub-kind. This sub-kind is used to represent details of organizations.
         *
         * @since BlackBerry 10.0.0
         */
        OrganizationAffiliationDetails = 45,
        /*!
         * Indicates the EducationInstitutionName sub-kind. This sub-kind is used to represent the education institution's name.
         *
         * @since BlackBerry 10.0.0
         */
        EducationInstitutionName = 46,
        /*!
         * Indicates the EducationStartDate sub-kind. This sub-kind is the same as StartDate.
         *
         * @since BlackBerry 10.0.0
         */
        EducationStartDate = StartDate,
        /*!
         * Indicates the EducationEndDate sub-kind. This sub-kind is the same as EndDate.
         *
         * @since BlackBerry 10.0.0
         */
        EducationEndDate = EndDate,
        /*!
         * Indicates the EducationDegree sub-kind. This sub-kind is used to represent the education degree, such as BSc.
         *
         * @since BlackBerry 10.0.0
         */
        EducationDegree = 47,
        /*!
         * Indicates the EducationConcentration sub-kind. This sub-kind is used to represent the education degree's
         * concentration, such as Computer Science.
         *
         * @since BlackBerry 10.0.0
         */
        EducationConcentration = 48,
        /*!
         * Indicates the EducationActivities sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        EducationActivities = 49,
        /*!
         * Indicates the EducationNotes sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        EducationNotes = 50,
        /*!
         * Indicates the InstantMessagingBbmPin sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingBbmPin = 51,
        /*!
         * Indicates the InstantMessagingBbmId sub-kind.
         *
         * @since BlackBerry 10.3.0
         */
        HiddenInstantMessagingBbmId = 116,
        /*!
         * Indicates the InstantMessagingAim sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingAim = 52,
        /*!
         * Indicates the InstantMessagingAliwangwang sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingAliwangwang = 53,
        /*!
         * Indicates the InstantMessagingGoogleTalk sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingGoogleTalk = 54,
        /*!
         * Indicates the InstantMessagingSametime sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingSametime = 55,
        /*!
         * Indicates the InstantMessagingIcq sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingIcq = 56,
        /*!
         * Indicates the InstantMessagingIrc sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingIrc = 57,
        /*!
         * Indicates the InstantMessagingJabber sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingJabber = 58,
        /*!
         * Indicates the InstantMessagingMsLcs sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingMsLcs = 59,
        /*!
         * Indicates the InstantMessagingMsn sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingMsn = 60,
        /*!
         * Indicates the InstantMessagingQq sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingQq = 61,
        /*!
         * Indicates the InstantMessagingSkype sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingSkype = 62,
        /*!
         * Indicates the InstantMessagingYahooMessenger sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingYahooMessenger = 63,
        /*!
         * Indicates the InstantMessagingYahooMessengerJapan sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        InstantMessagingYahooMessengerJapan = 64,
        /*!
         * Indicates the VideoChatBbPlaybook sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        VideoChatBbPlaybook = 65,
        /*!
         * Indicates the HiddenLinkedIn sub-kind. This sub-kind is used to represent hidden data about the LinkedIn contact.
         *
         * @since BlackBerry 10.0.0
         */
        HiddenLinkedIn = 66,
        /*!
         * Indicates the HiddenFacebook sub-kind. This sub-kind is used to represent hidden data about the Facebook contact.
         *
         * @since BlackBerry 10.0.0
         */
        HiddenFacebook = 67,
        /*!
         * Indicates the HiddenTwitter sub-kind. This sub-kind is used to represent hidden data about the Twitter contact.
         *
         * @since BlackBerry 10.0.0
         */
        HiddenTwitter = 68,
        /*!
         * Indicates the ConnectionCountLinkedIn sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        ConnectionCountLinkedIn = 69,
        /*!
         * Indicates the ConnectionCountFacebook sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        ConnectionCountFacebook = 70,
        /*!
         * Indicates the ConnectionCountTwitter sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        ConnectionCountTwitter = 71,
        /*!
         * Indicates the HiddenChecksum sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        HiddenChecksum = 72,
        /*!
         * Indicates the HiddenSpeedDial sub-kind. This sub-kind is used to represent hidden speed dial data for the contact
         * if the contact is a speed dial contact.
         *
         * @since BlackBerry 10.0.0
         */
        HiddenSpeedDial = 73,
        /*!
         * Indicates the BiographyFacebook sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        BiographyFacebook = 74,
        /*!
         * Indicates the BiographyTwitter sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        BiographyTwitter = 75,
        /*!
         * Indicates the BiographyLinkedIn sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        BiographyLinkedIn = 76,
        /*!
         * Indicates the SoundRingtone sub-kind. This sub-kind is used to represent custom ring tone information for the contact.
         *
         * @since BlackBerry 10.0.0
         */
        SoundRingtone = 77,
        /*!
         * Indicates the SimContactType sub-kind. This sub-kind is used to represent whether the contact is from a SIM card.
         *
         * @since BlackBerry 10.0.0
         */
        SimContactType = 78,
        /*!
         * Indicates the EcoID sub-kind. This sub-kind is used to communicate with Cloud Services for contact enhancement.
         *
         * @since BlackBerry 10.0.0
         */
        EcoID = 79,
        /*!
         * Indicates the Personal sub-kind. This sub-kind is used in conjunction with the Email kind to represent a personal
         * email address.
         *
         * @since BlackBerry 10.0.0
         */
        Personal = 80,
        /*!
         * Indicates the StockSymbolAll sub-kind. This sub-kind is used to communicate with Cloud Services for contact enhancement.
         *
         * @since BlackBerry 10.0.0
         */
        StockSymbolAll = 81,

        //Notifications

        /*!
         * Indicates the NotificationVibration sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
         */
        NotificationVibration = 82,
        /*!
         * Indicates the NotificationLED sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
         */
        NotificationLED = 83,
        /*!
         * Indicates the MessageNotificationVibration sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
        */
        MessageNotificationVibration = 84,
        /*!
         * Indicates the MessageNotificationLED sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
         */
        MessageNotificationLED = 85,
        /*!
         * Indicates the MessageNotificationDuringCall sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
         */
        MessageNotificationDuringCall = 86,

        /*!
         * Indicates the BBMNotificationTone sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
         */
        BBMNotificationTone = 95,
        /*!
         * Indicates the BBMNotificationVibration sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
         */
        BBMNotificationVibration = 96,
        /*!
         * Indicates the BBMNotificationLED sub-kind. This sub-kind is used in the contacts edit form.
         *
         * @since BlackBerry 10.0.0
         */
        BBMNotificationLED = 97,
        /*!
         * Indicates the BBMNotificationInstantPreview sub-kind. This sub-kind is used to indicate whether Instant Preview notifications
         * should appear for this contact.
         *
         * @since BlackBerry 10.2.0
         */
        BBMNotificationInstantPreview = 100,
        /**
         * Indicates the PhoneNotificationAllAlert sub-kind. This sub-kind is used to represent all phone alerts for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        PhoneNotificationAllAlert = 101,
        /**
         * Indicates the MessageNotificationAllAlert sub-kind. This sub-kind is used to represent all message alerts for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        MessageNotificationAllAlert = 102,
        /**
         * Indicates the MessageNotificationInstantPreview sub-kind. This sub-kind is used to represent the message instant preview for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        MessageNotificationInstantPreview = 103,
        /**
         * Indicates the BBMNotificationAllAlert sub-kind. This sub-kind is used to represent all BBM alerts for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        BBMNotificationAllAlert = 104,
        /**
         * Indicates the TextMessageNotificationAllAlert sub-kind. This sub-kind is used to represent all text messaging alerts for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        TextMessageNotificationAllAlert = 105,
        /**
         * Indicates the TextMessageNotificationInstantPreview sub-kind. This sub-kind is used to represent the text message instant preview for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        TextMessageNotificationInstantPreview = 106,
        /**
         * Indicates the TextMessageNotificationRingtone sub-kind. This sub-kind is used to represent the text message ring tone for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        TextMessageNotificationRingtone = 107,
        /**
         * Indicates the TextMessageNotificationVibration sub-kind. This sub-kind is used to represent the text message vibration for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        TextMessageNotificationVibration = 108,
        /**
         * Indicates the TextMessageNotificationLED sub-kind. This sub-kind is used to represent the text message LED for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        TextMessageNotificationLED = 109,
        /**
         * Indicates the OtherMessageNotificationAllAlert sub-kind. This sub-kind is used to represent all other message alerts for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        OtherMessageNotificationAllAlert = 110,
        /**
         * Indicates the OtherMessageNotificationInstantPreview sub-kind. This sub-kind is used to represent the other message instant preview for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        OtherMessageNotificationInstantPreview = 111,
        /**
         * Indicates the OtherMessageNotificationRingtone sub-kind. This sub-kind is used to represent the other message ring tone for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        OtherMessageNotificationRingtone = 112,
        /**
         * Indicates the OtherMessageNotificationVibration sub-kind. This sub-kind is used to represent the other message vibration for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        OtherMessageNotificationVibration = 113,
        /**
         * Indicates the OtherMessageNotificationLED sub-kind. This sub-kind is used to represent the other message LED for the contact.
         *
         * @since BlackBerry 10.3.0
         */
        OtherMessageNotificationLED = 114,

        //End of Notifications

        /*!
         * Indicates the VideoChatPin sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        VideoChatPin = 87,
        /*!
         * Indicates the Name Prefix sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        NamePrefix = 88,
        /*!
         * Indicates the Business sub-kind. This sub-kind can be used with certain kinds to more precisely define an
         * attribute, such as "Work Postal Address", and so on.
         *
         * @since BlackBerry 10.0.0
         */
        Business = 89,
        /*!
         * Indicates the ProfileSinaWeibo sub-kind. This sub-kind means that the attribute contains data pointing to a
         * public SinaWeibo profile.
         *
         * @since BlackBerry 10.0.0
         */
        ProfileSinaWeibo = 90,
        /*!
         * Indicates the HiddenSinaWeibo sub-kind. This sub-kind is used to represent hidden data about the SinaWeibo contact.
         *
         * @since BlackBerry 10.0.0
         */
        HiddenSinaWeibo = 91,
        /*!
         * Indicates the ConnectionCountSinaWeibo sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        ConnectionCountSinaWeibo = 92,
        /*!
         * Indicates the BiographySinaWeibor sub-kind.
         *
         * @since BlackBerry 10.0.0
         */
        BiographySinaWeibo = 93,
        /**
         * Specifies the type of device in the format "DeviceType:PIN" where device type is one of: BB10-L, PR, or BBOS.  The values supplied here are provided by
         * the ICRS enhancer
         *
         * @since BlackBerry 10.1.0
         */
        DeviceInfo = 94,
        /**
         * Specifies the hidden list of joyn capable phone numbers.
         *
         * @since BlackBerry 10.2.0
         */
        HiddenJoynNumbers = 98,
        /**
         * Indicates the JoynInfo sub-kind. Used to represent hidden joyn meta data.
         *
         * @since BlackBerry 10.2.0
         */
        HiddenJoynInfo = 99,
        /**
         * Indicates the SecureVoiceId sub-kind. Used to represent the id used in secure voice calls (usually a phone number).
         *
         * @since BlackBerry 10.3.0
         */
        SecureVoiceId = 115,
        /**
         * Specifies the hidden list of VoLTE Video capable phone numbers.
         *
         * @since BlackBerry 10.3.0
         */
        HiddenVoLTEVideo = 117,
        /**
         * Specifies the hidden list of VoLTE Voice capable phone numbers.
         *
         *
         * @since BlackBerry 10.3.0
         */
        HiddenVoLTEVoice = 118

        // Current last number 118 - Please update when adding new enum
    };
};

/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c SortColumn class represents the columns that can be used to sort contacts.
 *
 * @details You can use the @c SortColumn::Type enumeration to specify the columns that should be used to sort contacts. For
 * example, you can use a @c %SortColumn::Type enumeration value in @c ContactListFilters::setSortBy() to sort contacts by
 * first name, last name, or company name.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT SortColumn
{
public:
    /*!
     * @brief An enumeration of possible columns that can be used to sort contacts.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that contacts should be sorted by FirstName. This is the default value.
         *
         * @since BlackBerry 10.0.0
         */
        FirstName = 0,
        /*!
         * Indicates that contacts should be sorted by LastName.
         *
         * @since BlackBerry 10.0.0
         */
        LastName = 1,
        /*!
         * Indicates that contacts should be sorted by CompanyName.
         *
         * @since BlackBerry 10.0.0
         */
        CompanyName = 2
    };
};

/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c SortOrder class represents the sort order (ascending or descending) of a contact list or search response.
 *
 * @see ContactSearchFilters, ContactListFilters
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT SortOrder
{
public:
    /*!
     * @brief An enumeration of possible sort orders.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that contacts should be sorted in ascending order. This is the default value.
         *
         * @since BlackBerry 10.0.0
         */
        Ascending = 0,
        /*!
         * Indicates that contacts should be sorted in descending order.
         *
         * @since BlackBerry 10.0.0
         */
        Descending = 1
    };
};

/*!
 * @brief The @c SortSpecifier typedef represents a pair consisting of a @c SortColumn::Type value and a @c SortOrder::Type
 * value.
 *
 * @details Sort order and sort column are strongly related, and the @c %SortSpecifier typedef represents this
 * relationship.
 *
 * @since BlackBerry 10.0.0
 */
typedef QPair<SortColumn::Type, SortOrder::Type> SortSpecifier;

/*!
 * @brief The @c AnchorValueSpecifier typedef represents a pair consisting of a @c SortSpecifier value and a @c QString
 * value.
 *
 * @details The @c %AnchorValueSpecifier typedef is used in both the @c ContactListFilters and @c ContactSearchFilter classes,
 * and specifies a sort column and order, and offset the response by a certain anchor value. Here's an example of how to
 * use this typedef:
 *
 * @code
 * ContactService service;
 * QList<Contact> contacts;
 * ContactListFilters options;
 * options.setLimit(5);
 * AnchorValueSpecifier anchorValue;
 * anchorValue.first = SortSpecifier(SortColumn::FirstName, SortOrder::Ascending);
 * anchorValue.second = "b";
 * options.setSortAndAnchorBy(anchorValue);
 *
 * contacts = service.contacts(options);
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
typedef QPair<SortSpecifier, QString> AnchorValueSpecifier;

typedef QPair<ContactId, QList<int> > GroupMembershipSpecifier;

/*!
 * @brief The @c KindSubKindSpecifier typedef represents a pair consisting of an @c AttributeKind::Type value and a
 * @c AttributeSubKind::Type value.
 *
 * @details The @c %KindSubKindSpecifier typedef is used to specify a specific kind/sub-kind combination filter for
 * list and search queries.
 *
 * @see ContactListFilters::setHasKindSubKind(), ContactSearchFilters::setHasKindSubKind()
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
typedef QPair<AttributeKind::Type, AttributeSubKind::Type> KindSubKindSpecifier;


/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c SearchField class represents the fields that a @c ContactSearchFilters can apply to.
 *
 * @details You can use the @c SearchField::Type enumeration to specify which fields should be searched when using a
 * @c %ContactSearchFilters.
 *
 * @see ContactSearchFilters
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT SearchField
{
public:
    /*!
     * @brief An enumeration of possible fields to search.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that the search should apply to the FirstName field.
         *
         * @since BlackBerry 10.0.0
         */
        FirstName = 0,
        /*!
         * Indicates that the search should apply to the LastName field.
         *
         * @since BlackBerry 10.0.0
         */
        LastName = 1,
        /*!
         * Indicates that the search should apply to the CompanyName field.
         *
         * @since BlackBerry 10.0.0
         */
        CompanyName = 2,
        /*!
         * Indicates that the search should apply to the Phone field.
         *
         * @since BlackBerry 10.0.0
         */
        Phone = 3,
        /*!
         * Indicates that the search should apply to the Email field.
         *
         * @since BlackBerry 10.0.0
         */
        Email = 4,
        /*!
         * Indicates that the search should apply to the BBMPin field.
         *
         * @since BlackBerry 10.0.0
         */
        BBMPin = 5,
        /*!
         * Indicates that the search should apply to the LinkedIn field.
         *
         * @since BlackBerry 10.0.0
         */
        LinkedIn = 6,
        /*!
         * Indicates that the search should apply to the Twitter field.
         *
         * @since BlackBerry 10.0.0
         */
        Twitter = 7,
        /*!
         * Indicates that the search should apply to the VideoChat field.
         *
         * @since BlackBerry 10.0.0
         */
        VideoChat = 8,
        /*!
         * Indicates that the search should apply to the Facebook field.
         *
         * @since BlackBerry 10.0.0
         */
        Facebook = 9,
        /*!
         * Indicates that the search should apply to the VideoChatPin field.
         *
         * @since BlackBerry 10.0.0
         */
        VideoChatPin = 10,
        /*!
         * Indicates that the search should apply to the SinaWeibo field.
         *
         * @since BlackBerry 10.0.0
         */
        SinaWeibo = 11,

        /*!
         * Indicates that the search should apply to the ecoid field.
         *
         * @since BlackBerry 10.0.0
         */
        Ecoid = 12,

        /*!
         * Indicates that the search should apply to the BBM unique id field.
         *
         * @since BlackBerry 10.2.0
         */
        BBM = 13

    };
};

/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c SearchAutoCompleteField class represents the fields that a @c ContactAutoCompleteSearchFilters can apply to.
 *
 * @details You can use the @c SearchAutoCompleteField::Type enumeration to specify which fields should be searched when using a
 * @c %ContactAutoCompleteSearchFilters.
 *
 * @see ContactAutoCompleteSearchFilters
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT SearchAutoCompleteField
{
public:
    /*!
     * @brief An enumeration of possible fields to search.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that the auto-complete search should search by email.
         *
         * @since BlackBerry 10.0.0
         */
        Email = 0,
        /*!
         * Indicates that the auto-complete search should search by Twitter profile information.
         *
         * @since BlackBerry 10.0.0
         */
        Twitter = 1,
        /*!
         * Indicates that the auto-complete search should search by Facebook profile information.
         *
         * @since BlackBerry 10.0.0
         */
        Facebook = 2,
        /*!
         * Indicates that the auto-complete search should search by LinkedIn profile information.
         *
         * @since BlackBerry 10.0.0
         */
        LinkedIn = 3,
        /*!
         * Indicates that the auto-complete search should search by SinaWeibo profile information.
         *
         * @since BlackBerry 10.0.0
         */
        SinaWeibo = 4,
    };
};

/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c PerimeterStatus class represents the enterprise perimeter state.
 *
 * @details You can use the @c PerimeterStatus::Type enumeration to determine the state of the enterprise perimeter
 * on the device.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT PerimeterStatus
{
public:
    /*!
     * @brief An enumeration of possible enterprise perimeter states.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that the perimeter is inactive.
         *
         * @since BlackBerry 10.0.0
         */
        Inactive = 0,
        /*!
         * Indicates that the perimeter is unlocked.
         *
         * @since BlackBerry 10.0.0
         */
        UnLocked= 1,
        /*!
         * Indicates that the perimeter is locked.
         *
         * @since BlackBerry 10.0.0
         */
        Locked = 2,
        /*!
         * Indicates that the perimeter is hard locked.
         *
         * @since BlackBerry 10.2.0
         */
        HardLocked = 3
    };
};


/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c VCardPhotoEncoding class represents possible vCard photo encoding types.
 *
 * @details You can use the @c VCardPhotoEncoding::Type enumeration to determine the photo encoding on
 * a vCard.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT VCardPhotoEncoding
{
public:
    /*!
     * @brief An enumeration of possible vCard photo encoding.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * Indicates that the encoding type will have ENCODING=B set on the photo property.
         *
         * @since BlackBerry 10.0.0
         */
        B = 0,
        /*!
         * Indicates that the encoding type will have ENCODING=BASE64 set on the photo property.
         *
         * @since BlackBerry 10.0.0
         */
        BASE64 = 1
    };

};


/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c NameOrder class represents the orders that can be used for the contacts display name.
 *
 * @details You can use the @c NameOrder::Type enumeration to specify the order that should be used for contacts display name. For
 * example, you can use a @c %NameOrder::Type enumeration value in @c ContactListFilters::setDisplayNameOrder()
 * to change the display name returned for a contact with the first name, John and Last name, Doe to "Doe John" or "John Doe"
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT NameOrder
{
public:
    /*!
     * @brief An enumeration of possible name orders that can be set.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type
    {
        /*!
         * Indicates that name order should be "FirstName LastName" e.g. "John Doe"
         *
         * @since BlackBerry 10.3.0
         */
        FirstLast = 0,
        /*!
         * Indicates that name order should be "LastName FirstName" e.g. "Doe John"
         *
         * @since BlackBerry 10.3.0
         */
        LastFirst = 1
    };
};


/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c Activity class represents the PIM activity types that can be queried.
 *
 * @details For example, you can query for email activities, calendar events, phone calls, and
 * so on.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.1.0
 */
class BB_PIM_EXPORT Activity
{
public:
    /*!
     * @brief An enumeration of possible activity types.
     */
    enum Type
    {
        /*!
         * Indicates all email activities.
         *
         * @since BlackBerry 10.1.0
         */
        Email = 1,
        /*!
         * Indicates all calendar events.
         *
         * @since BlackBerry 10.1.0
         */
        CalendarEvent = 2,
        /*!
         * Indicates all phone calls.
         *
         * @since BlackBerry 10.1.0
         */
        PhoneCall = 4,
        /*!
         * Indicates all text messages.
         *
         * @since BlackBerry 10.1.0
         */
        TextMessage = 8,
        /*!
         * Indicates all BBM messages.
         *
         * @since BlackBerry 10.1.0
         */
        BBM = 16,
        /*!
         * Indicates all video chat messages.
         *
         * @since BlackBerry 10.1.0
         */
        VideoChat = 32,
        /*!
         * Indicates all social messages.
         *
         * @since BlackBerry 10.1.0
         */
        SocialMessage = 64,

        /*!
         * Indicates all activities.
         *
         * @since BlackBerry 10.1.0
         */
        All = 0xffffffffUL
    };
    Q_DECLARE_FLAGS(Types, Type)

    private:
        Activity();
        ~Activity();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Activity::Types)

/*!
 * @headerfile ContactConsts.hpp <bb/pim/contacts/ContactConsts>
 *
 * @brief The @c ContactType class represents the type of contact.
 *
 * @details For example, a Contact returned by the @c ContactService can be of type Contact or ContactGroup.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT ContactType{
public:
    /*!
    * @brief An enumeration of possible contact types.
    */
    enum Type
    {
        /*!
         * Indicates a regular contact
         *
         * @since BlackBerry 10.3.0
         */
        Contact = 0,
        /*!
         * Indicates a ContactGroup
         *
         * @since BlackBerry 10.3.0
         */
        ContactGroup = 1
    };
};

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTCONSTS_HPP

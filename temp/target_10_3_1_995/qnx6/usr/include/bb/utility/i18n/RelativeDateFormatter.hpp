/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_I18N_RELATIVEDATEFORMATTER_HPP
#define BB_UTILITY_I18N_RELATIVEDATEFORMATTER_HPP

#include <bb/utility/i18n/Global>
#include <bb/utility/i18n/RelativeDateFormat>
#include <bb/utility/i18n/ClockFormat>

#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

class QDateTime;
class QLocale;

namespace bb
{
namespace utility
{
namespace i18n
{

class RelativeDateFormatterPrivate;

/*!
 * @headerfile RelativeDateFormatter.hpp <bb/utility/i18n/RelativeDateFormatter>
 *
 * @brief Formats @c QDateTime objects relative to current date/time.
 *
 * @details A @c bb::utility::i18n::RelativeDateFormatter uses several ranges
 * of QDateTime offsets to provide an informative yet simple representation.
 * The supported types of @c bb::utility::i18n::RelativeDateFormatter objects are
 * enumerated by and summarized in @c bb::utility::i18n::RelativeDateFormat.
 *
 * @xmlonly
 * <qml>
 * <class register="yes" />
 * </qml>
 * <apigrouping group="Platform/Language"/>
 * <library name="bbutilityi18n"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_UTILITY_I18N_EXPORT RelativeDateFormatter : public QObject
{
    Q_OBJECT

    /*!
     * @brief The type of this relative date/time formatter.
     *
     * @details This is an init-only property. If your application needs
     * to format date/time in several relative formats, it is expected to
     * maintain several @c bb::utility::i18n::RelativeDateFormatter objects.
     *
     * @sa bb::utility::i18n::RelativeDateFormat
     *
     * @xmlonly
     * <qml>
     * <property name="type" readable="no" writable="init-only"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::utility::i18n::RelativeDateFormat::Type type READ type WRITE setType FINAL)

public:

    /*!
     * @brief Destroys this instance.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~RelativeDateFormatter();

    /*!
     * @brief Creates a relative date/time formatter of the supplied type.
     *
     * @note By default, all @c bb::utility::i18n::RelativeDateFormatter objects
     * start with the user's currently selected locale and clock format override.
     * The application is expected to call @c applyUserRegionLocale()
     * and/or @c setClockFormat(bb::utility::i18n::ClockFormat::Type) with
     * @c bb::utility::i18n::ClockFormat::ApplyUserFormat whenever the user changes these values.
     *
     * @param type The @c bb::utility::i18n::RelativeDateFormat::Type to apply to this formatter.
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit RelativeDateFormatter(bb::utility::i18n::RelativeDateFormat::Type type = bb::utility::i18n::RelativeDateFormat::TimeCritical, QObject * parent = 0);

    /*!
     * @brief Prints out a localized date/time to a string relative to the cached current time.
     *
     * @param dateTime A @c QDateTime object that should be printed.
     *
     * @return A @c QString with a formatted date and/or time.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE QString format(const QDateTime & dateTime)const;


    /*!
     * @brief Sets this formatter's reference time.
     *
     * @param anchorTime A custom @c QDateTime to relate future @c format(const QDateTime &)const calls to.
     *
     * @sa applyCurrentTimeAsAnchor()
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setAnchorTime(const QDateTime & anchorTime);

    /*!
     * @brief Updates this formatter with the current system date/time.
     *
     * @note The user of @c bb::utility::i18n::RelativeDateFormatter is expected to call
     * this function prior to calling @c format(const QDateTime &)const to ensure an accuracy.
     * The current system time is automatically cached at creation of the formatter.
     *
     * @details Applications filling out tables should call this function only once before each update,
     * and then call @c format(const QDateTime &)const on all the rows to optimize performance.
     *
     * @sa setAnchorTime(const QDateTime &)
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void applyCurrentTimeAsAnchor();


    /*!
     * @brief Updates this formatter with the currently selected region locale.
     *
     * @details The user of @c bb::utility::i18n::RelativeDateFormatter is expected to listen
     * and maintain their own @c bb::system::LocaleType::Region type of @c bb::system::LocaleHandler,
     * and call this function whenever the locale changes.
     *
     * @note Cascades QML users may listen to @c bb::cascades::LocaleHandler or the QML Retranslate plugin.
     *
     * @sa setLocale(const QLocale &)
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void applyUserRegionLocale();

    /*!
     * @brief Changes the locale used for formatting.
     *
     * @param locale A @c QLocale to use as the new locale.
     *
     * @sa @c applyUserRegionLocale()
     *
     * @since BlackBerry 10.2.0
     */
    void setLocale(const QLocale & locale);

    /*!
     * @brief Changes the clock format used for formatting.
     *
     * @details The @c bb::utility::i18n::ClockFormat::Type enum offers
     * the choice to use the currently selected user setting, the default
     * format in the current locale, or custom value.
     *
     * @note If the clock format was previously set to
     * @c bb::utility::i18n::ClockFormat::ApplyLocaleFormat,
     * changing the locale will not affect the actual clock format used to format time.
     *
     * @param format A @c bb::utility::i18n::ClockFormat to use as the new locale.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setClockFormat(bb::utility::i18n::ClockFormat::Type format);

Q_SIGNALS:

    /*!
     * @brief Emitted whenever this formatter changes.
     *
     * @details The application can register a slot to this signal that
     * calls @c format(const QDateTime &)const on all it's date/time values.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void changed();

//!@cond PRIVATE

protected:

    Q_SLOT void setClockFormat(int format);

private:

    QScopedPointer<RelativeDateFormatterPrivate> d_ptr;
    Q_DECLARE_PRIVATE(RelativeDateFormatter)
    Q_DISABLE_COPY(RelativeDateFormatter)

    // for the init-only property "type"
    bb::utility::i18n::RelativeDateFormat::Type type()const;
    void setType(bb::utility::i18n::RelativeDateFormat::Type type);

//!@endcond PRIVATE

}; // class

} // namespace
} // namespace
} // namespace

QML_DECLARE_TYPE(bb::utility::i18n::RelativeDateFormatter)

#endif  // _HPP

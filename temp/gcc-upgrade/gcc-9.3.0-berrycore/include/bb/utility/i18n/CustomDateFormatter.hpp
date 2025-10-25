/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_I18N_CUSTOMDATEFORMATTER_HPP
#define BB_UTILITY_I18N_CUSTOMDATEFORMATTER_HPP

#include <bb/utility/i18n/Global>

#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

class QDateTime;

namespace bb
{
namespace utility
{
namespace i18n
{

class CustomDateFormatterPrivate;

/*!
 * @headerfile CustomDateFormatter.hpp <bb/utility/i18n/CustomDateFormatter>
 *
 * @brief Formats @c QDateTime objects using skeleton patterns.
 *
 * @details A date/time format skeleton is a @c QString containing any arrangement of @c icu::SimpleDateFormat
 * pattern characters specified by the Internationalization Components for Unicode (ICU).
 * The table below also shows the Qt4 equivalencies for your convenience.
 * The passed in @c QString should only contain character sequences from the left column (ICU).
 *
 * Do not include any whitespace or punctuation. The formatter will automatically format using
 * the most appropriate date-time pattern for the current system settings.
 *
 * #### Supported characters:
 * An asterisk (*) in the left column indicates that this character may be repeated to pad the output with 0s.
 *
 * |  ICU  |     description    |  Qt4 |         US English example       |                   notes                         |
 * | ----- | ------------------ | ---- | -------------------------------- | ----------------------------------------------- |
 * |     G | era designator     |   AD |                               AD |                                                 |
 * |  GGGG | era designator     |      |                      Anno Domini |                                                 |
 * |     y | year               | yyyy |                             1996 | Can also use yyyy                               |
 * |    yy | 2-digit year       |   yy |                               96 | 00 through 99                                   |
 * |     Y | of year            |      |                             1997 | 3rd month of year 1997 <-> March 1996           |
 * |    YY | of 2-digit year    |      |                               97 | 00 through 99                                   |
 * |     u | extended year      |      |                             4601 | Based on region locale calendar                 |
 * |     U | cyclic year name   |      |                         ren-chen | Falls back to number (29) for many locales      |
 * |     Q | quarter            |      |                                2 | Use QQ to pad with 0s                           |
 * |   QQQ | quarter            |      |                               Q2 |                                                 |
 * |  QQQQ | quarter            |      |                      2nd quarter |                                                 |
 * |   qqq | standalone quarter |      |                               Q2 |                                                 |
 * |  qqqq | quarter            |      |                      2nd quarter |                                                 |
 * |     M | month in year      |    M |                                8 |                                                 |
 * |    MM | month in year      |   MM |                               08 |                                                 |
 * |   MMM | month in year      |  MMM |                              Aug |                                                 |
 * |  MMMM | month in year      | MMMM |                           August |                                                 |
 * |   LLL | standalone month   |      |                              Aug |                                                 |
 * |  LLLL | standalone month   |      |                           August |                                                 |
 * | *   w | week in year       |      |                               33 |                                                 |
 * | *   W | week in month      |      |                                3 |                                                 |
 * | *   F | weekday in month   |      |                                3 | i.e. 3rd Tuesday in August                      |
 * | *   g | Julian day         |      |                          2451370 |                                                 |
 * | *   D | day in year        |      |                              226 |                                                 |
 * | *   d | day in month       |    d |                                9 |                                                 |
 * |     e | day of week        |      |                                2 | Numeric: 1 through 7                            |
 * |    ee | day of week        |      |                               02 | Numeric: 01 through 07                          |
 * |     E | day of week        |  ddd |                              Tue |                                                 |
 * |  eeee | day of week        |      |                             Tues |                                                 |
 * |  EEEE | day of week        | dddd |                          Tuesday |                                                 |
 * |   ccc | standalone day     |      |                              Tue |                                                 |
 * |  cccc | standalone day     |      |                          Tuesday |                                                 |
 * | *   H | hour in day        |    h |                                0 | 0 through 23                                    |
 * | *   k | hour of day        |      |                               24 | 1 through 24; i.e. the 1st hour of the day      |
 * |     a | am/pm marker       |   AP |                               PM | Qt4 uses AP for AM/PM and ap for am/am          |
 * | *   h | hour of am/pm      |    h |                               12 | 1 through 12; Qt4 checks for presence of AP/ap  |
 * | *   K | hour in am/pm      |      |                                0 | 0 through 11                                    |
 * | *   m | minute in hour     |    m |                               30 |                                                 |
 * | *   s | second in minute   |    s |                               55 |                                                 |
 * |     S | decisecond         |      |                              9   | Tenths of the next second: 0 through 9          |
 * |    SS | centisecond        |      |                              97  | Hundredths of the next second: 00 through 99    |
 * |   SSS | millisecond        |  zzz |                              978 | Thousandths of the next second: 000 through 999 |
 * | *   A | ms in day          |      |                         69540000 |                                                 |
 * |     z | timezone           |      |                              PST |                                                 |
 * |  zzzz | timezone           |      |            Pacific Standard Time |                                                 |
 * |     Z | timezone           |      |                            -0800 | RFC 822                                         |
 * |  ZZZZ | timezone           |    t |                        GMT-08:00 |                                                 |
 * | ZZZZZ | timezone           |      |                           -08:00 | ISO 8601                                        |
 * |     v | timezone           |      |                               PT | Short wall (generic) time                       |
 * |  vvvv | timezone           |      |                     Pacific Time | Long wall (generic) time                        |
 * |     V | timezone           |      |                              PST |                                                 |
 * |  VVVV | timezone           |      | United States Time (Los Angeles) | Location                                        |
 *
 * ##### Sample skeleton patterns:
 *
 * | skeleton  |     US English      |       Catalan        |     Liechtenstein     |
 * | --------- | ------------------- | -------------------- | --------------------- |
 * | MMMMEEEEd | Tuesday, October 30 | dimarts 30 d'octubre | Dienstag, 30. Oktober |
 * | MMMMEd    | Tue, October 30     | dt. 30 d'octubre     | Di., 30. Oktober      |
 * | MMMEd     | Tue, Oct 30         | dt. 30 d'oct.        | Di., 30. Okt          |
 * | yMMMM     | October 2012        | octubre de 2012      | Oktober 2012          |
 * | MMMd      | Oct 30              | 30 d'oct.            | 30. Okt               |
 * | Ehm       | Tue 7:46 PM         | dt. 19.46            | Di. 19:46             |
 *
 *
 * @xmlonly
 * <qml>
 * <class register="yes" />
 * </qml>
 * <apigrouping group="Platform/Language"/>
 * <library name="bbutilityi18n"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_UTILITY_I18N_EXPORT CustomDateFormatter : public QObject
{
    Q_OBJECT

    /*!
     * @brief A collection of letter sequences used for parsing and formatting dates.
     *
     * @xmlonly
     * <qml>
     * <property name="skeleton" readable="no" writable="init-only"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString skeleton READ skeleton WRITE setSkeleton FINAL)

public:

    /*!
     * @brief Destroys this instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~CustomDateFormatter();

    /*!
     * @brief Creates a date/time formatter of the supplied skeleton type.
     *
     * @param skeleton The skeleton this object should format with.
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit CustomDateFormatter(const QString & skeleton = QString(), QObject * parent = 0);

    /*!
     * @brief Verifies if this formatter was created successfully.
     *
     * @return @c true if this @c DateFormatter is ready to use, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isValid() const;

    /*!
     * @brief Prints out date and time components formatted and localized according to the system settings.
     *
     * @param dateTime A @c QDateTime object that should be printed using this format.
     *
     * @return A @c QString with a localized and formatted date and time.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QString format(const QDateTime & dateTime) const;

    /*!
     * @brief Returns the skeleton used for parsing and formatting dates/time.
     *
     * @return The skeleton used for parsing and formatting dates/time.
     *
     * @since BlackBerry 10.0.0
     */
    QString skeleton() const;

    /*!
     * @brief Changes the skeleton used for parsing and formatting dates.
     *
     * @param skeleton A @c QString to use as the new skeleton.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setSkeleton(const QString & skeleton);

//!@cond PRIVATE

private:

    QScopedPointer<CustomDateFormatterPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(CustomDateFormatter)
    Q_DISABLE_COPY(CustomDateFormatter)

//!@endcond PRIVATE

}; // class

} // namespace
} // namespace
} // namespace

QML_DECLARE_TYPE(bb::utility::i18n::CustomDateFormatter)

#endif  // _HPP

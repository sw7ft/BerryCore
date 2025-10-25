/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PICKERS_CALENDAREVENTPICKER_HPP
#define BB_CASCADES_PICKERS_CALENDAREVENTPICKER_HPP

#include <bb/cascades/pickers/Global>
#include <bb/cascades/pickers/CalendarEventPickerError>
#include <bb/cascades/pickers/ICalendarConstants>
#include <bb/system/SecurityPerimeter>

#include <QObject>
#include <QByteArray>

namespace bb
{
namespace cascades
{
namespace pickers
{

class CalendarEventPickerPrivate;

/*!
 * @headerfile CalendarEventPicker.hpp <bb/cascades/pickers/CalendarEventPicker>
 *
 * @brief A picker for selecting a calendar event.
 *
 *
 * @details The @c %CalendarEventPicker is a full-screen card that allows the user to select a calendar event.
 *
 * When @c open() is called then one of the below scenarios will occur:
 *  @c canceled() signal will be emitted if the user has cancelled the selection
 *  @c error(bb::cascades::pickers::CalendarEventPickerError::Type error) signal will be emitted if an error occurs
 *  @c eventSelected(const QByteArray &vcsData) signal will be emitted if the user successfully selected an event.
 *
 * Permissions that are required in the bar descriptor of the calling application:
 *  @permissions @c access_pimdomain_calendars
 *
 * The following example demonstrates how to create a  @c %CalendarEventPicker :
 *
 * @code
 * CalendarEventPicker *calendarEventPicker = new CalendarEventPicker();
 * QObject::connect(calendarEventPicker, SIGNAL(eventSelected(const QByteArray &)), this, SLOT(onEventSelected(const QByteArray &)));
 * QObject::connect(calendarEventPicker, SIGNAL(canceled()), this, SLOT(onCanceled()));
 * QObject::connect(calendarEventPicker, SIGNAL(error(bb::cascades::pickers::CalendarEventPickerError::Type)),
 *  this, SLOT(onError(bb::cascades::pickers::CalendarEventPickerError::Type)));
 * calendarEventPicker->open();
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbcascadespickers"/>
 * @endxmlonly
 *
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT CalendarEventPicker : public QObject
{
    Q_OBJECT

public:

    /*!
     * @brief Constructs a @c CalendarEventPicker.
     *
     *@param parent The parent or 0. If not 0, the ownership of constructed @c %CalendarEventPicker will be transferred to the parent.
     *
     * @since BlackBerry 10.0.0
     */
    explicit CalendarEventPicker(QObject *parent = 0);

    /*!
     * @brief Destructs the @c %CalendarEventPicker.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~CalendarEventPicker();

    /*!
     * @brief Opens the @c %CalendarEventPicker.
     *
     * This will display the @c %CalendarEventPicker, allowing the user to perform the selection. Output is in iCal 1.0 format.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void open();

    /*!
     * @brief Opens the @c %CalendarEventPicker.
     *
     * This will display the @c %CalendarEventPicker, allowing the user to perform the selection.
     *
     * @param iCalVersion The version of the iCal file that the picker will output. Currently supports 1.0 (.vcs) and 2.0 (.ics)
     *
     * @since BlackBerry 10.1.0
     */
    Q_SLOT void open(bb::cascades::pickers::ICalendarConstants::Version iCalVersion);

    /*!
     * @brief Closes the picker.
     *
     * Use this only when the user's input is no longer needed. Normally, the picker will close automatically as soon the user completes the selection.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void close();

    /*!
     * @brief Sets the security perimeter in which @c %CalendarEventPicker should be invoked.
     *
     * Only required for hybrid applications using this api.
     *
     * @param perimeter Security perimeter to use for @c %CalendarEventPicker invoke.
     *
     * @since BlackBerry 10.1.0
     */
    void setPerimeter(bb::system::SecurityPerimeter::Type perimeter);

Q_SIGNALS:

    /*!
     * @brief Emitted when the cancel button is clicked in the @c %CalendarEventPicker.
     *
     * @since BlackBerry 10.0.0
     */
    void canceled();

    /*!
     * @brief Emitted when launching the picker fails.
     *
     * @since BlackBerry 10.0.0
     */
    void error(bb::cascades::pickers::CalendarEventPickerError::Type error);

    /*!
     * @brief Emitted when an event is selected.
     *
     * @param vcsData The @c QByteArray containing the vcs representation of the event.
     *
     * @since BlackBerry 10.0.0
     */
    void eventSelected(const QByteArray &vcsData);

private:
    //! @cond PRIVATE
    Q_DECLARE_PRIVATE(CalendarEventPicker)
    Q_DISABLE_COPY(CalendarEventPicker)
    CalendarEventPickerPrivate *d_ptr;
    //! @endcond PRIVATE
};

} /* namespace pickers */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_PICKERS_CALENDAREVENTPICKER_HPP */

/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_STATUSREPORT_HPP
#define BB_PIM_MESSAGE_STATUSREPORT_HPP

#include <bb/pim/Global>
#include <bb/pim/message/StatusReportType>

#include <QString>
#include <QDateTime>
#include <QSharedData>

namespace bb {
namespace pim {
namespace message {

class StatusReportPrivate;

/*!
 * @brief The @c StatusReport class represents status information for a @c Message.
 * 
 * @details A @c %StatusReport is associated with a particular recipient of a @c %Message.
 * You can retrieve the status reports for each recipient of a @c %Message by
 * calling @c Message::statusReports(), and you can use this information to check the
 * delivery status for each recipient of the message.
 * 
 * @see Message
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT StatusReport
{
public:
    /*!
     * @brief Constructs a new @c StatusReport.
     *
     * @since BlackBerry 10.0.0
     */
    StatusReport();
    
    /*!
     * @brief Destroys this @c StatusReport.
     *
     * @since BlackBerry 10.0.0
     */
    ~StatusReport();
    
    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c StatusReport containing exactly the same values as
     * the provided @c %StatusReport.
     * 
     * @param other The @c %StatusReport to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    StatusReport(const StatusReport &other);

    /*!
     * @brief Retrieves the status value of this @c StatusReport.
     * 
     * @return The status value.
     *
     * @since BlackBerry 10.0.0
     */
    int status() const;
    
    /*!
     * @brief Sets the status value of this @c StatusReport.
     * 
     * @param status The status value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setStatus(int status);

    /*!
     * @brief Retrieves the type of this @c StatusReport.
     * 
     * @details This function returns the type as an enumeration value in the
     * @c StatusReportType::Type enumeration, and can include types such as
     * read report and delivery report.
     * 
     * @return The status report type.
     *
     * @since BlackBerry 10.0.0
     */
    StatusReportType::Type type() const;
    
    /*!
     * @brief Sets the type of this @c StatusReport.
     * 
     * @param type The status report type to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setType(StatusReportType::Type type);

    /*!
     * @brief Retrieves the date of this @c StatusReport.
     * 
     * @return The status report date.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime date() const;
    
    /*!
     * @brief Sets the date of this @c StatusReport.
     * 
     * @param date The date to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setDate(const QDateTime &date);

    /*!
     * @brief Retrieves the email address of the recipient that this @c StatusReport
     * is associated with.
     *
     * @return The email address of the recipient.
     *
     * @since BlackBerry 10.0.0
     */
    QString address() const;
    
    /*!
     * @brief Sets the email address of the recipient that this @c StatusReport is
     * associated with.
     * 
     * @param address The email address to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setAddress(const QString &address);

private:
    QSharedDataPointer<StatusReportPrivate> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif /* BB_PIM_MESSAGE_STATUSREPORT_HPP_ */

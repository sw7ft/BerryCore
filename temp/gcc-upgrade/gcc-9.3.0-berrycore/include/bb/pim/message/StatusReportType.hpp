/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_STATUSREPORTTYPE_HPP
#define BB_PIM_STATUSREPORTTYPE_HPP

#include <bb/pim/Global>

#include <QMetaType>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile StatusReportType.hpp <bb/pim/message/StatusReportType>
 *
 * @brief The @c StatusReportType class includes possible status types for a message status
 * report.
 * 
 * @details You can retrieve a list of status reports for a @c Message by calling
 * @c Message::statusReports(). Each report has a type, such as a read report or delivery
 * report.
 * 
 * @see StatusReport, Message
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT StatusReportType
{
public:
    /*!
     * @brief An enumeration of supported status report types.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the status report is invalid.
         *
         * @since BlackBerry 10.2.0
         */
        Invalid = -1,
        /*!
         * @brief Indicates that the status report is a read report.
         *
         * @since BlackBerry 10.0.0
         */
        ReadReport = 0,
        /*!
         * @brief Indicates that the status report is a delivery report.
         *
         * @since BlackBerry 10.0.0
         */
        DeliveryReport = 1,
        /*!
         * @brief Indicates that the status report is an error report.
         *
         * @since BlackBerry 10.0.0
         */
        ErrorReport = 2
    };

private:
    /*! @cond PRIVATE */
    StatusReportType();
    ~StatusReportType();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::StatusReportType::Type)

#endif // BB_PIM_STATUSREPORTTYPE_HPP

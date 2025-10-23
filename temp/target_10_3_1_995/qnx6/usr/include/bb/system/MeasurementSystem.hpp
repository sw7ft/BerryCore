/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_MEASUREMENTSYSTEM_HPP
#define BB_SYSTEM_MEASUREMENTSYSTEM_HPP

#include <bb/system/Global>

#include <QObject>
#include <QLocale>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile MeasurementSystem.hpp <bb/system/MeasurementSystem>
 *
 * @brief Indicates the system of measurement for the current locale.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT MeasurementSystem
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief Indicates the system of measurement for the current locale.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief The metric measurement system.
         *
         * @since BlackBerry 10.0.0
         */
        Metric = QLocale::MetricSystem,
        
        /*!
         * @brief The imperial measurement system.
         *
         * @since BlackBerry 10.0.0
         */
        Imperial = QLocale::ImperialSystem
    };

private:
//!@cond PRIVATE
    MeasurementSystem();
    ~MeasurementSystem();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::MeasurementSystem)
#endif // BB_SYSTEM_MEASUREMENTSYSTEM_HPP

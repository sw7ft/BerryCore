/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_LOCALEHANDLER_HPP
#define BB_SYSTEM_LOCALEHANDLER_HPP

#include <bb/system/Global>
#include <bb/system/LocaleType>
#include <bb/system/MeasurementSystem>

#include <QLocale>
#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class LocaleHandlerPrivate;

/*!
 * @headerfile LocaleHandler.hpp <bb/system/LocaleHandler>
 *
 * @brief Queries and listens for changes to system locales.
 *
 * When creating a @c LocaleHandler, you can specify the type of changes to listen for using
 * a @c LocaleType. @c LocalType::Region is used for listening to changes to
 * regional formatting, such as currency, date and time, etc. @c LocalType::Messages is used for handling changes to
 * strings as a result of localization.
 *
 * @xmlonly
 * <apigrouping group="Platform/Language"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT LocaleHandler : public QObject
{
    Q_OBJECT

    /*!
     * @brief A property that allows string parameters to automatically retranslate.
     *
     * Here's an example of how to listen to region changes and automatically update a @c Label with
     * the new currency format.
     *
     * app.hpp:
     * @code
     * class App : public QObject {
     *     Q_OBJECT
     * public:
     *     Q_INVOKABLE QString formatCurrency (float value) {
     *         return region->locale().toCurrencyString( value );
     *     }
     *     App() : region( new bb::system::LocaleHandler( 
     *             bb::system::LocaleType::Region, this ) ) {
     *         QmlDocument *qml = QmlDocument::create( "main.qml" );
     *         qml->setContextProperty( "app", this );
     *         qml->setContextProperty( "region", region ) );
     *         AbstractPane *root = qml->createRootNode<AbstractPane>();
     *         Application::instance()->setScene( root );
     *     }
     * private:
     *     bb::system::LocaleHandler * region;
     * };
     * @endcode
     *
     * main.qml:
     * @code
     * Page {
     *   Container {
     *     Label {
     *       text: app.formatCurrency( parseFloat("34.56") ) + 
     *             region.forceUpdateOnChange
     *     }
     *   }
     * }
     * @endcode
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString forceUpdateOnChange READ emptyString NOTIFY changed FINAL)

    /*!
     * @brief The measurement system currently in use in the system.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::system::MeasurementSystem::Type measurementSystem READ measurementSystem NOTIFY measurementSystemChanged FINAL );

public:

    /*!
     * @brief Creates a locale handler for the supplied @c LocaleType.
     *
     * @param type The type of locale this object should monitor.
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit LocaleHandler(LocaleType::Type type = LocaleType::Messages, QObject * parent = 0);

    /*!
     * @brief Destroys this @c LocaleHandler instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~LocaleHandler();

    //!@cond PRIVATE
    /*!
     * @brief Returns the Qt representation of the currently selected locale.
     *
     * @return The @c QtLocale object representing the currently selected locale.
     *
     * @note Deprecated in favour of the const version.
     */
    QLocale locale();
    //!@endcond

    /*!
     * @brief Returns the Qt representation of the currently selected locale.
     *
     * @return The @c QtLocale object representing the currently selected locale.
     *
     * @since BlackBerry 10.0.0
     */
    QLocale locale() const;

    /*!
     * @brief Returns the measurement system currently in use on the system.
     *
     * @return One of @c MeasurementSystem::Metric or @c MeasurementSystem::Imperial
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::MeasurementSystem::Type measurementSystem() const;

Q_SIGNALS:

    /*!
     * @brief Emitted when the locale type associated with this object changes.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
     void changed();

     /*!
      * @brief Emitted when the unit of measurement system is changed.
      *
      * @param measurementSystem The system of measurement currently in use. One of @c MeasurementSystem::Metric or @c MeasurementSystem::Imperial.
      *
      * @ingroup Signals
      *
      * @since BlackBerry 10.0.0
      */
     void measurementSystemChanged( bb::system::MeasurementSystem::Type measurementSystem );

protected:
//!@cond PRIVATE
    Q_SIGNAL void measurementSystemChanged( int measurementSystem );
//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(LocaleHandler);
    Q_DISABLE_COPY(LocaleHandler);

    const QString emptyString(); // returns empty string for the QML property trick

    QScopedPointer<LocaleHandlerPrivate> const d_ptr;
//!@endcond

}; // class

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::LocaleHandler)

#endif  // BB_SYSTEM_LOCALEHANDLER_HPP

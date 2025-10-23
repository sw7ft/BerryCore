/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_SDCARDINFO_HPP
#define BB_DEVICE_SDCARDINFO_HPP

#include <bb/device/SdCardState>
#include <bb/device/SdCardActivity>

#include <bb/device/Global>

#include <QObject>
#include <QScopedPointer>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class SdCardInfoPrivate;

/*!
 * @headerfile SdCardInfo.hpp <bb/device/SdCardInfo>
 *
 * @brief A class that provides information about the state of the SD card.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT SdCardInfo : public QObject
{
    Q_OBJECT

    /*!
     * @brief The state of the SD card.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::device::SdCardState::Type state READ state NOTIFY stateChanged FINAL )

    /*!
     * @brief Whether the SD card is performing an operation or not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::device::SdCardActivity::Type activity READ activity NOTIFY activityChanged FINAL )

public:

    /*!
     * @brief Constructs an @c SdCardInfo object.
     *
     * @details Constructs an @c SdCardInfo object that can be used to retrieve 
     *          information about the SD card.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting 
     *               this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SdCardInfo(QObject * parent = 0);

    /*!
     * @brief Destroys an @c SdCardInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SdCardInfo();

    /*!
     * @brief The state of the SD card.
     *
     * @return The current state of the SD card. See @c bb::device::SdCardState for
     *         the list of possible states.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::SdCardState::Type state() const;

    /*!
     * @brief Whether the SD card is currently performing an activity or not.
     *
     * @return Returns whether or not the SD card is currently busy. See 
     *         @c bb::device::SdCardActivity for a list of possible states.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::SdCardActivity::Type activity() const;

Q_SIGNALS:
    /*!
     * @brief Indicates that the state of the SD card has changed.
     *
     * @param newState The new state of the SD card.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void stateChanged( bb::device::SdCardState::Type newState );

    /*!
     * @brief Indicates that the activity state of the SD card has changed.
     *
     * @param newActivity The new activity state of the SD card.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void activityChanged( bb::device::SdCardActivity::Type newActivity );

protected:
//!@cond PRIVATE
    Q_SIGNAL void stateChanged( int newState );

    Q_SIGNAL void activityChanged( int newActivity );
//!@endcond

private:
    //!@cond PRIVATE
    SdCardInfoPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(SdCardInfo)
    Q_DISABLE_COPY(SdCardInfo)
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::SdCardInfo)
#endif // BB_DEVICE_SDCARDINFO_HPP

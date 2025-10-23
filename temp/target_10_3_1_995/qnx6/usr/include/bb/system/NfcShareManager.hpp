/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHAREMANAGER_HPP
#define BB_SYSTEM_NFCSHAREMANAGER_HPP

#include <bb/system/Global>

#include <bb/system/NfcShareSetContentError>
#include <bb/system/NfcShareSuccess>
#include <bb/system/NfcShareError>
#include <bb/system/NfcShareMode>
#include <bb/system/NfcShareStartTransferMode>
#include <bb/system/NfcShareHandoverTransport>
#include <bb/system/NfcShareFilesContent>
#include <bb/system/NfcShareDataContent>

#include <QObject>

namespace bb
{
namespace system
{

class NfcShareManagerPrivate;

/*!
 * @headerfile NfcShareManager.hpp <bb/system/NfcShareManager>
 *
 * @brief The @c NfcShareManager class manages all interactions related to sharing files and data over NFC.
 *
 * @details A client process can share content (data or files) using NFC technology by tapping
 *          an NFC-enabled device or an NFC tag. The @c NfcShareManager class is the entry point to access this
 *          functionality.
 *
 *          To share content using NFC, the client process must do the following:
 *           -# Specify the type of content to be shared and "Start Transfer" mode by calling @c setShareMode() with the
 *              desired content type.
 *           -# Specify the content to be shared by making a successful call to one of
 *              - @c setShareContent(const bb::system::NfcShareFilesContent&) to share a file, or
 *              - @c setShareContent(const bb::system::NfcShareDataContent&) to share data.
 *              .
 *              Note that the content type must match the type set in the preceding call to @c setShareMode().
 *           -# Tap the device with another NFC-enabled device or an NFC tag.
 *
 *          The client process can call @c setShareContent() as many times as needed provided that the content being set
 *          matches the current content type set in a preceding call to @c setShareMode().
 *
 *          When sharing files, the client process can call @c setShareContent() even after tapping another NFC-enabled
 *          device. To enable this functionality, the client process should first call the @c setShareMode(bb::system::NfcShareMode::File,
 *          bb::system::NfcShareStartTransferMode::OnDemand) method.
 *
 *          The client process can change the content type and "Start Transfer" mode at any time by calling @c setShareMode()
 *          with a new content type and a new "Start Transfer" mode. If the new content type differs from the previous content type,
 *          any content that was previously set by a call to @c setShareContent() will be cleared. If the "Start Transfer" mode was
 *          set to @c NfcShareStartTransferMode::OnTap, new content must be set before any sharing can take place.
 *
 *          The client application can reset both the content type and the content to be shared using the @c reset() method.
 *
 *          The status of any sharing operations is obtained using the signals @c finished() and @c error(). The @c finished()
 *          signal is emitted when the operation is successful. The @c error() signal is emitted when the operation fails.
 *          Both signals include a parameter providing more detailed information.
 *
 *          @note You should create only one instance of @c %NfcShareManger per application. Each additional instance that
 *          you create receives events that are identical to the original, making their creation redundant. In addition, there
 *          are cases where a @c %NfcShareManger might try to access an event that has already been managed exclusively
 *          by another instance of the @c %NfcShareManger, which can cause the application to crash.
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */

class BB_SYSTEM_EXPORT NfcShareManager: public QObject
{
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c NfcShareManager object.
     *
     * You should create only one instance of @c %NfcShareManger per application. Each additional instance that
     * you create receives events that are identical to the original, making their creation redundant. In addition, there
     * are cases where an @c %NfcShareManger might try to access an event that has already been managed exclusively
     * by another instance of the @c %NfcShareManger, which can cause the application to crash.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit NfcShareManager(QObject *parent = 0);

    /*!
     * @brief Destroys this @c NfcShareManager object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~NfcShareManager();

    /*!
     * @brief Specifies file content to be shared over NFC.
     *
     * @details The current share mode must be set to @c NfcShareMode::File for this
     * method to complete successfully.
     *
     * The supplied request must contain at least one file in its list of URLs.
     *
     * @param request A description of the file content to share.
     * @return Returns the result of the operation. See @c NfcShareSetContentError for the list
     * of values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::NfcShareSetContentError::Type setShareContent(const NfcShareFilesContent &request);

    /*!
     * @brief Specifies the data content to be shared over NFC.
     *
     * @details The current share mode must be set to @c NfcShareMode::Data for this
     * method to complete successfully.
     *
     * @param request A description of the data content to share.
     * @return Returns the result of the operation. See @c NfcShareSetContentError for the list
     * of values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::NfcShareSetContentError::Type setShareContent(const NfcShareDataContent &request);

    /*!
     * @brief Retrieves the current share mode for this NFC manager.
     *
     * @return Returns the current NFC share mode. See @c NfcShareMode for the list of share modes.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::NfcShareMode::Type shareMode() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the share mode for this NFC manager changes.
     *
     *  @param mode The new share mode. See @c NfcShareMode for a list of share modes.
     *
     * @since BlackBerry 10.0.0
     */
    void shareModeChanged(bb::system::NfcShareMode::Type mode);

    /*!
     * @brief Emitted when content is successfully shared using NFC.
     *
     * @param result More specific information on the successfully completed operation. See @c NfcShareSuccess
     * for a list of values.
     *
     * @since BlackBerry 10.0.0
     */
    void finished(bb::system::NfcShareSuccess::Type result);

    /*!
     * @brief Emitted when an attempt to share content using NFC fails.
     *
     * @param error More specific information about the failure. See @c NfcShareError for a list
     * of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    void error(bb::system::NfcShareError::Type error);

    /*!
     * @brief A connection handover was successfully established.
     *
     * @details This signal is only sent when the "Start Transfer" mode from the
     * @c NfcShareManager::setShareMode() method is set to @c NfcShareStartTransferMode::OnDemand.
     * This signal indicates that the content to share can be set, and that the file transfer can be initiated by calling the
     * @c NfcShareManager::startTransfer() method.
     *
     * @note Currently this signal is only emitted when share mode is set to @c NfcShareMode::File and the
     * "Start Transfer" mode is set to @c NfcShareStartTransferMode::OnDemand in the
     * @c NfcShareManager::setShareMode() method.
     *
     * @since BlackBerry 10.2.0
     */
    void targetAcquired();

    /*!
     * @brief A target that was acquired during the last successful handover is discarded.
     *
     * @details This signal is only sent after developer calls @c NfcShareManager::cancelTarget() method. 
     * This signal indicates that there are no more targets to transfer data or files to, and any attempt 
     * to initiate a file transfer by calling the @c NfcShareManager::startTransfer() method will fail 
     * with a @c NfcShareError::NoTransferTarget error.
     *
     * @since BlackBerry 10.2.0
     */
    void targetCancelled();


public Q_SLOTS:

    /*!
     * @brief Changes the share mode for this NFC manager.
     *
     * @details If the new mode is different than the previous mode, any content that was set by
     * a previous call to the @c setShareContent() method is cleared. If data or file sharing is in progress,
     * an attempt to change the Share Mode will fail, and the NFC Share Manager will deliver a 
     * @c NfcShareError::TransferInProgress error.
     *
     * @note If this method is called, the "Start Transfer" mode is set to @c NfcShareStartTransferMode::OnTap
     * by default.
     *
     * @param method The new share mode for this manager. See @c NfcShareMode for
     * the list of share modes.
     *
     * @note When handover transports are not specified, the most appropriate order of transports available will 
     * be used based on the payload that the shared content contains at the moment a tap occurs.
     * 
     * @since BlackBerry 10.0.0
     */
    void setShareMode(bb::system::NfcShareMode::Type method);

    /*!
     * @brief Changes the share mode for this NFC manager.
     *
     * @details If the mode is being switched between different "File" and "Data" modes, any content
     * that was set by a previous call to the @c setShareContent() method is cleared. If data or file sharing is in progress,
     * an attempt to change the Share Mode and/or the "Transfer On Tap" setting will have no effect, and the NFC Share Manager
     * will deliver a @c NfcShareError::TransferInProgress error.
     *
     * @param method The new share mode for this manager. See @c NfcShareMode for
     * a list of share modes.
     *
     * @param transferMode Specifies "Start Transfer" mode for this NFC manager for a given Share Mode.
     * When this option is set to @c NfcShareStartTransferMode::OnTap, the share content being set by
     * @c NfcShareManager::setShareContent() will be shared with the device being tapped
     * as soon as tap happens. When the "Start Transfer" mode is set to @c NfcShareStartTransferMode::OnDemand,
     * the share content WILL NOT be transferred to the device being tapped until the @c NfcShareManager::startTransfer()
     * method is called. This option allows content to be prepared (or set) for sharing AFTER the tap occurs. 
     * Currently, the @c NfcShareStartTransferMode::OnDemand option is only supported for files.
     *
     * @note When handover transports are not specified, the most appropriate order of transports available will be used based
     * on the payload that the shared content contains at the moment a tap occurs.
     *
     * @since BlackBerry 10.2.0
     */
    void setShareMode(bb::system::NfcShareMode::Type method,
                      bb::system::NfcShareStartTransferMode::Type transferMode);

    /*!
     * @brief Changes the share mode for this NFC manager.
     *
     * @details If the mode is being switched between different "File" and "Data" modes, any content
     * that was set by a previous call to the @c setShareContent() method is cleared. If data or file sharing is in progress,
     * an attempt to change the Share Mode and/or the "Transfer On Tap" setting will have no effect, and the NFC Share Manager
     * will deliver a @c NfcShareError::TransferInProgress error.
     *
     * @param method The new share mode for this manager. See @c NfcShareMode for
     * the list of share modes.
     *
     * @param transferMode Specifies the "Start Transfer" mode for this NFC manager, for a given Share Mode.
     * When this option is set to @c NfcShareStartTransferMode::OnTap, the share content being set by the
     * @c NfcShareManager::setShareContent() method will be shared with the device being tapped
     * as soon as the tap happens. When the "Start Transfer" mode is set to @c NfcShareStartTransferMode::OnDemand,
     * the share content WILL NOT be transferred to the device being tapped until the @c NfcShareManager::startTransfer()
     * method is called. This option allows content to be prepared (or set) for sharing AFTER the tap occurs.
     * Currently, @c NfcShareStartTransferMode::OnDemand option is only supported for files.
     *
     * @param transports Specifies the list of handover transports that should be used during the handover negotiation. 
     * The handover transports are listed in priority sequence. This means that the transport listed first will be used 
     * as the most preferred transport during the handover negotiation process. If this transport fails, there will be 
     * an attempt to use the second transport specified in this list etc. This process will continue until all one of the 
     * handover transports listed succeeds.
     *
     * @since BlackBerry 10.2.0
     */
    void setShareMode(bb::system::NfcShareMode::Type method,
                      bb::system::NfcShareStartTransferMode::Type transferMode,
                      const QList<bb::system::NfcShareHandoverTransport::Type>& transports);

    /*!
     * @brief Triggers the transfer of the shared content when the "Start Transfer" mode was previously set to @c NfcShareStartTransferMode::OnDemand.
     *
     * @details Triggers the transfer of the shared content, when the "Start Transfer" mode is set to @c NfcShareStartTransferMode::OnDemand.
     * As with the @c NfcShareManager::setShareMode() method, the result of this call is obtained using the
     * signals @c finished() and @c error(). You should not be calling the @c NfcShareManager::startTransfer() method more than
     * once for every @c NfcShareSuccess::TargetAcquired signal received, when the "Start Transfer" mode is set to
     * @c NfcShareStartTransferMode::OnDemand. Currently, only the file transfer is supported. If data or file sharing is in progress, an
     * attempt to call this method will result in a @c NfcShareError::TransferInProgress error
     * being delivered over the @c NfcShareError::error() signal.
     *
     * @note Calling this method 20 seconds after the tap has occurred will cause the transfer to fail. This is because handover
     * negotiation results between two devices will have already expired. In this case, the users must tap their devices again.
     *
     * @since BlackBerry 10.2.0
     */
    void startTransfer();

    /*!
     * @brief Cancels the target that was acquired as a result of the last successful handover.
     *
     * @details Discards the target that was acquired as a result of the last successful handover. This method should be used you have no
     * intention to start a transfer to the recently acquired target. Cancellation of the target will result in clearing (resetting) the target acquired
     * as result of the latest tap.
     * You should not be calling the @c NfcShareManager::cancelTransfer() method more than
     * once for every @c NfcShareSuccess::TargetAcquired signal received, when the "Start Transfer" mode is set to
     * @c NfcShareStartTransferMode::OnDemand. This method will not cancel the target if the transfer is already in progress.
     * The targetCancelled() signal is emitted when this command is successfully executed.
     *
     * @since BlackBerry 10.2.0
     */
    void cancelTarget();

    /*!
     * @brief Resets the state of this NFC manager.
     *
     * @details The share mode is reset to @c NfcShareMode::Disabled. Any content set by a call
     * to the @c setShareContent() method is cleared. The target will also be cleared however no 
     * @c targetCancelled() signal is emitted.
     *
     * @since BlackBerry 10.0.0
     */
    void reset();

private:
//!@cond PRIVATE
    QScopedPointer<NfcShareManagerPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(NfcShareManager)
    Q_DISABLE_COPY(NfcShareManager)
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHAREMANAGER_HPP */

/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

/**
 * @file btopp.h
 *
 * @brief Functions, enumerations, and structures for the Bluetooth Object Push
 *        Profile (OPP) library.
 *
 *        OPP enables file transfer between Bluetooth devices. These APIs allow
 *        you to send one or more files to a paired Bluetooth enabled device
 *        that supports OPP.
 *
 */

#ifndef BTOPP_H_

#define BTOPP_H_

/**
 * Bluetooth OPP API version.
 * For example, the value @c 0x00011000 translates to 0001.10.00 or v1.1.0.
 */
#define BT_OPP_VERSION  0x00011000

/**
 * Possible reasons for cancellation of an Object Push Profile (OPP) operation.
 */
typedef enum {

    /**
     * The remote device is not available.
     */
    BT_OPP_DEVICE_NOT_AVAILABLE                     = 0x00,

    /**
     * @deprecated
     * Original alternate spelling of available.  Use @c BT_OPP_DEVICE_NOT_AVAILABLE instead.
     */
    BT_OPP_DEVICE_NOT_AVAIABLE                     = 0x00,

    /**
     * The transfer was cancelled.
     */
    BT_OPP_TRANSFER_CANCELLED                     = 0x01,

    /**
     * Unable to find the OPP server on the remote device.
     */
    BT_OPP_FAILED_TO_FIND_SERVICE                 = 0x02,

    /**
     * The transfer was interrupted.
     */
    BT_OPP_TRANSFER_INTERRUPTED                   = 0x03,

} bt_opp_reason_t;

/**
 * The callback prototype to indicate the amount of data transmitted to the
 * remote device.
 *
 * @param bdaddr The address of the Bluetooth-enabled device the file was
 *               transfered to.
 * @param sent   The number of bytes sent to the remote device.
 * @param total  The total number of bytes to be sent to the remote device.
  */
typedef void (*bt_opp_update_cb) (const char *bdaddr, uint32_t sent, uint32_t total);

/**
 * The callback prototype to indicate that the transfer has been completed.
 *
 * @param bdaddr The address of the Bluetooth-enabled device the file was
 *               transfered to.
 */
typedef void (*bt_opp_complete_cb) (const char *bdaddr);

/**
 * The callback prototype to indicate that the transfer was cancelled before
 * it was completed.
 *
 * @param bdaddr The address of the Bluetooth-enabled device the file was
 *               transfered to.
 * @param reason The reason why the transfer was cancelled.
 */
typedef void (*bt_opp_cancelled_cb) (const char *bdaddr, bt_opp_reason_t reason);


/**
 * A structure that contains the list of callbacks to be used for OPP transfer
 */
typedef struct {
    /**
     * The callback that indicates that data has been transfered.
     */
    bt_opp_update_cb update;
    /**
     * The callback that indicates that a transfer has been completed.
     */
    bt_opp_complete_cb complete;
    /**
     * The callback that indicates that a transfer has been cancelled.
     */
    bt_opp_cancelled_cb cancelled;
} bt_opp_callbacks_t;

__BEGIN_DECLS

/**
 * @brief Initialize the Bluetooth Object Push Profile (OPP) library and
 *        allocate the required resources for the library
 * @details This function must be called before you call any other functions
 *          in this file. A corresponding call to the @c bt_opp_deinit()
 *          function must be made when you have completed using functionality
 *          from this file.
 *
 * @param callbacks A list of callback functions that are invoked during an OPP
 *                  transfer.
 * @return @c 0 is returned upon success, @c -1 with the @c errno set otherwise.
 *         Any @c errno value other than the following indicates that a system
 *         error has occurred:
 *         - @c EBUSY: @c bt_opp_init() has already been called.
 *         - @c ENOMEM: There was insufficient memory to allocate required
 *                      structures.
 */
int bt_opp_init( bt_opp_callbacks_t *callbacks );

/**
 * @brief Deallocate resources that were allocated to handle Object Push Profile (OPP) requests
 * @details This function also disables functionality that was initialized when
 *          the @c bt_opp_init() function was called. You must call this function
 *          when you have completed using functionality from this file or
 *          before your application exits.
 */
void bt_opp_deinit( );

/**
 * @brief Send a file to a Bluetooth enabled device
 * @details This function initiates the sending of a single file to a remote
 *          device. It will trigger the send operation, but does not wait until
 *          the operation is completed.  Updates on the transfer progress will
 *          be provided through the callbacks.
 *
 * @param remote_device_addr The Bluetooth MAC address of the remote device,
 *                           including the terminating NULL character. For
 *                           example, <tt>00:00:00:00:00:00\0</tt>.
 * @param filename The complete NULL-terminated path of the file you wish to
 *                 send.
 * @return @c 0 is returned upon successfully starting transfer, @c -1 with the
 *         @c errno set otherwise. Any @c errno value other than the following
 *         indicates that a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device_addr
 *                      or @c filename.
 *         - @c EBUSY:  A transfer to this device is already in progress.
 *         - @c EAGAIN: The stack is currently busy. You can try again.
 *         - @c ENXIO: The remote device does not support the Object Push Profile.
 */
int bt_opp_send_file( const char *remote_device_addr, const char *filename );

/**
 * @brief Send multiple files to a Bluetooth enabled device
 * @details This function initiates the sending of a list of files to a remote
 *          device. It will trigger the send operation, but does not wait until
 *          the operation is completed.  Updates on the transfer progress will
 *          be provided through the callbacks.
 *
 * @param remote_device_addr The Bluetooth MAC address of the remote device,
 *                           including the terminating NULL character. For
 *                           example, <tt>00:00:00:00:00:00\0</tt>.
 * @param filelist An array of NULL-terminated filename strings that you wish to
 *                 send.
 * @param filelist_len The number of entries in @c filelist.
 * @return @c 0 is returned upon successfully starting transfer, @c -1 with the
 *         @c errno set otherwise. Any @c errno value other than the following
 *         indicates that a system error has occurred:
 *         - @c EINVAL: An invalid value was passed in for @c remote_device_addr
 *                      or @c filename.
 *         - @c EBUSY:  A transfer to this device is already in progress.
 *         - @c EAGAIN: The stack is currently busy. You can try again.
 *         - @c ENXIO: The remote device does not support the Object Push Profile.
 */
int bt_opp_send_file_list( const char *remote_device_addr, const char **filelist, int filelist_len );

/**
 * @cond
 * For internal use only. Do not use.
 * The following are prototypes that are used for the initialization function.
 * This function passes the version information as an argument so that it is
 * possible to determine the version an application was compiled with.
 */
int _bt_opp_init( bt_opp_callbacks_t *callbacks, uint32_t version );
#define bt_opp_init(callbacks) _bt_opp_init((callbacks), BT_OPP_VERSION)


__END_DECLS

#endif /* BTOPP_H_ */

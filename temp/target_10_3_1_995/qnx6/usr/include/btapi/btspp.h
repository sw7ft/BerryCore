/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef BTSPP_H_
#define BTSPP_H_

/**
 * @file btspp.h
 *
 * @brief Functions to provide Bluetooth Serial Port (SPP) Protocol
 *        communication
 *
 * This file defines functions to work with Bluetooth. Communication via
 * Bluetooth uses SPP.
 */

#include <unistd.h>

__BEGIN_DECLS

/**
 * @brief Initialize the resources required for the Bluetooth library
 * @details This function initializes resources needed for the library
 *          to function. If you are using a version before BlackBerry 10.3.0, you
 *          must call this function before calling any other function
 *          in the library. Starting in BlackBerry 10.3.0, this function is called
 *          internally so you don't have to call it, but it's safe if you do.
 *
 * @return @c 0 when initialization is successful, @c -1 with the @c errno
 *         value set otherwise. An @c errno of @c ENOMEM indicates that there was
 *         insufficient memory to initialize resources. If the @c errno is set
 *         to any other value than what is listed, a system error has occurred.
 */
int bt_spp_init();

/**
 * @brief Clean up resources used by the library
 * @details This function closes all connections and services created by the user
 *        and cleans up resources initialized by @c bt_spp_init(). Normally
 *        all the resources are internally freed if the user calls @c bt_spp_close()
 *        for the client side, @c bt_spp_close_server() for the server side, or
 *        POSIX @c close() for both. If, for any reason, a service or connection
 *        might not be properly closed, you can close them all by calling
 *        this function. Note that this behaviour is different from that
 *        of the versions before BlackBerry 10.3.0, where @c bt_spp_deinit()
 *        would fail in case of any active connection pending.
 *
 * @return @c 0 when de-initialization is completed.
 */
int bt_spp_deinit();

/**
 * @brief Create a Serial Port Profile (SPP) connection to a service on a remote
 *        Bluetooth device (server)
 * @details The connection can be opened in non-blocking or blocking mode.
 *          After you successfully call this function, and when your application
 *          is finished with the file descriptor that is returned from this
 *          function, call the @c bt_spp_close() function to clean up resources.
 *
 * @param addr The remote Bluetooth device (server) address. The address is in
 *             the following format: 2:2:2:2:2:2, where each digit indicates
 *             the number of hexadecimal digits. For example: <tt>
 *             00:11:22:33:AA:BB</tt>.
 * @param service_uuid The Universally Unique Identifier (UUID) or the name of
 *                     the service to connect to. If this parameter represents
 *                     the UUID, it must be the service ID defined by the
 *                     developer, not the Service Class ID assigned by the
 *                     Bluetooth organization. For example, the SPP profile has
 *                     a 4-digit Service Class ID of @c 0x1101. A developer can
 *                     create multiple services for this service class, and must
 *                     define a unique service ID for each of the services. This
 *                     function searches for the intended service using the input
 *                     UUID when the input matches a supported service ID format.
 *                     If @c service_uuid does not match any supported UUID format,
 *                     this argument is considered to contain the service name,
 *                     which has a maximal length of 50 including the terminating
 *                     NULL character. Then the search for the service is done
 *                     by service name and generic SPP attributes.
 *                     If this argument represents the service ID, it must be in
 *                     one of the following formats:
 *                     - "0x1101": search by generic SPP attributes
 *                     - "0x1101:<uuid>": search by UUID \<uuid\>
 *                     - "<uuid>": search by UUID \<uuid\>
 *                     where \<uuid\> is in <8-4-4-4-12> format, in which each
 *                     digit indicates the number of hexadecimal digits. For
 *                     example, a valid service ID can be:
 *                     - @c "00001101-1111-2222-3333-444444444444": search by
 *                       service UUID @c "00001101-1111-2222-3333-444444444444"
 *                     - <tt> "0x1101:00001101-1111-2222-3333-444444444444"</tt>:
 *                       search by service UUID
 *                       @c "00001101-1111-2222-3333-444444444444"
 *                     - @c "0x1101": search by generic SPP attributes
 *                     - @c "0x1102": search by service name @c "0x1102" and
 *                       generic SPP attributes
 *                     - <tt>"3rd party SPP service"</tt>: search by service
 *                       name <tt>"3rd party SPP service"</tt> and generic SPP
 *                       attributes
 * @param nonblock A flag that specifies whether to open a mount point of the
 *                 connection in non-blocking mode. A value of @c true means
 *                 opening the connection in non-blocking mode.
 * @return The mount point file descriptor if a connection has been successfully
 *         created, @c -1 with the @c errno set otherwise. The @c errno can be
 *         set to one of the following values when @c -1 is returned. If the @c
 *         errno is set to any other value than the following, a system error
 *         has occurred.
 *         - @c EINVAL: Invalid arguments were specified.
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 *         - @c ENONMEM: There is insufficient memory to allocate to complete
 *                       the function.
 *         - @c ESRVRFAULT: The operation was aborted by the user.
 *         - @c EBADMSG: There was an error parsing the incoming message.
 *         - @c EMLINK: A connection to the same service on the same device has
 *                      already been established.
 *         - @c ENODATA: A failure occurred because an error occurred on the
 *                       stack.
 */
int bt_spp_open(char *addr, char *service_uuid, bool nonblock);

/**
 * @brief Create a Serial Port Profile (SPP) connection to a service on a remote
 *        Bluetooth device (server) - an extended version of @c bt_spp_open
 * @details The function allows a user to create a connection to the SPP service
 *        on a remote device that can be found in the SDP by a combination of the
 *        following parameters: service name, service UUID, and RFCOMM channel ID.
 *        The combination may use any or all of the three parameters. If you don't
 *        want to use @c service_name or @c service_uuid for the retrieval of an SDP
 *        record, pass in @c NULL for either or both parameters; if you don't want
 *        to use @c service_port, pass in zero.
 *
 *        For an SDP record to be found, all non-zero parameters must match. There
 *        are two exceptions:
 *        - If all three parameters are zero, the SDP database is searched by generic SPP
 *          features.
 *        - If @c service_port is a non-zero value and an SDP record is not found, this
 *          function still tries to connect to the service by the RFCOMM channel
 *          ID. It does so because sometimes the SPP service is registered with
 *          a known RFCOMM channel ID but is not registered in the SDP. Note,
 *          however, that this function makes no attempt to connect by the RFCOMM
 *          channel ID if @c service_port is non-zero, an SDP record with that value
 *          exists, but no match is found for a non-zero @c service_name or @c service_uuid.
 *
 *        You can open the connection in non-blocking or blocking mode. After you
 *        successfully call this function, and when your application is finished
 *        with the file descriptor that is returned from this function, call
 *        @c bt_spp_close() to clean up resources.
 *
 * @param addr The remote Bluetooth device (server) address. The address is in
 *             the following format: 2:2:2:2:2:2, where each digit indicates
 *             the number of hexadecimal digits. For example: <tt>
 *             00:11:22:33:AA:BB</tt>.
 * @param service_name The name of the service that might appear in the service's
 *                     Service Discovery Protocol (SDP) record. The maximal
 *                     length is 50, including the terminating '\0' character.
 *                     If this argument is set to an empty string or @c NULL, it
 *                     will be excluded from the querying criteria of the remote
 *                     side SDP database.
 * @param service_uuid The Universally Unique Identifier (UUID) of the service to
 *                     connect to. This parameter must be the service ID defined by
 *                     the developer, not the Service Class ID assigned by the
 *                     Bluetooth organization. For example, the SPP profile has
 *                     a 4-digit Service Class ID of @c 0x1101. A developer can
 *                     create multiple services for this service class, and must
 *                     define a unique service ID for each of the services. This
 *                     function searches for the intended service using the input
 *                     UUID when the input matches a supported service ID format.
 *                     If this argument is set to @c NULL, it will be considered
 *                     as being set to UUID @c 00001101-0000-1000-8000-00805f9b34fb,
 *                     which is reserved by the Bluetooth organization as the
 *                     Service Class ID for the SPP service.
 * @param service_port The RFCOMM channel ID that is needed to create an SPP link
 *                     to the server. Any registered service on a server has this
 *                     number. Normally a client-side system retrieves it for the
 *                     user by querying the server's SDP database using the service
 *                     UUID, the service name, or generic SPP features, or some
 *                     combination of the three. However, there are situations
 *                     when the user wants to connect to a known RFCOMM channel
 *                     ID. In that case a non-zero @c service_port must be passed in.
 *                     If it is left as zero, the search in the remote SDP database
 *                     is done by a combination of @c service_name, @c service_uuid
 *                     and generic SPP features.
 * @param nonblock A flag that specifies whether to open a mount point of the
 *                 connection in non-blocking mode. A value of @c true means
 *                 opening the connection in non-blocking mode.
 * @param callback A pointer to a valid callback function that provides the
 *                 mount point file descriptor if you are using the function
 *                 in asynchronous mode. For the synchronous mode, pass in a @c NULL value.
 *                 The mount point file descriptor is provided when the connection
 *                 to the SPP server is established. In case of a failure, the file
 *                 descriptor returns with a value of @c -1 and @c errno is set with the reason.
 * @param param  The user's parameter as the first argument of the returned
 *               callback.
 * @return In the synchronous mode, this function returns the mount point file descriptor if
 *         a connection has been successfully created, @c -1 with the @c errno set otherwise.
 *         In the asynchronous mode, it returns @c 0 if a connection procedure has been successfully
 *         launched, @c -1 with the @c errno set otherwise. The @c errno can be set to one of
 *         the following values when @c -1 is returned. If the @c errno is set to any other
 *         value, a system error has occurred.
 *         - @c EINVAL: Invalid arguments were specified.
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 *         - @c ENONMEM: There is insufficient memory to allocate to complete
 *                       the function.
 *         - @c ESRVRFAULT: The operation was aborted by the user.
 *         - @c EBADMSG: There was an error parsing the incoming message.
 *         - @c EMLINK: A connection to the same service on the same device has
 *                      already been established.
 *         - @c ENODATA: A failure occurred because an error occurred on the
 *                       stack.
 */
int bt_spp_open_ex(char *addr, char *service_name, char *service_uuid, int service_port, bool nonblock, void (*callback)(long,int), long param);

/**
 * @brief Open a Serial Port Profile (SPP) server
 * @details This function registers a service record and starts a thread to
 *          listen for incoming connections. When an incoming connection is
 *          accepted, a callback gets called with a valid mount point file
 *          descriptor as the argument. If the connection is not accepted, the
 *          callback returns an invalid file descriptor (-1).
 *          You cannot register two services with the same UUID even if the
 *          service names are different.
 *
 *          Before you attempt to call this function again using the same UUID,
 *          you must call @c bt_spp_close_server(). If you do not call
 *          @c bt_spp_close_server(), subsequent attempts to open
 *          an SPP server will fail.
 *
 * @param service_name The name of the service to appear in the service's
 *                     Service Discovery Protocol (SDP) record. The maximal
 *                     length is 50 including the terminating NULL character.
 *                     If this argument is empty or set to @c NULL, the default
 *                     service name that appears in the SDP record is "SPP Service".
 * @param service_uuid The Universally Unique Identifier (UUID) of the service
 *                     to register. Note that this is the service ID defined
 *                     by the developer, not the Service Class ID assigned by the
 *                     Bluetooth organization. For example, the SPP profile has
 *                     a 4-digit Service Class ID of @c 0x1101. A developer can
 *                     create multiple services for this service class, and must
 *                     define a unique service ID for each of the services. The
 *                     service ID must be in the following format: 8-4-4-4-12,
 *                     where each digit indicates the number of hexadecimal
 *                     digits. For example, a valid service ID can be:
 *                     @c 00001101-1111-2222-3333-444444444444.
 *                     UUID @c 00001101-0000-1000-8000-00805f9b34fb is reserved
 *                     by the Bluetooth organization as the Service Class ID for
 *                     SPP. We do not recommend that you use it on the server
 *                     side as the service ID for a newly defined service, as it
 *                     cannot guarantee the uniqueness of the service.
 * @param nonblock A flag that specifies whether to open a mount point of the
 *                 connection in non-blocking mode. A value of @c true will
 *                 open the connection in non-blocking mode.
 * @param param  The user's parameter as the first argument of the returned
 *               callback.
 * @param callback A pointer to a valid callback function that provides the
 *                 mount point file descriptor. The mount point file descriptor
 *                 is available when the SPP server has accepted incoming
 *                 connections. In case of a failure, the file descriptor
 *                 returns with a value of @c -1 and @c errno is set with the
 *                 reason.
  * @return @c 0 if the operation is successful, @c -1 otherwise. If your call
 *              to this functions is successful, even if the callback returns
 *              a file descriptor of @c -1, ensure that you call
 *              @c bt_spp_close_server() when you no longer need this connection.
 *              When @c -1 is returned, the @c errno can be set to one of the following values:
 *         - @c EINVAL: Invalid arguments were specified.
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 *         - @c ENONMEM: There is insufficient memory to allocate to complete
 *                       the function.
 *         - @c ESRVRFAULT: The operation was aborted by the user.
 *         - @c EBADMSG: There was an error parsing the incoming message.
 *         - @c EMLINK: A service with the same @c service_uuid
 *                      has already been registered.
 *         - @c ENODATA: A failure occurred because an error occurred on the
 *                       stack.
 */
int bt_spp_open_server(char *service_name, char *service_uuid, bool nonblock, void (*callback)(long param,int fd), long param);


/**
 * @brief Open a Serial Port Profile (SPP) server - an extended version of
 *        @c bt_spp_open_server
 * @details This function registers a service record and starts a thread to
 *          listen for incoming connections. When an incoming connection is
 *          accepted, a callback gets called with a valid mount point file
 *          descriptor as the argument. If the connection is not accepted, the
 *          callback returns an invalid file descriptor (@c -1).
 *
 *          You cannot register two services with the same service UUID even
 *          if other parameters (service names and RFCOMM channel IDs) are different.
 *          You also cannot register two servers with the same RFCOMM channel ID
 *          (@c service_port).
 *
 *          Before calling this function again using the same service UUID or
 *          the RFCOMM channel, you must call @c bt_spp_close_server(). If you
 *          do not call @c bt_spp_close_server(), subsequent attempts to open
 *          an SPP server will fail.
 *
 * @param service_name The name of the service to appear in the service's
 *                     Service Discovery Protocol (SDP) record. The maximal
 *                     length is 50, including the terminating NULL character.
 *                     If this argument is empty or set to @c NULL, the default
 *                     service name that appears in the SDP record is "SPP Service".
 * @param service_uuid The Universally Unique Identifier (UUID) of the service
 *                     to register. Note that this is the service ID defined
 *                     by the developer, not the Service Class ID assigned by the
 *                     Bluetooth organization. For example, the SPP profile has
 *                     a 4-digit Service Class ID of @c 0x1101. A developer can
 *                     create multiple services for this service class, and must
 *                     define a unique service ID for each of the services. The
 *                     service ID must be in the following format: 8-4-4-4-12,
 *                     where each digit indicates the number of hexadecimal
 *                     digits. For example, a valid service ID can be:
 *                     @c 00001101-1111-2222-3333-444444444444.
 *                     UUID @c 00001101-0000-1000-8000-00805f9b34fb is reserved
 *                     by the Bluetooth organization as the Service Class ID for
 *                     SPP. We do not recommend that you use it on the server
 *                     side as the service ID for a newly defined service, as it
 *                     cannot guarantee the uniqueness of the service.
 * @param service_port The RFCOMM channel ID that is needed to create an SPP link
 *                     to the server. Any registered service on a server has this
 *                     number. Normally a client-side system retrieves it for the
 *                     user by querying the server's SDP database by a known service
 *                     UUID. However, there are situations when the user wants to
 *                     connect to a known RFCOMM channel ID. In that case a non-zero
 *                     @c service_port must be passed in. If it is left as zero, the
 *                     search in the remote SDP database is done by a combination of
 *                     @c service_name and @c service_uuid.
 * @param nonblock A flag that specifies whether to open a mount point of the
 *                 connection in non-blocking mode. A value of @c true means
 *                 opening the connection in non-blocking mode.
 * @param param  The user's parameter as the first argument of the returned
 *               callback.
 * @param callback A pointer to a valid callback function that provides the
 *                 mount point file descriptor. The mount point file descriptor
 *                 is available when the SPP server has accepted incoming
 *                 connections. In case of a failure, the file descriptor
 *                 returns with a value of @c -1 and @c errno is set with the
 *                 reason.
 * @return @c 0 if the operation is successful, @c -1 otherwise. If your call
 *         to this functions is successful, even if the callback returns
 *         a file descriptor of @c -1, ensure that you call
 *         @c bt_spp_close_server() when you no longer need this connection.
 *         When @c -1 is returned, the @c errno can be set to one of the following values:
 *         - @c EINVAL: Invalid arguments were specified.
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 *         - @c ENONMEM: There is insufficient memory to allocate to complete
 *                       the function.
 *         - @c ESRVRFAULT: The operation was aborted by the user.
 *         - @c EBADMSG: There was an error parsing the incoming message.
 *         - @c EMLINK: A service with the same @c service_uuid or @c service_port
 *                      has already been registered.
 *         - @c ENODATA: A failure occurred because an error occurred on the
 *                       stack.
 */
int bt_spp_open_server_ex(char *service_name, char *service_uuid, int service_port, bool nonblock, void (*callback)(long,int), long param);


/**
 * @brief Disconnect the link and deregister the Serial Port Profile (SPP) server
 * @details This function requires that you use the Universally Unique
 *          Identifier (UUID) that you used to register the server.
 *          You opened the server using @c bt_spp_open_server() or
 *          @c bt_spp_open_server_ex().
 *
 * @param service_uuid The UUID of the service to deregister.
 * @return  @c 0 when the link is disconnected and the SPP server is deregistered
 *          successfully, @c -1 with @c errno set otherwise. The @c errno can be
 *          set to one of the following values:
 *          - @c EINVAL: An invalid argument was specified.
 *          - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                     failed.
 */
int bt_spp_close_server(char *service_uuid);

/**
 * @brief Disconnect from the service associated with the file descriptor
 * @details This function closes the client side SPP connection opened with 
 *          @c bt_spp_open() or @c bt_spp_open_ex(). Ensure that you call this
 *          function after your application has finished using the file descriptor
 *          from a successful call to @c bt_spp_open() or @c bt_spp_open_ex().
 *
 *          Do not call this function if you started a session with
 *          @c bt_spp_open_server() or @c bt_spp_open_server_ex(), even if the
 *          callback returned a valid file descriptor.
 *
 * @param fd The mount point file descriptor returned by @c bt_spp_open()
 *           or @c bt_spp_open_ex().
 * @return  @c 0 when the service is successfully disconnected, @c -1 with the
 *          @c errno set otherwise. The @c errno can be set to one of the
 *          following values:
 *          - @c EPERM: The @c bt_spp_init() function has not been called or has
 *                      failed.
 *          - @c EBADF: An invalid file descriptor is passed to the function.
 */
int bt_spp_close(int fd);

/**
 * @brief Get the address of a remote device
 * @details This function returns the address of a remote device for the
 *         connection identified by the file descriptor.
 * @param fd The mount point file descriptor returned through one of the
 *           following functions:
 *           - @c bt_spp_open()
 *           - @c bt_spp_open_ex()
 *           - @c bt_spp_open_server()
 *           - @c bt_spp_open_server_ex()
 * @param addr The 18-byte buffer allocated by a user in which the address is
 *             returned.
 * @return @c 0 if the address is returned, @c -1 otherwise, with @c errno
 *         set to one of the following values:
 *         - @c EINVAL: @c addr is NULL.
 *         - @c EPERM: The @c bt_spp_init() has not been called or has
 *                     failed.
 *         - @c EBADF: The file descriptor is invalid.
 */
int bt_spp_get_address(int fd, char *addr);

/**
 * @brief Get the RFCOMM channel number of the established connection or the registered service
 * @details This function returns the RFCOMM channel number either of the established
 *         connection identified by the file descriptor or of the registered service
 *         identified by the service UUID.
 * @param fd The mount point file descriptor returned by @c bt_spp_open(),
 *         or through a callback registered with @c bt_spp_open_server(),
 *         or through an asynchronous call of @c bt_spp_open_ex(). If you wish to
 *         retrieve the RFCOMM channel number for a registered server when a connection
 *         is not yet established, pass in @c -1. The @c service_uuid parameter is ignored if
 *         a valid @c fd is passed in.
 * @param service_uuid The UUID of the service registered on the server side. When the service
 *         is registered but a connection is not established yet, the
 *         RFCOMM channel number is already known on the server side and can be retrieved.
 *         To use this option, you have to pass in @c -1 for @c fd and a valid @c service_uuid.
 * @param service_port The pointer to a user-allocated integer for RFCOMM
 *         channel number that the function returns.
 * @return @c 0 if the RFCOMM channel number is returned, @c -1 otherwise,
 *         with @c errno set to one of the following values:
 *         - @c EINVAL: @c service_port is NULL.
 *         - @c EPERM: The @c bt_spp_init() function has not been called or has failed.
 *         - @c EBADF: The file descriptor is invalid.
 *         - @c ENODEV: No service with this UUID is found.
 */
int bt_spp_get_service_port(int fd, char *service_uuid, int *service_port);

__END_DECLS

#endif /* BTSPP_H_ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )

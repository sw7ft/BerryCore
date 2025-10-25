/*
 * Copyright (c) 1996-2012 Certicom Corp. All rights reserved.
 *
 * This software contains trade secrets, confidential information, and other
 * intellectual property of Certicom Corp. and its licensors. This software
 * cannot be used, reproduced, or distributed in whole or in part by any means
 * without the explicit prior consent of Certicom Corp. Such consent must arise
 * from a separate license agreement from Certicom or its licensees, as 
 * appropriate.
 * 
 * Certicom, Certicom AMS, ACC, Asset Control Core, Certicom Bar Code
 * Authentication Agent, Certicom ECC Core, Certicom Security Architecture,
 * Certicom Trusted Infrastructure, Certicom CodeSign, Certicom KeyInject,
 * ChipActivate, DieMax, Security Builder, Security Builder API, 
 * Security Builder API for .NET, Security Builder BSP, Security Builder Crypto,
 * Security Builder ETS, Security Builder GSE, Security Builder IPSec, Security
 * Builder MCE, Security Builder NSE, Security Builder PKI, Security Builder SSL
 * and SysActivate are trademarks or registered trademarks of Certicom Corp.
 * All other companies and products listed herein are trademarks or registered
 * trademarks of their respective holders.
 *
 * BlackBerry(R), RIM(R), Research In Motion(R) and related trademarks are owned
 * by Research In Motion Limited. Used under license.
 * 
 */
/* @file sbengine.h */
#ifndef SBENGINE_H
#define SBENGINE_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include <openssl/engine.h>


#define SBENGINE_VER_MAJOR 1        /**< Major version number */
#define SBENGINE_VER_MINOR 0        /**< Minor version number */

/** ID of the engine. This must be identical to the shared library
 *  filename (without .dll or .so) */
#define SBENGINE_ID "sbengine"

/**

Load the Security Builder Engine for OpenSSL.

You can call @c ENGINE_load_sb() to use the OpenSSL @e dynamic ENGINE to load
and register the Security Builder ENGINE.

For the @c flags parameter, you can specify any combination of the following 
flags defined in @c openssl/engine.h:

- @c ENGINE_METHOD_RSA
- @c ENGINE_METHOD_DSA
- @c ENGINE_METHOD_DH
- @c ENGINE_METHOD_RAND
- @c ENGINE_METHOD_ECDH
- @c ENGINE_METHOD_ECDSA
- @c ENGINE_METHOD_CIPHERS
- @c ENGINE_METHOD_DIGESTS
- @c ENGINE_METHOD_PKEY_METHS
- @c ENGINE_METHOD_PKEY_ASN1_METHS
- @c ENGINE_METHOD_ALL
- @c ENGINE_METHOD_NONE

@c ENGINE_load_sb() implements the following steps:

1.) It obtains an ENGINE instance of the OpenSSL @c dynamic ENGINE:<p>
<code>
e = ENGINE_by_id("dynamic");
</code>

2.) It uses the <tt>SO_PATH</tt> and <tt>LOAD</tt> ctrl options of the
    <tt>dynamic</tt> ENGINE to load the Security Builder ENGINE shared library:
    <p>
<code>
ENGINE_ctrl_cmd_string(e, "SO_PATH", SBENGINE_ID, 0);

ENGINE_ctrl_cmd_string(e, "LOAD", NULL, 0);
</code>

3.) It obtains an ENGINE instance of the Security Builder ENGINE:

<code>
e = ENGINE_by_id(SBENGINE_ID);
</code>

4.) It adds the Security Builder ENGINE shared library into OpenSSL's list of 
    ENGINEs:

<code>
ENGINE_add(e);
</code>

5.) It sets the Security Builder ENGINE as default for all methods identified by
    the <tt>flags</tt> parameter:

<code>
ENGINE_set_default(e, flags);
</code>

@param[in] flags  Identifies which methods should be configured as default for
OpenSSL.

@return 1 on success, 0 otherwise.

*/
extern
int
ENGINE_load_sb(
    unsigned int flags
    );

/** A custom ENGINE CTRL command to set log level

To enable logging, an application must first call <TT>ENGINE_ctrl()</TT> with
the <tt>cmd</tt> parameter equal to <TT>ENGINE_CTRL_SET_LOGSTREAM</TT> to set a
<TT>BIO</TT> object for log output.

Once logging is enabled, the SB OpenSSL Engine will log various kinds of
information.

The log level controls what information is output to the logging BIO.

<ol>
<li><tt>SBENGINE_LOG_LEVEL_NONE</tt> - absolutely no information is output.

<li><tt>SBENGINE_LOG_LEVEL_ERROR</tt> - only SB OpenSSL Engine errors are
                                        output.

<li><tt>SBENGINE_LOG_LEVEL_WARNING</tt> - SB OpenSSL Engine errors and warnings
                                          are output.

<li><tt>SBENGINE_LOG_LEVEL_DEBUG</tt> - SB OpenSSL Engine errors and warnings are output, but also DEBUGGING information which may include:
    <ul>
    <li>text messages indicating entry and exit to SB OpenSSL Engine functions, useful for following the execution path of an SB OpenSSL Engine operation.
    <li>text messages indicating return codes from all SBAPI crypto functions, useful for understanding SBAPI success/failures.
    <li>text dumps of key data, ciphertext, etc.
    </ul>
    This debugging information may contain sensitive information and may be disabled during compilation of the SB OpenSSL Engine.
</ol>

*/
#define ENGINE_CTRL_SBENGINE_SET_LOGLEVEL       ENGINE_CMD_BASE

/* supported log levels */
#define SBENGINE_LOG_LEVEL_NONE                     0x00    /**< Log level = nothing */
#define SBENGINE_LOG_LEVEL_ERROR                    0x01    /**< Log level = errors */
#define SBENGINE_LOG_LEVEL_WARNING                  0x02    /**< Log level = warnings */
#define SBENGINE_LOG_LEVEL_DEBUG                    0x03    /**< Log level = debug */


#ifdef  __cplusplus
}
#endif
#endif


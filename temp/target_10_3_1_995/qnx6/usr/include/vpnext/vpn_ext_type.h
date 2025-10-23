/*-----------------------------------------------------------------------------
 * BlackBerry VPN Extensions Library
 *
 * Copyright 2013-2014, BlackBerry Limited. All Rights Reserved.
 *
 * This source code may contain confidential information of BlackBerry
 * and its licensors. Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by BlackBerry by written agreement. For more information
 * (including whether this source code file has been published) please
 * email licensing@blackberry.com.
 */


/**
 * @file vpn_ext_type.h
 *
 * @brief Contains constants and data types for VPN Extensions
 *
 */

#ifndef _VPN_EXT_TYPE_H_
#define _VPN_EXT_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>

/**
 * @brief The domain name for Authorization APIs
 */
#define VPN_EXT_DOMAIN_AUTH      "auth"
/**
 * @brief The domain name for Cryptographic APIs
 */
#define VPN_EXT_DOMAIN_CRYPTO    "crypto"
/**
 * @brief The domain name for the Service Extension API
 */
#define VPN_EXT_DOMAIN_SERVICE   "service"
/**
 * @brief The domain name that's used to query the provider's functionality
 */
#define VPN_EXT_DOMAIN_SUPPORT   "support"
/**
 * @brief The domain name for Key Agreement APIs
 */
#define VPN_EXT_DOMAIN_KEYAGREE  "keyagree"


/**
 * @brief The name for the custom Diffie-Hellman Key Agreement API
 */
#define VPN_EXT_KEYAGREE_CUSTOM_DH  "custom_dh"


/**
 * @brief The provider name
 */
#define VPN_EXT_ATTR_PROVIDER          "provider"
/**
 * @brief The API list
 */
#define VPN_EXT_ATTR_API_LIST          "api_list"
/**
 * @brief The API name
 */
#define VPN_EXT_ATTR_API               "api"
/**
 * @brief The API version
 */
#define VPN_EXT_ATTR_VERSION           "version"
/**
 * @brief The domain
 */
#define VPN_EXT_ATTR_DOMAIN            "instance"
/**
 * @brief The enterprise perimeter indication
 */
#define VPN_EXT_ATTR_ENTERPRISE        "enterprise"
/**
 * @brief The pid of the extension entry point
 */
#define VPN_EXT_ATTR_PID                "pid"


/**
 * @brief The maximum length of string names that are used in structures
 */
#define VPN_EXT_NAME_LEN 31

/**
 * @brief An opaque pointer for VPN Extension Provider context
 */
typedef struct _vpn_ext_context *vpn_ext_context;

/**
 * @brief Callback function prototype
 *
 * @param context The VPN Extension context.
 * @param in_buffer The input message to the callback.
 * @param in_buffer_len The input message length.
 * @param pOut_buffer The output message from the callback. If this
 *                    parameter is set to @c NULL, then there is no message
 *                    to return. If it's set to @c in_buffer, then the
 *                    input buffer is reused for output. If it's not set to
 *                    either of these values, then the buffer should be
 *                    allocated by the callback function. After the buffer
 *                    is used, it will be freed by the caller after the
 *                    message is sent to the VPN Manager.
 * @param pOut_buffer_len The output message length.
 *
 * @return An @c errno value that indicates whether an error occurred and what
 *         the error was.
 *
 * @ingroup vpnextapi
 */
typedef errno_t (*vpn_ext_callback_t)( vpn_ext_context context,
                                       char *in_buffer,    unsigned int in_buffer_len,
                                       char **pOut_buffer, unsigned int *pOut_buffer_len );


/**
 * @brief A structure that represents a request message for support callbacks
 */
typedef struct support_request {
    /**
     * @brief The domain that we're checking on
     *
     * @details This value is one of @c VPN_EXT_DOMAIN_*.
     */
    char                domain[VPN_EXT_NAME_LEN + 1];
    /**
     * @brief The API that we're checking on
     *
     * @details This value is one of @c VPN_EXT_DOMAIN_SUPPORT_* or any API
     *          name.
     */
    char                api[VPN_EXT_NAME_LEN + 1];
} support_request_t;


/**
 * @brief A structure that represents a response message for support callbacks
 *
 * @details The response message includes a version number, which is made up
 *          of a major version number (@c version_major) and a minor version
 *          number (@c version_minor).
 */
typedef struct support_response {
    /**
     * @brief The major version number
     */
    unsigned short version_major;
    /**
     * @brief The minor version number
     */
    unsigned short version_minor;
    /**
     * @brief A JSON string listing information on the domain or API that's
     * requested
     */
    char                info[0];
} support_response_t;


/**
 * @brief Custom Diffie-Hellman (DH) transaction types
 *
 * @details Custom Diffie-Hellman transaction types belong to only these types.
 *          Matching request and response structures are associated with each
 *          transaction type.
 */
typedef enum key_agree_request {
    /**
     * @brief A DH information transaction
     */
    KEY_AGREE_REQUEST_DH_INFO          = 0,
    /**
     * @brief A DH initialization transaction
     */
    KEY_AGREE_REQUEST_DH_INIT          = 1,
    /**
     * @brief A DH transaction to obtain the extension's public key
     */
    KEY_AGREE_REQUEST_DH_PUBLIC_KEY    = 2,
    /**
     * @brief A DH transaction to return the gateway's public key and obtain the
     * extension's shared secret
     */
    KEY_AGREE_REQUEST_DH_SHARED_SECRET = 3,
    /**
     * @brief A DH termination transaction
     */
    KEY_AGREE_REQUEST_DH_TERM          = 4,
} key_agree_request_e;

/**
 * @brief The maximum length of a custom Diffie-Hellman name
 */
#define DH_CUSTOM_MAX_LEN 16

/**
 * @brief A Diffie-Hellman (DH) information request
 *
 * @details This type of request is sent by @c VPN_ExP_DhInfo.
 */
typedef struct dh_info_request {
    /**
     * @brief The request type, which is set to @c KEY_AGREE_REQUEST_DH_INFO
     */
    key_agree_request_e      request_type;
    /**
     * @brief The DH custom name
     */
    char                     dh_custom[DH_CUSTOM_MAX_LEN];
} dh_info_request_t;

/**
 * @brief A Diffie-Hellman (DH) initialization request
 *
 * @details This type of request is sent by @c VPN_ExP_DhInit.
 */
typedef struct dh_init_request {
    /**
     * @brief The request type, which is set to @c KEY_AGREE_REQUEST_DH_INIT
     */
    key_agree_request_e      request_type;
    /**
     * @brief The DH custom name
     */
    char                     dh_custom[DH_CUSTOM_MAX_LEN];
} dh_init_request_t;

/**
 * @brief A Diffie-Hellman (DH) public key request
 *
 * @details This type of request is sent by @c VPN_ExP_DhPublicKey.
 */
typedef struct dh_public_key_request {
    /**
     * @brief The request type, which is set to
     *        @c KEY_AGREE_REQUEST_DH_PUBLIC_KEY
     */
    key_agree_request_e      request_type;
    /**
     * @brief The session identifier, which is used for key and termination
     *        requests
     */
    unsigned int             session_id;
} dh_public_key_request_t;

/**
 * @brief A Diffie-Hellman (DH) shared secret request
 *
 * @details This type of request is sent by @c VPN_ExP_DhSharedSecret.
 */
typedef struct dh_shared_secret_request {
    /**
     * @brief The request type, which is set to
     * @c KEY_AGREE_REQUEST_DH_SHARED_SECRET
     */
    key_agree_request_e      request_type;
    /**
     * @brief The session identifier, which is used for key and termination
     * requests
     */
    unsigned int             session_id;
    /**
     * @brief The size (in bytes) of the gateway's public key
     */
    unsigned int             public_key_size;
    /**
     * @brief The public key from the gateway
     */
    unsigned char            public_key[];
} dh_shared_secret_request_t;

/**
 * @brief A Diffie-Hellman (DH) termination request
 *
 * @details This type of request is sent by @c VPN_ExP_DhTerm.
 */
typedef struct dh_term_request {
    /**
     * @brief The request type, which is set to @c KEY_AGREE_REQUEST_DH_TERM
     */
    key_agree_request_e      request_type;
    /**
     * @brief The session identifier, which is used for key and termination
     * requests
     */
    unsigned int             session_id;
} dh_term_request_t;

/**
 * @brief A Key Agreement request message including all request types
 */
typedef struct key_agree_request_t {
    union {
        /**
         * @brief The request type, which is a value from
         * @c key_agree_request_e
         */
        key_agree_request_e            request_type;
        /**
         * @brief A @c DH_INFO request
         */
        dh_info_request_t              dh_info;
        /**
         * @brief A @c DH_INIT request
         */
        dh_init_request_t              dh_init;
        /**
         * @brief A @c DH_PUBLIC_KEY request
         */
        dh_public_key_request_t        dh_public_key;
        /**
         * @brief A @c DH_SHARED_SECRET request
         */
        dh_shared_secret_request_t     dh_shared_secret;
        /**
         * @brief A @c DH_TERM request
         */
        dh_term_request_t              dh_term;
    };
} key_agree_request_t;


/**
 * @brief A Diffie-Hellman (DH) information response
 *
 * @details This type of response is returned to @c VPN_ExP_DhInfo.
 */
typedef struct dh_info_response {
    /**
     * @brief The request type, which is set to @c KEY_AGREE_REQUEST_DH_INFO
     */
    key_agree_request_e      request_type;
    /**
     * @brief The size (in bytes) of the provider's public key
     */
    unsigned int             public_key_size;
    /**
     * @brief The size (in bytes) of the shared secret key
     */
    unsigned int             shared_secret_size;
} dh_info_response_t;

/**
 * @brief A Diffie-Hellman (DH) initialization response
 *
 * @details This type of response is returned to @c VPN_ExP_DhInit.
 */
typedef struct dh_init_response {
    /**
     * @brief The request type, which is set to @c KEY_AGREE_REQUEST_DH_INIT
     */
    key_agree_request_e      request_type;
    /**
     * @brief The session identifier, which is used for key and termination
     * requests
     */
    unsigned int             session_id;
} dh_init_response_t;

/**
 * @brief A Diffie-Hellman (DH) public key response
 *
 * @details This type of response is returned to @c VPN_ExP_DhPublicKey.
 */
typedef struct dh_public_key_response {
    /**
     * @brief The request type, which is set to
     * @c KEY_AGREE_REQUEST_DH_PUBLIC_KEY
     */
    key_agree_request_e      request_type;
    /**
     * @brief The session identifier, which is used for key and termination
     * requests
     */
    unsigned int             session_id;
    /**
     * @brief The size (in bytes) of the provider's public key
     */
    unsigned int             public_key_size;
    /**
     * @brief The public key
     */
    unsigned char            public_key[];
} dh_public_key_response_t;

/**
 * @brief A Diffie-Hellman (DH) shared secret response
 *
 * @details This type of response is returned to @c VPN_ExP_DhSharedSecret.
 */
typedef struct dh_shared_secret_response {
    /**
     * @brief The request type, which is set to
     * @c KEY_AGREE_REQUEST_DH_SHARED_SECRET
     */
    key_agree_request_e      request_type;
    /**
     * @brief The session identifier, which is used for key and termination
     * requests
     */
    unsigned int             session_id;
    /**
     * @brief The size (in bytes) of the shared secret key
     */
    unsigned int             shared_secret_size;
    /**
     * @brief The shared secret key
     */
    unsigned char            shared_secret[];
} dh_shared_secret_response_t;

/**
 * @brief A Diffie-Hellman (DH) termination response
 *
 * @details This type of response is returned to @c VPN_ExP_DhTerm.
 */
 typedef struct dh_term_response {
    /**
     * @brief The request type, which is set to @c KEY_AGREE_REQUEST_DH_TERM
     */
    key_agree_request_e      request_type;
    /**
     * @brief The session identifier, which is used for key and termination
     * requests
     */
    unsigned int             session_id;
} dh_term_response_t;

/**
 * @brief A Diffie-Hellman (DH) response including all request types
 */
typedef struct key_agree_response {
    union {
        /**
         * @brief The request type, which is a value from
         * @c key_agree_request_e
         */
        key_agree_request_e            request_type;
        /**
         * @brief A @c DH_INFO response
         */
        dh_info_response_t             dh_info;
        /**
         * @brief A @c DH_INIT response
         */
        dh_init_response_t             dh_init;
        /**
         * @brief A @c DH_PUBLIC_KEY response
         */
        dh_public_key_response_t       dh_public_key;
        /**
         * @brief A @c DH_SHARED_SECRET response
         */
        dh_shared_secret_response_t    dh_shared_secret;
        /**
         * @brief A @c DH_TERM response
         */
        dh_term_response_t             dh_term;
    };
} key_agree_response_t;


/**
 * @brief VPN service types
 *
 * @details The service type maps to a specific shared library name that's
 *          particular to that service.
 */
typedef enum vpn_service_type {
    /**
     * @brief The AnyConnect service
     */
    VPN_SERVICE_ANYCONNECT    = 0,
    /**
     * @brief The OpenVPN service
     */
    VPN_SERVICE_OPENVPN      = 1,
    /**
     * @brief The P2E service
     */
    VPN_SERVICE_P2E      = 2,
    /**
     * @brief The Max service
     */
    VPN_SERVICE_MAX
} vpn_service_type_e;

/**
 * @brief A structure for VPN Service callbacks
 *
 * @details These callbacks are used to start or stop a registered VPN service.
 *          Typically, these callbacks will be used to start or stop a 3rd party
 *          VPN daemon. The VPN service will be started or stopped under the
 *          control of the VPN Manager.
 */
typedef struct _vpn_service_callbacks
{
    /**
     * @brief A function to start the VPN service
     *
     * @param service_ctx An output parameter that is populated with the
     *        returned service data.
     *
     * @retval EOK Success.
     */
    errno_t (*service_start) ( void ** service_ctx );

    /**
     * @brief A function to stop the VPN service
     *
     * @param service_ctx A pointer to the service data.
     *
     * @retval EOK Success.
     */
    errno_t (*service_stop) ( void ** service_ctx );

} vpn_service_callbacks_t;

#ifdef __cplusplus
}
#endif

#endif // _VPN_EXT_TYPE_H_

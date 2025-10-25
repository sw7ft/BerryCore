/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/*
 * "fs_events.h" -- Public / shared file system event information
 * QNX Software Systems Ltd, 2010
 *
 */

#ifndef __FS_EVENTS_H_INCLUDED
#define __FS_EVENTS_H_INCLUDED

/*  fsev_t describes an event, it's orgin, locale, identity, and
    any data that is associated with it.  Generally the data is
    a path string, but is subject to the actual event identity.

    The length field represents the entire length from the starting
    address of the tuple.

    To ensure future and backward compatibility, the length field
    offset and size shall *not* change.  Clients will use this
    information to parse tuples.
 */
typedef struct fse_event_s {
    uint32_t        signature;          /* Version and fixed identifier      */
    uint16_t        length;             /* Type and length of the event data */
    uint16_t        command;            /* Command / request information     */
    uint32_t        properties;         /* Classification of the event       */
    uint32_t        reserved;           /* Reserved for future use (zero)    */
    uint32_t        identity;           /* Locale and ID of the event        */
} fsev_t;


/*  Note sizeof() is explicitly *not* used in this context since the header
    structure used may end with a flexary or be part of another structure.
*/
#define FSE_HEADER_LENGTH       (20)
#define FSE_MIN_LENGTH          FSE_HEADER_LENGTH


/*  The signature byts are simply a fixed string used for easy identifiation
    and validation of an event.  The version information is generally fixed,
    but may change to accomodate extensions to the event management.
*/
#define FSE_VERSION_1_1         (0x0101)
#define FSE_VERSION_VAL         FSE_VERSION_1_1
#define FSE_VERSION_MASK        (0xFFFF0000)
#define FSE_VERSION_SHIFT       (16)
#define FSE_SIGNATURE_VAL       (0x652f)
#define FSE_SIGNATURE_MASK      (0x0000FFFF)
#define FSE_SIGNATURE           ((FSE_VERSION_VAL << FSE_VERSION_SHIFT)     \
                                    | FSE_SIGNATURE_VAL)

/*  Commands are used in communication with the event manager.  The file
    system uses the FSE_CMD_POST for sending data to the event manager.
    FSE_CMD_FILTER is reserved for use of event clients for setting the
    filters against file descriptors.
*/
#define FSE_CMD_INVALID         (0)
#define FSE_CMD_POST            (1)
#define FSE_CMD_FILTER          (2)
#define FSE_CMD_REPORT          (3)


/*  The maximum length needs to accomodate at least two paths of 1024 bytes
    Some name based operations may have three paths, a mount point and the
    two relative paths.

    Note that events whose data extends beyond what can be logged here
    may be lost.
*/
#define FSE_MAX_EVENT_LENGTH    ((PATH_MAX*3) + 512)
#define FSE_LENGTH_MASK         (0x0FFF)
#define FSE_LENGTH_RESERVED     (0xF000)
#define FSE_LENGTH_PAD_TO       (4)
#define FSE_DATA_PAD_VALUE      (0x00)


/*  Event types are used to describe the use of an event, whether it is
    in place to assist with general file system monitoring, debugging,
    or tracing code execution.

    FSE_TYPE_GENERAL  - General purpose event.
    FSE_TYPE_TRACE    - An event meant to be used for tracking code execution.
    FSE_TYPE_INTERNAL - An internal event such as a specific file system.
    FSE_DATA_ZSTRING  - Data is composed of zero-byte terminated strings.
    FSE_CLASS_UPDATE  - The associated event caused a change to the file system.
    FSE_CLASS_ACCESS  - The event is due to an access to a file
    FSE_CLASS_INFO    - The event is informational.
    FSE_CLASS_PRIVATE - This class is reserved for internal use.

    Event types and classifications are OR'd together to form the properties
    field of an event.
*/
#define FSE_RESERVED_PROPS      (0x07FFFFF0)
#define FSE_TYPE_GENERAL        (0x80000000)
#define FSE_TYPE_TRACE          (0x40000000)
#define FSE_TYPE_DEBUG          (0x20000000)
#define FSE_TYPE_INTERNAL       (0x10000000)
#define FSE_DATA_ZSTRING        (0x08000000)

#define FSE_CLASS_UPDATE        (0x00000001)
#define FSE_CLASS_ACCESS        (0x00000002)
#define FSE_CLASS_INFO          (0x00000004)
#define FSE_CLASS_PRIVATE       (0x00000008)
#define FSE_CLASS_UPDATE2       (0x00000010)


/*  An event identity describes the specific event identifier and source of
    the event within the file subsystem.

    The locale of an event describes where, internal to the io-blk subsystem
    the event came from.  The SYSCALL locale describes those events originating
    from the public entry points of the file system(s).

    Note it is possible for the same event ID to originate from multiple
    locales for instance, an open call will be passed from SYSCALL to a
    specific file system, which may in turn return the same ID with a
    different locale.
*/
#define FSE_LOCALE_MAX          (0x00FF)
#define FSE_LOCALE_MASK         (0x00FF0000)
#define FSE_ID_MAX              (0x0FFF)
#define FSE_ID_MASK             (0x00000FFF)
#define FSE_ID_ISDIR_MASK		(0x00001000)
#define FSE_ID_RESERVED         (0xFF00E000)

/*  Event manager clients should *always* check the following two
    fields to ensure foward compatibility.
*/
#define FSE_TUPLE_LEN(p)        (((p))->length & FSE_LENGTH_MASK)
#define FSE_IS_V1_EVENT(p)      ((((FSE_SIG_VAL(p) & FSE_VERSION_MASK)      \
                                >> FSE_VERSION_SHIFT) == FSE_VERSION_1_1)   \
                                && ((FSE_SIG_VAL(p) & FSE_SIGNATURE_MASK)    \
                                == FSE_SIGNATURE_VAL))


/*  Accessors for an event structure.  All access to event members
    should be completed through or derived from these wrappers.
*/
#define FSE_DATA_PTR(p)         ((void*)(((uint8_t*)(p)) + FSE_HEADER_LENGTH))
#define FSE_DATA_LEN(p)         (FSE_TUPLE_LEN(p) - FSE_HEADER_LENGTH)
#define FSE_VERSION_OF(p)       (((p)->signature) >> FSE_VERSION_SHIFT)
#define FSE_LOCALE_VAL(p)       ((((p)->identity) & FSE_LOCALE_MASK) >> 16)
#define FSE_ID_VAL(p)           ((((p)->identity) & FSE_ID_MASK) >> 00)
#define FSE_ID_ISDIR_VAL(p)     ((((p)->identity) & FSE_ID_ISDIR_MASK) >> 12)
#define FSE_IDENTITY_VAL(p)     ((p)->identity)
#define FSE_CMD_VAL(p)          ((p)->command)
#define FSE_SIG_VAL(p)          ((p)->signature)
#define FSE_PROP_VAL(p)         ((p)->properties)
#define FSE_LEN_VAL(p)          ((p)->length)


/*  Validation checks for convenience (internally used)
*/
#define FSE_IS_VALID_SIG(p)     ((FSE_SIG_VAL(p) == FSE_SIGNATURE) && (((p)->reserved) == 0))
#define FSE_IS_VALID_LEN(p)     ((FSE_LEN_VAL(p) & ~FSE_LENGTH_MASK) == 0)
#define FSE_IS_VALID_CMD(p)     ((FSE_CMD_VAL(p) == FSE_CMD_POST) || (FSE_CMD_VAL(p) == FSE_CMD_FILTER))
#define FSE_IS_VALID_PROPS(p)   ((FSE_PROP_VAL(p) & FSE_RESERVED_PROPS) == 0)
#define FSE_IS_KNOWN_ID(p)      (FSE_ID_VAL(p) && (FSE_ID_VAL(p) < FSE_ID_COUNT))
#define FSE_IS_KNOWN_LOCALE(p)  (FSE_LOCALE_VAL(p) && (FSE_LOCALE_VAL(p) < FSE_LOCALE_COUNT))


/*  Macros to complete the basic initialization of an event structure.
*/
#define FSE_EVENT_ID(loc, id)   ( ((id) & (FSE_ID_MAX | FSE_ID_ISDIR_MASK)) | (((loc) & FSE_LOCALE_MAX) << 16) )

/*  Event initialization wrapper.

        p    - pointer to an fsev_t structure to initialize
        cmd  - Command indicating the operation to complete (FSE_LOCALE_xxx)
        loc  - Indicator of the source of the event (FSE_LOCALE_xxx)
        id   - Specific event identifier (FSE_ID_xxx)
        prop - Properties of this event (FSE_TYPE_xxx, FSE_CLASS_xxx, FSE_DATA_xxx)
        len  - Length of the data in bytes that is associated with this event
*/
#define FSE_INIT_EVENT(p, cmd, loc, id, prop, len)          \
        do {                                                \
            (p)->signature   = FSE_SIGNATURE;               \
            (p)->command     = (cmd);                       \
            (p)->length      = ((len) + FSE_HEADER_LENGTH); \
            (p)->properties  = (prop);                      \
            (p)->reserved    = 0;                           \
            (p)->identity    = FSE_EVENT_ID((loc), (id));   \
        } while (0)

/*  Events are managed as an array of bytes.  To avoid alignment faults,
    event data bytes must be copied into an event structure.  The macro
    below provides that functionality using the library memcpy().
*/
#define FSE_READ_EVENT_S(pev, pdata)      memcpy((pev), (pdata), FSE_HEADER_LENGTH)


/*  Event Manager defaults
*/
#define FSE_INOTIFY_MANAGER_NAME	"/dev/fsnotify"
#define FSE_DEFAULT_MANAGER_NAME    "/dev/fsevents"
#define FSE_MIN_QUEUE_SIZE          (FSE_MAX_WRITE_MSG_SIZE * 2)
#define FSE_MAX_QUEUE_PERCENTAGE    (0.01)
#define FSE_MAX_DEFAULT_QUEUE_SIZE  (1024*1024)
#define FSE_DEFAULT_QUEUE_SIZE      (256*1024)
#define FSE_MIN_WRITE_MSG_SIZE      (FSE_MAX_EVENT_LENGTH)
#define FSE_MAX_WRITE_MSG_SIZE      (64*1024)

/*  Event Mechanism defaults
*/
#define FSE_MINIMUM_PERIOD_MS       (20)
#define FSE_DEFAULT_PERIOD_MS       (250)
#define FSE_MAXIMUM_PERIOD_MS       (2500)
#define FSE_DEFAULT_BUFFER_SIZE     (50*1024)

/* A few sanity checks of the above parameters */
#if FSE_DEFAULT_BUFFER_SIZE > FSE_MAX_WRITE_MSG_SIZE
#error Mechanism writes cannot be larger than what the event manager accepts.
#endif
#if FSE_DEFAULT_QUEUE_SIZE < FSE_MAX_WRITE_MSG_SIZE
#error Event Manager queue size must be substantially larger than a single write.
#endif

/*  Locales indicate where events originated.  Changes here need to
    be reflected in the string declarations below.
*/
enum fst_locale_e {
    FSE_LOCALE_INVALID              = 0,
    FSE_LOCALE_EVMGR,
    FSE_LOCALE_SYSCALL,
    FSE_LOCALE_VFS,
    FSE_LOCALE_BLOCK,
    FSE_LOCALE_FSYS,
    FSE_LOCALE_EXT,     /* External to io-blk file system */
    FSE_LOCALE_COUNT,
    FSE_LOCALE_ALL                  = FSE_LOCALE_MAX
};
#define FSE_LOCALE_TO_STR_LIST      \
    {                               \
        "<invalid-locale>",         \
        "LOCALE_EVMGR",             \
        "LOCALE_SYSCALL",           \
        "LOCALE_VFS",               \
        "LOCALE_BLOCK",             \
        "LOCALE_FSYS",              \
		"LOCALE_EXT",               \
    }
#define FSE_DECL_LOCALE_STRINGS     const char *aszFseLocaleStr[] = FSE_LOCALE_TO_STR_LIST
#define FSE_LOCALE_STR(p)           aszFseLocaleStr[FSE_LOCALE_VAL(p)]


/*  Any changes to the id codes need to be matched to the string
    declaration lists below.
*/
enum fst_id_e {
    FSE_ID_INVALID      = 0,
    FSE_ID_MOUNT,
    FSE_ID_UNMOUNT,
    FSE_ID_OPEN_UPDATE,
    FSE_ID_CLOSE_UPDATE,
    FSE_ID_UNLINK,
    FSE_ID_RENAME,
    FSE_ID_MKDIR,
    FSE_ID_LINK,
    FSE_ID_CHMOD,
    FSE_ID_CHOWN,
    FSE_ID_TRUNCATE,
    FSE_ID_WRITE,
    FSE_ID_OPEN_OTHER,
    FSE_ID_CLOSE_OTHER,
    FSE_ID_OPENFD,
    FSE_ID_READLINK,
    FSE_ID_FDINFO,
    FSE_ID_STAT,
    FSE_ID_READ,
    FSE_ID_SEEK,
    FSE_ID_DEVCTL,
    FSE_ID_CHECK,
    FSE_ID_CREATE,
    FSE_ID_FREE_SPACE,
    FSE_ID_COUNT,
    FSE_ID_ALL                  = FSE_ID_MAX
};


/*  OR'd with FSE_ID_xxx to indicate the operation is against a directory.
*/
#define FSE_ID_ISDIR				FSE_ID_ISDIR_MASK


#define FSE_ID_TO_STR_LIST          \
    {                               \
        "<invalid-id>",             \
        "SYS_MOUNT",                \
        "SYS_UNMOUNT",              \
        "SYS_OPEN_UPDATE",          \
        "SYS_CLOSE_UPDATE",         \
        "SYS_UNLINK",               \
        "SYS_RENAME",               \
        "SYS_MKDIR",                \
        "SYS_LINK",                 \
        "SYS_CHMOD",                \
        "SYS_CHOWN",                \
        "SYS_TRUNCATE",             \
        "SYS_WRITE",                \
        "SYS_OPEN_OTHER",           \
        "SYS_CLOSE_OTHER",          \
        "SYS_OPENFD",               \
        "SYS_READLINK",             \
        "SYS_FDINFO",               \
        "SYS_STAT",                 \
        "SYS_READ",                 \
        "SYS_SEEK",                 \
        "SYS_DEVCTL",               \
        "SYS_CHECK",                \
        "SYS_CREATE",               \
        "SYS_FREE_SPACE"            \
    }

#define FSE_DECL_ID_STRINGS         const char *aszFseIdStr[] = FSE_ID_TO_STR_LIST;
#define FSE_ID_STR(p)               aszFseIdStr[FSE_ID_VAL(p)]


/*  Destination information for an fsnotify event
*/
typedef struct fsnotify_dest_s {
	uint32_t muid;					/* Receiving mailbox unique id */
	uint32_t wuid;					/* Watch unique id */
} fsnotify_dest_t;


/*  Event format sent to fsevmgr
*/
typedef struct fsnotify_event_s {
	uint32_t count;					/* Number of destination entries */
	fsnotify_dest_t dest[8];		/* Destination entries */
	uint32_t mask;					/* Mask that triggered the event */
	uint32_t cookie;				/* Rename cookie */
	uint32_t len;					/* Length of the name that follows */
	char name[0];					/* Name relative to the watch */
} fsnotify_event_t;


/*  Request types for fsnotify devctl
*/
#define FSNOTIFY_REQ_ENABLE			0x01	/* Enable the fsnotify module */
#define FSNOTIFY_REQ_INFO			0x02	/* Get mount point info */
#define FSNOTIFY_REQ_WATCH_ADD		0x03	/* Add a watch */
#define FSNOTIFY_REQ_WATCH_REM		0x04	/* Remove a watch */
#define FSNOTIFY_REQ_RWATCH_ADD		0x05	/* Add a recursive watch */
#define FSNOTIFY_REQ_DEBUG_LEVEL	0x06	/* Set debug level */
#define FSNOTIFY_REQ_QUEUE_STATUS	0x07	/* Report event queue status */
#define FSNOTIFY_REQ_QUEUE_FLUSH	0x08	/* Force event queue flush */
#define FSNOTIFY_REQ_TIMER_ARM		0x09	/* Arm the event queue timer */
#define FSNOTIFY_REQ_MPUID			0x0A	/* Get mount point id */
#define FSNOTIFY_REQ_INODE_WATCHES	0x0B	/* Watches associated with an inode */
#define FSNOTIFY_REQ_MP_INODES		0x0C	/* Watches associated with an inode */


/*  devctl for watch add and remove
*/
typedef struct fsnotify_watch_cmd_s {
	uint32_t command;				/* Structure type command */
	uint32_t muid;					/* Receiving mailbox unique id */
	uint32_t wuid;					/* Watch unique id */
	uint32_t mask;					/* inotify watch mask */
	uint64_t inode;					/* inode being watched */
	uint32_t mpuid;					/* Mount point unique id */
} fsnotify_watch_cmd_t;


/*  devctl for mount point info
*/
typedef struct _fsnotify_info_s {
	uint32_t command;				/* Structure type command */
	uint32_t uid;					/* Mount point unique id */
} fsnotify_info_t;


/*  Commands fsnotify sends to fsevmgr
*/
#define FSNOTIFY_SC_WRITE			0x01	/* Write events */
#define FSNOTIFY_SC_SAVE			0x02	/* Initiating a save */


/*  Message header that preceeds any FSNOTIFY_BT_xxx command
*/
typedef struct fsnotify_sc_header_s {
	uint32_t command;				/* Requested operation */
	uint32_t headersize;			/* Size of this header */
	uint64_t key;					/* Write authorization key */
} fsnotify_sc_header_t;


/*  Message header for FSNOTIFY_SC_WRITE command
*/
typedef struct fsnotify_sc_write_s {
	fsnotify_sc_header_t hdr;		/* Message header */
} fsnotify_sc_write_t;


/*  Message header for FSNOTIFY_SC_SAVE command
*/
typedef struct fsnotify_sc_save_s {
	fsnotify_sc_header_t hdr;		/* Message header */
	uint32_t wrid;					/* Writer id */
} fsnotify_sc_save_t;


/*  devctl for setting the debug level
*/
typedef struct fsnotify_debug_level_s {
	uint32_t command;				/* Structure type command */
	unsigned level;					/* debug level */
} fsnotify_debug_level_t;


/*  Devctl for retrieving queue status
*/
typedef struct fsnotify_queue_status_s {
	uint32_t command;				/* Structure type command */
	size_t size;					/* Size of the event queue */
	size_t used;					/* Amount of queued event data */
	int armed;						/* Boolean for timer being enabled */
    long nsec;            			/* Periodic event writer time in nano-secs */
} fsnotify_queue_status_t;


/*  Devctl for sending simple commands
*/
typedef struct fsnotify_simple_command_s {
	uint32_t command;				/* Structure type command */
} fsnotify_simple_command_t;


/*  Devctl for arming the event queue timer
*/
typedef struct fsnotify_timer_arm_s {
	uint32_t command;				/* Structure type command */
    long nsec;            			/* Periodic event writer time in nano-secs */
} fsnotify_timer_arm_t;


/*  Some information about a watch as used by fsnotify_inode_status_t
*/
typedef struct fsnotify_vwatch_s {
	uint32_t muid;					/* Receiving mailbox unique id */
	int32_t wuid;					/* Watch unique id */
	uint32_t mask;					/* Inotify watch mask */
	int32_t pwuid;					/* Parent watch unique id */
} fsnotify_vwatch_t;


/*  Devctl for viewing watches assigned to an inode
*/
typedef struct fsnotify_inode_status_s {
	uint32_t command;				/* Structure type command */
    unsigned count;            		/* Number of watches */
    unsigned maxcount;            	/* Maximum number of watches */
    uint64_t inode;					/* Inode number */
    fsnotify_vwatch_t watch[0];		/* Watches associated with the inode */
} fsnotify_inode_status_t;


/*  devctl for mount point inodes
*/
typedef struct fsnotify_mp_inodes_s {
	uint32_t command;				/* Structure type command */
	uint32_t uid;					/* Mount point unique id */
    unsigned count;            		/* Number of watches */
    unsigned maxcount;            	/* Maximum number of inodes */
	uint64_t inodes[0];				/* Inodes associated with this mount point */
} fsnotify_mp_inodes_t;




#endif /* __FS_EVENTS_H_INCLUDED */

__SRCVERSION("$URL$ $Rev$");


/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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
 * http://licensing.qnx.com/license-guide/ for other information. $
 */
#ifndef __FS_QNX6_H_INCLUDED
#define __FS_QNX6_H_INCLUDED

#include _NTO_HDR_(sys/platform.h)
#include <sys/types.h>

#define QNX6FS_NAME_MAX			510
#define QNX6FS_SYMLINK_MAX		512
#ifdef PATH_MAX
#define QNX6FS_PATH_MAX			PATH_MAX
#else
#define QNX6FS_PATH_MAX			1024
#endif

#define QNX6FS_DIRECT_BLKS		16
#define QNX6FS_INDIRECT_LEVELS	3
#define QNX6FS_UNUSED_BLK		((_Uint32t)-1)

#define QNX6FS_INO_USED			0x01
#define QNX6FS_INO_MODIFIED		0x02

typedef struct q6_dinode {
	_Uint64t			i_size;
	_Uint32t			i_uid;
	_Uint32t			i_gid;
	_Uint32t			i_ftime;
	_Uint32t			i_mtime;
	_Uint32t			i_atime;
	_Uint32t			i_ctime;
	_Uint16t			i_mode;
	_Uint16t			i_nlink;
	_Uint32t			i_blocks[QNX6FS_DIRECT_BLKS];
	_Uint8t				i_indirect;
	_Uint8t				i_flags;
	_Uint8t				i_spare1[2];
	_Uint32t			i_crypt;
	_Uint32t			i_emode;
	_Uint8t				i_spare2[16];
} q6_dinode_t;

typedef struct q6_iinode {
	_Uint64t			i_size;
	_Uint32t			i_blocks[QNX6FS_DIRECT_BLKS];
	_Uint8t				i_indirect;
	_Uint8t				i_flags;
	_Uint8t				i_spare[6];
} q6_iinode_t;


/*  Bits for the q6_iinode_t.i_emode field
*/
#define QNX6FS_EMODE_ALIMIT		0x00000001	/* Don't allocate beyond allocation limit */
#define QNX6FS_EMODE_INPLACE	0x00000002	/* Do not COW the inode */
#define QNX6FS_EMODE_MASK		0x00000003	/* Mask of changeable emode bits */
#define QNX6FS_EMODE_BTREE		0x80000000	/* Directory is a btree */


/*  The .iextra file is organized as a set of fixed size records
 *  and only the first record is fixed as the keylist.
 */
#define QNX6FS_IEXTRA_VERSION       1
#define QNX6FS_IEXTRA_SIZE          512
#define QNX6FS_IEXTRA_TRAILER       16

#define QNX6FS_IEXTRA_UNUSED        0
#define QNX6FS_IEXTRA_DOMAIN_LIST	1
#define QNX6FS_IEXTRA_DOMAIN_KEY    2
#define QNX6FS_IEXTRA_FILE_KEY		3
#define QNX6FS_IEXTRA_FILE_NAME		4
#define QNX6FS_IEXTRA_ATTRIBUTE		5

#define QNX6FS_IEXTRA_SALT_SIZE     64
#define QNX6FS_IEXTRA_KEY_SIZE     (512/8)
#define QNX6FS_IEXTRA_MAX_KEY_SIZE (2048/8)

#define QNX6FS_DOMAIN_UNUSED        0
#define QNX6FS_DOMAIN_MAX		\
			((QNX6FS_IEXTRA_SIZE - QNX6FS_IEXTRA_TRAILER) / 4 - 2)
#define QNX6FS_DOMAIN_DYNAMIC		(0xFF)

/*	Compile time check to ensure the dynamic domain value does not coincide
	with a fixed keylist domain value.
*/
#if QNX6FS_DOMAIN_DYNAMIC <= QNX6FS_DOMAIN_MAX
  #error qnx6 dynamic domain value overlaps key list range
#endif

/*  Flags used in the public iextra record information (trailer)
*/

/*	The mask of valid bits describing the migration state. If any bit is set in
	this mask, the file is undergoing some form of migration. The migration
	state values are NOT binary exclusive. Since only four states can ever
	exist, we only use 2 bits to store the state.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION        0x03

/*	The file is being migrated from plaintext 'P' to ciphertext 'C'.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION_P2C	0x01

/*	The file is being migrated from ciphertext 'C' to plaintext 'P'.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION_C2P	0x02

/*	The file is being migrated from ciphertext 'C' produced from one key to
	ciphertext 'C' produced by a different key.

	This flag is currently not supported.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION_C2C	0x03

/*	Flags saved exclusively in the domain list entry of the iextra file.
	These flags cannot use the lower 2 bits since that is technically reserved
	for migration, even if these flags should never be set on the same record.
*/

/*	This define is for an obsolete flag, and it can be used at a later date.
    The flag is not used on-disk in any system, and therefore no conflict exists.
*/
#define QNX6FS_IEXTRA_FLAG_UNUSED_1			0x04

/*	This define is for an obsolete flag, and it can be used at a later date.
    The flag is not used on-disk in any system, and therefore no conflict exists.
*/
#define QNX6FS_IEXTRA_FLAG_UNUSED_2			0x08

/*	The inode uses a dynamic encryption domain that does not have an entry in
	the iextra domain key list. These encryption domains are retrieved directly
	using their iextra slot index.
*/
#define QNX6FS_IEXTRA_FLAG_DOMAIN_DYNAMIC	0x10

/*	The inode's name is encrypted and QNX6FS_IEXTRA_FILE_NAME records exist.
    This flag implies that just because a file is encrypted does NOT mean the
    name is encrypted as well.
*/
#define QNX6FS_IEXTRA_FLAG_ENCRYPTED_NAME	0x20


/*  Flags used to define attributes of domain and file key data.
*/

/*  Enable a SHA256 HMAC within the key data.
*/
#define QNX6FS_IEXTRA_KEY_ENABLE_SHA256_HMAC  0x01



/*  Record definition for QNX6FS_IEXTRA_DOMAIN_LIST.

    This is a PACKED ondisk structure; it is being included in q6_iextra_t and
    must not be padded to ensure the definition here matches the layout on disk.
*/
typedef struct __attribute__ ((__packed__)) ie_keylist_s {
	union {
		struct {
			_Uint32t	il_version;
			_Uint32t	il_key[QNX6FS_DOMAIN_MAX+1];
		};
		_Uint8t			ie_data[QNX6FS_IEXTRA_SIZE - QNX6FS_IEXTRA_TRAILER];
	}			ie_extra;
	_Uint8t		ie_spare[15];
	/*_Uint8t	ie_rectype;*/
} ie_keylist_t;
typedef char __size_check_ie_keylist[ (sizeof(struct ie_keylist_s) == QNX6FS_IEXTRA_SIZE-1) ? 1 : -1 ];


/*  Record definition for QNX6FS_IEXTRA_DOMAIN_KEY.

    This is a PACKED ondisk structure; it is being included in q6_iextra_t and
    must not be padded to ensure the definition here matches the layout on disk.

    The field 'ie_spare2' is only available for use when the field 'ie_flags'
    does not contain the bit QNX6FS_IEXTRA_FLAG_DOMAIN_DYNAMIC (in effect, when
    the domain key entry does not describe a dynamic domain). Otherwise the
    'ie_ino' portion of the union is used for dynamic domains to record the inode
    number of the directory for which the domain was originally created and
    assigned.
*/
typedef struct __attribute__ ((__packed__)) ie_domainkey_s {
	union {
		struct {
			_Uint8t		ik_random[QNX6FS_IEXTRA_SALT_SIZE];
			_Uint32t	ik_version;
			_Uint32t	ik_signature;
			_Uint8t		ik_keyno;
			_Uint8t		ik_reserved1;
			_Uint16t	ik_reserved2;
			_Uint8t		ik_spare[49];
			_Uint8t		ik_keyflags;
			_Uint8t		ik_keytype;
			_Uint8t		ik_keylen;
			_Uint8t		ik_key[QNX6FS_IEXTRA_MAX_KEY_SIZE];
		};
		_Uint8t			ie_data[QNX6FS_IEXTRA_SIZE - QNX6FS_IEXTRA_TRAILER];
	}				ie_extra;
	union {
		_Uint8t		ie_spare2[8];
		_Uint64t	ie_ino;
	};
	_Uint8t			ie_spare1[4];
	_Uint8t			ie_flags;
	_Uint8t			ie_domaintype;
	_Uint8t			ie_domain;
	/*_Uint8t		ie_rectype;*/
} ie_domainkey_t;
typedef char __size_check_ie_domainkey[ (sizeof(struct ie_domainkey_s) == QNX6FS_IEXTRA_SIZE-1) ? 1 : -1 ];


/*  Record definition for QNX6FS_IEXTRA_FILE_KEY.

    This is a PACKED ondisk structure; it is being included in q6_iextra_t and
    must not be padded to ensure the definition here matches the layout on disk.
*/
typedef struct __attribute__ ((__packed__)) ie_filekey_s {
	union {
		struct {
			_Uint8t		ic_random[QNX6FS_IEXTRA_SALT_SIZE];
			_Uint32t	ic_version;
			_Uint16t	ic_flags;
			_Uint16t	ic_mode;
			_Uint64t	ic_size;
			_Uint64t	ic_ino;
			_Uint32t	ic_uid;
			_Uint32t	ic_gid;
			_Uint64t	ic_migration;
			_Uint8t		ic_spare[21];
			_Uint8t		ic_keyflags;
			_Uint8t		ic_keytype;
			_Uint8t		ic_keylen;
			_Uint8t		ic_key[QNX6FS_IEXTRA_MAX_KEY_SIZE];
		};
		_Uint8t			ie_data[QNX6FS_IEXTRA_SIZE - QNX6FS_IEXTRA_TRAILER];
	}			ie_extra;
	_Uint64t	ie_inode;
	_Uint32t	ie_domainindex;
	_Uint8t		ie_flags;
	_Uint8t		ie_domaintype;
	_Uint8t		ie_domain;
	/*_Uint8t	ie_rectype;*/
} ie_filekey_t;
typedef char __size_check_ie_filekey[ (sizeof(struct ie_filekey_s) == QNX6FS_IEXTRA_SIZE-1) ? 1 : -1 ];


/*  The iextra record definition. The iextra record defines different types of
    records, depending on the ie_rectype field: KEYLIST, DOMAIN_KEY, or FILE_KEY.
*/
typedef struct q6_iextra {
	union {
		ie_keylist_t	ie_keylist;
		ie_domainkey_t	ie_domainkey;
		ie_filekey_t	ie_filekey;
	};
	_Uint8t				ie_rectype;
} q6_iextra_t;

#define QNX6FS_DIR_EOF			0x00
#define QNX6FS_DIR_LONGNAME		0xFFu
#define QNX6FS_DIR_DELETED		0
#define QNX6FS_DIR_SHORT_LEN	27

typedef struct q6_direntry {
	_Uint32t			d_inode;
	union {
		struct {
			_Uint8t		d_length;
			char		d_name[QNX6FS_DIR_SHORT_LEN];
		}				d_short;
		struct {
			_Uint8t		d_islfn;
			_Uint8t		d_spare1[3];
			_Uint32t	d_blkno;
			_Uint32t	d_cksum;
			_Uint8t		d_spare2[16];
		}				d_long;
	}					d_name;
} q6_direntry_t;

typedef struct q6_longname {
	_Uint16t			d_length;
	char				d_name[QNX6FS_NAME_MAX];
} q6_longname_t;

#define QNX6FS_SIGNATURE		0x68191122
#define QNX6FS_ROOT_INODE		1
#define QNX6FS_BOOTDIR_INODE	2
#define QNX6FS_FSYS_VERSION		4
#define QNX6FS_SBLK_SIZE		512
#define QNX6FS_SBLK_RSRV		4096
#define QNX6FS_BOOT_RSRV		8192
#define QNX6FS_BOOTDIR_SIZE		4096
#define QNX6FS_DEFAULT_RSRV		3
#define QNX6FS_MAX_NGROUPS		64

#define QNX6FS_MAX_BLK_SIZE     (32 * 1024)

/* With block sizes larger than 4KiB, an offset must be added to ensure data
   contents are aligned to the block size boundaries:
   0...8KiB-1         Boot Block
   8KiB..12KiB-1      Superblock reserved
   12KiB..Block Size  Padding
*/
#define QNX6FS_MIN_RSRV_SIZE    (QNX6FS_BOOT_RSRV + QNX6FS_SBLK_RSRV)
#define QNX6FS_OVERHEAD_SIZE(b) (QNX6FS_BOOT_RSRV + 2 * max(QNX6FS_SBLK_RSRV, (b)))
#define QNX6FS_DATA_START(b)    ((QNX6FS_BOOT_RSRV + QNX6FS_SBLK_RSRV)        \
								+ ( ((b) <= QNX6FS_SBLK_RSRV) ? 0             \
								  : abs((b) - QNX6FS_MIN_RSRV_SIZE)) )

#define QNX6FS_SBLK_UNSTABLE	0x00000001
#define QNX6FS_SBLK_V3_LE_RSRV	0x00000002
#define QNX6FS_VOLUME_LABEL		0x00000004	/* Volume label is a string, not a UUID */
#define QNX6FS_LFN_CKSUM		0x00000100
#define QNX6FS_IEXTRA			0x00000200
#define QNX6FS_SBLK_V3_BE_RSRV	0x40000000
#define QNX6FS_DIRBTREE			0x00010000	/* Btree directories were used */
#define QNX6FS_MASK_INCOMPAT	0x00FE0000
#define QNX6FS_MASK_READONLY	0x0000FF00


/*
 * max volume label length: overlays s_uuid[]
 */
#define QNX6FS_MAX_LABEL_LEN	16

typedef struct q6_superblock {
	_Uint32t			s_signature;
	_Uint32t			s_chksum;
	_Uint64t			s_seqno;
	_Uint32t			s_fmttime;
	_Uint32t			s_wrtime;
	_Uint32t			s_flags;
	_Uint16t			s_version;
	_Uint16t			s_rsrvblks;
	_Uint8t				s_uuid[16];
	_Uint32t			s_blksize;
	_Uint32t			s_ninodes;
	_Uint32t			s_finodes;
	_Uint32t			s_nblocks;
	_Uint32t			s_fblocks;
	_Uint32t			s_ngroups;
	q6_iinode_t			s_inodes;
	q6_iinode_t			s_bitmap;
	q6_iinode_t			s_lnames;
	q6_iinode_t			s_iclaim;
	q6_iinode_t			s_iextra;
	_Uint32t            s_migrate_blocks;
	_Uint32t            s_scrub_block;
	_Uint8t				s_spare[32];
} q6_superblock_t;

#define QNX6FS_BG_DEFRAG		0x4000
#define QNX6FS_SNAPSHOT_HOLD	0x8000

#define QNX6FS_BOOT_QUIET		0x01
#define QNX6FS_BOOT_CLS			0x02

typedef struct q6_boothdr {
	_Uint8t				b_jmp[3];
	_Uint8t				b_flags;
	_Uint32t			b_offset;
	_Uint32t			b_sblk0;
	_Uint32t			b_sblk1;
} q6_boothdr_t;


/*  Btree node type
*/
#define Q6_BTREE_NODE_TYPE_LEAF		0x464C	/* Leaf node - "LF" */
#define Q6_BTREE_NODE_TYPE_INTR		0x444E	/* Intermediate node - "ND" */


/*  Format of a btree block list entry
*/
typedef struct q6_btree_blist_s {
	_Uint32t hash;				/* 16-bit Name hash + 16-bit unique value */
	_Uint32t block;				/* Block number */
} q6_btree_blist_t;


/*  Format of a btree intermediate node
*/
typedef struct q6_btree_node_intermediate_s {
	_Uint16t type;				/* Node type */
	_Uint16t count;				/* Number of used entries */
	_Uint32t lastblock;			/* Block for the remaining hashes */
	q6_btree_blist_t blist[0];	/* Block list */
} q6_btree_node_intermediate_t;


/*  Size of an intermediate node header
*/
#define Q6_BTREE_HDR_SIZE_INTR	(offsetof(q6_btree_node_intermediate_t, blist))


/*  Format of a name record stored in a btree leaf node.
*/
typedef struct q6_btree_name_s {
	_Uint32t hash;				/* Name hash */
	_Uint32t ino;				/* Inode number */
	_Uint16t length;			/* Length of the name in bytes */
	_Uint16t reserved;			/* Reserved - zero */
	_Uint8t name[0];			/* Name (not zero terminated) */
} q6_btree_name_t;


/*  Size of an intermediate node header
*/
#define Q6_BTREE_HDR_SIZE_NAME	(offsetof(q6_btree_name_t, name))


/*  Name hash for the dot and dot-dot entries.  These are not the actual hashes
	of the name so that they appear first in a readdir and are easy to skip
	when checking if a directory is empty.
*/
#define BTREE_HASH_DOT				0	/* Name hash for the dot entry */
#define BTREE_HASH_DOTDOT			1	/* Name hash for the dot-dot entry */


/*  Lengths of the names for the dot and dot-dot entries
*/
#define BTREE_NAME_LENGTH_DOT		1	/* Name length for dot entry */
#define BTREE_NAME_LENGTH_DOTDOT	2	/* Name length for dot-dot entry */


/*  Format of a btree leaf node
*/
typedef struct q6_btree_node_leaf_s {
	_Uint16t type;				/* Node type */
	_Uint16t bytes;				/* Used bytes in leaf node */
	q6_btree_name_t first[0];	/* First name record in the leaf node */
} q6_btree_node_leaf_t;


/*  Size of a leaf node header
*/
#define Q6_BTREE_HDR_SIZE_LEAF	(offsetof(q6_btree_node_leaf_t, first))


/*  Adjust the size of a name record to ensure 32-bit alignment

	Parameters
		size - Raw size of a name record

	Returns
		An aligned size in bytes
*/
#define Q6_BTREE_NAME_ALIGN(__size)		(((__size) + 3) & ~3)


/*  Determine the size of a name record

	Parameters
		namelength - Length of the name

	Returns
		The size of the name record in bytes
*/
#define Q6_BTREE_NAME_SIZE(__namelength)	(Q6_BTREE_NAME_ALIGN(Q6_BTREE_HDR_SIZE_NAME + (_Uint16t)(__namelength)))


/*  Return the next name based on the supplied size

	Parameters
		name - Pointer to the name record
		size - Size of one or more name records

	Returns
		A pointer to the next name record
*/
#define Q6_BTREE_NAME_NEXT(__name, __size)	((q6_btree_name_t *)(((_Uint8t *)(__name)) + (__size)))



__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/blk/fs/qnx6/public/sys/fs_qnx6.h $ $Rev: 743970 $")
#endif

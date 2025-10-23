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
#ifndef __FS_DOS_H_INCLUDED
#define __FS_DOS_H_INCLUDED

#include <sys/dcmd_blk.h>
#include <sys/platform.h>
#include <sys/types.h>
#include <time.h>


#define DOSFS_HDR_SCTRSZ		512
#define DOSFS_BPB_SIGNATURE		0xAA55

#define DOSFS_BPB_BLOCK			0
#define DOSFS_LONG_NAME_MAX		255
#define DOSFS_SHORT_NAME_MAX	12
#ifdef PATH_MAX
#define DOSFS_PATHNAME_MAX		PATH_MAX
#else
#define DOSFS_PATHNAME_MAX		1024
#endif

#define DOSFS_RDONLY		0x01
#define DOSFS_HIDDEN		0x02
#define DOSFS_SYSTEM		0x04
#define DOSFS_VOLLABEL		0x08
#define DOSFS_DIR			0x10
#define DOSFS_ARCHIVE		0x20
#define DOSFS_LFN			0x0F

#define DOSFS_SFN_NAME		8
#define DOSFS_SFN_EXT		3

#define DOSFS_LFN_SEQNO		0x1F
#define DOSFS_LFN_FINAL		0x40
#define DOSFS_LFN_CHARS		13

#define DOSFS_LCASE_BASE	0x08
#define DOSFS_LCASE_EXT		0x10

__BEGIN_DECLS

typedef union dosfs_dir_entry  {
	struct dosfs_sfn_info {
		_Uint8t			d_name[DOSFS_SFN_NAME];
		_Uint8t			d_ext[DOSFS_SFN_EXT];
		_Uint8t			d_mode;
		_Uint8t			d_ntattr;
		_Uint8t			d_ntftime;
		_Uint16t		d_ftime;
		_Uint16t		d_fdate;
		_Uint16t		d_adate;
		_Uint16t		d_cluster_hi;
		_Uint16t		d_mtime;
		_Uint16t		d_mdate;
		_Uint16t		d_cluster;
		_Uint32t		d_size;
	}		d_sfn;
	struct dosfs_lfn_info {
		_Uint8t			d_sequence;
		uchar_t			d_name_0_4[10];
		_Uint8t			d_mode;
		_Uint8t			d_zero1[1];
		_Uint8t			d_crc;
		uchar_t			d_name_5_10[12];
		_Uint8t			d_zero2[2];
		uchar_t			d_name_11_12[4];
	}		d_lfn;
} dosfs_dir_entry_t;

typedef struct _bpb {
	uchar_t		bp_bytes_per_sctr[2];
	uchar_t		bp_sctr_per_cluster;
	uchar_t		bp_rsrv_sctr[2];
	uchar_t		bp_fats;
	uchar_t		bp_num_rootdir_ents[2];
	uchar_t		bp_sctrs[2];
	uchar_t		bp_media;
	uchar_t		bp_sctr_per_fat[2];
	uchar_t		bp_sctr_per_track[2];
	uchar_t		bp_heads[2];
	uchar_t		bp_num_hidden_sctr[4];
	uchar_t		bp_big_sctrs[4];
} dosfs_bpb_t;

typedef struct _bpb_ext_fat16 {
	uchar_t		bp_physdisk;
	uchar_t		bp_cur_head;
	uchar_t		bp_signature;
	uchar_t		bp_serialno[4];
	uchar_t		bp_vollabel[11];
	uchar_t		bp_sysid[8];
} dosfs_bpb_ext_fat16_t;

typedef struct _bpb_ext_fat32 {
	uchar_t		bp_big_sctr_per_fat[4];
	uchar_t		bp_ext_flags[2];
	uchar_t		bp_version[2];
	uchar_t		bp_rootdir_sctr[4];
	uchar_t		bp_fsinfo_sctr[2];
	uchar_t		bp_backup_boot_sctr[2];
	uchar_t		bp_reserved[12];
} dosfs_bpb_ext_fat32_t;

typedef struct _info32sctr {
	uchar_t		in_sig1[4];
	uchar_t		in_filler[DOSFS_HDR_SCTRSZ - 4 - 4 - 4 - 4 - 14 - 2];
	uchar_t		in_sig2[4];
	struct _info32 {
		uchar_t		in_free_clusters[4];
		uchar_t		in_next_cluster[4];
	}			in_fsinfo;
	uchar_t		in_reserved[14];
	uchar_t		in_signature[2];
} dosfs_info32sctr_t;

typedef struct _bootsctr {
	uchar_t		bs_jump[3];
	char		bs_oemname[8];
	char		bs_bpb[sizeof(struct _bpb)];
	char		bs_ext_bpb[DOSFS_HDR_SCTRSZ - 3 - 8 - sizeof(struct _bpb) - 2];
	uchar_t		bs_signature[2];
} dosfs_bootsctr_t;


__END_DECLS

__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/blk/fs/dos/public/sys/fs_dos.h $ $Rev: 701969 $")
#endif

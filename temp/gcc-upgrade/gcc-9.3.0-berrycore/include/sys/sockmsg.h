/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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





#ifndef __SOCKMSG_H_INCLUDED
#define __SOCKMSG_H_INCLUDED

#ifndef __IOMSG_H_INCLUDED
#include <sys/iomsg.h>
#endif

#ifndef __RESMGR_H_INCLUDED
#include <sys/resmgr.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#include <_pack64.h>

__BEGIN_DECLS

#define SOCKET_PREFIX "/dev/socket/"

/* Extra 4 bytes in connect message */
typedef struct _io_socket_extra {
	uint16_t type;
	uint16_t protocol;
} io_socket_extra_t;

enum _io_uint16_sock_subtypes {
	_IO_SOCK_SOPT,    /* Deprecated. Use _IO_SOCK_SOPT2 */
	_IO_SOCK_GOPT,    /* Deprecated. Use _IO_SOCK_GOPT2 */
	_IO_SOCK_NLIST,
	_IO_SOCK_SYSCTL,  /* Deprecated. Use _IO_SOCK_SYSCTL2 */
	_IO_SOCK_SYSCTL2, 
	_IO_SOCK_SOPT2,
	_IO_SOCK_GOPT2
};


/* int setsockopt( int fd, int level, int optname, const void* optval, size_t optlen ) */
struct _io_sock_sopt {
	struct _io_msg msg;
	uint16_t _;
	uint16_t level;
	uint16_t optname;
	uint16_t optlen;
	/* u_char data[optlen].  Server interprets type based on level and optname */
};

typedef union {
	struct _io_sock_sopt i;
	/* No data returned */
}	io_sock_sopt_t;

struct _io_sock_sopt2 {
	struct _io_msg msg;
	uint32_t level;
	uint32_t optname;
	uint32_t optlen;
	uint32_t zero;
	/* u_char data[optlen]. Server interprets type based on level and optname */
};

typedef union {
	struct _io_sock_sopt2 i;
	/* No data returned */
}   io_sock_sopt2_t;

/* int getsockopt( int fd, int level, int optname, void* optval, size_t* optlen ) */
struct _io_sock_gopt {
	struct _io_msg msg;
	uint16_t level;
	uint16_t optname;
};

typedef union {
	struct _io_sock_gopt i;
	/* 
	u_char [min (optlen, nbytes)] of data returned where nbytes 
	returned with MsgReply status is number of bytes server attempted to return 
	(client may have specified less in optlen).
	*/
}	io_sock_gopt_t;

struct _io_sock_gopt2 {
	struct _io_msg msg;
	uint32_t level;
	uint32_t optname;
	uint32_t optlen;
	uint32_t zero;
	/* u_char data[optlen] if(optname & GETSOCKOPT_EXTRA) */
};

typedef union {
	struct _io_sock_gopt2 i;
	/* 
	u_char [min (optlen, nbytes)] of data returned where nbytes 
	returned with MsgReply status is number of bytes server attempted to return 
	(client may have specified less in optlen).
	*/
}   io_sock_gopt2_t;

/* int nlist(char *name) */
struct _io_sock_nlist {
	struct _io_msg msg;
	/* struct nlist nl[] */
};

typedef union {
	struct _io_sock_nlist i;
	/* struct nlist[] returned with reply */
} io_sock_nlist_t;



/* int sysctl(int *name, u_int namelen, void *oldp, size_t *oldlenp, void *newp, size_t newlen) */
struct _io_sock_sysctl {
	struct _io_msg msg;
	uint16_t namelen;
	uint16_t oldlen;
	uint16_t newlen;
	uint16_t _;
	/* int [namelen] */
	/* new data    */
};

typedef union {
	struct _io_sock_sysctl i;
/* u_char old_data[oldlen] */
/* oldlen returned with MsgReply */
} io_sock_sysctl_t;
	


struct _io_sock_sysctl2 {
	struct _io_msg msg;
	uint32_t namelen;
	uint32_t oldlen;
	uint32_t newlen;
	/* int [namelen] */
	/* new data    */
};

typedef union {
	struct _io_sock_sysctl2 i;
/* u_char old_data[oldlen] */
/* oldlen returned with MsgReply */
} io_sock_sysctl2_t;


	
/* int sendto(int fd, const void *buffer, int nbytes, int flags, const struct sockaddr *addr, int addrlen) */

struct _io_sock_sendto {
	struct _io_write write;  /* xtype set to _IO_XTYPE_TCPIP */
	uint16_t flags;
	uint16_t addrlen;
	/* u_char addr[addrlen]; */
	/* u_char data[nbytes];  */
};

typedef union {
	struct _io_sock_sendto i;
/* nbytes returned with MsgReply */
} io_sock_sendto_t;



/* int recvfrom(int fd, void *buffer, int nbytes, int flags, struct sockaddr *addr, int *addrlen) */

struct _io_sock_recvfrom {
	struct _io_read read; /* xtype set to _IO_XTYPE_TCPIP */
	uint16_t flags;
	uint16_t addrlen;
};

struct _io_sock_recvfrom_reply {
	uint16_t addrlen;
	/* u_char addr[addrlen] */
	/* u_char data[nbytes]  */
/* nbytes returned with MsgReply */
};

typedef union {
	struct _io_sock_recvfrom       i;
	struct _io_sock_recvfrom_reply o;
} io_sock_recvfrom_t;



/* int sendmsg (int fd, const struct msghdr *msg, int flags) */

struct _io_sock_sendmsg {
	struct _io_write write; /* xtype set to _IO_XTYPE_TCPIP_MSG */
	uint16_t _;
	uint16_t flags;
	uint16_t addrlen;
	uint16_t controllen;
	/* u_char addr[addrlen];       */
	/* u_char control[controllen]; */
	/* u_char data[nbytes];        */
};

typedef union {
	struct _io_sock_sendmsg i;
/* nbytes returned with MsgReply */
} io_sock_sendmsg_t;


/* int sendmmsg(int fd, struct mmsghde *mmsg, unsigned int vlen, unsigned int flags) */

struct _io_sock_sendmmsg {
	struct _io_write write; /* xtype set to _IO_XTYPE_TCPIP_MMSG */
	uint32_t vlen;
	uint32_t flags;
	/* struct msghdr[vlen];					*/
	/* u_char addr[msghdr[0].msg_hdr.msg_namelen]		*/
	/* u_char addr[msghdr[0].msg_hdr.msg_controllen]	*/
	/* ...							*/
	/* u_char addr[msghdr[vlen].msg_hdr.msg_namelen]	*/
	/* u_char addr[msghdr[vlen].msg_hdr.msg_controllen]	*/

	/* u_char data[msghdr[0].nbytes]			*/
	/* ...							*/
	/* u_char data[msghdr[vlen]nbytes]			*/
};

struct _io_sock_sendmmsg_reply {
	struct _io_write        zero;
	uint32_t                zero1;
	uint32_t                zero2;
	/* struct msghdr[vlen];					*/
};

typedef union {
	struct _io_sock_sendmmsg       i;
	struct _io_sock_sendmmsg_reply o;
} io_sock_sendmmsg_t;


/* int recvmsg (int fd, struct msghdr *msg, int flags) */

struct _io_sock_recvmsg {
	struct _io_read read; /* xtype set to _IO_XTYPE_TCPIP_MSG */
	uint16_t _;
	uint16_t flags;
	uint16_t addrlen;
	uint16_t controllen;
};

struct _io_sock_recvmsg_reply {
	uint16_t _;
	uint16_t flags;
	uint16_t addrlen;
	uint16_t controllen;
	/* u_char addr[addrlen] */
	/* u_char control[controllen] */
	/* u_char data[nbytes]  */
/* nbytes returned with MsgReply */
};

typedef union {
	struct _io_sock_recvmsg       i;
	struct _io_sock_recvmsg_reply o;
} io_sock_recvmsg_t;


struct _io_sock_recvmsg2 {
	struct _io_read read; /* xtype set to _IO_XTYPE_TCPIP_MSG2 */
	uint32_t flags;
	uint32_t addrlen;
	uint32_t controllen;
	uint32_t controlseq;
};

struct _io_sock_recvmsg2_reply {
	uint32_t flags;
	uint32_t addrlen;
	uint32_t controllen;
	uint32_t controltot;
	uint32_t controlseq;
	/* u_char addr[addrlen] */
	/* u_char control[controllen] */
	/* u_char data[nbytes]  */
/* nbytes returned with MsgReply */
};

typedef union {
	struct _io_sock_recvmsg2       i;
	struct _io_sock_recvmsg2_reply o;
} io_sock_recvmsg2_t;


/* int recvmmsg(int fd, struct mmsghde *mmsg, unsigned int vlen, unsigned int flags, struct timespec *to) */

struct _io_sock_recvmmsg {
	struct _io_read read; /* xtype set to _IO_XTYPE_TCPIP_MMSG */
	uint32_t vlen;
	uint32_t flags;
	uint32_t addrlen_tot;
	uint32_t controllen_tot;
	struct timespec to;
	/* struct msghdr[vlen];					*/
};

struct _io_sock_recvmmsg_reply {
	struct _io_write        zero;
	uint32_t                zero1[4];
	struct timespec		to;
	/* struct msghdr[vlen];					*/
	/* u_char addr[msghdr[0].msg_hdr.msg_namelen]		*/
	/* u_char addr[msghdr[0].msg_hdr.msg_controllen]	*/
	/* ...							*/
	/* u_char addr[msghdr[vlen].msg_hdr.msg_namelen]	*/
	/* u_char addr[msghdr[vlen].msg_hdr.msg_controllen]	*/

	/* u_char data[msghdr[0].nbytes]			*/
	/* ...							*/
	/* u_char data[msghdr[vlen]nbytes]			*/
};

typedef union {
	struct _io_sock_recvmmsg       i;
	struct _io_sock_recvmmsg_reply o;
} io_sock_recvmmsg_t;


#include <_packpop.h>

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/sys/sockmsg.h $ $Rev: 732183 $" )

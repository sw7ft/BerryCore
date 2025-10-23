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



/*
 *  dcmd_chr.h   Non-portable low-level devctl definitions
 *

 */
#ifndef __DCMD_CHR_H_INCLUDED
#define __DCMD_CHR_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
 #include <devctl.h>
#endif

#include <_pack64.h>

/*
 Where possible we want the devctl to match the ioctl exactly
*/
#define _CMD_IOCTL_TTY			't'

/*
Desc:	This call is made to get the current terminal control settings of a device.
Args:	See the tcgettattr documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcgettattr cover function.
*/
#define DCMD_CHR_TCGETATTR		__DIOF(_CMD_IOCTL_TTY, 19, struct termios)  /* TIOCGETA */

/*
Desc:	These calls are made to change the current terminal control settings of a device.
Args:	See the tcsettattr documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcsettattr cover function.
*/
#define DCMD_CHR_TCSETATTR		__DIOT(_CMD_IOCTL_TTY, 20, struct termios)  /* TIOCSETA */
#define DCMD_CHR_TCSETATTRD		__DIOT(_CMD_IOCTL_TTY, 21, struct termios)  /* TIOCSETAW */
#define DCMD_CHR_TCSETATTRF		__DIOT(_CMD_IOCTL_TTY, 22, struct termios)  /* TIOCSETAF */

/*
Desc:	This call is made to get the process group ID associated with a device.
Args:	See the tcgetpgrp documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcgetpgrp cover function.
*/
#define DCMD_CHR_TCGETPGRP		__DIOF(_CMD_IOCTL_TTY, 119, pid_t)          /* TIOCGPGRP */

/*
Desc:	This call is made to set the process group ID associated with a device.
Args:	See the tcsetpgrp documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcsetpgrp cover function.
*/
#define DCMD_CHR_TCSETPGRP		__DIOT(_CMD_IOCTL_TTY, 118, pid_t)          /* TIOCSPGRP */

/*
Desc:	This call is made get the process group ID of the session leader for
		a controlling terminal.
Args:	See the tcgetsid documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcgetsid cover function.
*/
#define DCMD_CHR_TCGETSID		__DIOF(_DCMD_CHR, 7, pid_t)

/*
Desc:	This call is made set the process group ID of the session leader for
		a controlling terminal.
Args:	See the tcsetsid documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcsetsid cover function.
*/
#define DCMD_CHR_TCSETSID		__DIOT(_DCMD_CHR, 8, pid_t)

/*
Desc:	This call is made to flush the input and/or output stream.
Args:	See the tcflush documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcflush cover function.
*/
#define DCMD_CHR_TCFLUSH		__DIOT(_CMD_IOCTL_TTY, 16, int)             /* TIOCFLUSH */

/*
Desc:	This call is made to obtain information about a terminal device.  
		This call returns the name of the device associated with its file descriptor
		and the number of clients that have an open file descriptor to this
		terminal device.
Args: 	A pointer to a struct _ttyinfo is passed in and filled by the terminal device.
Notes:	
*/
#define DCMD_CHR_TTYINFO		__DIOF(_DCMD_CHR, 10, struct _ttyinfo)
	struct _ttyinfo {
		int	opencount;
		char ttyname[32];
		} ;


typedef enum _tty_queue {
	TTY_NULL_Q,
	TTY_DEVCTL_Q,
	TTY_DRAIN_Q,
	TTY_WRITE_Q,
	TTY_READ_Q,
	TTY_OPEN_Q     // By definition we won't see see anything here, since we have to open the device to query it
} _ttyqueue;

struct _pidtid {
	pid_t pid;
	int   tid;
	int   offset;
	int   nbytes;
};


/*
 * Client passes in queue to query and number of blocked processes it can handle seeing
 */

#define DCMD_CHR_WAITINFO		__DIOTF(_DCMD_CHR, 11, struct _ttywaitinfo)
	struct _ttywaitinfo {
		_ttyqueue      queue;
		unsigned int   num;
		struct _pidtid blocked[0];
	};


/*
Desc:	This call is made to perform a flow-control operation on a data stream.
Args:	See the tcflow documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcflow cover function.
*/
#define DCMD_CHR_TCFLOW			__DIOT('T', 6, int)							/* TCXONC */

/*
Desc:	This call is made to wait until all output has been transmitted to a device.
Args:	See the tcdrain documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcdrain cover function.
*/
#define DCMD_CHR_TCDRAIN		__DION(_CMD_IOCTL_TTY, 94)                  /* TIOCDRAIN */ 

/*
Desc:	These calls allow for the control of the serial communication lines.
Args:	See the tcsendbreak, tcdropline, and ioctl documentation.  
		A pointer to integer is passed and used by the terminal device to
		determine the desired serial line control action.
Notes:	The tcsendbreak, tcdropline, and ioctl functions act as a cover function
		for many of these commands.	 If these cover functions do not provide
		suitable functionality, these commands may be called directly.
*/
#define DCMD_CHR_SERCTL			__DIOT(_DCMD_CHR, 20, int)
	#define _CTL_DTR					0x0001	/* Uses duration */
	#define _CTL_DTR_CHG				0x0010
	#define _CTL_RTS					0x0002
	#define _CTL_RTS_CHG				0x0020
	#define _CTL_BRK					0x0004	/* Uses duration */
	#define _CTL_BRK_CHG				0x0040
	#define _CTL_TIMED					0x0008	/* Uses duration */
	#define _CTL_TIMED_CHG				0x0080
	#define _CTL_DSR                    0x0200  /* For use when DSR is an output (USB device side serial class driver), Uses duration */
	#define _CTL_DSR_CHG                0x2000
	#define _CTL_DCD                    0x0400  /* For use when DCD is an output (USB device side serial class driver), Uses duration */
	#define _CTL_DCD_CHG                0x4000
	#define _CTL_CTS                    0x0800  /* For use when CTS is an output (USB device side serial class driver) */
	#define _CTL_CTS_CHG                0x8000
	#define _CTL_MASK					0x0f0f
	#define _CTL_MASK_CHG				0xf0f0
	#define _CTL_DURATION(__duration)	((__duration) << 16)

	#define _SERCTL_DTR					_CTL_DTR
	#define _SERCTL_DTR_CHG				_CTL_DTR_CHG
	#define _SERCTL_RTS					_CTL_RTS
	#define _SERCTL_RTS_CHG				_CTL_RTS_CHG
	#define _SERCTL_BRK					_CTL_BRK
	#define _SERCTL_BRK_CHG				_CTL_BRK_CHG
	#define _SERCTL_LOOP				0x0100
	#define _SERCTL_LOOP_CHG			0x1000
	#define _SERCTL_DSR                 _CTL_DSR
	#define _SERCTL_DSR_CHG             _CTL_DSR_CHG
	#define _SERCTL_DCD                 _CTL_DCD
	#define _SERCTL_DCD_CHG             _CTL_DCD_CHG
	#define _SERCTL_CTS                 _CTL_CTS
	#define _SERCTL_CTS_CHG             _CTL_CTS_CHG
	#define _SERCTL_DURATION(__duration) _CTL_DURATION(__duration)

	#define _CONCTL_BELL				_CTL_TIMED
	#define _CONCTL_BELL_CHG			_CTL_TIMED_CHG
	#define _CONCTL_SCROLL				0x0100
	#define _CONCTL_SCROLL_CHG			0x1000
	#define _CONCTL_NUM					0x0200
	#define _CONCTL_NUM_CHG				0x2000
	#define _CONCTL_CAPS				0x0400
	#define _CONCTL_CAPS_CHG			0x4000
	#define _CONCTL_INVISIBLE			0x0800	/* Don't talk to video hardware */
	#define _CONCTL_INVISIBLE_CHG		0x8000
	#define _CONCTL_DURATION(__duration) _CTL_DURATION(__duration)

/*
Desc:	This call is made to obtain linestatus information for the terminal device.
Args: 	A pointer to an unsigned integer is passed in and filled by the terminal device.
Notes:	This call is usually associated with the control lines of a serial port.	
		The contents of the returned data is dependent on the device.
		The stty utility calls this function and displays this information.
*/
#define DCMD_CHR_LINESTATUS		__DIOF(_CMD_IOCTL_TTY, 106, int)			/* TIOCMGET */
	#define _LINESTATUS_SER_DTR			0x0001								/* TIOCM_DTR */
	#define _LINESTATUS_SER_RTS			0x0002								/* TIOCM_RTS */
	#define _LINESTATUS_SER_CTS			0x1000								/* TIOCM_CTS */
	#define _LINESTATUS_SER_DSR			0x2000								/* TIOCM_DSR */
	#define _LINESTATUS_SER_RI			0x4000								/* TIOCM_RI */
	#define _LINESTATUS_SER_CD			0x8000								/* TIOCM_CD */

	#define _LINESTATUS_CON_SCROLL		0x0001
	#define _LINESTATUS_CON_NUM			0x0002
	#define _LINESTATUS_CON_CAPS		0x0004
	#define _LINESTATUS_CON_SHIFT		0x0010
	#define _LINESTATUS_CON_CTRL		0x0020
	#define _LINESTATUS_CON_ALT			0x0040

	#define _LINESTATUS_PAR_NOERROR		0x0008
	#define _LINESTATUS_PAR_SELECTED	0x0010
	#define _LINESTATUS_PAR_PAPEROUT	0x0020
	#define _LINESTATUS_PAR_NOTACK		0x0040
	#define _LINESTATUS_PAR_NOTBUSY		0x0080

/*
Desc:	This call is made to obtain the text associated with a plug and play device. 
Args: 	A pointer to string buffer is passed in and filled by the device.
Notes:	This call is usually associated with printer devices.		
*/
#define DCMD_CHR_PNPTEXT        __DIOF(_DCMD_CHR, 99, char)

/*
Desc:	This call is made to control the control lines of a parallel device.	
Args:	
Notes:	Currently not used.	
*/
#define DCMD_CHR_PARCTL			__DIOT(_DCMD_CHR, 98, int)

/*
Desc:	These calls are made to inject characters into a device's input buffer.
Args:	See the tcinject documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcinject cover function.
*/
#define DCMD_CHR_TCINJECTC		__DIOT(_DCMD_CHR, 22, char *) 	/*CANONICAL Input Buffer*/
#define DCMD_CHR_TCINJECTR		__DIOT(_DCMD_CHR, 23, char *)	/*RAW Input Buffer*/

/*
Desc:	This call is made to test to see if a file descriptor is associated 
		with a terminal.
Args:	See the isatty documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the isatty cover function.
*/
#define DCMD_CHR_ISATTY			__DION(_DCMD_CHR, 24)

/*
Desc:	This call is made to obtain out of band data stored by the device.
Args: 	A pointer to an unsigned integer is passed in and filled by the terminal device.
Notes:	This is usually associated with a serial driver.  Note that the _OBAND_SER_** 
		options are not used.  Instead, the individual elements are encoded into the
		returned unsigned character.  This encoding is dependent on the individual device. 	
*/
#define DCMD_CHR_GETOBAND		__DIOF(_DCMD_CHR, 25, char *)
	#define _OBAND_SER_OE			0x01
	#define _OBAND_SER_PE			0x02
	#define _OBAND_SER_FE			0x04
	#define _OBAND_SER_BI			0x08
	#define _OBAND_SER_SW_OE		0x10
	#define _OBAND_SER_MS			0x20
	#define _OBAND_SER_RESUME		0x40

/*
Desc:	This call is made to send out of band data to the device.
Args: 	A pointer to an unsigned integer containing the out of band data is passed in.
Notes:	
*/
#define DCMD_CHR_PUTOBAND		__DIOT(_DCMD_CHR, 26, char *)

/*
Desc:	This call is made to get the size of a character device.
Args:	See the tcgetsize documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcgetsize cover function.
*/
#define DCMD_CHR_GETSIZE		__DIOF(_CMD_IOCTL_TTY, 104, struct winsize)	  /* TIOCGWINSZ */

/*
Desc:	This call is made to set the size of a character device.
Args:	See the tcsetsize documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcsetsize cover function.
*/
#define DCMD_CHR_SETSIZE		__DIOT(_CMD_IOCTL_TTY, 103, struct winsize)	  /* TIOCSWINSZ */

/*
Desc:	This call is made to determine the number of characters waiting to be read.
Args:	See the tcischars documentation.
Notes:	This function is for internal use and should not be called directly.
		Instead use the tcischars cover function.
*/
#define DCMD_CHR_ISCHARS		__DIOF('f', 127, unsigned)					  /* FIONREAD */

/*
Desc:	This call is made to determine the number of characters waiting to be sent.
Args: 	A pointer to an integer is passed in and filled by the terminal device.
Notes:	
*/
#define DCMD_CHR_OSCHARS		__DIOF(_CMD_IOCTL_TTY, 115, unsigned)		  /* TIOCOUTQ */

/*
Desc:	This call is made to determine the size of the device's input buffer.
Args: 	A pointer to an integer is passed in and filled by the terminal device.
Notes:	
*/
#define DCMD_CHR_ISSIZE			__DIOF(_DCMD_CHR, 27, unsigned)

/*
Desc:	This call is made to determine the size of the device's output buffer.
Args: 	A pointer to an integer is passed in and filled by the terminal device.
Notes:	
*/
#define DCMD_CHR_OSSIZE			__DIOF(_DCMD_CHR, 28, unsigned)

/*
 * Get and set the log verbosity of io-char
 */
#define DCMD_CHR_GETVERBOSITY	__DIOF(_DCMD_CHR, 29, unsigned)
#define DCMD_CHR_SETVERBOSITY	__DIOT(_DCMD_CHR, 30, unsigned)

/*
Desc:	This call is made to reset the device.
Args:	None
Notes:	Not all drivers make use of this devctl.
*/
#define DCMD_CHR_RESET			__DION(_DCMD_CHR, 31)

/*
Desc:	This call is made to put the device into idle.
Args:	None
Notes:	Not all drivers make use of this devctl.
*/
#define DCMD_CHR_IDLE           __DION(_DCMD_CHR, 32)

/*
Desc:	This call is made to resume the device from idle.
Args:	None
Notes:	Not all drivers make use of this devctl.
*/
#define DCMD_CHR_RESUME         __DION(_DCMD_CHR, 33)

/*
Desc:   This call is made to force the RTS line to the specified level
Args:   A pointer to an integer is passed in that sets the RTS line high or low
Notes:  Not all drivers make use of this devctl. Note that forcing it back low
        puts control of the RTS line back into io-char's (or the device's for
        auto RTS) hands. In other words, you could "force" it low but it could
        go back high immediately.
 */
#define DCMD_CHR_FORCE_RTS      __DIOT(_DCMD_CHR, 34, int)

/*
 * Desc:   This call is made to set the path to the logging directory
 * Args:   String containing path to logging directory
 * */
#define DCMD_CHR_SET_LOGGING_DIR	__DIOT(_DCMD_CHR, 35, char*)

/*
 * Desc:   These calls are made to enable/disable logging of transmitted and/or received data.
 * Args:   A pointer to integer containing logging enable/disable flags.
*/
#define DCMD_CHR_ENABLE_LOGGING     __DIOT(_DCMD_CHR, 36, int)
#define DCMD_CHR_DISABLE_LOGGING    __DIOT(_DCMD_CHR, 37, int)
	#define _LOG_TX	                0x01
	#define _LOG_RX                 0x02

/*
 * Desc:   This call is made to force a flush of the logged  data to the log files
 * Args:   A pointer to an integer containing the flush flags.
*/
#define DCMD_CHR_FLUSH_LOG     __DIOT(_DCMD_CHR, 38, int)
	#define _FLUSH_TX               0x0200 
	#define _FLUSH_RX               0x0400

#include <_packpop.h>

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/io-char/public/sys/dcmd_chr.h $ $Rev: 642129 $" )

/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef	_PM_H_INCLUDED
#define	_PM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef	__NEUTRINO_H_INCLUDED
#include <sys/neutrino.h>
#endif

#include <_pack64.h>

#define	PMM_PATH	"/dev/pmm"
#define	PMM_PREFIX	"/dev/pmm/"

#define	PM_NODE_NEXUS	S_IFDIR

/*
 * Device Power Modes
 *
 * There are 4 logical power modes:
 * PM_MODE_OFF:     the device is fully powered off
 * PM_MODE_STANDBY: the device is in a low power standby mode
 * PM_MODE_IDLE:    the device is in a low power idle mode
 * PM_MODE_ACTIVE:  the device is fully operational
 *
 * All drivers must implement these 4 power modes.
 * In addition, drivers may implement additional device specific modes:
 * - PM_DEVICE_MODE() is used to define these values. The mode encoding
 *   allows a driver to use bits 23-0 for any driver specific use.
 * - if one of the logical modes is actually implemented using one of these
 *   device specific modes, driver should set the mode to that device
 *   specific mode.
 *
 * PM_POWER_MODE() can be used to determine the logical mode corresponding
 * to any valid power mode value.
 */
typedef _Int32t			pm_power_mode_t;

#define	PM_MODE_OFF		0
#define	PM_MODE_STANDBY	(2 << 28)
#define	PM_MODE_IDLE	(4 << 28)
#define	PM_MODE_ACTIVE	(6 << 28)
#define	PM_MODE_UNKNOWN	-1

#define	_PM_MODE_DEVICE		(1 << 28)
#define	_PM_DEVICE_BITS		0x00ffffff
#define	_PM_DEVICE_MASK		(_PM_MODE_DEVICE|_PM_DEVICE_BITS)

/*
 * PM_DEVICE_MODE() creates a device specific power mode value:
 * __m is the logical mode corresponding to this mode (cannot be PM_MODE_OFF)
 * __d is a device specific encoding describing the mode
 *
 * PM_DEVICE_BITS() extracts the device specific bits from a mode value
 * PM_IS_DEVICE_MODE() is true if a mode value is a device specific mode
 */
#define	PM_DEVICE_BITS(__m)		((__m) & _PM_DEVICE_BITS)
#define	PM_DEVICE_MODE(__m, __d) \
	((__m) | PM_DEVICE_BITS(__d) | _PM_MODE_DEVICE)
#define	PM_IS_DEVICE_MODE(__m)	(((__m) & _PM_MODE_DEVICE) != 0)

/*
 * Check if __m is a valid power mode value
 */
#define	PM_VALID_MODE(__m) \
	((__m) >= PM_MODE_OFF && (__m) <= (PM_MODE_ACTIVE|_PM_DEVICE_MASK))

/*
 * Evaluate logical power mode corresponding to mode __m
 */
#define	PM_POWER_MODE(__m) \
	(PM_VALID_MODE(__m) ? ((__m) & ~_PM_DEVICE_MASK) : PM_MODE_UNKNOWN)

/*
 * Device Power status and attributes
 */
typedef struct _pm_power_attr {
	pm_power_mode_t		cur_mode;
	pm_power_mode_t		new_mode;
	pm_power_mode_t		nxt_mode;
	pm_power_mode_t		num_modes;
} pm_power_attr_t;


/*
 * Power Manager Properties
 */
typedef _Uint32t		pm_property_t;

#define	PM_PROPERTY_USER		0x80000000	/* user-defined properties */
#define	PM_PROPERTY_MODE_ATTR	0x00000001	/* pmd_mode_attr_t array   */

typedef struct {
	pm_property_t	id;
	_Uint32t		size;
} pm_property_attr_t;

/*
 * Power Manager connection
 */
typedef union {
	int		coid;
	void	*reserved;
} pm_hdl_t;

/*
 * Flags for pm_setmode()
 */
#define	PM_MODE_FORCE		0x00000001	/* force power mode to change       */
#define	PM_MODE_URGENT		0x00000002	/* require quick power down         */
#define	PM_MODE_NORAM		0x00000010	/* RAM not preserved on power down  */
#define	PM_MODE_HWVOL		0x00000020	/* device power will be lost        */
#define	PM_MODE_WAKEUP		0x00000040	/* device acts as a CPU wakeup      */

/*
 * Flags for pmd_setmode()/pmd_activate()
 */
#define	PM_MODE_DRIVER		0x00010000	/* driver initiated mode change     */
#define	PM_MODE_HWEVENT		0x00020000	/* h/w event requires mode change   */

/*
 * Flags for pm_notify()
 */
#define	PM_CHANGE_START		0x00000001	/* notify when mode change starts	*/
#define	PM_CHANGE_DONE		0x00000002	/* notify when mode change ends		*/
#define	PM_DRIVER_ATTACH	0x00000004	/* notify when driver attaches		*/
#define	PM_DRIVER_DETACH	0x00000008	/* notify when driver detaches		*/

/*
 * Power Managed Devices
 *
 * pmd_attr_t      contains Power Manager related information for a device
 * pmd_mode_attr_t describes the attributes for a device power mode
 */
typedef struct pmd_attr			pmd_attr_t;
typedef struct pmd_mode_attr	pmd_mode_attr_t;

struct pmd_mode_attr {
	pm_power_mode_t		mode;
	unsigned			flags;
	union {
		_Uint32t flags;
		void   *ptr;
	} drvprivate;
	_Uint32t			rsv1;
};

#define	PMD_MODE_ATTR_NORAM		PM_MODE_NORAM	/* will survive loss of RAM         */
#define	PMD_MODE_ATTR_HWVOL		PM_MODE_HWVOL	/* will preserve h/w context	    */
#define	PMD_MODE_ATTR_WAKEUP	PM_MODE_WAKEUP	/* device acts as a CPU wakeup      */

/*
 * Driver specific function to effect a power mode change
 */
typedef int	(*pmd_setpower_t)(pmd_attr_t *__pmd, unsigned __flags);

struct pmd_attr {
	pm_hdl_t			hdl;
	unsigned			pmm_flags;		/* flags set by pmd_attach()        */

	const pmd_mode_attr_t	*cur_attr;		/* current device power attr        */
	unsigned				cur_flags;		/* flags used to set cur_mode       */
	const pmd_mode_attr_t	*new_attr;		/* new attr if in transition        */
	unsigned				new_flags;		/* flags used to set new_mode       */
	pm_power_mode_t			last_active;	/* last active mode device was in   */

	const pmd_mode_attr_t	*modes;			/* device power modes               */
	int						nmodes;

	void				*data;			/* driver specific data pointer     */
	pmd_setpower_t		setpower;		/* driver mode change function      */
	short				setpower_flags;	/* driver flags for setpower() use  */

	short				lock_flag;
	short				want_ex;
	short				lock_sh;

	struct sigevent		event;

	_Uint32t			seqno;
	_Uint32t			reserved[7];
};

#define	_PMD_LOCK_EX	0x00000001
#define	_PMD_WANT_SH	0x00000002

/*
 * pmm_flags values
 */
#define	PMD_NO_PSTORE		0x00000001	/* do not use pstore                */
#define	PMD_NO_PSTORE_INIT	0x00000002	/* do not initialise from pstore    */

struct sigevent;
struct _iofunc_attr;

__BEGIN_DECLS

/*
 * File descriptor interface to device drivers
 *
 * iopower_getattr()  gets device power mode state
 * iopower_setmode()  sets device power mode
 * iopower_getmodes() gets the supported device power mode values
 * iopower_modeattr() gets the supported device modes and mode attributes
 */

extern int	iopower_getattr(int __fd, pm_power_attr_t *__attr);
extern int	iopower_setmode(int __fd, pm_power_mode_t __mode, unsigned __flags);
extern int	iopower_getmodes(int __fd, pm_power_mode_t *__modes, int __nmodes);
extern int	iopower_modeattr(int __fd, pmd_mode_attr_t *__modes, int __nmodes);

/*
 * These 3 functions are deprecated and are replaced by the iopower_* ones
 */
extern int	pm_get_power(int __fd, pm_power_attr_t *__attr);
extern int	pm_set_power(int __fd, pm_power_mode_t __mode, unsigned __flags);
extern int	pm_get_modes(int __fd, pm_power_mode_t *__modes, int __nmodes);

/*
 * PMM connection and name space manipulation
 *
 * pm_attach() obtains a handle to an existing Power Manager object.
 * pm_detach() closes a handle to a Power Manager object.
 * pm_create() creates a new Power Manager object.
 * pm_unlink() removes a Power Manager object from the Power Manager name space.
 */
extern pm_hdl_t	pm_attach(const char *__name, int __flags);
extern int		pm_detach(pm_hdl_t __hdl);
extern int		pm_create(const char *__name, mode_t __mode);
extern int		pm_unlink(const char *__name);
extern int		pm_valid_hdl(pm_hdl_t __hdl);

/*
 * Power mode manipulation:
 *
 * pm_getattr() returns the current power mode status.
 * pm_setmode() requests a power mode change.
 * pm_getmodes() returns a list of supported power modes.
 * pm_notify() requests notification via the supplied event of mode changes.
 */
extern int	pm_getattr(pm_hdl_t __hdl, pm_power_attr_t *__attr);
extern int	pm_setmode(pm_hdl_t __hdl, pm_power_mode_t __mode, unsigned __flags);
extern int	pm_getmodes(pm_hdl_t __hdl, pm_power_mode_t *__modes, int __nmodes);
extern int	pm_modeattr(pm_hdl_t __hdl, pmd_mode_attr_t *__modes, int __nmodes);
extern int	pm_notify(pm_hdl_t __hdl, unsigned __flags, const struct sigevent *__event);

/*
 * Property manipulation:
 *
 * pm_get_property() gets a property value.
 * pm_set_property() sets a property value.
 * pm_add_property() creates a new property and supplies its initial value.
 * pm_properties() returns a list of properties.
 */
extern int	pm_get_property(pm_hdl_t __hdl, pm_property_t __id, void *__data, int __size);
extern int	pm_set_property(pm_hdl_t __hdl, pm_property_t __id, void *__data, int __size);
extern int	pm_add_property(pm_hdl_t __hdl, pm_property_t __id, void *__data, int __size);
extern int	pm_properties(pm_hdl_t __hdl, pm_property_attr_t *__list, int __count);

/*
 * ------------------------------------------------------------------------
 * Driver support
 * ------------------------------------------------------------------------
 */

/*
 * Driver initialisation:
 *
 * pmd_attr_init() initialises the pmd_attr_t with default values.
 *
 * pmd_attr_setpower() specifies the driver's setpower() function and attaches
 * driver specific data to the pmd_attr_t.
 *
 * pmd_attr_setmodes() specifies the driver's supported power modes.
 *
 * pmd_attach() attaches the driver to the Power Manager. On succesful return,
 * the pmd_attr contains information specifying what power mode the device
 * should be placed in, and what persistent storage mechanisms are required.
 *
 * pmd_detach() is used to detach from the Power Manager when the driver
 * terminates.
 */
extern void	pmd_attr_init(pmd_attr_t *__pmd);
extern void	pmd_attr_setpower(pmd_attr_t *__pmd, pmd_setpower_t __func, void *__data);
extern void	pmd_attr_setmodes(pmd_attr_t *__pmd, pm_power_mode_t __mode, const pmd_mode_attr_t *__modes, int __nmodes);
extern int	pmd_attach(const char *__name, pmd_attr_t *__pmd, const struct sigevent *__event, mode_t __mode);
extern int	pmd_detach(pmd_attr_t *__pmd);

/*
 * Support for driver internal power mode requests:
 *
 * pmd_setmode() synchronously changes the device to a specified power mode.
 * This may return EINPROGRESS if the driver's setpower() function cannot
 * complete the operation immediately (for example it must drain buffers).
 * The caller must hold the exclusive lock (see below).
 *
 * pmd_activate() requests a change to the last active mode of the device.
 * This would typically be used when an I/O request arrives when the device
 * is not in an active mode.
 * The caller must hold the exclusive lock (see below).
 *
 * pmd_confirm() is used by the driver's setpower() function to confirm when
 * a power mode change has completed.
 * The caller must hold the exclusive lock (see below).
 *
 */
extern int	pmd_setmode(pmd_attr_t *__pmd, pm_power_mode_t __mode, unsigned __flags);
extern int	pmd_activate(pmd_attr_t *__pmd, unsigned __flags);
extern void	pmd_confirm(pmd_attr_t *__pmd, int __error);

/*
 * Support functions for handling external power mode requests:
 *
 * pmd_handler() should be called by the driver's Power Manager event handler.
 *
 * pmd_power() is called by iofunc_power() to process _IO_POWER messages.
 */
extern void	pmd_handler(pmd_attr_t *__pmd);
extern int	pmd_power(void *__ctp, void *__msg, pmd_attr_t *__pmd);

/*
 * Support for co-ordinating power mode changes:
 *
 * pmd_lock_shared() acquires a shared lock that will prevent the device
 * power mode from changing. This would typically be held during I/O
 * operations to ensure that the device power mode is stable.
 * The shared lock must be held when calling certain power related functions:
 * - pmd_activate()
 * - pmd_setmode()
 *
 * pmd_lock_exclusive() acquires an exclusive lock (waits for all outstanding
 * shared locks to be released). This must be held when calling any function
 * that may synchronously change the power mode state in the pmd_attr_t:
 * - setpower()
 * - pmd_confirm()
 *
 * pmd_lock_upgrade() can be used to convert a shared lock to an exclusive
 * lock (it will wait for all outstanding shared locks to be released first).
 *
 * pmd_lock_downgrade() can be used to convert an exclusive lock to a shared
 * lock. It will wake up any waiting shared lockers.
 */
extern int	pmd_lock_shared(pmd_attr_t *__pmd);
extern int	pmd_unlock_shared(pmd_attr_t *__pmd);
extern int	pmd_lock_exclusive(pmd_attr_t *__pmd);
extern int	pmd_unlock_exclusive(pmd_attr_t *__pmd);
extern int	pmd_lock_upgrade(pmd_attr_t *__pmd);
extern int	pmd_lock_downgrade(pmd_attr_t *__pmd);

/*
 * Internal support functions
 */
extern int		_pm_connect(const char *__name, int __flags, mode_t __mode, void *__extra, int __extra_len, void *__response, int __response_len);
extern char *	_pm_pathname(const char *__name);
extern const pmd_mode_attr_t *pmd_validate_mode ( pmd_attr_t *pmd , pm_power_mode_t mode , unsigned *flags );
extern int		_pmd_setmode(pmd_attr_t *__pmd, pm_power_mode_t __mode, unsigned __flags);

__END_DECLS

#include <_packpop.h>

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/pm/public/sys/pm.h $ $Rev: 231242 $" )

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



#ifndef _QDB_QDB_H_INCLUDED
#define _QDB_QDB_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _qdb_handle qdb_hdl_t;
typedef struct _qdb_result qdb_result_t;
typedef struct _qdb_stmt   qdb_stmt_t;


#ifndef _SQLITE3_H_
struct sqlite3_context;
struct Mem;
#endif

/* Collation= */
struct qdb_collation {
	char		*name;
	int			encoding;
	void		*arg;
	int			(*compare)(void *, int, const void *, int, const void *);
	int			(*setup)(void *, const void *, int, char **);
};

/* Function= */
struct qdb_function {
	char		*name;
	int			encoding;
	int			narg;
	void		*arg;
	void		(*func)(struct sqlite3_context *, int, struct Mem **);
	void		(*step)(struct sqlite3_context *, int, struct Mem **);
	void		(*final)(struct sqlite3_context *);
};

/* Binding definition */
typedef struct {
    int					index;
    int					type;
    int					len;
    const void			*data;
    unsigned long long	intcopy;
} qdb_binding_t;

/**
 * Binding assignment macros. These take the pointer to a binding array
 * and the 1-based offset into the array for the binding being assigned.
 */
#define QDB_SETARRAYBIND(bind, i, t, l, d) \
    ((bind)[(i)-1].index=(i), \
	 (bind)[(i)-1].type=(t), \
	 (bind)[(i)-1].len=(l), \
	 (bind)[(i)-1].data=(d))

#define QDB_SETARRAYBIND_INT(bind, i, d) \
    ((bind)[(i)-1].index=(i), \
	 (bind)[(i)-1].type=QDB_INTEGER, \
	 (bind)[(i)-1].len=sizeof(d), \
	 (bind)[(i)-1].data=&(d))

#define QDB_SETARRAYBIND_TEXT_OR_NULL(bind, i, d) \
	do { if(d) QDB_SETARRAYBIND_TEXT(bind, i, d); \
	     else QDB_SETARRAYBIND_NULL(bind, i); } while(0);

#define QDB_SETARRAYBIND_NULL(bind, i) \
    ((bind)[(i)-1].index=(i), \
	 (bind)[(i)-1].type=QDB_NULL, \
	 (bind)[(i)-1].len=0, \
	 (bind)[(i)-1].data=NULL)

#define QDB_SETARRAYBIND_TEXT(bind, i, d) \
    ((bind)[(i)-1].index=(i), \
	 (bind)[(i)-1].type=QDB_TEXT, \
	 (bind)[(i)-1].len=strlen(d), \
	 (bind)[(i)-1].data=(d))

#define QDB_SETARRAYBIND_INTCOPY(bind, i, d) \
    ((bind)[(i)-1].index=(i), \
	 (bind)[(i)-1].type=QDB_INTEGER, \
	 (bind)[(i)-1].intcopy = (d), \
	 (bind)[(i)-1].len=sizeof((bind)[(i)-1].intcopy), \
	 (bind)[(i)-1].data=&(bind)[(i)-1].intcopy)

#define QDB_SETARRAYBIND_BLOB(bind, i, d, l) \
    ((bind)[(i)-1].index=(i), \
	 (bind)[(i)-1].type=QDB_BLOB, \
	 (bind)[(i)-1].len=(l), \
	 (bind)[(i)-1].data=(d))

#define QDB_SETARRAYBIND_REAL(bind, i, d) \
    ((bind)[(i)-1].index=(i), \
	 (bind)[(i)-1].type=QDB_REAL, \
	 (bind)[(i)-1].len=(sizeof(double)), \
	 (bind)[(i)-1].data=&(d))


/**
 * Binding assignment macros. These take the pointer to a specifc binding
 * and the 1-based offset into the array that the binding is.
 */
#define QDB_SETBIND(bind, i, t, l, d) \
    ((bind)->index=i, (bind)->type=t, (bind)->len=l, (bind)->data=d)
#define QDB_SETBIND_INT(bind, i, d) \
    ((bind)->index=i, (bind)->type=QDB_INTEGER, (bind)->len=sizeof(d), (bind)->data=&(d))
#define QDB_SETBIND_NULL(bind, i) \
    ((bind)->index=i, (bind)->type=QDB_NULL, (bind)->len=0, (bind)->data=NULL)
#define QDB_SETBIND_TEXT(bind, i, d) \
    ((bind)->index=i, (bind)->type=QDB_TEXT, (bind)->len=strlen(d), (bind)->data=d)
#define QDB_SETBIND_INTCOPY(bind, i, d) \
    ((bind)->index=i, (bind)->type=QDB_INTEGER, (bind)->intcopy = (d), (bind)->len=sizeof((bind)->intcopy), (bind)->data=&(bind)->intcopy)
#define QDB_SETBIND_BLOB(bind, i, d, l) \
    ((bind)->index=i, (bind)->type=QDB_BLOB, (bind)->len=l, (bind)->data=d)
#define QDB_SETBIND_REAL(bind, i, d) \
    ((bind)->index=i, (bind)->type=QDB_REAL, (bind)->len=(sizeof(double)), (bind)->data=&(d))

/* qdb_connect() */
#define QDB_CONN_DFLT_SHARE				0x01
#define QDB_CONN_NONBLOCKING			0x02
#define QDB_CONN_STMT_ASYNC				0x04

/* qdb_getoption()/qdb_setoption() */
#define QDB_OPTION_LAST_INSERT_ROWID	0
#define QDB_OPTION_ROW_CHANGES			1
#define QDB_OPTION_COLUMN_NAMES			2
#define QDB_OPTION_STICKY_BINDINGS		3
#define QDB_OPTION_COLUMN_DECLTYPES		4 /* include declared column types with results; required to use qdb_column_decltype() */

/* qdb_setbusytimeout() */
#define QDB_TIMEOUT_NONBLOCK			0x00000000
#define QDB_TIMEOUT_BLOCK				0x7FFFFFFF

/* qdb_cell_type() */
#define QDB_UNSUPPORTED					0
#define QDB_INTEGER						1
#define QDB_REAL						2
#define QDB_TEXT						3
#define QDB_TEXT16						4
#define QDB_BLOB						5
#define QDB_NULL						6

/* qdb_vacuum(), qdb_backup(), qdb_getdbsize() */
#define QDB_ATTACH_DEFAULT				0
#define QDB_ATTACH_ALL					1
#define QDB_ATTACH_NONE					2
#define QDB_ATTACH_ALWAYS				QDB_ATTACH_ALL
#define QDB_ATTACH_NEVER				QDB_ATTACH_NONE

#define QDB_TRANSACTION_ROLLBACK		0
#define QDB_TRANSACTION_COMMIT			1
#define QDB_TRANSACTION_DEFERRED		2
#define QDB_TRANSACTION_IMMEDIATE		3
#define QDB_TRANSACTION_EXCLUSIVE		4
#define QDB_TRANSACTION_RDLOCK			5
#define QDB_TRANSACTION_WRLOCK			6
#define QDB_TRANSACTION_UNLOCK			7

/* qdb_printmsg() */
#define QDB_FORMAT_SIMPLE				0
#define QDB_FORMAT_HTML					1
#define QDB_FORMAT_COLUMN				2
#define QDB_FORMAT_SGML					3
#define QDB_FORMAT_DATA					4

extern qdb_hdl_t	*qdb_connect(const char *dbname, int flags);
extern int			qdb_disconnect(qdb_hdl_t *db);
extern int			qdb_parameters(qdb_hdl_t *db, int mask, int bits);
extern const char	*qdb_geterrmsg(qdb_hdl_t *db);
extern int			qdb_geterrcode(qdb_hdl_t *db);
extern int			qdb_binding(qdb_hdl_t *db, int index, int type, void *data, int len);
extern int			qdb_statement(qdb_hdl_t *db, const char *fmt, ...);
extern qdb_result_t	*qdb_getresult(qdb_hdl_t *db);
extern qdb_result_t *qdb_query(qdb_hdl_t *db, int size_hint, const char *fmt, ...);
extern int			qdb_getresultoption(qdb_result_t *result, int option);
extern int			qdb_columns(qdb_result_t *result);
extern int			qdb_rows(qdb_result_t *result);
extern const char	*qdb_column_name(qdb_result_t *result, int col);
extern const char	*qdb_column_decltype(qdb_result_t *result, int col);
extern int			qdb_column_index(qdb_result_t *result, const char *name);
extern int			qdb_cell_type(qdb_result_t *result, int row, int col);
extern int			qdb_cell_length(qdb_result_t *result, int row, int col);
extern void			*qdb_cell(qdb_result_t *result, int row, int col);
extern int			qdb_printmsg(FILE *fp, qdb_result_t *result, int format);
extern int			qdb_freeresult(qdb_result_t *result);
extern int			qdb_getoption(qdb_hdl_t *db, int option);
extern int			qdb_setoption(qdb_hdl_t *db, int option, int value);
extern int			qdb_setbusytimeout(qdb_hdl_t *db, int timeout);
extern uint64_t		qdb_last_insert_rowid(qdb_hdl_t *db, qdb_result_t *result);
extern uint64_t		qdb_rowchanges(qdb_hdl_t *db, qdb_result_t *result);
extern int			qdb_vacuum(qdb_hdl_t *db, int scope);
extern int			qdb_backup(qdb_hdl_t *db, int scope);
extern int			qdb_bkcancel(qdb_hdl_t *db, int *nactive);
extern int			qdb_getdbsize(qdb_hdl_t *db, int scope, uint32_t *page_size, uint32_t *total_pages, uint32_t *free_pages);
extern int			qdb_getdbsize_bytes(qdb_hdl_t *db, int scope, uint64_t *bytes_total, uint64_t *bytes_free);
extern int			qdb_collation(qdb_hdl_t *db, void *data, int nbytes, int reindex);
extern int			qdb_gettransstate(qdb_hdl_t *db);
extern int			qdb_data_source(qdb_hdl_t *hdl, char *buffer, int buflen);
extern int			qdb_stmt_init(qdb_hdl_t *db, const char *sql, uint32_t len);
extern int			qdb_stmt_free(qdb_hdl_t *db, int stmtid);
extern int			qdb_stmt_exec(qdb_hdl_t *db, int stmtid, qdb_binding_t *bindings, uint8_t binding_count);

/**
 * Retrieve declared column types for a prepared statement.
 * 
 * @param db The qdb connection handle.
 * @param stmtid The stmtid returned from qdb_stmt_init().
 * @param buf Pointer to a buffer of bufsize.
 *            Note: This is not a pointer to an array of buffers, but 
 *                  should be used as such after calling.
 * @param bufsize Size of given buffer - set to 0 to get required_size.
 * @param required_size Size of buffer required to hold all results.
 * @return if bufsize is 0 or buf is NULL, the total number of columns in the
 *         statement otherwise, the number of columns with a valid decltype.
 *         If bufsize >= required_size this is the total number of columns 
 *         in the statement.
 */
extern int			qdb_stmt_decltypes(qdb_hdl_t *db, int stmtid, char **buf, ssize_t bufsize, ssize_t *required_size);

/**
 * Interrupt a long-running query.
 * 
 * Care should be taken to ensure that the connection to qdb is not 
 * disconnected while this call is running.
 * 
 * @param db The qdb connection handle that you want to interrupt.
 * @return 0 on success, -1 on error with errno set.
 */
extern int			qdb_interrupt(qdb_hdl_t *db);
extern int			qdb_logmemstats(qdb_hdl_t *db);

extern char			*qdb_vmprintf(const char *format, va_list ap);
extern char			*qdb_mprintf(const char *format, ...);
extern char			*qdb_snprintf(int n, char *buf, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif

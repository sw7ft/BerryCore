/*
 * $QNXLicenseC:
 * Copyright 2012 QNX Software Systems. All Rights Reserved.
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

#ifndef __QPROFILER_H_INCLUDED
#define __QPROFILER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * This header contains APIs for profiling library (libprofiling)
 * which allows you to start/stop the profiler dynamically.
 *
 * There are two functions you can call, and they must be called from within the same function.
 *
 *   QPROFILER_START() - to start profiling
 *   QPROFILER_STOP() - to stop profiling
 *
 * By default these functions would expand to empty expressions, to enable them define extra variable QPROFILING
 * as compiler/preprocessor define macro for the profiling build configuration.
 *
 * All other functionality of the profiler is controlled by environment variables:
 *
 QPROF_HELP=1              - print this help
 QPROF_AUTO_START=0        - do not start profiling automatically (wait for signal or API call)
 QPROF_FILE=<file>         - enable profiler trace capture and store output to the file/device
 QPROF_KERNEL_TRACE=1      - use kernel trace events instead of profiler trace, default is off
 QPROF_BACKTRACING=1       - use hooks for backtracing (instead of profiling), use API to collect backtraces
 QPROF_METHOD=<num>        - defines profiler method or timer, for constant value see constants below (qprofiler_method_t type)
 QPROF_SIG_STOP_PROFILING=<signum>   - install stop profiling signal handler, by default is not installed
 QPROF_SIG_CONT_PROFILING=<signum>   - install resume profiling signal handler, by default is not installed
 */


typedef enum qprofiler_mode_t{
	MODE_NONE = 0,
	MODE_KERNEL_TRACE,
	MODE_LOG_FILE,
	MODE_BACKTRACING,
} qprofiler_mode_t;

typedef enum qprofiler_method_t{
	METHOD_DEFAULT = 0,
	METHOD_CLOCK_CYCLES,
	METHOD_REALTIME,
	METHOD_PROCESSTIME,
	METHOD_THREADTIME,
	METHOD_ALLOC
} qprofiler_method_t;



#ifdef QPROFILING

/**
 * Starts or restarts the profiler data collection. See qprofiler_stop() for details.
 * This function would expand to empty expression unless QPROFILING macro is defined.
 */
#define QPROFILER_START() (qprofiler_start())

/**
 * Stops the profiler data collection. See qprofiler_start() for details.
 * This function would expand to empty expression unless QPROFILING macro is defined.
 */
#define QPROFILER_STOP() (qprofiler_stop())

#else // QPROFILING

#define QPROFILER_START()
#define QPROFILER_STOP()

#endif // QPROFILING

/**
 * Stops the profiler data collection.
 * This function should be called in the same function as qprofiler_start() to preserve function call stack integrity.
 * To disable automatic data collection on start use QPROF_AUTO_START=0 as environment variable for the invocation.
 */
void qprofiler_stop();
/**
 * Starts or restarts the profiler data collection.
 * This function should be called in the same function as qprofiler_stop() to preserve function call stack integrity
 * To disable automatic data collection on start use QPROF_AUTO_START=0 as environment variable for the invocation.
 */
void qprofiler_start();

/**
 * Sets the profiling mode and timer resolution.
 * Instead of calling this API you can use an environment variable to define mode and method for profiling.
 *
 * @param mode - set profiler mode defined by qprofiler_mode_t type
 * @param method - set profiler method (or counter) defined by  qprofiler_method_t type
 * @return -1 if method did not succeed
 */
int qprofiler_set_mode(qprofiler_mode_t mode, qprofiler_method_t method);

/**
 * When collecting backtraces (MODE_BACKTRACING), this function will fill the buffer with backtrace addresses collected
 * @param buffer - array of void* representing addresses of call site for each frame
 * @param size - maximum size of the buffer array
 * @return - number of frame actually filled by the function, or -1 if error occured
 */
int qprofiler_backtrace_self(void **buffer, int size, int options);


typedef struct qprofiler_callstack_t {
	size_t size;
	void **top;
	void **base;
} qprofiler_callstack_t;

#ifdef __cplusplus
}
#endif

#endif /* __QPROFILER_H_INCLUDED */
__SRCVERSION( "$URL$ $Rev$" )

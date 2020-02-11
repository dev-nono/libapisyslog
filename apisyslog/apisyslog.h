/*
 * libappsyslog.h
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_H_
#define LIBAPISYSLOG_H_

#include <stdint.h>
#include <stdio.h>
#include <syslog.h>

#define APISYSLOG_TRACE_INOUT 	        (1UL << 0 )
#define APISYSLOG_TRACE_1 		        (1UL << 1 )
#define APISYSLOG_TRACE_2 		        (1UL << 2 )

#define APISYSLOG_DBG_WAIT1	            (1UL << 50 )
#define APISYSLOG_DBG_WAIT2             (1UL << 51 )

#define APISYSLOG_TRACE_STDERR          (1UL << 60 )
#define APISYSLOG_TRACE_STDOUT	        (1UL << 62 )
#define APISYSLOG_TRACE_NANO	        (1UL << 63 )
#define APISYSLOG_TRACE_END		0

#define APISYSLOG_WAIT_OFF      0
#define APISYSLOG_WAIT_ON       1
#define APISYSLOG_WAIT_AUTO     2

#define APISYSLOG_DEBUG_FIFO    "debug.fifo"
#define APISYSLOG_DEBUG_WAIT1   "debug.wait1"
#define APISYSLOG_DEBUG_WAIT2   "debug.wait2"



#define TRACE_IN(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_INOUT) )\
	{ apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_OUT(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_INOUT) )\
	{ apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG1(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_1) )\
	{ apisyslog_PrintLog(__FUNCTION__, arg_1);}
#define TRACE_DBG2(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_2) )\
			{ apisyslog_PrintLog(__FUNCTION__, arg_1);}


int apisyslog_init(const char* a_ConfigFilemame);
int apisyslog_release();

uint64_t apisyslog_getflag(uint64_t a_flag);
int apisyslog_PrintLog(const char *pszCompName, const char *a_pszFmt, ...);

int apisyslog_Wait(uint64_t a_flag);

#endif /* LIBAPISYSLOG_H_ */

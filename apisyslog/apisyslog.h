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

#define APISYSLOG_TRACE_INOUT 	(1 << 0 )
#define APISYSLOG_TRACE_1 		(1 << 1 )
#define APISYSLOG_TRACE_2 		(1 << 2 )
#define APISYSLOG_TRACE_STDERR	(1 << 61 )
#define APISYSLOG_TRACE_STDOUT	(1 << 62 )
#define APISYSLOG_TRACE_NANO	(1 << 63 )
#define APISYSLOG_TRACE_END		0

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

int apisyslog_getflag(uint64_t a_flag);
int apisyslog_PrintLog(const char *pszCompName, const char *a_pszFmt, ...);


#endif /* LIBAPISYSLOG_H_ */

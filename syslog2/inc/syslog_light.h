/*
 * syslog2.h
 *
 *  Created on: Nov 15, 2022
 *      Author: vagrant
 */

#ifndef SYSLOG_LIGHT_H_
#define SYSLOG_LIGHT_H_

#include <sys/syslog.h>

//*******************
//
//*******************
#undef syslog
#undef openlog
#undef closelog
#undef vsyslog

//#define	syslog 		syslog_ng
//#define	openlog		openlog_ng
//#define	closelog	closelog_ng
//#define	vsyslog		vsyslog_ng



/*************************************************
 DATE 	TIMESTAMP 			HOSTNAME  	USER PROC_NAME PID	MSG
 Nov 21 15:24:38.123456789 	buildsystem 	 nmbd[594]:   name_to_nstring: workgroup name USR.INGENICO.LOC is too long. Truncating to
 Nov 21 15:24:48.123456789 	buildsystem      nmbd[594]: 	[2022/11/21 15:24:48.031550,  0] ../source3/nmbd/nmbd_workgroupdb.c:57(name_to_unstring)

 DATE 	TIMESTAMP 	HOSTNAME  	PROCESS_NAME PID	FUNCTIOn IN/OUT	MSG...
 */

#define SYSLOG_MS			(1<<0)
#define SYSLOG_MICRO		(1<<1)
#define SYSLOG_NANO			(1<<2)

#define SYSLOG_IN			(1<<3)
#define SYSLOG_OUT			(1<<4)

#define SYSLOG_HOST			(1<<5)
#define SYSLOG_USER			(1<<6)
#define SYSLOG_PROCESS		(1<<7) // process name
#define SYSLOG_PID			(1<<8)
#define SYSLOG_TID			(1<<9)
#define SYSLOG_FUNCTION		(1<<10)

#define SYSLOG_NONE 	"-"
#define SYSLOG_IN_STR	"_IN"
#define SYSLOG_OUT_STR	"_OUT"

#define SYSLOG_DEF_OPTION	(SYSLOG_NANO|SYSLOG_PID|SYSLOG_TID)

void openlog_ng(const char *ident, int option, int facility);

void syslog_ng(int a_LogOptions,const char* a_FunctionName,int a_Pri, const char *a_Fmt, ...);

void closelog_ng(void);
void vsyslog_ng(int a_LogOptions,const char* a_FunctionName,int a_priority, const char *a_format, va_list a_ap);


#define syslog(a_priority, a_format...)									syslog_ng( SYSLOG_DEF_OPTION ,0, a_priority, a_format)
#define syslog2(a_logOptions,a_functionName,a_priority, a_format...)	syslog_ng( a_logOptions,a_functionName , a_priority, a_format)

#define syslog_IN(a_funcName,...)	\
	a_funcName(__VA_ARGS__) \
	{\
	int result = 0;\
	syslog_ng(SYSLOG_DEF_OPTION|SYSLOG_IN,#a_funcName,LOG_DEBUG,"");


#define syslog_OUT(a_funcName,...)	\
	syslog_ng(SYSLOG_DEF_OPTION|SYSLOG_OUT,#a_funcName,LOG_DEBUG,"result = %d",result); \
	return result; \
	}

#endif /* SYSLOG_LIGHT_H_ */

/*
 * syslog2.h
 *
 *  Created on: Nov 15, 2022
 *      Author: vagrant
 */

#ifndef SYSLOG2_H_
#define SYSLOG2_H_

#include <sys/syslog.h>


/*************************************************
 DATE 	TIMESTAMP 	HOSTNAME  	PROCESS_NAME PID	MSG
 Nov 21 15:24:38 	buildsystem nmbd[594]:   name_to_nstring: workgroup name USR.INGENICO.LOC is too long. Truncating to
 Nov 21 15:24:48 	buildsystem nmbd[594]: [2022/11/21 15:24:48.031550,  0] ../source3/nmbd/nmbd_workgroupdb.c:57(name_to_unstring)

 DATE 	TIMESTAMP 	HOSTNAME  	PROCESS_NAME PID	FUNCTIOn IN/OUT	MSG...


 */

#define LOG_MS				(1<<0)
#define LOG_MICRO			(1<<1)
#define LOG_NANO			(1<<2)
#define LOG_FUNCTION		(1<<3)
#define LOG_IN				(1<<4)
#define LOG_OUT				(1<<5)



 #undef syslog

void syslog2(int pri, const char *fmt, ...);


#endif /* SYSLOG2_H_ */

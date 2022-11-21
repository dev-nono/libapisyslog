/*
 * syslog2.h
 *
 *  Created on: Nov 15, 2022
 *      Author: vagrant
 */

#ifndef SYSLOG2_H_
#define SYSLOG2_H_

#include <syslog.h>

/* Close descriptor used to write to system logger.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
//extern void closelog (void);

/* Open connection to system logger.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
//extern void openlog (const char *__ident, int __option, int __facility);

/* Set the log mask level.  */
//extern int setlogmask (int __mask) __THROW;

/* Generate a log message using FMT string and option arguments.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
//extern void syslog (int __pri, const char *__fmt, ...)
//     __attribute__ ((__format__ (__printf__, 2, 3)));
//
//#ifdef __USE_MISC
///* Generate a log message using FMT and using arguments pointed to by AP.
//
//   This function is not part of POSIX and therefore no official
//   cancellation point.  But due to similarity with an POSIX interface
//   or due to the implementation it is a cancellation point and
//   therefore not marked with __THROW.  */
//extern void vsyslog (int __pri, const char *__fmt, __gnuc_va_list __ap)
//     __attribute__ ((__format__ (__printf__, 2, 0)));
//#endif

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

void syslog2(int pri, int options,const char *fmt, ...);


#define syslog syslog2

#endif /* SYSLOG2_H_ */

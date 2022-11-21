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

#undef syslog


void syslog2(int pri, const char *fmt, ...);

void syslog2(int pri, int options,const char *fmt, ...);


#define syslog syslog2

#endif /* SYSLOG2_H_ */

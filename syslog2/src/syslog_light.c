/*
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <netdb.h>
#include <sys/time.h>

#include <errno.h>
#include <fcntl.h>
#include <paths.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>

#include <stdarg.h>

#include <syslog_light.h>

//**********************************************************
//********	STATIC VARIABLES   *****************************
//**********************************************************

static int	LogType = SOCK_DGRAM;	/* type of socket connection */
static int	LogFile = -1;		/* fd for log */
static int	connected;		/* have done connect */
static int	LogStat;		/* status bits, set by openlog() */
static const char *LogTag;		/* string to tag the entry with */
static int	LogFacility = LOG_USER;	/* default facility code */
static int	LogMask = 0xff;		/* mask of priorities to be logged */
extern char	*__progname;		/* Program name, from crt0. */

//static struct sockaddr_un SyslogAddr;	/* AF_UNIX address of local logger */
static struct sockaddr SyslogAddr;	/* AF_UNIX address of local logger */



//**********************************************************
//********	STATIC FUNCTION   ******************************
//**********************************************************
static int printDate_ng();

#ifndef send_flags
# define send_flags 0
#endif

#if 0
/*
 * syslog, vsyslog --
 *	print message on log file; output is intended for syslogd(8).
 */
/*************************************
 * @fn void syslog2(int, const char*, ...)
 * @brief syslog, vsyslog --
 * 			print message on log file; output is intended for syslogd(8).
 *
 * @pre
 * @post
 * @param a_Pri
 * @param a_Fmt
 */
void syslog_ng(int a_Pri, const char *a_Fmt, ...)
{
	va_list ap;

	va_start(ap, a_Fmt);
	vsyslog_ng(a_Pri, a_Fmt, ap);
	va_end(ap);
}
#endif
/************************************
 * *@fn void syslog3_ng(int, const char*, int, const char*, ...)
 * @brief
 *
 * @pre
 * @post
 * @param a_LogOptions
 * @param a_Function
 * @param a_Pri
 * @param a_Fmt
 */
void syslog_ng(int a_LogOptions,const char* a_Function,int a_Pri, const char *a_Fmt, ...)
{
	va_list ap;

	va_start(ap, a_Fmt);
	vsyslog_ng(a_Pri, a_Fmt, ap);
	va_end(ap);

}
/*****************************************
 * @fn int printDate()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
static int printDate_ng()
{
	int result = 0;

	return result;
}
/**********************************
 * @fn void vsyslog_chk(int, int, const char*, va_list)
 * @brief
 *
 * @pre
 * @post
 * @param a_Pri
 * @param a_Flag
 * @param a_Fmt
 * @param a_ArgList
 */

void vsyslog_ng(int a_Pri, const char *a_Fmt, va_list a_ArgList)
{
	int result = 0;

	struct tm now_tm;
	time_t now;
	int fd;
	FILE *hFileStream;
	char *buf = 0;
	size_t bufsize = 0;
	size_t msgoff;
	char failbuf[3 * sizeof (pid_t) + sizeof "out of memory []"];

#define	INTERNALLOG	LOG_ERR|LOG_CONS|LOG_PERROR|LOG_PID
	//* Check for invalid bits.
	if (a_Pri & ~(LOG_PRIMASK|LOG_FACMASK)) {
		syslog(INTERNALLOG,
				"syslog: unknown facility/priority: %x", a_Pri);
		a_Pri &= LOG_PRIMASK|LOG_FACMASK;
	}

	/* Check priority against setlogmask values. */
	if ((LOG_MASK (LOG_PRI (a_Pri)) & LogMask) == 0)
		return;

	/* Set default facility if none specified. */
	if ((a_Pri & LOG_FACMASK) == 0)
		a_Pri |= LogFacility;

	/* Build the message in a memory-buffer stream.  */
	hFileStream = open_memstream (&buf, &bufsize);
	if (hFileStream == NULL)
	{
		/* We cannot get a stream.  There is not much we can do but
	       emitting an error messages.  */
		char numbuf[3 * sizeof (pid_t)];
		char *nump;
		char *endp = __stpcpy (failbuf, "out of memory [");
		pid_t pid = getpid ();

		nump = numbuf + sizeof (numbuf);
		/* The PID can never be zero.  */
		do
			*--nump = '0' + pid % 10;
		while ((pid /= 10) != 0);

		//	    endp = mempcpy (endp, nump, (numbuf + sizeof (numbuf)) - nump);
		endp = memcpy (endp, nump, (numbuf + sizeof (numbuf)) - nump);
		*endp++ = ']';
		*endp = '\0';
		buf = failbuf;
		bufsize = endp - failbuf;
		msgoff = 0;
	}
	else
	{
		__fsetlocking (hFileStream, FSETLOCKING_BYCALLER);
		fprintf (hFileStream, "<%d>", a_Pri);

		struct timeval tv = {0.0};
		struct tm *pTm = 0;
		//time_t now;
		//*****************************************************
		//*				DATE
		//*****************************************************
		result = gettimeofday(&tv,0);
		//(void) time (&now);
		now = tv.tv_sec;
		pTm = gmtime(&now);

		printf("tv_sec=%ld tv.tv_usec=%06ld \n",tv.tv_sec,tv.tv_usec);
		printf(" %02d:%02d:%02d\n",
				pTm->tm_hour,pTm->tm_min,pTm->tm_sec);


		//	    hFileStream->_IO_write_ptr += strftime (hFileStream->_IO_write_ptr,
		//					      hFileStream->_IO_write_end
		//					      - hFileStream->_IO_write_ptr,
		//					      "%h %e %T ",
		//						  localtime_r (&now, &now_tm));
		//_nl_C_locobj_ptr);
		msgoff = ftell (hFileStream);

		if (LogTag == NULL)
			LogTag = __progname;
		if (LogTag != NULL)
			fputs_unlocked (LogTag, hFileStream);

		fprintf (hFileStream, " %02d:%02d:%02d.%06ld ",
				pTm->tm_hour,pTm->tm_min,pTm->tm_sec,tv.tv_usec);
		//if (LogStat & LOG_PID)
		fprintf (hFileStream, " %d ", (int) getpid ());
		if (LogTag != NULL)
		{
			putc_unlocked (':', hFileStream);
			putc_unlocked (' ', hFileStream);
		}

		//		We have the header.  Print the user's format into the buffer
			vfprintf (hFileStream, a_Fmt, a_ArgList);

		//		Close the memory stream; this will finalize the data
		//	       into a malloc'd buffer in BUF.
		fclose (hFileStream);
	}

#if 0
	//* Output to stderr if requested.
	if (LogStat & LOG_PERROR) {
		struct iovec iov[2];
		struct iovec *v = iov;

		v->iov_base = buf + msgoff;
		v->iov_len = bufsize - msgoff;
		/* Append a newline if necessary.  */
		if (buf[bufsize - 1] != '\n')
		{
			++v;
			v->iov_base = (char *) "\n";
			v->iov_len = 1;
		}

		//		__libc_cleanup_push (free, buf == failbuf ? NULL : buf);

		/* writev is a cancellation point.  */
		(void)writev(STDERR_FILENO, iov, v - iov + 1);

		//		__libc_cleanup_pop (0);
	}
#endif


	/* Get connected, output the message to the local logger. */
	if (!connected)
		openlog_ng(LogTag, LogStat | LOG_NDELAY, 0);

	/* If we have a SOCK_STREAM connection, also send ASCII NUL as
	   a record terminator.  */
	if (LogType == SOCK_STREAM)
		++bufsize;

	if (!connected || send(LogFile, buf, bufsize, send_flags) < 0)
	{
		if (connected)
		{
			// Try to reopen the syslog connection.  Maybe it went		   down.
			closelog_ng ();
			openlog_ng(LogTag, LogStat | LOG_NDELAY, 0);
		}

		if (!connected || send(LogFile, buf, bufsize, send_flags) < 0)
		{
			closelog_ng ();	/* attempt re-open next time */
			/*
			 * Output the message to the console; don't worry
			 * about blocking, if console blocks everything will.
			 * Make sure the error reported is the one from the
			 * syslogd failure.
			 */
#if 0
			if (LogStat & LOG_CONS &&
					(fd = open(_PATH_CONSOLE, O_WRONLY|O_NOCTTY, 0)) >= 0)
			{
				dprintf (fd, "%s\r\n", buf + msgoff);
				(void)close(fd);
			}
#endif
		}
	}


	if (buf != failbuf)
		free (buf);

}
/***************
 * @fn void openlog_ng(const char*, int, int)
 * @brief
 *
 * @pre
 * @post
 * @param ident
 * @param logstat
 * @param logfac
 */
void openlog_ng(const char *ident, int logstat, int logfac)
{
	if (ident != NULL)
		LogTag = ident;
	LogStat = logstat;
	if (logfac != 0 && (logfac &~ LOG_FACMASK) == 0)
		LogFacility = logfac;

	int retry = 0;
	while (retry < 2)
	{
		if (LogFile == -1)
		{
			//			SyslogAddr.sun_family = AF_UNIX;
			//			(void)strncpy(SyslogAddr.sun_path, _PATH_LOG,
			//				      sizeof(SyslogAddr.sun_path));

			SyslogAddr.sa_family = AF_UNIX;
			(void)strncpy(SyslogAddr.sa_data, _PATH_LOG,
					sizeof(SyslogAddr.sa_data));

			if (LogStat & LOG_NDELAY) {
				LogFile = socket(AF_UNIX, LogType | SOCK_CLOEXEC, 0);
				if (LogFile == -1)
					return;
			}
		}
		if (LogFile != -1 && !connected)
		{
			//			int old_errno = errno;
			if (connect(LogFile, &SyslogAddr, sizeof(SyslogAddr))
					== -1)
			{
				int saved_errno = errno;
				int fd = LogFile;
				LogFile = -1;
				(void)close(fd);
				//				__set_errno (old_errno);
				if (saved_errno == EPROTOTYPE)
				{
					/* retry with the other type: */
					LogType = (LogType == SOCK_DGRAM
							? SOCK_STREAM : SOCK_DGRAM);
					++retry;
					continue;
				}
			} else
				connected = 1;
		}
		break;
	}
}


void closelog_ng (void)
{
	if (!connected)
		return;

	close (LogFile);
	LogFile = -1;
	connected = 0;

	LogTag = NULL;
	LogType = SOCK_DGRAM; /* this is the default */

}

#if 0
// setlogmask -- set the log mask level
static int setlogmask_ng (int pmask)
{
	int omask;

	omask = LogMask;
	if (pmask != 0)
		LogMask = pmask;
	return (omask);
}
#endif

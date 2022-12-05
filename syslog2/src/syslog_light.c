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

//*********************************************************
//*******	STATIC VARIABLES   *****************************
//*********************************************************
struct s_local_data
{

//int			LogType 		= SOCK_DGRAM;	// type of socket connection
//int			LogFile 		= -1;			// fd for log
//int			connected		= 0;			// have done connect
//int			LogStat;		= 0;			// status bits, set by openlog()
//const char 	*LogTag;		= 0;			// string to tag the entry with
//int			LogFacility 	= LOG_USER;		// default facility code
//int			LogMask 		= 0xff;			// mask of priorities to be logged

	int			LogType;	// type of socket connection
	int			LogFile;	// fd for log
	int			connected;	// have done connect
	int			LogStat;	// status bits, set by openlog()
	const char 	*LogTag;	// string to tag the entry with //TODO const char LogTag
	int			LogFacility;// default facility code
	int			LogMask;	// mask of priorities to be logged

	//static struct sockaddr_un SyslogAddr;	/* AF_UNIX address of local logger
	struct sockaddr SyslogAddr;	// AF_UNIX address of local logger

	int			init;
};
struct s_local_data g_localData = {0};

//g_localData. //SOCK_DGRAM,-1,0,0,0,LOG_USER,0xFF,{0,{0}}};

void init_LocalData()
{
	if( 0 == g_localData.init)
	{
		g_localData.LogType		= SOCK_DGRAM;	// type of socket connection
		g_localData.LogFile 	= -1;			// fd for log
		g_localData.connected	= 0;			// have done connect
		g_localData.LogStat		= 0;			// status bits, set by openlog()
		g_localData.LogTag		= 0;			// string to tag the entry with
		g_localData.LogFacility = LOG_USER;		// default facility code
		g_localData.LogMask 	= 0xFF;			// mask of priorities to be logged

		g_localData.init 		= 1;
	}
}



extern char	*__progname;			// Program name, from crt0.



//*********************************************************
//*******	STATIC FUNCTION   ******************************
//*********************************************************
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
void syslog_ng(int a_LogOptions,const char* a_FunctionName,int a_Pri, const char *a_Fmt, ...)
{
	//***************************************
	//*	initialize global data
	//***************************************
	init_LocalData();

	va_list ap;

	va_start(ap, a_Fmt);
	vsyslog_ng(a_LogOptions,a_FunctionName, a_Pri, a_Fmt, ap);
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
void vsyslog_ng(int a_LogOptions,const char* a_FunctionName,int a_priority, const char *a_format, va_list a_ap)
{
	//***************************************
	//*	initialize global data
	//***************************************
	init_LocalData();

	int result = 0;

	struct tm now_tm;
	time_t now;
	int fd;
	FILE *hFileStream;
	char *bufToPrint = 0;
	size_t bufsize = 0;
	size_t msgoff;
	char failbuf[3 * sizeof (pid_t) + sizeof "out of memory []"];

#define	INTERNALLOG	LOG_ERR|LOG_CONS|LOG_PERROR|LOG_PID
	// Check for invalid bits.
	if (a_priority & ~(LOG_PRIMASK|LOG_FACMASK)) {
		syslog(INTERNALLOG,
				"syslog: unknown facility/priority: %x", a_priority);
		a_priority &= LOG_PRIMASK|LOG_FACMASK;
	}

	// Check priority against setg_localData.LogMask values.
	if ((LOG_MASK (LOG_PRI (a_priority)) & g_localData.LogMask) == 0)
		return;

	// Set default facility if none specified.
	if ((a_priority & LOG_FACMASK) == 0)
		a_priority |= g_localData.LogFacility;

	// Build the message in a memory-buffer stream.
	hFileStream = open_memstream (&bufToPrint, &bufsize);
#if 0
	if (hFileStream == NULL)
	{
		// We cannot get a stream.  There is not much we can do but
	    //   emitting an error messages.
		char numbuf[3 * sizeof (pid_t)];
		char *nump;
		char *endp = __stpcpy (failbuf, "out of memory [");
		pid_t pid = getpid ();

		nump = numbuf + sizeof (numbuf);
		// The PID can never be zero.
		do
			*--nump = '0' + pid % 10;
		while ((pid /= 10) != 0);

		//	    endp = mempcpy (endp, nump, (numbuf + sizeof (numbuf)) - nump);
		endp = memcpy (endp, nump, (numbuf + sizeof (numbuf)) - nump);
		*endp++ = ']';
		*endp = '\0';
		bufToPrint = failbuf;
		bufsize = endp - failbuf;
		msgoff = 0;
	}
	else
#endif
	{
		__fsetlocking (hFileStream, FSETLOCKING_BYCALLER);
		fprintf (hFileStream, "<%d>", a_priority);

		struct timeval tv = {0.0};
		struct tm *pTm = 0;
		//time_t now;
		//****************************************************
		//				DATE
		//****************************************************
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

		if (g_localData.LogTag == NULL)
			g_localData.LogTag = __progname;
		if (g_localData.LogTag != NULL)
			fputs_unlocked (g_localData.LogTag, hFileStream);

		fprintf (hFileStream, " %02d:%02d:%02d.%06ld ",
				pTm->tm_hour,pTm->tm_min,pTm->tm_sec,tv.tv_usec);
		//if (g_localData.LogStat & LOG_PID)
		fprintf (hFileStream, " %d ", (int) getpid ());
		if (g_localData.LogTag != NULL)
		{
			putc_unlocked (':', hFileStream);
			putc_unlocked (' ', hFileStream);
		}

		//		We have the header.  Print the user's format into the buffer
			vfprintf (hFileStream, a_format, a_ap);

		//		Close the memory stream; this will finalize the data
		//	       into a malloc'd buffer in BUF.
		fclose (hFileStream);

		printf("%s\n",bufToPrint);
	}

#if 0
	// Output to stderr if requested.
	if (g_localData.LogStat & LOG_PERROR) {
		struct iovec iov[2];
		struct iovec *v = iov;

		v->iov_base = bufToPrint + msgoff;
		v->iov_len = bufsize - msgoff;
		// Append a newline if necessary.
		if (bufToPrint[bufsize - 1] != '\n')
		{
			++v;
			v->iov_base = (char *) "\n";
			v->iov_len = 1;
		}

		//		__libc_cleanup_push (free, buf == failbuf ? NULL : buf);

		// writev is a cancellation point.
		(void)writev(STDERR_FILENO, iov, v - iov + 1);

		//		__libc_cleanup_pop (0);
	}
#endif


	// Get g_localData.connected, output the message to the local logger.
	if (!g_localData.connected)
		openlog_ng(g_localData.LogTag, g_localData.LogStat | LOG_NDELAY, 0);

	// If we have a SOCK_STREAM connection, also send ASCII NUL as
	//   a record terminator.
	if (g_localData.LogType == SOCK_STREAM)
		++bufsize;

	if (!g_localData.connected || send(g_localData.LogFile, bufToPrint, bufsize, send_flags) < 0)
	{
		if (g_localData.connected)
		{
			// Try to reopen the syslog connection.  Maybe it went		   down.
			closelog_ng ();
			openlog_ng(g_localData.LogTag, g_localData.LogStat | LOG_NDELAY, 0);
		}

		if (!g_localData.connected || send(g_localData.LogFile, bufToPrint, bufsize, send_flags) < 0)
		{
			closelog_ng ();	/* attempt re-open next time */
			/*
			 * Output the message to the console; don't worry
			 * about blocking, if console blocks everything will.
			 * Make sure the error reported is the one from the
			 * syslogd failure.
			 */
#if 0
			if (g_localData.LogStat & LOG_CONS &&
					(fd = open(_PATH_CONSOLE, O_WRONLY|O_NOCTTY, 0)) >= 0)
			{
				dprintf (fd, "%s\r\n", bufToPrint + msgoff);
				(void)close(fd);
			}
#endif
		}
	}


	if (bufToPrint != failbuf)
		free (bufToPrint);

}

/***************
 * @fn void openlog_ng(const char*, int, int)
 * @brief
 *
 * @pre
 * @post
 * @param ident
 * @param g_localData.LogStat
 * @param logfac
 */
void openlog_ng(const char *a_ident, int a_LogStat, int a_logfac)
{
	//***************************************
	//*	initialize global data
	//***************************************
	init_LocalData();


	if (a_ident != NULL)
		g_localData.LogTag = a_ident;
	g_localData.LogStat = a_LogStat;
	if (a_logfac != 0 && (a_logfac &~ LOG_FACMASK) == 0)
		g_localData.LogFacility = a_logfac;

	int retry = 0;
	while (retry < 2)
	{
		if (g_localData.LogFile == -1)
		{
			//			SyslogAddr.sun_family = AF_UNIX;
			//			(void)strncpy(SyslogAddr.sun_path, _PATH_LOG,
			//				      sizeof(SyslogAddr.sun_path));

			g_localData.SyslogAddr.sa_family = AF_UNIX;
			(void)strncpy(g_localData.SyslogAddr.sa_data, _PATH_LOG,
					sizeof(g_localData.SyslogAddr.sa_data));

			if (g_localData.LogStat & LOG_NDELAY) {
				g_localData.LogFile = socket(AF_UNIX, g_localData.LogType | SOCK_CLOEXEC, 0);
				if (g_localData.LogFile == -1)
					return;
			}
		}
		if (g_localData.LogFile != -1 && !g_localData.connected)
		{
			//			int old_errno = errno;
			if (connect(g_localData.LogFile, &g_localData.SyslogAddr, sizeof(g_localData.SyslogAddr))
					== -1)
			{
				int saved_errno = errno;
				int fd = g_localData.LogFile;
				g_localData.LogFile = -1;
				(void)close(fd);
				//				__set_errno (old_errno);
				if (saved_errno == EPROTOTYPE)
				{
					/* retry with the other type: */
					g_localData.LogType = (g_localData.LogType == SOCK_DGRAM
							? SOCK_STREAM : SOCK_DGRAM);
					++retry;
					continue;
				}
			} else
				g_localData.connected = 1;
		}
		break;
	}
}


void closelog_ng (void)
{
	if (!g_localData.connected)
		return;

	close (g_localData.LogFile);
	g_localData.LogFile = -1;
	g_localData.connected = 0;

	g_localData.LogTag = NULL;
	g_localData.LogType = SOCK_DGRAM; /* this is the default */

}

#if 0
// setg_localData.LogMask -- set the log mask level
static int setg_localData.LogMask_ng (int pmask)
{
	int omask;

	omask = g_localData.LogMask;
	if (pmask != 0)
		g_localData.LogMask = pmask;
	return (omask);
}
#endif

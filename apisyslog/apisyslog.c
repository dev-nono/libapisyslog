/*
 * appsyslog.c
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#define _GNU_SOURCE         /* Consultez feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h>   /* Pour les définitions de SYS_xxx */

#include <errno.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/inotify.h>
#include <pthread.h>
#include <libgen.h>

#include <string.h>


#include "apisyslog_int.h"
#include "apisyslog.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

struct sTagId gArrayTagId[] =
{
		{"trace.inout", APISYSLOG_TRACE_INOUT},
		{"trace.dbg1", APISYSLOG_TRACE_1},
		{"trace.dbg2", APISYSLOG_TRACE_2},
		{"", APISYSLOG_TRACE_END}
};

sConfigSyslog_t gConfig;

//*********************************************************
//*
//*********************************************************
int apisyslog_init(const char* a_ConfigFilemame)
{
	int result = 0;
	char 	*pathname = 0;
	char 	linkbuf[PATH_MAX];

	memset(&gConfig,0,sizeof(gConfig));
	memset(linkbuf,0,sizeof(linkbuf));

	if( *a_ConfigFilemame == 0 )
	{
		readlink("/proc/self/exe", linkbuf, PATH_MAX-1);
		pathname = dirname(linkbuf);
		snprintf(gConfig.configFilename,PATH_MAX-1,"%s/debugtrace.conf", pathname);
	}
	else
	{
		strncpy(gConfig.configFilename,a_ConfigFilemame,PATH_MAX-1);
	}
	strncpy(gConfig.prefix,"PREFIX",100-1);

	openlog(gConfig.prefix, LOG_NDELAY | LOG_PID , LOG_LOCAL7);


	result = apisyslog_StartThread();

	return result;
}


//*********************************************************
//*
//*********************************************************
int apisyslog_release()
{
	int result = 0;


	return result;
}

//*********************************************************
//*
//*********************************************************
static void * apisyslog_thread_body(void *arg)
{
	int		result	= 0;
	char 	buffer[EVENT_BUF_LEN];

	(void)result;

	result = apisyslog_readFile();

	result = apisyslog_ConfigureInotify();

	do
	{
		result = read(gConfig.fdInit,buffer,EVENT_BUF_LEN);

		result = apisyslog_parseMessage(buffer);

	}while(1);

	inotify_rm_watch( gConfig.fdInit, gConfig.fdWatch);

	close(gConfig.fdWatch);
	close(gConfig.fdInit);

	return (void*) 0;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_parseMessage(const char* a_Buffer)
{
	int result 	= 0;
	int ii 		= 0;

	inotify_rm_watch( gConfig.fdInit, gConfig.fdWatch);
	close(gConfig.fdWatch);

	while ( ii < EVENT_BUF_LEN )
	{
		struct inotify_event *event = ( struct inotify_event * ) &a_Buffer[ ii ];
		if ( ( event->len ) && (event->mask & IN_MODIFY))
		{
			result = apisyslog_release();
			break; // one event need
		}
		ii += EVENT_SIZE + event->len;
	}

	gConfig.fdWatch = inotify_add_watch( 	gConfig.fdInit,
			gConfig.configFilename,
			IN_MODIFY);

	return result;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_readFile()
{
	int 	result  = 0;
	FILE* 	fd		= 0;
	char 	buffer[APISYSLOG_TAG_SIZE];
	char*	pBuffer = 0;
	char 	buffTag[APISYSLOG_TAG_SIZE];
	char 	buffTagValue[APISYSLOG_TAG_SIZE];
	int		lenBuff = 0;

	int		bitTag = 0;

	fd = fopen(gConfig.configFilename,"rt");

	if( fd == 0 )
	{
		result = errno;
	}
	else
	{
		while ( ! feof( fd ) )
		{
			memset(buffTag,0,sizeof(buffTag));
			memset(buffTagValue,0,sizeof(buffTagValue));
			memset(buffer,0,sizeof(buffer));


			fgets(buffer,APISYSLOG_TAG_SIZE,fd);

			lenBuff = strlen(buffer);

			if( buffer[lenBuff-1] == '\n')
				buffer[lenBuff-1] = 0;

			sscanf(buffer,"%[^=]=%s",buffTag,buffTagValue);

			bitTag = apisyslog_findTag(buffTag);

			printf("buffTag=%s buffTagValue=%s bitTag=%d\n",buffTag,buffTagValue,bitTag);

			if( bitTag >= 0 )
			{
				gConfig.flag |=  gArrayTagId[bitTag].id;
			}
		}
	}

	if( fd > 0 )
	{
		fclose(fd);
	}

	return result;
}

//*********************************************************
//*
//*********************************************************
int apisyslog_findTag(const char* a_Buffer)
{
	int  result = -1;
	int  ii = 0;

	do
	{
		if( gArrayTagId[ii].id == APISYSLOG_TRACE_END)
		{
			break;
		}
		else
		{
			if( strcmp(gArrayTagId[ii].tag,a_Buffer) == 0 )
			{
				result = ii;
				break;
			}
		}

		ii++;

	}while(1);

	return result;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_ConfigureInotify()
{
	int result = 0;


	gConfig.fdInit = inotify_init1(IN_CLOEXEC);

	if ( gConfig.fdInit < 0 )
	{
		fprintf(stderr,"Error inotify_init()  err<=%d %s",errno, strerror(errno) );
		result = errno;
	}
	if( result == 0)
	{
		gConfig.fdWatch = inotify_add_watch( 	gConfig.fdInit,
				gConfig.configFilename,
				IN_MODIFY);
	}

	return result;
}
//*********************************************************
//*
//*********************************************************

//*********************************************************
//*
//*********************************************************
int apisyslog_StartThread()
{
	int result 	= 0;
	pthread_attr_t attr;

	result = pthread_attr_init(&attr);
	if (result  != 0)
	{
		fprintf(stderr,"Error pthread_attr_init()  err<=%d %s",errno, strerror(errno) );
	}

	if( result == 0)
	{
		//The pthread_create() call stores the thread ID

		result = pthread_create(&gConfig.thread_id, &attr,
				&apisyslog_thread_body, (void*)NULL);

		if (result  != 0)
			fprintf(stderr,"Error pthread_create()  err<=%d %s",
					errno, strerror(errno) );
	}
	//Destroy the thread attributes object, since it is no longer needed
	pthread_attr_destroy(&attr);

	/* Now join with each thread, and display its returned value */
	result  = pthread_join(gConfig.thread_id, NULL);

	return result;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_getflag(uint64_t a_flag)
{
	int result = 0;

	result = gConfig.flag & a_flag;

	return result;
}


int apisyslog_PrintLog(const char *pszCompName, const char *a_pszFmt, ...)
{
	char 				vMessage[255];
	char 				vMessageToPrint[512];
	//
	int vNBuf = 0;
	int					vRetcode			= 0;
	va_list 			pVa_list;
	//struct timeval		vTimeval;

	(void)vNBuf;
	va_start(pVa_list, a_pszFmt);

	// Format user arguments
	vNBuf = vsnprintf(vMessage , 255, a_pszFmt, pVa_list);

	//	gettimeofday(&vTimeval,0);
	//		fprintf(getFdLog(),
	//                        //"%s %lu %-20s %s\n",
	//                        "%ld.%06ld %d %-20s %s\n",
	//						//vBuffDate,
	//						vTimeval.tv_sec,
	//						vTimeval.tv_usec,
	//						(int)syscall(SYS_gettid),
	//						pszCompName ? pszCompName : "",
	//						vMessage);
	//		fflush(getFdLog());


	//*********SYSLOG****########### APP #####
	// date				 TID   function	MESSAGE
	// 10:34:03.757525   14588 foo_ 		OUT_1 result = 1

	snprintf( vMessageToPrint, 512-1 , "%d %s %s",
			(int)syscall(SYS_gettid),
			pszCompName,
			vMessage);

	syslog(LOG_DEBUG,"%s",vMessageToPrint);

	va_end(pVa_list);

	return vRetcode;
}


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
#include <time.h>

#include <string.h>


#include "apisyslog_int.h"
#include "apisyslog.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

struct sTagId gArrayTagIdTrace[] =
{
        {"trace.inout",     APISYSLOG_TRACE_INOUT},
        {"trace.dbg1",      APISYSLOG_TRACE_1},
        {"trace.dbg2",      APISYSLOG_TRACE_2},

        {"trace.nano",      APISYSLOG_TRACE_NANO},
        {"trace.stdout",    APISYSLOG_TRACE_STDOUT},
        {"trace.stderr",    APISYSLOG_TRACE_STDERR},
        {"",                APISYSLOG_TRACE_END}
};
struct sTagId gArrayTagIdDebug[] =
{
        {APISYSLOG_DEBUG_FIFO,      0  },
        {APISYSLOG_DEBUG_WAIT1,     APISYSLOG_DBG_WAIT1},
        {APISYSLOG_DEBUG_WAIT2,     APISYSLOG_DBG_WAIT2},

        {"",                APISYSLOG_TRACE_END}
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
    char 	filename[PATH_MAX];

    memset(&gConfig,0,sizeof(gConfig));

    if( *a_ConfigFilemame == 0 )
    {
        readlink("/proc/self/exe", linkbuf, PATH_MAX-1);
        strncpy(filename,linkbuf,APISYSLOG_TAG_SIZE-1);
        pathname = dirname(linkbuf);

        snprintf(gConfig.dirname,PATH_MAX-1,"%s",pathname);
        snprintf(gConfig.basename,APISYSLOG_TAG_SIZE-1,"debugtrace.conf");
    }
    else
    {
        strncpy(filename,a_ConfigFilemame,PATH_MAX-1);
        pathname = basename(filename);
        strncpy(gConfig.basename,filename,APISYSLOG_TAG_SIZE-1);
    }
    snprintf(gConfig.filename,PATH_MAX,"%s/%s",gConfig.dirname,gConfig.basename);

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
    fd_set 	rfds;

    (void)result;

    result = apisyslog_readFile();

    gConfig.fdInit = inotify_init1(IN_CLOEXEC);

    do
    {
        gConfig.fdWatch = inotify_add_watch( 	gConfig.fdInit,
                gConfig.dirname,
                IN_MODIFY //| IN_CLOSE_WRITE
        );

        FD_ZERO(&rfds);
        FD_SET(gConfig.fdInit , &rfds);

        result = select(gConfig.fdInit+1, &rfds, NULL, NULL, NULL);

        inotify_rm_watch( gConfig.fdInit, gConfig.fdWatch);

        result = read(gConfig.fdInit ,buffer,EVENT_BUF_LEN);

        result = apisyslog_CheckModify(buffer);
        if( result > 0 )
        {
            apisyslog_readFile();
        }
    }while(1);

    inotify_rm_watch( gConfig.fdInit, gConfig.fdWatch);

    close(gConfig.fdWatch);
    close(gConfig.fdInit);

    return (void*) 0;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_CheckModify(const char* a_Buffer)
{
    int result 	= 0;
    int ii 		= 0;

    while ( ii < EVENT_BUF_LEN )
    {
        struct inotify_event *event = ( struct inotify_event * ) &a_Buffer[ ii ];
        if ( ( event->mask != 0 )
                && ( 0 == strcmp( event->name,gConfig.basename)))
        {
            //            printf("mask=%X name=%s \n",event->mask,event->name);
            result = 1;
            break; // one event need
        }
        ii += EVENT_SIZE + event->len;
    }
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
    //	char*	pBuffer = 0;
    char 	buffTag[APISYSLOG_TAG_SIZE];
    char 	buffTagValue[APISYSLOG_TAG_SIZE];
    int 	vTagValue = 0;
    int		lenBuff = 0;

    int		bitTag = 0;
    gConfig.flag = 0;

    //	printf("apisyslog_readFile \n");

    fd = fopen(gConfig.filename,"rt");

    if( fd == 0 )
    {
        result = errno;
    }
    else
    {

        while ( ! feof( fd ) )
        {
            memset(buffTag,0,sizeof(buffTag));
            //memset(buffTagValue,0,sizeof(buffTagValue));
            memset(buffer,0,sizeof(buffer));

            fgets(buffer,APISYSLOG_TAG_SIZE,fd);

            lenBuff = strlen(buffer);

            if( buffer[lenBuff-1] == '\n')
                buffer[lenBuff-1] = 0;

            //sscanf(buffer,"%[^=]=%d",buffTag,&buffTagValue);
            sscanf(buffer,"%[^=]=%s",buffTag,&buffTagValue);

            // ******************************************
            //      TRACE
            // ******************************************
            bitTag = apisyslog_findTagTrace(buffTag);

            if( bitTag >= 0 )
            {
                    //&& 	( buffTagValue != 0) )

                gConfig.flag |=  gArrayTagIdTrace[bitTag].id;
                //printf("buffTag=%s buffTagValue=%d bitTag=%d\n",buffTag,buffTagValue,bitTag);
            }
            // ******************************************
            //      DEBUG
            // ******************************************
           if( bitTag < 0 )
           {
               bitTag = apisyslog_findTagDebug(buffTag);

               if(     ( bitTag >= 0 ) )
                   //&&  ( buffTagValue != 0) )
               {
                   if( 0 == strcmp(buffTag,APISYSLOG_DEBUG_FIFO ) )
                   {
                       strcpy(gConfig.fifoname,bufft
                   }

                       gConfig.flag |=  gArrayTagIdDebug[bitTag].id;
                   //                printf("buffTag=%s buffTagValue=%d bitTag=%d\n",buffTag,buffTagValue,bitTag);
               }

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
int apisyslog_findTagTrace(const char* a_Buffer)
{
    int  result = -1;
    int  ii = 0;

    do
    {
        if( gArrayTagIdTrace[ii].id == APISYSLOG_TRACE_END)
        {
            break;
        }
        else
        {
            if( strcmp(gArrayTagIdTrace[ii].tag,a_Buffer) == 0 )
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
int apisyslog_findTagDebug(const char* a_Buffer)
{
    int  result = -1;
    int  ii = 0;

    do
    {
        if( gArrayTagIdDebug[ii].id == APISYSLOG_TRACE_END)
        {
            break;
        }
        else
        {
            if( strcmp(gArrayTagIdDebug[ii].tag,a_Buffer) == 0 )
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

    return result;
}
//*********************************************************
//*
//*********************************************************
uint64_t apisyslog_getflag(uint64_t a_flag)
{
    uint64_t result = 0;
    result = gConfig.flag & a_flag;

    //    printf("apisyslog_getflag %lX result=%lX\n",gConfig.flag,result);

    return result;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_PrintLog(const char *pszFuncName, const char *a_pszFmt, ...)
{
    char 				vMessage[255];
    char                vNano[25];
    char 				vMessageToPrint[512];
    int 				vTid = (int)syscall(SYS_gettid);
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
    // date				 NANO           TID   	function	MESSAGE
    // 10:34:03.757525   10.123456789   14588   foo_ 		OUT_1 result = 1

    //*********************************************************
    //              APISYSLOG_TRACE_NANO
    //*********************************************************
    *vNano = 0;
    if( apisyslog_getflag( APISYSLOG_TRACE_NANO ) )
    {
        struct timespec vRes = {0,0};
        vRetcode = clock_gettime(CLOCK_MONOTONIC_RAW,&vRes);
        snprintf(vNano,25, "%4ld.%09ld",vRes.tv_sec,vRes.tv_nsec);
    }

    //*********************************************************
    //              PRINT SYSLOG
    //*********************************************************

    snprintf( vMessageToPrint, 512-1 , "%s %5d %s %s",
            vNano,
            vTid,
            pszFuncName,
            vMessage);

    syslog(LOG_DEBUG,"%s",vMessageToPrint);

    //*********************************************************
    //              APISYSLOG_TRACE_STDOUT
    //*********************************************************
    if( apisyslog_getflag( APISYSLOG_TRACE_STDOUT ) )
    {
        fprintf(stdout,"%s\n",vMessageToPrint);
    }
    //*********************************************************
    //              APISYSLOG_TRACE_STDERR
    //*********************************************************
    if( apisyslog_getflag( APISYSLOG_TRACE_STDERR ) )
    {
        fprintf(stderr,"%s\n",vMessageToPrint);
    }

    va_end(pVa_list);

    return vRetcode;
}

int apisyslog_Wait(uint64_t a_flag)
{
    uint64_t result = 0;
    result = gConfig.flag & a_flag;

    if ( result )
    {

    }

    return result;
}

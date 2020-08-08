/*
 * appsyslog.c
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

//#define _GNU_SOURCE         /* Consultez feature_test_macros(7) */
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
#include <syslog.h>
#include <stdio.h>
#include <sys/stat.h>
#include <poll.h>


#include <string.h>

#include "apisyslog_int.h"
#include "apisyslog.h"
#include "utilstools.h"

// #define PRINT_DBG 1

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

struct sTagId gArrayTagIdTrace[] =
{
        {"trace.in",        APISYSLOG_TRACE_IN},
        {"trace.out",       APISYSLOG_TRACE_OUT},
        {"trace.inout",     APISYSLOG_TRACE_INOUT},

        {"trace.nano",      APISYSLOG_TRACE_NANO},
        {"trace.stdout",    APISYSLOG_TRACE_STDOUT},
        {"trace.stderr",    APISYSLOG_TRACE_STDERR},
        {"trace.log",       APISYSLOG_TRACE_LOG},
        {"trace.err",       APISYSLOG_TRACE_ERR},

        {"trace.dbg1",       APISYSLOG_TRACE_1},
        {"trace.dbg2",       APISYSLOG_TRACE_2},
        {"trace.dbg3",       APISYSLOG_TRACE_3},
        {"trace.dbg4",       APISYSLOG_TRACE_4},
        {"trace.dbg5",       APISYSLOG_TRACE_5},
        {"trace.dbg6",       APISYSLOG_TRACE_6},
        {"trace.dbg7",       APISYSLOG_TRACE_7},
        {"trace.dbg8",       APISYSLOG_TRACE_8},
        {"trace.dbg9",       APISYSLOG_TRACE_9},
        {"trace.dbg10",      APISYSLOG_TRACE_10},
        {"trace.dbg11",      APISYSLOG_TRACE_11},
        {"trace.dbg12",      APISYSLOG_TRACE_12},
        {"trace.dbg13",      APISYSLOG_TRACE_13},
        {"trace.dbg14",      APISYSLOG_TRACE_14},
        {"trace.dbg15",      APISYSLOG_TRACE_15},
        {"trace.dbg16",      APISYSLOG_TRACE_16},
        {"trace.dbg17",      APISYSLOG_TRACE_17},
        {"trace.dbg18",      APISYSLOG_TRACE_18},
        {"trace.dbg19",      APISYSLOG_TRACE_19},
        {"trace.dbg20",      APISYSLOG_TRACE_20},
        {"trace.dbg21",      APISYSLOG_TRACE_21},
        {"trace.dbg22",      APISYSLOG_TRACE_22},
        {"trace.dbg23",      APISYSLOG_TRACE_23},
        {"trace.dbg24",      APISYSLOG_TRACE_24},
        {"trace.dbg25",      APISYSLOG_TRACE_25},
        {"trace.dbg26",      APISYSLOG_TRACE_26},
        {"trace.dbg27",      APISYSLOG_TRACE_27},
        {"trace.dbg28",      APISYSLOG_TRACE_28},
        {"trace.dbg29",      APISYSLOG_TRACE_29},
        {"trace.dbg30",      APISYSLOG_TRACE_30},
        {"trace.dbg31",      APISYSLOG_TRACE_31},
        {"trace.dbg32",      APISYSLOG_TRACE_32},
        {"trace.dbg33",      APISYSLOG_TRACE_33},
        {"trace.dbg34",      APISYSLOG_TRACE_34},
        {"trace.dbg35",      APISYSLOG_TRACE_35},
        {"trace.dbg36",      APISYSLOG_TRACE_36},
        {"trace.dbg37",      APISYSLOG_TRACE_37},
        {"trace.dbg38",      APISYSLOG_TRACE_38},
        {"trace.dbg39",      APISYSLOG_TRACE_39},
        {"trace.dbg40",      APISYSLOG_TRACE_40},
        {"trace.dbg41",      APISYSLOG_TRACE_41},
        {"trace.dbg42",      APISYSLOG_TRACE_42},
        {"trace.dbg43",      APISYSLOG_TRACE_43},
        {"trace.dbg44",      APISYSLOG_TRACE_44},
        {"trace.dbg45",      APISYSLOG_TRACE_45},
        {"trace.dbg46",      APISYSLOG_TRACE_46},
        {"trace.dbg47",      APISYSLOG_TRACE_47},
        {"trace.dbg48",      APISYSLOG_TRACE_48},
        {"trace.dbg49",      APISYSLOG_TRACE_49},
        {"trace.dbg50",      APISYSLOG_TRACE_50},



        {"",                APISYSLOG_TRACE_END}
};
struct sTagId gArrayTagIdDebug[] =
{
        {APISYSLOG_DEBUG_FIFO,      0  },
        {APISYSLOG_DEBUG_WAIT1,     APISYSLOG_DBG_WAIT1},
        {APISYSLOG_DEBUG_WAIT2,     APISYSLOG_DBG_WAIT2},

        {"",                APISYSLOG_TRACE_END}
};

sConfigSyslog_t g_Config = {0};

//*********************************************************
//*
//*********************************************************
int apisyslog_init(const char* a_ConfigFilemame)
{
    int result = 0;
    char 	*pPathname = 0;
    char    *pBasename  = 0;
    char 	linkbuf[PATH_MAX];
    char 	filename[PATH_MAX];

    memset(&g_Config,0,sizeof(g_Config));

    readlink("/proc/self/exe", linkbuf, PATH_MAX-1);


    if( *a_ConfigFilemame == 0 )
    {
        strncpy(filename,linkbuf,APISYSLOG_TAG_SIZE-1);

        pPathname = dirname(filename);
        snprintf(g_Config.process_dirname,PATH_MAX-1,"%s",pPathname);

        strncpy(filename,linkbuf,APISYSLOG_TAG_SIZE-1);

        pBasename = basename(filename);
        snprintf(g_Config.process_basename,APISYSLOG_TAG_SIZE-1,"%s",pBasename);
    }
    else
    {
        strncpy(filename,a_ConfigFilemame,APISYSLOG_TAG_SIZE-1);

        pPathname = dirname(filename);
        snprintf(g_Config.process_dirname,PATH_MAX-1,"%s",pPathname);

        strncpy(filename,a_ConfigFilemame,APISYSLOG_TAG_SIZE-1);

        pBasename = basename(filename);
        snprintf(g_Config.process_basename,APISYSLOG_TAG_SIZE-1,"%s",pBasename);
    }
    snprintf(g_Config.config_filename,PATH_MAX,"%s/%s",
            g_Config.process_dirname,
            APISYSLOG_CONFIG_FILENAME);

#ifdef  PRINT_DBG
    printf("%s : g_Config.config_filename=%s \n",
            __FUNCTION__, g_Config.config_filename);
#endif
    strncpy(g_Config.prefix,"PREFIX",100-1);

    openlog(g_Config.prefix, LOG_NDELAY | LOG_PID , LOG_LOCAL7);

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
    struct pollfd   vPollfd = {0};
    nfds_t          vNfds    = 1;
    int             vTimeout = -1;


    (void)result;
    (void)arg;

    result = apisyslog_readFile();

    errno = 0;
    result = sem_post(&g_Config.semaphore);
    if (0 != result )
    {
        fprintf(stderr,"%s Error sem_post()  err=%d %s \n",
                __FUNCTION__,errno, strerror(errno) );
        result = errno;
    }

    g_Config.fdInit = inotify_init1(IN_CLOEXEC);

    do
    {
        g_Config.fdWatch = inotify_add_watch( 	g_Config.fdInit,
                g_Config.process_dirname,
                IN_MODIFY //| IN_CLOSE_WRITE
        );

        vPollfd.fd =  g_Config.fdInit;
        vPollfd.events = POLLIN | POLLPRI ;
        vPollfd.revents = 0;
        errno = 0;

        result  = poll(&vPollfd, vNfds, vTimeout);

#ifdef  PRINT_DBG
        printf("%s : _4_ poll  result=%d: revents=%d 0x%X \n",
                __FUNCTION__,result,
                (int)vPollfd.revents,(int)vPollfd.revents);
#endif

        inotify_rm_watch( g_Config.fdInit, g_Config.fdWatch);

        result = read(g_Config.fdInit ,buffer,EVENT_BUF_LEN);

#ifdef  PRINT_DBG
        printf("%s: %d = read(fd=%d size=%ld) \n",
                __FUNCTION__,result, g_Config.fdInit, EVENT_BUF_LEN);
#endif

        result = apisyslog_CheckModify(buffer,result);

#ifdef  PRINT_DBG
        printf("%s: %d = apisyslog_CheckModify() \n",
                __FUNCTION__,result);
#endif

        if( result > 0 )
        {
            apisyslog_readFile();
#ifdef  PRINT_DBG
        printf("%s: apisyslog_readFile() \n",__FUNCTION__);
#endif
        }
    }while(1);

    inotify_rm_watch( g_Config.fdInit, g_Config.fdWatch);

    close(g_Config.fdWatch);
    close(g_Config.fdInit);

    return (void*) 0;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_CheckModify(const char* a_Buffer,int a_Size)
{
    int result 	= 0;
    char*                   pBuffer     = (char*)a_Buffer;
    struct inotify_event    *pEvent     = 0;


    for (pBuffer = (char*)a_Buffer; pBuffer < a_Buffer + a_Size ; )
    {
        pEvent = (struct inotify_event *) pBuffer;

#ifdef PRINT_DBG
      printf("%s: mask=%X name=%s \n",__FUNCTION__,pEvent->mask,pEvent->name);
#endif
        if ( ( pEvent->mask != 0 )
                && ( 0 == strcmp( pEvent->name,APISYSLOG_CONFIG_FILENAME)))
        {
            result = 1;
            break; // one event need
        }

        pBuffer += sizeof(struct inotify_event) + pEvent->len;
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
    char 	buffTag[APISYSLOG_TAG_SIZE];
    char 	buffTagValue[APISYSLOG_TAG_SIZE];
    int 	vTagValue = 0;
    int		lenBuff = 0;

    int		bitTag = 0;
    g_Config.flag = 0;

    (void) vTagValue;
    //	printf("apisyslog_readFile \n");

    fd = fopen(g_Config.config_filename,"rt");

    if( fd == 0 )
    {
        result = errno;

        g_Config.flag =     APISYSLOG_TRACE_NANO
                        |   APISYSLOG_TRACE_STDERR
                        |   APISYSLOG_TRACE_LOG;
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
            sscanf(buffer,"%[^=]=%s",buffTag,buffTagValue);

            if( buffTagValue[0] == '0' )
            {
            }
            else
            {
                // ******************************************
                //      TRACE
                // ******************************************
                bitTag = apisyslog_findTagTrace(buffTag);

                if( bitTag >= 0 )
                {
                        //&& 	( buffTagValue != 0) )

                    g_Config.flag |=  gArrayTagIdTrace[bitTag].id;
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
                           strncpy(g_Config.fifoname,buffTag,PATH_MAX-1);
                       }

                           g_Config.flag |=  gArrayTagIdDebug[bitTag].id;
                       //                printf("buffTag=%s buffTagValue=%d bitTag=%d\n",buffTag,buffTagValue,bitTag);
                   }
               }// if( bitTag < 0 )
            }// if( buffTagValue[0] == '0' )
        }//while ( ! feof( fd ) )
    }// if( fd == 0 ) else

    if( NULL != fd  )
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


    errno = 0;
    result = sem_init(&g_Config.semaphore,1,0);
    if (0 != result  )
    {
        result = errno;
        fprintf(stderr,"%s Error sem_init(1,0)  err=%d %s \n",
                __FUNCTION__,errno, strerror(errno) );
    }

    if( 0 == result  )
    {
        errno = 0;
        result = pthread_attr_init(&attr);
        if (0 != result )
        {
            fprintf(stderr,"%s Error pthread_attr_init()  err<=%d %s \n",
                    __FUNCTION__,errno, strerror(errno) );
            result = errno;
        }
    }
    if( 0 == result  )
    {
        //The pthread_create() call stores the thread ID

        errno = 0;
        result = pthread_create(&g_Config.thread_id, &attr,
                &apisyslog_thread_body, (void*)NULL);

        if (result  != 0)
            fprintf(stderr,"%s Error pthread_create()  err<=%d %s \n",
                    __FUNCTION__,errno, strerror(errno) );
        result = errno;
    }
    //Destroy the thread attributes object, since it is no longer needed
    pthread_attr_destroy(&attr);


    if( 0 == result  )
    {
        struct timespec vDate = {0,0};
        struct timespec vTimeout = {0,1e9/100}; // 10ms

        timeradd_real(vTimeout,&vDate);

        errno = 0;
        result = sem_timedwait(&g_Config.semaphore,&vDate);
        if (result  != 0)
            fprintf(stderr,"%s Error sem_timedwait()  err<=%d %s \n",
                    __FUNCTION__,errno, strerror(errno) );
        result = errno;

        sem_destroy(&g_Config.semaphore);
    }

    return result;
}
//*********************************************************
//*
//*********************************************************
uint64_t apisyslog_getflag(uint64_t a_flag)
{
    uint64_t result = 0;
    result = g_Config.flag & a_flag;

#ifdef  PRINT_DBG
        printf("apisyslog_getflag flag=%#lX result=%#lX\n",g_Config.flag,result);
#endif
    return result;
}
//*********************************************************
//*
//*********************************************************
int apisyslog_PrintLog(const char *pszFuncName, const char *a_pszFmt, ...)
{
#define LEN_MESSAGETOPRINT (512)
#define LEN_MESSAGE (255)
#define LEN_NANO   (25)

    char 				vMessage[LEN_MESSAGE];
    char                vNano[LEN_NANO];
    char 				vMessageToPrint[LEN_MESSAGETOPRINT];
    char                vFormat[LEN_MESSAGE];
    int 				vTid = (int)syscall(SYS_gettid);
    int                 vNBuf = 0;
    int					vRetcode			= 0;
    va_list 			pVa_list;
    //struct timeval		vTimeval;

    (void)vNBuf;
    va_start(pVa_list, a_pszFmt);

    // Format user arguments
    vNBuf = vsnprintf(vMessage , LEN_MESSAGE, a_pszFmt, pVa_list);

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
        snprintf(vNano,25, "%4ld,%09ld",vRes.tv_sec,vRes.tv_nsec);
    }

    //*********************************************************
    //              PRINT SYSLOG
    //*********************************************************

    strncpy(vFormat,"%s %5d %-15s %s %s",LEN_MESSAGE);
    snprintf( vMessageToPrint, LEN_MESSAGETOPRINT - strlen(vFormat) , vFormat,
            vNano,
            vTid,
            g_Config.process_basename,
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
    result = g_Config.flag & a_flag;

    if ( result )
    {

    }

    return result;
}

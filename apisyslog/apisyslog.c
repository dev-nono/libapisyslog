/*
 * appsyslog.c
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#include <errno.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include <string.h>


#include "apisyslog_int.h"
#include "apisyslog.h"



sConfigSyslog_t gConfig;

//*********************************************************
//*
//*********************************************************
int32_t apisyslog_init(const char* a_ConfigFilemame)
{
	int32_t result = 0;

	memset(&gConfig,0,sizeof(gConfig));

	strncpy(gConfig.configFilename,a_ConfigFilemame,PATH_MAX-1);
	strncpy(gConfig.prefix,"PREFIX",100-1);

	result = apisyslog_StartThread();

	gConfig.flag = APISYSLOG_TRACE_INOUT | APISYSLOG_TRACE_1;

	openlog(gConfig.prefix, LOG_NDELAY | LOG_PID , LOG_LOCAL7);


	return result;
}


//*********************************************************
//*
//*********************************************************
int32_t apisyslog_release()
{
	int32_t result = 0;


	return result;
}

//*********************************************************
//*
//*********************************************************
int32_t apisyslog_StartThread()
{
	int32_t result = 0;


	return result;
}
//*********************************************************
//*
//*********************************************************
int32_t apisyslog_getflag(uint64_t a_flag)
{
	int32_t result = 0;

	result = gConfig.flag & a_flag;

	return result;
}


int32_t apisyslog_PrintLog(const char *pszCompName, const char *a_pszFmt, ...)
{
	char 				vMessage[512];
	char 				vMessageArg[512];
	//
	__attribute__((unused)) int vNBuf = 0;
	int					vRetcode			= 0;
	va_list 			pVa_list;
	//struct timeval		vTimeval;

	va_start(pVa_list, a_pszFmt);

	// Format user arguments
	vNBuf = vsnprintf(vMessage , 512, a_pszFmt, pVa_list);

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

	snprintf(vMessageArg,512,"%d %s",
			(int)syscall(SYS_gettid),
			vMessage);

	syslog(LOG_DEBUG,"%s",vMessageArg);

	va_end(pVa_list);

	return vRetcode;
}


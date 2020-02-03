/*
 * appsyslog.c
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#include "apisyslog_int.h"
#include "apisyslog.h"

#include <string.h>


sConfigSyslog_t gConfig;

//*********************************************************
//*
//*********************************************************
int32_t apisyslog_init(const char* a_ConfigFilemame)
{
	int32_t result = 0;

	memset(&gConfig,0,sizeof(gConfig));

	strncpy(gConfig.configFilename,a_ConfigFilemame,PATH_MAX-1);

	result = apisyslog_StartThread();

	gConfig.flag = APISYSLOG_TRACE_INOUT | APISYSLOG_TRACE_1;

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



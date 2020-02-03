/*
 * appsyslog.c
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#include "libapisyslog_int.h"
#include "libapisyslog.h"

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
	int result = 0;


	return result;
}


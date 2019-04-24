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
static int Initilise()
{
	int result = 0;

	memset(&gConfig,0,sizeof(gConfig));

	return result;
}

//*********************************************************
//*
//*********************************************************
int readConfig(const char* a_ConfigFilemame)
{
	int result = 0;

	result = Initilise();

	if( 0 == result )
	{
		strncpy(gConfig.configFilename,a_ConfigFilemame, PATH_MAX -1);
	}



	return result;
}


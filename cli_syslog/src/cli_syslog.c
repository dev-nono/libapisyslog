/*
 ============================================================================
 Name        : cli_syslog.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "apisyslog.h"

#include "apisyslog_int.h"
extern sConfigSyslog_t gConfig;


int main( int argc, char* argv[] )
{
	int result = EXIT_SUCCESS;


	result = apisyslog_init( "");

	gConfig.flag = 0;
	TRACE_IN("main_IN_1")
	TRACE_OUT("main_OUT_1")

	gConfig.flag = APISYSLOG_TRACE_INOUT;
	TRACE_IN("main_IN_2")
	TRACE_OUT("main_OUT_2")

	gConfig.flag = APISYSLOG_TRACE_1;
	TRACE_DBG1("TRACE_DBG1")
	TRACE_DBG2("TRACE_DBG2")

	gConfig.flag = APISYSLOG_TRACE_2;
	TRACE_DBG1("TRACE_DBG1_2")
	TRACE_DBG2("TRACE_DBG2_2")

	result = apisyslog_release();


	//TRACE_OUT("main_OUT",result)

	return result;
}

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

//#include "apisyslog_int.h"
//extern sConfigSyslog_t gConfig;


int main( int argc, char* argv[] )
{
	int result = EXIT_SUCCESS;

	result = apisyslog_init( "");

	TRACE_IN("main_IN_1")
	TRACE_OUT("main_OUT_1 result = %d",result)


	result = apisyslog_release();


	//TRACE_OUT("main_OUT",result)

	return result;
}

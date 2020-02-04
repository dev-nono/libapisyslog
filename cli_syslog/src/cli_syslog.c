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
//extern sConfigSyslog_t gConfig;


int main( int argc, char* argv[] )
{
	int result = EXIT_SUCCESS;

	result = apisyslog_init( "");

	TRACE_IN("IN")

	result = apisyslog_release();


	TRACE_OUT("OUT result = %d",result)

	return result;
}

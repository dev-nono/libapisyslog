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
#include <string.h>


#include "apisyslog.h"
#include "apisyslog_int.h"
//extern sConfigSyslog_t gConfig;


int main( int argc, char* argv[] )
{
	int result = EXIT_SUCCESS;

	#define BUF_SIZE 255
	char buffer[BUF_SIZE-1];
	char *pBuff = 0;

	(void)pBuff;

	result = apisyslog_init( "");

	printf("argv0 = %s\n",argv[0]);

	TRACE_IN("IN")

	//result = apisyslog_release();

	do
	{
		memset(buffer,0,sizeof(buffer));

		pBuff = fgets(buffer,BUF_SIZE-1,stdin);

		TRACE_DBG1("DBG1 %s", buffer);
		TRACE_DBG2("DBG2 %s", buffer);

	}while(1);

	TRACE_OUT("OUT result = %d",result)

	return result;
}

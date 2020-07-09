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
//#include "apisyslog_int.h"
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
        TRACE_DBG3("DBG3 %s", buffer);
        TRACE_DBG4("DBG4 %s", buffer);
        TRACE_DBG5("DBG5 %s", buffer);
        TRACE_DBG6("DBG6 %s", buffer);
        TRACE_DBG7("DBG7 %s", buffer);
        TRACE_DBG8("DBG8 %s", buffer);
        TRACE_DBG9("DBG9 %s", buffer);
        TRACE_DBG10("DB10 %s", buffer);
        TRACE_DBG11("DBG11 %s", buffer);
        TRACE_DBG12("DBG12 %s", buffer);
        TRACE_DBG13("DBG13 %s", buffer);

	}while(1);

	TRACE_OUT("OUT result = %d",result)

	return result;
}

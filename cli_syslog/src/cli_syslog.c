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


#include "utils.h"
#include "apisyslog.h"



int main( int argc, char* argv[] )
{
	int result = SUCCESS;

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

		TRACE_DBG1( "DBG1 %s", buffer);
		TRACE_DBG2( "DBG2 %s", buffer);
        TRACE_DBG3( "DBG3 %s", buffer);
        TRACE_DBG4( "DBG4 %s", buffer);
        TRACE_DBG5( "DBG5 %s", buffer);
        TRACE_DBG6( "DBG6 %s", buffer);
        TRACE_DBG7( "DBG7 %s", buffer);
        TRACE_DBG8( "DBG8 %s", buffer);
        TRACE_DBG9( "DBG9 %s", buffer);
        TRACE_DBG10("DBG10 %s", buffer);

        TRACE_DBG11("DBG11 %s", buffer);
        TRACE_DBG12("DBG12 %s", buffer);
        TRACE_DBG13("DBG13 %s", buffer);
        TRACE_DBG14("DBG14 %s", buffer);
        TRACE_DBG15("DBG15 %s", buffer);
        TRACE_DBG16("DBG16 %s", buffer);
        TRACE_DBG17("DBG17 %s", buffer);
        TRACE_DBG18("DBG18 %s", buffer);
        TRACE_DBG19("DBG19 %s", buffer);
        TRACE_DBG20("DBG20 %s", buffer);

        TRACE_DBG21("DBG21 %s", buffer);
        TRACE_DBG22("DBG22 %s", buffer);
        TRACE_DBG23("DBG23 %s", buffer);
        TRACE_DBG24("DBG24 %s", buffer);
        TRACE_DBG25("DBG25 %s", buffer);
        TRACE_DBG26("DBG26 %s", buffer);
        TRACE_DBG27("DBG27 %s", buffer);
        TRACE_DBG28("DBG28 %s", buffer);
        TRACE_DBG29("DBG29 %s", buffer);

        TRACE_DBG30("DBG30 %s", buffer);
        TRACE_DBG31("DBG31 %s", buffer);
        TRACE_DBG32("DBG32 %s", buffer);
        TRACE_DBG33("DBG33 %s", buffer);
        TRACE_DBG34("DBG34 %s", buffer);
        TRACE_DBG35("DBG35 %s", buffer);
        TRACE_DBG36("DBG36 %s", buffer);
        TRACE_DBG37("DBG37 %s", buffer);
        TRACE_DBG38("DBG38 %s", buffer);
        TRACE_DBG39("DBG39 %s", buffer);

        TRACE_DBG40("DBG40 %s", buffer);
        TRACE_DBG41("DBG41 %s", buffer);
        TRACE_DBG42("DBG42 %s", buffer);
        TRACE_DBG43("DBG43 %s", buffer);
        TRACE_DBG44("DBG44 %s", buffer);
        TRACE_DBG45("DBG45 %s", buffer);
        TRACE_DBG46("DBG46 %s", buffer);
        TRACE_DBG47("DBG47 %s", buffer);
        TRACE_DBG48("DBG48 %s", buffer);
        TRACE_DBG49("DBG49 %s", buffer);

        TRACE_DBG50("DBG50 %s", buffer);

	}while(1);

	TRACE_OUT("OUT result = %d",result)

	return result;
}

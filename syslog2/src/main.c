/*
 ============================================================================
 Name        : apptests.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <syslog_light.h>

#include "tst_time.h"

int syslog_IN(toto_1, int a_ii,int a_bb)


syslog_OUT(toto_1)

int main(int argc, char **argv)
{

	(void) argc;
	(void) argv;
	//	time_dateNano(argc,argv);

	syslog(LOG_DEBUG,"%s","syslog(LOG_DEBUG,'%s','coucou')");

	syslog_ng(SYSLOG_DEF_OPTION ,0 , LOG_DEBUG, "syslog_ng(SYSLOG_DEF_OPTION ,0 , LOG_DEBUG, '...');");
	syslog_ng(SYSLOG_DEF_OPTION ,SYSLOG_NONE , LOG_DEBUG, "syslog_ng(SYSLOG_DEF_OPTION ,SYSLOG_NONE , LOG_DEBUG, '...');");
	syslog_ng(SYSLOG_DEF_OPTION ,__FUNCTION__, LOG_DEBUG, "syslog_ng(SYSLOG_DEF_OPTION ,%s , LOG_DEBUG, '...');",__FUNCTION__);

	return EXIT_SUCCESS;
}

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

syslog(LOG_DEBUG,"toto_1(a_ii=%d, a_bb=%d)",a_ii, a_bb);


syslog_OUT(toto_1)

void test_syslog(int argc, char **argv)
{
	syslog(LOG_DEBUG,"%s","syslog(LOG_DEBUG,'%s','coucou')");

	syslog_ng(SYSLOG_DEF_OPTION ,0 , LOG_DEBUG, "syslog_ng(SYSLOG_DEF_OPTION ,0 , LOG_DEBUG, '...');");
	syslog_ng(SYSLOG_DEF_OPTION ,SYSLOG_NONE , LOG_DEBUG, "syslog_ng(SYSLOG_DEF_OPTION ,SYSLOG_NONE , LOG_DEBUG, '...');");
	syslog_ng(SYSLOG_DEF_OPTION ,__FUNCTION__, LOG_DEBUG, "syslog_ng(SYSLOG_DEF_OPTION ,%s , LOG_DEBUG, '...');",__FUNCTION__);

	/*
Dec  5 16:54:04 buildsystem syslog2 15:54:04.030671  335 : syslog(LOG_DEBUG,'%s','coucou')
Dec  5 16:54:04 buildsystem syslog2 15:54:04.030945  335 : syslog_ng(SYSLOG_DEF_OPTION ,0 , LOG_DEBUG, '...');
Dec  5 16:54:04 buildsystem syslog2 15:54:04.031120  335 : syslog_ng(SYSLOG_DEF_OPTION ,SYSLOG_NONE , LOG_DEBUG, '...');
Dec  5 16:54:04 buildsystem syslog2 15:54:04.031292  335 : syslog_ng(SYSLOG_DEF_OPTION ,main , LOG_DEBUG, '...');


	 */

	toto_1(1,2);

}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	//	time_dateNano(argc,argv);

	test_syslog(argc,argv);

	return EXIT_SUCCESS;
}

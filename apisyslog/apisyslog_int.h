/*
 * libapisyslog_int.h
 *
 *  Created on: Apr 24, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_INT_H_
#define LIBAPISYSLOG_INT_H_

#include <stdint.h>
#include <limits.h>
#include <semaphore.h>

#define APISYSLOG_CONFIG_FILENAME "debugtrace.conf"
#define APISYSLOG_TAG_SIZE 255

struct sConfigSyslog
{
	char 		process_basename[APISYSLOG_TAG_SIZE];
	char 		process_dirname[PATH_MAX-APISYSLOG_TAG_SIZE];
	char 		config_filename[PATH_MAX];
    char        fifoname[PATH_MAX];
	uint64_t	flag;
	char		prefix[100];
	pthread_t	thread_id;
	sem_t       semaphore;
	int			fdInit;
	int			fdWatch;
};
typedef struct sConfigSyslog sConfigSyslog_t;

struct sTagId
{
	char 		tag[APISYSLOG_TAG_SIZE];
	uint64_t	id;
};

int apisyslog_StartThread();
int apisyslog_readFile();
int apisyslog_CheckModify(const char* a_Buffer);
int apisyslog_findTagTrace(const char* a_Buffer);
int apisyslog_findTagDebug(const char* a_Buffer);




#endif /* LIBAPISYSLOG_INT_H_ */

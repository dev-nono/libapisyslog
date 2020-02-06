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

#define APISYSLOG_TAG_SIZE 255
struct sConfigSyslog
{
	char 		basename[APISYSLOG_TAG_SIZE];
	char 		dirname[PATH_MAX-APISYSLOG_TAG_SIZE];
	char 		filename[PATH_MAX];
	uint64_t	flag;
	char		prefix[100];
	pthread_t	thread_id;
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
int apisyslog_findTag(const char* a_Buffer);




#endif /* LIBAPISYSLOG_INT_H_ */

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

struct sConfigSyslog
{
	char 		configFilename[PATH_MAX];
	uint64_t	flag;
	char		prefix[100];

};
typedef struct sConfigSyslog sConfigSyslog_t;

int32_t apisyslog_StartThread();


#endif /* LIBAPISYSLOG_INT_H_ */

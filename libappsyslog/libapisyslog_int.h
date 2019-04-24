/*
 * libapisyslog_int.h
 *
 *  Created on: Apr 24, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_INT_H_
#define LIBAPISYSLOG_INT_H_

#include "limits.h"

struct sConfigSyslog
{
	char configFilename[PATH_MAX];

};
typedef struct sConfigSyslog sConfigSyslog_t;


static int Initilise();



#endif /* LIBAPISYSLOG_INT_H_ */

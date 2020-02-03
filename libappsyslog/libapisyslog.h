/*
 * libappsyslog.h
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_H_
#define LIBAPISYSLOG_H_

#include <stdint-gcc.h>


#define APISYSLOG_TRACE_INOUT 	(1 << 0 )
#define APISYSLOG_TRACE_1 		(1 << 1 )



int32_t apisyslog_init(const char* a_ConfigFilemame);
int32_t apisyslog_release();



#endif /* LIBAPISYSLOG_H_ */

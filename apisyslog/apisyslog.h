/*
 * libappsyslog.h
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_H_
#define LIBAPISYSLOG_H_

#include <stdint.h>
#include <stdio.h>

#define APISYSLOG_TRACE_INOUT 	(1 << 0 )
#define APISYSLOG_TRACE_1 		(1 << 1 )
#define APISYSLOG_TRACE_2 		(1 << 2 )

#define TRACE_IN(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_INOUT) ){ printf("%s\n",arg_1);}
#define TRACE_OUT(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_INOUT) ){ printf("%s\n",arg_1);}

#define TRACE_DBG1(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_1) ){ printf("%s\n",arg_1);}
#define TRACE_DBG2(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_2) ){ printf("%s\n",arg_1);}

int32_t apisyslog_init(const char* a_ConfigFilemame);
int32_t apisyslog_release();

int32_t apisyslog_getflag(uint64_t a_flag);


#endif /* LIBAPISYSLOG_H_ */

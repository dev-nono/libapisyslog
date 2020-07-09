/*
 * libappsyslog.h
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_H_
#define LIBAPISYSLOG_H_

#include <stdint.h>

#define APISYSLOG_TRACE_INOUT 	        (1UL << 0 )
#define APISYSLOG_TRACE_1 		        (1UL << 1 )
#define APISYSLOG_TRACE_2 		        (1UL << 2 )
#define APISYSLOG_TRACE_3               (1UL << 3 )
#define APISYSLOG_TRACE_4               (1UL << 4 )
#define APISYSLOG_TRACE_5               (1UL << 5 )
#define APISYSLOG_TRACE_6               (1UL << 6 )
#define APISYSLOG_TRACE_7               (1UL << 7 )
#define APISYSLOG_TRACE_8               (1UL << 8 )
#define APISYSLOG_TRACE_9               (1UL << 9 )
#define APISYSLOG_TRACE_10               (1UL << 10 )
#define APISYSLOG_TRACE_11               (1UL << 11 )
#define APISYSLOG_TRACE_12               (1UL << 12 )
#define APISYSLOG_TRACE_13               (1UL << 13 )


#define APISYSLOG_DBG_WAIT1	            (1UL << 50 )
#define APISYSLOG_DBG_WAIT2             (1UL << 51 )

#define APISYSLOG_TRACE_STDERR          (1UL << 60 )
#define APISYSLOG_TRACE_STDOUT	        (1UL << 62 )
#define APISYSLOG_TRACE_NANO	        (1UL << 63 )
#define APISYSLOG_TRACE_END		0

#define APISYSLOG_WAIT_OFF      0
#define APISYSLOG_WAIT_ON       1
#define APISYSLOG_WAIT_AUTO     2

#define APISYSLOG_DEBUG_FIFO    "debug.fifo"
#define APISYSLOG_DEBUG_WAIT1   "debug.wait1"
#define APISYSLOG_DEBUG_WAIT2   "debug.wait2"



#define TRACE_IN(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_INOUT) )\
	{ apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_OUT(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_INOUT) )\
	{ apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG1(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_1) )\
	{ apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG2(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_2) )\
			{ apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG3(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_3) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG4(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_4) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG5(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_5) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG6(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_6) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG7(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_7) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG8(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_8) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG9(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_9) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG10(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_10) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG11(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_11) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG12(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_12) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG13(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_13) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG14(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_14) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG15(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_15) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG16(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_16) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG17(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_17) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG18(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_18) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG19(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_19) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG20(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_20) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}


int apisyslog_init(const char* a_ConfigFilemame);
int apisyslog_release();

uint64_t apisyslog_getflag(uint64_t a_flag);
int apisyslog_PrintLog(const char *pszCompName, const char *a_pszFmt, ...);

int apisyslog_Wait(uint64_t a_flag);

#endif /* LIBAPISYSLOG_H_ */

/*
 * libappsyslog.h
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_H_
#define LIBAPISYSLOG_H_

#include <stdint.h>

#define APISYSLOG_TRACE_1 		         (1UL << 0 )
#define APISYSLOG_TRACE_2 		         (1UL << 1 )
#define APISYSLOG_TRACE_3                (1UL << 2 )
#define APISYSLOG_TRACE_4                (1UL << 3 )
#define APISYSLOG_TRACE_5                (1UL << 4 )
#define APISYSLOG_TRACE_6                (1UL << 5 )
#define APISYSLOG_TRACE_7                (1UL << 6 )
#define APISYSLOG_TRACE_8                (1UL << 7 )
#define APISYSLOG_TRACE_9                (1UL << 8 )
#define APISYSLOG_TRACE_10               (1UL << 9 )
#define APISYSLOG_TRACE_11               (1UL << 10 )
#define APISYSLOG_TRACE_12               (1UL << 11 )
#define APISYSLOG_TRACE_13               (1UL << 12 )
#define APISYSLOG_TRACE_14               (1UL << 13 )
#define APISYSLOG_TRACE_15               (1UL << 14 )
#define APISYSLOG_TRACE_16               (1UL << 15 )
#define APISYSLOG_TRACE_17               (1UL << 16 )
#define APISYSLOG_TRACE_18               (1UL << 17 )
#define APISYSLOG_TRACE_19               (1UL << 18 )
#define APISYSLOG_TRACE_20               (1UL << 19 )
#define APISYSLOG_TRACE_21               (1UL << 20 )
#define APISYSLOG_TRACE_22               (1UL << 21 )
#define APISYSLOG_TRACE_23               (1UL << 22 )
#define APISYSLOG_TRACE_24               (1UL << 23 )
#define APISYSLOG_TRACE_25               (1UL << 24 )
#define APISYSLOG_TRACE_26               (1UL << 25 )
#define APISYSLOG_TRACE_27               (1UL << 26 )
#define APISYSLOG_TRACE_28               (1UL << 27 )
#define APISYSLOG_TRACE_29               (1UL << 28 )
#define APISYSLOG_TRACE_30               (1UL << 29 )
#define APISYSLOG_TRACE_31               (1UL << 30 )
#define APISYSLOG_TRACE_32               (1UL << 31 )
#define APISYSLOG_TRACE_33               (1UL << 32 )
#define APISYSLOG_TRACE_34               (1UL << 33 )
#define APISYSLOG_TRACE_35               (1UL << 34 )
#define APISYSLOG_TRACE_36               (1UL << 35 )
#define APISYSLOG_TRACE_37               (1UL << 36 )
#define APISYSLOG_TRACE_38               (1UL << 37 )
#define APISYSLOG_TRACE_39               (1UL << 38 )
#define APISYSLOG_TRACE_40               (1UL << 39 )
#define APISYSLOG_TRACE_41               (1UL << 40 )
#define APISYSLOG_TRACE_42               (1UL << 41 )
#define APISYSLOG_TRACE_43               (1UL << 42 )
#define APISYSLOG_TRACE_44               (1UL << 43 )
#define APISYSLOG_TRACE_45               (1UL << 44 )
#define APISYSLOG_TRACE_46               (1UL << 45 )
#define APISYSLOG_TRACE_47               (1UL << 46 )
#define APISYSLOG_TRACE_48               (1UL << 47 )
#define APISYSLOG_TRACE_49               (1UL << 48 )
#define APISYSLOG_TRACE_50               (1UL << 49 )

#define APISYSLOG_TRACE_IN              (1UL << 50 )
#define APISYSLOG_TRACE_OUT             (1UL << 51 )
#define APISYSLOG_TRACE_INOUT           (APISYSLOG_TRACE_IN | APISYSLOG_TRACE_OUT )


#define APISYSLOG_DBG_WAIT1	            (1UL << 52 )
#define APISYSLOG_DBG_WAIT2             (1UL << 53 )

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



#define TRACE_IN(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_IN) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_OUT(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_OUT) )\
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

#define TRACE_DBG21(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_21) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG22(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_22) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG23(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_23) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG24(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_24) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG25(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_25) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG26(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_26) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG27(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_27) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG28(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_28) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG29(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_29) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG30(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_30) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG31(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_31) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG32(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_32) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG33(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_33) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG34(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_34) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG35(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_35) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG36(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_36) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG37(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_37) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG38(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_38) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG39(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_39) )\
        { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG40(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_40) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG41(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_41) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG42(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_42) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG43(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_43) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG44(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_44) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG45(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_45) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG46(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_46) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG47(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_47) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG48(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_48) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG49(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_49) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

#define TRACE_DBG50(arg_1...) if ( apisyslog_getflag(APISYSLOG_TRACE_50) )\
            { apisyslog_PrintLog(__FUNCTION__, arg_1);}

int apisyslog_init(const char* a_ConfigFilemame);
int apisyslog_release();

uint64_t apisyslog_getflag(uint64_t a_flag);
int apisyslog_PrintLog(const char *pszCompName, const char *a_pszFmt, ...);

int apisyslog_Wait(uint64_t a_flag);

#endif /* LIBAPISYSLOG_H_ */

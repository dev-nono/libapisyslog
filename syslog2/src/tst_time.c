/*
 * time.c
 *
 *  Created on: Nov 10, 2022
 *      Author: vagrant
 */



#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "tst_time.h"


# define TIME_UTC 1

int time_dateNano(int argc, char **argv)
{
	int result = 0;
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];

    //gettimeofday()

    strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    printf("Current gmtime: %s.%09ld UTC\n", buff, ts.tv_nsec);

    strftime(buff, sizeof buff, "%D %T", localtime(&ts.tv_sec));
    printf("Current localtime: %s.%09ld UTC\n", buff, ts.tv_nsec);


    printf("Raw timespec.time_t: %ld\n", ts.tv_sec);
    printf("Raw timespec.tv_nsec: %09ld\n", ts.tv_nsec);

    return result;
}





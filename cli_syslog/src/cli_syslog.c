/*
 ============================================================================
 Name        : cli_syslog.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "libapisyslog.h"


int main( int argc, char* argv[] )
{
	int result = EXIT_SUCCESS;

	result = readConfig( "");

	return result;
}

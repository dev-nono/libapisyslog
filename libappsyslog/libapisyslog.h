/*
 * libappsyslog.h
 *
 *  Created on: Apr 17, 2019
 *      Author: bruno
 */

#ifndef LIBAPISYSLOG_H_
#define LIBAPISYSLOG_H_

int apisyslog_init(const char* a_ConfigFilemame);
int apisyslog_release();

#endif /* LIBAPISYSLOG_H_ */

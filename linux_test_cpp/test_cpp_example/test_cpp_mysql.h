/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_mysql.h
 *
 *    Description:  for test_cpp_mysql.cpp
 *
 *        Version:  1.0
 *        Created:  2013/1/20 20:03:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */

#ifndef TEST_CPP_MYSQL_H_
#define TEST_CPP_MYSQL_H_

#include "./include_mysql/mysql.h"
#include "test_cpp_dll.h"
#include <winsock2.h>

//函数声明
DLL_EXPORT int TestConnectMysql();
//extern int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen);
//extern int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

#endif //TEST_CPP_MYSQL_H_



/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_otl.h
 *
 *    Description:  the head file for test_cpp_otl.cpp
 *
 *        Version:  1.0
 *        Created:  2012/5/23 22:51:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha 
 *   Organization:  si-tech
 *
 * =====================================================================================
 */

#ifndef TEST_CPP_OTL_H_
#define TEST_CPP_OTL_H_

//#define OTL_ORA11G  //Compile OTL 4.0/OCI10g
//#define OTL_ANSI_CPP
//#define OTL_STL
#define OTL_ODBC
//#define OTL_UNICODE //Enable Unicode OTL for 10g
#include <otlv4.h> //include the OTL 4.0 header file
//#include <odbcinst.h>

//函数声明
int TestOtl();
int OtlConnectDb(char *, otl_connect &);
int OtlDisConnectDb(otl_connect &);

#endif //TEST_CPP_OTL_H_


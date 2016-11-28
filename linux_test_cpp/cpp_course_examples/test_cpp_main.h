/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_common.h
 *
 *    Description:  for all cpp
 *
 *        Version:  1.0
 *        Created:  2012/5/1 13:48:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha 
 *   Organization:  si-tech
 *
 * =====================================================================================
 */

#ifndef TEST_CPP_COMMON_H_
#define TEST_CPP_COMMON_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <unistd.h> //这是unix系统标准头文件，即unix Standard,相当于win32中的windows.h，获取对应的系统变量
#include <iomanip>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/vfs.h>
#include <sys/types.h>//Unix/Linux系统的基本系统数据类型的头文件，含有size_t，time_t，pid_t等类型
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <stdexcept>//继承于exception类，实现好了的异常处理类，包含常见的错误:runtime_error、overflow_error等

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
//mingw中windows.h中Sleep函数为ms级别
#define sleep(n) Sleep(1000*(n));
#else
#include <unistd.h> //这是unix系统标准头文件，即unix Standard,相当于win32中的windows.h，获取对应的系统变量
#endif

#include <dlfcn.h>
using namespace std; //using namespace::std
/* using std::cout;
 * using std::cin;
 * using std::endl;
 * using std::string;
 */

#endif //TEST_CPP_COMMON_H_


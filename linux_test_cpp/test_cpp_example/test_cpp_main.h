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

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
//mingw中windows.h中Sleep函数为ms级别
#define sleep(n) Sleep(1000*(n));
#else
#include <unistd.h> //这是unix系统标准头文件，即unix Standard,相当于win32中的windows.h，获取对应的系统变量
#endif

using namespace std; //using namespace::std
/* using std::cout;
 * using std::cin;
 * using std::endl;
 * using std::string;
 */

#endif //TEST_CPP_COMMON_H_


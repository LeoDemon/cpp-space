/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_linux.h
 *
 *    Description:  for test_cpp_linux
 *
 *        Version:  1.0
 *        Created:  2013年04月13日 10时39分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef TEST_CPP_LINUX_H_
#define TEST_CPP_LINUX_H_

#include <pthread.h>
#include <semaphore.h>

int TestShareSo();
extern "C" int TestPopen();
extern "C" int TestFork();
int TestForkExec(const char *, int);
extern "C" int TestThread();
extern "C" int TestThreadSyn1();
extern "C" int TestThreadSyn2();

// typedef unsigned short __kernel_mode_t;
//typedef __kernel_mode_t mode_t;

int GetFileType(mode_t , char *);
int GetFileMode(mode_t , char *);
int GetFileOtherAttr(struct stat , char *);
extern "C" int TestLinuxLs(const char*);

#endif	//TEST_CPP_LINUX_H_


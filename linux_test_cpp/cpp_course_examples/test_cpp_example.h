/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_example.h
 *
 *    Description:  .h for example
 *
 *        Version:  1.0
 *        Created:  2012/5/1 14:00:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha 
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#ifndef TEST_CPP_EXAMPLE_H_
#define TEST_CPP_EXAMPLE_H_

#include <iconv.h>
#include "test_cpp_dll.h"

//绘制[0,360]余弦曲线
int TestCosx();
int code_convert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen);
int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen);
int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

#endif //TEST_CPP_EXAMPLE_H_


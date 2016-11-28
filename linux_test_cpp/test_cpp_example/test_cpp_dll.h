/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_dll.h
 *
 *    Description:  for cpptest.dll
 *
 *        Version:  1.0
 *        Created:  2013/1/11 15:27:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef TEST_CPP_DLL_H_
#define TEST_CPP_DLL_H_

//这里BUILD_DLL参数由makefile中编译参数-DBUILD_DLL传过来
#ifdef BUILD_DLL
// __declspec(dllexport) 关键字从 DLL 导出数据、函数、类或类成员函数
// __declspec(dllexport) 定义一个宏DLL_EXPORT并对正在导出的每个符号使用该宏
// __declspec(dllexport) 将函数名存储在 DLL 的导出表中
/* dll export */
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
/*dll import */
#define DLL_IMPORT __declspec(dllimport)
#endif

#endif

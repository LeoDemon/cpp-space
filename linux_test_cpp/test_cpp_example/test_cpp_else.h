/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_else.h
 *
 *    Description:  for test_cpp_else.cpp
 *
 *        Version:  1.0
 *        Created:  2012/5/7 20:49:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */

#ifndef TEST_CPP_ELSE_H_
#define TEST_CPP_ELSE_H_

#include <map>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <malloc.h>
#include <algorithm> //stl：提供一组基于算法的函数，包括置换、排序、合并和搜索的头文件
#include <locale>
#include <cctype>
#include <bitset>
#include "./include_libxl/libxl.h"
#include "test_cpp_dll.h"

using namespace libxl;

//宏定义声明，获取数组的个数
#define GET_ARRAY_LEN(array,len) len=sizeof(array)/sizeof(array[0])
//#表示：对应变量字符串化
#define trace(x, format) printf(#x " = %" #format "\n", x)
//##表示：把宏参数名与宏定义代码序列中的标识符连接在一起，形成一个新的标识
#define trace2(i) trace(ipr##i, d)

int TestTemp1();
int TestTemp2();
int TestTemp3();
int TestMap();
int TestVector();
int TestList();
int PrintList(list<int> &ls1, list<int> &ls2);
int TestDeque();
int TestSet();
int TestTemp9(const string&, string&);
void split_name( char * name , char * store , int len );
int TestHashTable();
int TestBuffer();
int TestVariable();
int TestStl();
int TestStl2();
DLL_EXPORT int TestStl3();
DLL_EXPORT int TestExcel();
const TCHAR* ReadDataToWChar(Sheet* sheet, int row,int col);
extern int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen);
extern int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen);
DLL_EXPORT int TestQryfolder(const char path[]);
DLL_EXPORT int TestPointer();
DLL_EXPORT int TestTempWin();

//c++ enum 声明
enum Flag{f1=1,f2,f3,f4=8,f5,f6};
//enum ++ 前置自增重载声明
Flag &operator ++ (Flag &f);
//enum ++ 后置自增重载声明
Flag &operator ++ (Flag &f, int);

class Olympicmedal
{
	public:
		Olympicmedal(string country, unsigned medalnum)
		{
			this->country=country;
			this->medalnum=medalnum;
		}
		//常成员函数，只能引用成员，不能修改它们
		bool operator < (const Olympicmedal& ol) const
		{
			return this->medalnum < ol.medalnum;
		}

	public:
		string country;
		unsigned medalnum;
};


/*哈希表---begin*/
#define SUCCESS 1
#define ERROR 0
#define DUPLIC -1

typedef char KeyType[11];

typedef struct
{
	KeyType key;
	char value[50+1];
}ElemType;

typedef struct
{
	ElemType *elem;
	int count;//hashtable数据元素个数
	int size;//hashtable容量
}HashTable;

/*哈希表---end*/

/*
   struct _finddata_t 是用来存储文件各种信息的结构体
*/
//typedef struct
//{
//	unsigned attrib;  //文件属性
//	time_t time_create; //创建时间
//	time_t time_access; //文件最后一次被访问时间
//	time_t time_write;  //文件最后一次被修改时间
//	_fsize_t size;  //文件大小
//	char name[_MAX_FNAME]; //文件名
//}_finddata_t;

#endif //TEST_CPP_ELSE_H_


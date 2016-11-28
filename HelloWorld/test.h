#include <iostream>
//#include <Windows.h>
#include <unistd.h>  这是unix系统标准头文件，即unix Standard,相当于win32中的windows.h，
//#include <WinBase.h>//实验中，用到unistd中的getpid(),获取系统进程的id，在windows下直接用GetCurrentProcessId和getWindowThreadProcessId函数可实现要求，在winbase.h头文件中。
#include <malloc.h>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define NULL 0
#define LEN sizeof(STU)
#define S(A,B,C) (A+B+C)/2
#define AREA(S,A,B,C) S*(S-A)*(S-B)*(S-C)


template <typename T>
T mins(T a,T b,T c){
	if(a>b)a=b;
	if(a>c)a=c;
	return a;
}

//结构体
//typedef struct 
//{
//	int num;
//	char *name;//char name[20];
//	float score[3];
//}STUDENT;

//typedef struct _STUDENT
//{
//	int num;
//	char *name;//char name[20];
//	float score[3];
//	struct _STUDENT *next;//指向自身的指针，就必须不能少结构体名
//}STUDENT;

struct _STUDENT
{
	int num;
	char *name;//char name[20];
	float score[3];
	struct _STUDENT *next;//指向自身的指针，就必须不能少结构体名
};
typedef struct _STUDENT STUDENT;

typedef struct _STU
{
	int stu_num;
	char stu_name[255+1];
	float score;
	struct _STU *next;
}STU;

//枚举型变量声明
enum color {red,yellow,blue,white,black};

//C++类声明
class Staff {
	private:
		int num;
		int bonus;

	public:
		void setdata(){
			cin>>num;
			cin>>bonus;
		}
		void display(){
			cout<<"num=="<<num<<endl;
			cout<<"bonus=="<<bonus<<endl;
		};
};

//函数声明
int iotest();
int iotest2();
char * chartest(char *ch);
int iofstreamtest();
int efl();
int sqrtmath();
void search1(float (*p)[4],int n);
float *search2(float (*p)[4]);
void enter();
void fgets_test();
void string_test();
int fac(int n);
void strdef();
//void strprt(STUDENT);//用结构体变量作为实参
void strprt(STUDENT *p);//用结构体变量的指针作为实参
void sortball();
color &operator++(color &k);
int GenDeamon();
void IgnoreAllSignal();
void Linkedlist_test();
void LinkedList_cid();
STU *Createlist();
STU *Dellist(STU *head,int num);
void Insertlist(STU **head,STU *stu);
void print(STU *stu);
void csetget();
int pi_js();
int fibon();
int prime();
int cipher();
int pic();
int recursum();
int recursive(int n);
int triangle();
int mpfsort();
int xzfsort();
int stringcmp();
int strrev();
int txpic();
int studinfo();
int studinput();
int studsearch(string num);
int writeLog(const char *logpath,const char *msg);

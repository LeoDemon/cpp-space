#include <iostream>
//#include <Windows.h>
#include <unistd.h>  ����unixϵͳ��׼ͷ�ļ�����unix Standard,�൱��win32�е�windows.h��
//#include <WinBase.h>//ʵ���У��õ�unistd�е�getpid(),��ȡϵͳ���̵�id����windows��ֱ����GetCurrentProcessId��getWindowThreadProcessId������ʵ��Ҫ����winbase.hͷ�ļ��С�
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

//�ṹ��
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
//	struct _STUDENT *next;//ָ�������ָ�룬�ͱ��벻���ٽṹ����
//}STUDENT;

struct _STUDENT
{
	int num;
	char *name;//char name[20];
	float score[3];
	struct _STUDENT *next;//ָ�������ָ�룬�ͱ��벻���ٽṹ����
};
typedef struct _STUDENT STUDENT;

typedef struct _STU
{
	int stu_num;
	char stu_name[255+1];
	float score;
	struct _STU *next;
}STU;

//ö���ͱ�������
enum color {red,yellow,blue,white,black};

//C++������
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

//��������
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
//void strprt(STUDENT);//�ýṹ�������Ϊʵ��
void strprt(STUDENT *p);//�ýṹ�������ָ����Ϊʵ��
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

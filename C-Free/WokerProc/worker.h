#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

using namespace std;

typedef struct staff
{
	char name[15];
	char num[10];
	char sex[10];
	char age[10];
	char record[10];
	char position[15];
	char wanges[10];
	char tel[15];
	char addr[50];
}worker;                                    /*定义一个结构体*/

void append();                               /*定义一个创建函数*/
void search();                               /*定义一个查询的函数*/
void modify();                              /*定义一个修改函数*/
void output();                              /*定义一个输出信息的函数*/
void delwork();                              /*定义一个删除函数*/

int login_db(char *dbname,char *dbuser,char *dbpassword); /*连接数据库*/	
int append_db(worker wk);                               /*定义一个创建函数*/
worker search_db(worker wk);                               /*定义一个查询的函数*/
int modify_db(worker wk);                              /*定义一个修改函数*/
int output_db();                              /*定义一个输出信息的函数*/
int delwork_db(worker wk);                              /*定义一个删除函数*/
static void error_handler(const char *msg);   /*数据库执行报错调用该函数*/

int serachname(char filename[20]);			 /*查询是否有第一列姓名等,保证后面不重复输入这一列*/
int array_ts();							/*数组与指针的函数测试*/
int else_test();							/*定义一个测试其他问题的函数*/


#define WORKER DB;

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
}worker;                                    /*����һ���ṹ��*/

void append();                               /*����һ����������*/
void search();                               /*����һ����ѯ�ĺ���*/
void modify();                              /*����һ���޸ĺ���*/
void output();                              /*����һ�������Ϣ�ĺ���*/
void delwork();                              /*����һ��ɾ������*/

int login_db(char *dbname,char *dbuser,char *dbpassword); /*�������ݿ�*/	
int append_db(worker wk);                               /*����һ����������*/
worker search_db(worker wk);                               /*����һ����ѯ�ĺ���*/
int modify_db(worker wk);                              /*����һ���޸ĺ���*/
int output_db();                              /*����һ�������Ϣ�ĺ���*/
int delwork_db(worker wk);                              /*����һ��ɾ������*/
static void error_handler(const char *msg);   /*���ݿ�ִ�б�����øú���*/

int serachname(char filename[20]);			 /*��ѯ�Ƿ��е�һ��������,��֤���治�ظ�������һ��*/
int array_ts();							/*������ָ��ĺ�������*/
int else_test();							/*����һ��������������ĺ���*/


#define WORKER DB;

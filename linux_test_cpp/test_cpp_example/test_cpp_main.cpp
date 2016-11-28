/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_main.cpp
 *
 *    Description:  main()
 *
 *        Version:  1.0
 *        Created:  2012/5/1 12:52:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "test_cpp_main.h"
//#include "test_cpp_example.h"
//#include "test_cpp_course.h"
//#include "test_cpp_else.h"
//#include "test_cpp_otl.h"
#include "./include_mysql/mysql.h"
#include <winsock2.h>

//extern 外部变量，不能定义在函数里面
//extern int ex_int=200;  //声明时直接定义，并且加上extern，也是可行的
//extern string ex_str="china";
extern const int ex_int=200;	//加上const，则其他文件只能使用，不能改变原值
extern const string ex_str="china";
string s;
string st[10];
int itm[10];

typedef int (*_FUNC)(); //这里_FUNC就代表一个别名，定义了_FUNC为指向函数的指针类型
//typedef int (_FUNC)();//这里_FUNC为指向函数的指针类型的基类型，可以用_FUNC *func定义一个新的函数指针
typedef int (*_FUNC_CH)(const char[]);
//char *argv[]:argv[]先结合成为数组，然后与前面的*结合,即*argv[] 指针数组，argv[i]中的每个元素都是一个指向char型的指针变量
int main(int argc,char *argv[])
{

	cout<<"...in testcpp..."<<endl;

	/* C++ Primer 第4章 4.1 p157
	 * • 在函数体外定义的内置数组，其元素均初始化为 0。
	 * • 在函数体内定义的内置数组，其元素无初始化。
	 * • 不管数组在哪里定义，如果其元素为类类型，则自动调用该类的默认构造函数进行初始化；如果该类没有默认构造函数，则必须为该数组的元素提供显式初始化。
	 */
	string s2;
	string st2[10];
	int itm2[10];
	//s==,s2==,s.size()==0,s2.size()==0
	cout<<"s=="<<s<<",s2=="<<s2<<",s.size()=="<<s.size()<<",s2.size()=="<<s2.length()<<endl;
	int k=0;
	//st==~~~~~~~~~~
	cout<<"st==";
	for(k=0;k!=10;k++)
	{
		cout<<st[k]<<"~";
	}
	//st2==~~~~~~~~~~
	cout<<"\nst2==";
	for(k=0;k!=10;k++)
	{
		cout<<st2[k]<<"~";
	}
	//itm==0~0~0~0~0~0~0~0~0~0~
	cout<<"\nitm==";
	for(k=0;k!=10;k++)
	{
		cout<<itm[k]<<"~";
	}
	//itm2==4276192~2293456~2293503~2293700~1975749845~-1195249379~-2~1975652706~1975999428~4276192~
	cout<<"\nitm2==";
	for(k=0;k!=10;k++)
	{
		cout<<itm2[k]<<"~";
	}
	cout<<"\n";

	//测试主函数入参
	cout<<"argc=="<<argc<<endl;//默认为1
	for(int iargc=0;iargc<argc;iargc++)
	{
		cout<<"argv["<<iargc<<"]=="<<argv[iargc]<<endl;
		//argv[0]为进程路径：argv[0]==d:\Workspace\space_for_study\C__Space\test_cpp_example\testcpp.exe
	}
	//ex_int = argc;
	if(argc < 3)
	{
		cout<<"-----argc < 2------"<<endl;
		return -1;
	}
	printf("---argv[2]==[%s]---\n", argv[2]);
	unsigned int pid = atoi(argv[2]);
	cout<<"------pid=="<<pid<<endl;
	if(pid > 9)
	{
		cout<<"---pid > 9===="<<pid<<endl;
		return -1;
	}
	string spid = argv[2];
	string spidsql = "select to_char(login_accept),opr_lrt,op_code,to_char(opt_time,'yyyymmddhh24miss'),LOGIN_NO from ur_batchMange_busi where deal_flag='0' and plandeal_date < sysdate and login_accept>0  and substr(login_accept, -1, 1)="+spid+" and rownum < 100";
	cout<<"---spidsql=="<<spidsql<<endl;
	char *func_name = argv[1];
	if(strcmp(func_name, "") == 0 || func_name[0] == '\0')
	{
		cout<<"-----func_name is null------"<<endl;
		return -1;
	}

	try
	{
		MYSQL *mysql = NULL;
		mysql = mysql_init(mysql);
		mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "gbk");//由于vim编辑器的编码为utf-8，故这里设置字符集:utf8,函数成功返回0
		if(mysql !=NULL && mysql_real_connect(mysql, "localhost", "dbtest", "admin", "test", 3306, NULL, 0))
		{
			//
		}
		else
		{
			cout<<"---connect db failed, err_code=="<<mysql_errno(mysql)<<", err_msg=="<<mysql_error(mysql)<<"---"<<endl;
			return -1;
		}
		char dll_id[10];
		char sqlstr[255];
		memset(sqlstr, '\0', strlen(dll_id));
		memset(sqlstr, '\0', strlen(sqlstr));
		sprintf(sqlstr, "select module_id from or_method_dict where method_no='%s'", func_name);
		cout<<"------sqlstr=="<<sqlstr<<endl;
		if(0 == mysql_real_query(mysql, sqlstr, strlen(sqlstr)))
		{
			MYSQL_RES *result = NULL;
			result = mysql_store_result(mysql);
			if(result != NULL)
			{
				MYSQL_ROW row = NULL;
				row = mysql_fetch_row(result);
				if(NULL != row)
				{
					strcpy(dll_id, row[0]);
				}
				else
				{
					cout<<"------or_method_dict has no rows------"<<endl;
					mysql_free_result(result);
					mysql_close(mysql);
					return -1;
				}
			}
			else
			{
				cout<<"---get result failed, err_code=="<<mysql_errno(mysql)<<", err_msg=="<<mysql_error(mysql)<<"---"<<endl;
				mysql_free_result(result);
				mysql_close(mysql);
				return -1;
			}
			mysql_free_result(result);
		}
		else
		{
			cout<<"---select or_method_dict failed, err_code=="<<mysql_errno(mysql)<<", err_msg=="<<mysql_error(mysql)<<"---"<<endl;
			mysql_close(mysql);
			return -1;
		}
		cout<<"---dll_id=="<<dll_id<<endl;
		memset(sqlstr, '\0', strlen(sqlstr));
		sprintf(sqlstr, "select dll_name from or_module_dict where module_id='%s'", dll_id);
		cout<<"------sqlstr=="<<sqlstr<<endl;
		char dll_name[50];
		memset(dll_name, '\0', strlen(dll_name));
		if(0 == mysql_real_query(mysql, sqlstr, strlen(sqlstr)))
		{
			MYSQL_RES *result1 = NULL;
			result1 = mysql_store_result(mysql);
			if(result1 != NULL)
			{
				MYSQL_ROW row = NULL;
				row = mysql_fetch_row(result1);
				if(NULL != row)
				{
					strcpy(dll_name, row[0]);
				}
				else
				{
					cout<<"------or_module_dict has no rows------"<<endl;
					mysql_free_result(result1);
					mysql_close(mysql);
					return -1;
				}
			}
			else
			{
				cout<<"---get result1 failed, err_code=="<<mysql_errno(mysql)<<", err_msg=="<<mysql_error(mysql)<<"---"<<endl;
				mysql_free_result(result1);
				mysql_close(mysql);
				return -1;
			}
			mysql_free_result(result1);
		}
		else
		{
			cout<<"---select or_module_dict failed, err_code=="<<mysql_errno(mysql)<<", err_msg=="<<mysql_error(mysql)<<"---"<<endl;
			mysql_close(mysql);
			return -1;
		}
		mysql_close(mysql);
		cout<<"---dll_name=="<<dll_name<<endl;

		HMODULE mod;  //HMODULE返回一个指向模块的句柄,句柄其实就是void *(VOID指针),http://zhidao.baidu.com/question/51875218
		_FUNC func = NULL;
		//_FUNC_CH func = NULL;
		//LoadLibrary载入指定的动态链接库，并将它映射到当前进程使用的地址空间。一旦载入，即可访问库内保存的资源
		//返回值：Long，成功则返回库模块的句柄，失败返回0。会设置GetLastError
		char dll_path[255];
		memset(dll_path, '\0', strlen(dll_path));
		sprintf(dll_path, "./solib/%s", dll_name);
		cout<<"---dll_path=="<<dll_path<<endl;
		mod = LoadLibrary(dll_path);
		cout<<"mod=="<<mod<<endl;
		if(mod)
		{
			//GetProcAddress函数被用来检索在DLL中的输出函数地址,返回值: succ->是DLL中的输出函数地址;err->NULL
			if((func = (_FUNC)GetProcAddress(mod, func_name)) != NULL)
			{
				//func("D:\\Workspace\\space_for_study\\C__Space\\test_cpp_example");
				func();
			}
			else
			{
				//GetLastError函数返回调用线程最近的错误代码值,例如，127:找不到指定的程序
				cout<<"-----------------------GetProcAddress "<<func_name<<" error..."<<GetLastError()<<endl;
			}
			//cout<<"---FreeLibrary=="<<FreeLibrary(mod)<<endl;
		}
		else
		{
			cout<<"-----------------------Loading "<<dll_path<<" error..."<<GetLastError()<<endl;//126:找不到指定的模块,http://baike.baidu.com/view/1730168.htm
		}
		//要释放的一个库句柄,释放指定的动态链接库,返回值：Long，成功则返回非0，失败返回0。会设置GetLastError
		cout<<"---FreeLibrary=="<<FreeLibrary(mod)<<endl;//succ:1;  err:0

		//c++经典50案例练习
		/*
		   cout<<"------begin test cpp 50 examples ------"<<endl;
		//绘制余弦曲线
		TestCosx();
		cout<<"------end test cpp 50 examples------"<<endl;
		*/


		//c++程序设计课本案例练习
		//cout<<"******begin test the course examples******"<<endl;
		//流对象成员函数控制输出格式
		//TestCourse132();
		//流成员函数put、get等
		//TestCourse133();
		//文件输入输出
		//TestCourse138();
		//TestCourse1310();
		//TestCourse1313();
		//TestCourse611();
		//TestCourse613();
		//TestCourse1315();
		//TestCourse614();
		//TestCourse83();
		//TestCourse84();
		//TestCourse92to6();
		//TestCourse102();
		//TestCourse104();
		//TestCourse109();
		//TestCourse914();
		//TestCourse111();
		//TestCourse118();
		//TestCourse121();
		//cout<<"******end test the course examples******"<<endl;


		//其他相关知识点学习
		//cout<<"******begin test the else examples******"<<endl;
		//TestTemp1();
		//获取系统变量
		//TestTemp2();
		//TestTemp3();
		//TestMap();
		//TestVector();
		//TestList();
		//TestDeque();
		//TestSet();
		//TestHashTable();
		//TestBuffer();
		//TestVariable();
		//TestStl();
		//TestStl2();
		//TestStl3();
		//TestExcel();
		//cout<<"******end test the else examples******"<<endl;


		//otl学习
		//TestOtl();

	}
	catch(const exception &e)
	{
		printf("__FUNCTION__==%s, __LINE___==%d, __FILE__==%s, __DATE__==%s, __TIME__==%s\n", __FUNCTION__, __LINE__, __FILE__, __DATE__, __TIME__);
		cout<<"exception==="<<e.what()<<endl;
	}
	//printf("__FUNCTION__==%s, __LINE___==%d, __FILE__==%s, __DATE__==%s, __TIME__==%s\n", __FUNCTION__, __LINE__, __FILE__, __DATE__, __TIME__);

	cout<<"ex_int=="<<ex_int<<endl	//ex_int==100
		<<"ex_str=="<<ex_str	//ex_str==love china
		<<endl;

	cout<<"...out testcpp..."<<endl;

	return 0;

	//main函数返回值，可以执行下面的命令获取
	//[jwkljh@msys test_cpp_example]＄ echo $?
	//0
}


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
//#include <mysql/mysql.h>
//.bashrc中新增： CPLUS_INCLUDE_PATH=:/usr/include/mysql++:/usr/include/mysql
#include "mysql++.h"
//#include <winsock2.h>

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
int main(int argc,char **argv)
{
//	//关闭标准输出和标准错误输出,终端不会打日志
//	int fd;
//	for(fd=1; fd<=2; fd++)
//	{
//		close(fd);
//	}
//	//打开输出终端，写入到testcpp.log
//	fd = open("./testcpp.log", O_WRONLY|O_APPEND|O_CREAT, 0644);
//	cout<<"---fd=="<<fd<<endl;//文件描述符从最小开始，故这里是1

//	cout<<"...in testcpp..."<<endl;

	/* C++ Primer 第4章 4.1 p157
	 * • 在函数体外定义的内置数组，其元素均初始化为 0。
	 * • 在函数体内定义的内置数组，其元素无初始化。
	 * • 不管数组在哪里定义，如果其元素为类类型，则自动调用该类的默认构造函数进行初始化；如果该类没有默认构造函数，则必须为该数组的元素提供显式初始化。
	 */
	//	string s2;
	//	string st2[10];
	//	int itm2[10];
	//	//s==,s2==,s.size()==0,s2.size()==0
	//	cout<<"s=="<<s<<",s2=="<<s2<<",s.size()=="<<s.size()<<",s2.size()=="<<s2.length()<<endl;
	//	int k=0;
	//	//st==~~~~~~~~~~
	//	cout<<"st==";
	//	for(k=0;k!=10;k++)
	//	{
	//		cout<<st[k]<<"~";
	//	}
	//	//st2==~~~~~~~~~~
	//	cout<<"\nst2==";
	//	for(k=0;k!=10;k++)
	//	{
	//		cout<<st2[k]<<"~";
	//	}
	//	//itm==0~0~0~0~0~0~0~0~0~0~
	//	cout<<"\nitm==";
	//	for(k=0;k!=10;k++)
	//	{
	//		cout<<itm[k]<<"~";
	//	}
	//	//itm2==4276192~2293456~2293503~2293700~1975749845~-1195249379~-2~1975652706~1975999428~4276192~
	//	cout<<"\nitm2==";
	//	for(k=0;k!=10;k++)
	//	{
	//		cout<<itm2[k]<<"~";
	//	}
	//	cout<<"\n";
	//
	//测试主函数入参
	//	cout<<"argc=="<<argc<<endl;//默认为1
	//	for(int iargc=0;iargc<argc;iargc++)
	//	{
	//		cout<<"argv["<<iargc<<"]=="<<argv[iargc]<<endl;
	//		//win下 argv[0]为进程路径：argv[0]==d:\Workspace\space_for_study\C__Space\test_cpp_example\testcpp.exe
	//		//linux下 则为进程名./testcpp
	//	}
	//ex_int = argc;
    cout<<"argv=="<<argv<<endl;
    cout<<"*argv=="<<*argv<<endl;
    char opt;
    char **parg = argv;
    while(*parg != NULL)
    {
        cout<<"----parg=="<<*parg<<endl;
        cout<<"parg=="<<parg<<endl;
        //        while((opt = *++*parg) != '\0')
        char *pch = *parg;
        while((opt = *pch) != '\0')
        {
            cout<<"opt=="<<opt<<",";
            pch++;
        }
//        while((opt = **parg) != '\0')
//        {
//            cout<<"opt=="<<opt<<",";
//            (*parg)++;
//            printf("---&*parg==[%p]\n", *parg);
//        }
        cout<<endl;
        parg++;
        printf("---&*parg==[%p]\n", *parg);
    }
    parg = NULL;
    if(argc < 3)
    {
        cout<<"-----入参个数argc < 3------"<<endl;
        return -1;
    }
    cout<<"argv=="<<argv<<endl;
    cout<<"*argv=="<<*argv<<endl;
    printf("---&*argv==[%p]\n", *argv);
    char lib_path[256];
    char func_name[50];
    memset(lib_path, '\0', sizeof(lib_path));
    memset(func_name, '\0', sizeof(func_name));
    strcpy(func_name, argv[1]);
    cout<<"------func_name=="<<func_name<<endl;
    if(strcmp(func_name, "") == 0 || func_name[0] == '\0')
    {
        cout<<"-----func_name is null------"<<endl;
        return -1;
    }

    //1: use MYSQL-C API to connect MYSQL database, to get func's library
    /*MYSQL *mysql = NULL;*/
    //mysql = mysql_init(mysql);
    //mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8");
    //if(mysql != NULL && mysql_real_connect(mysql, "localhost", "testadm", "test123", "testdb", 3306, NULL, 0))
    //{
    //cout<<"---connect db test success---"<<endl;
    //}
    //else
    //{
    //cout<<"---connect db test error---"<<endl;
    //}
    //string sqlstr = "select b.dll_name,b.module_name from Ts_Method_Dict a, TS_MODULE_DICT b "
    //" where a.module_id=b.module_id and a.method_no='"+(string)func_name+"'";
    //cout<<"---sqlstr=="<<sqlstr<<endl;
    //if(0 == mysql_real_query(mysql, sqlstr.c_str(), sqlstr.length()))
    //{
    //MYSQL_RES *result = NULL;
    //cout<<"---select data success---"<<endl;
    //result = mysql_store_result(mysql);
    //cout<<"result=="<<result<<endl;
    //if(result != 0)
    //{
    //MYSQL_ROW row = NULL;
    //row = mysql_fetch_row(result);
    //if(NULL != row)
    //{
    //char *libPathPtr = NULL;
    //libPathPtr = getenv("TEST_SOLIB");
    //sprintf(lib_path, "%s%s", libPathPtr, row[0]);
    ////cout<<"---module_name=="<<row[1]<<endl;
    //}
    //else
    //{
    //cout<<"---no data---"<<endl;
    //mysql_free_result(result);
    //mysql_close(mysql);
    //return -2;
    //}
    //cout<<"------lib_path=="<<lib_path<<endl;
    //}
    //mysql_free_result(result);
    //}
    //else
    //{
    //cout<<"---select data error---"<<endl;
    //mysql_close(mysql);
    //return -3;
    //}
    /*mysql_close(mysql);*/

    //2: use MYSQL++ API to connect MYSQL database, to get func's library
    mysqlpp::Connection myConn(false);
    bool connFlag = true;
    if(myConn.connect("testdb", "localhost", "testadm", "test123"))
    {
        string sqlstr = "select b.dll_name,b.module_name from Ts_Method_Dict a, Ts_Module_Dict b "
            " where a.module_id=b.module_id and a.method_no='"+(string)func_name+"'";
        //cout<<"---sqlstr=="<<sqlstr<<endl;
        //mysqlpp::Query Myquery = myConn.query(sqlstr);
        mysqlpp::Query Myquery = myConn.query();
        //Myquery << sqlstr;
        Myquery << "select b.dll_name,b.module_name from Ts_Method_Dict a, Ts_Module_Dict b "
            " where a.module_id=b.module_id and a.method_no='"+(string)func_name+"'";
        if(mysqlpp::StoreQueryResult myRes = Myquery.store())
        {
			if(myRes.num_rows() == 0)
			{
				cout<<"----------can't find this func_name and dll_name"<<endl;
				connFlag = false;
			}
			char *libPathPtr = NULL;
			libPathPtr = getenv("TEST_SOLIB");
			sprintf(lib_path, "%s%s", libPathPtr, myRes[0][0].c_str());
		}
		else
		{
			cerr<<"----------Failed to get item list:"<<Myquery.error()<<endl;
			connFlag = false;
		}
	}
	else
	{
		cerr<<"--------DB Connection failed:"<<myConn.error()<<endl;
		connFlag = false;
	}

	myConn.disconnect();
	if(!connFlag)
	{
		return -1;
	}
	//cout<<"-----------lib_path=="<<lib_path<<endl;

	try
	{
		_FUNC_CH func = NULL;
		void *dp = NULL;
		dp = dlopen(lib_path, RTLD_LAZY);
		//cout<<"++++++++getcwd=="<<getcwd(NULL, NULL)<<endl;
		if(dp == NULL)
		{
			cout<<"------dlopen error======>"<<dlerror()<<endl;
			printf("__FUNCTION__==%s, __LINE___==%d, __FILE__==%s, __DATE__==%s, __TIME__==%s\n", __FUNCTION__, __LINE__, __FILE__, __DATE__, __TIME__);
			return -1;
		}
		func = (_FUNC_CH)dlsym(dp, func_name);
		if(func == NULL)
		{
			cout<<"------dlsym error======>"<<dlerror()<<endl;
			printf("__FUNCTION__==%s, __LINE___==%d, __FILE__==%s, __DATE__==%s, __TIME__==%s\n", __FUNCTION__, __LINE__, __FILE__, __DATE__, __TIME__);
			return -1;
		}

		struct tm *curTime;
		time_t tv = time(NULL);
		struct timeval micTime;//时间精确到微秒
		curTime = localtime(&tv);
		gettimeofday(&micTime, NULL);

		char timeNow[60];
		memset(timeNow, '\0', sizeof(timeNow));
		//strftime(timeNow, 30, "[%H:%M:%S]..........", curTime);
		snprintf(timeNow, sizeof(timeNow)-1, "[%02d:%02d:%02d:%06ld]", curTime->tm_hour,
				curTime->tm_min, curTime->tm_sec, micTime.tv_usec);
//		cout<<timeNow<<"===>begin call func======>"<<func_name<<endl;

		func(argv[2]);

		tv = time(NULL);
		curTime = localtime(&tv);
		gettimeofday(&micTime, NULL);
		snprintf(timeNow, sizeof(timeNow)-1, "[%02d:%02d:%02d:%06ld]", curTime->tm_hour,
				curTime->tm_min, curTime->tm_sec, micTime.tv_usec);
//		cout<<timeNow<<"===>end call func======>"<<func_name<<endl;
		int idc = dlclose(dp);
		if(idc != 0)
		{
			cout<<"------dlclose error======>"<<dlerror()<<endl;
		}
		//cout<<"---currPath=="<<getcwd(NULL, 0)<<endl;


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
	catch(std::runtime_error &re)
	{
		cout<<"exception=="<<re.what()<<endl;
		exit(-1);
	}
	catch(const exception &e)
	{
		printf("__FUNCTION__==%s, __LINE___==%d, __FILE__==%s, __DATE__==%s, __TIME__==%s\n", __FUNCTION__, __LINE__, __FILE__, __DATE__, __TIME__);
		cout<<"exception==="<<e.what()<<endl;
	}

	//	cout<<"ex_int=="<<ex_int<<endl	//ex_int==100
	//		<<"ex_str=="<<ex_str	//ex_str==love china
	//		<<endl;

//	cout<<"...out testcpp..."<<endl;

	return 0;

	//main函数返回值，可以执行下面的命令获取
	//[jwkljh@msys test_cpp_example]＄ echo $?
	//0
}


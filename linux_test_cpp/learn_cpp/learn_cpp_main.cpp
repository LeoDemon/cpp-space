/*
 * =====================================================================================
 *
 *       Filename:  learn_cpp_main.cpp
 *
 *    Description:  main()
 *
 *        Version:  1.0
 *        Created:  2014/7/9 11:20:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "learn_cpp_main.h"
#include "learn_otl_pub.h"

//#define MYSQL_QUERY
typedef int (*_FUNC)(); //这里_FUNC就代表一个别名，定义了_FUNC为指向函数的指针类型
//typedef int (_FUNC)();//这里_FUNC为指向函数的指针类型的基类型，可以用_FUNC *func定义一个新的函数指针
typedef int (*_FUNC_CH)(const char[]);
typedef int (*_FUNC_DB_CH)(const char[], otl_connect*);
//char *argv[]:argv[]先结合成为数组，然后与前面的*结合,即*argv[] 指针数组，argv[i]中的每个元素都是一个指向char型的指针变量
int main(int argc,char *argv[])
{
    cout<<"...in learncpp..."<<endl;

    if(argc < 3)
    {
        cout<<"-----入参个数argc < 3------"<<endl;
        return -1;
    }
    char lib_path[256];
    char func_name[50];
    char dll[30+1];
    memset(lib_path, '\0', sizeof(lib_path));
    memset(func_name, '\0', sizeof(func_name));
    memset(dll, '\0', sizeof(dll));
    strcpy(func_name, argv[1]);
    cout<<"------func_name=="<<func_name<<endl;

    //2: use otl to connect MYSQL database, to get func's library
    otl_connect mydb;
    otl_connect::otl_initialize(); //initialize OCI environment
    try
    {
        mydb.rlogon("testadm/test123@learn_mysql_dsn");
        otl_cursor::direct_exec(mydb, "use testdb");
        otl_cursor::direct_exec(mydb, "set autocommit=0");

        char sqlstr[512];
        memset(sqlstr, '\0', sizeof(sqlstr));
        sprintf(sqlstr, "%s limit 1", "select b.dll_name from ts_Method_Dict a, ts_Module_Dict b "
            " where a.module_id=b.module_id and a.method_no=:func_name<char[50+1]>");

        otl_nocommit_stream qrystr(1, sqlstr, mydb);
        qrystr.set_flush(false);
        qrystr << func_name;
        if(!qrystr.eof())
        {
            qrystr >> dll;

            char *libPathPtr = NULL;
            libPathPtr = getenv("TEST_SOLIB");
            sprintf(lib_path, "%s%s", libPathPtr, dll);
        }
        else
        {
            cout<<"---select no datas---"<<endl;
        }
        qrystr.close();

#ifdef MYSQL_QUERY
        memset(sqlstr, '\0', sizeof(sqlstr));
        sprintf(sqlstr, "%s '%d%%'", "select method_no,concat(module_id),method_name,method_desc from ts_Method_Dict where module_id like ", 2);
        printf("-----sqlstr==[%s]\n", sqlstr);
        otl_nocommit_stream qryMethod(1, sqlstr, mydb);
        qryMethod.set_flush(false);
        int iRows = 1;
        cout<<"------select datas from ts_method_dict------"<<endl;
        while(!qryMethod.eof())
        {
            char f0[60+1];
            char f1[10];
            char f2[128];
            char f3[128];
            qryMethod >> f0 >> f1 >> f2 >> f3;
            cout<<"------The "<<iRows<<" row: (";
            cout<<f0<<", ";
            cout<<f1<<", ";
            cout<<f2<<", ";
            cout<<f3<<")"<<endl;
            iRows++;
        }
        qryMethod.close();

        const char* dateFormatStr="%Y%m%d%H%i%s";
        memset(sqlstr, '\0', sizeof(sqlstr));
        sprintf(sqlstr, "select  date_format(sysdate(), '%s') from dual", dateFormatStr);
        printf("-----sqlstr==[%s]\n", sqlstr);
        otl_nocommit_stream qryTime(1, sqlstr, mydb);
        qryTime.set_flush(false);
        if(!qryTime.eof())
        {
            char f1[20];
            qryTime >> f1;
            cout<<"-------f1=="<<f1<<endl;
        }
#endif    //MYSQL_QUERY
    }
    catch(otl_exception &p)
    {
        cerr <<"------msg=="<< p.msg << endl; // print out error message
        cerr <<"------stm_text=="<< p.stm_text << endl; // print out SQL that caused the error
        cerr <<"------sqlstate=="<< p.sqlstate << endl; // print out SQLSTATE message
        cerr <<"------var_info=="<< p.var_info << endl; // print out the variable that caused the error
        exit(1);
    }

    if(strlen(dll)  == 0)
    {
        exit(-1);
    }
    cout<<"-----------lib_path=="<<lib_path<<endl;

    try
    {
        _FUNC_DB_CH func = NULL;
        void *dp = NULL;
        dp = dlopen(lib_path, RTLD_LAZY);
        //cout<<"++++++++getcwd=="<<getcwd(NULL, NULL)<<endl;
        if(dp == NULL)
        {
            cout<<"------dlopen error======>"<<dlerror()<<endl;
            printf("__FUNCTION__==%s, __LINE___==%d, __FILE__==%s, __DATE__==%s, __TIME__==%s\n", __FUNCTION__, __LINE__, __FILE__, __DATE__, __TIME__);
            return -1;
        }
        func = (_FUNC_DB_CH)dlsym(dp, func_name);
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
        cout<<timeNow<<"===>begin call func======>"<<func_name<<endl;

        int ret = func(argv[2], &mydb);
//        cout<<"---heihei--- I am out..."<<endl;
        if(ret == 0)
            mydb.commit();
        else 
            mydb.rollback();

        tv = time(NULL);
        curTime = localtime(&tv);
        gettimeofday(&micTime, NULL);
        snprintf(timeNow, sizeof(timeNow)-1, "[%02d:%02d:%02d:%06ld]", curTime->tm_hour,
                curTime->tm_min, curTime->tm_sec, micTime.tv_usec);
        cout<<timeNow<<"===>end call func======>"<<func_name<<endl;
        int idc = dlclose(dp);
        if(idc != 0)
        {
            cout<<"------dlclose error======>"<<dlerror()<<endl;
        }
        //cout<<"---currPath=="<<getcwd(NULL, 0)<<endl;
    }
    catch(otl_exception &p)
    {
        cerr <<"------msg=="<< p.msg << endl; // print out error message
        cerr <<"------stm_text=="<< p.stm_text << endl; // print out SQL that caused the error
        cerr <<"------sqlstate=="<< p.sqlstate << endl; // print out SQLSTATE message
        cerr <<"------var_info=="<< p.var_info << endl; // print out the variable that caused the error
        exit(1);
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
    mydb.logoff();

    cout<<"...out learncpp..."<<endl;

    return 0;
}


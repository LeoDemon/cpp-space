/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_otl.cpp
 *
 *    Description:  study otl...
 *
 *        Version:  1.0
 *        Created:  2012/5/23 22:49:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "test_cpp_main.h"
#include "test_cpp_otl.h"


int TestOtl()
{
	cout<<"...in TestOtl..."<<endl;
	
	otl_connect tdb;
	char test_conn[64]="dbcustopr/dbcustopr@sxcrma";
	
	if(OtlConnectDb(test_conn, tdb) != 0)
	{
		cout<<"Connect db failed!"<<endl;
		return -1;
	}

	OtlDisConnectDb(tdb);

	cout<<"...out TestOtl..."<<endl;

	return 0;
}


//连接数据库
int OtlConnectDb(char *test_conn, otl_connect &tdb)
{
	cout<<"...in OtlConnectDb..."<<endl;

	try
	{
		otl_connect::otl_initialize();
		tdb.rlogon(test_conn);
		tdb.auto_commit_off();
		cout<<"Connect db success..."<<endl;
	}
	catch(otl_exception &p)
	{
		cout<<"Connect error: "<<p.msg<<", "<<p.stm_text<<", "<<p.var_info<<endl;
		return -1;
	}

	cout<<"...out OtlConnectDb..."<<endl;

	return 0;
}


//断开数据库连接
int OtlDisConnectDb(otl_connect &tdb)
{
	cout<<"...in OtlDisConnectDb..."<<endl;

	tdb.rollback();
	tdb.logoff();
	cout<<"DisConnect db success..."<<endl;

	cout<<"...out OtlDisConnectDb..."<<endl;
	return 0;
}


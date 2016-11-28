/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_mysql.cpp
 *
 *    Description:  test for mysql
 *
 *        Version:  1.0
 *        Created:  2013/1/20 20:01:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "test_cpp_main.h"
#include "test_cpp_mysql.h"

MYSQL *mysql;

//output error info
void GetMysqlErrorInfo(const char *info, MYSQL *mysql)
{
	int err_code = mysql_errno(mysql);
	const char *err_msg = mysql_error(mysql);
	cout<<"---"<<info<<", err_code=="<<err_code<<", err_msg=="<<err_msg<<"---"<<endl;
}

//初始化mysql，连接数据库，并设置字符集
bool ConnInit()
{
	cout<<"---in ConnInit---"<<endl;
	mysql = mysql_init(mysql);
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8");//由于vim编辑器的编码为utf-8，故这里设置字符集:utf8,函数成功返回0
	
	if(mysql !=NULL && mysql_real_connect(mysql, "localhost", "dbtest", "admin", "test", 3306, NULL, 0))
	{
		cout<<"---connect db test success---"<<endl;
	}
	else
	{
		GetMysqlErrorInfo("connect mysql failed", mysql);
		return false;
	}
	cout<<"---out ConnInit---"<<endl;
	return true;
}

//query
bool QueryInfo()
{
	cout<<"---in QueryInfo---"<<endl;

	string sqlstr = "SET CHARACTER SET GBK";//防止utf8编码方式查询出来展示时乱码，这里设置编码为GBK，查询结束再还原为utf8
	mysql_real_query(mysql, sqlstr.c_str(), sqlstr.length());
	sqlstr = "select id_no, user_id, user_name, user_age, remark from ur_user_info t";
	//sqlstr = "insert into ur_user_info(user_id,user_name)values(1008, 'Leo')";
	if(0 == mysql_real_query(mysql, sqlstr.c_str(), sqlstr.length()))
	{
		MYSQL_RES *result = NULL;
		cout<<"---select data success---"<<endl;
		//cout<<"------result=="<<result<<endl;//result=0
		result = mysql_store_result(mysql);
		cout<<"------result=="<<result<<endl;
		if(result != NULL)    //result != 0 也可以
		{
			cout<<"------rows=="<<mysql_num_rows(result)<<endl;
			unsigned int fieldcount = mysql_num_fields(result);
			cout<<"------fields=="<<fieldcount<<endl;
			MYSQL_FIELD *field = NULL;
			for(unsigned int i=0; i<fieldcount; i++)
			{
				field = mysql_fetch_field_direct(result, i);
				cout<<"    ";
				cout<<setw(12)<<setiosflags(ios::left)<<field->name;
				if(i<fieldcount-1)
					cout<<"|";
			}
			cout<<endl<<"---------------------------------------------------------------------------------------"<<endl;
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			while(NULL != row)
			{
				for(unsigned int j=0; j<fieldcount; j++)
				{
					cout<<"    ";
					cout<<setw(12)<<setiosflags(ios::left)<<row[j];
					if(j<fieldcount-1)
						cout<<"|";
					//cout<<resetiosflags(ios::left)<<"|";
				}
				cout<<endl<<"---------------------------------------------------------------------------------------"<<endl;
				row = mysql_fetch_row(result);
			}
		}
		mysql_free_result(result);
	}
	else
	{
		GetMysqlErrorInfo("select data failed", mysql);
		return false;
	}
	sqlstr = "SET CHARACTER SET UTF8";
	mysql_real_query(mysql, sqlstr.c_str(), sqlstr.length());//查询结束再还原为utf8

	cout<<"---out QueryInfo---"<<endl;
	//sleep(6);

	return true;
}

//insert
bool InsertInfo()
{
	cout<<"---in InsertInfo---"<<endl;

	long id_no = 1008;
	char str_id_no[10];
	sprintf(str_id_no, "%ld", id_no);
	string user_id = "Leo";
	string user_name = "华夏英雄";
	int user_age = 25;
	char str_user_age[4];
	sprintf(str_user_age, "%d", user_age);
	string user_remark = "我来也...";
	string sqlstr("insert into ur_user_info(id_no, user_id, user_name, user_age, remark)values("+(string)str_id_no+", '"+user_id+"', '"+user_name+"', "+(string)str_user_age+", '"+user_remark+"')");
//	char sqlstrout[255];
//	char sqlstrin[255];
//	sprintf(sqlstrin, "insert into ur_user_info(id_no, user_id, user_name, user_age, remark)values(%ld, '%s', '%s', %d, '%s')", 
//			id_no, user_id.c_str(), user_name.c_str(), user_age, user_remark.c_str());
//	u2g(sqlstrin, strlen(sqlstrin), sqlstrout, 255);
//	cout<<"sqlstrin=="<<sqlstrin<<endl;
//	cout<<"sqlstrout=="<<sqlstrout<<endl;
	//if(0 == mysql_query(mysql, sqlstr.c_str()))
	if(0 == mysql_real_query(mysql, sqlstr.c_str(), sqlstr.length()))
	//if(0 == mysql_real_query(mysql, sqlstrout, strlen(sqlstrout)))
	{
		cout<<"---insert data success---"<<endl;
		//cout<<"---commit=="<<mysql_real_query(mysql, "COMMIT", (unsigned long)strlen("COMMIT"))<<endl;
		//mysql_commit(mysql);
	}
	else
	{
		GetMysqlErrorInfo("insert data failed", mysql);
		//cout<<"---rollback=="<<mysql_real_query(mysql, "ROLLBACK", (unsigned long)strlen("ROLLBACK"))<<endl;
		mysql_rollback(mysql);
		return false;
	}

	cout<<"---out InsertInfo---"<<endl;

	return true;
}

//update
bool UpdateInfo()
{
	cout<<"---in UpdateInfo---"<<endl;

	string id_no = "1007";
	string sqlstr("Update ur_user_info t set t.user_name='浪迹天涯路' where id_no='"+id_no+"'");
	//if(0 == mysql_query(mysql, sqlstr.c_str()))
	if(0 == mysql_real_query(mysql, sqlstr.c_str(), sqlstr.length()))
	{
		cout<<"---Update data success---id_no=="<<id_no<<endl;
		//cout<<"---commit=="<<mysql_real_query(mysql, "COMMIT", (unsigned long)strlen("COMMIT"))<<endl;
		//mysql_commit(mysql);
	}
	else
	{
		GetMysqlErrorInfo("Update data failed", mysql);
		//cout<<"---rollback=="<<mysql_real_query(mysql, "ROLLBACK", (unsigned long)strlen("ROLLBACK"))<<endl;
		mysql_rollback(mysql);
		return false;
	}

	cout<<"---out UpdateInfo---"<<endl;

	return true;
}

//delete
bool DeleteInfo()
{
	cout<<"---in DeleteInfo---"<<endl;

	string id_no = "1008";
	string sqlstr("delete from ur_user_info where id_no='"+id_no+"'");
	//if(0 == mysql_query(mysql, sqlstr.c_str()))
	if(0 == mysql_real_query(mysql, sqlstr.c_str(), sqlstr.length()))
	{
		cout<<"---Delete data success---id_no=="<<id_no<<endl;
		//cout<<"---commit=="<<mysql_real_query(mysql, "COMMIT", (unsigned long)strlen("COMMIT"))<<endl;
		//mysql_commit(mysql);
	}
	else
	{
		GetMysqlErrorInfo("Delete data failed", mysql);
		//cout<<"---rollback=="<<mysql_real_query(mysql, "ROLLBACK", (unsigned long)strlen("ROLLBACK"))<<endl;
		mysql_rollback(mysql);
		return false;
	}

	cout<<"---out DeleteInfo---"<<endl;

	return true;
}


int TestConnectMysql()
{
	cout<<"+++++++++++++in TestConnectMysql+++++++++++++"<<endl;

	bool flag =	ConnInit();
	if(!flag)
	{
		return -1;
	}

	QueryInfo();
	
//	DeleteInfo();
//
	//InsertInfo();
//
//	UpdateInfo();
//
//	QueryInfo();
//
//	cout<<"---commit=="<<mysql_real_query(mysql, "COMMIT", (unsigned long)strlen("COMMIT"))<<endl;
	//mysql_commit(mysql);
//	cout<<"---rollback=="<<mysql_real_query(mysql, "ROLLBACK", (unsigned long)strlen("ROLLBACK"))<<endl;
	//mysql_rollback(mysql);
	QueryInfo();

	mysql_close(mysql);

	cout<<"+++++++++++++out TestConnectMysql+++++++++++++"<<endl;

	return 0;
}



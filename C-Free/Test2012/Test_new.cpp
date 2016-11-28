/*
 * =====================================================================================
 *
 *       Filename:  Test_new.cpp
 *
 *    Description:  Test for c.vim
 *
 *        Version:  1.0
 *        Created:  2012/4/15 22:33:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (lijha), 
 *   Organization:  si-tech
 *
 * =====================================================================================
 */


#include "test.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name: testSimple 
 *  Description: c语言中如果想输出%的话应该是printf("%%")；
 所以连续两个%输出结果就是%，%%ld 应该是%%和ld，而不是%和%ld 
 * =====================================================================================
 */

int testSimple ( )
{
	char cFormat[63+1]="";
	long a2=6;
	long a3=12345678;
	char a4[63+1]="";
	if (0==a2)
	{
		printf("if\n");
		printf("%%\n");
		sprintf(cFormat,"%%ld",a2);//%ld
	}
	else if(5==a2)
	{
		printf("else if\n");
	}
	else
	{   
		printf("else\n");
		sprintf(cFormat,"%%0%dld",a2);//%06ld
	}

	switch (a2)
	{
		case 6:
			cout<<"a2="<<a2<<endl;
		case 7:
			cout<<"case go on..."<<endl;
		case 0:
			cout<<"*******"<<endl;
			break;
		default:
			cout<<"!!!!!!"<<endl;
			break;
	}

	sprintf(a4,cFormat,a3);
	cout<<"cFormat="<<cFormat<<endl;
	cout<<"a4=="<<a4<<endl;

	int a = 1;
	char ca[10+1];
	for(;a<=10;a++){
		itoa(a, ca, 10);
		cout<<"ca=="<<ca<<endl;
	}

	struct tm *datetime;
	time_t lNowtime=0 ;
	//memset(lNowtime, 0, sizeof(time_t));
	lNowtime = time(NULL);
	datetime=localtime(&lNowtime);
	printf("Now time is = %d-%d-%d %d:%d:%d\n",(datetime->tm_year)+1900,(datetime->tm_mon)+1,datetime->tm_mday,datetime->tm_hour,datetime->tm_min,datetime->tm_sec);
	char errRetMsg[512];
	cout<<"before memset errRetMsg =="<<errRetMsg<<endl;
	cout<<"sizeof(errRetMsg)=="<<sizeof(errRetMsg)<<endl;
	cout<<"strlen(errRetMsg)=="<<strlen(errRetMsg)<<endl;
	memset(errRetMsg, 0, sizeof(errRetMsg));
	cout<<"after memset errRetMsg =="<<errRetMsg<<endl;
	sprintf(errRetMsg, "------Can not find order_line_id=[%s]------", "L11xxxxxxxx8899");
	printf("%s\n", errRetMsg);
	return 0;
}			
/* ----------  end of function testSimple  ---------- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name: testCpp 
 *  Description: c++ 常用函数学习
 * =====================================================================================
 */
int testCpp()
{
	/*string str1="";
	//1. const char *str2=NULL;
	char *str2=NULL;//2.
	string str3="123";
	str3=str3.erase(2,1);
	cout<<"str3=="<<str3<<endl;
	char str4[3+1]="123";
	if((string)str4 == "123"){
		cout<<"str4==123"<<endl;
	}else{
		cout<<"str4<>123"<<endl;
	}
	str2=(char *)malloc(sizeof(str2)*5);
	memset(str2,'\0',sizeof(str2)*5);
	str1+="ORA-00001: unique constraint (DBORDERADM.IDX_ORSENDDATA4_PK) violated;";
	str1+=";对外部数据库插入失败;";
	cout<<"str1.length="<<str1.length()<<endl;
	if (72<str1.length())
	{
		str1=str1.substr(0,72);
	}
	//1.str2=str1.c_str();
	strncpy(str2,str1.c_str(),5);//2.
	cout<<"str1="<<str1.c_str()<<endl;
	//cout<<"str1="<<str1<<endl;
	cout<<"str2="<<str2<<endl;*/

	/*学习：指针*/
	/*char *ch_p1="I love China";
	char ch2[20]="Go to 2012";
	char ch_te[30];
	sprintf(ch_te,"%s",ch2);
	cout<<"ch_te=="<<ch_te<<endl;
	sprintf(ch_te,"%s",ch_p1);
	cout<<"ch_te=="<<ch_te<<endl;
	int i3=100;
	int *i_pos=NULL;
	char *ch_p2=NULL;
	int num_3=100;
	int *int_p3 = &num_3;
	ch_p2=&ch2[0];
	i_pos=&i3;
	cout<<"ch_p1="<<ch_p1<<endl;//
	printf("***ch_p1****==%s\n",ch_p1);
	printf("***ch_p2****==%s\n",ch_p2);
	cout<<"---int_p3---=="<<int_p3<<endl;//输出地址 0x22fe30
	cout<<"--*int_p3---=="<<*int_p3<<endl;//输出值：100
	cout<<"*ch_p1="<<*ch_p1<<endl;//输出第一个字符：I
	//for(int i=0;*ch_p1!='\0';ch_p1++,i++){
	//   		cout<<"ch_p1["<<i<<"]="<<*ch_p1<<endl;
	//    }
	cout<<"ch_p2="<<ch_p2<<endl;// 输出时从ch_p2指向的字符开始，直到遇到'\0'
	cout<<"*ch_p2="<<*ch_p2<<endl;//输出第一个字符：C
	// for(int i=0;*ch_p2!='\0';ch_p2++,i++){
	//   		cout<<"ch_p2["<<i<<"]="<<*ch_p2<<endl;
	//    }
	cout<<"int_p3="<<*int_p3<<endl;//输出：100
	

	//studying C++ vector stringstream*/
	cout<<endl<<"begin studying vector..."<<endl;
	/*
	   vector<int> v1;
	   v1.reserve(10);
	   for(int i=0;i<10;i++){
	   v1.push_back(i);
	   }*/

	vector<string> v1;
	v1.push_back("I");
	v1.push_back("LOVE");
	v1.push_back("CHINA 2012!");

	try
	{
		cout<<"v1.size()=="<<v1.size()<<endl;
		cout<<"v1.at(2)=="<<v1.at(2)<<endl;
		cout<<"v1.back()=="<<v1.back()<<endl;
		cout<<"v1.begin()=="<<*v1.begin()<<endl;
		cout<<"v1.front()=="<<v1.front()<<endl;
		cout<<"v1.empty()=="<<v1.empty()<<endl;
		cout<<"v1.at(3)=="<<v1.at(3)<<endl;//数组越界，抛出异常 
	}
	catch (const exception& e)
	{
		cout<<"Exception=="<<e.what()<<endl;
	}
	cout<<"end studying vector..."<<endl<<endl;

	cout<<"begin studying stringstream"<<endl;
	stringstream iostr;
	for(int i=10;i<=15;i++){
		iostr<<"'";
		iostr<<i;
		iostr<<"',";
	}
	string sstr=iostr.str();
	sstr.erase(sstr.length()-1,1);
	cout<<"sstr=="<<sstr<<endl;
	cout<<"end studying stringstream"<<endl;

	cout<<"***begin studying cerr***"<<endl;
	float a,b,c,disc;
	cout<<"please input a,b,c: "<<endl;
	cin>>a>>b>>c;
	if(0==a)
	{
		cerr<<"a=0,error!"<<endl;	
	}
	else
	{
		if((disc=b*b-4*a*c)<0)
		{
			cerr<<"b*b-4*a*c<0,error!"<<endl;
		}
		else
		{
			cout<<"x1="<<(-b+sqrt(disc))/(2*a)<<endl;
			cout<<"x2="<<(-b-sqrt(disc))/(2*a)<<endl;
		}
	}

	cout<<"***end studying cerr***"<<endl;

	return 0;
}
/* ----------  end of function testCpp  ---------- */

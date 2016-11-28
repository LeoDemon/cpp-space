/*
 * =====================================================================================
 *
 *       Filename:  testUtype.cpp
 *
 *    Description:  studying utype
 *
 *        Version:  1.0
 *        Created:  2012/4/21 21:22:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "test.h"

int testUtype()
{
	printf("......c-utype test begin ......\n");
	char phone_no[15];
	char email[20];
	int cust_level;
	int age;
	double fee;
	utype *p;
	p = uInit(0);

	utAddStr(p, "phone_no", "13956971375");
	utAddStr(p, "email", "jwkljh@163.com");
	utAddInt(p, "cust_level", 3);
	utAddInt(p, "age", 23);

	utAddDouble(p, "fee", 28.60);

	utSetStr(p, "email", 1, "jwkljh@qq.com");
	utSetInt(p, "cust_level", UPOS_END, 1);
	utSetDouble(p, "free_fee", UPOS_END, 86.88);

	strcpy(phone_no, utGetStr(p, "phone_no"));
	strcpy(email, utGetStr(p, "email"));
	cust_level = utGetInt(p, "cust_level");
	age = utGetInt(p, "age");
	fee = utGetDouble(p, "fee");

	cout << "lijha's info:" << endl; //cout为c++中的输出，endl为c++中的换行
	cout << "------------phone_no==[" << phone_no << "]" << endl;
	cout << "------------email==[" << email << "]" << endl;
	cout << "------------cust_level==[" << cust_level << "]" << endl;
	cout << "------------age==[" << age << "]" << endl;

	cout << "------------fee==[" << fee << "]" << endl;
	cout << "------------free_fee==[" << utGetDouble(p, "free_fee") << "]" << endl;
	//    printf("lijha's info:\n");
	//    printf("---------phone_no=[%s]\n",phone_no);
	//    printf("---------email=[%s]\n",email);
	//    printf("---------cust_level=[%d]\n",cust_level);
	//    printf("---------age=[%d]\n",age);
	//    printf("---------fee=[%f]\n",fee);
	/* uFree(p); */
	return 0;
}

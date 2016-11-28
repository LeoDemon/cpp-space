/*
 * =====================================================================================
 *
 *       Filename:  testTryCatch.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/4/27 22:18:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "test.h" 

int testTryCatch(){
	cout<<"---test try-catch---"<<endl;

	try
	{
		TtcFun1();
	}
	catch(double)
	{
		cout<<"---ERROR-0---"<<endl;
	}
	cout<<"---end-0---"<<endl;

	return 0;
}

void TtcFun1(){
	try
	{
		TtcFun2();
	}
	catch(char)
	{
		cout<<"---ERROR-1---"<<endl;
	}
	cout<<"---end-1---"<<endl;
	return ;
}

void TtcFun2(){
	try
	{
		TtcFun3();
	}
	catch(int)
	{
		cout<<"---ERROR-2-int---"<<endl;
	}
	catch(...)
	{
		cout<<"---ERROR-2...---"<<endl;
		throw ;
	}
	cout<<"---end-2---"<<endl;
	return ;
}

void TtcFun3(){
	double a=0;
	try
	{
		throw a;
	}
	catch(float)
	{
		cout<<"---ERROR-3-float---"<<endl;
	}
	catch(string)
	{
		cout<<"---ERROR-3...---"<<endl;
	}
	cout<<"---end-3---"<<endl;
	return ;
}


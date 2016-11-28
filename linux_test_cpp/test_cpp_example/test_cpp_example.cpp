/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_example.cpp
 *
 *    Description:  50 c++ examples
 *
 *        Version:  1.0
 *        Created:  2012/5/1 10:34:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "test_cpp_main.h"
#include "test_cpp_example.h"

//绘制[0,360]余弦曲线
int TestCosx()
{
	double y;
	int x,m;

	/*
	 C++中cos,sin,asin,acos这些三角函数操作的是弧度,而非角度
	 弧度=角度*Pi/180
	 */

	for(y=1; y>=-1; y-=0.1) //y轴区间
	{
		m = acos(y)*10; //获取反余弦函数的值并扩大10倍，即x轴，(m最大值为31，即0-180度)
		for(x=1;x<m;x++)
			cout<<" ";
		cout<<"*";
		for(;x<62-m;x++)//对称，180-360度x轴，x=62-m
			cout<<" ";
		cout<<"*"<<endl;
	}

	return 0;
}

//代码转换:从一种编码转为另一种编码, http://worldant.blog.sohu.com/96069463.html
//1.iconv函数族有三个函数,原型如下:
//1)iconv_t iconv_open(const char *tocode, const char *fromcode);
//此函数说明将要进行哪两种编码的转换,tocode是目标编码,fromcode是原编码,该函数返回一个转换句柄,供以下两个函数使用
//2)size_t iconv(iconv_t cd,char **inbuf,size_t *inbytesleft,char **outbuf,size_t *outbytesleft);
//此函数从inbuf中读取字符,转换后输出到outbuf中,inbytesleft用以记录还未转换的字符数,outbytesleft用以记录输出缓冲的剩余空间
//3)int iconv_close(iconv_t cd);
//此函数用于关闭转换句柄,释放资源
int code_convert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen,char *outbuf, size_t outlen)
{
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;
	//iconv_open函数用来打开一个编码转换的流，iconv函数的作用是实际进行转换，iconv_close函数的作用就是关闭这个流
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == size_t(-1))
		return -1;
	iconv_close(cd);
	return 0;
}

//utf-8码转为GB2312码
int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

//GB2312码转为UNICODE码
int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}


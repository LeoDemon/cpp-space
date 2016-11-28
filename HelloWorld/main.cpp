#include "test.h"  //如果这里引入 include "ts_sch.cpp"; 是否在main.cpp中编译一次ts_sch.cpp,然后再单独编译一次ts_sch.cpp,这样就重复编译了
char table_code[30]="";
char db_section[30]="";
char log_msg[2000]="";
char log_path[256]="./";

int writeLog(const char *logpath,const char *msg){
	char log_path[256]="";
	char lt[50]="";
	char logtime[50]="";
	char log_msg[500]="";
	time_t t;
	tm *lctime;

	t=time(NULL);//得到机器的日历时间或者设置日历时间
	lctime=localtime(&t);//返回一个以tm结构表达的机器时间信息
	//cout<<"localtime="<<lctime->tm_hour<<":"<<lctime->tm_min<<":"<<lctime->tm_sec<<endl;//h:m:s
	strftime(lt,sizeof(lt)-1,"%Y.%m.%d %H:%M:%S",lctime);
	strftime(logtime,sizeof(logtime)-1,"%Y%m%d",lctime);

	sprintf(log_path,"%s%s%s%s",logpath,"hello_",logtime,".log");
	ofstream out(log_path,ios::app);		//输出log ios::out为覆盖，ios::app追加

	sprintf(log_msg,"%s:  %s",lt,msg);
	out<<log_msg<<endl;
	out.close();

	return 0;
}

int main(int argc,char * argv[]){

	char *env = NULL;

    cout<<"argc=="<<argc<<", argv[0]"<<argv[0]<<endl;

	//cout<<"Hello World!!!"<<endl<<endl;
	writeLog(log_path,"Hello World begin...");


	while(--argc > 0){

		if(argv[argc][0] != '-'){
			//cout<<"Input parames error..."<<endl;
			writeLog(log_path,"Input parames error...");
			return -1;
		}

		switch(argv[argc][1]){
			case 'T':
				strncpy(table_code,argv[argc]+2,sizeof(table_code)-1);
				break;
			case 'U':
				strncpy(db_section,argv[argc]+2,sizeof(db_section)-1);
				break;
		}
	}

	//cout<<"table_code=="<<table_code<<", db_section=="<<db_section<<endl;
	sprintf(log_msg,"%s%s%s%s","table_code=",table_code,",db_section=",db_section);
	writeLog(log_path,log_msg);
	//
	//	//c++标准输入输出流的控制符
	//	//iotest();
	//	//iotest2();
	//
	//	//c++ fstream类
	//	//iofstreamtest();
	//	
	//	//endl;flush;ends区别
	//	//efl();
	//
	//	//求解一元二次方程的根
	//	//sqrtmath();
	//
	//	//启动后台进程
	//	//GenDeamon();
	//
	//	//查询有低于60分的学生，并输出该学生所有的分数
	//	float score[3][4] = {{65,57,70,60},{58,87,90,81},{90,99,100,98}};
	//	writeLog(log_path,"查询低于60分的学生...begin");
	//#ifdef RUN
	//	//方法1
	//	search1(score,3);
	//#else
	//	//方法2
	//	float *p;
	//	int i,j;
	//	for(i=0;i<3;i++){
	//		p=search2(score+i);
	//		if(p==*(score+i)){
	//			cout<<"search2~~~No."<<i+1<<" fails, his scores are :";
	//			for(j=0;j<4;j++){
	//				cout<<*(p+j)<<",";
	//			}
	//			cout<<endl;
	//		}
	//	}
	//	//return 0;//exit(-1);//exit(0);//exit(1)  ---注意区别
	//#endif
	//
	//	//cout<<"查询低于60分的学生...end"<<endl<<endl;
	//	writeLog(log_path,"查询低于60分的学生...end");


	//输入输出
	//enter();

	//从文件中读写数据
	//fgets_test();

	//字符串练习
	//string_test();

	//static变量求阶乘
	/*{
	  int i;
	  for(i=1;i<=5;i++)
	  cout<<i<<"!="<<fac(i)<<endl;
	  }*/

	//结构体
	//strdef();

	//枚举类型
	//sortball();

	//链表了解
	//Linkedlist_test();

	//链表创建、输出、插入、删除
	//LinkedList_cid();

	//C++类入门
	//csetget();

	//求pi的近似值
	//pi_js();

	//Fibonacci数列
	//fibon();

	//100~200之间的全部素数
	//prime();

	//密码转义
	//cipher();

	//输出图案
	//pic();

	//利用递归求和
	//recursum();

	//三角形面积
	//triangle();

	//冒泡法排序
	//mpfsort();

	//选择法排序
	//xzfsort();

	//string比较
	//stringcmp();

	//string倒序输出char
	//strrev();

	//输出平行四边形
	//txpic();

	//string array
	//studinfo();


	env = getenv("USER");
	if(NULL == env || 0 == strlen(env)){
		writeLog(log_path,"no env ...");
		//setenv("USER","Lijha",1);//stdlib.h 在Linux和Windows里略有不同，比如setenv函数是用在Linux里的，而在Windows里则没有setenv函数，可用putenv来代替
		putenv("USER=Lijha");
		env = getenv("USER");
	}
	if(NULL == env || 0 == strlen(env)){
		writeLog(log_path,"get env error ...");
	}else{
		writeLog(log_path,"get env success ...");
		sprintf(log_msg,"env=%s",env);
		writeLog(log_path,log_msg);
	}


	/*int m=0;
	  while(m<100){
	  writeLog(log_path,"begin deal ...");
	  writeLog(log_path,"end deal ...\n");
	  m++;
	  }*/

	writeLog(log_path,"Hello World end...\n");

	return 0;
}

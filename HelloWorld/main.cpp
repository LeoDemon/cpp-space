#include "test.h"  //����������� include "ts_sch.cpp"; �Ƿ���main.cpp�б���һ��ts_sch.cpp,Ȼ���ٵ�������һ��ts_sch.cpp,�������ظ�������
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

	t=time(NULL);//�õ�����������ʱ�������������ʱ��
	lctime=localtime(&t);//����һ����tm�ṹ���Ļ���ʱ����Ϣ
	//cout<<"localtime="<<lctime->tm_hour<<":"<<lctime->tm_min<<":"<<lctime->tm_sec<<endl;//h:m:s
	strftime(lt,sizeof(lt)-1,"%Y.%m.%d %H:%M:%S",lctime);
	strftime(logtime,sizeof(logtime)-1,"%Y%m%d",lctime);

	sprintf(log_path,"%s%s%s%s",logpath,"hello_",logtime,".log");
	ofstream out(log_path,ios::app);		//���log ios::outΪ���ǣ�ios::app׷��

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
	//	//c++��׼����������Ŀ��Ʒ�
	//	//iotest();
	//	//iotest2();
	//
	//	//c++ fstream��
	//	//iofstreamtest();
	//	
	//	//endl;flush;ends����
	//	//efl();
	//
	//	//���һԪ���η��̵ĸ�
	//	//sqrtmath();
	//
	//	//������̨����
	//	//GenDeamon();
	//
	//	//��ѯ�е���60�ֵ�ѧ�����������ѧ�����еķ���
	//	float score[3][4] = {{65,57,70,60},{58,87,90,81},{90,99,100,98}};
	//	writeLog(log_path,"��ѯ����60�ֵ�ѧ��...begin");
	//#ifdef RUN
	//	//����1
	//	search1(score,3);
	//#else
	//	//����2
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
	//	//return 0;//exit(-1);//exit(0);//exit(1)  ---ע������
	//#endif
	//
	//	//cout<<"��ѯ����60�ֵ�ѧ��...end"<<endl<<endl;
	//	writeLog(log_path,"��ѯ����60�ֵ�ѧ��...end");


	//�������
	//enter();

	//���ļ��ж�д����
	//fgets_test();

	//�ַ�����ϰ
	//string_test();

	//static������׳�
	/*{
	  int i;
	  for(i=1;i<=5;i++)
	  cout<<i<<"!="<<fac(i)<<endl;
	  }*/

	//�ṹ��
	//strdef();

	//ö������
	//sortball();

	//�����˽�
	//Linkedlist_test();

	//����������������롢ɾ��
	//LinkedList_cid();

	//C++������
	//csetget();

	//��pi�Ľ���ֵ
	//pi_js();

	//Fibonacci����
	//fibon();

	//100~200֮���ȫ������
	//prime();

	//����ת��
	//cipher();

	//���ͼ��
	//pic();

	//���õݹ����
	//recursum();

	//���������
	//triangle();

	//ð�ݷ�����
	//mpfsort();

	//ѡ������
	//xzfsort();

	//string�Ƚ�
	//stringcmp();

	//string�������char
	//strrev();

	//���ƽ���ı���
	//txpic();

	//string array
	//studinfo();


	env = getenv("USER");
	if(NULL == env || 0 == strlen(env)){
		writeLog(log_path,"no env ...");
		//setenv("USER","Lijha",1);//stdlib.h ��Linux��Windows�����в�ͬ������setenv����������Linux��ģ�����Windows����û��setenv����������putenv������
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

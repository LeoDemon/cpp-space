#include "worker.h"


int else_test(){
	
	char *ch1="This is my first C-Free programe...";
	int ch2[10];
	
	printf("sizeof(ch1)=%d\n",sizeof(ch1));
	printf("sizeof(ch2)=%d\n",sizeof(ch2));
	printf("strlen(ch1)=%d\n",strlen(ch1));
	
	/*数组与指针*/
	int a[10]; 
	char ch3[10];
	int *pi=NULL;
	char *pc=NULL;
	
	memset(a,0x0,sizeof(a));
	memset(ch3,0x0,sizeof(ch3));
	
	pi=&a[0];
	pc=ch3;
	
	*pi=1;
	*(pi+1)=2;
	*pc='s';
	*(pc+2)='c';
	
	for(int i=0;pi<a+10,i<10;pi++,i++){
		cout<<"a["<<i<<"]="<<*pi<<endl;
	}
	for(int i=0;i<10;i++){
		cout<<"ch3["<<i<<"]="<<*(pc+i)<<endl;
	}
	
	return 0;
}

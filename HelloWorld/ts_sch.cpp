#include "test.h"

extern char log_path[256];

int iotest(){
	cout<<"c++ iostream test begin..."<<endl;

	char *a="0133";
	char *p;
	for(p=a;*p!='\0';p++){
		cout<<"*a=="<<(*p)<<endl;
	}
	cout<<"atoi(a)=="<<atoi(a)<<endl;

	char temp1[18] = "  I love china  ";
	char temp2[20];
	strncpy(temp2,temp1,20-1);
	cout<<"strlen(temp1)=="<<strlen(temp1)<<endl;
	cout<<"sizeof(temp1)=="<<sizeof(temp1)<<endl;
	cout<<"strlen(temp2)=="<<strlen(temp2)<<endl;
	cout<<"sizeof(temp2)=="<<sizeof(temp2)<<endl;
	cout<<"temp2=="<<temp2<<endl;

	char *temp3;
	temp3=chartest(temp1);
	cout<<"strlen(temp3)=="<<strlen(temp3)<<endl;
	cout<<"sizeof(temp3)=="<<sizeof(temp3)<<endl;
	cout<<"temp3=="<<temp3<<endl;

	int t=0;
	bool fl1=true,fl2;
	cout<<"fl1=="<<fl1<<endl;
	fl2=-122;
	cout<<"t+fl1+fl2+true=="<<(t+fl1+fl2+true)<<endl;

	float d=13.9812338; //6位有效数字，输出13.9812
	double x=123.456,y=3.14159,z=-3214.67;//15位有效数字
	cout<<"x=="<<x<<",d=="<<d<<endl;
	//cout<<setiosflags(ios::fixed)<<setiosflags(ios::right)<<setprecision(5);
	cout<<setw(15)<<x<<endl;
	cout<<setw(15)<<y<<endl;
	cout<<setw(15)<<z<<endl;

	int b=123456;
	//cout<<b<<endl;
	//cout<<hex<<b<<endl;
	//cout<<oct<<b<<endl;
	//cout<<setiosflags(ios::uppercase)<<b<<endl;
	//cout<<setw(10)<<b<<","<<b<<endl;
	cout<<setw(10)<<b<<','<<setw(10)<<b<<endl;//setw(10)只对其后一个输出项有效,其他的设置对后面的输出都有效
	cout<<setfill('*')<<setw(10)<<b<<endl;
	//cout<<setiosflags(ios::showpos)<<b<<endl;
	
	char c;
	//c=getchar();
	//putchar(c);
	for(;(c=getchar())!='\n';)
	cout<<c;
	putchar(10);//putchar('\n')

	cout<<"c++ iostream test end..."<<endl<<endl;
	return 0;
}

int iotest2(){
	//函数模板
	int e,f,g;
	cout<<"please input 3 numbers again:";
	cin>>e>>f>>g;
	cout<<"T min(e,f,g)="<<mins(e,f,g)<<endl;
	
	//输入流cin.getline,读取一行数据
	char ptr1[10];
	char ptr2[10];
	char ptr3[10];
	memset(ptr1,'\0',10);
	memset(ptr2,'\0',10);
	memset(ptr3,'\0',10);
	cout<<"please input string:";
	cin.ignore(10,'\n');//跳过输入流中的10个字符，或遇到换行符停止
	cin.getline(ptr1,10,'/');//实际上只取9个字符，最后一个给'\0'   
		//输入：chinalove99/abc/sss   chinalove/abc123ccc88/sssaaa
	cout<<"ptr1=="<<ptr1<<endl;

	cout<<"cin-flags1: "<<cin.good()<<endl;
	cin.clear();//清除错误标志,下面cin.get()即可继续取数据
	cout<<"cin-flags2: "<<cin.good()<<endl;
	cin.getline(ptr2,10,'/');
	cout<<"ptr2=="<<ptr2<<endl;

	cout<<"cin-flags3: "<<cin.good()<<endl;
	cin.clear();
	char *buffer;
	streambuf *buf;
	buf = cin.rdbuf();//获得指向输入流缓冲区的指针
	buffer = new char(buf->in_avail());//开辟一块输入流缓冲区那么大的内存,其中buf->in_avail():获取缓冲区的大小    
	buf->sgetn(buffer,buf->in_avail());//这一行可以将输入流缓冲区中的内容读到buffer中,这样的话输入缓冲区中就没有内容了！也就不会影响你下面的输入了
	
	cout<<"please input string again:";
	cin.get(ptr3,10,'/');
	cout<<"ptr3=="<<ptr3<<endl;

	return 0;
}

char * chartest(char *ch){
	int len;

	if(ch == NULL)
		return NULL;

	for(len=strlen(ch)-1;len>0;len--){
		if(ch[len] == ' ' || ch[len] == '\t' || ch[len] == 0x0a || ch[len] == 0x0d){
			ch[len] = 0x0;
		}
		else 
			break;
	}
	//cout<<"ch=="<<ch<<endl;
	for(;;){
		if(*ch == ' ' || *ch == '\t' || *ch == 0x0a || *ch == 0x0d){
			*ch=0x0;
			ch++;
		}
		else 
			return ch;
	}
}

int iofstreamtest(){
	cout<<"ifstream~ofstream...test begin..."<<endl;

	//fstream out("./oftest.log",ios::in|ios::out);		//输出到当前路径下 ios::out为覆盖，ios::app追加
	ofstream out("./oftest.log"); // 输出到绝对路径  默认以输出方式打开文件  ofstream out("E:\\oftest.log",ios::out);
	int i;
	for(i=0;i<100;i++){
		out<<"I love feifei"<<endl;
	}
	out<<"come on..."<<endl;
	char str1[] = "forever...\n";
	out.write(str1,strlen(str1));
	out.close();

	cout<<"ifstream~ofstream...test end..."<<endl<<endl;
	return 0;
}


int efl(){
	cout<<"ends~flush~endl~test begin..."<<endl;

	cout << "a" ;
    cout << "b" <<ends;//ends 输出一个空字符 
    cout << "c" <<endl;
    cout << "e" << flush;
    cout << "f" << flush;
    cout << "g" ;
    cout << "h" <<ends;
    cout << "i" << flush;
    cout << "j" <<endl;

	//ab c
	//efgh ij

	cout<<"ends~flush~endl~test end..."<<endl<<endl;
	return 0;
}

int sqrtmath(){
	cout<<"...ax2+bx+c=0...begin"<<endl;
	
	float a,b,c,x1,x2;
	cin>>a>>b>>c;
	cout<<sqrt(b*b-4*a*c)<<endl;
	if(sqrt(b*b-4*a*c)>=0){
		x1=(-b+sqrt(b*b-4*a*c))/(2*a);
		x2=(-b-sqrt(b*b-4*a*c))/(2*a);
		cout<<"x1=="<<x1<<endl;
		cout<<"x2=="<<x2<<endl;
	}

	cout<<"...ax2+bx+c=0...end"<<endl<<endl;
	return 0;
}

//p为指针变量，它指向包含4个浮点型元素的一维数组
void search1(float (*p)[4],int n){
	cout<<"search1~~~查询低于60分的学生...begin"<<endl;

	int i,j,flag;
	for(j=0;j<n;j++)
	{
		flag = 0;
		for(i=0;i<4;i++) 
			if(*(*(p+j)+i)<60)flag=1;
		if(flag == 1)
		{
			cout<<"No."<<j+1<<" fails, his scores are :";
			for(i=0;i<4;i++)
			{
				cout<<*(*(p+j)+i)<<",";
			}
			cout<<endl;
		}
	}
	cout<<endl;
}


float *search2(float (*pointer)[4]){
	int i;
	float *pt;
	pt = *(pointer+1);
	for(i=0;i<4;i++){
		if(*(*pointer+i)<60) pt=*pointer;
	}
	return pt;
}


void enter(){
	//输入字符
	int c;
	cout<<"请输入字符:";
	//c=getchar();
	//printf("您输入的字符是:%c\n",c);
	while((c=getchar()) != '\n'){  //getchar()返回的是int型
	cout<<"您输入的字符是:"<<(unsigned char)c<<endl<<endl;
	}
	system("cls");//c++中清屏,在c语言中是ClearScreen()和clrscr()函数
	char *a,str[100+1];
	a=str;
	cout<<"请输入 love: ";
	scanf("%s",a);
	int i;
	cout<<"验证中,请稍候";
	for(i=0;i<3;i++){
		cout<<".";
		Sleep(500);//引入windows.h使用Sleep()函数，注意Sleep首字母大写，括号内为毫秒数
	}
	while(strcmp(a,"love")!=0){
		cout<<"您输入的是："<<a<<",字符不对,请重新输入:";
		//scanf("%s",a);
		cin>>a;
	}
	cout<<"***输入正确***"<<endl<<endl;
}


void fgets_test(){
	cout<<"从文件中读写数据...begin"<<endl;

	FILE *fp1,*fp2;
	char inmsg[60];
	//sizeof(inmsg)返回的是字符数组的长度，包括\0,而strlen不计入\0，strlen不区分是数组还是指针，就读到\0为止返回长度
	cout<<"******sizeof(inmsg)=="<<sizeof(inmsg)<<endl;
	if((fp1 = fopen("./file.txt","r+")) == NULL){
		cout<<"打开file.txt失败..."<<endl;
		return;
	}
	if(fgets(inmsg,12+1,fp1) == NULL){
		cout<<"读取file.txt失败,请检查配置文件!"<<endl;
		return;
	}
	while(!feof(fp1)){
			cout<<"info=="<<inmsg<<endl;
			if((fp2 = fopen("./fp.log","a+")) == NULL){
				cout<<"打开fp.log失败..."<<endl;
				return;
			 }
			//string s1 = "\n";
			fflush(fp2);
			//fwrite(s1.c_str(),s1.length(),1,fp2);
			fwrite(inmsg,strlen(inmsg),1,fp2);
			fgets(inmsg,12+1,fp1);
		}
	fclose(fp2);
	fclose(fp1);


    cout<<"从文件中读写数据...end"<<endl<<endl;
}


void string_test(){
	cout<<"字符串学习...begin"<<endl;

	char *a="I love you...";
	cout<<"the length of a =="<<strlen(a)<<endl;
	char b[13+1];//13+1,防止因\0导致的数组越界
	int i;
	for(i=0;*(a+i)!='\0';i++)//不等于\0，那么结束符就没有复制
		*(b+i)=*(a+i);
	*(b+i)='\0';//这里需要补上结束符，字符串都必须以\0作为结束符
	cout<<"string a =="<<a<<endl;
	cout<<"string b =="<<b<<endl;

    cout<<"字符串学习...end"<<endl<<endl;
}

int fac(int i){
	static int m=1;
	m=m*i;
	return m;
}

void strdef(){
	STUDENT student;
	student.num=1066;
	student.name="wangfeifei";//strcpy(student.name,"wangfeifei");
	student.score[0]=98.5;
	student.score[1]=93;
	student.score[2]=95;

	//strprt(student);  //用结构体变量作为实参
	strprt(&student);	//用结构体变量的指针作为实参
}

void strprt(STUDENT *p){
	cout<<endl;
	/*cout<<"Her info 1: name="<<stu.name<<",num="<<stu.num<<",score="
		<<stu.score[0]<<","<<stu.score[1]<<","<<stu.score[2]<<endl;*///用结构体变量作为实参
	cout<<"Her info 2: name="<<p->name<<",num="<<p->num<<",score="
		<<p->score[0]<<","<<p->score[1]<<","<<p->score[2]<<endl<<endl;//用结构体变量的指针作为实参
}

color &operator++(color &k){
	k = (color)(k+1);
	return k;
}

void sortball(){//5个不同颜色的球，取出三种不同颜色的球的方法有多少种
	//enum color {red,yellow,blue,white,black};
	enum color i,j,k,pri;
	//enum {red,yellow,blue,white,black}i,j,k,pri;效果是一样的

	int n,loop;
	n=0;
	for(i=red;i<=black;i++/*i=(color)(i+1)*/){ //c++中不支持++，--等运算符，都需要自己定义，这里用color进行转换
		for(j=red;j<=black;j++/*j=(color)(j+1)*/){//自定义了&operator++(color &k)函数，即可用++了
			if(i!=j){
				for(k=red;k<=black;k++/*k=(color)(k+1)*/){
					if((k!=i)&&(k!=j)){
						n=n+1;
						cout<<"    "<<n;
						for(loop=1;loop<=3;loop++){
							switch(loop){
							case 1:pri=i;break;
							case 2:pri=j;break;
							case 3:pri=k;break;
							default:break;
							}
							switch(pri){
							case red:cout<<"           red";break;
							case yellow:cout<<"           yellow";break;
							case blue:cout<<"           blue";break;
							case white:cout<<"           white";break;
							case black:cout<<"           black";break;
							default:break;
							}
						}
						cout<<endl;
					}
				}
			}
		}

	}
	cout<<"toal:"<<n<<endl<<endl;
}

int GenDeamon(){
	cout<<"daemon start begin..."<<endl;
	//int childpid,fd;
	//int flag;

	if(GetCurrentProcessId()==1){
		//chdir("/");
		//umask(002);
		cout<<"father process is 1..."<<endl;
		return 0;
	}

	cout<<"GetCurrentProcessId()=="<<GetCurrentProcessId()<<endl;//获取当前进程一个唯一的标识符 
	//cout<<"GetWindowThreadProcessId()=="<<GetWindowThreadProcessId()<<endl;
	
	//if ((childpid = fork())=0 ) {
	//	printf("can't fork first child %s %d\n",__FILE__,__LINE__);
	//	exit(-1);
	//}


	cout<<"daemon start finish..."<<endl;
	return 0;
}

void Linkedlist_test(){
	cout<<"Linked list test begin..."<<endl;

	STUDENT li,wang,lwa,*head,*p;
	li.num=1088;li.name="lijha";li.score[0]=93;
	wang.num=1066;wang.name="wangff";wang.score[0]=96;
	lwa.num=1099;lwa.name="lwrlf";lwa.score[0]=99;
	head=&li;
	li.next=&wang;
	wang.next=&lwa;
	lwa.next=NULL;
	p=head;

	do{
		cout<<"num="<<p->num<<",name="<<p->name<<",score="<<p->score[0]<<endl;
		p=p->next;
	}while(p!=NULL);

	cout<<"Linked list test end..."<<endl<<endl;
}

void LinkedList_cid(){
	STU *student,*head;
	int del_num;

	//create list
	cout<<"create a list, please input records:"<<endl;
	head=Createlist();

	//output list
	print(head);

	//delete list node
	cout<<"delete a list node, please input record:";
	cin>>del_num;
	while(del_num > 0 && head != NULL){
		head=Dellist(head,del_num);
		print(head);
		if(head != NULL){
			cout<<"If you want to delete a list node again, please input del_num larger than 0:";
			cin>>del_num;
		}else{
			cout<<"This list is null..."<<endl;
		}	
	}

	//insert list node
	cout<<"insert a list node, please input records:"<<endl;
	student=(STU *)malloc(LEN);
	cin>>student->stu_num>>student->stu_name>>student->score;
	while(student->stu_num > 0){
		cout<<"head0=="<<head<<endl;
		//cout<<"&head0=="<<&head<<endl;
		Insertlist(&head,student);
		//cout<<"&head1=="<<&head<<endl;
		cout<<"head1=="<<head<<endl;
		print(head);
		cout<<"If you want to insert a list node again, please input stu_num larger than 0:"<<endl;
		student=(STU *)malloc(LEN);
		cin>>student->stu_num>>student->stu_name>>student->score;
	}
}

STU *Createlist(){
	STU *head,*p1,*p2;
	int n=0;
	p1=p2=(STU *)malloc(LEN);
	//如果stu_name定义时为指针变量，即char *stu_name;那么这里会报错，因为此时stu_name无值，cin输入的值放到哪里呢？
	cin>>p1->stu_num>>p1->stu_name>>p1->score;
	head=NULL;
	while(p1->stu_num>0){
		n=n+1;
		if(n==1)
			head=p1; 
		else
			p2->next=p1;
		p2=p1;
		p1=(STU *)malloc(LEN);
		cin>>p1->stu_num>>p1->stu_name>>p1->score;
	}
	p2->next=NULL;
	cout<<"There are "<<n<<" records:"<<endl;
	return(head);
}

void print(STU *head){
	STU *p;
	char space[2+1]="  ";
	for(p=head;p!=NULL;p=p->next){
		cout<<p->stu_num<<space<<p->stu_name<<space<<p->score<<endl;
	}
}

STU *Dellist(STU *head,int num){
	STU *p1,*p2;
	int n = num;
	if(head == NULL){
		cout<<"This list is null..."<<endl;
		return NULL;
	}
	p1=head;
	while(num != p1->stu_num && p1->next != NULL){
		p2 = p1;
		p1 = p1->next;
	}
	if(num == p1->stu_num){
		if(head == p1){
			head = p1->next;
		}
		else {
			p2->next = p1->next;
		}
		cout<<"The "<<num<<" is deleted..."<<endl;
		n = n-1;
	}
	else {
		cout<<"The "<<num<<" not been found...delete failed..."<<endl;
	}
	return head;
}

void Insertlist(STU **head,STU *stu){
	STU *p1,*p2,*p0;
	p0 = *head;
	p1 = stu;
	if(*head == NULL){	//链表为空
		*head = p1;
		p1->next = NULL;
		return ;
	}
	while(p1->stu_num > p0->stu_num && p0->next != NULL){
		p2 = p0;
		p0 = p0->next;
	}
	if(p1->stu_num <= p0->stu_num){
		if(p0 == *head){		//插入到首节点
			*head = p1;
			cout<<"head2=="<<*head<<endl;
			p1->next = p0;
		}else{				//插入到中间节点
			p1->next = p0;
			p2->next = p1;
		}
	}else{					//插入到尾节点
		p0->next = p1;
		p1->next = NULL;
	}
	return ;
}

void csetget(){

	cout<<endl;
	cout<<"C++ class test begin..."<<endl;

	Staff staff1,staff2;

	staff1.setdata();
	staff2.setdata();

	staff1.display();
	staff2.display();

	cout<<"C++ class test end..."<<endl;
}

/*******pi/4 = 1-1/3+1/5-1/7+...********/
int pi_js(){
	cout<<"求pi的近似值...begin..."<<endl;
	int s=1;
	double t=1,pi=0,n=1;
	while(fabs(t)>1e-8){
		pi=pi+t;
		s=-s;
		n=n+2;
		t=s/n;
	}
	pi = pi *4;
	cout<<"pi == "<<setiosflags(ios::fixed)<<setprecision(15)<<pi<<endl;
	cout<<"求pi的近似值...end..."<<endl<<endl;
	return 0;
}

/************1,1,2,3,5,8,13,21,34,55...**************/
int fibon(){
	cout<<"Fibonacci 数列 begin..."<<endl;
	int f1=1,f2=1;
	for(int i=1;i<=20;i++){
		cout<<setw(12)<<f1<<setw(12)<<f2;
		if(i%2==0)cout<<endl;
		f1=f2+f1;
		f2=f1+f2;
	}
	cout<<"Fibonacci 数列 end..."<<endl<<endl;
	return 0;
}

/***********101,103,107...************/
int prime(){
	cout<<"prime between 100 and 200 begin..."<<endl;
	int i,j,k,n=0;
	bool pri;
	for(i=101;i<200;i=i+2){
		pri=true;
		k=(int)sqrt((double)i);
		for(j=2;j<=k;j++){
			if(i%j==0){
				pri=false;
				break;
			}
		}
		if(pri==true){
			cout<<setw(6)<<i;
			n=n+1;
		}
		if(n%10==0){
			cout<<endl;
		}
	}
	cout<<endl;
	cout<<"prime between 100 and 200 end..."<<endl<<endl;
	return 0;
}

/***********A-E,B-F,C-G,z-d...************/
int cipher(){
	cout<<"cipher begin..."<<endl;
	cout<<"please input : ";
	char c;
	while((c=getchar())!=0x0a){
		if((c>='A' && c<='Z')||(c>='a' && c<='z')){
			c=c+4;
		}
		if((c>'Z' && c<'Z'+4)||(c>'z')){
			c=c-26;
		}
		cout<<c;
	}
	cout<<endl;
	cout<<"cipher end..."<<endl<<endl;
	return 0;
}

/*
*
* * *
* * * * *
* * * * * * *
* * * * *
* * *
*
*/
int pic(){
	cout<<"pic begin..."<<endl;

	int n,i,k;
	cout<<"please input the number:";
	cin>>n;
	while(n>0){
	for(i=1;i<=n;i++){
		for(int j=1;j<=2*i-1;j++){
			cout<<"* ";
		}
		cout<<endl;
	}
	for(k=n-1;k>=1;k--){
		for(int m=1;m<=2*k-1;m++){
			cout<<"* ";
		}
		cout<<endl;
	}
	cin>>n;
	}

	cout<<"pic end..."<<endl<<endl;
	return 0;
}

/**********求和 1*1+2*2+3*3+...***********/
int recursum(){
	cout<<"recursive begin..."<<endl;

	int n,sum;
	cout<<"please input number:";
	cin>>n;
	sum=recursive(n);
	cout<<"sum("<<n<<")="<<sum<<endl;

	cout<<"recursive end..."<<endl<<endl;
	return 0;
}

int recursive(int n){
	int sum;
	if(n<1){
		cout<<"input number is error..."<<endl;
		sum=0;
	}
	if(n==1){
		return sum=1;
	}
	else if(n>1){
		sum=recursive(n-1)+n*n;
	}
	return sum;
}

/**********area=s*(s-a)*(s-b)*(s-c),s=1/2(a+b+c)***********/
int triangle(){
	cout<<"triangle begin..."<<endl;

	double a,b,c,s,area;
	cout<<"please input triangle a,b,c:";
	cin>>a>>b>>c; //输入时以空格隔开，不要用逗号隔开，3 4 5
	//cout<<"a=="<<a<<",b=="<<b<<",c=="<<c<<endl;
	if(((a+b)>c)&&((a+c)>b)&&((b+c)>a)){
		s=S(a,b,c);
		area=AREA(s,a,b,c);
		cout<<"S(a,b,c)="<<s<<", AREA(a,b,c)="<<area<<endl;
	}else{
		cout<<"input triangle a,b,c number is error..."<<endl;	
	}
	cout<<"triangle end..."<<endl;
	return 0;
}

/*******3 6 1 9 4 22 18 99 100 88*******将a[0]-a[9]中最大的数与a[0]对换，将a[1]-a[9]中最大的数与a[1]对换******/
int xzfsort(){
	cout<<"xzfsort begin..."<<endl;

	int a[10],temp,Count=0;
	cout<<"please input 10 numbers:";
	for(int i=0;i<10;i++){
		cin>>a[i];
	}

	cout<<"before sort the 10 numbers is:";
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
	for(int j=0;j<9;j++){
		for(int k=j+1;k<10;k++){
			if(a[j]<a[k]){
				temp=a[j];
				a[j]=a[k];
				a[k]=temp;
			}
			Count++;
		}
	}
	cout<<"after sort the 10 numbers is : ";
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl<<"Count=="<<Count<<endl;

	cout<<"xzfsort end..."<<endl<<endl;

	return 0;
}

/*******3 6 1 9 4 22 18 99 100 88****将相邻的两个数比较，大的数放到前面********/
int mpfsort(){
	cout<<"mpfsort begin..."<<endl;

	int a[10],temp,Count=0;
	cout<<"please input 10 numbers:";
	for(int i=0;i<10;i++){
		cin>>a[i];
	}

	cout<<"before sort the 10 numbers is : ";
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;

	for(int i=0;i<9;i++){
		for(int j=0;j<9-i;j++){
			if(a[j]<a[j+1]){
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
			Count++;
		}
	}


	cout<<"after sort the 10 numbers is : ";
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl<<"Count=="<<Count<<endl;

	cout<<"mpfsort end..."<<endl<<endl;

	return 0;
}

/************china China love myself Abc --> Abc China china love myself************/
int stringcmp(){
	cout<<"string compare begin..."<<endl;

	string name[5],temp;
	int Count=0;

	//string str1="love",str2="China";
	//if(str1 > str2){
	//	cout<<"love > China"<<endl;
	//}else{
	//	cout<<"love < China"<<endl;
	//}

	cout<<"please input 5 strings: ";
	for(int i=0;i<5;i++){
		cin>>name[i];
	}

	cout<<"before sort the 5 strings: ";
	for(int i=0;i<5;i++){
		cout<<name[i]<<" ";
	}
	cout<<endl;

	for(int i=0;i<4;i++){
		for(int j=i+1;j<5;j++){
			if(name[i]>name[j]){
				temp=name[i];
				name[i]=name[j];
				name[j]=temp;
			}
			Count++;
		}
	}

	cout<<"after sort the 5 strings: ";
	for(int i=0;i<5;i++){
		cout<<name[i]<<" ";
	}
	cout<<endl<<"Count=="<<Count<<endl;

	cout<<"string compare end..."<<endl<<endl;
	return 0;
}

/*****************EMEVOL--->LOVEME******************/
int strrev(){
	cout<<"string reverse begin..."<<endl;
	char str[10]="EMEVOL";
	string str2="EMEVOL";

	//方法一：用字符数组
	for(int i=strlen(str)-1;i>=0;i--){
		cout<<str[i];
	}
	cout<<endl;

	//方法二：用字符串
	/*cout<<"str2.length=="<<str2.length()<<endl;
	cout<<"str2.size=="<<str2.size()<<endl;*/
	//string str3="";
	for(int i=str2.length()-1;i>=0;i--){
		//str3+=str2.at(i);
		cout<<str2.at(i);
	}
	//cout<<str3<<endl;
	cout<<endl;

	cout<<"string reverse end..."<<endl<<endl;
	return 0;
}

/*
* * * * *
  * * * * * 
    * * * * * 
	  * * * * * 
	    * * * * * 
*/
int txpic(){
	cout<<"txpic begin..."<<endl;
	
	int n;
	cout<<"please input a number:";
	cin>>n;

	if(n<2){
		cout<<"The number is smaller then 2..."<<endl;
		return -1;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<i;j++){
			cout<<" "<<" ";
		}
		for(int k=0;k<n;k++){
			cout<<"* ";
		}
		cout<<endl;
	}

	cout<<"txpic end..."<<endl<<endl;
	return 0;
}

/*********
1001 aa 87
1002 bb 92
1003 cc 56
1004 dd 67
1005 ee 71
1006 ff 23
1007 gg 82
1008 hh 43
1009 ii 19
1010 kk 32
*******/
string studnum[10],studname[10],studscore[10];
int studinfo(){
	//cout<<"studinfo begin..."<<endl;
	writeLog(log_path,"studinfo begin...");

	cout<<"please input 10 students' info:"<<endl;
	studinput();

	cout<<"please input student's num:";
	string num="";
	cin>>num;
	studsearch(num);

	cout<<"the student info who score is small then 60 : "<<endl;
	for(int i=0;i<10;i++){
		if(studscore[i]<"60"){
			cout<<"studnum="<<studnum[i]<<",studname="<<studname[i]<<",studscore="<<studscore[i]<<endl;
		}
	}
	writeLog(log_path,"studinfo end...\n");
	//cout<<"studinfo end..."<<endl<<endl;
	return 0;
}

int studinput(){
	for(int i=0;i<10;i++)
		cin>>studnum[i]>>studname[i]>>studscore[i];
	return 0;
}

int studsearch(string num){
	bool flag=false;
	for(int i=0;i<10;i++){
		if(num==studnum[i]){
			cout<<"The student's info has found:";
			cout<<"studnum="<<studnum[i]<<",studname="<<studname[i]<<",studscore="<<studscore[i]<<endl;
			flag=true;
			break;
		}
	}
	if(flag==false){
		cout<<"The student's info has not found..."<<endl;
	}
	cout<<endl;
	return 0;
}

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

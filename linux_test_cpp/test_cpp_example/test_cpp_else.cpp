/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_else.cpp
 *
 *    Description:  for else cpp example
 *
 *        Version:  1.1
 *        Created:  2012/5/7 20:35:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "test_cpp_main.h"
#include "test_cpp_else.h"

char *pStr=NULL;

/*
 *测试知识点：
 *1.逗号表达式：
 *2.scanf函数的输入格式:
 */
int TestTemp1()
{
	int n,m;
	cout<<"please enter two num: ";
	while(cin>>n>>m,m+n) //逗号表达式，先求解表达式1，再求解表达式2，结果为表达式2的值
	{
		int a=n*n-4*m;//求注解
		if(a<0)//a 有什么作用？
			cout<<"No\n";
		else
		{
			double b= (n+sqrt(double(a)))/2;//什么意思？
			if(b==int(b))// 求注解
				cout<<"Yes\n";
			else
				cout<<"No\n";
		}
	}

	printf("please enter two num again: ");
	scanf("%d,%d",&n,&m);//这里%d%d 或%d %d 或%d,%d  都可以，但输入时前两种要用空格隔开，第3种方式用逗号隔开
	printf("%d,%d\n",n,m);

	return 0;
}


/*
 *知识点：
 *   1. 获取系统变量
 *   2. 指针变量使用strcpy问题
 *   3. strchr(char *s,char c) 查找字符串s中首次出现字符c的位置，返回首次出现c的位置的指针，如果s中不存在c则返回NULL
 *   4. strstr(char *s,char *c) 从字符串s中查找首次出现字符串c的位置(不比较结束符NULL)，返回首次出现c位置的指针，如果s中不存在c则返回NULL
 *   5. sscanf(char *str,const char * format,...) 将参数str的字符串根据参数format字符串来转换并格式化数据，成功返回返回的参数数目，失败返回-1，若将str格式化到s1,s2,s3三个变量，3个变量都获得到了值，则返回3，若其中一个获得值，则返回1，若都没获得值，则返回0.
 *   6. strcmp(char *s1,char *s2)与stricmp(char *s1,char *s2)区别:stricmp不区分大小写
 */
int TestTemp2()
{
	cout<<"...int TestTemp2..."<<endl;

	char *userName=NULL;
	int pid=0;
	pid=getpid();//获取进程id，是主进程还是子进程？
	userName=getenv("USERNAME");
	cout<<"pid=="<<pid<<endl;
	if(NULL == userName || strlen(userName) == 0)
	{
		cout<<"...get USERNAME from env failed..."<<endl;
	}
	else
	{
		cout<<"...get USERNAME from env successed..."<<endl;
		cout<<"userName=="<<userName<<endl;
	}

	char user_name[255]="I love China...123...999...go!";
	char temp_name[25];
	char *uname;
	//char *uname2 = NULL;
	uname = user_name;
	cout<<"sizeof(uname)=="<<sizeof(uname)<<endl;
	cout<<"sizeof(temp_name)=="<<sizeof(temp_name)<<endl;
	memset(uname, '\0', sizeof(uname));//为指针变量分配的字节长度为4
	//memset(user_name, '\0', sizeof(user_name));
	memset(temp_name, '\0', sizeof(temp_name));
	sprintf(temp_name, "%s", "My name is lijha.");
	//strcpy(uname, temp_name); //比较此行和下一行的导致运行结果的不同
	strncpy(uname, temp_name, 10);
	//strcpy(uname2, temp_name);//编译通过，运行报错，未给uname2分配内存空间，不能赋值
	cout<<"uname=="<<uname<<endl;
	cout<<"user_name=="<<user_name<<endl;
	cout<<"temp_name=="<<temp_name<<endl;

	char temp_chars[20]="$I love CHINA.~go~";
	char *icharpos=NULL;
	char *istrpos=NULL;
	char ichar = 'C';
	char istr[10] = "CHINA";//char *istr = "CHINA"; 都可以
	icharpos = strchr(temp_chars, ichar);
	istrpos = strstr(temp_chars, istr);
	if(icharpos)
	{
		cout<<"icharpos=="<<icharpos<<endl;
		cout<<"temp_chars=="<<temp_chars<<endl;
	}
	else
		cout<<"Not Found ichar"<<endl;

	if(istrpos)
		cout<<"istrpos=="<<istrpos<<endl;
	else
		cout<<"Not Found istr"<<endl;

	char tempstrs[255] = "Beijing best # welcome 2008 come123On #love=china!";
	char ist0[15] = "";
	char ist1[15] = "";
	char ist2[15] = "";
	int ist3 = 0;
	char ist4[15] = "";
	/*%[^#]:读取字符串，一直到出现“＃”号为止
	 *%*s:忽略中间的字符
	 *%5[1-9a-z]:最多读入5个字符，全部是小写字母或1-9的数字
	 *#love=%s:按此格式匹配出对应的值
	 */
	int isucc = sscanf(tempstrs, "%[^#] %s %*s %d %5[1-9a-z] %*s #love=%s", ist1, ist2, &ist3, ist0, ist4);
	cout<<"isucc=="<<isucc<<endl;
	cout<<"ist0=="<<ist0<<", ist1=="<<ist1<<", ist2=="<<ist2<<", ist3=="<<ist3<<", ist4=="<<ist4<<endl;
	//Output:ist0==come1, ist1==Beijing best , ist2==#, ist3==2008, ist4==china!

	char isrc1[10]="Beijing";
	char isrc2[10]="beijing";
	int ret_icmp = stricmp(isrc1,isrc2);
	int ret_cmp = strcmp(isrc1,isrc2);
	cout<<"ret_icmp=="<<ret_icmp<<endl;//ret_icmp==0
	cout<<"ret_cmp=="<<ret_cmp<<endl;//ret_cmp==-1

	//alloca函数,内存分配函数,与malloc,calloc,realloc类似. 但是注意一个重要的区别,_alloca是在栈(stack)上申请空间,用完马上就释放. 包含在头文件malloc.h中. 在某些系统中会宏定义成_alloca使用
	const char *lablestr="a,b";
	char *tar = (char *)alloca(strlen(lablestr)+1);
	strcpy(tar,lablestr);
	char *slable=tar;
	printf("1---slable==%s---\n", slable);
	while(1)
	{
		char* st=strchr(slable, ',');
		if(st!=NULL){
			char* sn=st+1;
			*st=0;//将逗号改为0，所以slable=a
			printf("2---slable==%s---\n", slable);//a
			slable=sn;//将sn赋给slable，所以slable=b
		}else{
			printf("3---slable==%s---\n", slable);//b
			break;
		}
	}

	//string 常引用
	string strTemp = "I love china...";
	string strTemp2 = "999";
	TestTemp9(strTemp,strTemp2);

	cout<<"...out TestTemp2..."<<endl;

	return 0;
}


int TestTemp3()
{
	cout<<"...int TestTemp3..."<<endl;

	//char *name="abc123";
	char nam[10]="china99";
	string nastr=nam;
	cout<<"nastr=="<<nastr<<",length=="<<nastr.length()<<",size=="<<nastr.size()<<endl;
	string cha = "c";
	if(cha < "a" || cha > "k")
	{
		cout<<"...cha does not in a~k..."<<endl;
	}
	else
		cout<<"...cha ok..."<<endl;
	string ia = "123";
	int n = atoi(ia.c_str());
	printf("n==%d\n", n);

	char stemp[20];
	char suffix[2];

	for(long itemp=10000;itemp<10013;itemp++)
	{
		memset(suffix, '\0', sizeof(suffix));
		memset(stemp, '\0', sizeof(stemp));
		sprintf(stemp, "%ld", itemp);
		if(strlen(stemp)<2)
			sprintf(suffix, "%s", "00");
		else
			sprintf(suffix, "%s", stemp+strlen(stemp)-2);
		cout<<"suffix=="<<suffix<<", stemp=="<<stemp<<", itemp=="<<itemp<<endl;
	}

	char a='a',b='b',c='c',d='d',x='x',y='y',z='z';
	char aa[60]="china";
	char st2[3]="";
	char e='e',f='f',g='g';
	strcpy(st2, "love");//使用了申请之后的内存
	cout<<"st2="<<st2<<endl;
	cout<<"aa="<<aa<<endl;
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
	cout<<"c="<<c<<endl;
	cout<<"d="<<d<<endl;
	cout<<"e="<<e<<endl;
	cout<<"f="<<f<<endl;
	cout<<"g="<<g<<endl;
	cout<<"x="<<x<<endl;
	cout<<"y="<<y<<endl;
	cout<<"z="<<z<<endl;

	//string s2 = NULL;  编译通过，但是运行抛出异常：basic_string::_S_construct NULL not valid
	//c++不允许用null来初始化string或者给string赋null,在 C++中，为一个变量赋NULL,那代表这个变量是指针
	//const char *p = NULL p是一个char*变量
	//const char *p = "adbc"; p是一个指向c风格的字符串指针
	//std::string 的构造函数需要的是一个 c 风格的字符串指针(要求以字符 null 结尾),
	//而不是一个char *的变量. 所以运行时出了上述错误
	string s2;
	//s2 = p;
	if(s2.empty())
		cout<<"s2 is null"<<endl;
	else
		cout<<"s2 is:"<<s2<<endl;


	cout<<"...out TestTemp3..."<<endl;

	return 0;
}


/*STL键值对:  map<key, value>
 * 1.平衡二叉树，快速查找
 */
void MapInsert(map<string, string, greater<string> > *mapStudent, string index, string name)
{
	mapStudent->insert(map<string, string>::value_type(index, name));
}

int TestMap()
{
	cout<<"...in TestMap..."<<endl;
	struct tm *CostTime;
	time_t BeginTimes = time(NULL);
	CostTime = localtime(&BeginTimes);
	cout<<"begin time is "<<CostTime->tm_hour<<":"<<CostTime->tm_min<<":"<<CostTime->tm_sec<<endl;

	char cc[10];
	const char* cc2;
	string cl="100088";
	memset(cc, '\0', sizeof(cc));
	sprintf(cc, "china 3000");
	cc2=cc;
	string sc = "I love "+ (string)cc;
	cout<<"sc=="<<sc<<", cl=="<<atol(cl.c_str())<<endl;
	cout<<"cc=="<<cc<<", cc2=="<<cc2<<endl;

	//map<string, string> mapStu;//缺省情况按key升序，即map<string,string,less<string> >mapStu
	map<string, string, greater<string> > mapStu;//按key降序排
	//map插入<key, value>
	MapInsert(&mapStu, "10085#Ichina", "zhaoa");
	MapInsert(&mapStu, "101#D_go", "hz1988");
	MapInsert(&mapStu, "1003~I_92", "hz998");
	MapInsert(&mapStu, "10012#Ulove", "wangff");
	MapInsert(&mapStu, "10045#X20120722", "zhangsan");
	MapInsert(&mapStu, "1001#I", "lijha");
	MapInsert(&mapStu, "1009#83", "love");
	//直接使用下标操作符[],如果不存在key，则新增一条数据
	mapStu["10011#sss"] = "sitech";
	mapStu["1001#I"] = "china_hz";

	//mapStu.size()返回元素个数
	cout<<"mapStu.size()=="<<mapStu.size()<<endl;

	//正向迭代器
	map<string, string,greater<string> >::iterator it;
	//逆向迭代器
	map<string, string,greater<string> >::reverse_iterator reit;
	//根据key查找value
	it = mapStu.find("1005");
	if(it != mapStu.end())
	{
		cout<<"Find..."<<it->first<<"=="<<it->second<<endl;
		//mapStu.erase(it);   //iterator erase(iterator it); 通过一个条目对象删除
		mapStu.erase("1005"); //size_type erase(const Key& key); 通过关键字删除
	}
	else
	{
		cout<<"Not Find..."<<endl;
	}
	it = mapStu.find("1009#83");
	//it = find(mapStu.begin(),mapStu.end(),"1009#83"); 编译报错
	if(it != mapStu.end())
	{
		cout<<"Find..."<<it->first<<"=="<<it->second<<endl;
		it->second = "china";
	}
	cout<<"mapStu.size()=="<<mapStu.size()<<endl;
	//清空map
	//mapStu.clear();
	//cout<<"mapStu.size()=="<<mapStu.size()<<endl;
	//判断map是否为空
	if(!mapStu.empty())
	{
		//遍历移除值为"zhangsan"的所有元素
		for(it=mapStu.begin(); it!=mapStu.end(); )
		{
			if(it->second == "zhangsan")
				mapStu.erase(it++);//it指向下一个元素，因为当前元素已经被删了
			else
				++it;
		}
		//逆向迭代器
		for(reit=mapStu.rbegin();reit!=mapStu.rend();reit++)
		{
			cout<<reit->first<<"==>"<<reit->second<<endl;
		}

		//遍历map,正向迭代器
		for(it = mapStu.begin(); it != mapStu.end(); it++)
		{
			//截取字符串
			//第1种方式：用find_first_of和substr处理
			size_t imap = it->first.find_first_of("#");
			if(imap != string::npos)
			{
				cout<<it->first<<"=="<<it->second<<", ";
				string id = it->first.substr(0, imap);
				string type = it->first.substr(imap+1, it->first.size()-(imap+1));
				cout<<"size=="<<it->first.size()<<", imap=="<<imap<<", id=="<<id<<", type=="<<type<<endl;
			}

			//第2种方式：用strtok实现
			/* 			char c[20];
			 * 			memset(c, '\0', sizeof(c));
			 * 			strcpy(c, it->first.c_str());
			 * 			char *p = strtok(c, "#");
			 * 			if(p != NULL)
			 * 			{
			 * 				cout<<it->first<<"=="<<it->second<<endl;
			 * 				char id[10], type[10];
			 * 				memset(id, '\0', sizeof(id));
			 * 				memset(type, '\0', sizeof(type));
			 * 				strcpy(id, p);
			 * 				p = strtok(NULL, "#");
			 * 				if(p != NULL)
			 * 				{
			 * 					strcpy(type, p);
			 * 				}
			 * 				cout<<"id=="<<id<<", type=="<<type<<endl;
			 * 			}
			 */
		}

	}
	//sleep(3);
	time_t EndTimes = time(NULL);
	CostTime = localtime(&EndTimes);
	cout<<"end time is "<<CostTime->tm_hour<<":"<<CostTime->tm_min<<":"<<CostTime->tm_sec<<endl;

	cout<<"Cost times=="<<EndTimes-BeginTimes<<"s"<<endl;

	cout<<"...out TestMap..."<<endl;

	return 0;
}


/*STL动态数组：vector<T> vecObj
 * 1.初始化时分配足够的空间，防止因容量不够，重新分配内存空间，导致references、pointers和iterator失效，耗时间
 * 2.主要用来查询和在尾部插入或删除数据，效率高，其他操作，如中间部分插入数据都慢
 * 3.查询时，只有at()函数会抛出异常，其他不抛异常
 * 4.当容量不够时，会重新分配一段内存空间，并且是原来的两倍空间
 */
int TestVector()
{
	cout<<"...in TestVector..."<<endl;
	try
	{
		string strArr[]={
			"CHINA","USA","RUSSIA","ENGLISH","JAPAN"
		};
		int arrSize = 0;
		string *pos = NULL;
		if(sizeof(strArr) > 0){
			cout<<"...get array size..."<<endl;
			GET_ARRAY_LEN(strArr,arrSize);
		}
		//使用标准动态库中的find函数
		pos = find(strArr, strArr+arrSize, "FRANCE");
		if(pos == strArr+arrSize)
			cout<<"not find pos"<<endl;
		else
			cout<<"find pos =="<<*pos<<endl;

		//create empty vector for string
		vector<string> vecStr;
		//reserve memory for 5 elements to avoid reallocation
		vecStr.reserve(5);
		//append some elements
		vecStr.push_back("Hello,");
		vecStr.push_back("how");
		vecStr.push_back("are");
		vecStr.push_back("you");
		vecStr.push_back("?");
		//accessing elements by at()
		for(unsigned int i=0;i<vecStr.size();i++)
			cout<<vecStr.at(i)<<" ";
		cout<<endl;
		//vector::at signals if the requested position is out of range by throwing an out_of_range exception,else not throw
		//cout<<"vecStr.at(6)=="<<vecStr.at(6)<<endl;
		//print "technical data"
		cout<<"vecStr.max_size()=="<<vecStr.max_size()<<endl;
		cout<<"vecStr.size()=="<<vecStr.size()<<endl;
		cout<<"vecStr.capacity()=="<<vecStr.capacity()<<endl;
		//swap second and fourth element
		swap(vecStr.at(1),vecStr.at(3));
		//insert "always" in the fourth element
		vector<string>::iterator it;
		it = vecStr.begin();
		vecStr.insert(it+3, "always");
		//assign "!" to the last element
		vecStr.back() = "!";
		//delete the last element
		vecStr.pop_back();
		//使用algorithm中的find函数查找
		it = find(vecStr.begin(),vecStr.end(),"are1");
		if(it != vecStr.end())
			cout<<"find it=="<<*it<<endl;
		else
			cout<<"not find it"<<endl;
		for(it=vecStr.begin();it!=vecStr.end();it++)
			cout<<*it<<" ";
		cout<<endl;
		//print "technical data"
		cout<<"vecStr.max_size()=="<<vecStr.max_size()<<endl;
		cout<<"vecStr.size()=="<<vecStr.size()<<endl;
		cout<<"vecStr.capacity()=="<<vecStr.capacity()<<endl;
	}catch(const exception& e)
	{
		cout<<"Error..."<<e.what()<<endl;
	}

	cout<<"...out TestVector..."<<endl;
	return 0;
}


/*STL双向链表：list
 * 1.list主要用于随机位置插入和删除，效率高，而随机查询则效率低。
 */
int TestList()
{
	cout<<"...in TestList..."<<endl;

	list<int> list1,list2;
	for(int i=0;i<6;i++)
	{
		//尾部插入
		list1.push_back(i);
		//头部插入
		list2.push_front(i);
	}
	//遍历
	list<int>::iterator it;
	PrintList(list1,list2);
	//splice：将一个list2插入到另一个list1指定位置的前面，list2内的指针就指向了list1，list2本身数据就移走了
	it = list1.begin();
	++it;//it指向list1中的1
	list1.splice(it,list2);
	PrintList(list1,list2);
	list2.splice(list2.end(), list1, list1.begin());
	PrintList(list1,list2);
	list2 = list1;
	list2.sort();//排序，默认按照升序
	list1.unique();//排序前，踢重
	PrintList(list1,list2);
	list1.sort();
	list1.unique();//排序后，踢重
	PrintList(list1,list2);
	list1.merge(list2);//排序后的list1和list2，将list2中的全部数据移入到list1
	PrintList(list1,list2);
	list1.remove(4);//移除值为4的所有元素
	PrintList(list1,list2);
	it = list1.begin();
	++it;
	list1.erase(it);//删除it位置的元素，返回下一个元素的位置
	PrintList(list1,list2);
	cout<<"...out TestList..."<<endl;
	return 0;
}


int PrintList(list<int> &ls1, list<int> &ls2)
{
	list<int>::iterator it;
	cout<<"list1:";
	for(it=ls1.begin();it!=ls1.end();it++)
		cout<<*it<<",";
	cout<<endl;
	cout<<"list2:";
	for(it=ls2.begin();it!=ls2.end();it++)
		cout<<*it<<",";
	cout<<endl;
	return 0;
}


/*STL双端队列：deque
 * 1.与vector相似，主要用于随机遍历(但效率没有vector好)，尾部插入和删除，效率高
 * 2.与vector更优的是，头部也放开，也可进行插入和删除，效率高
 * 3.元素的插入和删除或导致内存重新分配，references、pointers和iterators失效，只有在头部或尾部插入元素，references、pointers不会失效，但是iterators还是会失效
 以下情形，最好采用deque：
 1)需要在两端插入和删除元素。
 2)无需引用容器内的元素。
 3)要求容器释放不再使用的元素。
 */
int TestDeque()
{
	cout<<"...in TestDeque..."<<endl;

	deque<string> deqStr(3,"love");
	//deqStr.assign(3, "you"); 会将原有数据覆盖
	deqStr.pop_front();//删除头
	deqStr.pop_back();//删除尾
	deqStr.push_front("I");//头部插入
	deqStr.push_back("you");//尾部插入
	deqStr.resize(5, "10000");//将元素个数修改为5，新增元素的值为"10000"
	deqStr.at(4)="years";//at()越界会抛异常，其他不抛
	deque<string>::iterator it;
	for(it=deqStr.begin();it!=deqStr.end();it++)
		cout<<*it<<" ";
	cout<<endl;

	cout<<"...out TestDeque..."<<endl;
	return 0;
}


/*STL集合：set和multiset
 * 1.支持快速查找
 * 平衡二叉树存储数据
 */
int TestSet()
{
	cout<<"...in TestSet..."<<endl;

	//按照升序排列
	typedef multiset<int, less<int> > IntSet;//> >之间要有空格，否则被解析成为位移动符
	IntSet intSet1;
	intSet1.insert(5);
	intSet1.insert(3);
	intSet1.insert(2);
	intSet1.insert(7);
	intSet1.insert(5);
	intSet1.insert(8);
	intSet1.insert(1);

	/* 	//multiset不会返回pair，只有set会，因为multiset肯定可以插入重复数据
	 * 	pair<IntSet::iterator, bool> status = intSet1.insert(6);
	 * 	if(status.second)
	 * 		cout<<"...insert the "<<*(status.first)<<" element success..."<<endl;
	 * 	else
	 * 		cout<<"...insert the "<<*(status.first)<<" element error...it does already exists..."<<endl;
	 */
	intSet1.insert(8);
	IntSet::iterator it;
	for(it=intSet1.begin();it!=intSet1.end();it++)
		cout<<*it<<" ";
	cout<<endl;

	IntSet intSet2(intSet1.begin(), intSet1.end());
	//删除所有值为5的元素，返回删除的个数
	int num = intSet2.erase(5);
	cout<<"...erase.count=="<<num<<endl;
	//删除值为8的第一个元素，无返回值
	it = intSet2.find(8);
	if(it != intSet2.end())
		intSet2.erase(it);
	//删除3之前的元素
	intSet2.erase(intSet2.begin(),intSet2.find(3));
	for(it=intSet2.begin();it!=intSet2.end();it++)
		cout<<*it<<" ";
	cout<<endl;

	typedef set<Olympicmedal, less<Olympicmedal> > Olym;
	Olym Olym2012;

	Olympicmedal o1("CHINA",50);
	Olympicmedal o2("USA", 40);
	Olympicmedal o3("RUSSIA", 45);
	Olympicmedal o4("JAPAN", 10);

	Olym2012.insert(o1);
	Olym2012.insert(o2);
	Olym2012.insert(o3);
	Olym2012.insert(o4);

	Olym::iterator itr;
	for(itr = Olym2012.begin(); itr != Olym2012.end(); itr++)
	{
		cout<<itr->country<<":"<<itr->medalnum<<endl;
	}

	cout<<"...out TestSet..."<<endl;
	return 0;
}

int TestTemp9(const string &str1, string &str2)
{
	cout<<"...in TestTemp9..."<<endl;

	char s1[22];
	char s2[20];
	memset(s1, '\0', sizeof(s1));
	memset(s2, '\0', sizeof(s2));

	strcpy(s1, str1.c_str());
	strcpy(s2, str2.c_str());

	cout<<"s1=="<<s1<<endl;
	cout<<"s2=="<<s2<<endl;

	string xml_buffer = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>";
	xml_buffer += "<SalesList><ProvinceID type=\"string\">551</ProvinceID>"
		"</SalesList>";
	cout<<"xml_buffer=="<<xml_buffer<<endl;

	char sFileTmp[5];
	for(int ifile=0;ifile<10;ifile++)
	{
		if(ifile < 10)
			sprintf(sFileTmp, "00%d", ifile);
		else if(ifile < 100)
			sprintf(sFileTmp, "0%d", ifile);
		else
			sprintf(sFileTmp, "%d", ifile);
		cout<<"sFileTmp=="<<sFileTmp<<endl;
	}

	int istr2;
	stringstream ssstr;
	ssstr<<str2;
	ssstr>>istr2;
	printf("istr2==%d\n", istr2);

	if(system(NULL))
		cout<<"--system null---"<<endl;
	/* 	int is = system("dir/b");
	 * 	cout<<"is=="<<is<<endl;
	 *
	 * 	is = system("testcppbak.exe 999");
	 * 	cout<<"is=="<<is<<endl;
	 */
	string stest="123456789";
	cout<<"stest1=="<<stest.substr(1,1)<<endl;
	cout<<"stest2=="<<stest.substr(7)<<endl;

	int strnull[]={};
	if(sizeof(strnull) == 0)
	{
		for(int i=100001;i<100003;i++)
		{
			//cout<<"strnull["<<i<<"]=="<<strnull[i]<<endl;
		}
	}

	cout<<"...in TestTemp9..."<<endl;

	return 0;
}


//功能描述:截取字符串,防止截取半个汉字的乱码情况,替代strncpy。
void split_name( char * name , char * store , unsigned len )
{
	unsigned i= 0 ;

	if ( strlen(name)<len )
	{
		strcpy( store, name );
		return ;
	}

	//从第１个字节开始判断
	while( i < len )
	{
		if ( name[i]>>7&1 && name[i+1]>>7&1 )
			i = i + 2 ;
		else
			i = i + 1 ;
	}
	i = i > len ? i-3 :i-1;
	strncpy( store , name , i+1 ); //截取前i+1位
	*(store+i+1)=0;
}

//开放定址哈希表的存储结构
int Hsize[]={11,19,29,37}; //哈希表容量递增表，一个合适的素数序列
int Hs;
//构造一个空的哈希表
int InitHashTable(HashTable *H)
{
	H->count = 0;
	H->size = 0;
	Hs = Hsize[0];
	H->elem = (ElemType*)malloc(sizeof(ElemType) * Hs);
	if(H->elem == NULL)
	{
		printf("---InitHashTable malloc memory error---\n");
		exit(-1);
	}
	//初始化元素
	for(int i=0;i<Hs;i++)
	{
		//(H->elem+i)->value 与 H->elem[i].key写法相同
		//elem相当于指向一个ElemType类型的结构体数组
		memset(H->elem[i].key, '\0', sizeof(H->elem[i].key));
		memset((H->elem+i)->value, '\0', sizeof((H->elem+i)->value));
	}
	return 1;
}

//HashTable
int TestHashTable()
{
	cout<<"...in TestHashTable..."<<endl;

	HashTable stuHash;
	InitHashTable(&stuHash);
	for(int i=0;i<Hs;i++)
	{
		printf("stuHash.elem[%d]-->key=[%s], value=[%s]\n", i, stuHash.elem[i].key, stuHash.elem[i].value);
	}

	cout<<"...out TestHashTable..."<<endl;

	return 0;
}


//C++ 缓冲区学习
int TestBuffer()
{
	cout<<"...in TestBuffer..."<<endl;

	//系统缓冲区大小为511B
	ofstream outfile("./file/f1.dat");
	for(int i=0; i<510; i++)
		outfile<<"1";
	system("PAUSE");
	outfile<<"9";
	system("PAUSE");
	outfile.close();

	//getchar
	cout<<"input: ";
	char c = getchar();				//input: abc123
	cout<<"output: "<<c<<endl;		//output: a
	system("PAUSE");
	while((c=getchar()) != '\n')	//no input
		cout<<"output2: "<<c<<endl;



	//stdin stdout
	cout<<"input: ";
	string ss1;
	for(int i=0;i<3;i++)
	{
		ss1.clear();
		cin>>ss1;	//china 2012 love
		cout<<"ss1=="<<ss1<<endl;
		fflush(stdin);	//刷新输入流,C++中使用cin.clear();cin.sync();或cin.clear();cin.ignore(1024, '\n');
		//fflush(stdout);	//刷新输出流
		//fflush(NULL);   //刷新所有
	}

	cout<<"...out TestBuffer..."<<endl;

	return 0;
}


//enum ++ 前置自增重载
Flag &operator ++ (Flag &f)
{
	int i = f;
	f = (enum Flag)(i+1);
	return f;
}
//enum ++ 后置自增重载，增加一个int形参(这里后置自增写法不大合理)
Flag &operator ++ (Flag &f, int)
{
	int i = f;
	f = (enum Flag)(i+1);
	return f;
}


//C++ Primer 第2章：变量的学习
int TestVariable()
{
	cout<<"...in TestVariable..."<<endl;

	cout<<"/*";
	cout<<"*/";
	//cout<</*"*/"*/;   error: missing terminating " character
	cout<<endl;
	cout<<"sizeof(int)=="<<sizeof(int)<<endl;
	cout<<"sizeof(short)=="<<sizeof(short)<<endl;
	cout<<"sizeof(bool)=="<<sizeof(bool)<<endl;
	cout<<"sizeof(char)=="<<sizeof(char)<<endl;
	//C++标准中，wchar_t是宽字符类型，每个wchar_t类型占2个字节，16位宽。汉字的表示就要用到wchar_t
	cout<<"sizeof(wchar_t)=="<<sizeof(wchar_t)<<endl;
	cout<<"sizeof(long)=="<<sizeof(long)<<endl;
	cout<<"sizeof(double)=="<<sizeof(double)<<endl;
	cout<<"sizeof(float)=="<<sizeof(float)<<endl;

	/* 	//locale loc("chs");
	 * 	setlocale(LC_ALL, "chs");
	 * 	//wchar_t wc = L'中';
	 * 	const wchar_t *wc = L"中文";
	 * 	//wcout.imbue(loc);
	 * 	wcout<<wc<<endl;
	 */
	unsigned short iu = -1;
	cout<<"iu=="<<iu<<endl;
	unsigned short iu2 = (-1) % 65536;
	cout<<"iu2=="<<iu2<<endl;

	/*下面的写法是合法的
	  两个相邻的仅由空格、制表符或换行符分开的字符串字面值（或宽字符串字
	  面值），可连接成一个新字符串字面值。这使得多行书写长字符串字面值变得简单
	  */
	cout<<"aaa""bbb"
		"111""222"
		"689 \
		090"
		<<"xxx\
		8		zzz"
		<<endl;
	//output: aaabbb111222689 090xxx8         zzz
	//末尾行使用反斜线\，该行行尾不能有空格，下一行不能有正常的缩进，行首的缩进被当作是空格，显示就不正常了

	//变量初始化
	string st1="abc", st11=st1+"_123"; //复制初始化
	//int a0;//warning: 'a0' may be used uninitialized in this function [-Wuninitialized]
	int a1=100;
	int a2(300);//直接初始化
	string st2("xyz");
	string st3(10, 'h');
	cout<<"st1=="<<st1
		<<", st11=="<<st11
		<<", st2=="<<st2
		<<", st3=="<<st3
		//<<", a0=="<<a0
		<<", a1=="<<a1
		<<", a2=="<<a2
		<<endl;
	//output: st1==abc, st11==abc_123, st2==xyz, st3==hhhhhhhhhh, a0==0, a1==100, a2==300

	//extern
	//extern const int ex_int;
	//extern const string ex_str;
	//	ex_int = 100;
	//	ex_str = "love china";
	//cout<<"ex_int=="<<ex_int<<endl	//ex_int==4
	//	<<"ex_str=="<<ex_str	//ex_str==d:\Workspace\space_for_study\C__Space\test_cpp_example\testcpp.exe
	//	<<endl;
	//ex_int = 100;
	//ex_str = "love china";

	//string判断首字符是否为空格
	string str_1="ss ";
	string str_2 = "LOVE CHINA";
	int k1 = 330;	//warning: unused variable 'k1' [-Wunused-variable]
	size_t foud;
	foud=str_1.find_first_of("abc");	//find_first_of(" \t");
	if(foud != string::npos)
	{
		cout<<"first character == "<<str_1[foud]<<endl;
		cout<<"first character position =="<<int(foud)<<endl;
	}
	else
	{
		cout<<"str_2=="<<str_2<<endl;	//str_2==LOVE CHINA
		cout<<"not found..."<<endl;
		cout<<"k1=="<<k1<<endl;		//k1==330
		int str_2 = 128;
		int k1 = 980;
		int k2 = k1;
		cout<<"k1=="<<k1<<", k2=="<<k2<<endl;   //k1==980, k2==980
		cout<<"str_2=="<<str_2<<endl;	//str_2==128,此时局部变量str_2屏蔽了全局变量str_2
	}

	//const引用可以初始化为右值，而非const则编译报错
	const int &c1 = 98;
	cout<<"c1=="<<c1<<", line=="<<__LINE__<<endl;

	//enum枚举类型
	//enum Flag{f1,f2,f3,f4,f5,f6}; 默认f1从0开始
	Flag f;
	for(f=f1;f<=f3;f++/*f=(Flag)(f+1)*/)	//这里需要重载++运算符
		cout<<"f"<<f<<"=="<<f<<endl;
	for(f=f4;f<=f6;++f)
		cout<<"f"<<f<<"=="<<f<<endl;

	//预定义宏
	//	__DATE__，字符串常量类型，表示当前所在源文件的编译日期，输出格式为Mmm dd yyyy（如May 27 2006）。
	//  __TIME__，字符串常量类型，表示当前所在源文件的编译日期，输出格式为hh:mm:ss（如09:11:10）。
	//  __FILE__，字符串常量类型，表示当前所在源文件名，且包含文件路径。
	//  __LINE__，整数常量类型，表示当前所在源文件中的行号。
	//  __FUNCTION__，字符串常量类型，表示当前所在函数名。
	printf("__FUNCTION__==%s, __LINE___==%d, __FILE__==%s, __DATE__==%s, __TIME__==%s\n", __FUNCTION__, __LINE__, __FILE__, __DATE__, __TIME__);

	//宏定义#与##
	int  ipr = 100, ipr2 = 200, ipr3 = 300;
	const char *spr = "tree";
	float fpr = 189.98;
	trace(ipr, d);	//printf("ipr = % d \n", ipr)
	trace(fpr, f);	//printf("fpr = % f \n", fpr)
	trace(spr, s);	//printf("spr = % s \n", spr)
	trace2();		//trace(ipr, d)
	trace2(2);		//trace(ipr2, d)
	trace2(3);		//trace(ipr3, d)

	cout<<"...out TestVariable..."<<endl;

	return 0;
}


//C++ Primer 第3章：标准库类型
int TestStl()
{
	cout<<"...in TestStl..."<<endl;

	string s1 = "work hard...";
	//各个编译器的int字节长度不一样，为保证能保存任意string长度的字符串，
	//建议使用标准库类型string::size_type
	string::size_type slen = s1.size();
	cout<<"s1=="<<s1<<endl;
	cout<<"string::size_type--->s1.size()=="<<slen<<endl;
	char lf = 10;//ASCII中10是换行LF
	//char cr = 13;//ASCII中13是回车CR
	for(string::size_type sl = 0; sl <= s1.size()-1; sl++)
	{
		//输出标点符号的字符
		if(ispunct(s1[sl]))
			cout<<"s1["<<sl<<"]=="<<s1[sl]<<lf;
		//将s1大写输出,toupper,ispunct等函数都在cctype中定义
		s1[sl] = toupper(s1[sl]);
	}
	cout<<"s1=="<<s1<<endl;

	string s2 = "xV01,I am 11,A,china2012,love99,come on,";
	size_t sfound=0, spos = 0;
	sfound = s2.find(",", spos);
	while(sfound != string::npos)
	{
		string stmp = s2.substr(spos, sfound - spos);
		cout<<"spos=="<<spos<<", sfound=="<<sfound<<", stmp=="<<stmp<<endl;
		spos = sfound + 1;
		sfound = s2.find(",", spos);
	}
	//string id = it->first.substr(0, imap);
	//string type = it->first.substr(imap+1, it->first.size()-(imap+1));
	{
		printf("++++++++++++++++++++hz test begin pd_userprc_info_his_xx changing...\n");
		string tmpSvcId("");
		string tmpUpdateType("");
		string tmpState("");
		string tmpPrcId("");
		//pcc_step1:根据统一代码表和订购关系历史表进行关联，将订购和删除的数据分别入对应map
		multimap<string, string> addPrcMap;
		multimap<string, string> delPrcMap;
		addPrcMap.insert(multimap<string, string>::value_type("BP01", "BV01,I,A,"));
		addPrcMap.insert(multimap<string, string>::value_type("BP01", "BV01,I,A,"));
		addPrcMap.insert(multimap<string, string>::value_type("BP02", "BV02,I,A,"));
		addPrcMap.insert(multimap<string, string>::value_type("BP03", "BV03,I,A,"));
		addPrcMap.insert(multimap<string, string>::value_type("BP04", "BV04,I,A,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP02", "BV02,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP02", "BV02,X,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP02", "BV02,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP02", "BV02,X,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP03", "BV03,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		delPrcMap.insert(multimap<string, string>::value_type("BP05", "BV05,D,X,"));
		//pcc_step2:将同时存在订购和退订的资费进行过滤
		printf("++++++++++++++++++++before remove duplicate addPrcMap.size==[%d], delPrcMap.size==[%d]\n", addPrcMap.size(), delPrcMap.size());
		multimap<string, string>::iterator itadd;
		multimap<string, string>::iterator itdel;
		for(itadd = addPrcMap.begin(); itadd != addPrcMap.end(); itadd++)
		{
			cout<<itadd->first<<"-->"<<itadd->second<<endl;
		}
		for(itdel = delPrcMap.begin(); itdel != delPrcMap.end(); itdel++)
		{
			cout<<itdel->first<<"-->"<<itdel->second<<endl;
		}
		if(!addPrcMap.empty() && !delPrcMap.empty())
		{
			for(itadd = addPrcMap.begin(); itadd != addPrcMap.end(); )
			{
				itdel = delPrcMap.find(itadd -> first);
				if(itdel != delPrcMap.end())
				{
					addPrcMap.erase(itadd++);
					delPrcMap.erase(itdel);
				}
				else
				{
					++itadd;
				}
			}
		}
		printf("++++++++++++++++++++after remove duplicate addPrcMap.size==[%d], delPrcMap.size==[%d]\n", addPrcMap.size(), delPrcMap.size());
		for(itadd = addPrcMap.begin(); itadd != addPrcMap.end(); itadd++)
		{
			cout<<itadd->first<<"-->"<<itadd->second<<endl;
		}
		for(itdel = delPrcMap.begin(); itdel != delPrcMap.end(); itdel++)
		{
			cout<<itdel->first<<"-->"<<itdel->second<<endl;
		}
		string tmpKey1("");
		string tmpKey2("");
		string tmpValue("");
		string stmp("");
		string stmpAct("");
		string sSvcIdVal("");
		vector<string> val(6, "");
		//pcc_step3:入CRM到服务开通附加服务临时表
		multimap<string, string>::iterator itmap;
		if(!addPrcMap.empty())
		{
			printf("--------------addPrcMap begin...\n");
			tmpValue.clear();
			stmp.clear();
			int ict = 1;
			char sct[6];
			memset(sct, '\0', sizeof(sct));
			tmpKey2.clear();
			for(itmap = addPrcMap.begin(); itmap != addPrcMap.end(); itmap++)
			{
				val.clear();
				memset(sct, '\0', sizeof(sct));
				tmpKey1 = tmpKey2;
				tmpKey2 = itmap -> first;
				tmpValue = itmap -> second;
				size_t sfound=0, spos = 0;
				sfound = tmpValue.find(",", spos);
				while(sfound != string::npos)
				{
					stmp = tmpValue.substr(spos, sfound - spos);
					//cout<<"spos=="<<spos<<", sfound=="<<sfound<<", stmp=="<<stmp<<endl;
					val.push_back(stmp);
					spos = sfound + 1;
					sfound = tmpValue.find(",", spos);
				}
				if(tmpKey1 == tmpKey2)
				{
					ict++;
				}
				else
				{
					ict = 1;
				}
				//为将相同的资费以不同的服务标识发服务开通，后面补01-99
				if(ict <= 9)
				{
					sprintf(sct, "0%d", ict);
				}
				else
				{
					sprintf(sct, "%d", ict);
				}
				sSvcIdVal = val.at(0) + sct;
				//update_type --> val.at(1) = I -->svc_act = 1;
				cout<<"tmpKey1=="<<tmpKey1<<",tmpKey2=="<<tmpKey2<<",";
				cout<<"sSvcIdVal=="<<sSvcIdVal<<",tmpUpType=="<<val.at(1)<<",tmpState=="<<val.at(2)<<endl;
			}
		}
		if(!delPrcMap.empty())
		{
			printf("--------------delPrcMap begin...\n");
			tmpValue.clear();
			stmp.clear();
			int ict = 1;
			char sct[6];
			memset(sct, '\0', sizeof(sct));
			tmpKey2.clear();
			for(itmap = delPrcMap.begin(); itmap != delPrcMap.end(); itmap++)
			{
				val.clear();
				memset(sct, '\0', sizeof(sct));
				tmpKey1 = tmpKey2;
				tmpKey2 = itmap -> first;
				tmpValue = itmap -> second;
				size_t sfound=0, spos = 0;
				sfound = tmpValue.find(",", spos);
				while(sfound != string::npos)
				{
					stmp = tmpValue.substr(spos, sfound - spos);
					//cout<<"spos=="<<spos<<", sfound=="<<sfound<<", stmp=="<<stmp<<endl;
					val.push_back(stmp);
					spos = sfound + 1;
					sfound = tmpValue.find(",", spos);
				}
				if(tmpKey1 == tmpKey2)
				{
					ict++;
				}
				else
				{
					ict = 1;
				}
				//为将相同的资费以不同的服务标识发服务开通，后面补01-99
				if(ict <= 9)
				{
					sprintf(sct, "0%d", ict);
				}
				else
				{
					sprintf(sct, "%d", ict);
				}
				sSvcIdVal = val.at(0) + sct;
				//update_type --> val.at(1) = D,X -->svc_act = 0;
				cout<<"tmpKey1=="<<tmpKey1<<",tmpKey2=="<<tmpKey2<<",";
				cout<<"sSvcIdVal=="<<sSvcIdVal<<",tmpUpType=="<<val.at(1)<<",tmpState=="<<val.at(2)<<endl;
			}
		}
		printf("++++++++++++++++++++hz test end pd_userprc_info_his_xx changing...\n");
	}
	/***end 关于下发PCC网络试点工作中业务需求_ah,根据订购信息变化发送工单 modify by hz 20121130***/

	cout<<"...out TestStl..."<<endl;

	return 0;
}

int TestStl2()
{
	cout<<"...in TestStl2..."<<endl;

	//vector<string> strVec;
	vector<string> strVec(12, "");
	cout<<"strVec.size=="<<strVec.size()<<", strVec.capacity=="<<strVec.capacity()<<", strVec.max_size=="<<strVec.max_size()<<endl;
	//vector<string> strVec(11);
	strVec.clear();
	cout<<"strVec.size=="<<strVec.size()<<", strVec.capacity=="<<strVec.capacity()<<", strVec.max_size=="<<strVec.max_size()<<endl;
	for(int i=0;i!=11;i++)
	{
		strVec.push_back("Hello");
		//cout<<"strVec.size=="<<strVec.size()<<", strVec.capacity=="<<strVec.capacity()<<", strVec.max_size=="<<strVec.max_size()<<endl;
	}
	strVec[1] = "World";
	strVec.at(2) = "Love";
	strVec.at(3) = "CHINA";
	strVec.at(4) = "come";
	strVec.at(5) = "gogo";
	strVec.at(6) = "how";
	cout<<"strVec.size=="<<strVec.size()<<", strVec.capacity=="<<strVec.capacity()<<", strVec.max_size=="<<strVec.max_size()<<endl;
	/* 	for(vector<int>::size_type j=0;j!=10;j++)
	 * 	{
	 * 		cout<<"strVec["<<j<<"] == "<<strVec[j]<<endl;
	 * 	}
	 */
	vector<string>::iterator it;
	vector<string>::const_iterator cit;//只能读取vector容器元素，cit自身的值可以改变，但不能通过*it改变其所指向元素的值
	const vector<string>::iterator iter;//iter只能是固定一个值，并且定义时需要初始化值，之后不能改变
	//iter = strVec.begin();   //error 不能改变iter本身的值
	//vector::end 最后一个元素的下一个位置; 参考http://tieba.baidu.com/f?kz=1688197575
	//Returns an iterator referring to the past-the-end element in the vector container
	for(cit = strVec.begin(); cit != strVec.end(); cit++)
	{
		cout<<"*cit == "<<*cit<<endl;
	}
	vector<string>::size_type dis = strVec.end() - strVec.begin();//the result is unsigned
	vector<string>::size_type c_dis = strVec.begin() - strVec.end();
	cout<<"dis == "<<dis<<", c_dis == "<<c_dis<<endl;
	cit = strVec.begin() + strVec.size()/2;//取中间元素的值
	cout<<"*cit_mid=="<<*cit<<endl;
	//*cit = "2013";  //error 不能改变cit所指向变量的值

	int aaa[5] = {3,6,8,9};
	for(int m=0; m<5; m++)
	{
		cout<<"aaa["<<m<<"] == "<<aaa[m]<<endl;
	}

	cout<<"...in TestStl2..."<<endl;

	return 0;
}


//3.5 bitset容器
int TestStl3()
{
	cout<<"...in TestStl3..."<<endl;

	//gb2312码转为unicode码
	char out[255];
	int rec;
	char in_utf8[50]="---终于可以输出中文了，泪奔---";
	rec = u2g(in_utf8,strlen(in_utf8),out,255);
	printf("utf-8-->gb2312, rec==[%d], out=[%s]\n",rec, out);
	//printf("gb2312-->unicode out=%s \n",out);

	//16进制数值初始化bitset
	//bitset<16> bitval1(0xffff); //1-15:1
	bitset<32> bitval1(0xffff);//1-15:1, 16-31:0
	//bitset<128> bitval1(0xffff);//1-15:1, 16-127:0
	for(size_t i=0; i!=bitval1.size(); i++)//here use "size_t"
	{
		//cout<<"bitval1["<<i<<"]=="<<bitval1[i]<<endl;
	}
	//直接输出整个bitset
	cout<<"bitval1=="<<bitval1<<endl;//00000000000000001111111111111111
	//bit to unsigned long
	cout<<"bitval1.ulong=="<<bitval1.to_ulong()<<endl;//65535
	//bit to string
	cout<<"bitval1.string=="<<bitval1.to_string()<<endl;//00000000000000001111111111111111

	//string初始化bitset
	//string 对象和 bitsets 对象之间是反向转化的：string 对象的最右边字符（即下标最大的那个字符）用来初始化 bitset 对象的低阶位（即下标为 0 的位）
	string strval("101100011");//如果用包含非0或1的字符串初始化bitset对象，它将抛出无效参数异常bitset::_M_copy_from_ptr
	bitset<16> bitval2(strval);
	for(size_t j=0; j!=bitval2.size(); j++)//here use "size_t"
	{
		//cout<<"bitval2["<<j<<"]=="<<bitval2[j]<<endl;
		cout<<bitval2[j]<<"-";
		//output: 1-1-0-0-0-1-1-0-1-0-0-0-0-0-0-0-
	}
	cout<<endl;
	//直接输出整个bitset
	cout<<"the original bitval2=="<<bitval2<<endl;
	//1~0~5~16
	cout<<"any~none~count~size=="<<bitval2.any()<<"~"<<bitval2.none()<<"~"<<bitval2.count()<<"~"<<bitval2.size()<<endl;
	//b.set(pos)
	for(size_t index=0; index!=bitval2.size(); index+=2)//here use "size_t"
	{
		bitval2.set(index);//把bitval2中在 pos 处的二进制位置为 1
	}
	cout<<"after set(pos) bitval2=="<<bitval2<<endl;//0101010101110111
	//set--1, reset--0
	bitval2.set();
	cout<<"after set bitval2=="<<bitval2<<endl;//1111111111111111
	bitval2.reset();
	cout<<"after reset bitval2=="<<bitval2<<endl;//0000000000000000

	bitset<32> bitval3(32);
	cout<<"bitval3=="<<bitval3<<endl;
	bitval3.reset();
	size_t preval1=1;
	size_t preval2=2;
	for(size_t idx=1; idx!=bitval3.size();)
	{
		if(idx==1 || idx==2 || idx == (preval1+preval2))
		{
			preval1=preval2;
			preval2=idx;
			bitval3.set(idx);
		}
		idx++;
	}
	cout<<"after deal the bitval3=="<<bitval3<<endl;

	cout<<"...out TestStl3..."<<endl;
	return 0;
}


int TestExcel()
{
	cout<<"...in TestExcel..."<<endl;

	Book* book = xlCreateBook();
	if(book)
	{
		cout<<"+++++++++++I'm coming..."<<endl;
		if(book->load("./file/example.xls"))
		{
			cout<<"+++++++++++I'm coming 2..."<<endl;
			Sheet* sheet = book->getSheet(0);
			if(sheet)
			{
				double d = sheet->readNum(0, 1);
				for(int i=0;i<10;i++)
				{
					if(!sheet->writeStr(i, 0, "Yes"))
					{
						cout<<"writeStr error..."<<i<<", message:"<<book->errorMessage()<<endl;
					}
					if(!sheet->writeNum(i, 3, d * 10))
					{
						cout<<"writeNum error..."<<i<<", message:"<<book->errorMessage()<<endl;
					}
				}
				sheet->writeNum(8, 3, d * 5);
				sheet->writeStr(3, 9, "come on");
				sheet->writeStr(6, 6, "CHINA");
			}
			if(book->save("./file/example3.xls"))
				cout << "++++++++++++File example.xls has been modified." <<endl;
		}
		else
		{
			cout<<"------------load error=="<<book->errorMessage()<<endl;
		}
		book->release();
	}

	cout<<"...out TestExcel..."<<endl;

	return 0;
}


//将数组myarray的内容复制到数组S中
void initarray(char s[],const char myarray[])
{
	unsigned i;
	for(i=0;i<strlen(myarray);i++)
	{
		s[i]=myarray[i];
	}
	s[i]='\0';
	strcat(s,"\\");
}
//递归的列出文件夹下所有的子文件夹和文件
//参数path:要进行查找的目录路径
//TestQryfolder("F:\\study");
int TestQryfolder(const char path[])
{
	//gb2312码转为unicode码
	char out[255];
	char in_utf8[50]="";

	_finddata_t FileInfo; //_finddata_t是文件信息结构体
	long Handle;
	char str1[256],str2[256];
	initarray(str1,path);
	strcat(str1,"*");
	initarray(str2,path);
	if((Handle=_findfirst(str1,&FileInfo))==-1L) //查找目录中符合条件的文件
	{
		strcpy(in_utf8, "没有找到");
		u2g(in_utf8,strlen(in_utf8),out,255);
		printf("%s\n", out);
	}
	else
	{
		//最先找到的是当前文件夹"."，所以不用处理
		while(!_findnext(Handle,&FileInfo))
		{
			//printf("%s\n",FileInfo.name);
			if((FileInfo.attrib & _A_SUBDIR)==16  && strcmp(FileInfo.name,".."))
			{
				//printf("%s是文件夹\n",FileInfo.name);
				strcat(str2,FileInfo.name);
				strcpy(in_utf8, "子文件夹：");
				u2g(in_utf8,strlen(in_utf8),out,255);
				printf("%s%s\n",out, str2);
				TestQryfolder(str2);
			}
			else if(!(FileInfo.attrib & _A_SUBDIR))
			{
				strcat(str2,FileInfo.name);
				strcpy(in_utf8, "文件：");
				u2g(in_utf8,strlen(in_utf8),out,255);
				printf("%s%s\n",out, str2);
			}
			initarray(str2,path);
		}
		_findclose(Handle);
	}

	return 0;
}


//4.2 指针
int TestPointer()
{
	cout<<"------in TestPointer------"<<endl;

	//step1:指针声明与定义
	int i1=100;
	int *p1=&i1;
	int *p2=p1;
	int **p3=&p1;
	int *p4=*p3;
	cout<<"p1=="<<p1<<", p2=="<<p2<<", *p3=="<<*p3<<", p3=="<<p3<<", p4=="<<p4<<endl;
	cout<<"*p1=="<<*p1<<", *p2=="<<*p2<<", **p3=="<<**p3<<", *p4=="<<*p4<<endl;
	cout<<"sizeof(int*)=="<<sizeof(int*)<<", sizeof(char*)=="<<sizeof(char*)<<", sizeof(char)=="<<sizeof(char)<<endl;

	//step2:通过指针变量修改指针所指向变量的值
	//void* 指针只支持几种有限的操作：与另一个指针进行比较；向函数传递void* 指针或从函数返回 void* 指针；给另一个 void* 指针赋值。
	//不允许使用 void* 指针操纵它所指向的对象, void*指针也称作通用指针
	int i2 = 42, j1 = 1024;
	int *p5 = &i2, *p6 = &j1;
	*p6 = *p5 * *p6;
	*p5 *= *p5;
	void *v1 = p5;
	int *p7 = (int*)v1;
	cout<<"i2=="<<i2<<", j1=="<<j1<<", *p7=="<<*p7<<endl;

	//setp3:野指针的成因
	//1、指针变量没有被初始化。任何指针变量刚被创建时不会自动成为NULL指针，它的默认值是随机的，它会乱指一气。
	//2、指针p被free或者delete之后，没有置为NULL，让人误以为p是个合法的指针。
	//3、指针操作超越了变量的作用范围。这种情况让人防不胜防。
	int *p8 = NULL;   //http://blog.csdn.net/tongxinxiao/article/details/8502304, NULL不一定就是地址0x0000,也有可能是0x0000-0xffff中间任何一个值
	//int *p8 = 0;
	cout<<"p8=="<<p8<<endl;//p8==0,p8中存放的是地址0，地址0x00000000~0x0000ffff中是机器的私有地址，不能读写。故cout<<*p8会导致程序崩溃
	int *p9 = (int *)0x0000ffff;
	//*p9 = 99;   //程序崩溃
	cout<<"p9=="<<p9<<endl;       //p9==0xffff
	//cout<<"*p9=="<<*p9<<endl;   //程序崩溃
	int *p10 = (int *)0x00010000;
	*p10 = 88;
	cout<<"p10=="<<p10<<", *p10=="<<*p10<<endl;  //p10==0x10000, *p10==88
	cout<<"0x00010000=="<<*(int*)(0x00010000)<<endl;//0x00010000==88
	cout<<"0x00010001=="<<*(int*)(0x00010001)<<endl;//0x00010001==-1895825408

	cout<<"------out TestPointer------"<<endl;

	return 0;
}

//转义CLOB字段特殊字符
int ChangeXmlVal(const char* varSrc, char *varDest)
{
	char varTmp[10];
	memset(varTmp, '\0', sizeof(varTmp));

	for(long j=0; ; )
	{
		if(*varSrc == '\0')
		{
			break;
		}
		else if(*varSrc == '&')
		{
			//&lt;&gt;
			memset(varTmp, '\0', sizeof(varTmp));
			strncpy(varTmp, varSrc, 4);

			if(strcmp(varTmp, "&lt;") == 0)
			{
				varDest[j++] = '<';
				varSrc = varSrc+4;
				continue;
			}
			else if(strcmp(varTmp, "&gt;") == 0)
			{
				varDest[j++] = '>';
				varSrc = varSrc+4;
				continue;
			}

			//&amp;
			memset(varTmp, '\0', sizeof(varTmp));
			strncpy(varTmp, varSrc, 5);
			if(strcmp(varTmp, "&amp;") == 0)
			{
				varDest[j++] = '&';
				varSrc = varSrc+5;
				continue;
			}

			//&quot;&apos;
			memset(varTmp, '\0', sizeof(varTmp));
			strncpy(varTmp, varSrc, 6);
			if(strcmp(varTmp, "&quot;") == 0)
			{
				varDest[j++] = '"';
				varSrc = varSrc+6;
				continue;
			}
			else if(strcmp(varTmp, "&apos;") == 0)
			{
				varDest[j++] = '\'';
				varSrc = varSrc+6;
				continue;
			}

			//default
			varDest[j++] = *varSrc;
			varSrc ++;
		}
		else
		{
			varDest[j++] = *varSrc;
			varSrc ++;
		}
	}

	return 0;
}


int changeValue(string &s, const char* src)
{
	int i=0;
	for(i=0; ; i++)
	{
		if(src[i]==0) break ;
		switch(src[i])
		{
			case '<':
				s += "&lt;";
				break;
			case '>':
				s += "&gt;";
				break;
			case '&':
				s += "&amp;";
				break;
			case '\'':
				s += "&apos;";
				break;
			case '"':
				s += "&quot;";
				break;
			default :
				s +=src[i];
		}
	}
	return i;
}


int TestTempWin()
{
	string xmlstr = "<V>&lt;?xml version=&quot;1.0&quot; encoding=&quot;GBK&quot; standalone=&quot;no&quot; ?&gt;&lt;ROOT&gt;&lt;ERR_CODE type=&quot;";
			xmlstr+="string&quot;&gt;303000010&lt;/ERR_CODE&gt;&lt;ERR_MSG type=&quot;string&quot;&gt;utGetStruct,[ORDERLINE_INFO]&lt;";
			xmlstr+="/ERR_MSG&gt;&lt;/ROOT&gt;</V>";
	char cstr[xmlstr.length() + 1];
	//char *strpos = cstr;
	char cstr2[xmlstr.length() + 1];
	char cstr3[10];

	memset(cstr, '\0', sizeof(cstr));
	memset(cstr2, '\0', sizeof(cstr2));
	memset(cstr3, '\0', sizeof(cstr3));
	strcpy(cstr, xmlstr.c_str());

	ChangeXmlVal(cstr, cstr2);

	cout<<"------cstr=="<<cstr<<endl;
	cout<<"------cstr2=="<<cstr2<<endl;

	string cstr4("");
	string cstr5(cstr2);
	changeValue(cstr4, cstr5.c_str());
	cout<<"------cstr4=="<<cstr4<<endl;

	typedef set<string, less<string> > TableSet;
	TableSet tabSet;
	tabSet.insert("abc");
	tabSet.insert("123");
	tabSet.insert("ade");
	tabSet.insert("123");
	tabSet.insert("010");
	set<string>::iterator ist;
	for(ist=tabSet.begin(); ist!=tabSet.end(); ist++)
	{
		cout<<"----*ist=="<<*ist<<endl;
	}
	cout<<"----tabSet.size()=="<<tabSet.size()<<endl;
	ist=tabSet.find("012");
	if(ist!=tabSet.end())
		cout<<"----find---"<<*ist<<endl;
	else
		cout<<"----not find it"<<endl;

	long lTimeYM = 201305;
	char sTimeYM[9+1];
	memset(sTimeYM, '\0', sizeof(sTimeYM));
	snprintf(sTimeYM, 9, "%ld", lTimeYM);
	cout<<"----sTimeYM=="<<sTimeYM<<endl;

	char all_suffix[30];
	cout<<"----all_suffix=="<<all_suffix<<endl;
	all_suffix[0] = '\0';
	const char *sOrderId = "L120305283823289369";
	const char *sord = sOrderId + (strlen(sOrderId) - 2);
	int iord = atoi(sord);
	sprintf(all_suffix, "%02d", iord%100);
	cout<<"----all_suffix=="<<all_suffix<<endl;

	int rule=10;
	switch(rule)
	{
		case 1:
			cout<<"----1"<<endl;
			break;
		case 9:
			cout<<"----9"<<endl;
			break;
		case 10:
			cout<<"----10"<<endl;
			break;
	}
	char temp_table_name[35]={""};
	char temp_table_tail[35]={""};
	char tableName[35]={"or_ordfnsh_$"};
	if(strchr(tableName, '$') != NULL)
	{
		char *tabpos = strchr(tableName, '$');
		strcpy(temp_table_tail, tabpos+1);
		cout<<"----temp_table_tail==["<<temp_table_tail<<"]"<<endl;
		*tabpos = '\0';
		snprintf(temp_table_name, 35, "%s%s%s", tableName, all_suffix, temp_table_tail);
		cout<<"----temp_table_name=="<<temp_table_name<<endl;
	}
	else
	{
		cout<<"------no suffix $"<<endl;
	}
	string tabXml("");
//	tabXml += (string)123;
//	tabXml += temp_table_name;
	cout<<"------tabXml=="<<tabXml<<endl;

	return 0;
}


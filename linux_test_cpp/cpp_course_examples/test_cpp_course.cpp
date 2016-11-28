/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_course.cpp
 *
 *    Description:  c++ 程序设计（第2版） 谭浩强主编  案例学习
 *
 *        Version:  1.0
 *        Created:  2012/5/6 19:58:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */
#include "test_cpp_main.h"
#include "test_cpp_course.h"
#include <vector>
#include <map>
/*
 *案例学习 P424 例13.2
 *用流对象的成员函数控制输出数据格式
 *
 *流成员函数 <------> 控制符函数
 *unsetf     <------> resetiosflags  终止对应的输出格式状态
 *setf       <------> setiosflags    设置新的输出格式状态
 *width(n)   <------> setw(n)        设置字符宽度为n位
 *fill(c)    <------> setfill(c)     设置填充字符c
 *precision(n)<------> setprecision(n) 设置实数的精度为n位
 */
int TestCourse132()
{
    cout<<"...in TestCourse132..."<<endl;

    int a=21;
    cout.setf(ios::showbase);
    cout<<"dec.a=="<<a<<endl;//默认以10进制形式输出
    cout.unsetf(ios::dec);//先要终止已设置的输出格式状态，即终止10进制输出
    cout.setf(ios::hex);//重新设置为16进制形式输出
    cout<<"hex.a=="<<a<<endl;
    //使用控制符函数  需要加入iomanip头文件
    cout<<resetiosflags(ios::hex)<<setiosflags(ios::oct)<<"oct.a=="<<a<<endl;//先终止16进制，再设置8进制

    /*  char *pch = NULL;
     *  pch = "I love China!";
     *  cout.width(20);
     *  cout<<pch<<endl; //       I love China!
     *  cout.width(20);
     *  cout.fill('*');  *******I love China!
     *  cout<<pch<<endl;
     *  cout<<pch<<endl; //I love China!   从三个输出结果：width/fill只对cout输出后的第一项有效
     */
    double pi=22.0/7.0;
    cout.setf(ios::scientific);
    cout<<"pi=";
    cout.width(14);
    cout<<pi<<endl;
    cout<<resetiosflags(ios::scientific)<<setiosflags(ios::fixed)<<setw(12)<<setiosflags(ios::showpos|ios::internal)<<setprecision(6)<<pi<<endl;//setf函数设置格式状态时，对于多个格式，可以使用|隔开即可

    cout<<"...out TestCourse132..."<<endl;

    return 0;
}

/*
 *案例学习 P427-P432 例13.3-13.7
 *用流成员函数put/putchar/get/peek/putback/ignore等
 *
 *1. put():流对象成员函数输出单个字符；
 *   putchar()也可以实现，但putchar()不是流对象成员函数，c语言中定义在stdio.h中，c++定义在iostream.
 *2. get():输入流中提取一个字符;
 *   get(char ch):输入流中提取一个字符,赋值给字符变量ch;
 *   get(char *ch, n, 'x'):从输入流中读取n-1个字符，赋给指定的字符数组（或字符指针）,
 *                     如果在读取n-1个字符之前遇到指定的终止字符x *，则提前结束读取;
 *   getline(char *ch, n, 'x'):读入一行字符(长度n-1)，放到字符指针ch中.
 *3. eof():文件结束符判断，从输入流中读取数据，如果到达文件末尾，eof函数值非0，否则为0.
 *4. peek():观测下一个字符，指针停留在当前位置不变，如果访问的是文件结束符，则返回EOF(-1)，一般以Ctrl+Z或Ctrl+D表示文件结束符.
 *5. putback(char ch):将字符ch插入到输入流当前指针位置，以供后面读取.
 *6. ignore(n,'x'):跳过输入流中的n个字符，或遇到字符x不再跳了.如果不带参数，即ignore(),相当于ignore(1,EOF).
 */
int TestCourse133()
{
    cout<<"...in TestCourse133..."<<endl;

    int cnum=0;
    char c;//int c=0;  使用char或int定义c都可以，以ascii码进行运算
    cout<<"please enter a sentence: ";
    while(!cin.eof())//while((c = cin.get()) != EOF)  EOF是在iostream头文件中定义的符号常量，代表-1
    {
        if((c=cin.get())!=' ')
        {
            ++cnum;
            putchar(c);  //cout.put(c);  使用putchar函数或使用cout.put()都可以
            if(cnum>3) break;
        }

    }
    cout<<endl;

    char ch[20];
    char ch_next=' ';
    memset(ch, '\0',sizeof(ch));
    cout<<"please enter a senterce again: "; //输入：abc123090/8jh999/defxyz/*I love China!/
    cin.getline(ch,15,'/');
    cout<<"ch=="<<ch<<endl; //输出：abc123090，指针停留在/处后面,8的前面
    if(cin)   //测试cin流的状态，如果为0则表示出错，无法提取数据，否则为非0
        cout<<"~~~cin ok~~~"<<endl;
    else
        cout<<"~~~cin error~~~"<<endl;
    ch_next=cin.peek();
    cout<<"peek.ch_next=="<<ch_next<<endl;//输出：8
    cin.putback('6');
    memset(ch, '\0', sizeof(ch));
    cin.getline(ch,15,'/');
    cout<<"putback.ch=="<<ch<<endl;//输出：68jh999
    cin.ignore(8,'/'); //跳过8个字符，提前遇到/也结束
    cin.ignore();  //相当于ignore(1,EOF)
    memset(ch, '\0', sizeof(ch));
    cin.get(ch, 15, '/');
    cout<<"ignore.ch=="<<ch<<endl;//输出：I love China!

    cout<<"...out TestCourse133..."<<endl;

    return 0;
}

/*案例学习  P437-P439  例13.8-13.9
 *ASCII文件输入输出,数值输入输出
 *
 *1.打开磁盘文件  ofstream testfile("f1.dat",ios::out);或者使用open函数，即ofstream testfile;testfile.open("f1.dat",ios::out);
 *2.如果打开文件失败，那么open返回假(0);也可以直接用testfile进行判断,即if(!testfile) 则"open error";
 */
int TestCourse138()
{
    cout<<"...in TestCourse138..."<<endl;

    //输出10个数到f1.dat
    ofstream outfile;//可以不需要使用open，直接ofstream outfile("./file/f1.dat",ios::app);  ios::out覆盖输出,ios::app追加输出
    outfile.open("./file/f8.dat",ios::app);
    if(!outfile)
    {
        cout<<"...outfile open f1.dat error..."<<endl;
        exit(-1);
    }
    cout<<"please enter 10 numbers: ";
    int innum[50];
    int knum=0;
    memset(innum, 0, sizeof(innum));
    int i = 0;
    for(i=0;i<10;i++)
    {
        cin>>knum;
        outfile<<knum<<endl;//outfile<<knum<<' '也是可以的,数据移空格隔开
    }
    outfile.close();
    //取出文件中的所有数，然后找出最大的数及其位置
    ifstream infile("./file/f1.dat",ios::in);
    if(!infile)
    {
        cout<<"...infile open f1.dat error..."<<endl;
        exit(-1);
    }
    memset(innum,0,sizeof(innum));
    cout<<"The numbers are: ";
    int j=0;
    while(!infile.eof()) //判断是否到了文件结尾
    {
        infile>>innum[j];//最后的换行也输出了，怎么判断？
        cout<<innum[j]<<' ';
        j++;
    }
    cout<<endl;
    infile.close();
    int max=innum[0];
    int order=0;
    for(i=1;i<50;i++)
    {
        if(max<innum[i])
        {
            max=innum[i];
            order=i;
        }
    }
    cout<<"The max num is: "<<max<<", its order is: "<<order<<endl;

    cout<<"...out TestCourse138..."<<endl;
    return 0;
}


/*案例学习  P439-P440  例13.10
 *ASCII文件输入输出
 *字符输入输出测试
 *
 */
int TestCourse1310()
{
    cout<<"...in TestCourse1310..."<<endl;

    char infile_name[20]="./file/f2.dat";
    char outfile_name[20]="./file/f3.dat";

    //输出到磁盘文件
    SaveToFile(infile_name);
    //从磁盘文件输入
    GetFromFile(infile_name,outfile_name);
    cout<<"...out TestCourse1310..."<<endl;

    return 0;
}

/*
 *从键盘读入一行字符并将其中的字母存入磁盘文件f2.dat
 */
int SaveToFile(char *infile_name)
{
    cout<<"...in SaveToFile..."<<endl;

    ofstream outfile(infile_name,ios::out); //默认方式为ios::out
    if(!outfile)
    {
        cout<<"...outfile "<<infile_name<<" open error..."<<endl;
        exit(-1);
    }
    char kch[80];
    cout<<"Please input a sentence: ";
    memset(kch,'\0',sizeof(kch));
    for(int j=0;j<5;j++)
    {
        cin.getline(kch,30,'/'); //输入：I/love/china/and/study./;也可以用cin>>kch;实现,将/换成回车
        for(int i=0;kch[i]!=0;i++) //截止到'\0'
        {
            //如果是字母则输出到文件
            if((kch[i]>=65 && kch[i]<=90) || (kch[i]>=97 && kch[i]<=122))
            {
                outfile.put(kch[i]);//put函数，将一个字符输出到f2.dat
            }
        }
        outfile<<endl;
    }
    outfile.close();
    cout<<"...out SaveToFile..."<<endl;

    return 0;
}


/*
 *1. 从f2.dat中读入字母字符，再将其中的小写字母改为大写字母，再存入f3.dat
 *2. 删除文件:int retval = unlink(filename);成功返回0，失败返回-1
 *   unlink的功能是当该文件沒有被其它任何文件链接，並且沒有进程在访问该文件的情況下，才将文件真正的刪除
 */
int GetFromFile(char *infile_name, char *outfile_name)
{
    cout<<"...in GetFromFile..."<<endl;

    ifstream infile(infile_name);//默认为ios::in
    if(!infile)
    {
        cout<<"...infile "<<infile_name<<" open error..."<<endl;
        exit(-1);
    }
    ofstream outfile(outfile_name);
    if(!outfile)
    {
        cout<<"...outfile "<<outfile_name<<" open error..."<<endl;
        exit(-1);
    }
    char ch='\0';
    cout<<"The sentence in "<<outfile_name<<": ";
    while(infile.get(ch))  //get函数，每次读入一个字符进行判断
    {
        if(ch>=97 && ch<=122)
        {
            ch=ch-32;
        }
        outfile.put(ch);
        cout.put(ch);
    }
    outfile.close();
    infile.close();

    //删除原始文件f2.dat
    int linkval = unlink(infile_name);
    if(linkval == 0)
        cout<<"unlink the  "<<infile_name<<" success..."<<endl;
    else
        cout<<"linkval=="<<linkval<<", unlink the "<<infile_name<<" error..."<<endl;


    cout<<"...out GetFromFile..."<<endl;

    return 0;
}


/*案例学习  P446  例13.13
 *二进制文件输入输出
 *   1. 使用read函数，从二进制文件中读入到缓存中
 *   2. 使用write函数，从缓存中写入到二进制文件中
 *   3. 结构体变量定义及结构体指针变量的使用
 *   4. 使用malloc(free)与new(delete)的区别:尽量用new(delete)
 *      free(p)或delete p之后，加上一个p=NULL,防止出现野指针
 */
int TestCourse1313()
{
    cout<<"...in TestCourse1313..."<<endl;

    Student stu1[5] =
        {
            {1001,"Zhaoa",98.5,80,NULL},
            {1002,"Qianb",78.5,50,NULL},
            {1003,"Sunc",82.3,100,NULL},
            {1004,"Lid",66.25,55,NULL},
            {1005,"Zhoue",58.0,72,NULL}
        };
    fstream iofile("./file/stu.dat",ios::out|ios::binary|ios::in);
    if(!iofile)  //同时指定了ios::in和ios::out,而stu.dat文件不存在的话，会打开文件失败，待确认是否为编译器问题？
    {
        cerr<<"...open stud.dat error..."<<endl;
        exit(-1);//abort();终止程序，注意与return/exit的区别:http://blog.csdn.net/wjscl520/article/details/6115450,用return是好习惯.
    }
    iofile.write((char *)&stu1[0],sizeof(stu1));//write(char * buffer,int len),buffer为指向内存里面的一段空间，len为字节数

    Student stu2[5];
    memset(stu2, '\0', sizeof(stu2));//sizeof(stu2)=180
    int i = 0;
    for(i=0; i<5; i=i+2)
    {
        iofile.seekg(i*sizeof(stu2[i]), ios::beg);//seekg(位移量, 参照位置) 以参照位置为基础移动若干字节 用于输入 g代表get
        iofile.read((char *)&stu2[i/2], sizeof(stu2[i/2]));//read(char *buffer, int len) 参数同write函数
        cout<<"stu2["<<i/2<<"].stu_id=="<<stu2[i/2].stu_id<<
            ", stu2["<<i/2<<"].stu_name=="<<stu2[i/2].stu_name<<
            ", stu2["<<i/2<<"].stu_score=="<<stu2[i/2].stu_score<<
            ", stu2["<<i/2<<"].stu_count=="<<stu2[i/2].stu_count<<
            ", stu2["<<i/2<<"].stu_next=="<<stu2[i/2].next<<endl;
    }

    stu1[2].stu_score = 96.5;
    stu1[2].stu_count = 90;
    strcpy(stu1[2].stu_name, "wangff");
    iofile.seekp(2*sizeof(stu1[0]), ios::beg);//seekp(位移量, 参照位置) 用于输出p代表put
    iofile.write((char *)&stu1[2], sizeof(stu1[2]));

    iofile.seekg(0, ios::beg);
    for(i=0; i<5; i++)
    {
        iofile.read((char *)&stu1[i], sizeof(stu1[i]));
    }
    iofile.close();

    Student *stu1pos = stu1;//stu1为结构体指针数组的数组名，代表结构体指针数组的首地址，也就是stu1[0]的起始地址
    stu1[0].next = &stu1[1];//stu1[i]为结构体指针数组的成员，即结构体变量
    stu1[1].next = &stu1[2];
    stu1[2].next = &stu1[3];
    stu1[3].next = &stu1[4];
    stu1[4].next = NULL;
    do
    {
        cout<<stu1pos->stu_id<<", "<<stu1pos->stu_name<<", "<<stu1pos->stu_score<<", "<<stu1pos->stu_count<<endl;
    }while((stu1pos = stu1pos->next) != NULL);

    //printStu(stu1[0]);//结构体引用传参，结构体变量,其实传送过去的是地址，传址方式
    printStuPoint(&stu1[0]);//函数指针传参，传的是地址的值，传值方式

    //Student *ps = (Student *)malloc(sizeof(Student)*5); malloc分配内存空间
    Student *ps = new Student[5];//new分配内存空间
    memset(ps, '\0', sizeof(Student)*5);//sizeof(ps)==4,故初始化长度为sizeof(Student)*5
    if(NULL == ps)
    {
        cerr<<"malloc Student error!"<<endl;
        return -1;
    }

    for(int j=0; j<5; j++)
    {
        (ps+j)->stu_id = stu1[j].stu_id;
        strcpy((ps+j)->stu_name,stu1[j].stu_name);
        (ps+j)->stu_score = stu1[j].stu_score;
        (ps+j)->stu_count = stu1[j].stu_count;
        (ps+j)->next = stu1[j].next;
    }
    for(; ps!=NULL; ps=ps->next)
    {
        cout<<ps->stu_id<<", "<<ps->stu_name<<", "<<ps->stu_score<<", "<<ps->stu_count<<endl;
    }
    //free(ps);//对应malloc，如果前面未使用malloc，这里用free释放，则会报错
    delete [] ps;//对应new，加[]是释放数组的内存，不是数组则不需要[]
    ps = NULL;//目的是防止出现野指针

    cout<<"...out TestCourse1313..."<<endl;

    return 0;
}


/*
 *利用函数引用传递参数，输出结构体数据
 *知识点:
 *  1.虚实结合时，实参的地址传送给形参，prtstu与stu1[0]指向的是同一段内存空间
 *  2.引用传值为"传址方式"，指针变量和结构体变量传值为"传值方式"
 *  3.结构体变量作为形参和实参，都需要开辟内存空间，开销大，效率不高，但程序比较直观;
 *    指针变量作为形参，形参需要开辟4个字节大小的内存空间，效率较高;
 *    Student变量的引用作为形参，不需要开辟内存空间，效率较高，并且程序比较直观.
 */
int printStu(Student &prtstu)
{
    cout<<"prtstu.stu_id=="<<prtstu.stu_id<<
        ", prtstu.stu_name=="<<prtstu.stu_name<<
        ", prtstu.stu_score=="<<prtstu.stu_score<<
        ", prtstu.stu_count=="<<prtstu.stu_count<<
        ", prtstu.stu_next=="<<prtstu.next<<endl;

    return 0;
}

int printStuPoint(Student *prtstu)
{
    cout<<"...in printStuPoint..."<<endl;

    int stuid = prtstu->stu_id;
    if(1001 == stuid)
    {
        Student newStud = {1066,"wangff",888.8,200,NULL};
        printStuPoint(&newStud);//循环调用
    }
    cout<<"prtstu->stu_id=="<<prtstu->stu_id<<
        ", prtstu->stu_name=="<<prtstu->stu_name<<
        ", prtstu->stu_score=="<<prtstu->stu_score<<
        ", prtstu->stu_count=="<<prtstu->stu_count<<
        ", prtstu->stu_next=="<<prtstu->next<<endl;

    cout<<"...out printStuPoint..."<<endl;

    return 0;
}


/*案例学习  P175  例6.11
 *指向函数的指针
 */
int TestCourse611()
{
    cout<<"...in TestCourse611..."<<endl;
    int (*p)();
    p = &TestCourse613;//这里去掉&也是可行的，即p = TestCourse613; C++中建议加上&
    (*p)();        //上一行若去掉&，则该行去掉*,即p()
    cout<<"...in TestCourse611..."<<endl;

    return 0;
}


/*案例学习  P180  例6.13
 *指针数组、指针的指针和二维数组
 */
int TestCourse613()
{
    cout<<"...in TestCourse613..."<<endl;
    /*
      char *name[5] = {"BASIC","FORTRAN","C++","Pascal","COBOL"};
      char **pname=name+2;
      cout<<"*pname=="<<*pname<<endl;
      cout<<"**pname=="<<**pname<<endl;

      char name2[5][10] = {"BASIC","FORTRAN","C++","Pascal","COBOL"};
      char *pn = name2[0];
      cout<<"pn=="<<pn<<endl;

      int numid[5]={100,200,222,999,111};
      int *pnum = numid;
      for(int i=0; i<5; i++)
      {
      cout<<"pnum=="<<pnum[i]<<endl;//<pnum[i]=*(pnum+i)
      }

      char *iname="Lijha";
      int i=0;
      do
      {
      cout<<"iname=="<<iname[i]<<endl;
      i++;
      }while(iname[i]);
    */

    cout<<"...out TestCourse613..."<<endl;

    return 0;
}


/*案例学习  P450  例13.15
 * 字符串输入输出流，知识点:
 *  1.输入流：istrstream::istrstream(char *buffer,int n); buffer为指向字符数组的首元素的地址，第2个输入流缓冲区大小参数可选
 *  2.输出流：ostrstream::ostrstream(char *buffer,int n,int mode=ios::out); buffer为指向字符数组的首元素的地址，第3个输出流模式可选，默认为ios::out.
 *  3.输入输出流：strstream::strstream(char *buffer,int n,int mode);
 */
/*
  int TestCourse1315()
  {
  cout<<"...in TestCourse1315..."<<endl;

  char chararr[50]="12 34 65 -23 -32 33 61 99 321 32";
  int numarr[10]={0};
  //输入流,从字符数组将内容输入到整型数组中
  istrstream strin(chararr,sizeof(chararr));
  for(int i=0;i<10;i++)
  {
  strin>>numarr[i];
  }
  cout<<"numarr: ";
  for(int i=0;i<10;i++)
  {
  cout<<numarr[i]<<" ";
  }
  cout<<endl;
  //将整型数组按照选择法从大到小排序
  int tempnum=0,knum=0;
  for(int i=0;i<9;i++)
  {
  knum = i;
  for(int j=i+1;j<10;j++)
  {
  if(numarr[knum] < numarr[j])
  {
  knum = j;
  }
  }
  tempnum = numarr[i];
  numarr[i] = numarr[knum];
  numarr[knum] = tempnum;
  }
  cout<<"numarr sorted: ";
  for(int i=0;i<10;i++)
  {
  cout<<numarr[i]<<" ";
  }
  cout<<endl;
  //输出流，从整型数组将内容输出到字符数组
  ostrstream strout(chararr,sizeof(chararr));
  for(int i=0;i<10;i++)
  {
  strout<<numarr[i]<<" ";
  }
  strout<<ends; //ends为C++的I/O操作符，即同'\0'
  cout<<"chararr : "<<chararr<<endl;

  cout<<"...out TestCourse1315..."<<endl;

  return 0;
  }
*/

/*案例学习  P182  例6.14
 * const指针作为形参、void指针类型
 * 知识点：
 *  1.指向常量的指针变量：const int *p = &a,那么不能通过*p(即指针变量)来改变它指向的变量的对象的值
 *  2.指向常量的指针变量常用于作函数形参，以防止指针形参所指对象的值改变影响实参
 *  3.可以将非void类的指针赋值给void型指针变量，但反过来则不行，即不能将void类型指针赋值给非void类型指针变量，必须先进行强制类型转换
 *  4.void类型不能理解为"任何的类型"，而应理解成"指向空类型"或"不指向确定的类型"
 */
int TestCourse614()
{
    cout<<"...in TestCourse614..."<<endl;

    //const指针
    int a = 10;
    FuncTest(&a);
    cout<<"a=="<<a<<endl;
    /*  //void指针
     *  int *p1=&a;
     *  char *p2="new";
     *  void *p3;
     *  p3=p1;
     *  //cout<<"*p3=="<<*p3<<endl;编译报错：'void*' is not a pointer-to-object type p3指向不确定类型的变量
     *  cout<<"*(int *)p3=="<<*(int *)p3<<endl;//把p3的值转换为(int *)型，可以指向变量a
     *  p2=(char *)p3;//将p3的值转换为char *型，再赋值给p2
     *  printf("*p2==%d\n",*p2);*p2=10 这里为何是%d
     *  cout<<"*p2=="<<*p2<<endl;*p2=  输出空
     *
     */

    cout<<"...out TestCourse614..."<<endl;

    return 0;
}


int FuncTest(const int *pt)
{
    cout<<"...in FuncTest..."<<endl;

    //*pt = *pt *5;  //编译报错： error: assignment of read-only location '* pt',也就是说不能改变*pt的值，只能使用
    int b =0;
    b = *pt * 5;
    cout<<"b=="<<b<<endl;

    cout<<"...out FuncTest..."<<endl;

    return 0;
}


/*案例学习  P250/P324  例8.3/例10.6
 * 类基本操作
 * 知识点：
 *  1.声明定义类和成员函数
 *  2.区分什么场合使用域运算符::,什么场合使用成员运算符.
 *  3.单目运算符重载
 */
int TestCourse83()
{
    cout<<"...in TestCourse83..."<<endl;

    Time t1;
    //t1.SetTime();
    cout<<"++t1==";
    ++t1;
    t1.GetTime();

    Time t2(22,59,53);
    //t2.SetTime();
    for(int i=0;i<10;i++)
    {
        ++t2;
        cout<<"++t2==";
        t2.GetTime();
    }
    t1 = t2++;
    cout<<"t1==";
    t1.GetTime();
    cout<<"t2==";
    t2.GetTime();

    Time t3;
    for(int i=0;i<10;i++)
    {
        --t3;
        cout<<"--t3==";
        t3.GetTime();
    }
    Time t4 = t3--;
    cout<<"t4==";
    t4.GetTime();
    cout<<"t3==";
    t3.GetTime();

    cout<<"...out TestCourse83..."<<endl;

    return 0;
}

//默认构造函数
Time::Time()
{
    this->hour = 0;
    this->min = 0;
    this->sec = 0;
}

//带参构造函数
Time::Time(int h,int m,int s)
{
    this->hour = h;
    this->min = m;
    this->sec = s;
}

//前置自增++
void Time::operator ++()
{
    if(++this->sec >= 60)
    {
        this->sec = this->sec - 60;
        if(++this->min >= 60)
        {
            this->min = this->min - 60;
            if(++this->hour >=24)
            {
                this->hour = this->hour - 24;
            }
        }
    }
}

//后置自增++, C++约定：在自增(自减)运算符重载函数中，增加一个int型形参，就是后置自增(自减)运算符函数
Time Time::operator ++(int)
{
    Time timeTemp = *this;
    if(++this->sec >= 60)
    {
        this->sec = this->sec - 60;
        if(++this->min >= 60)
        {
            this->min = this->min - 60;
            if(++this->hour >=24)
            {
                this->hour = this->hour - 24;
            }
        }
    }

    return timeTemp;
}

//前置自减--
void Time::operator --()
{
    if(--this->sec < 0)
    {
        this->sec = this->sec + 60;
        if(--this->min < 0)
        {
            this->min = this->min + 60;
            if(--this->hour < 0)
            {
                this->hour = this->hour + 24;
            }
        }
    }
}

//后置自减--
Time Time::operator --(int)
{
    Time timeTemp(*this);
    if(--this->sec < 0)
    {
        this->sec = this->sec + 60;
        if(--this->min < 0)
        {
            this->min = this->min + 60;
            if(--this->hour < 0)
            {
                this->hour = this->hour + 24;
            }
        }
    }

    return timeTemp;
}

//类外定义函数，指明函数在哪个作用域中
int Time::SetTime()
{
    cout<<"please input hour-min-sec: ";
    cin>>hour;  //在成员函数引用本对象的数据成员时，只须直接写数据成员名，C++系统会把它默认为本对象的数据成员
    cin>>min;   //也可以显示的写出类名并使用域运算符，即Time::min
    cin>>sec;

    return 0;
}


int Time::GetTime()
{
    cout<<hour<<":"<<min<<":"<<sec<<endl;

    return 0;
}


/*案例学习  P251  例8.4
 * 找出一个整型数组中的元素最大值
 * 知识点：
 *  1.主函数做的事情: 定义对象;向各对象发出"消息",通知各对象完成有关任务
 */
int TestCourse84()
{
    cout<<"...in TestCourse84..."<<endl;

    Array_max arr;
    arr.SetValue();
    arr.MaxValue();
    Box box6("box6");
    arr.GetValue(box6);

    cout<<"...out TestCourse84"<<endl;

    return 0;
}


int Array_max::SetValue()
{
    cout<<"please input 10 numbers:"<<endl;
    for(int i=0;i<10;i++)
        cin>>array[i];

    return 0;
}


int Array_max::MaxValue()
{
    maxnum=array[0];
    for(int i=1;i<10;i++)
        if(maxnum<array[i])
            maxnum=array[i];

    return 0;
}

int Array_max::GetValue(Box &box) //友元成员函数
{
    cout<<"...GetValue..."<<box.boxname<<".length=="<<box.length<<endl;
    cout<<"maxnum=="<<maxnum<<endl;

    return 0;
}


/* 案例学习  P259,P261,P263 例9.2,9.3,9.4,9.5,9.6
 * 类的构造函数
 * 知识点：
 *  1.无参构造函数
 *  2.带参构造函数(参数初始化表)
 *  3.构造函数重载
 *  4.使用默认参数的构造函数
 *  5.调用构造函数和析构函数的顺序
 *  6.对象数组
 *  7.this指针
 */
int TestCourse92to6()
{
    cout<<"...in TestCourse92to6..."<<endl;

    Box box1; //不能写成Box box1();这样box1变成了普通函数，返回值类型为Box
    box1.Volume();
    Box box2("box2", 10, 12, 15);//初始化类对象时，先执行构造函数
    box2.Volume();
    Box box3("box3", 20,8);
    box3 = box2;//对象赋值，只对数据成员赋值，不对成员函数赋值
    box3.Volume();
    Box box4 = box3;//对象复制，注意与对象赋值的区别
    box4.SetBoxName("box4");
    box4.Volume();
    Box box5(box4);//对象复制
    box5.SetBoxName("box5");
    box5.Volume();
    cout<<"AverWidth=="<<Box::AverWidth()<<endl;

    /*  //对象数组初始化：花括号中分别写出构造函数名并在括号内指定实参
     *  Box boxarr[3] =
     *  {
     *      Box("boxarr0",5,5),
     *      Box("boxarr1",9),
     *      Box("boxarr2",30,15,8)
     *  };
     *      for(int i=0;i<3;i++)
     *          boxarr[i].Volume();
     *
     *  Box *bp;
     *  bp = &boxarr[2];
     *  bp->Volume();//这里的指针bp只能引用public成员函数，无法引用private成员变量，因为不在Box类中的定义的函数
     *  bp->Testpri();
     *  int (Box::*vp)();//定义指向Box类公用成员函数的指针变量vp
     *  vp = &Box::Volume;//使vp指向Box类公用成员函数Volume，这里不能写成vp=&box3.Volume()，必须是类的函数接口，
     *  //注意与TestCourse611的比较，这里去掉&，无法编译通过
     *  (box3.*vp)();//调用对象box3中vp所指的成员函数，即box3.Volume()
     *  FunCout(bp);
     */
    FunCout2(box5);


    cout<<"...out TestCourse92to6..."<<endl;

    return 0;
}


//无参构造函数
/* Box::Box() //构造函数无类型，无返回值
 * {
 *  //cout<<"I am first..."<<endl;
 *  strcpy(boxname,"null");//不能直接赋值，需要使用strcpy函数
 *  height=0;
 *  width=0;
 *  length=0;
 * }
 */


//带参的构造函数
/*Box::Box(char *name, int h, int w, int l)
  {
  strcpy(boxname,name);
  height = h;
  width = w;
  length = l;
  }*/
//上面的写法也可以用参数初始化表实现
Box::Box(const string name,int h,int w,int l):height(h),width(w),length(l)
{
    boxname=name;
}


/* 析构函数
 * 析构函数调用的顺序与构造函数正好相反
 * 先构造，后析构，类似于堆栈:先进后出
 * this指针即当前对象的指针变量
 */
Box::~Box()
{
    cout<<this->boxname<<" call ~Box..."<<endl;
    //cout<<(*this).boxname<<" call ~Box..."<<endl;  不能使用Box.boxname因为成员变量是对象下的，不是类下的
}


//静态数据成员初始化，不能通过参数初始化表进行数据成员初始化
int Box::count = 0;
int Box::sumwidth = 0;


//计算长方体体积 公用的成员函数可以引用本对象中的非静态数据成员，也可以引用类中的静态数据成员
int Box::Volume()
{
    //Box::count 或this->count都可以 静态数据成员不属于某一个对象，属于类
    Box::count++;//每次保留上一次的值
    Box::sumwidth+=this->width;
    cout<<"The volume of "<<this->count<<"_"<<boxname<<" is "<<height*width*length<<endl;
    return 0;
}

//计算长方体体积 常成员函数(可以被const对象引用，也可以被普通对象引用，但const对象只能引用const函数)
int Box::Volume2() const
{
    cout<<"The volume2 of "<<boxname<<" is "<<height*width*length<<endl;
    return 0;
}


//计算长方体的平均参数 静态成员函数主要是用来访问静态数据成员，而不访问非静态成员
float Box::AverWidth()//这里float前面不需要再加static，否则编译报错，声明时有static就可以了
{
    cout<<"Box::count=="<<Box::count<<endl;
    cout<<"Box::sumwidth=="<<Box::sumwidth<<endl;
    return (float)sumwidth/count;//不能用this指针，因为静态成员函数没有this指针，它也不属于对象，而是属于类
}


//验证Box类中定义的函数，可以使用private成员变量
//对象的动态的建立与释放 new delete
int Box::Testpri()
{
    Box *px = new Box("box4",99);
    cout<<"px->height=="<<px->height<<endl;
    px->Volume2();
    int *hp = &px->height;
    cout<<"*hp=="<<*hp<<endl;
    delete px;

    return 0;
}


void Box::SetBoxName(string name)
{
    this->boxname = name;
}


//指向常对象的指针变量: http://zhidao.baidu.com/question/95867277.html
void FunCout(const Box *ptr)
{
    cout<<"...in FunCout..."<<endl;

    //ptr->Volume();编译报错error: passing 'const Box' as 'this' argument of 'int Box::Volume()' discards qualifiers [-fpermissive]
    ptr->Volume2();//调用常成员函数不会报错
    //ptr->boxname="boxCout";编译报错initializing argument 1 of 'char* strcpy(char*, const char*)' [-fpermissive]
    cout<<"...ptr->boxname=="<<ptr->boxname<<endl;

    cout<<"...out FunCout..."<<endl;
}


//常对象引用
void FunCout2(const Box &bx)
{
    cout<<"...in FunCout2..."<<endl;

    bx.Volume2();//调用常成员函数不会报错
    //bx.boxname="boxCout";//编译报错initializing argument 1 of 'char* strcpy(char*, const char*)' [-fpermissive]
    cout<<"...bx.boxname=="<<bx.boxname<<endl;
    cout<<"...bx.width=="<<bx.width<<endl;//友元函数可以访问private成员

    cout<<"...out FunCout2..."<<endl;
}


/* 案例学习  P310 例10.2
 * 运算符重载
 * 知识点：
 *  1.格式：函数类型 operator 运算符名称(形参表){对运算符的重载处理}
 *  2.函数名即为：operator 运算符
 *  3.C++不允许定义新的运算符，只能重载已有的运算符，并且不能改变运算符重载的个数和优先级别,
 *    不能重载的运算符有5个：. * :: sizeof ?:
 *    类的运算符一般必须重载，但是 = 和 & 不需要重载
 *  4.运算符重载函数：作为类的成员函数 和 作为类的友元函数，作为类的成员函数只需要一个入参，另一个参数是成员本身，而作为友元函数则需要两个入参
 *  5.一搬将双目运算符和<<，>> 作为类的友元函数；将单目运算符和复合运算符及=，[],(),-> 作为类的成员函数
 */
int TestCourse102()
{
    cout<<"...in TestCourse102..."<<endl;

    Complex c1(3,4),c2(5,-10),c3,c4,c5;
    c3=c1+c2;//复数相加
    int i=8;
    c4=i+c2;
    cin>>c5;
    cout<<"c1=="<<c1;
    cout<<"c2==";c2.Display();
    cout<<"c3=="<<c3;
    cout<<"c4==";c4.Display();
    cout<<"c5=="<<c5;

    cout<<"...out TestCourse102..."<<endl;

    return 0;
}


//对+进行重载，作为成员函数，可以理解为：c3=c1.operator+c2
//第一个Complex为函数返回值，第2个为域名
/* Complex Complex::operator + (Complex &c)
 * {
 *  Complex cx;
 *  cx.real=this->real+c.real;
 *  cx.imag=this->imag+c.imag;
 *  return cx;
 * }
 */

//对+进行重载，作为友元函数,可以理解为：c3=operator+(c1,c2)
/* Complex operator + (Complex c1, Complex c2)
 * {
 *  Complex cx;
 *  cx.real=c1.real+c2.real;
 *  cx.imag=c1.imag+c2.imag;
 *  return cx;
 * }
 */

//int + Complex
Complex operator + (int &i, Complex &c2)
{
    Complex cx;
    cx.real=i+c2.real;
    cx.imag=c2.imag;
    return cx;
}

//Complex + i
Complex operator + (Complex &c2, int &i)
{
    Complex cx;
    cx.real=i+c2.real;
    cx.imag=c2.imag;
    return cx;
}

//输出Complex
void Complex::Display()
{
    cout<<"("<<this->real;
    if(this->imag >= 0)
        cout<<"+";
    cout<<this->imag<<"i)"<<endl;

    return;
}

//重载输出运算符<<
ostream& operator <<(ostream& output, Complex& c)
{
    output<<"("<<c.real;
    if(c.imag >= 0)
        output<<"+";
    output<<c.imag<<"i)"<<endl;

    return output;
}


//重载输入运算符>>
istream& operator >>(istream& input, Complex& c)
{
    cout<<"please input a complex number: ";
    input>>c.real>>c.imag;
    return input;
}

/* 案例学习  P318 例10.4
 * 双目运算符重载
 * 知识点：
 *  1.格式：函数类型 operator 运算符名称(形参表){对运算符的重载处理}
 *  2.函数名即为：operator 运算符
 *  3.C++不允许定义新的运算符，只能重载已有的运算符，并且不能改变运算符重载的个数和优先级别,
 *    不能重载的运算符有5个：. * :: sizeof ?:
 *    类的运算符一般必须重载，但是 = 和 & 不需要重载
 *  4.运算符重载函数：作为类的成员函数 和 作为类的友元函数，作为类的成员函数只需要一个入参，另一个参数是成员本身，而作为友元函数则需要两个入参
 *  5.一搬将双目运算符和<<，>> 作为类的友元函数；将单目运算符和复合运算符及=，[],(),-> 作为类的成员函数
 */
int TestCourse104()
{
    cout<<"...in TestCourse104..."<<endl;

    String str1("Hell0"),str2("book"),str3("Love"),str4("book");
    Compare(str1, str2);
    Compare(str2, str3);
    Compare(str3, str4);
    Compare(str2, str4);

    cout<<"...out TestCourse104..."<<endl;

    return 0;
}


//初始化带参构造函数
String::String(const char *str)
{
    p = str;
}

//重载>
bool operator > (String &str1, String &str2)
{
    if(strcmp(str1.p, str2.p) > 0)
        return true;
    else
        return false;
}


//重载<
bool operator < (String &str1, String &str2)
{
    if(strcmp(str1.p, str2.p) < 0)
        return true;
    else
        return false;
}


//重载==
bool operator == (String &str1, String &str2)
{
    if(strcmp(str1.p, str2.p) == 0)
        return true;
    else
        return false;
}


void String::Display()
{
    if(this->p == NULL)
    {
        cout<<"NULL";
        return;
    }
    cout<<this->p;
}


//通用比较函数
void Compare(String &str1, String &str2)
{
    if(str1 > str2)
    {
        str1.Display();
        cout<<">";
        str2.Display();
        cout<<endl;
    }
    else if(str1 < str2)
    {
        str1.Display();
        cout<<"<";
        str2.Display();
        cout<<endl;
    }
    else
    {
        str1.Display();
        cout<<"==";
        str2.Display();
        cout<<endl;
    }
}


/*
 *案例学习  P334/336 例10.9/10.10
 * 1.转换构造函数:将double类型转换为Complex类对象
 * 2.类型转换函数:将Complex类对象转换为double类型
 */
int TestCourse109()
{
    cout<<"...in TestCourse109..."<<endl;

    Complex c1(3, 4), c2(5, -10), c3(8), c4, c5, c6;
    double d;
    d = 2.5 + c1; //调用类型转换函数
    cout<<"d=="<<d<<endl;//d==5.5
    c4 = c2 + c3;//调用运算符重载+
    cout<<"c4==";c4.Display();//c4==(13-10i)
    //c5,c6证明交换律成立
    c5 = 2.5 + c1;//调用转换构造函数，再调用运算符+重载函数
    cout<<"c5==";c5.Display();//c5==(5.5+0i)
    c6 = c2 + 3.5;//调用转换构造函数，再调用运算符+重载函数
    cout<<"c6==";c6.Display();//c6==(8.5+0i)

    cout<<"...out TestCourse109..."<<endl;

    return 0;
}


//类模板外定义构造函数
template <class uType>
CompareAll<uType>::CompareAll(uType x, uType y)
{
    this->x = x;
    this->y = y;
}

//类模板外定义成员函数
template <class uType>
uType CompareAll<uType>::max()
{
    return x>y?x:y;
}

//类模板外定义成员函数
template <class uType>
uType CompareAll<uType>::min()
{
    return x<y?x:y;
}

/*
 *案例学习  P302 例9.14 类模板
 * 1.类是对象的抽象，对象是类的实例;类模板是类的抽象，类是类模板的实例;
 * 2.类模板定义方式
 */
int TestCourse914()
{
    cout<<"...in TestCourse10914..."<<endl;

    CompareAll<int> cpi(3, -2);
    CompareAll<double> cpd(9.8, 12.3);
    CompareAll<char> cpc('a', 'B');
    CompareAll<string> cps("love", "china");

    cout<<"cpi.max()=="<<cpi.max()<<",cpi.min()=="<<cpi.min()<<endl;
    cout<<"cpd.max()=="<<cpd.max()<<",cpd.min()=="<<cpd.min()<<endl;
    cout<<"cpc.max()=="<<cpc.max()<<",cpc.min()=="<<cpc.min()<<endl;
    cout<<"cps.max()=="<<cps.max()<<",cps.min()=="<<cps.min()<<endl;

    cout<<"...in TestCourse10914..."<<endl;

    return 0;
}


//派生类默认构造函数，调用基类的默认构造函数
TimeDer::TimeDer()//:Time(),tm() 可以隐式调用
{
    this->year=1970;
    this->month=1;
    this->day=1;
}

//派生类带参构造函数，调用基类的带参构造函数
//参数可以乱序排列
TimeDer::TimeDer(int h, int y, int s, int min, int month, int d, int tmh, int tmm, int tms, const char *str):Time(h, min, s),tm(tmh,tmm,tms),Str1(str)
{
    this->year = y;
    this->month = month;
    this->day = d;
}
//子对象是空构造函数，可以隐式调用
TimeDer::TimeDer(int h, int y, int s, int min, int month, int d, const char *str):Time(h, min, s),Str1(str)
{
    this->year = y;
    this->month = month;
    this->day = d;
}

//可以将带参构造函数用初始化表类表示
//TimeDer::TimeDer(int h, int y, int s, int min, int month, int d):year(y),month(month),day(d),Time(h, min, s){}

int TimeDer::SetTimeDer()
{
    cout<<"please input year-month-day hour:min:sec :";
    cin>>year>>month>>day;
    //this->SetTime();
    cin>>hour>>min>>sec;
    return 0;
}

int TimeDer::GetTimeDer()
{
    cout<<"you input time is :";
    cout<<year<<"-"<<month<<"-"<<day<<"  ";
    //this->GetTime();
    cout<<this->hour<<":"<<this->min<<":"<<this->sec;
    cout<<endl;
    return 0;
}

int TimeDer::TmDisplay()
{
    cout<<"tm is:";
    tm.GetTime();
    return 0;
}

int TimeDer::StrDisplay()
{
    cout<<"Str is:";
    Str1.Display();
    cout<<endl;
    return 0;
}

TimeGra::TimeGra()
{
    this->country="BeiJing";
}

TimeGra::TimeGra(int h, int y, int s, int min, int month, int d, int tmh, int tmm, int tms, const char *str, string country):TimeDer(h, y, s, min, month, d, tmh, tmm, tms, str)
{
    this->country=country;
}

int TimeGra::showall()
{
    this->GetTimeDer();
    this->TmDisplay();
    this->StrDisplay();
    cout<<"country=="<<this->country<<endl;
    return 0;
}
/*
 *案例学习  P350/P360 例11.1/11.5 类的派生
 1.派生的方式及访问权限
 在基类的访问属性     继承方式      在派生类中的访问属性
 private              public        不可访问
 private              private       不可访问
 private              protected     不可访问
 public               public        public
 public               private       private
 public               protected     protected
 protected            public        protected
 protected            private       private
 protected            protected     protected
 在实际开发中，常用的是公用继承
 2.派生类中的构造函数:基类的构造函数不能继承到派生类中，在执行派生类的构造函数时，需要调用基类的构造函数;
 派生类对象先调用派发类析构函数，再调用子对象析构函数，最后调用基类析构函数
 3.含有子对象的构造函数:
 派生类构造函数名(总参数表):基类构造函数名(参数表),子对象名(参数表)
 {派生类中新增数据成员初始化语句}
 4.类属性中包含另外一个类对象，叫类的组合
 继承是纵向的，组合是横向的
*/
int TestCourse111()
{
    cout<<"...in TestCourse111..."<<endl;

    /*  TimeDer td1;
     *  td1.GetTimeDer();
     *  td1.TmDisplay();
     *  td1.StrDisplay();
     *  TimeDer td2(22,2012,30,28,9,8,23,59,59,"test 2012");
     *  td2.GetTimeDer();
     *  td2.TmDisplay();
     *  td2.StrDisplay();
     *  TimeDer td3(10,2049,00,00,10,1,"china 2049");
     *  td3.GetTimeDer();
     *  td3.TmDisplay();
     *  td3.StrDisplay();
     */

    TimeGra tg1;
    tg1.showall();
    TimeGra tg2(22,2012,30,28,9,8,23,59,59,"test 2012","HongKong");
    tg2.showall();

    cout<<"...in TestCourse111..."<<endl;

    return 0;
}


//Teacher类空构造函数初始化
Teacher::Teacher():People()
{
    this->name = "";
    this->age = 0;
    this->title = "";
}

//Teacher类带参构造函数初始化
Teacher::Teacher(string name,string iccid, size_t age, string title):People(name, iccid)
{
    this->name = name;
    this->age = age;
    this->title = title;
}

//Teacher类信息展示
void Teacher::Display()     //声明时加virtual，外部定义时不能再加virtual，否则编译报错:error: 'virtual' outside class declaration
{
    cout<<"Teacher.name=="<<this->name<<endl;
    cout<<"age=="<<this->age<<endl;
    cout<<"title=="<<this->title<<endl;
}


//StuDent类空构造函数初始化
StuDent::StuDent():People()
{
    this->name = "";//不能写成this->name=NULL
    this->sex = '\0';
    this->score = 0;
}

//StuDent类带参构造函数初始化
StuDent::StuDent(string name, string iccid, char sex, float score):People(name, iccid)
{
    this->name = name;
    this->sex = sex;
    this->score = score;
}

//StuDent类信息展示
void StuDent::Display()
{
    cout<<"StuDent.name=="<<this->name<<endl;
    cout<<"sex=="<<this->sex<<endl;
    cout<<"score=="<<this->score<<endl;
    //this->People::Display();
}


//Graduate类空构造函数初始化，基类由系统隐式调用
Graduate::Graduate()
{
    this->wage = 0;
}

//Graduate类带参构造函数初始化
Graduate::Graduate(string name, string iccid, size_t age, string title, char sex, float score, float wage)\
    :People(name, iccid),Teacher(name,iccid, age, title),StuDent(name, iccid, sex, score),wage(wage){}

//Graduate类信息展示
void Graduate::Display()
{
    //this->name="china"; //这里出现二义性，编译报错
    //this->iccid = "340827198808211811";//定义虚基类之前，这里编译报错，出现二义性
    this->People::Display(); //定义虚基类之前，这里编译报错 'People' is an ambiguous base of 'Graduate';StuDent和Teacher类都继承了该函数
    this->StuDent::Display();
    this->Teacher::Display();
    cout<<"wage=="<<this->wage<<endl;
}

//基类对象引用作为形参，子对象作为实参
void TeaFunc(Teacher &t)
{
    t.Display();
}

/*案例学习 P370 例11.8 多重继承派生类
 *1.派生类构造函数名(总参数表):基类1构造函数(参数表),基类2构造函数(参数表),基类3构造函数(参数表){派生类中新增成员初始化语句}
 *2.基类的同名成员在派生类中被屏蔽，成为“不可见”的，或者说，派生类新增加的同名成员覆盖了基类中的同名成员。
 *3.虚基类，继承间接共同基类时只保留一份成员,虚基类并不是在声明基类时声明的，而是在声明派生类时，指定继承方式时声明的：
 class 派生类名:virtual 继承方式  基类名
 4.在派生类的构造函数中只须负责对直接基类初始化，再由其直接基类负责对间接基类初始化；
 在最后的派生类中不仅要负责对其直接基类进行初始化，还要负责对虚基类初始化；
 C++编译系统只执行最后的派生类对虚基类的构造函数调用，而忽略虚基类的其他派生类对构造函数的调用，这就保证了虚基类的数据成员不会被多次初始化。
 5.只能用子类对象对其基类对象赋值，不能用基类对象对其子类对象赋值，同一基类的不同派生类对象之间也不能赋值。
 6.通过指向基类对象的指针，只能访问派生类中的基线成员，而不能访问派生类增加的成员；
 用指向基类对象的指针变量指向子类对象是合法的、安全的，不会出现编译上的错误。
*/
int TestCourse118()
{
    cout<<"...in TestCourse118..."<<endl;

    try
    {
        //调用默认构造函数
        Graduate g1;
        cout<<"g1 ---------------->"<<endl;
        g1.Display();
        cout<<"<-----------------g1"<<endl;
        //调用带参构造函数
        Graduate g2("wangff","34290119880902064X", 24,"logistics engineer",'f',120,520);
        cout<<"g2 ---------------->"<<endl;
        g2.Display();
        cout<<"<-----------------g2"<<endl;

        //派生类对象向基类对象赋值
        StuDent s1;
        s1 = g2;
        cout<<"s1 ---------------->"<<endl;
        s1.Display();
        cout<<"<-----------------s1"<<endl;
        cout<<"t1 ---------------->"<<endl;
        TeaFunc(g2);
        cout<<"<-----------------t1"<<endl;
        StuDent s2("lijha","340827198808211811", 'm', 99.5);
        cout<<"s3_s ---------------->"<<endl;
        StuDent *s3 = &s2;
        s3->Display();//这里调用的是StuDent类对象的Display()函数
        cout<<"<-----------------s3_s"<<endl;
        cout<<"s3_g ---------------->"<<endl;
        s3 = &g2;
        s3->Display();//这里调用的仍然是StuDent类的Display()函数，而不是Graduate子类对象的Display()函数
        cout<<"<-----------------s3_g"<<endl;
    }
    catch(const exception &ex)
    {
        cout<<"error..."<<ex.what()<<endl;
    }

    cout<<"...out TestCourse118..."<<endl;
    return 0;
}


//Point类构造函数
Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

//Point设置坐标值
void Point::SetPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

//Point <<运算符重载
ostream & operator << (ostream &output, Point &p)
{
    output<<"[x="<<p.x<<", y="<<p.y<<"]";
    return output;
}

//Circle类构造函数
Circle::Circle(float x, float y, float r):Point(x, y), radius(r){}

//设置Circle的半径
void Circle::SetRadius(float r)
{
    this->radius = r;
}

//获取Circle的半径
float Circle::GetRadius() const
{
    return this->radius;
}

//计算Circle的面积
float Circle::Area() const
{
    return this->radius*this->radius*3.14159;
}

//Circle <<运算符重载
ostream & operator << (ostream & output, Circle & c)
{
    output<<"[x="<<c.x<<", y="<<c.y<<", radius="<<c.radius<<"], area="<<c.Area();
    return output;
}

//Cylinder构造函数
Cylinder::Cylinder(float x, float y, float r, float h):Circle(x, y, r)
{
    this->height = h;
}

//Cylinder设置高度
void Cylinder::SetHeight(float h)
{
    this->height = h;
}

//Cylinder获取高度
float Cylinder::GetHeight() const
{
    return this->height;
}

//Cylinder面积
float Cylinder::Area() const
{
    return 2*Circle::Area() + 2*3.14159*this->GetRadius()*height;
}

//Cylinder体积
float Cylinder::Volume() const
{
    return Circle::Area()*this->height;
}

//Cylinder << 运算符重载
ostream & operator << (ostream &output, const Cylinder & c)
{
    output<<"[x="<<c.GetX()<<", y="<<c.GetY()<<", radius="<<c.GetRadius()<<", height="<<c.GetHeight()<<"], "\
          <<"area="<<c.Area()<<", volume="<<c.Volume();
    return output;
}



/*案例学习：P391/P399 例12.1/12.2 C++ 静态多态性/动态多态性
 *1.回顾常成员函数
 * 数据成员                 非const的普通成员函数           const成员函数
 * 1)非const的普通数据成员  可以引用，也可以改变值          可以引用，但不可以改变值
 * 2)const数据成员          可以引用，但不可以改变值        可以引用，但不可以改变值
 * 3)const对象              不允许                          可以引用，但不可以改变值
 *2.静态多态性
 * 1)编译时的多态性，通过函数重载实现的
 * 2)速度快、效率高，但缺乏灵活性，在程序运行前就已经决定了执行的函数和方法
 *3.动态多态性
 * 1)运行时的多态性，通过虚函数(virtual function)实现的
 * 2)所谓虚函数，就是在基类声明函数是虚拟的，并不是实际存在的函数，然后在派生类中才正式定义此函数
 *4.虚析构函数
 *  如果将基类的析构函数声明为虚函数时，由该基类所派生的所有派生类的析构函数也都自动成为虚函数，
 *  即使派生类的析构函数与基类的析构函数名字不相同
 *5.纯虚函数
 *  纯虚函数定义：virtual 函数类型 函数名(参数表列) = 0;
 *  类中有一个或以上纯虚函数，则该类为抽象类，抽象类可以使用对象指针，但不能声明具体对象。
 */
int TestCourse121()
{
    cout<<"...in TestCourse121..."<<endl;

    //Point class
    Point p1;
    p1.ShapeName();
    cout<<"p1===>"<<"[x="<<p1.GetX()<<", y="<<p1.GetY()<<"]"<<endl;
    //  p1.SetPoint(3.6, 2.8);
    //  cout<<"p1===>"<<p1<<endl;
    //
    //  //Circle class
    Circle c1(3.2,5.0);
    c1.SetRadius(3.6);
    c1.ShapeName();
    cout<<"c1===>[x="<<c1.GetX()<<", y="<<c1.GetY()<<", radius="<<c1.GetRadius()<<"], area="<<c1.Area()<<endl;
    //  c1.SetPoint(5.2, 8.5);
    //  c1.SetRadius(3.6);
    //  cout<<"c1===>"<<c1<<endl;
    //  //Circle初始化Point类的引用
    //  Point &p2 = c1;
    //  cout<<"p2===>"<<p2<<endl;
    //
    //  //Cylinder class
    Cylinder cy1(10.0, 8.5, 3.6, 5.2);
    cy1.ShapeName();
    cout<<"cy1===>"<<cy1<<endl;
    //  cy1.SetPoint(5, 6.2);
    //  cy1.SetRadius(8);
    //  cy1.SetHeight(20.5);
    //  cout<<"cy1===>"<<cy1<<endl;
    //  //Cylinder初始化Point类的引用
    //  p2 = cy1;
    //  cout<<"p2===>"<<p2<<endl;
    //  //Cylinder初始化Circle类的引用
    //  Circle &c2 = cy1;
    //  cout<<"c2===>"<<c2<<endl;
    //
    //  //People StuDent Teacher Graduat class
    //  People pe1("lijha", "340827198808211811");
    //  StuDent st1("lijhg", "340827199108181839", 'm', 99.0);
    //  Teacher tr1("wangff", "34290119880902064X", 24, "logistics engineer");
    //  Graduate ge1("lijha", "340827198808211811", 24, "Software engineer", 'm', 98.5, 860.58);
    //  People *pe = &pe1;
    //  cout<<"pe--->People:"<<endl;
    //  pe->Display();
    //  pe = &st1;
    //  cout<<"pe--->StuDent:"<<endl;
    //  pe->Display();
    //  pe = &tr1;
    //  cout<<"pe--->Teacher:"<<endl;
    //  pe->Display();
    //  pe = &ge1;
    //  cout<<"pe--->Graduate:"<<endl;
    //  pe->Display();

    Shape *sp;
    sp = &p1;
    sp->ShapeName();
    cout<<"sp->Area()=="<<sp->Area()<<", sp->Volume()=="<<sp->Volume()<<endl;

    sp = &c1;
    sp ->ShapeName();
    cout<<"sp->Area()=="<<sp->Area()<<", sp->Volume()=="<<sp->Volume()<<endl;

    sp = &cy1;
    sp ->ShapeName();
    cout<<"sp->Area()=="<<sp->Area()<<", sp->Volume()=="<<sp->Volume()<<endl;

    Graduate *ge2 = new Graduate("lijha", "340827198808211811", 24, "Software engineer", 'm', 98.5, 860.58);
    cout<<"ge2--->Graduate:"<<endl;
    //ge2->Display();
    delete ge2;         //基类析构函数~People定义为虚函数之前，可以释放派生类和基类

    People *pe3 = new Graduate("lijha", "340827198808211811", 24, "Software engineer", 'm', 98.5, 860.58);
    cout<<"pe3--->Graduate:"<<endl;
    //pe3->Display();
    delete pe3;         //基类析构函数~People定义为虚函数之前，只能释放People基类

    Teacher *tr3 = new Graduate("lijha", "340827198808211811", 24, "Software engineer", 'm', 98.5, 860.58);
    cout<<"tr3--->Graduate:"<<endl;
    //tr3->Display();
    delete tr3;         //基类析构函数~People定义为虚函数之前，只能释放Teacher和People基类

    cout<<"...out TestCourse121..."<<endl;

    return 0;
}


struct personInfo psIn1;
struct personInfo & TestTemp2()
{
    psIn1.stu_id=1001;
    strcpy(psIn1.stu_name, "lijha");
    psIn1.stu_score=98;
    psIn1.stu_count=1;

    return psIn1;
}


PerInfo pi2;
PerInfo & PerInfo::TestPe1()
{
    pi2.stu_id=1002;
    strcpy(pi2.stu_name, "wangff");
    pi2.stu_score=99;
    pi2.stu_count=2;

    return pi2;
}


struct s1
{
    char k;
    double i;
    char c;
};
struct a1
{
    char k;
    long l;
    char c;
    double i;
};
struct b1
{
    char k;
    int i;
    char c;
    double d;
};
//临时测试函数
int TestTemp_1()
{
    People pp[5];
    for(int i=0; i<5; i++)
    {
        pp[i].Display();
    }
    ifstream infile("./file/t1.txt");//默认为ios::in
    if(!infile)cout<<"---open file error---"<<endl;
    int j=0;
    while(infile)
    {
        infile>>pp[j].name>>pp[j].iccid;
        j++;
        if(j>=5)break;
    }
    cout<<"------j=="<<j<<endl;
    for(int i=0; i<5; i++)
    {
        pp[i].Display();
    }

    char abc[100];
    memset(abc, '\0', sizeof(abc));
    strcpy(abc, "340827");
    char sa[2];
    sa[0]=0x01;
    //sa[2]='\0';
    sa[1]='\0';
    strcat(abc, sa);
    strcat(abc, "china2013");
    strcat(abc, sa);
    strcat(abc, "Hello World");
    cout<<"abc==["<<abc<<"]"<<endl;
    char *strPos = abc;
    char *pVec = NULL;
    while((pVec = strstr(strPos, sa)) != NULL)
    {
        *pVec = '\0';
        cout<<"----strPos==["<<strPos<<"]"<<endl;
        strPos = pVec + strlen(sa);
    }
    pVec = NULL;
    if(strlen(strPos) != 0)
    {
        cout<<"----strPos==["<<strPos<<"]"<<endl;
    }
    //结构体默认构造函数测试
    struct personInfo perIn;
    cout<<"---"<<perIn.stu_id<<endl;
    cout<<"---"<<perIn.stu_name<<endl;
    cout<<"---"<<perIn.stu_score<<endl;
    cout<<"---"<<perIn.stu_count<<endl;

    //内存数据对齐
    cout<<"---sizeof(perIn)=="<<sizeof(perIn)<<endl;//40
    cout<<"---sizeof(s1)=="<<sizeof(struct s1)<<endl;//24,,,8+8+8
    cout<<"---sizeof(a1)=="<<sizeof(struct a1)<<endl;//32,,,8+8+8+8
    cout<<"---sizeof(b1)=="<<sizeof(struct b1)<<endl;//24,,,4+4+8+8

    cout<<"---sizeof(int)=="<<sizeof(int)<<endl;//4
    cout<<"---sizeof(double)=="<<sizeof(double)<<endl;//8
    cout<<"---sizeof(char)=="<<sizeof(char)<<endl;//1
    cout<<"---sizeof(char*)=="<<sizeof(char *)<<endl;//8--->64位系统
    cout<<"---sizeof(float)=="<<sizeof(float)<<endl;//4
    cout<<"---sizeof(long)=="<<sizeof(long)<<endl;//8--->64位系统

    //  cout<<"perIn1---"<<psIn1.stu_id<<endl;
    //  cout<<"perIn1---"<<psIn1.stu_name<<endl;
    //  cout<<"perIn1---"<<psIn1.stu_score<<endl;
    //  cout<<"perIn1---"<<psIn1.stu_count<<endl;
    //  //变量的引用传递
    //  struct personInfo perIn2(TestTemp2());
    //  cout<<"perIn2---"<<perIn2.stu_id<<endl;
    //  cout<<"perIn2---"<<perIn2.stu_name<<endl;
    //  cout<<"perIn2---"<<perIn2.stu_score<<endl;
    //  cout<<"perIn2---"<<perIn2.stu_count<<endl;

    //  //类测试
    //  PerInfo pi1(pi2.TestPe1());
    //  cout<<"pi1---"<<pi1.stu_id<<endl;
    //  cout<<"pi1---"<<pi1.stu_name<<endl;
    //  cout<<"pi1---"<<pi1.stu_score<<endl;
    //  cout<<"pi1---"<<pi1.stu_count<<endl;
    //
    string xmlstr = "<a>&lt;b&gt;123&lt;/b&gt;&lt;c&gt;gogo&lt;/c&gt;&lt;d&gt;123&lt;/d&gt;</a>";
    char cstr[xmlstr.length() + 1];
    //char *strpos = cstr;
    char cstr2[xmlstr.length() + 1];
    char cstr3[10];

    char *cpos = cstr;
    memset(cstr, '\0', sizeof(cstr));
    memset(cstr2, '\0', sizeof(cstr2));
    memset(cstr3, '\0', sizeof(cstr3));
    strcpy(cstr, xmlstr.c_str());
    cout<<"------cstr=="<<cstr<<endl;
    for(long j=0; ;)
    {
        if(*cpos == '\0')
        {
            break;
        }
        else if(*cpos == '&')
        {
            memset(cstr3, '\0', sizeof(cstr3));
            strncpy(cstr3, cpos, 4);
            if(strcmp(cstr3, "&lt;") == 0)
                cstr2[j++] = '<';
            else if(strcmp(cstr3, "&gt;") == 0)
                cstr2[j++] = '>';
            cpos = cpos+4;
        }
        else
        {
            cstr2[j++] = *cpos;
            cpos++;
        }
    }
    cout<<"------cstr2=="<<cstr2<<endl;
    //  string xmlkey="123";
    //  string xmlval="";
    //  for(; ; )
    //  {
    //      size_t keypos = xmlstr.find(xmlkey);
    //      if(keypos == string::npos)
    //      {
    //          xmlval += xmlstr;
    //          break;
    //      }
    ////        xmlstr.replace(keypos, xmlkey.length(), "888");
    //
    //      xmlval += xmlstr.substr(0, keypos);
    //      xmlval += "888";
    //      xmlstr = xmlstr.substr(keypos+3);
    //  }
    //  cout<<"----xmlstr=="<<xmlstr<<endl;
    //  cout<<"----xmlval=="<<xmlval<<endl;

    return 0;
}

//test c function: isdigit,isupper...
int TestTemp_2(const char* puInparam)
{
    printf("\n---in TestTemp_2...puInparam==[%s]\n", puInparam);
    unsigned int a=6;
    unsigned int b=7;
    int c = 3;
    int d = 8;
    int e = 2;
    int cc = -3;
    //printf("---a-b==[%ld]\n", a-b);//a-b=4294967295 unsigned int
//    printf("---c-d==[%ld]\n", c-d);
//    printf("---c-a==[%ld]\n", c-a);
//    printf("---b-d==[%ld]\n", b-d);
    printf("---a-b==[%d]\n", a-b);//a-b=-1
    printf("---c-d==[%d]\n", c-d);
    printf("---c-a==[%d]\n", c-a);
    printf("---b-d==[%d]\n", b-d);
    printf("---c/e==[%d]\n", c/e);
    printf("---c mod e==[%d]\n", c%e);
    printf("---cc/e==[%d]\n", cc/e);
    printf("---cc mod e==[%d]\n", cc%e);
    c = c << 1;
    printf("---c==[%d]\n", c);

    char puIn2[100];
    memset(puIn2, '\0', sizeof(puIn2));
    strcpy(puIn2, puInparam);

    char *puIn = puIn2;

    if(puIn == NULL)
        return 0;
    unsigned int flag = 1;
    while(*puIn != '\0')
    {
        printf("-----check [%c]...\n", *puIn);
        if(!isdigit(*puIn))
        {
            printf("-----[%c] is not digital...\n", *puIn);
            flag = 0;
            break;
        }

        puIn++;
    }
    if(flag == 1)
    {
        printf("-----check [%s] is digital...\n", puInparam);
    }
    else
    {
        printf("-----check [%s] is not digital...\n", puInparam);
    }
    printf("------out TestTemp_2------\n");

    return 0;
}


//测试和学习 ， & 、&&
int TestBitCalc(const char* puInparam)
{
    cout<<"++++++++++in TestBitCalc++++++++"<<endl;
    cout<<"++++++++++puInparam=="<<puInparam<<endl;

    char * pch = NULL;
    char str[1000];
    char desstr[1000];
    memset(str, '\0', sizeof(str));
    memset(desstr, '\0', sizeof(desstr));
    strcpy(str, puInparam);
    pch = strtok(str,",'");
    while(pch != NULL)
    {
        strcat(desstr, pch);
        pch = strtok (NULL, ",'");
    }
    printf("----------desstr==[%s]\n",desstr);

    char sqlText1[20];
    char sqlText2[20];
    char *sqlPtr = sqlText1;
    memset(sqlText2, '\0', sizeof(sqlText2));
    snprintf(sqlText1, 5, "%s", "12345");//这里写入4个字符,结尾还有一个\0占用一个字节
    strcpy(sqlText2, "china2013");
    cout<<"--------sqlPtr=="<<sqlText1<<endl;
    //snprintf(sqlPtr, sizeof(sqlPtr)-strlen(sqlPtr)-1, "%s | %s", sqlPtr, "abc123");
    strncat(sqlText1, "xyzefg", sizeof(sqlText1)-strlen(sqlText1)-1);
    cout<<"--------sqlPtr=="<<sqlText1<<endl;
    string p="abc";
    strncat(sqlText1, p.c_str(), sizeof(sqlText1)-strlen(sqlText1)-1);
    cout<<"--------sqlPtr=="<<sqlPtr<<endl;
    strncat(sqlText1, sqlText2, sizeof(sqlText1)-strlen(sqlText1)-1);
    cout<<"--------sqlPtr=="<<sqlPtr<<endl;
    strncat(sqlText1, "999999", sizeof(sqlText1)-strlen(sqlText1)-1);
    cout<<"--------sqlPtr=="<<sqlPtr<<endl;

    unsigned int a = 0x11;
    unsigned int b = 0x00;
    unsigned short s = 0x10;
    unsigned char c = 0x01;

    //%x: 用于将参数以16进制的格式输出
    printf("a && b = %x \n", a&&b);
    printf("a && s = %x \n", a&&s);
    printf("a && c = %x \n", a&&c);
    printf("s && c = %x \n", s&&c);
    printf("a && 0x110 = %x \n", a&&0x110);

    printf("a & b = %x \n", a&b);
    printf("a & s = %x \n", a&s);
    printf("a & c = %x \n", a&c);
    printf("s & c = %x \n", s&c);
    printf("a & 0x110 = %x \n", a&0x110);

    printf("a || b = %x \n", a||b);
    printf("a || s = %x \n", a||s);
    printf("a || c = %x \n", a||c);
    printf("s || c = %x \n", s||c);
    printf("a || 0x110 = %x \n", a||0x110);

    printf("a | b = %x \n", a|b);
    printf("a | s = %x \n", a|s);
    printf("a | c = %x \n", a|c);
    printf("s | c = %x \n", s|c);
    printf("a | 0x110 = %x \n", a|0x110);

    cout<<"++++++++++out TestBitCalc++++++++"<<endl;

    return 0;
}


//Learning union-struct , 2014.7.13
int TestUnionStruct(const char* puIn)
{
    printf("\n------in TestUnionStruct-----\n");

    union
    {
        int a;
        float b;
        char c[10];
    }Record = {18};//init union data(must be the first element)

    printf("******init element a | Record.a==[%d], Record.b==[%f], Record.c==[%s]******\n", Record.a, Record.b, Record.c);
    Record.b = 20.12;
    printf("******init element b | Record.a==[%d], Record.b==[%f], Record.c==[%s]******\n", Record.a, Record.b, Record.c);
    strcpy(Record.c, "hahaha");
    printf("******init element c | Record.a==[%d], Record.b==[%f], Record.c==[%s]******\n", Record.a, Record.b, Record.c);

    struct BIT_FILELD
    {
        unsigned int a:1;
        unsigned int b:3;
        unsigned int c:4;
    };
    struct BIT_FILELD bitStr, *bitPos;
    bitStr.a = 1;
    bitStr.b = 7;
    bitStr.c = 15;
    //1, 7, 15
    printf("++++++a=%d, b=%d, c=%d, sizeof(bitStr)=%ld++++++\n", bitStr.a, bitStr.b, bitStr.c, sizeof(bitStr));
    bitPos = &bitStr;
    bitPos->b = 21;
    //1, 4, 15
    printf("++++++a=%d, b=%d, c=%d, sizeof(bitStr)=%ld, sizeof(bitPos)=%ld++++++\n",
           bitPos->a, bitPos->b, bitPos->c, sizeof(bitStr), sizeof(bitPos));

    printf("++++++sizeof(char*)=%ld, sizeof(int*)=%ld\n", sizeof(char*), sizeof(int*));

    printf("------out TestUnionStruct-----\n");

    return 0;
}


//learning linked list, 2014.7.16
struct STU_NODE
{
    int stu_id;
    char stu_name[20];
    struct STU_NODE *link;//next node
    struct STU_NODE *back;//previous node; add by Leo 2014.7.27

    //constructed function
    STU_NODE();
    //init function
    void Clean();
};
typedef struct STU_NODE stuNode;

stuNode::STU_NODE()
{
    this->stu_id = 0;
    memset(this->stu_name, '\0', sizeof(stu_name));
    this->link = NULL;
    this->back = NULL;
}

void stuNode::Clean()
{
    this->stu_id = 0;
    memset(this->stu_name, '\0', sizeof(stu_name));
    this->link = NULL;
    this->back = NULL;
}

void PrintLinkedList(stuNode* stuPos, int start=1)
{
    printf("begin");
    if(stuPos == NULL)
    {
        printf("--->");
    }
    while(stuPos != NULL)
    {
        printf("--->stu_id==[%d], stu_name==[%s]--->", stuPos->stu_id, stuPos->stu_name);
        if(start==1)
            stuPos = stuPos->link;
        else
            stuPos = stuPos->back;
    }
    printf("end\n\n");

    return;
}

//create the one-way linked list
void CreateSimLinkedList(stuNode** root)
{
    printf("******CreateSimLinkedList******\n");
    stuNode *stuNode1,*stuNode2,*stuNode3;
    stuNode1 = (stuNode*)malloc(sizeof(stuNode));
    if(stuNode1 == NULL)
    {
        printf("---exec malloc error...out of memory---\n");
        return;
    }
    stuNode1->Clean();
    stuNode1->stu_id=1003;

    stuNode2 = (stuNode*)malloc(sizeof(stuNode));
    if(stuNode2 == NULL)
    {
        printf("---exec malloc error...out of memory---\n");
        return;
    }
    stuNode2->Clean();
    stuNode2->stu_id = 1005;
    strcpy(stuNode2->stu_name, "jwkljh");

    stuNode3 = (stuNode*)malloc(sizeof(stuNode));
    if(stuNode3 == NULL)
    {
        printf("---exec malloc error...out of memory---\n");
        return;
    }
    stuNode3->Clean();
    stuNode3->stu_id = 1008;
    strcpy(stuNode3->stu_name, "LeoDemon");

    *root = stuNode1;
    stuNode1->link = stuNode2;
    stuNode2->link = stuNode3;

    return;
}

//create the one-way linked list
void InsertSimLinkedList(stuNode** stuPos, int new_id, const char* new_name)
{
    printf("------insert data (%d, %s)\n", new_id, new_name);

    stuNode* curr = NULL;
    while((curr = *stuPos) != NULL && curr->stu_id < new_id)
    {
        stuPos = &curr->link;
    }
    stuNode* newNode = (stuNode*)malloc(sizeof(stuNode));
    if(newNode == NULL)
    {
        printf("---exec malloc error...out of memory---\n");
        return;
    }
    newNode->Clean();
    newNode->stu_id = new_id;
    strcpy(newNode->stu_name, new_name);

    newNode->link = curr;
    *stuPos = newNode;

    return;
}

//free the one-way linked list
void FreeLinkedList(stuNode* stuPos)
{
    while(stuPos != NULL)
    {
        printf("......free stu_id==[%d] success......\n", stuPos->stu_id);
        free(stuPos);
        stuPos = stuPos->link;
    }
    stuPos = NULL;

    return;
}

//One-Way Linked List
int TestSimpleLinkedList()
{
    printf("\n------in TestSimpleLinkedList-----\n");
    stuNode stuRoot;
    PrintLinkedList(&stuRoot);//test the struct constructed function

    stuNode *root = NULL;
    //create linked list
//    CreateSimLinkedList(&root);
//    PrintLinkedList(root);

    //insert data into linked list
    InsertSimLinkedList(&root, 1001, "Jack");
    PrintLinkedList(root);
    InsertSimLinkedList(&root, 1010, "Rose");
    PrintLinkedList(root);
    InsertSimLinkedList(&root, 1006, "Smith");
    PrintLinkedList(root);

    //free the memory
    FreeLinkedList(root);

    printf("------out TestSimpleLinkedList-----\n");

    return 0;
}


//create or Insert data into double-linked-list
void InsDoubleLink(stuNode* stuPos, int new_id, const char* new_name)
{
    //consider 4 conditions:
    //1.insert into the middle;
    //2.insert into the begin;
    //3.insert into the end;
    //4.insert into the begin, at the same time it's the end
    printf("------insert data (%d, %s)\n", new_id, new_name);

    stuNode* curr = NULL;
    stuNode* next = NULL;
    for(curr=stuPos; (next=curr->link)!=NULL; curr=next)
    {
        if(next->stu_id > new_id)
        {
            break;
        }
    }
    stuNode* newNode = (stuNode*)malloc(sizeof(stuNode));
    if(newNode == NULL)
    {
        printf("---exec malloc error...out of memory---\n");
        return;
    }
    newNode->Clean();
    newNode->stu_id = new_id;
    strcpy(newNode->stu_name, new_name);

    newNode->link = next;
    curr->link = newNode;

    //consider the begin or end
    if(curr != stuPos)
    {
        newNode->back = curr;
    }
    else
    {
        newNode->back = NULL;
    }
    //consider the begin or end
    if(next != NULL)
    {
        next->back = newNode;
    }
    else
    {
        stuPos->back = newNode;
    }

    return;
}

//free the double linked list
void FreeDoubleLink(stuNode* stuPos)
{
    while(stuPos != NULL)
    {
        printf("......free stu_id==[%d] success......\n", stuPos->stu_id);
        free(stuPos);
        stuPos = stuPos->link;
    }
    stuPos = NULL;

    return;
}

//double Linked List
int TestDoubleLink()
{
    printf("\n------in TestDoubleLink-----\n");
    stuNode *root = NULL;
    stuNode stuRoot;
    root = &stuRoot;
    PrintLinkedList(root);
    PrintLinkedList(root->link);

    //insert data into linked list
    InsDoubleLink(root, 1003, "Nina");
    PrintLinkedList(root->link);
    PrintLinkedList(root->back, 0);
    InsDoubleLink(root, 1001, "Jack");
    PrintLinkedList(root->link);
    PrintLinkedList(root->back, 0);
    InsDoubleLink(root, 1010, "Rose");
    PrintLinkedList(root->link);
    PrintLinkedList(root->back, 0);
    InsDoubleLink(root, 1006, "Smith");
    PrintLinkedList(root->link);
    PrintLinkedList(root->back, 0);
    InsDoubleLink(root, 1018, "Neo");
    PrintLinkedList(root->link);
    PrintLinkedList(root->back, 0);
    InsDoubleLink(root, 1006, "Jason");
    PrintLinkedList(root->link);
    PrintLinkedList(root->back, 0);

    //free the memory
    FreeLinkedList(root->link);

    printf("------out TestDoubleLink-----\n");

    return 0;
}


//const character string
int TestConstStr()
{
    {
        cout<<"(xyz)=="<<"xyz"<<endl;
        cout<<"*(xyz)=="<<*"xyz"<<endl;
        cout<<"(xyz+1)=="<<("xyz"+1)<<endl;
        cout<<"*(xyz+1)=="<<*("xyz"+1)<<endl;
        cout<<"xyz[2]=="<<"xyz"[2]<<endl;
//        cout<<"*(xyz+4)=="<<*("xyz"+4)<<endl;
    }
    int i=1, n=0;
    for(; i<=10; i++)
    {
        n = i;
        n %=10;
        cout<<"**********" + 10-n<<endl;
    }

    return 0;
}

#define PRINT(FORMAT, VALUE) printf("The value of "#VALUE " is " FORMAT "\n", VALUE)
#define ADD_TO_SUM(sum_number, value) sum ## sum_number += value
int TestDefine()
{
#pragma message("compile TestDefine")
    printf("%s:%d\n", __FILE__, __LINE__);
//#line 888 "xxx.cpp"
    printf("%s:%d\n", __FILE__, __LINE__);
    int sum5 = 10;
    PRINT("%d", sum5);//The value of sum5 is 10
#ifdef ADD_TO_SUM
    ADD_TO_SUM(5, 20);//sum5 += value
#else
#error No define ADD_TO_SUM
#endif
    PRINT("%d", sum5);//The value of sum5 is 30

    return 0;
}

//C I/O BUFFER
int TestIOBuffer()
{
    FILE *fp;
    fp = tmpfile();
    sleep(5);
    fclose(fp);
    char *pointer = tmpnam(NULL);
    printf ("Tempname #2: %s\n",pointer);
    char buffer[L_tmpnam];
    tmpnam(buffer);
    printf("Tempname #1: %s\n",buffer);
    return 0;
}

int TestForkBuffer()
{
    int i=0;
    for(; i<2; i++)
    {
        fork();
        printf("+ ");
//        fflush(stdout);// 6 +
    }
    fflush(stdout);//8 +
    sleep(10);
    return 0;
}

int ts_comp(const void* a, const void *b)
{
    return strcmp(((stuNode*)a)->stu_name, ((stuNode*)b)->stu_name);
}

int in_comp(const void* a, const void *b)
{
    return ((stuNode*)a)->stu_id >= ((stuNode*)b)->stu_id;
}

int TestCharStr()
{
    char s1[100];
    memset(s1, '\0', sizeof(s1));
    strcpy(s1, "love China 2010...");
    char *pch = s1;
    printf("---pch==[%s]\n", pch);
    while(*pch != '\0')
    {
        printf("%c|", *pch);
        pch++;
    }
    printf("\n---pch==[%s]\n", pch);
    assert(pch != NULL);//for test assert

    int i=1, j=1, n=0;
    n = (++i)*(++i);
    printf("+++i==[%d], n==[%d]\n", i, n);
    n = (j++)*(j++);
    printf("+++j==[%d], n==[%d]\n", j, n);

    //qsort
    stuNode stuRec[5];
    stuRec[0].stu_id=398;
    strcpy(stuRec[0].stu_name, "changxx");
    stuRec[1].stu_id=263;
    strcpy(stuRec[1].stu_name, "liyy");
    stuRec[2].stu_id=689;
    strcpy(stuRec[2].stu_name, "dongkk");
    stuRec[3].stu_id=101;
    strcpy(stuRec[3].stu_name, "xiazz");
    stuRec[4].stu_id=560;
    strcpy(stuRec[4].stu_name, "heio");
    printf("++++++++before sort++++++++++\n");
    int ai=0;
    for(; ai<5; ai++)
    {
        printf("---stu_id==[%d], stu_name==[%s]\n", stuRec[ai].stu_id, stuRec[ai].stu_name);
    }
    qsort(stuRec, 5, sizeof(stuNode), ts_comp);
    printf("\n++++++++after sort by name++++++++++\n");
    ai=0;
    for(; ai<5; ai++)
    {
        printf("---stu_id==[%d], stu_name==[%s]\n", stuRec[ai].stu_id, stuRec[ai].stu_name);
    }
    qsort(stuRec, 5, sizeof(stuNode), in_comp);
    printf("\n++++++++after sort by id++++++++++\n");
    ai=0;
    for(; ai<5; ai++)
    {
        printf("---stu_id==[%d], stu_name==[%s]\n", stuRec[ai].stu_id, stuRec[ai].stu_name);
    }

    return 0;
}

//class
int TestBalaValue()
{
    printf("-------in TestBalavalue---------\n");
    BalaValue b1("china", 100);
    printf("-------out TestBalavalue---------\n");

    return 0;
}

typedef vector<string> BalaVector;
static int GetDataBySplit(const char *strSource, BalaVector &balaVecInfo, const char *SPLIT_STR)
{
    printf("in GetDataBySplit, strSource==[%s]\n", strSource);

    balaVecInfo.clear();
    char *pVec = NULL;
    char strInfo[2560+1];
    memset(strInfo, '\0', sizeof(strInfo));
    strncpy(strInfo, strSource, sizeof(strInfo)-1);
    char *strPos = strInfo;

    unsigned int inum = 0;
    while((pVec = strstr(strPos, SPLIT_STR)) != NULL)
    {
        *pVec = '\0';
        balaVecInfo.push_back(string(strPos));
        strPos = pVec + strlen(SPLIT_STR);
        inum++;
    }
    pVec = NULL;
    if(strlen(strPos) != 0)
    {
        balaVecInfo.push_back(string(strPos));
    }
    printf("---------inum==%d\n", inum);

    BalaVector::iterator varit;
    for(varit = balaVecInfo.begin(); varit != balaVecInfo.end(); varit++)
    {
        printf("Get varVal==[%s]\n", (*varit).c_str());
    }
    printf("out GetDataBySplit\n");

    return 0;
}

void TestYuanlya()
{
    int i,j;
    int k=3;
    for(i=0;i<k;i++)
    {
        for(j=0;j<k-1-i;j++){
            printf(" ");
        }
        for(j=k-1-i;j<i+k;j++){
            printf("*");
        }
        printf("\n");
    }
    return;
}

void TestWangyfe()
{
    int n=5;
    {int i,j;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=2*(n-i);j++)printf(" "); 
            for(j=1;j<=2*i-1;j++)printf("*");
            printf("\n");
        }
    }

    return;
}
void TestLvdd()
{
    int a=1,b;
    for(;a<=3;a++)
    {
        for(b=1;b<=20-a;b++)
        {
            printf(" ");
        }
        for(b=1;b<=2*a-1;b++)
        {
            printf("*");
        }
        printf("\n");
    }
    return;
}

//void TestWangyfe1();
#define PATH_MAX 2000
typedef enum tagWorkerRunStatus
{
    BO_WRS_INIT_START   = 0,        //初始启动状态
    BO_WRS_RUNNING_START,           //正常工作状态
    BO_WRS_NO_RUNNING,              //工作进程没有正常启动
    BO_WRS_DEAD,                    //工作进程处于僵死状态
    BO_WRS_TERMINATED               //工作进程已经停止运行
} TWorkerRunStatus;

//工作进程的内存结构
typedef struct tagWorkerProcShm
{
    char sWorkerName[255+1];            //工作进程的名称，一般填写资料生成、服务开通报文生成、竣工、BOSS资料同步等名字。由调度进程分配。
    unsigned int iWorkerId;             //工作进程的唯一编码，由调度进程分配。
//  TProcessId tProcessId;              //进程的ID。
    TWorkerRunStatus iRunStatus;        //    工作进程的运行状态。调度程序初始设置成BO_WRS_INIT_START，当工作进程正
                                        //常运行时，此状态工作进程会改成BO_WRS_RUNNING_START状态。
                                        //当调度程序发现工作进程工作不正常时，也会修改此值。
    int iRestartTimes;                  //重新启动的次数。

    time_t tStartupTime;                //启动时间。由调度进程分配。

    //执行情况
    unsigned long lSuccNum;             //成功执行的数量。
    unsigned long lErrNum;              //失败的数量。
    unsigned long lSleepTimes;          //空处理次数。

    struct tagExecInfo
    {
        time_t tExecTime;               //本次的处理时间。
        unsigned long lDealNum;         //本次的处理数量。
    }tExecInfo[3];                      //最后三次的执行时间和处理数量。

    time_t tLastUpdateTime;             //最后一次更新共享内存的时间。
    time_t tLastDataBeginDealTime;      //最后一次开始处理数据的时间，通过此时间可以知道工作进程是否锁表。

    bool bTerminateWorker;              //是否终止工作进程，由调度进程更新此值，工作进程根据此值判断是否中断工作进程。由调度进程分配。

    unsigned long iPhiMemSize;          //使用物理内存的大小，单位字节。
    unsigned long iPageMemSize;         //使用虚拟内存的大小，单位字节。
    unsigned long lUsedTime;            //使用CPU的时间长度。得到的是以纳秒为单位的数值。纳秒等于一秒的十亿分之一。

    char sCmd[PATH_MAX+1];              //工作进程的启动参数。由调度进程分配。

    char sWorkerDllName[PATH_MAX+1];    //工作函数对应的动态链接库名称。
    char sWorkerDllVersion[PATH_MAX+1]; //工作函数对应的动态链接库版本号。
    char sWorkerFullDir[PATH_MAX+1];    //工作函数对应的动态链接库路径。
    
    char sWorkerRunningInfo[1023+1];    //工作进程的当前运行信息。可参数可以用于检查当前进程的运行情况。
}TWorkerProcShm;

//调度进程的共享内存。
typedef struct tagDispatchProcShm
{
    unsigned int iShmSize;              //共享内存的大小。
    unsigned int iIdleProcessNum;       //空闲进程的数量。
    unsigned int iTotalProcessNum;      //总共进程的数量。
    unsigned long lTotalUsedMemory;     //总共使用的内存大小，此参数暂时不启用。

    unsigned int iStartupedWorkderNum;  //当前已经启动工作进程的数量。
    unsigned int iMaxWorkerProcNum;     //最大工作进程的数量。
    TWorkerProcShm tWorkerProcShm[1];   //所有的工作进程，1只是一个站位符。
}TDispatchProcShm;

typedef struct AAA
{
    int a[3];
    char b[10];
    long c;
}aaa;

typedef struct BBB
{
    int d;
    char e[20];
    aaa aaa1[1];
}bbb;

void TestArrayStruct()
{
    printf("---in TestArrayStruct---\n");

    TDispatchProcShm tps;
    tps.iShmSize = 512;
    tps.iMaxWorkerProcNum = 1000;

    unsigned int kk = 0;
    for(; kk<10; kk++)
    {
        printf("------kk1==[%d], iWorkId==[%d]\n", kk, tps.tWorkerProcShm[kk].iWorkerId);
    }

    bbb bbb1;
    bbb1.d = 10;
    kk = 0;
    for(; kk<10; kk++)
    {
        printf("------kk2==[%d], c==[%ld]\n", kk, bbb1.aaa1[kk].c);
    }
    printf("\n----bbb1.aaa1.c==[%ld]\n\n", bbb1.aaa1[3].c);

    aaa aaa2[3];
    kk = 0;
    for(; kk<10; kk++)
    {
        aaa2[kk].c=20;
        printf("------kk3==[%d], c==[%ld]\n", kk, aaa2[kk].c);
    }
    printf("\n-----aaa2.a6==[%d]\n\n", aaa2[0].a[0]);

    char sss[10];
    memset(sss, 0, sizeof(sss));
    strcpy(sss, "abcdefgh");
    printf("------sss==[%s], &sss==[%s], *sss==[%c], sss[0]==[%c]\n", sss, &sss, *sss, sss[0]);
    
    printf("---out TestArrayStruct---\n");
    return;
}

void TestCharPos1(const char *src, char *dest)
{
    memset(dest, '\0', 100);
    printf("...src==[%s]\n", src);
    strcpy(dest, src);
    return;
}

//临时测试函数
map<string, string> informClientMap;
int TestTemp(const char* puIn)
{
    printf("\n------ in TestTemp  ------\n");
    printf("----puIn==[%s]\n", puIn);
    informClientMap["ttt"] = "123";
    cout<<"---["<<informClientMap["ttt"]<<"],---["<<informClientMap["sss"]<<"]"<<endl;
    if(informClientMap["aaa"] == "")
        cout<<"aaa is null"<<endl;
    char dest[100];
    TestCharPos1(puIn, dest);
    printf("...dest==[%s]\n", dest);
    //    int kk = atoi("");
    //    printf("-------kk==[%d]\n", kk);
    //    kk = atoi(puIn);
    //    printf("-------kk==[%d]\n", kk);
    //BalaVector vvc;
    //GetDataBySplit(puIn, vvc, ",");
    //    int flag=0;
    //    flag=system(NULL);
    //    printf("-----exec system null, flag==[%d]\n", flag);
    //    flag=system("ls -l|wc -l");
    //    printf("-----exec system ls, flag==[%d]\n", flag);
    // printf("---------test lvdd's codes:\n");
    // TestLvdd();
    // printf("---------test yuanlya's codes:\n");
    // TestYuanlya();
    // printf("---------test wangyfe's codes:\n");
    // TestWangyfe();
    //TestArrayStruct();
    printf("\n------out TestTemp------\n\n");

    return 0;
}


extern "C" int ChinaValentine(const char* leaveDay)
{
    int leaveDays = atoi(leaveDay);
    int i=1;
    for(;i<=leaveDays; i++)
    {
        printf("Dear Sophie, when you leave %d day, I", i);
        int j=0;
        for(; j<i; j++)
            printf(" miss you ");
        printf("!\n");
    }

    return 0;
}


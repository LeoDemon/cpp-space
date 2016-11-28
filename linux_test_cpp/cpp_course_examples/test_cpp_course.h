/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_course.h
 *
 *    Description:  for test_cpp_course.cpp
 *
 *        Version:  1.0
 *        Created:  2012/5/6 20:02:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:  si-tech
 *
 * =====================================================================================
 */

#ifndef TEST_CPP_COURSE_H_
#define TEST_CPP_COURSE_H_

//引入头文件
#include "test_cpp_dll.h"
#include <assert.h>

//声明其他类型
//定义结构体四种方式:
//    1.先声明结构体类型，再定义结构体变量,如下即第1种方式
//    2.在声明结构体类型的同时定义结构体变量
//    3.直接定义结构体类型变量 很少，不建议使用
//    4.使用typedef，但现在按照第1种方式定义，也可以直接使用Student定义结构体变量，故可不需要使用typedef
struct Student
{
	int stu_id;
	char stu_name[20];
	float stu_score;
	int stu_count;
	Student *next;
};  //在;的前面如果加上stud1,stud2,即用的第2种方式定义

struct personInfo
{
	int stu_id;
	char stu_name[20];
	float stu_score;
	int stu_count;
	personInfo *next;

	personInfo()
	{
		stu_id=0;
		memset(stu_name, '\0', sizeof(stu_name));
		stu_score = 0;
		stu_count = 0;
		next = NULL;
	}

	personInfo(const struct personInfo &psIn)
	{
		stu_id=psIn.stu_id;
		strcpy(stu_name, psIn.stu_name);
		stu_score = psIn.stu_score;
		stu_count = psIn.stu_count;
		next = psIn.next;
	}
};

//第4种方式，有3种不同的写法如下:
/*
 * (1) 不能定义结构体本身的类型变量
 typedef struct
 {
 int stu_id;
 char stu_name[20];
 float stu_score;
 int stu_count;
 Student *next; //错误，Student还不存在,不能缺少结构体名
 }Student;
 (2)
 struct STUDENT
 {
 int stu_id;
 char stu_name[20];
 float stu_score;
 int stu_count;
 STUDENT *next;
 };
 typedef struct STUDENT Student;
 (3)
 typedef struct STUDENT
 {
 int stu_id;
 char stu_name[20];
 float stu_score;
 int stu_count;
 struct STUDENT *next;//不加struct也是可行的
 }Student;
 */

class PerInfo
{
	public:
		int stu_id;
		char stu_name[20];
		float stu_score;
		int stu_count;
		personInfo *next;

	public:
		PerInfo()
		{
			stu_id=0;
			memset(stu_name, '\0', sizeof(stu_name));
			stu_score = 0;
			stu_count = 0;
			next = NULL;
		}

		PerInfo(const PerInfo &psIn)
		{
			stu_id=psIn.stu_id;
			strcpy(stu_name, psIn.stu_name);
			stu_score = psIn.stu_score;
			stu_count = psIn.stu_count;
			next = psIn.next;
		}

		PerInfo & TestPe1();
};

//String类
class String
{
	public:
		String(){p = NULL;}
		String(const char *str);
		friend bool operator > (String &str1, String &str2);
		friend bool operator < (String &str1, String &str2);
		friend bool operator == (String &str1, String &str2);
		void Display();
		~String()
		{
			cout<<"~String..."<<endl;
		}

	private:
		const char *p;
};

//类定义
class Time
{
	public:
		Time();
		Time(int h,int m,int s);
		void operator ++();//声明前置自增运算符++为成员函数
		void operator --();//声明前置自减运算符--为成员函数
		Time operator ++(int);//声明后置自增运算符++为成员函数,多一个int参数，只是为区分前置还是后置，无其他作用
		Time operator --(int);//声明后置自减运算符--为成员函数
		int SetTime();
		int GetTime();
		~Time()
		{
			cout<<"~Time()..."<<endl;
		}

	protected:
		int hour;
		int min;
		int sec;
};
//Time类的派生类TimeDer
class TimeDer:protected Time
{
	public:
		TimeDer();
		TimeDer(int h, int y, int s, int min, int month, int d, int tmh, int tmm, int tms, const char *str);
		TimeDer(int h, int y, int s, int min, int month, int d, const char *str);
		int SetTimeDer();
		int GetTimeDer();
		int TmDisplay();
		int StrDisplay();
		~TimeDer()
		{
			cout<<"~TimeDer()..."<<endl;
		}

	private:
		Time tm;	//子对象
		String Str1;//子对象
		int year;
		int month;
		int day;
};
//TimeDer类的派生类TimeGra
class TimeGra:public TimeDer //一个冒号，最后没有小括号
{
	public:
		TimeGra();
		TimeGra(int h, int y, int s, int min, int month, int d, int tmh, int tmm, int tms, const char *str, string country);
		int showall();
		~TimeGra()
		{
			cout<<"~TimeGra()..."<<endl;
		}

	private:
		string country;
};


//Box类声明，下面友元成员函数需要声明
//友元类一般不建议使用，因为破坏了C++的对象封装性
class Box;

class Array_max
{
	public:
		int SetValue();
		int MaxValue();
		int GetValue(Box &);
	private:
		int array[10];
		int maxnum;
};

class Box
{
	public:
		string boxname;
		//Box();
		//Box(char *,int,int,int);
		//一般不应同时使用构造函数的重载和有默认参数的构造函数
		Box(const string name="Box_Default",int h=10,int w=10,int l=10);
		int Volume();
		int Volume2() const;
		int Testpri();
		void SetBoxName(string);
		static float AverWidth();
		friend void FunCout2(const Box &);//声明为友元函数
		friend int Array_max::GetValue(Box &);
		~Box();
	private:
		static int count;//静态数据成员
		static int sumwidth;
		int height;
		int width;
		int length;
};//类声明结尾要有分号

//复数类Complex
class Complex
{
	public:
		Complex(){real=0;imag=0;}
		Complex(double r, double i){real=r; imag=i;}
		//转换构造函数，double->Complex
		Complex(double r){real=r; imag=0;}
		//类型转换函数，Complex->double，下面两行不能同时存在，否则出现二义性
		operator double(){return this->real;}
		//friend Complex operator +(Complex c1, Complex c2);//TestCourse109中不能使用引用
		//Complex operator +(Complex &c);
		friend Complex operator +(int &i, Complex &c2);
		friend Complex operator +(Complex &c2, int &i);
		//只能作为友元函数，返回类型和第一个参数必须为ostream类型，保证cout可以连续输出
		friend ostream & operator <<(ostream&, Complex&);
		friend istream & operator >>(istream&, Complex&);
		void Display();

	private:
		double real;
		double imag;
};


//人(People)类
class People
{
	public:
		People()
		{
			this->name = "";
			this->iccid = "";
		}
		People(string name, string iccid)
		{
			this->name = name;
			this->iccid = iccid;
		}
		//声明为virtual，派生类都为虚函数，派生类函数声明时可以加virtual，也可以不加
		virtual void Display()
		{
			cout<<"People.name=="<<this->name<<endl;
			cout<<"iccid=="<<this->iccid<<endl;
		}
		virtual ~People()
		{
			cout<<"~People..."<<endl;
		}

	public:
		string  name;	//姓名
		string iccid;	//身份证
};

//教师(Teacher)类
class Teacher:virtual public People
{
	public:
		Teacher();
		Teacher(string name,string iccid, size_t age, string title);
		virtual void Display();
		~Teacher()
		{
			cout<<"~Teacher..."<<endl;
		}

	protected:
		string name;	//姓名
		size_t age;		//年龄
		string title;	//职称
};

//学生(StuDent)类
class StuDent:virtual public People
{
	public:
		StuDent();
		StuDent(string name, string iccid, char sex, float score);
		virtual void Display();
		~StuDent()
		{
			cout<<"~StuDent..."<<endl;
		}

	protected:
		string name;	//姓名
		char sex;		//性别
		float score;	//成绩
};

//研究生(Graduate)类
class Graduate:public Teacher, public StuDent
{
	public:
		Graduate();
		Graduate(string name, string iccid, size_t age, string title, char sex, float score, float wage);
		void Display();		//不加virtual,默认就是继承下来的
		~Graduate()
		{
			cout<<"~Graduate..."<<endl;
		}

	private:
		float wage;		//津贴
};


//形状(Shape)类	    抽象类
class Shape
{
	public:
		virtual void ShapeName() const = 0;		//定义为纯虚函数
		virtual float Area() const {return 0.0;}
		virtual float Volume() const {return 0.0;}
};

//点(Point)类
class Point:public Shape
{
	public:
		Point(float x=0, float y=0);	//有默认参数的构造函数
		void SetPoint(float, float);
		float GetX() const
		{
			return this->x;
		}
		float GetY() const
		{
			return this->y;
		}
		friend ostream & operator << (ostream &, Point &);
		virtual void ShapeName() const 
		{
			cout<<"Point: ";
		}
		//virtual float Area() const = 0; 这里如果定义为纯虚函数，定义Point对象时将会编译报错

	protected:
		float x;	//横坐标
		float y;	//纵坐标
};

//圆(Circle)类
class Circle:public Point
{
	public:
		Circle(float x=0, float y=0, float r=0);
		void SetRadius(float);
		float GetRadius() const;
		float Area() const;			//求圆的面积
		friend ostream & operator <<(ostream &, Circle &);
		virtual void ShapeName() const 
		{
			cout<<"Circle: ";
		}

	private:
		float radius;
};

//圆柱体(Cylinder)类
class Cylinder:public Circle
{
	public:
		Cylinder(float x=0, float y=0, float r=0, float h=0);
		void SetHeight(float);
		float GetHeight() const;
		float Area() const;
		float Volume() const;
		friend ostream & operator << (ostream &, const Cylinder &);
		virtual void ShapeName() const 
		{
			cout<<"Cylinder: ";
		}

	protected:
		float height;

};

//bala class
class BalaValue
{
  public:
    BalaValue(string value, int flag)
    {
        cout<<"---in BalaValue---"<<endl;
        this->value = value;
        this->flag = flag;
    }
    ~BalaValue()
    {
        cout<<"~~~~~~~~~~in ~BalaValue()----"<<endl;
        cout<<"---value=="<<this->value<<endl;
        cout<<"---flag=="<<this->flag<<endl;
        this->value = "";
        this->flag = 0;
        cout<<"---value=="<<this->value<<endl;
        cout<<"---flag=="<<this->flag<<endl;
        cout<<"~~~~~~~~~~out ~BalaValue()----"<<endl;
    }

  private:
    string value;
    int flag;
};


//模板类
template <class uType>
class CompareAll
{
	public:
		//类模板内定义成员函数和构造函数
		/* 		CompareAll(uType x, uType y){this->x=x; this->y=y;}
		 * 		uType max(){return x>y?x:y;}
		 * 		uType min(){return x<y?x:y;}
		 */
		CompareAll(uType x, uType y);
		uType max();
		uType min();

	private:
		uType x, y;
};


//函数声明
int TestCourse132();
int TestCourse133();
int TestCourse138();
int TestCourse1310();
int SaveToFile(char *);
int GetFromFile(char *,char *);
int TestCourse1313();
int printStu(Student &);
int printStuPoint(Student *);
int TestCourse611();
int TestCourse613();
int TestCourse1315();
int TestCourse614();
int FuncTest(const int *);
int TestCourse83();
int TestCourse84();
int TestCourse92to6();
void FunCout(const Box *);//void FunCout(const Box *); 将类定义放到了前面，这里用到了类Box
void FunCout2(const Box &);//常引用
int TestCourse102();
int TestCourse104();
int TestCourse109();
int TestCourse914();
int TestCourse111();
int TestCourse118();
void Compare(String &str1, String &str2);
void TeaFunc(Teacher &t);
extern "C" int TestCourse121();
extern "C" int TestTemp(const char*);
extern "C" int TestBitCalc(const char*);
int TestUnionStruct(const char*);
int TestSimpleLinkedList(const char* puIn);


#endif //TEST_CPP_COURSE_H_


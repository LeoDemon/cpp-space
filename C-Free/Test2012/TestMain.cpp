#include "test.h"
#include "head1.h"
#include "head2.h"


int main(int argc, char *argv[])
{
	cout<<"Test2012 begin..."<<endl;

	//test c 
	//testSimple();	

	//test c++
	testCpp();	

	/*study utype*/
	testUtype();	
	
	//test namespace
	ns1::STUDENT stud1(101,"lijha",24);
	stud1.get_data();
	cout <<  "func(a,b)=" << ns1::func(6,3) << endl;

	ns2::STUDENT stud2(102,"wangff",'w');
	stud2.get_data();
	cout << "func(a,b)=" << ns2::func(6,3) << endl;

	//test try-catch
	testTryCatch();

	cout<<"Test2012 end..."<<endl;
	return 0;
}



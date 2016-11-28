/*
 * =====================================================================================
 *
 *       Filename:  head1.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/4/22 17:51:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "test.h"

namespace ns1
{

	class STUDENT
	{
		public:
			// ====================  LIFECYCLE     =======================================
			STUDENT (int n,string nam,int a)
			{
				num = n;
				name = nam;
				age = a;
			};                           /* constructor      */

			void get_data();

		protected:
			/* ====================  DATA MEMBERS  ======================================= */

		private:
			int num;
			string name;
			int age;
			/* ====================  DATA MEMBERS  ======================================= */

	}; 


	void STUDENT::get_data()
	{
		cout << "num=" << num << ", name=" << name << ", age="<< age << endl;
	}


	double func(double a, double b)
	{
		return sqrt(a+b);
	}

}

/*
 * =====================================================================================
 *
 *       Filename:  head2.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/4/22 18:09:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "test.h"

namespace ns2
{

	class STUDENT
	{
		public:
			// ====================  LIFECYCLE     =======================================
			STUDENT (int n,string nam,char s)
			{
				num = n;
				strcpy(name,nam.c_str());
				sex = s;
			};                           /* constructor      */

			void get_data();

		protected:
			/* ====================  DATA MEMBERS  ======================================= */

		private:
			int num;
			char name[20];
			char sex;
			/* ====================  DATA MEMBERS  ======================================= */

	}; 


	void STUDENT::get_data()
	{
		cout << "num=" << num << ", name=" << name << ", sex="<< sex << endl;
	}


	double func(double a, double b)
	{
		return sqrt(a-b);
	}

}


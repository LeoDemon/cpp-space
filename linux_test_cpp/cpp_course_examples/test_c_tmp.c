#include <stdio.h>

int CalcTest()
{
	int i = 0;
	for(i=0; i<10; i++)
		printf("--------i==%d\n", i*10);

	int x = 2;
	printf("calc==%d\n", 3*x*x-4*x+6);

	int nonzero_a = x != 0;
	int b = 3;
	if(nonzero_a == (b != 0))
	{
		printf("---This is true...nonzero_a==[%d]\n", nonzero_a);
	}

	//C语言中没有bool类型，下面一行语句编译报错
	//bool c = false;
	//printf("C语言没有bool类型，亲！\n");
	
	return 0;
}


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

	//C������û��bool���ͣ�����һ�������뱨��
	//bool c = false;
	//printf("C����û��bool���ͣ��ף�\n");
	
	return 0;
}


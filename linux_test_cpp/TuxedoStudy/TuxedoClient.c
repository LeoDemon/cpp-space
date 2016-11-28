#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atmi.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("argc is error\n");
		exit(1);
	}
	char *buf = NULL;
	long len = 0L;
	if(tpinit((TPINIT *)NULL) == -1)
	{
		printf("tpinit failed\n");
		exit(-1);
	}
	if((buf=tpalloc("STRING", NULL, 80))==NULL)
	{
		printf("tpalloc failed\n");
		tpterm();
		exit(-2);
	}
	strcpy(buf, argv[1]);
	if(tpcall("TOUPPER", buf, 0, &buf, &len, 0) == -1)
	{
		printf("service request failed\n");
		tpfree(buf);
		tpterm();
		exit(-3);
	}

	printf("return string == [%s]\n", buf);
	tpfree(buf);
	tpterm();

	return 0;
}


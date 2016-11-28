#include <stdio.h>
#include <ctype.h>
#include "atmi.h"

void TOUPPER(TPSVCINFO *rqst)
{
	printf("-----in TOUPPER-----\n");
	int i=0;
	for(; i<rqst->len-1; i++)
	{
		rqst->data[i] = toupper(rqst->data[i]);
	}

	tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}


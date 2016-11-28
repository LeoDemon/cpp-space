#include "hash.h"
#include <stdio.h>

int main(void)
{
     HashTable hashTable;
     createHashTable(&hashTable, 5);
     printf("sizeof hashTable is %d\n", sizeof(hashTable.elem));

     HashElem a, b, c, d, e;
     a.key="a";
     a.data="adata";
     a.next=NULL;

     b.key="b";
     b.data="bdata";
     b.next=NULL;

     c.key="c";
     c.data="cdata";
     c.next=NULL;

     d.key="d";
     d.data="ddata";
     d.next=NULL;

     e.key="e";
     e.data="edata";
     e.next=NULL;

     printf("insert a\n");
     insertHashTable(&hashTable, &a);

     printf("insert b\n");
     insertHashTable(&hashTable, &b);
     
     printf("insert c\n");
     insertHashTable(&hashTable, &c);
     
     printf("insert d\n");
     insertHashTable(&hashTable, &d);
     
     printf("insert e\n");
     insertHashTable(&hashTable, &e);

     searchHashTable(&hashTable, "a");

     searchHashTable(&hashTable, "c");

     searchHashTable(&hashTable, "d");

     /* destoryHashTable(&hashTable); */
     
     return 0;
}

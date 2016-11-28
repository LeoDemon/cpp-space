#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/shm.h>
#include "hash.h"

static unsigned long hashAlgorithm(const char *c);


#ifdef MALLOC
void createHashTable(HashTable *hashTable, const int size)
{
     hashTable->elem=(HashElem*)malloc(sizeof(HashElem)*size);
          
     if(hashTable->elem==NULL)
     {
          printf("createHashTable failure!\n");
          exit(1);
     }
     memset(hashTable->elem, '\0', sizeof(HashElem)*size);
     
     hashTable->count = 0;
     hashTable->size = size;
}
#else
void createHashTable(HashTable *hashTable, const int size, char *proj)
{    int shmid;
     shmid=shmget(IPC_PRIVATE, sizeof(HashElem)*size, IPC_CREAT|IPC_EXCL|0600);
     if(shmid==-1)
     {
          perror("shmget");
          exit(1);
     }
     
     hashTable->elem=(HashElem*)shmat(shmid, NULL, 0600);
     if(hashTable->elem==(HashElem *)SHM_FAILED)
     {
          perror("shmat");
          exit(1);
     }
     
     memset(hashTable->elem, '\0', sizeof(HashElem)*size); 
     hashTable->count=0;
     hashTable->size=size;

     FILE *fp=NULL;
     fp=fopen(proj, "w");
     if(fp==NULL)
     {
          perror("fopen");
          exit(1);
     }
     fprintf(fp, "%d\n", shmid);
     fclose(fp);
}
#endif            
     

void insertHashTable(HashTable *hashTable, HashElem *elem)
{
     int id=0;

     id=(int)hashAlgorithm(elem->key)%hashTable->size;

#ifdef DEBUG
     printf("\n%s , %d\n", __FILE__, __LINE__);
     printf("insertHashTable: id is %d\n", id);
#endif
     
     elem->next=hashTable->elem[id].next;
     hashTable->elem[id].next=elem;
     hashTable->count++;   
}

HashElem* searchHashTable(const HashTable *hashTable, const char *key)
{
     int id=0;
     id=(int)hashAlgorithm(key)%hashTable->size;

     if(hashTable->elem[id].next==NULL)
     {
          return NULL;
     }
     else
     {
          return hashTable->elem[id].next;
     }
}

#ifdef MALLOC
void destoryHashTable(HashTable *hashTable)
{

     free(hashTable->elem);
}
#else
void destoryHashTable(HashTable *hashTable, char *proj)
{
     FILE *fp=NULL;
     char buf[10]="";
     
     if(shmdt(hashTable->elem)==-1)
     {
          perror("shmdt");
          exit(1);
     }
     
     
     fp=fopen(proj, "r");
     if(fp==NULL)
     {
          perror("fopen");
          exit(1);
     }
     
     fgets(buf, sizeof(buf), fp);
     
     if(shmctl(atoi(buf), IPC_RMID, NULL)==-1)
     {
          perror("shmctl");
          exit(1);
     }
     fclose(fp);
     unlink(proj);
}
#endif

static unsigned long hashAlgorithm(const char *str) 
{ 

     unsigned  int  hash  =   0 ;
     unsigned  int  x     =   0 ;

     while  ( * str)
     {
          hash  =  (hash  <<   4 )  +  ( * str ++ );
          if  ((x  =  hash  &   0xF0000000L )  !=   0 )
          {
               hash  ^=  (x  >>   24 );
               hash  &=   ~ x;
          } 
     } 
 
     return  (hash  &   0x7FFFFFFF );

} 

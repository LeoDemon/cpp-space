#ifndef HASH_H_
#define HASH_H_
#define HASH_KEY_LENGTH 100
#define MALLOC

/* ��ϣ������Ԫ�ؽṹ */
struct hashElem
{
     char key[HASH_KEY_LENGTH];
     void *data;
     struct hashElem *next;
};
typedef struct hashElem HashElem;

/* ��ϣ��ṹ */
struct hashTable
{
     HashElem *elem;            /* ��ϣ������Ԫ�ش洢�׵�ַ������Ԫ��������̬���� */
     int count;                 /* ��ǰԪ���� */
     int size;                  /* ��ϣ������ */
};
typedef struct hashTable HashTable;

/* ��ʼ����ϣ�� */
#ifdef MALLOC
extern void createHashTable(HashTable *hashTable, const int size);
#else
extern void createHashTable(HashTable *hashTable, const int size, const char *proj);
#endif
/* �����ϣ�� */
extern void insertHashTable(HashTable *hashTable, HashElem *elem);

/* ������ϣ�� */
extern HashElem* searchHashTable(const HashTable *hashTable, const char *key);

/* ɾ����ϣ�� */
#ifdef MALLOC
extern void destoryHashTable(HashTable *hashTable);
#else
extern void destoryHashTable(HashTable *hashTable, const char *proj);
#endif
#endif

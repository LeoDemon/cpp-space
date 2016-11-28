#ifndef HASH_H_
#define HASH_H_
#define HASH_KEY_LENGTH 100
#define MALLOC

/* 哈希表数据元素结构 */
struct hashElem
{
     char key[HASH_KEY_LENGTH];
     void *data;
     struct hashElem *next;
};
typedef struct hashElem HashElem;

/* 哈希表结构 */
struct hashTable
{
     HashElem *elem;            /* 哈希表数据元素存储首地址，数据元素数量动态分配 */
     int count;                 /* 当前元素数 */
     int size;                  /* 哈希表容量 */
};
typedef struct hashTable HashTable;

/* 初始化哈希表 */
#ifdef MALLOC
extern void createHashTable(HashTable *hashTable, const int size);
#else
extern void createHashTable(HashTable *hashTable, const int size, const char *proj);
#endif
/* 构造哈希表 */
extern void insertHashTable(HashTable *hashTable, HashElem *elem);

/* 检索哈希表 */
extern HashElem* searchHashTable(const HashTable *hashTable, const char *key);

/* 删除哈希表 */
#ifdef MALLOC
extern void destoryHashTable(HashTable *hashTable);
#else
extern void destoryHashTable(HashTable *hashTable, const char *proj);
#endif
#endif

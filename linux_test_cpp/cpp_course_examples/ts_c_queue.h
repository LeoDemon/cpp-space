/*
 * =====================================================================================
 *
 *       Filename:  ts_c_queue.h
 *
 *    Description:  the header of ts_c_queue.c
 *
 *        Version:  1.0
 *        Created:  2014年10月04日 09时37分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LeoDemon
 *   Organization:  leo-open-free
 *
 * =====================================================================================
 */
#ifndef _TS_C_QUEUE
#define _TS_C_QUEUE

//define a struct Queue type
struct QUEUE_NODE
{
    int queue_id;
    char queue_name[32];
    struct QUEUE_NODE *next;
//    void QueueClean();
};
typedef struct QUEUE_NODE QUEUE_TYPE;

//init function
//void QueueClean()
//{
//    Queue_id = 0;
//    memset(Queue_name, '\0', sizeof(Queue_name));
//    next = NULL;
//}

#ifdef _CPLUSPLUS_
extern "C"{
#endif //_CPLUSPLUS_

//Dispaly Queue struct
void QueueDisplay(QUEUE_TYPE *);

//static array Queue push function
void staticInsert(QUEUE_TYPE *);

//static array Queue pop function
void staticDelete();

//static array Queue top function
void staticFirst(QUEUE_TYPE **);

//static array Queue empty check function
int isStaticEmpty();

//static array Queue full check function
int isStaticFull();

#ifdef _CPLUSPLUS_
}
#endif //_CPLUSPLUS_

#endif    //_TS_C_QUEUE


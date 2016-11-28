/*
 * =====================================================================================
 *
 *       Filename:  ts_c_queue.c
 *
 *    Description:  for learning C-queue
 *
 *        Version:  1.0
 *        Created:  2014年10月04日 09时55分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LeoDemon
 *   Organization:  leo-open-free
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ts_c_queue.h"

#define QUEUE_SIZE 30
#define QUEUE_STATIC_SIZE (QUEUE_SIZE + 1)
static QUEUE_TYPE staticArr[QUEUE_STATIC_SIZE];
static size_t front = 1;
static size_t rear = 0;

//static QUEUE_TYPE *queueDynPos = NULL;
//static size_t queueDynSize = 0;
//static QUEUE_TYPE *queueLink = NULL;

//display
void queueDisplay(QUEUE_TYPE *queuePos)
{
    printf("------queuePos->queue_id==[%d], queuePos->queue_name==[%s]\n",
            queuePos->queue_id, queuePos->queue_name);
}

//static array queue push function
void staticInsert(QUEUE_TYPE *value)
{
    assert(!isStaticFull());
    rear = (rear + 1) % QUEUE_STATIC_SIZE;
    staticArr[rear] = *value;

    return;
}

//static array queue pop function
void staticDelete()
{
    assert(!isStaticEmpty());
    memset(&staticArr[front], '\0', sizeof(QUEUE_TYPE));
    front = (front+1) % QUEUE_STATIC_SIZE;

    return;
}

//static array queue top function
void staticFirst(QUEUE_TYPE **queuePos)
{
    assert(!isStaticEmpty());
    *queuePos = &staticArr[front];

    return;
}

//static array queue empty check function
int isStaticEmpty()
{
    if((rear + 1) % QUEUE_STATIC_SIZE == front)
    {
        return 1;
    }
    return 0;
}

//static array queue full check function
int isStaticFull()
{
    if((rear + 2) % QUEUE_STATIC_SIZE == front)
    {
        return 1;
    }
    return 0;
}

//static queue function
int TsStaticQueue()
{
    printf("++++++++++front==[%d], rear==[%d]\n", (int)front, (int)rear);
    QUEUE_TYPE queInfo;
    int i=0;
    for(; i<30; i++)
    {
        memset(&queInfo, '\0', sizeof(QUEUE_TYPE));
        queInfo.queue_id = 3000+i+1;
        sprintf(queInfo.queue_name, "%s_%d", "uQueue", i+1);
        staticInsert(&queInfo);
    }
    printf("++++++++++front==[%d], rear==[%d]\n", (int)front, (int)rear);
    QUEUE_TYPE *quePos = NULL;
    printf("------the first data: ");
    staticFirst(&quePos);
    queueDisplay(quePos);
    printf("------after delete, the first data: ");
    staticDelete();
    staticFirst(&quePos);
    queueDisplay(quePos);
    for(i=0;i<20;i++)
    {
        staticDelete();
    }
    printf("++++++++++front==[%d], rear==[%d]\n", (int)front, (int)rear);
    printf("------after delete 20 times, the first data: ");
    staticFirst(&quePos);
    queueDisplay(quePos);
    for(i=0; i<10; i++)
    {
        memset(&queInfo, '\0', sizeof(QUEUE_TYPE));
        queInfo.queue_id = 8800+i*10+i;
        sprintf(queInfo.queue_name, "%s_%d", "new_Queue", i*10+i);
        staticInsert(&queInfo);
    }
    printf("++++++++++front==[%d], rear==[%d]\n", (int)front, (int)rear);
    printf("------after insert 3 times, the first data: ");
    staticFirst(&quePos);
    queueDisplay(quePos);
    //traversal the queue
    for(i=0; i<QUEUE_STATIC_SIZE; i++)
    {
        queueDisplay(&staticArr[i]);
    }
    return 0;
}

//test queue
int queueFunc()
{
    printf("==========Hello, queueFunc!\n");
    TsStaticQueue();
    printf("==========Bye, queueFunc!\n");
    return 0;
}


/*
 * =====================================================================================
 *
 *       Filename:  ts_c_stack.c
 *
 *    Description:  for learning C-stack
 *
 *        Version:  1.0
 *        Created:  2014年09月02日 16时55分06秒
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

#include "ts_c_stack.h"

#define STACK_STATIC_SIZE 20
static STACK_TYPE staticArr[STACK_STATIC_SIZE];
static int topElement = -1;

static STACK_TYPE *stackDynPos = NULL;
static size_t stackDynSize = 0;
static STACK_TYPE *stackLink = NULL;

//display
void stackDisplay(STACK_TYPE *stackPos)
{
    printf("------stackPos->stack_id==[%d], stackPos->stack_name==[%s]\n",
           stackPos->stack_id, stackPos->stack_name);
}

//static array stack push function
void staticPush(STACK_TYPE *value)
{
    assert(!staticFull());
    topElement += 1;
    staticArr[topElement] = *value;

    return;
}

//static array stack pop function
void staticPop()
{
    assert(!staticEmpty());
    memset(&staticArr[topElement], '\0', sizeof(STACK_TYPE));
    topElement -= 1;

    return;
}

//static array stack top function
void staticTop(STACK_TYPE **stackPos)
{
    assert(!staticEmpty());
    *stackPos = &staticArr[topElement];

    return;
}

//static array stack empty check function
int staticEmpty()
{
    if(topElement == -1)
    {
        return 1;
    }
    return 0;
}

//static array stack full check function
int staticFull()
{
    if(topElement == STACK_STATIC_SIZE -1)
    {
        return 1;
    }
    return 0;
}

//create dynamic array
void dynamicCreate(size_t size)
{
    assert( stackDynSize == 0 );
    stackDynPos = malloc(size * sizeof(STACK_TYPE));
    assert(stackDynPos != NULL);
    stackDynSize = size;
}

//create dynamic array
void dynamicDestory()
{
    assert(stackDynSize > 0);
    stackDynSize = 0;
    free(stackDynPos);
    stackDynPos = NULL;
}

//dynamic array stack push function
void dynamicPush(STACK_TYPE *value)
{
    assert(!dynamicFull());
    topElement += 1;
    stackDynPos[topElement] = *value;
}

//dynamic array stack pop function
void dynamicPop()
{
    assert(!dynamicEmpty());
    memset(&stackDynPos[topElement], '\0', sizeof(STACK_TYPE));
    topElement -= 1;
}

//dynamic array stack top function
void dynamicTop(STACK_TYPE **value)
{
    assert(!dynamicEmpty());
    *value = &stackDynPos[topElement];
}

//dynamic array stack empty check function
int dynamicEmpty()
{
    assert(stackDynSize > 0);
    if(topElement == - 1)
    {
        return 1;
    }
    return 0;
}

//dynamic array stack full check function
int dynamicFull()
{
    assert(stackDynSize > 0);
    if(topElement == stackDynSize - 1)
    {
        return 1;
    }
    return 0;
}

//linked stack push function
void linkedPush(STACK_TYPE *value)
{
    STACK_TYPE *newStack = malloc(sizeof(STACK_TYPE));
    assert(newStack != NULL);
    *newStack = *value;
    newStack->next = stackLink;
    stackLink = newStack;
}

//linked stack pop function
void linkedPop()
{
    assert(!linkedEmpty());
    STACK_TYPE *stackNode = stackLink;
    stackLink = stackLink->next;
    free(stackNode);
}

//linked stack top function
void linkedTop(STACK_TYPE **value)
{
    assert(!linkedEmpty());
    *value = stackLink;
}

//linked stack empty check function
int linkedEmpty()
{
    return stackLink == NULL;
}

//linked stack full check function
int linkedFull()
{
    return 0;
}

//destory the linked-stack
void linkedDestory()
{
    STACK_TYPE *stackNode = NULL;
    stackNode = stackLink;
    while(stackNode != NULL)
    {
        printf(".........free %d now......\n", stackNode->stack_id);
        free(stackNode);
        stackNode = stackNode->next;
    }
    stackLink = NULL;
}

//static stack function for test
int TsStaticStack()
{
    STACK_TYPE stackInfo;
    int i=0;
    printf("------topElement==[%d]\n", topElement);
    for(; i<20; i++)
    {
        memset(&stackInfo, '\0', sizeof(STACK_TYPE));
        stackInfo.stack_id=1000+i;
        sprintf(stackInfo.stack_name, "%s_%d", "iStack", i);
        staticPush(&stackInfo);
    }
    printf("------topElement==[%d]\n", topElement);
    STACK_TYPE *stackPos = NULL;
    printf("------The top data: ");
    staticTop(&stackPos);
    stackDisplay(stackPos);
    staticPop();
    printf("------After pop 1, The top data: ");
    staticTop(&stackPos);
    stackDisplay(stackPos);
    staticPop();
    printf("------After pop 2, The top data: ");
    staticTop(&stackPos);
    stackDisplay(stackPos);
    for(i=0; i<2; i++)
    {
        memset(&stackInfo, '\0', sizeof(STACK_TYPE));
        stackInfo.stack_id=1320+i;
        sprintf(stackInfo.stack_name, "%s_%d", "iCode", i);
        staticPush(&stackInfo);
    }
    printf("------After push, The top data: ");
    staticTop(&stackPos);
    stackDisplay(stackPos);
    for(i=0; i<8; i++)
    {
        staticPop();
    }
    printf("######After pop3, loop the stack: \n");
    for(i=0; i<=topElement; i++)
    {
        stackDisplay(&staticArr[i]);
    }
    printf("######list the stack: \n");
    for(i=0; i<STACK_STATIC_SIZE; i++)
    {
        stackDisplay(&staticArr[i]);
    }

    return 0;
}

//int TsErrRet()
//{
//    int x = 0;
//
//    int a=1, b=2;
//    x = a+b;
//    return;
//}

//create generic stack
GENERIC_STACK(int, _int, 20);
GENERIC_STACK(double, _double, 20);

//generic stack test function
int TestGenericStack()
{
    push_int(5);
    push_int(20);
    push_int(188);

    push_double(219.22);
    push_double(300.88);
    push_double(911.09);
    push_double(666.66);
    push_double(888.28);

    while(!is_empty_int())
    {
        printf("------stack_int, popping value is: [%d]\n", top_int());
        pop_int();
    }

    while(!is_empty_double()){
        printf("------stack_double, popping value is: [%f]\n", top_double());
        pop_double();
    }

    return 0;
}

//stack function for test
int TestStack()
{
    printf("\n@@@@@@@@@@@@@@@@@@@---in TestStack---@@@@@@@@@@@@@@@@@@@\n");
//    TsStaticStack();
//    TsDynStack();
//    TsLinkStack();
    TestGenericStack();
//    int x  = TsErrRet();
//    printf("-----------x==[%d]\n", x);
    printf("@@@@@@@@@@@@@@@@@@@---out TestStack---@@@@@@@@@@@@@@@@@@@\n");

    return 0;
}

//dynamic stack function for test
int TsDynStack()
{
    STACK_TYPE stackInfo;
    printf("------topElement==[%d]\n", topElement);
    dynamicCreate(STACK_STATIC_SIZE);
    int i=0;
    for(; i<STACK_STATIC_SIZE; i++)
    {
        memset(&stackInfo, '\0', sizeof(STACK_TYPE));
        stackInfo.stack_id=1800+i;
        sprintf(stackInfo.stack_name, "%s_%d", "dynamic", i);
        dynamicPush(&stackInfo);
    }
    printf("------topElement==[%d]\n", topElement);
    STACK_TYPE *stackPos = NULL;
    printf("------The top data: ");
    dynamicTop(&stackPos);
    stackDisplay(stackPos);
    dynamicPop();
    printf("------After pop 1, The top data: ");
    dynamicTop(&stackPos);
    stackDisplay(stackPos);
    dynamicPop();
    printf("------After pop 2, The top data: ");
    dynamicTop(&stackPos);
    stackDisplay(stackPos);
    for(i=0; i<5; i++)
    {
        dynamicPop();
    }
    for(i=0; i<3; i++)
    {
        memset(&stackInfo, '\0', sizeof(STACK_TYPE));
        stackInfo.stack_id=1920+i;
        sprintf(stackInfo.stack_name, "%s_%d", "iCode", i);
        dynamicPush(&stackInfo);
    }
    printf("------After push, The top data: ");
    dynamicTop(&stackPos);
    stackDisplay(stackPos);
    printf("######After pop3, loop the stack: \n");
    for(i=0; i<=topElement; i++)
    {
        stackDisplay(&stackDynPos[i]);
    }
    printf("######list the stack: \n");
    for(i=0; i<STACK_STATIC_SIZE; i++)
    {
        stackDisplay(&stackDynPos[i]);
    }
    dynamicDestory();

    return 0;
}

//link stack function for test
int TsLinkStack()
{
    STACK_TYPE stackInfo;
    int i=0;
    for(; i<STACK_STATIC_SIZE; i++)
    {
        memset(&stackInfo, '\0', sizeof(STACK_TYPE));
        stackInfo.stack_id=1800+i;
        sprintf(stackInfo.stack_name, "%s_%d", "linked", i);
        linkedPush(&stackInfo);
    }
    printf("******list the linked-stack data:\n");
    STACK_TYPE *staLinkPos = NULL;
    staLinkPos = stackLink;
    while(staLinkPos != NULL)
    {
        stackDisplay(staLinkPos);
        staLinkPos = staLinkPos->next;
    }
    printf("******get the top linked-stack data:\n");
    STACK_TYPE *stackLinkPos=NULL;
    linkedTop(&stackLinkPos);
    stackDisplay(stackLinkPos);
    stackDisplay(stackLink);
    printf("******after pop 1, get the top linked-stack data:\n");
    for(i=0; i<7; i++)
    {
        linkedPop();
    }
    stackDisplay(stackLink);
    linkedDestory();

    return 0;
}


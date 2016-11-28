/*
 * =====================================================================================
 *
 *       Filename:  ts_c_stack.h
 *
 *    Description:  the header of ts_c_stack.c
 *
 *        Version:  1.0
 *        Created:  2014年09月02日 16时57分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LeoDemon
 *   Organization:  leo-open-free
 *
 * =====================================================================================
 */
#ifndef _TS_C_STACK_
#define _TS_C_STACK_

//define a struct stack type
struct STACK_NODE
{
    int stack_id;
    char stack_name[32];
    struct STACK_NODE *next;
//    void StackClean();
};
typedef struct STACK_NODE STACK_TYPE;

//init function
//void StackClean()
//{
//    stack_id = 0;
//    memset(stack_name, '\0', sizeof(stack_name));
//    next = NULL;
//}

#ifdef _CPLUSPLUS_
extern "C"{
#endif //_CPLUSPLUS_

//Dispaly stack struct
void stackDisplay(STACK_TYPE *);

//static array stack push function
void staticPush(STACK_TYPE *);

//static array stack pop function
void staticPop();

//static array stack top function
void staticTop(STACK_TYPE **);

//static array stack empty check function
int staticEmpty();

//static array stack full check function
int staticFull();

//create dynamic array
void dynamicCreate(size_t size);

//create dynamic array
void dynamicDestory();

//dynamic array stack push function
void dynamicPush(STACK_TYPE *value);

//dynamic array stack pop function
void dynamicPop();

//dynamic array stack top function
void dynamicTop(STACK_TYPE **value);

//dynamic array stack empty check function
int dynamicEmpty();

//dynamic array stack full check function
int dynamicFull();

//linked stack push function
void linkedPush(STACK_TYPE *value);

//linked stack pop function
void linkedPop();

//linked stack top function
void linkedTop(STACK_TYPE **value);

//linked stack empty check function
int linkedEmpty();

//linked stack full check function
int linkedFull();

//destory linked-stack
void linkedDestory();

//test static stack function
int TsStaticStack();

//test dynamic stack function
int TsDynStack();

//test stack function
int TestStack();

//test stack function
int TsLinkStack();

#ifdef _CPLUSPLUS_
}
#endif //_CPLUSPLUS_

//a genericity stack by static array
#define GENERIC_STACK(STACK_TYPE, SUFFIX, STACK_SIZE) \
    static STACK_TYPE stack##SUFFIX[STACK_SIZE];\
    static int top_element##SUFFIX = -1;        \
                                                \
    int is_empty##SUFFIX(void)                  \
    {                                           \
        return top_element##SUFFIX == -1;       \
    }                                           \
                                                \
    int is_full##SUFFIX(void)                   \
    {                                           \
        return top_element##SUFFIX == STACK_SIZE -1;\
    }                                               \
                                                    \
    void push##SUFFIX(STACK_TYPE value)             \
    {                                               \
        assert(!is_full##SUFFIX());                 \
        top_element##SUFFIX += 1;                   \
            stack##SUFFIX[top_element##SUFFIX] = value; \
    }                                                   \
                                                        \
    void pop##SUFFIX(void)                              \
    {                                                   \
        assert(!is_empty##SUFFIX());                     \
        top_element##SUFFIX -= 1;                        \
    }                                                    \
                                                         \
    STACK_TYPE top##SUFFIX(void)                         \
    {                                                    \
        assert(!is_empty##SUFFIX());                     \
        return stack##SUFFIX[top_element##SUFFIX];       \
    }                                                    \

#endif    //_TS_C_STACK_


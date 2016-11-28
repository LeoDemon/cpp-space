/*
 * =====================================================================================
 *
 *       Filename:  ts_c_tree.c
 *
 *    Description:  learning c-tree
 *
 *        Version:  1.0
 *        Created:  2014年10月07日 17时12分51秒
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
#include "ts_c_tree.h"

//treeNode struct
typedef struct TREE_NODE
{
    TREE_TYPE value;
    struct TREE_NODE *left;
    struct TREE_NODE *right;
}TreeNode;

//a pointer to the tree's root
static TreeNode *rootPos=NULL;

//insert
void TreeInsert(TREE_TYPE value)
{
    TreeNode *curr;
    TreeNode **link;

    //from root pointer beginning
    link = &rootPos;

    //search the tree, find the address
    while((curr = *link) != NULL){
        if(value < curr->value){
            link = &curr->left;
        }else{
            assert(value != curr->value);
            link = &curr->right;
        }
    }

    //create a new node
    curr = (TreeNode*)malloc(sizeof(TreeNode));
    assert(curr != NULL);
    curr->value = value;
    curr->left = NULL;
    curr->right = NULL;
    *link = curr;
}

//recursion pre-order-traversal
void Pre_Order_Traversal(TreeNode *pos)
{
    if(pos != NULL)
    {
        printf("--->%d", pos->value);
        Pre_Order_Traversal(pos->left);
        Pre_Order_Traversal(pos->right);
    }
}

//recursion infix-order-traversal
void Infix_Order_Traversal(TreeNode *pos)
{
    if(pos != NULL){
        Infix_Order_Traversal(pos->left);
        printf("--->%d", pos->value);
        Infix_Order_Traversal(pos->right);
    }
}

//recursion suf-order-traversal
void Suf_Order_Traversal(TreeNode *pos)
{
    if(pos != NULL){
        Suf_Order_Traversal(pos->left);
        Suf_Order_Traversal(pos->right);
        printf("--->%d", pos->value);
    }
}

//find
TREE_TYPE *TreeFind(TREE_TYPE value)
{
    TreeNode *curr = rootPos;

    while(curr != NULL && curr->value != value){
        if(value < curr->value)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if(curr != NULL)
        return &curr->value;
    else
        return NULL;
}

//Test Function
int TestTreeFunc()
{
    printf("\n++++++++++in TestTreefunc++++++++++\n");
    int i = 100;
    for( ; i<103; i++)
        TreeInsert(i);
    for(i=60; i>57; i--)
        TreeInsert(i);
    for(i=70; i<73; i++)
        TreeInsert(i);

    //recursion traversal
    {
        printf("==============pre-order-traversal============\n");
        Pre_Order_Traversal(rootPos);
        printf("\n==============pre-order-traversal============\n");
    
        printf("==============infix-order-traversal============\n");
        Infix_Order_Traversal(rootPos);
        printf("\n==============infix-order-traversal============\n");

        printf("==============suf-order-traversal============\n");
        Suf_Order_Traversal(rootPos);
        printf("\n==============suf-order-traversal============\n");
    }

    TREE_TYPE *tpos = NULL;
    tpos = TreeFind(99);
    if(tpos == NULL)
        printf("--------sorry, can't find this node...\n");
    else
        printf("--------find it out...[%d]\n", *tpos);

    tpos = TreeFind(88);
    if(tpos == NULL)
        printf("--------sorry, can't find this node...\n");
    else
        printf("--------%d, find it success...\n", *tpos);

    printf("++++++++++out TestTreefunc++++++++++\n");

    return 0;
}


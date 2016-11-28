/*
 * =====================================================================================
 *
 *       Filename:  ts_c_tree.h
 *
 *    Description:  the header file of ts_c_tree.c
 *
 *        Version:  1.0
 *        Created:  2014年10月07日 16时55分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LeoDemon
 *   Organization:  leo-open-free
 *
 * =====================================================================================
 */
#ifndef _TS_C_TREE_
#define _TS_C_TREE_

//tree type
#define TREE_TYPE int

//insert a new value into tree
void TreeInsert(TREE_TYPE value);

//find a value from tree
TREE_TYPE *TreeFind(TREE_TYPE value);

//pre_order_traversel
void pre_order_traverse(void (*callback) (TREE_TYPE value));

#endif    //_TS_C_TREE_


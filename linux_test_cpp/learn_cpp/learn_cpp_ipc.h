/*
 * =====================================================================================
 *
 *       Filename:  learn_cpp_ipc.h
 *
 *    Description:  the head file of learn_cpp_ipc.cpp
 *
 *        Version:  1.0
 *        Created:  2015年01月11日 20时14分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LeoDemon
 *   Organization:  open-free
 *
 * =====================================================================================
 */
#ifndef _LEARN_CPP_IPC_
#define _LEARN_CPP_IPC_

#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <signal.h>
#include <map>
#include <vector>
typedef vector<string> IpcVec;

static int ForDataBySplit(const char *, IpcVec &, const char *);
extern "C" int TestIpcPipe(const char*, otl_connect*);
extern "C" int TestIpcPopen(const char*, otl_connect*);
extern "C" int TestIpcCopro(const char*, otl_connect*);
extern "C" int TestIpcFifoClient(const char* puIn, otl_connect *otlDB);
extern "C" int TestIpcFifoServ(const char* puIn, otl_connect *otlDB);
extern "C" int TestOtlMysql(const char*, otl_connect*);
extern "C" int TestIpcShmServ(const char*, otl_connect*);
extern "C" int TestIpcShmClient(const char*, otl_connect*);
extern "C" int TestMsgQueClient(const char*, otl_connect*);
extern "C" int TestMsgQueServ(const char*, otl_connect*);
extern "C" int TestForkMap(const char*, otl_connect*);

struct SHM_MSG_INFO
{
    int shm_iseq;
    char shm_msg[100];
};

struct SHM_TEXT
{
    int shm_tid;
    char shm_text[100];
    struct SHM_MSG_INFO shm_info[1];
};

struct MSG_MQ_INFO
{
    char text[1024];
    unsigned char sendFlag;
};

struct msg_st
{
    long int msg_type;
    char msg[1];
};

#define IPC_KEY_ID 0xABC
#define SHM_IPC_NAME "/home/leodemon/Study/workspace/space-for-study/cpp-space/public/learn_cpp_ipc.shm"
#define MQ_IPC_NAME "/home/leodemon/Study/workspace/space-for-study/cpp-space/public/learn_cpp_ipc.mq"
#define SEMA_IPC_NAME "/home/leodemon/Study/workspace/space-for-study/cpp-space/public/learn_cpp_ipc.sema"
#define FIFO_IPC_NAME "/home/leodemon/Study/workspace/space-for-study/cpp-space/public/learn_cpp_fifo.serv"
#define FIFO_IPC_CLIENT "/home/leodemon/Study/workspace/space-for-study/cpp-space/public/learn_cpp_fifo.cli"
#define FIFO_IPC_PATH "/home/leodemon/Study/workspace/space-for-study/cpp-space/linux_test_cpp/learn_cpp/"
#define SHM_SIZE 12306
#define IPC_AUTH 0644

#define SPLIT_ATTR "##"

#endif    //_LEARN_CPP_IPC_


/*
 * =====================================================================================
 *
 *       Filename:  learn_cpp_ipc.cpp
 *
 *    Description:  for unix-ipc
 *
 *        Version:  1.0
 *        Created:  2014年12月31日 17时39分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LeoDemon
 *   Organization:  open-free
 *
 * =====================================================================================
 */

#include "learn_cpp_main.h"
#include "learn_otl_pub.h"
#include "learn_cpp_ipc.h"
#define MAXLINE 1024 

int ForDataBySplit(const char *strSource, IpcVec &forIpcVector, const char *SPLIT_STR)
{
    LOG_DEBUG_FUNC;

    forIpcVector.clear();
    char *pVec = NULL;
    char strInfo[2560+1];
    memset(strInfo, '\0', sizeof(strInfo));
    strncpy(strInfo, strSource, sizeof(strInfo)-1);
    char *strPos = strInfo;

    while((pVec = strstr(strPos, SPLIT_STR)) != NULL)
    {
        *pVec = '\0';
        forIpcVector.push_back(string(strPos));
        strPos = pVec + strlen(SPLIT_STR);
    }
    pVec = NULL;
    if(strlen(strPos) != 0)
    {
        forIpcVector.push_back(string(strPos));
    }

#ifdef LOG_DEBUG
    printf("...strSource==[%s]\n", strSource);
    IpcVec::iterator varit;
    for(varit = forIpcVector.begin(); varit != forIpcVector.end(); varit++)
    {
        printf("Get varVal==[%s]\n", (*varit).c_str());
    }
#endif

    return 0;
}

//ipc---pipe
int TestIpcPipe(const char* puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;

    if(-1)
    {
        printf("------test -1 out...\n");
    }
    if(1)
    {
        printf("------test +1 out...\n");
    }
    if(0)
    {
        printf("------test 0 out...\n");
    }

    int n = 0;
    int fd[2];
    pid_t pid;

    if(pipe(fd) < 0)    //fd[0] for read, fd[1] for write
    {
        printf("------pipe error-----\n");
    }
    pid=fork();
    if(pid<0)
    {
        printf("------fork error-----\n");
    }
    else if(pid == 0)
    {
        close(fd[1]);
        printf("...child process [%d] begin...\n", getpid());
        char msg[MAXLINE];
        while(1)
        {
            memset(msg, '\0', sizeof(msg));    //clear
            n = read(fd[0], msg, MAXLINE);
            printf("----------msg==[%s], size==[%d]\n", msg, n);
            if(strcmp(msg, "quit") == 0)
                break;
        }
        printf("...child process [%d] end...\n", getpid());
        exit(6);
    }

    close(fd[0]);
    printf("...father process [%d] begin...\n", getpid());
    char scn[1000];
    memset(scn, '\0', sizeof(scn));
    sleep(1);
    printf("> ");
    while(fgets(scn, 1000, stdin) != NULL)
    {
        scn[strlen(scn) - 1] = '\0';    //erase the 'LF'
        n=write(fd[1], scn, strlen(scn));
        sleep(1);
        if(strcmp(scn, "quit") == 0)
            break;
        printf("> ");
        fflush(stdout);
        memset(scn, '\0', sizeof(scn));    //clear
    }
    printf("...father process [%d] end...\n", getpid());

    int status = 0;
    waitpid(-1, &status, 0);    //recover child process
    printf("...recover child process status==[%d]...\n", WEXITSTATUS(status));

    return 0;
}

//ipc---popen
int TestIpcPopen(const char* puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;
 
    FILE *fpin = NULL;
    char fmsg[MAXLINE];
    memset(fmsg, '\0', sizeof(fmsg));
    if((fpin=popen("./forpopen", "r")) == NULL)
        perror("popen error:");
    while(1)
    {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if(fgets(fmsg, MAXLINE, fpin) == NULL)
        {
            printf("...fpin is null...\n");
            break;
        }
        if(fputs(fmsg, stdout) == EOF)
            perror("popen fputs error:");
    }
    if(pclose(fpin) == -1)
        perror("pclose error:");

    return 0;
}

//deal SIGPIPE signal...
void DealSignPipe(int signo)
{
    printf("---catch SIGPIPE signal...signo==[%d]\n", signo);
    return;
}

//ipc---coprocess
int TestIpcCopro(const char* puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;
 
    int n, fdi[2], fdo[2];
    char fmsg[MAXLINE];
    memset(fmsg, '\0', sizeof(fmsg));

    if(signal(SIGPIPE, DealSignPipe) == SIG_ERR)
        perror("signal error:");
    if(pipe(fdi) < 0 || pipe(fdo) < 0)
        perror("pipe error:");
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error:");
    }
    else if(pid > 0)    //parent
    {
        printf("...parent process...\n");
        close(fdi[0]);
        close(fdo[1]);
        sleep(1);
        printf("prompt> ");
        fflush(stdout);
        while(fgets(fmsg, MAXLINE, stdin) != NULL)
        {
            n = strlen(fmsg);
            if(write(fdi[1], fmsg, n) != n)
                perror("write error: ");

            memset(fmsg, '\0', sizeof(fmsg));    //init for read
            if((n=read(fdo[0], fmsg, MAXLINE)) < 0)
                perror("read error: ");
            if(n == 0)
            {
                printf("...child process has closed pipe...\n");
                break;
            }
            if(fmsg[n-1] == '\n')
                fmsg[n-1] = '\0';
            printf("%s\n", fmsg);
            printf("prompt> ");
            fflush(stdout);
            memset(fmsg, '\0', sizeof(fmsg));    //init for gets
        }
        if(ferror(stdin))
            perror("fgets error: ");
        printf("...parent process end...\n");
    }
    else    //child
    {
        printf("...child process...\n");
        close(fdi[1]);
        close(fdo[0]);
        if(fdi[0] != STDIN_FILENO)
        {
            if(dup2(fdi[0], STDIN_FILENO) != STDIN_FILENO)
                perror("dup2 error to stdin: ");
            close(fdi[0]);
        }
        if(fdo[1] != STDOUT_FILENO)
        {
            if(dup2(fdo[1], STDOUT_FILENO) != STDOUT_FILENO)
                perror("dup2 error to stdout: ");
            close(fdo[1]);
        }
        if(execl("./forcopro", "forcopro", NULL) < 0)
            perror("execl error: ");
        printf("...child process end...\n");

        exit(0);
    }
    waitpid(-1, NULL, 0);

    return 0;
}

//ipc---FIFO client
int TestIpcFifoClient(const char* puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;

    char fifoName[MAXLINE];
    char buff[MAXLINE];
    memset(buff, '\0', sizeof(buff));
    memset(fifoName, '\0', sizeof(fifoName));

    //create client FIFO
    sprintf(fifoName, "%s%ld", FIFO_IPC_CLIENT, (long)getpid());
    unlink(fifoName);
    if(mkfifo(fifoName, IPC_AUTH) < 0 && (errno != EEXIST))
    {
        printf("...cannot creat %s...\n", fifoName);
    }

    //input by stdin
    //open server FIFO and write
    int wrtInfo = open(FIFO_IPC_NAME, O_WRONLY, 0);
    if(wrtInfo < 0)
    {
        printf("...cann't open server FIFO...\n");
        return -1;
    }
    int readInfo;
    char sBuffMsg[MAXLINE];
    printf("prompt> ");
    fflush(stdout);
    while(fgets(buff, MAXLINE, stdin) != NULL)
    {
        if(strlen(buff) > 0)
        {
            if(buff[strlen(buff) - 1]== '\n')
                buff[strlen(buff) - 1]= '\0';
 
            memset(sBuffMsg, '\0', sizeof(sBuffMsg));
            sprintf(sBuffMsg, "%ld#%s", (long)getpid(), buff);
            printf("...sBuffMsg==[%s]...\n", sBuffMsg);
            write(wrtInfo, sBuffMsg, strlen(sBuffMsg));
            if(strcmp(buff, "quit") == 0)
                break;

            memset(buff, '\0', sizeof(buff));
            //open client FIFO and read from server
            readInfo = open(fifoName, O_RDONLY, 0);
            if(readInfo < 0)
            {
                printf("...cann't open CLIENT FIFO...\n");
                return -1;
            }
            int n = 0;
            printf("replymsg> \n");
            while((n = read(readInfo, buff, MAXLINE)) > 0)
            {
                write(STDOUT_FILENO, buff, n);
            }
            close(readInfo);
        }
        printf("prompt> ");
        fflush(stdout);
    }

    //close
    close(readInfo);
    close(wrtInfo);
    unlink(fifoName);

    return 0;
}

//ipc---FIFO server 
int TestIpcFifoServ(const char* puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;

    char fifoName[MAXLINE];
    char buff[MAXLINE];
    memset(buff, '\0', sizeof(buff));
    memset(fifoName, '\0', sizeof(fifoName));

    //create server FIFO and open read interface
    unlink(FIFO_IPC_NAME);
    if(mkfifo(FIFO_IPC_NAME, IPC_AUTH) < 0 && (errno != EEXIST))
    {
        printf("...cannot creat %s...\n", fifoName);
        return -1;
    }
    int readInfo;

    //read msg from client
    int n = 0;
    char *ptr = NULL;
    while(1)
    {
        ptr = NULL;
        memset(buff, '\0', sizeof(buff));
        readInfo = open(FIFO_IPC_NAME, O_RDONLY, 0);
        n = read(readInfo, buff, MAXLINE);
        if(n <= 0)
        {
            printf("...no msg recv, sleep 3 seconds...\n");
            sleep(3);
            close(readInfo);
            continue;
        }
        if(buff[n-1] == '\n')
            buff[n-1] = '\0';
        printf("...recvmsg==[%s]...\n", buff);
        if((ptr = strchr(buff, '#')) == NULL)
        {
            printf("...bogus request==[%s]...\n", buff);
            close(readInfo);
            continue;
        }
        *ptr++ = '\0';
        if(strcmp(ptr, "quit") == 0)
            break;

        //open client FIFO
        sprintf(fifoName, "%s%s", FIFO_IPC_CLIENT, buff);
        int wrtInfo = open(fifoName, O_WRONLY, 0);
        if(wrtInfo < 0)
        {
            printf("...cann't open CLIENT FIFO==[%s]...\n", fifoName);
            close(readInfo);
            continue;
        }
        if(strcmp(ptr, "") == 0 || ptr == NULL)
        {
            strcpy(buff, "...error: request file is null...\n");
            n = strlen(buff);
            write(wrtInfo, buff, n);
            close(wrtInfo);
            close(readInfo);
            continue;
        }
        //read from files
        char path[MAXLINE];
        sprintf(path, "%s%s", FIFO_IPC_PATH, ptr);
        int fd;
        if((fd = open(path, O_RDONLY)) < 0)
        {
            sprintf(buff, "...cann't open [%s], errmsg=[%s]...\n", path, strerror(errno));
            n = strlen(buff);
            write(wrtInfo, buff, n);
            close(wrtInfo);
            close(readInfo);
            continue;
        }
        while((n = read(fd, buff, MAXLINE)) > 0)
        {
            write(wrtInfo, buff, n);
        }
        close(readInfo);
        close(wrtInfo);
        close(fd);
    }
    close(readInfo);
    unlink(FIFO_IPC_NAME);

    return 0;
}

//otl--mysql
int TestOtlMysql(const char* puIn, otl_connect* otlDB)
{
    LOG_DEBUG_FUNC;

    if(strcmp(puIn, "") == 0)
    {
        printf("...input is null...\n");
        return -1;
    }
    IpcVec inPramVec;
    ForDataBySplit(puIn, inPramVec, SPLIT_ATTR);

    otl_nocommit_stream sm_methoddeal;
    sm_methoddeal.set_flush(false);
    try
    {
        if(inPramVec.at(0) == "Q" && inPramVec.size() >= 2)
        {
            sm_methoddeal.open(10, "select method_no,module_id,method_name,method_desc\
                    from ts_method_dict where module_id=:MODULE_ID<int>", *otlDB);
            sm_methoddeal<<atoi(inPramVec.at(1).c_str());
            sm_methoddeal.flush();
            while(!sm_methoddeal.eof())
            {
                char f0[60];
                int f1;
                char f2[128];
                char f3[128];
                sm_methoddeal >> f0 >> f1 >> f2 >> f3;
                printf("{%s || %d || %s || %s}\n", f0, f1, f2, f3);
            }
        }
        else if(inPramVec.at(0) == "I" && inPramVec.size() >= 5)
        {
            sm_methoddeal.open(1, "insert into ts_method_dict(method_no,module_id,method_name,method_desc)\
                    values(:METHOD_NO<char[60]>, :MODULE_ID<int>, :METHOD_NAME<char[128]>, \
                    :METHOD_DESC<char[128]>)", *otlDB);
            sm_methoddeal<<inPramVec.at(1).c_str();
            sm_methoddeal<<atoi(inPramVec.at(2).c_str());
            sm_methoddeal<<inPramVec.at(3).c_str();
            sm_methoddeal<<inPramVec.at(4).c_str();
            sm_methoddeal.flush();
            printf("insert sucess...{%s || %d || %s || %s}\n", inPramVec.at(1).c_str(), atoi(inPramVec.at(2).c_str()),
                    inPramVec.at(3).c_str(), inPramVec.at(4).c_str());
        }
        else if(inPramVec.at(0) == "U" && inPramVec.size() >= 5)
        {
            sm_methoddeal.open(1, "update ts_method_dict set \
                    module_id=:MODULE_ID<int>,method_name=:METHOD_NAME<char[128]>,\
                    method_desc=:METHOD_DESC<char[128]> where method_no=:METHOD_NO<char[60]>", *otlDB);
            sm_methoddeal<<atoi(inPramVec.at(2).c_str());
            sm_methoddeal<<inPramVec.at(3).c_str();
            sm_methoddeal<<inPramVec.at(4).c_str();
            sm_methoddeal<<inPramVec.at(1).c_str();
            sm_methoddeal.flush();
            printf("update sucess...{%s || %d || %s || %s}\n", inPramVec.at(1).c_str(), atoi(inPramVec.at(2).c_str()),
                    inPramVec.at(3).c_str(), inPramVec.at(4).c_str());
        }
        else if(inPramVec.at(0) == "D" && inPramVec.size() >= 2)
        {
            sm_methoddeal.open(1, "delete from ts_method_dict where method_no=:METHOD_NO<char[60]>", *otlDB);
            sm_methoddeal<<inPramVec.at(1).c_str();
            sm_methoddeal.flush();
            printf("delete sucess...{%s}\n", inPramVec.at(1).c_str());
        }
        else
        {
            printf("...input [%s] error...\n", puIn);
            return -1;
        }
        sm_methoddeal.close();
    }
    catch(otl_exception& p)
    {
        cerr <<"-----err_code=="<<p.code<<endl;
        cerr <<"------err_msg=="<< p.msg << endl; // print out error message
        cerr <<"------stm_text=="<< p.stm_text << endl; // print out SQL that caused the error
        cerr <<"------sqlstate=="<< p.sqlstate << endl; // print out SQLSTATE message
        cerr <<"------var_info=="<< p.var_info << endl; // print out the variable that caused the error
        return -1;
    }
    catch(...)
    {
        cout<<"------unknown exception-----"<<endl;
        return -2;
    }

    return 0;
}

//ipc---shared memory and semaphore
int TestIpcShmServ(const char *puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;

    int sysret = system("ipcs -m|grep 640");
    struct SHM_TEXT *shm_text_pos;
    //get the key_id
    key_t key = ftok(SHM_IPC_NAME, IPC_KEY_ID);
    //check the share-memory
    int shm_id = shmget(key, SHM_SIZE, IPC_AUTH);
    if(shm_id != -1)
    {
        printf("shm exist already...\n");
        shm_text_pos = (struct SHM_TEXT*)shmat(shm_id, NULL, 0);
        if(shm_text_pos != (void*)-1)
        {
            printf("delete the existence shm ...\n");
            shmdt(shm_text_pos);
            shmctl(shm_id, IPC_RMID, 0);
        }
    }
    //create the new share-memory
    shm_id = shmget(key, SHM_SIZE, IPC_CREAT|IPC_EXCL|IPC_AUTH);
    if(shm_id == -1)
    {
        printf("shmget create error...\n");
        return -1;
    }
    sysret = system("ipcs -m|grep 640");
    //set the shm address to my own process
    shm_text_pos = (struct SHM_TEXT*)shmat(shm_id, NULL, 0);
    strcpy(shm_text_pos->shm_text, "hello, unix-shm");
    shm_text_pos->shm_tid = 999;
    //see the ipc message
    sysret = system("ipcs -m|grep 640");
    printf("set the share msg:\n");
    printf("shm_text_pos->shm_text==[%s], shm_text_pos->shm_tid==[%d]\n",
            shm_text_pos->shm_text, shm_text_pos->shm_tid);

    sleep(3);
    printf("get the new share msg:\n");
    printf("shm_text_pos->shm_text==[%s], shm_text_pos->shm_tid==[%d]\n",
            shm_text_pos->shm_text, shm_text_pos->shm_tid);

    //use semaphore
    key_t key_s = ftok(SEMA_IPC_NAME, IPC_KEY_ID);
    int sema_id = semget(key_s, 1, IPC_CREAT|IPC_EXCL|IPC_AUTH);
    if(sema_id != -1)
    {
        if(semctl(sema_id, 0, SETVAL, 1) != -1)
        {
            printf("------lock data now------\n");
            struct sembuf p_op_buf,v_op_buf;
            //lock
            p_op_buf.sem_num = 0;
            p_op_buf.sem_op = -1;
            p_op_buf.sem_flg = SEM_UNDO;
            if(semop(sema_id, &p_op_buf, 1) != -1)
            {
                int ishm = 0;
                char shm_msg[100];
                for(; ishm<=20; ishm++)
                {
                    shm_text_pos->shm_info[ishm].shm_iseq = ishm;
                    memset(shm_msg, '\0', sizeof(shm_msg));
                    sprintf(shm_msg, "shm_info_%d", ishm);
                    strcpy(shm_text_pos->shm_info[ishm].shm_msg, shm_msg);
                    printf("set share msg: [%d] | [%s]...\n", ishm, shm_msg);
                    sleep(1);
                }
                //release
                v_op_buf.sem_num = 0;
                v_op_buf.sem_op = 1;
                v_op_buf.sem_flg = SEM_UNDO;
                if(semop(sema_id, &v_op_buf, 1) == -1)
                    printf("------semop failed, errno==[%d], errmsg==[%s]\n", errno, strerror(errno));
                printf("------release data now------\n");
                sleep(20);
                if(semctl(sema_id, 0, IPC_RMID, 0) == -1)
                    printf("------semctl failed, errno==[%d], errmsg==[%s]\n", errno, strerror(errno));
            }
        }
    }
    else
    {
        printf("------semget failed, errno==[%d], errmsg==[%s]-------\n", errno, strerror(errno));
    }
    if(shmdt((const void *)shm_text_pos) == -1)
        printf("shmdt error...\n");
    sysret = system("ipcs -m|grep 640");

    if(shmctl(shm_id, IPC_RMID, NULL) == -1)
        printf("shmctl error...\n");

    //    sysret = system("ipcs -m");
    printf("-----sysret==[%d]------\n", sysret);

    return 0;
}

//ipc---shared memory
int TestIpcShmClient(const char *puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;

    int sysret = system("ipcs -m|grep 640");

    struct SHM_TEXT *shm_text_msg = NULL;
    //get the key_id
    key_t key = ftok(SHM_IPC_NAME, IPC_KEY_ID);
    //get the shm address
    int shm_id = shmget(key, 0, 0);
    if(shm_id == -1)
    {
        printf("------Get the server-shm failed, errno==[%d], errmsg==[%s]-------\n", errno, strerror(errno));
        return -1;
    }
    else
    {
        printf("shmget the address success...\n");
    }
    //map the shm address to current function
    shm_text_msg = (struct SHM_TEXT *)shmat(shm_id, NULL, 0);
    if(shm_text_msg == (void *)-1)
    {
        printf("shmat the address failed...\n");
        return -1;
    }
    else
    {
        printf("get the share msg:\n");
        printf("shm_text_msg->shm_text==[%s], shm_text_msg->shm_tid==[%d]\n",
                shm_text_msg->shm_text, shm_text_msg->shm_tid);
    }
    sysret = system("ipcs -m|grep 640");
    strcpy(shm_text_msg->shm_text, "so, 123, 我赢了...");
    shm_text_msg->shm_tid = 123;
    printf("modify the share msg:\n");
    printf("shm_text_msg->shm_text==[%s], shm_text_msg->shm_tid==[%d]\n",
            shm_text_msg->shm_text, shm_text_msg->shm_tid);

    //use semaphore
    sleep(5);
    key_t key_s = ftok(SEMA_IPC_NAME, IPC_KEY_ID);
    int sema_id = semget(key_s, 1, 0);
    if(sema_id != -1)
    {
        {
            struct sembuf p_op_buf,v_op_buf;
            //lock
            printf("------lock data now------\n");
            p_op_buf.sem_num = 0;
            p_op_buf.sem_op = -1;
            p_op_buf.sem_flg = SEM_UNDO;
            printf("----------process wait here------------\n");
            if(semop(sema_id, &p_op_buf, 1) != -1)
            {
                int ishm = 0;
                int ichk = 0;
                //    while(1)
                for(ishm=0; ishm<=20; ishm++)
                {
                    if(strcmp(shm_text_msg->shm_info[ishm].shm_msg, "shm_info_15") == 0)
                    {
                        printf("-------found it: [%d] | [%s]\n",
                                shm_text_msg->shm_info[ishm].shm_iseq, shm_text_msg->shm_info[ishm].shm_msg);
                        ichk = 1;
                        break;
                    }
                }
                if(ichk==0)
                {
                    printf("----------doesn't get the msg------------\n");
                    //sleep(2);
                }
                //        else
                //        {
                //            break;
                //        }
                //release
                v_op_buf.sem_num = 0;
                v_op_buf.sem_op = 1;
                v_op_buf.sem_flg = SEM_UNDO;
                if(semop(sema_id, &v_op_buf, 1) == -1)
                    printf("------semop failed, errno==[%d], errmsg==[%s]\n", errno, strerror(errno));
                printf("------release data now------\n");
            }
        }
    }
    else
    {
        printf("------Get the server-sema failed, errno==[%d], errmsg==[%s]-------\n", errno, strerror(errno));
    }

    //delete the shm from current function
    if(shmdt((const void *)shm_text_msg) == -1)
    {
        printf("shmdt the shm failed...\n");
    }
    sysret = system("ipcs -m|grep 640");
    printf("----sysret==[%d]\n", sysret);
    sleep(2);

    return 0;
}

//ipc---message queue
int TestMsgQueClient(const char *puIn, otl_connect *otlDb)
{
    LOG_DEBUG_FUNC;

    struct msg_st *data;
    struct msg_st *revData;
    struct MSG_MQ_INFO msgInfo;
    struct MSG_MQ_INFO *revMsgInfo;
    memset(&msgInfo, '\0', sizeof(struct MSG_MQ_INFO));
    data = (struct msg_st*)malloc(BUFSIZ);
    revData = (struct msg_st*)malloc(BUFSIZ);
    memset(data, '\0', sizeof(BUFSIZ));
    memset(revData, '\0', sizeof(BUFSIZ));

    char buffer[1024];
    int msgid = -1;
    long int revType = 2;
    int running = 1;

    //get the key_id
    key_t key = ftok(MQ_IPC_NAME, IPC_KEY_ID);

    //get the server-msg queue
    msgid = msgget(key, 0);
    if(msgid == -1)
    {
        printf("------Get the server msg-queue failed, errno==[%d], errmsg==[%s]-------\n", errno, strerror(errno));
        return -1;
    }

    //send msg until get "end" string
    while(running)
    {
        //input msg:
        printf("> ");
        char *pos = fgets(buffer, 1024, stdin);
        if(pos != NULL);
        data->msg_type = 1;
        buffer[strlen(buffer)-1]='\0';//erase the ending 'LF'
        strcpy(msgInfo.text, buffer);
        msgInfo.sendFlag = '1';
        memcpy(data->msg, (void*)&msgInfo, sizeof(msgInfo));
        //send msg to queue
        if(msgsnd(msgid, (const void*)data, BUFSIZ, 0) == -1)
        {
            printf("-------msgsnd failed------errno==[%d]\n", errno);
            exit(EXIT_FAILURE);
        }
        //if input "quit", then break
        if(strncmp(buffer, "quit", 4) == 0)
        {
            running = 0;
        }
        else
        {
            if(msgrcv(msgid, (void*)revData, BUFSIZ, revType, 0) == -1)
            {
                printf("-------msgrcv failed, errno==[%d]------\n", errno);
                exit(EXIT_FAILURE);
            }
            else
            {
                revMsgInfo = (struct MSG_MQ_INFO*)revData->msg;
                printf("%s\n", revMsgInfo->text);
            }
            //printf("---revMsgInfo.sendFlag==%c\n", revMsgInfo->sendFlag);
            while(revMsgInfo->sendFlag == '0')
            {
                if(msgrcv(msgid, (void*)revData, BUFSIZ, revType, 0) == -1)
                {
                    printf("-------msgrcv failed, errno==[%d]------\n", errno);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    revMsgInfo = (struct MSG_MQ_INFO*)revData->msg;
                    printf("%s\n", revMsgInfo->text);
                }
            }
        }
    }

    free(revData);
    free(data);

    return 0;
}

//ipc---message queue
int TestMsgQueServ(const char *puIn, otl_connect *otlDb)
{
    LOG_DEBUG_FUNC;

    int running = 1;
    struct msg_st *data;
    struct msg_st *revData;
    struct MSG_MQ_INFO *msgInfo = NULL;
    struct MSG_MQ_INFO revMsgInfo;
    memset(&revMsgInfo, '\0', sizeof(struct MSG_MQ_INFO));
    data = (struct msg_st*)malloc(BUFSIZ);
    revData = (struct msg_st*)malloc(BUFSIZ);
    memset(data, '\0', sizeof(BUFSIZ));
    memset(revData, '\0', sizeof(BUFSIZ));
    int msgid = -1;
    long int msgtype = 1;

    //get the key_id
    key_t key = ftok(MQ_IPC_NAME, IPC_KEY_ID);

    //create msg queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1)
    {
        printf("------call msgget failed-------\n");
        exit(EXIT_FAILURE);
    }

    //receive msg
    while(running)
    {
        printf("> ");
        fflush(stdout);
        if(msgrcv(msgid, (void*)data, BUFSIZ, msgtype, IPC_NOWAIT) == -1)
        {
            if(errno == ENOMSG)
            {
                printf("---No msg is received, sleep 3 seconds...\n");
                sleep(3);
                continue;
            }
            else
            {
                printf("-------msgrcv failed, errno==[%d]------\n", errno);
                exit(EXIT_FAILURE);
            }
        }
        msgInfo = (struct MSG_MQ_INFO*)data->msg;
        printf("Receive Msg==[%s]\n", msgInfo->text);

        revMsgInfo.sendFlag = '1';
        //if get "quit", then break
        if(strncmp(msgInfo->text, "quit", 4) == 0)
        {
            running = 0;
            continue;
        }
        if(strcmp(msgInfo->text, "more") == 0)
        {
            //send more than 1 time
            revData->msg_type = 2;
            int imsg = 0;
            for(; imsg<10; imsg++)
            {
                if(imsg == 10-1)
                    revMsgInfo.sendFlag = '1';//the last time
                else
                    revMsgInfo.sendFlag = '0';
                sprintf(revMsgInfo.text, "heihei,,,reply time %d", imsg);
                memcpy(revData->msg, (void*)&revMsgInfo, sizeof(revMsgInfo));
                if(msgsnd(msgid, (const void*)revData, BUFSIZ, 0) == -1)
                {
                    printf("-------msgsnd failed------errno==[%d]\n", errno);
                    exit(EXIT_FAILURE);
                }
                printf("----reply msg==[%s]\n", revMsgInfo.text);
            }
        }
        else
        {
            //send 1 time
            revData->msg_type = 2;
            if(strncmp(msgInfo->text, "reply", 5) == 0)
            {
                strcpy(revMsgInfo.text, "I get it...reply to you...");
            }
            else if(strncmp(msgInfo->text, "test", 4) == 0)
            {
                strcpy(revMsgInfo.text, "测试...123,back to you...");
            }
            else
            {
                strcpy(revMsgInfo.text, "unknown command...");
            }
            memcpy(revData->msg, (void*)&revMsgInfo, sizeof(revMsgInfo));
            printf("----reply msg==[%s]\n", revMsgInfo.text);
            //send msg to queue
            if(msgsnd(msgid, (const void*)revData, BUFSIZ, 0) == -1)
            {
                printf("-------msgsnd failed------errno==[%d]\n", errno);
                exit(EXIT_FAILURE);
            }
        }
    }

    //delete queue msg
    if(msgctl(msgid, IPC_RMID, 0) == -1)
    {
        printf("------msgctrl failed------\n");
        exit(EXIT_FAILURE);
    }

    free(revData);
    free(data);

    return 0;
}

//map---multiprocess deal
int TestForkMap(const char *puIn, otl_connect *otlDB)
{
    LOG_DEBUG_FUNC;

    map<char*, int> forkMap;
    char *pos = NULL;
    char buffer[100];
    printf("> ");
    pos = fgets(buffer, 100, stdin);

    printf("---forkMap.size==%d\n", (int)forkMap.size());
    char *sOrder = NULL;
    int im = 0;
    for( ; im<10000; im++ )
    {
        sOrder = (char*)malloc(30);
        sprintf(sOrder, "aaabbbcccxxxyyyzzz_%d", im);
        forkMap.insert(map<char*, int>::value_type(sOrder, im));
    }
    printf("---forkMap.size==%d\n", (int)forkMap.size());
    printf("> ");
    pos = fgets(buffer, 100, stdin);

    char *sOrd = (char*)malloc(30);
    map<char*, int>::iterator itm;
    for(itm=forkMap.begin(); itm!=forkMap.end(); itm++)
    {
        //        printf("[%s , %d]\n", itm->first, itm->second);
        free(itm->first);
        forkMap.erase(itm);
    }
    for( im=0; im<10000; im++ )
    {
        sprintf(sOrd, "aaabbbcccxxxyyyzzz_%d", im);
        itm = forkMap.find(sOrd);
        if(itm != forkMap.end())
        {
            free(itm->first);
            forkMap.erase(itm);
            printf("%d\n", im);
        }
        else
        {
            //            printf("%s\n", sOrd);
        }
    }
    free(sOrd);
    printf("---forkMap.size==%d\n", (int)forkMap.size());
    printf("> ");
    pos = fgets(buffer, 100, stdin);
    printf("%s", pos);

    return 0;
}


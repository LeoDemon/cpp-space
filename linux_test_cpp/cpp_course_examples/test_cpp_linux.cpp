/*
 * =====================================================================================
 *
 *       Filename:  test_cpp_linux.cpp
 *
 *    Description:  linux c 一站式学习案例测试
 *
 *        Version:  1.0
 *        Created:  2013年04月13日 10时21分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lijha
 *   Organization:
 *
 * =====================================================================================
 */
#include "test_cpp_main.h"
#include "test_cpp_linux.h"

int TestShareSo()
{
    cout<<"Just want to test the share lib..."<<endl;

    return 0;
}
//linux popen等函数,创建管道并调用shell
//FILE *popen( const char* command, const char* mode );成功返回文件指针，错误返回NULL
//void perror( const char *str ); 将上一个函数发生错误的原因输出到标准错误(stderr)
//int pclose (FILE* stream);返回cmdstring的终止状态，错误返回-1
int TestPopen()
{
    cout<<"----------in TestPopen----------"<<endl;

    FILE *fRead = NULL;
    const char* pCommand = "ps -ef|grep -v grep|grep -v tail|grep mysql|grep `whoami`|grep -v vi|wc -l";
    cout<<"++++++pCommand=="<<pCommand<<endl;
    char pVal[100];
    memset(pVal, '\0', sizeof(pVal));
    if((fRead = popen(pCommand, "r")) == NULL)
    {
        perror("++++++popen failed");
        return -1;
    }
    while(fgets(pVal, 100, fRead))
    {
        printf("++++++pVal==%s", pVal);
    }
    int iVal = atoi(pVal);
    printf("++++++iVal==[%d]+++++\n", iVal);
    if(pclose(fRead) == -1)
    {
        perror("++++++pclose error");
        return -1;
    }

    cout<<"----------out TestPopen----------"<<endl;
    return 0;
}

//父进程中止处理
static void FaProcessDie(int n=0)
{
    cout<<"++++++++FaProcessDie | 主进程["<<getpid()<<"]非正常结束++++++++++"<<endl;
    //int kill(pid_t pid, int sig);
    //pid参数:
    //pid>0:pid是信号欲送往的进程的标识
    //pid=0:信号将送往所有与调用kill()的那个进程属同一个使用组的进程
    //pid=-1:信号将送往所有调用进程有权给其发送信号的进程，除了进程1(init)
    //pid<-1:信号将送往以-pid为组标识的进程
    //sig：准备发送的信号代码，假如其值为零则没有任何信号送出，但是系统会执行错误检查，通常会利用sig值为零来检验某个进程是否仍在执行
    //返回值说明： 成功执行时，返回0。失败返回-1，errno被设为以下的某个值:
    //EINVAL：指定的信号码无效（参数 sig 不合法）; EPERM:权限不够无法传送信号给指定进程; ESRCH：参数 pid 所指定的进程或进程组不存在
    int ret=kill(0, SIGTERM);
    cout<<"-----------ret=="<<ret<<endl;
    exit(-1);
}

//子进程中止处理
/*
  static void SubProcessDie(int n=0)
  {
  int pid,status;
  //wait函数回收子进程
  pid = wait(&status);

  if(pid>0)
  {
  printf("++++++++++SubProcessDie | 子进程[%d]非正常结束 ++++++++++", pid);
  //WIFEXITED、WEXITSTATUS检验子进程退出的正常还是非正常和返回值的宏
  if(WIFEXITED(status))
  printf("~~~~~~Child exited with code %d\n", WEXITSTATUS(status));
  else if(WIFSIGNALED(status))
  printf("~~~~~~Child terminated abnormally, signal %d\n", WTERMSIG(status));

  printf("errno=%d\n",errno);
  //FaProcessDie();
  }
  }
*/

//子进程中止处理
static void CatchSubProc(int n=0)
{
    cout<<"---------------catch popen sub process---------------"<<endl;
}


//子进程中止处理
static void CatchSubProc2(int n=0)
{
    cout<<"---------------catch popen sub process test 000000---------------"<<endl;
}

//忽略所有信号
void  IgnoreAllSignal()
{
    //如参数结构sigaction定义如下
    //  struct sigaction
    //  {
    //      void (*sa_handler) (int);//信号捕捉函数，处理方式
    //      sigset_t sa_mask;//说明了一个信号集，在调用该信号捕捉函数之前，这一信号集要加进进程的信号屏蔽字中。仅当从信号捕捉函数返回时再将进程的信号屏蔽字复位为原先值;(指定在信号处理程序执行过程中，哪些信号应当被阻塞。默认当前信号本身被阻塞)
    //      int sa_flags;//SA_INTERRUPT 由此信号中断的系统调用不会自动重启;SA_RESTART 由此信号中断的系统调用会自动重启;SA_SIGINFO 提供附加信息，一个指向siginfo结构的指针以及一个指向进程上下文标识符的指针
    //      void (*sa_restorer) (void);//未使用
    //  }
    struct sigaction act;

    //SIG_IGN处理方式：忽略产生的信号，程序继续
    //SIG_DFL处理方式：执行系统默认操作
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);//初始化屏蔽字
    act.sa_flags=0;//初始化flags

    //int sigaction(int signum,const struct sigaction *act ,struct sigaction *oldact);
    //sigaction()会依参数signum指定的信号编号来设置该信号的处理函数。参数signum可以指定SIGKILL和SIGSTOP以外的所有信号
    //signum：除了SIGKILL和SIGSTOP之外的其它任何信号编码。
    //act：如果值非NULL，将安装为signum关联信号的新处理方式。
    //oldact：如果值非NULL，存储以前对signum关联信号的处理方式。
    sigaction(SIGHUP,&act,NULL);
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);

    return ;
}

//创建守护进程
int GenDaemonFork()
{
    printf("++++++++++deamon start begin++++++++++\n");

    //如果主进程僵死, 子进程由init进程接管
    int retVal;
    if(getppid() == 1)
    {
        retVal = chdir("/");
        printf("+++++++++++++++++retVal==[%d]\n", retVal);
        umask(0);
        IgnoreAllSignal();
        printf("++++++++father process is 1+++++++++\n");
        return 0;
    }

    //step1:创建第1子进程，父进程退出
    int childpid;
    if((childpid = fork())<0)
    {
        printf("+++++++++can't fork the 1st child [%s] [%d]+++++++++\n", __FILE__, __LINE__);
        exit(-1);
    }
    else if(childpid > 0)
    {
        printf("+++++++++father process exit+++++++++\n");
        exit(0);//父进程退出
    }
    cout<<"+++++++++childpid1=="<<getpid()<<endl;
    cout<<"+++++++++getsid1=="<<getsid(0)<<endl;

    //step2:摆脱父进程控制及终端控制(第1子进程成为新的会话组长和进程组长)
    //pid_t getsid(pid_t pid);返回会话首进程的进程组ID (session ID)
    if(getsid(0) != getpid())//会话组id等于当前进程id,则当前进程已经是会话组长
    {
        if(setsid()<0)
        {
            perror("setsid");
            exit(1) ;
        }
    }

    cout<<"+++++++++getsid2=="<<getsid(0)<<endl;
    cout<<"+++++++++getsid3=="<<getsid(getpid())<<endl;
    IgnoreAllSignal();

    //step3:禁止进程重新打开控制终端(创建第2子进程,第1子进程退出)
    if((childpid = fork()) < 0)
    {
        printf("+++++++++can't fork the 2nd child [%s] [%d]+++++++++\n", __FILE__, __LINE__);
        exit(-3);
    }
    else if(childpid > 0)
    {
        printf("+++++++++the 1st child process exit+++++++++\n");
        exit(0);//第1子进程退出
    }
    cout<<"+++++++++childpid2=="<<getpid()<<endl;

    //step4:关闭从父进程继承的文件描述符(标准输入(输出)0,1,2也应关闭)
    int fd;
    for(fd=3; fd<=1024; fd++)
        //close(fd);

        //step5:改变当前目录为根目录(进程不再依赖当前目录)
        retVal = chdir("/");

    //step6:重设文件权限掩码
    //000对应文件权限为:664
    //000对应文件夹权限为:775
    umask(0);

    printf("++++++++++deamon start finish++++++++++\n");

    IgnoreAllSignal();

    return 0;
}


int TestFork()
{
    cout<<"++++++++++in TestFork+++++++++"<<endl;
    char pMessage[255];
    memset(pMessage, '\0', sizeof(pMessage));

    //  char pwd[200];
    //  pwd[0]='\0';
    //  cout<<"+++++++++getppid=="<<getppid()<<endl;
    //  cout<<"+++++++++getpid=="<<getpid()<<endl;
    //  getcwd(pwd, 200);
    //  cout<<"+++++++++before chdir pwd=="<<pwd<<endl;
    //  chdir("/home");
    //  getcwd(pwd, 200);
    //  cout<<"+++++++++after chdir pwd=="<<pwd<<endl;
    signal(SIGCLD, CatchSubProc);
    TestPopen();

    GenDaemonFork();

    //libc 中定义的全局变量environ指向环境变量表
    //  extern char **environ;
    //  for(int ienv=0; environ[ienv] != NULL; ienv++)
    //  {
    //      cout<<"this is parent++++++environ["<<ienv<<"]=="<<environ[ienv]<<endl;
    //  }

    //void (*signal(int signum, void (*handler)(int)))(int);函数逻辑
    //1)void (*handler)(int)为用户定义的函数指针,signal(int, void(*)(int))接收两个参数
    //2)void (*signal())(int),signal函数返回一个函数指针,这个函数指针所指向的函数接受一个整型参数,且没有返回值,
    //其实signal函数返回的函数指针就是handler,即它的第2个参数，用户定义的处理函数( signal内部时, signal把信号做为参数传递给handler信号处理函数,接着 signal函数返回指针, 并且又指向信号处理函数, 就开始执行它)
    //上面可以简化为:void (*signal(int, void(*)(int)))(int);
    //继续简化为:typedef void (*HANDLER)(int);
    //           HANDLER signal(int, HANDLER);
    signal(SIGCLD, CatchSubProc2);
    signal(SIGTERM, FaProcessDie);

    for(int iFork=0; iFork<1; iFork++)
    {
        int pid=fork();
        if(pid == 0)//子进程进入，pid值为0
        {
            sprintf(pMessage, "This is the child, pid=[%d]!", getpid());
            TestForkExec(pMessage, iFork);
        }
        else if(pid < 0)
        {
            perror("---fork failed---");
            break;
        }
        else//父进程进入,pid值为子进程的进程id,该值大于0
        {
            //sleep(1);
            //cout<<"++++++child pid=="<<pid<<endl;
            //          int stat_val;
            //          waitpid(pid, &stat_val, 0);
            //          //WIFEXITED、WEXITSTATUS检验子进程退出的正常还是非正常和返回值的宏
            //          if(WIFEXITED(stat_val))
            //              printf("~~~~~~Child exited with code %d\n", WEXITSTATUS(stat_val));
            //          else if(WIFSIGNALED(stat_val))
            //              printf("~~~~~~Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
        }
    }

    //让主进程挂起
    while(1)
    {
        //cout<<"------this is paren1-------pid=="<<getpid()<<endl;
        pause();
        //exit(1);
    }

    cout<<"++++++++++out TestFork+++++++++"<<endl;

    return 0;
}

int TestForkExec(const char *str, int iFork)
{
    //  extern char **environ;
    //  for(int ienv=0; environ[ienv] != NULL; ienv++)
    //  {
    //      cout<<"this is child["<<iFork<<"]++++++environ["<<ienv<<"]=="<<environ[ienv]<<endl;
    //  }
    //子进程死循环跑
    while(1)
    {
        cout<<"------exec hz 001----["<<iFork<<"]=="<<str<<endl;
        TestPopen();
        sleep(10);
        //cout<<"+++++++++getppid=="<<getppid()<<endl;

        //      if(iFork == 1)
        //          exit(iFork);
    }

    return 0;
}

//golbal counter
unsigned int counter = 0;
//init pthread mutex
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void ThreadPrtTemp()
{
    pid_t pid;
    pthread_t ptid;
    pid = getpid();
    ptid = pthread_self();
    cout<<"++++++pid=="<<(unsigned int)pid<<", ptid=="<<(unsigned int)ptid;

    return ;
}

void *PrtThread(void *arg)
{
    int val;
    for(int i=0; i<10; i++)
    {
        //current thread get the mutex lock
        pthread_mutex_lock(&counter_mutex);
        val = counter;
        ThreadPrtTemp();
        cout<<"-------This is ["<<(const char*)arg<<"] process...val=="<<val+1<<endl;
        counter = val + 1;
        //release the lock
        pthread_mutex_unlock(&counter_mutex);
        sleep(1);
    }
    return (void *)2;
}

//多线程
int TestThread()
{
    pthread_t ptid1,ptid2,ptid3;
    void *pret;
    //pthread-1
    int iRet = pthread_create(&ptid1, NULL, PrtThread, (void *)"---1st sub pthread---");
    if(iRet != 0)
    {
        cout<<"--------pthread_create error"<<endl;
        exit(-1);
    }
    //pthread-2
    iRet = pthread_create(&ptid2, NULL, PrtThread, (void *)"---2nd sub pthread---");
    if(iRet != 0)
    {
        cout<<"--------pthread_create error"<<endl;
        exit(-1);
    }
    //pthread-3
    iRet = pthread_create(&ptid3, NULL, PrtThread, (void *)"---3th sub pthread---");
    if(iRet != 0)
    {
        cout<<"--------pthread_create error"<<endl;
        exit(-1);
    }
    for(int i=0; i<3; i++)
    {
        ThreadPrtTemp();
        cout<<"-------This is the main process..."<<endl;
        sleep(1);
    }
    //pthread_cancel(ptid);
    pthread_join(ptid1, &pret);
    pthread_join(ptid2, &pret);
    pthread_join(ptid3, &pret);
    printf("------exit code---pret==[%d]\n", (int*)(pret));

    string abc = "123hello,";
    cout <<"abc===["<<abc<<"], abc.length()=="<<abc.length()<<endl;
    abc = abc.substr(0, abc.length()-1);
    cout <<"abc==="<<abc<<endl;

    return 0;
}

struct prodmsg
{
    struct prodmsg *next;
    int id;
};
struct prodmsg *prodhead;
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock_prod = PTHREAD_MUTEX_INITIALIZER;

void *TestConsumer(void *p)
{
    struct prodmsg *mp;
    //for(;;)
    for(int i=0; i<10; i++)
    {
        pthread_mutex_lock(&lock_prod);
        while(prodhead==NULL)
        {
            pthread_cond_wait(&cond_prod, &lock_prod);
        }
        mp=prodhead;
        prodhead=mp->next;
        pthread_mutex_unlock(&lock_prod);
        printf("++++++Consumer...mp->id==[%d]\n", mp->id);
        free(mp);
        sleep(rand()%5);
    }

    return NULL;
}

void *TestProducer(void *p)
{
    struct prodmsg *mp;
    //for(;;)
    for(int i=0; i<10; i++)
    {
        mp=(struct prodmsg*)malloc(sizeof(struct prodmsg));
        mp->id=rand()%1000+1;
        printf("++++++Producer...mp->id==[%d]\n", mp->id);
        pthread_mutex_lock(&lock_prod);
        mp->next=prodhead;
        prodhead=mp;
        pthread_mutex_unlock(&lock_prod);
        pthread_cond_signal(&cond_prod);
        sleep(rand()%5);
    }
    return NULL;
}

//多线程间同步
int TestThreadSyn1()
{
    printf("+++++++++in TestThreadSyn1++++++++\n");
    pthread_t pid, cid;
    srand(time(NULL));
    //srand(1);
    /*for(int i=0; i<10; i++)*/
    //{
    //srand(time(NULL));
    ////srand(1);
    //sleep(1);
    ////srand(10);
    //printf("-----rand[%d]==[%d]\n", i, rand()%100);
    /*}*/
    pthread_create(&pid, NULL, TestProducer, NULL);
    pthread_create(&cid, NULL, TestConsumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    printf("+++++++++out TestThreadSyn1++++++++\n");

    return 0;
}

#define PT_NUM 6
int pt_quene[PT_NUM];
sem_t blank_num, prod_num;

void *TestConsumer2(void *ptr)
{
    int c=0;
    for(;;)
    {
        sem_wait(&prod_num);
        printf("++++++Consumer...pt_quene[%d]==[%d]\n", c, pt_quene[c]);
        pt_quene[c]=0;
        sem_post(&blank_num);
        c=(c+1)%PT_NUM;
        sleep(rand()%5);
    }
    return NULL;
}

void *TestProducer2(void *ptr)
{
    int p=0;
    for(;;)
    {
        sem_wait(&blank_num);
        pt_quene[p]=rand()%1000+1;
        printf("++++++Producer...pt_quene[%d]==[%d]\n", p, pt_quene[p]);
        sem_post(&prod_num);
        p=(p+1)%PT_NUM;
        sleep(rand()%5);
    }
    return NULL;
}

//多线程间同步2
int TestThreadSyn2()
{
    printf("+++++++++in TestThreadSyn2++++++++\n");
    pthread_t pid, cid;
    sem_init(&blank_num, 0, PT_NUM);
    sem_init(&prod_num, 0, 0);
    srand(time(NULL));

    pthread_create(&pid, NULL, TestProducer2, NULL);
    pthread_create(&cid, NULL, TestConsumer2, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    sem_destroy(&blank_num);
    sem_destroy(&prod_num);
    printf("+++++++++out TestThreadSyn2++++++++\n");

    return 0;
}

//精通UNIX下C语言编程与项目实践
//P67 代码4-7, 4-9
int TestLinuxLs(const char *puInparam)
{
    cout<<"++++++++in TestLinuxLs+++++++"<<endl;
    cout<<"++++++++puInparam=="<<puInparam<<endl;

    //struct stat
    //{
    //......
    //dev_t st_dev;//文件常驻设备ID
    //ino_t st_ino;//i节点编号
    //mode_t st_mode;//文件类型与权限
    //nlink_t st_nlink;//文件链接数
    //uid_t st_uid;//文件属主ID
    //gid_t st_gid;//文件属组ID
    //dev_t st_rdev;//特别文件(字符文件或块文件)设备号
    //off_t st_size;//文件长度
    //time_t st_atime;//文件最近访问时间
    //time_t st_mtime;//文件最近修改时间
    //time_t st_ctime;//文件状态最近改变时间
    //......
    //};
    struct stat info;//文件属性的结构体
    char buf[100];
    memset(buf, '\0', sizeof(buf));
    char *p = buf;
    if(lstat(puInparam, &info) == 0)//读取puInparam指向的文件属性信息并保存到参数info所指向的结构stat中
    {
        p += GetFileType(info.st_mode, p);
        p += GetFileMode(info.st_mode, p);
        p += GetFileOtherAttr(info, p);
        printf("%s %s \n", buf, puInparam);
    }
    else
    {
        fprintf(stderr, "++++++open file failed.++++++\n");
    }

    //文件系统属性
    // struct statfs
    //{
    //  ......
    //short f_type;//文件系统类型
    //long f_bsize;//数据块大小
    //long f_blocks;//数据块总数
    //long f_bfree;//可用块数
    //long f_files;//inode总数
    //long f_ffree;//可用inode数
    //.......
    //}
    //int statfs(char *path, struct statfs *buf);
    //函数statfs通过读取文件系统的超级块信息，获取文件系统的属性，并把该属性存储于参数buf所指向的缓冲区中.
    struct statfs sbuf;
    statfs(puInparam, &sbuf);
    printf("FILE SYSTEM: \n");
    printf("type==%ld\n", (long)sbuf.f_type);
    printf("bsize==%ld\n", sbuf.f_bsize);
    printf("blocks==%ld\n", sbuf.f_blocks);
    printf("bfree==%ld\n", sbuf.f_bfree);
    printf("files==%ld\n", sbuf.f_files);
    printf("free==%ld\n", sbuf.f_ffree);

    cout<<"++++++++out TestLinuxLs++++++++"<<endl;

    return 0;
}

//文件其他属性
int GetFileOtherAttr(struct stat info, char *resp)
{
    struct tm *mtime;
    if(resp == NULL) return 0;
    mtime = localtime(&info.st_mtime);

    int ret = sprintf(resp, " %3d %6d %6d %11d %04d%02d%02d",
                      info.st_nlink, info.st_uid, info.st_gid, info.st_size,
                      mtime->tm_year+1900, mtime->tm_mon+1, mtime->tm_mday);

    return ret;
}

//文件访问权限
int GetFileMode(mode_t st_mode, char *resp)
{
    if(resp == NULL) return 0;
    memset(resp, '-', 9);

    if(st_mode & S_IRUSR) resp[0] = 'r';
    if(st_mode & S_IWUSR) resp[1] = 'w';
    if(st_mode & S_IXUSR) resp[2] = 'x';
    if(st_mode & S_IRGRP) resp[3] = 'r';
    if(st_mode & S_IWGRP) resp[4] = 'w';
    if(st_mode & S_IXGRP) resp[5] = 'x';
    if(st_mode & S_IROTH) resp[6] = 'r';
    if(st_mode & S_IWOTH) resp[7] = 'w';
    if(st_mode & S_IXOTH) resp[8] = 'x';

    return 9;
}

//文件类型
int GetFileType(mode_t st_mode, char *resp)
{
    if(resp == NULL) return 0;

    if(S_ISDIR(st_mode)) resp[0] = 'd';
    else if(S_ISCHR(st_mode)) resp[0] ='c';
    else if(S_ISBLK(st_mode)) resp[0] ='b';
    else if(S_ISREG(st_mode)) resp[0] ='-';
    else if(S_ISFIFO(st_mode)) resp[0] ='p';
    else if(S_ISLNK(st_mode)) resp[0] ='l';
    else resp[0] = ' ';

    return 1;
}


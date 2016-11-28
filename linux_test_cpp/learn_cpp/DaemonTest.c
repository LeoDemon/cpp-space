#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdarg.h>


//忽略控制终端信号
void  IgnoreAllSignal()
{
    struct sigaction act;

    //SIG_IGN处理:忽略信号
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGHUP,&act,NULL);
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);

    return ;
}


//创建守护进程
int	GenDaemonFork()
{
    printf("++++++++++deamon start begin++++++++++\n");

    //如果主进程僵死, 子进程由init进程接管
    if(getppid() == 1)
    {
        chdir("/");
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

    //step2:摆脱父进程控制及终端控制(第1子进程成为新的会话组长和进程组长)
    if(getsid(0) != getpid())
    {
        if(setsid()<0)
        {
            perror("setsid");
            exit(1)	;
        }
    }

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

    //step4:关闭从父进程继承的文件描述符
    //标准输入(输出)0,1,2也应关闭(这里为输出父进程日志而保留)
    int fd;
    for(fd=3; fd<=1024; fd++)
        close(fd);

    //step5:改变当前目录为根目录(进程不再依赖当前目录)
    chdir("/");

    //step6:重设文件权限掩码
    umask(0);

    printf("++++++++++deamon start finish++++++++++\n");

    IgnoreAllSignal();

    return 0;
}


static void subprocess_die(int n=0)
{
    printf("------------catch the child signal SIGCLD-----------\n");
    int pid,ret;
    int status;
    //回收子进程
    pid=wait(&status);
    if(pid>0)
    {
        ret=kill(0,SIGTERM);
    }
    exit(1);
}

//业务处理
int DoBusiWork()
{
    printf("---DoBusi now---\n");
    //while(1)
    //{
    //    ......
    //}

    exit (0);
}


//主函数
int main(int argc, char *argv[])
{
    //step1:验证及初始化操作
    printf("++++++++++init++++++++++\n");

    //设置标准输出流缓冲区为行缓冲,BufferSize=20k
    char buffer[20480];
    setvbuf(stdout, buffer, _IOLBF, 20480);

    //验证入参个数
    if(argc != 2)
    {
        printf("++++++++++the argc==[%d] was wrong, exit now!!!++++++++++\n", argc);
        exit(-1);
    }
    int procSum = atoi(argv[1]);
    printf("---procSum==%d\n", procSum);

    //创建守护进程
    GenDaemonFork();

    //
    signal(SIGCLD,subprocess_die);

    //step2:读取进程配置文件
    printf("++++++++++get data from cfg++++++++++\n");
    //......

    //step3:动态库初始化
    printf("++++++++++Lib init++++++++++\n");
    //......

    try
    {
        //step4:启动子进程
        int pid = 0, procNo = 0;
        if(procSum > 0)
        {
            for(procNo=0; procNo<procSum; procNo++)
            {
                pid = fork();
                if(pid < 0)
                {
                    printf("+++++++++++fork子进程失败+++++++++\n");
                    exit(-2);
                }
                if(pid == 0)
                {
                    printf("第[%d]子进程启动成功,进程号[%d]\n", procNo, getpid());
                    DoBusiWork();
                }
            }
        }
    }
    catch(...)
    {
        printf("%s|%d|unknow exception, 进程启动失败!!!\n", __FUNCTION__, __LINE__);
        exit(1);
    }

    while(1)
    {
        //主进程挂起，直到有信号唤醒
        pause();
    }

    return 0;
}


#include <sys/sem.h> 

#include <sys/shm.h> 

#include <sys/ipc.h> 

#include <stdio.h> 

#define  SHMKEY  75 

int  shmid;   

int  *addr; 

int fatal(char *mes) 

{ 	perror(mes); 

	exit(1); 

} 

void  client( ) 

{  int i; 

addr=shmat(shmid,0,0);           /*获得共享存储区首地址*/ 

for (i=9;i>=0;i--) 

  {  

     while (*addr!=-1); 

     printf("(client) sent *addr= %d\n",i); 

     *addr=i;

 } 

sleep(1);

exit(0); 

} 

 

void  server( ) 

{ 

 int tmp;

addr=shmat(shmid,0,0);        /*获取首地址*/ 

do  

 {    

     *addr=-1; /*将-1写入这个存储区*/

     while (*addr==-1); 

     tmp=*addr;

     printf("(server) received *addr=%d\n",tmp); 

 }while (tmp);  

shmctl(shmid,IPC_RMID,0);     /*撤消共享存储区，归还资源*/ 

exit(0); 

} 

 

int main() 

{ 

    int pid;

    shmid=shmget(SHMKEY,1024,0660|IPC_CREAT); /*创建1024字节大小的共享存储区*/     

   while ((pid=fork( ))==-1); /*pid=0 表示在子进程,让子进程进行server（），然后退出*/

   if (!pid) server( ); 

   system("ipcs  -m"); /*父进程从这里开始执行，将执行的命令显示在终端，观察现在共享存储区的情况，是否创建等*/

   while ((pid=fork( ))==-1); /*父进程创建第二个子进程，client（），执行完正常退出，有循环，会执行一段时间*/

   if (!pid) client( ); 

   system("ipcs  -m"); 

   wait(0); /*等待子进程结束回收它*/

   system("ipcs  -m"); /*观察一下*/

   wait(0); 

   system("ipcs  -m"); 

}

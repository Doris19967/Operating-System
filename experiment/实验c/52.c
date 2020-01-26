#include <sys/sem.h> 

#include <sys/shm.h> 

#include <sys/ipc.h> 

#include <stdio.h> 



#define  SHMKEY  75 



int  shmid;   

char  *addr; 



int fatal(char *mes) 

{ 	perror(mes); 

	exit(1); 

}

 /******************/

int  mutexid,senid,recid;   

int mutex,sen,rec;

typedef union semun{

    int val;

    struct semid_ds *buf;

    unsigned short *array;

} semun;



int sem_init(int key,int i)

{

int semid;

semun arg;

if((semid=semget(key,1,0660|IPC_CREAT))<0)

 fatal("sem_init:semget");

arg.val=i;

if(semctl(semid,0,SETVAL,arg)<0)

 fatal("sem_init:semctl");

return semid;

}



void sem_rmv(int semid)

{

if(semctl(semid,0,IPC_RMID,NULL)< -1)

 fatal("sem_rmv:semctl");

}

int sem_p(int semid){

struct sembuf sb;

sb.sem_num=0;

sb.sem_op=-1;

sb.sem_flg=SEM_UNDO;

if(semop(semid,&sb,1)==-1)

 fatal("sem_p:semop"); 

return 0;

}



int sem_v(int semid){

struct sembuf sb;

sb.sem_num=0;

sb.sem_op=1;

sb.sem_flg=SEM_UNDO;

if(semop(semid,&sb,1)==-1)

 fatal("sem_v:semop"); 

return 0;   

}

/******************/



void  client( ) 

{  int i; 

addr=shmat(shmid,0,0);           /*获得共享存储区首地址*/ 



for (i=9;i>=0;i--) 

  {  

     sem_p(senid); /*senid初始值为0*/

  //   while (*addr!=-1); 

     printf("(client) sent *addr= %d\n",i); 

     *addr=i;

     sem_v(recid);         

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

   //  *addr=-1; 

   //  while (*addr==-1); 

     sem_p(recid); /*recid初始值为1*/

     tmp=*addr;

     printf("(server) received *addr=%d\n",tmp); 

     sem_v(senid); 

 }while (tmp);  

exit(0); 

} 

 

int main() 

{ 

    int pid;

    shmid=shmget(SHMKEY,1024,0660|IPC_CREAT); /*创建1024字节大小的共享存储区*/ 

    /****************/

 //   mutex=78;

   sen=73; /*信息量对象*/

   rec=74;    /*信号量对象，有两个信号量*/

//   mutexid=sem_init(mutex);

   senid=sem_init(sen,1);

   recid=sem_init(rec,0);

    /****************/

    

   while ((pid=fork( ))==-1); 

   if (!pid) server( ); 

   system("ipcs  -m"); 

   system("ipcs  -s"); 

   while ((pid=fork( ))==-1); 

   if (!pid) client( ); 

   system("ipcs  -m"); 

   wait(0); 

   system("ipcs  -m"); 

   wait(0); 

   system("ipcs  -m"); 

   sem_rmv(senid);

   sem_rmv(recid);

// sem_rmv(mutexid);

   shmctl(shmid,IPC_RMID,0);     /*撤消共享存储区，归还资源*/ 

}

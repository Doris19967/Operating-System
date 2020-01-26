#include <sys/sem.h> 
#include <sys/ipc.h> 
typedef union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;
int sem_init(int key)
{
int semid;
semun arg;
if((semid=semget(key,1,0660|IPC_CREAT))<0)
 fatal("sem_init:semget");
arg.val=1;
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

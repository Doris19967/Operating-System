#include<fcntl.h>
#include<stdio.h>

int fatal (const char* info)
{

  perror (info);

  exit (1);

}



int lock(int fd)
{

lseek(fd,0,SEEK_SET);

if(lockf(fd,F_LOCK,0)==-1)

fatal("lockf()");

return 0;

}



int unlock(int fd)
{

lseek(fd,0,SEEK_SET);

if(lockf(fd,F_ULOCK,0)==-1)

 fatal("unlockf()");

return 0;

}



int main( )
{      

  int pid,fd;   

char str[80];


 fd=open("tmp.txt",O_RDWR|O_CREAT|O_TRUNC,0644);

  pid=fork();       

switch(pid) 

{

    case  -1:                        

       fatal("fork fail!");

    case  0:       

  /*   sleep(1)*/

      lock(fd);

       lseek(fd, SEEK_SET,0);

       read(fd,str,sizeof(str));

       unlock(fd);

       printf("son %d:read str from tmpfile:%s\n",getpid(),str);

       exit(0); 

    default:                                 

       lock(fd);

       printf("parent %d :please enter a str for tmpfile(strlen<80):\n",getpid());

       scanf("%s",str);

       lseek(fd, SEEK_SET,0);

       write(fd,str,strlen(str));

       unlock(fd);

          wait(0);

          close(fd);

          exit(0);

   }

}

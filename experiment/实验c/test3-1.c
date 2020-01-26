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



int main()

{

int fd;   

int p1,p2,i;

char str[20];



if((fd=open("locked_file.txt",O_RDWR|O_APPEND|O_CREAT,0666))<0)

   fatal("open");  

write(fd,"=========\n",10);

while((p1=fork( ))== -1);       /*创建子进程p1*/

if (p1==0)

  {

   /* lock(fd);*/             /*加锁*/

    for(i=0;i<3;i++)

    {

     sprintf(str,"daughter %d\n",i);     

     write(fd,str,strlen(str));

     sleep(1);

     }

    /* unlock(fd);*/              /*解锁*/

   }

else

{

   while((p2=fork( ))==-1);  /*创建子进程p2*/

   if (p2==0)

   {

    /* lock(fd);*/             /*加锁*/

    for(i=0;i<3;i++)

    {

     sprintf(str,"son %d\n",i);

     write(fd,str,strlen(str));

     sleep(1);

    }

   /* unlock(fd);*/              /*解锁*/

    }

    else

   {

   /* lock(fd);*/             /*加锁*/

    for(i=0;i<3;i++)

     {

     sprintf(str,"parent %d\n",i);

     write(fd,str,strlen(str));

      sleep(1);

     }

    /* unlock(fd);*/              /*解锁*/

     wait(NULL);

     wait(NULL);

   }

}

close(fd);

}

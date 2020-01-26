#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
main( )
{      
        int pid;    
        pid=fork( );         /*创建子进程*/
switch(pid) 
{
               case  -1:                          /*创建失败*/
                       printf("fork fail!\n");
                       exit(1);
               case  0:                                 /*子进程*/
                     sleep(1);
		     printf("Is son:\n"); 
execl("/bin/ls","ls","-l",NULL);  
                      printf("exec fail!\n");
                      exit(1);
               default:                                 /*父进程*/
                      printf("ls parent:\n");
                   wait(0);
	       	   while(1)  sleep(1);
                       exit(0);
          }
}

#include <stdio.h> 

#include <fcntl.h> 

int fatal(char *mes) 

{ 	perror(mes); 

	exit(1); 

}

int main() 

{ 

int fd,rd; 

char str[1024];



if((fd=open("/dev/tty",O_RDONLY))<0) 

fatal("open /dev/tty");

if((rd=read(fd,str,1024))<0) 

fatal("read");

else 

printf("/dev/tty:: %s\n",str); 

close(fd); 

return 0; 

}

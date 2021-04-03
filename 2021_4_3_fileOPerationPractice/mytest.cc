#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
using namespace std;
int main()
{
   int fd=open("bite.txt",O_RDONLY); 
   if(fd<0)
   {
     perror("open err");
     return 1;
   }
   const char* msg="I love Linux";
   char buf[1024];
   read(fd,buf,strlen(msg));
   printf("%s\n",buf);
   close(fd);

  return 0;
}

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
  int fd=open("./fifo",O_WRONLY);
  if(fd>=0)
  {
   char buf[64];
   while(1)
   {
   //从键盘输入的字符到buf里
   
   printf("please write memsage# \n");
     fflush(stdout); 
   ssize_t s=read(0,buf,sizeof(buf)-1);
   if(s>0)
   {
     buf[s]=0;
     //往fd里写buf，想发s个字节
     write(fd,buf,s);
   }
  }
  }
  return 0;
}

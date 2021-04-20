#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
  if(-1==mkfifo("./fifo",0644))
  {
   perror("err");
  }
  int fd=open("./fifo",O_RDONLY);
  if(fd>=0)
  {
     char buf[64];
     while(1)
     {
       ssize_t s=read(fd,buf,sizeof(buf)-1);
      if(s>0)
      {
        buf[s]=0;
        printf("client#:  %s",buf);
      }
      else if(s==0)
      {
        //当实际读到字节为0时
      }
      else{
        perror("read err");
        break;
      }

       }
  }


  return 0;
}

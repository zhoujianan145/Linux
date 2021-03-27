#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#define SIZE 128
int main()
{
  close(1);
  int fd=open("log.txt",O_WRONLY|O_CREAT,0644);
  if(fd<0)
  {
    perror("open err!\n");
    return 0;
  }
  printf("hello world ---%d\n",fd);   
  fflush(stdout);
  close(fd);

}

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{
   int pipefd[2]={0};
    pipe(pipefd);
   pid_t id= fork();
   if(id==0)
   {
     const char* str="i am child ,child writing";
     close(pipefd[0]);
     int cout=0;
     while(1)
     {
       //子进程写
       write(pipefd[1],str,strlen(str));
       cout++;
     }
   }
   else if(id>0){
       close(pipefd[1]);
       char buf[64];
       while(1)
       {
         //第三个参数为你期望读多少,返回值为实际读了多少字节
         ssize_t s=read(pipefd[0],buf,sizeof(buf)-1);
         if(s>0)
         {
           buf[s]=0;
         }
         printf("father get message:%s\n",buf);
         sleep(5);
       }
   }
  return 0;
}

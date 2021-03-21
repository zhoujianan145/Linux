#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
  pid_t id =fork();
  if(id<0)
  {
    perror("fork err\n");
    return 1;
  }
  else if(id==0)
  {
   int count=0;
   while(count<3)
   {
     printf("child:%d is running\n",getpid());
     sleep(1);
     count++;
   }
  int i=1/0; 
   exit(12);
  }
  else{
    printf("father wait  before\n");
    int st=0;
    pid_t ret= waitpid(id,&st,0);
    if(ret>0)
    {
      printf("st:%d \n",st);
      int exit_singal=st & 0x7f;
      int exit_code=(st>>8)&(0xff);
      
      if(exit_singal)
      {
        printf("child error terminal,exit_singal:%d\n",exit_singal);
      }
      else{
        if(exit_code)
        {
               printf("child successed but result is not  right, exit_code: %d \n",exit_code);
        }
        else{
          printf("child successed  result is  right ,exit_code: %d\n ",exit_code);
        }
      }
    }
    else{
      printf("wait failed\n");
    }
    printf("father wait after\n");
  }
  return 0;
}

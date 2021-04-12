#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include"commnd.h"
int main()
{
  key_t key = ftok(PATHNAME,PROJ_ID);
  int shmid=shmget(key,SIZE,IPC_CREAT|IPC_EXCL|0666);
  sleep(5);
  if(shmid<0)
  {
    perror("err");
    return 1;
  }
  char* str= (char*)shmat(shmid,NULL,0);
  while(1)
  {
    
    //str为首元素地址，直接可以用它打印字符串，就是打印共享区里的内容
    printf("%s\n",str);
    sleep(1);
  }
  shmdt(str);
  shmctl(shmid,IPC_RMID,NULL);
  return 0;
}

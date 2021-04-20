#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include"commnd.h"
int main()
{
  //形参一样得到的key值一样
  key_t key = ftok(PATHNAME,PROJ_ID);
  //去掉权限，因为在server端已经创建共享内存。
  int shmid=shmget(key,SIZE,0);
  sleep(5);
  if(shmid<0)
  {
    perror("err");
    return 1;
  }
  //挂接，拿到地址
  char* str= (char*)shmat(shmid,NULL,0);
  char s='a';
  for(;s<='z';s++)
  {
    str[s-'a']=s;
    //5s写一次
    sleep(5);
  }
  shmdt(str);
  //shmctl(shmid,IPC_RMID,NULL);
  return 0;
}

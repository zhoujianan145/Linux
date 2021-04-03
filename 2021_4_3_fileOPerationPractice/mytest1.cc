#include<iostream>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>
using namespace std;
int main()
{
  FILE* fpfile = fopen("log.txt","w");
  const char buf[]="Linux so easy";  
  if(fpfile!=NULL)
  {
    fwrite(buf,1,strlen(buf),fpfile);
    
  }
  fclose(fpfile);
  pid_t id =fork();
  if(id<0)
  {
    perror("error");
    exit(1);
  }
  else if (id==0)
  {
      FILE* fpfile1=fopen("bite.txt","r");
      if(fpfile!=NULL)
      {
        char buf1[1024]={0};
        fread(buf1,1,strlen(buf),fpfile1);
      cout<<buf1<<endl;
      }
      
      fclose(fpfile1);

  }
  else{
    int st=0;
    waitpid(id,&st,0);
  }

  return 0;
}

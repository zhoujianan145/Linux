#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  // close(1);
  int fd=open("log.txt",O_CREAT|O_APPEND|O_WRONLY,0644);
  
  const char* str="hello write\n";
  const char* str1="hello world printf\n";
  const char* str2="hello world fprintf\n";
  const char* str3="hello world fwrite\n";
  dup2(fd,1);
  write(1,str,strlen(str));
  fwrite(str3,1,strlen(str3),stdout);
 // FILE* fp=fopen("log1.txt","w");
 // fwrite(str3,1,strlen(str3),fp);
  printf(str1);
  fprintf(stdout,str2);
  
  //fork();
  //fflush(stdout); 
  close(fd);
  return 0;
}

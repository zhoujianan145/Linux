#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 100
#define NUM  26

//找出文件名，看是输出重定向还是追加重定向，从而确定open文件的权限
void redirect(char* cmd)
{
  int fd=-1;
  char* ptr=cmd;
  int redirect_count=0;
  while(*ptr)
  {
    if(*ptr=='>')
    {
      *ptr='\0';
       ptr++;
       redirect_count++;
       if(*ptr=='>')
       {
            *ptr='\0';
            ptr++;
            redirect_count++;
       }
     //可能有空格
     //ls >> ,可能后面没跟东西
       while(*ptr!='\0' && isspace(*ptr))
       {
        ptr++;
       }
       //假如>>后面跟文件名，此时ptr指向文件名的首字母。
       char *file=ptr;
       //文件名后面可能有空格  ls >> file.txt      ；
       while(*ptr!='\0' && !isspace(*ptr))
       {
         ptr++;
       }
       *ptr='\0';
       if(redirect_count==1)
       {
           fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);
      
          
       }
      else  if(redirect_count==2)
       {
          fd=open(file,O_CREAT|O_APPEND|O_WRONLY,0644);
           
           
       }
      dup2(fd,1);
      close(fd);
    }
    //假如没有那么就遍历了一遍，啥都没影响
    ptr++;
  }
}
int main()
{

    char cmd[SIZE];
    cmd[0]=0;
    const char* cmd_line="[temp@VM-0-3-centos 13_lesson]# ";
    while(1)
    {
       printf("%s",cmd_line);
       fgets(cmd,SIZE,stdin);
        cmd[strlen(cmd)-1]='\0';
       pid_t id=fork();
       if(id<0)
       {
              perror("fork error");
              continue;
       }
       else if(id==0)
       {
         redirect(cmd);
         char* args[NUM];
         args[0]=strtok(cmd," ");
         int i=1;
         do{
            args[i]=strtok(NULL," ");
            if(args[i]==NULL)
           {
             break;
                                
           }
           i++;
                         
           }while(1);

         execvp(args[0],args);
         exit(1);
       }
       else{
          int st=0;
          waitpid(id,&st,0);
          int exit_code=st>>8 & 0xff;       
            printf("exit code:%d\n",exit_code);
          
       }
    }
  
  return 0;
}

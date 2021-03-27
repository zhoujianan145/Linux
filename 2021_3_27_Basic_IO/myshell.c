#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#define SIZE 100
#define NUM  26
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
       pid_t id=fork();
       if(id<0)
       {
              perror("fork error");
              continue;
       }
       else if(id==0)
       {
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

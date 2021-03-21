#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;
int main()
{
  pid_t id=fork();
  if(id==0)
  {
    int count=0;
    while(1)
    {
      sleep(1);

      cout<<"i am child"<<endl;
      count++;
      if(count>=15)
     {
      break;
     }
     }
    exit(0);
  }
  else{
    int count=0;
    
    while(1)
    {
      sleep(1);
      cout<<"i am father"<<endl;
      if(count==20)
      {
        wait(NULL);
      }
      count++;
    }
  }
return 0;
}

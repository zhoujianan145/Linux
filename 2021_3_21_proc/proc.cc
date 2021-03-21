#include<iostream>
#include<unistd.h>
#include<sys/types.h>
using namespace std;
int main()
{
  cout<< "i am a process:"<<getpid()<<endl;
  pid_t id=fork();
  if(id<0)
  {
    cerr<<"fork err"<<endl;
  }
  else if(id==0)
  {
       cout<<"i am son:"<<getpid()<<endl;
       sleep(2);
  }
  else{
  cout <<"i am father: "<<getpid()<<" myson pid :"<<id<<endl;
  sleep(5);
  }
  return 0;
}

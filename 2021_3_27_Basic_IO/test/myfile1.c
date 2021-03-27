#include<stdio.h>
#include<string.h>
int main()
{
  FILE* fp=fopen("log.txt","w");

  if(fp==NULL)
  {
    perror("fopen err\n");
    return 1;
  }
  const char* msg="hello world!!";
  int n=5;
  while(n--){
  fwrite(msg,strlen(msg),1,stdout);
  }
  fclose(fp);
  return 0;
}

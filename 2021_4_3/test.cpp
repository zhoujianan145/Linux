#include"Date.h"

int main()
{
  Date d1(2021,2,3);
  d1.print();
  (d1+5+5).print();
  d1.print();
  d1+=100;
  d1.print();
  d1-=100;
  d1.print();
  d1-=-100;
  d1.print();
  (d1++).print();
  d1.print();
  (++d1).print();
  Date d2(2021,2,4);
  cout<<(d2-d1)<<endl;
  return 0;
}

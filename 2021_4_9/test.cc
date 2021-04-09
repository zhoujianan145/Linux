#include<iostream>

using namespace std;

class Date
{
  public:
    Date(int year )
      :_year(year)
    {}
    void Print()
    {
      cout<<_year<<endl;
    }
  private:
    int _year;
};
int main()
{
  Date d1(2000);
  d1.Print();
  return 0;
}


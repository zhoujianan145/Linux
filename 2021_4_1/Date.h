#include<iostream>
using namespace std;

class Date{
  public:
    Date(int year=1900,int month=1,int day=1);
    ~Date();
    Date(const Date& d);
    Date& operator=(const Date& d);
    void print();
    Date& operator+=(const Date& d);
  private:
    int _year;
    int _month;
    int _day;

};

#include<iostream>
using namespace std;

class Date{
  public:
    Date(int year=1900,int month=1,int day=1);
    ~Date();
    Date(const Date& d);
    Date& operator=(const Date& d);
    void print();
    //日期与天数之间操作
    Date& operator+=(const int&  day);
    Date operator+(const int&  day);
    Date& operator-=(const int& day);
    Date operator-(const int& day);
    Date operator++(int);
    Date&  operator++();
    Date operator--(int);
    Date& operator--();
    //日期与日期之间操作
    bool operator>(const Date& d);
    bool operator==(const Date& d);
    bool operator!=(const Date& d);
    bool operator>=(const Date& d);
    bool operator<(const Date& d);
    bool operator<=(const Date& d);
    int  operator-(const Date& d);
  private:
    int _year;
    int _month;
    int _day;

};

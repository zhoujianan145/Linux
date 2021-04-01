#include"Date.h"

int GetMonthDay(int year,int month)
{
 int dayArray[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
   static int days=dayArray[month];
   if((month==2 && (year%4==0 &&year%100!=0))||year%400==0)
   {
     days=29;
   }
   return days;
}
Date::Date(int year,int month,int day)
{
 if(year>=0 && month>0 && month<13 && day>0 && day<=GetMonthDay(year,month) ) 
 {
   _year=year;
   _month=month;
   _day=day;
 }
 else{
   cout<<"日期不合法"<<endl;
 }
}
Date::~Date()
{
  _year=_month=_day=0;
}
Date::Date(const Date& s)
{
  _year=s._year;
  _month=s._month;
  _day=s._day;
}
Date& Date::operator=(const Date& d)
{
  if(this!=&d)
  {
    _year=d._year;
    _month=d._month;
    _day=d._day;
  }
 return *this;
}
void Date::print()
{
  cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
}


#include"Date.h"
//获取当前天数
int GetMonthDay(int year,int month)
{
   static int dayArray[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
   int days=dayArray[month];
   if(month==2 &&((year%4==0 &&year%100!=0)||(year%400==0)))
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

Date&  Date::operator+=(const int&  day)
{
  //1.内置类型减少值拷贝，减少对象的拷贝构造
  //2.希望在外面修改的是同一个对象
  //3.当出了作用域返回的对象还存在就传引用
      //直接自己完成+=操作
      if(day<0)
      {
        return *this-=-day;
      }
      _day+=day;
      while(_day>GetMonthDay(_year,_month))
      {
          _day-=GetMonthDay(_year,_month); 
          _month++;
          if(_month==13)
          {
             _month=1;
             _year++;
          }
          
      }
      return *this; 
}
Date Date::operator+(const int&  day) 
{
  //构造一个属性相同的对象让他去完成+操作，因为他出了作用域不在了，所以传值
  //Date temp(*this);
  //temp._day+=day;
  //while(temp._day>GetMonthDay(_year,_month))
 // {
    //_day-=GetMonthDay(_year,_month);
   // _month++;
   // if(_month==13)
   // {
      //_year++;
      //_month=1;
    //}
 // }
   Date temp(*this);
   temp+=day;
  return temp;
}
Date&  Date::operator-=(const int & day)
{
  if(day<0)
  {
    return *this+=-day;
  }
  _day-=day;
  while(_day<=0)
  {
    _month--;

  //这个语句必须在下面 _day=GetMonthDay(_year,_month)+_day;
    if(_month==0)
    {
      _year--;
      _month=12;
    }
   _day=GetMonthDay(_year,_month)+_day;
  }
  return *this;
}

 //和前面一样，-的话原对象不能改变
Date Date::operator-(const int& day)
{
   Date temp(*this);
   temp-=day;
   return temp;
}
//后置++为了和前置++区分，所以后置++有个参数int,
//但是虽然++返回的没有改变，但是最终实际上是加1了的
Date Date::operator++(int)
{
  Date ret(*this);
  *this+=1;
  return ret;
}
//前置++
Date& Date::operator++()
{
*this+=1;
return *this;
}
//后置--，虽然还是+1了，但是返回值没有变。
Date Date::operator--(int)
{
 Date temp(*this);
 *this+=1;
 return temp;
}
//前置--
Date& Date::operator--()
{
  *this+=1;
  return *this;
}
bool Date::operator>(const Date& d)
{
  if(_year>d._year)
  {
    return true;
  }
  else{
    if(_year==d._year)
    {
      if(_month>d._month)
      {
        return true;
      }
      else{
        if(_month==d._month)
        {
          if(_day>d._day)
          {
            return true;
          }
          else{
            return false;
          }
        }
        return false;
      }
    }
    else{ 
    return false;
  }

}
}

bool Date::operator==(const Date& d)
{
  return _year==d._year && _month==d._month && _day==d._day;
}
bool Date::operator!=(const Date& d)
{
  return !(*this==d);
}
bool Date::operator>=(const Date& d)
{
   return *this>d || *this==d;
}
bool Date::operator<(const Date& d)
{
return !(*this>=d);
}
bool Date::operator<=(const Date& d)
{
  return !(*this>d);
}
int Date::operator-(const Date& d)
{
  //默认认为*this大，如果小，让max始终保持大的那一个
  Date max(*this);
  Date min(d);
  //标志位，假如前面大，后面小，没有交换位置，默认为正
  int flag=1;
  if(max<min)
  {
    max=d;
    min=*this;
    //交换位置说明后者大，给减出来的数乘以-1.
    flag=-1;
  }
 int n=0;
 while(min!=max)
 {
   min++;
   n++;
 }
 return n*flag;
}

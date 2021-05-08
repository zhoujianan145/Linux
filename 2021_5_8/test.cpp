#include<iostream>
#include<string>
using namespace std;
//class person
//{
//public:
//	void print()
//	{
//		cout << _name << endl;
//	}
//protected:
//	string _name;
//};
//class student:public person
//{
//public:
//	void print(int i)
//	{
//		cout << i << endl;
//	}
//protected:
//	string _num;
//};
//
//int main()
//{
//	student s;
//	s.person::person();
//	person p;
//	p.~person();
//	return 0;
//}
//class A
//{
//public:
//	void add()
//	{
//
//	}
//};
//class B:public A
//{
//public:
//	void add(int i)
//	{
//   
//	}
//
//};
//
//class Person
//{
//public:
//	virtual void BuyTicket()const
//	{
//		cout << "正常排队-全价买票" << endl;
//     }
//	virtual ~Person()
//	{
//		cout << "~Person"<< endl;
//	}
//	
//};
//
//class Student:public Person
//{
//public:
//	virtual void BuyTicket()const
//	{
//		cout << "正常排队-半价买票" << endl;
//	}
//	virtual ~Student()
//	{
//		cout << "~student" << endl;
//	}
//};
//
//void Buy(const Person& p)
//{
//	p.BuyTicket();
//}
class A
{
public:
	int a;
};
class B: public A
{
public:
	int b;

};
class C:public A
{
public:
	int c;
};
class D:public B,public C
{
public:
	int d;
};

int main()
{
	D d;
	
	d.a = 5;

	return 0;
}
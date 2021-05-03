#pragma once
#include<iostream>
#include<vector>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
#define NUM 10

class CircleQueue{
private:
	vector<int> v;
	sem_t sem_blank;
	sem_t sem_data;
	int max_cap;
	int c_index;
	int p_index;
public:
	CircleQueue(int cap = NUM)
		:v(cap)
		, max_cap(cap)
		, c_index(0)
		, p_index(0)
	{
		sem_init(&sem_blank, 0, max_cap);
		sem_init(&sem_data, 0, 0);
	}

	~CircleQueue()
	{
		sem_destroy(&sem_blank);
		sem_destroy(&sem_data);
	}
	void P(sem_t& sem)
	{
		sem_wait(&sem);
	}
	void V(sem_t& sem)
	{
		sem_post(&sem);
	}
	void put(const int& in)
	{
		P(sem_blank);
		v[p_index++] = in;
		p_index %= max_cap;
		V(sem_data);
	}
	void get(int& out)
	{
		P(sem_data);
		out = v[c_index++];
		c_index %= max_cap;
		V(sem_blank);

	}

};
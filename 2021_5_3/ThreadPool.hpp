#include<iostream>
#include<queue>
#include<math.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;

#define NUM 5
class Task
{
private:
	int _a;

public:
	Task(){}
	Task(int a)
		:_a(a)
	{};
	void run()
	{

		cout << "pthread[" << pthread_self() << "] : " << _a << ":" << pow(_a, 2) << endl;
	}
};


class Pool
{
private:
	queue<Task*> q;
	int max_num;
	pthread_mutex_t lock;
	pthread_cond_t cond;
public:
	Pool(int max = NUM)
		:max_num(max)
	{}

	bool IsEmpty()
	{
		return q.size() == 0;
	}
	void Threadwait()
	{
		pthread_cond_wait(&cond, &lock);
	}
	void ThreadWakeUp()
	{

		pthread_cond_signal(&cond);
	}
	//外部放任务
	void put(Task& in)
	{
		LockQueue();
		q.push(&in);
		UnlockQueue();
		//放任务就把你唤醒，一次唤醒一个
		ThreadWakeUp();
	}

	//线程池线程拿任务
	void Get(Task& out)
	{

		//调用的地方加了
		Task *t = q.front();
		q.pop();
		out = *t;

	}
	static void* routine(void* args)
	{
		Pool* this_p = (Pool*)args;
		this_p->LockQueue();
		while (1)
		{
			//为空时不拿

			while (this_p->IsEmpty())
			{
				this_p->Threadwait();
			}

			Task t;
			this_p->Get(t);

			this_p->UnlockQueue();

			t.run();

		}
	}

	void PoolInit()
	{
		pthread_mutex_init(&lock, NULL);
		pthread_cond_init(&cond, NULL);

		//不关心线程id，所以用一个变量当参数就行了
		pthread_t tid;
		for (int i = 0; i<max_num; i++)
		{
			//因为成员函数routine中有两个参数，这里要传函数名和形参，形参只能传一个。用static
			// 又因为静态函数没有this指针，而里面又要调用成员函数，所以传递this指针

			pthread_create(&tid, NULL, routine, this);
		}

	}
	void LockQueue()
	{
		pthread_mutex_lock(&lock);
	}
	void UnlockQueue()
	{
		pthread_mutex_unlock(&lock);
	}


};

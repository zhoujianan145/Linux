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
	//�ⲿ������
	void put(Task& in)
	{
		LockQueue();
		q.push(&in);
		UnlockQueue();
		//������Ͱ��㻽�ѣ�һ�λ���һ��
		ThreadWakeUp();
	}

	//�̳߳��߳�������
	void Get(Task& out)
	{

		//���õĵط�����
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
			//Ϊ��ʱ����

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

		//�������߳�id��������һ������������������
		pthread_t tid;
		for (int i = 0; i<max_num; i++)
		{
			//��Ϊ��Ա����routine������������������Ҫ�����������βΣ��β�ֻ�ܴ�һ������static
			// ����Ϊ��̬����û��thisָ�룬��������Ҫ���ó�Ա���������Դ���thisָ��

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

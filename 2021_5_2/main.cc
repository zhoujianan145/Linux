#include"CircleQueue.hpp"


void* consumer(void* cq)
{

	CircleQueue* Cq = (CircleQueue*)cq;
	while (1)
	{
		int out;
		Cq->get(out);
		cout << "consumer: " << out << endl;
		sleep(1);
	}
}

void* productor(void* cq)
{
	//保证让消费者先进去，就挂起了
	sleep(1);
	CircleQueue* Cq = (CircleQueue*)cq;
	while (1)
	{

		int in = rand() % 10 + 1;
		Cq->put(in);
		cout << "productor: " << in << endl;


	}

}
int main()
{
	CircleQueue *Cq = new CircleQueue;
	pthread_t c, p;
	pthread_create(&c, NULL, consumer, (void*)Cq);
	pthread_create(&p, NULL, productor, (void*)Cq);

	pthread_join(c, NULL);
	pthread_join(p, NULL);
	delete Cq;
}

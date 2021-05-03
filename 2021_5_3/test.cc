#include"Threadpoll.hpp"

int main()
{
	Pool p;
	p.PoolInit();
	sleep(2);
	while (true)
	{
		int x = rand() % 10 + 1;

		Task t(x);

		p.put(t);
		sleep(1);
	}
	return 0;
}

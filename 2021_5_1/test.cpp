#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<math.h>
pthread_mutex_t lock;
pthread_cond_t cond;

void *routine_r1(void* args)
{
	while (1)
	{
		pthread_cond_wait(&cond, &lock);
		printf("%s get cond", (char*)args);
		printf("»î¶¯ÖÐ...\n");
	}
}
void* routine_r2(void* args)
{
	while (1)
	{
		sleep(rand() % 3 + 1);
		pthread_cond_signal(&cond);
		printf("%s signal \n", (char*)args);
	}
}
int main()
{
	pthread_t t1, t2, t3, t4, t5;

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_create(&t1, NULL, routine_r2, (void*)"thread 1");
	pthread_create(&t2, NULL, routine_r1, (void*)"thread 2");
	pthread_create(&t3, NULL, routine_r1, (void*)"thread 3");
	pthread_create(&t4, NULL, routine_r1, (void*)"thread 4");
	pthread_create(&t5, NULL, routine_r1, (void*)"thread 5");



	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);

	return 0;
}

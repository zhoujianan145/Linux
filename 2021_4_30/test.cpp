//#include<stdio.h>
//#include<pthread.h>
//#include<unistd.h>
//void* thread_run(void *args)
//{
//	while (1)
//	{
//		printf("i am %s, pid: %d ,mytid:%p \n", (char*)args, getpid(), pthread_self());
//		sleep(10);
//		break;
//	}
//	// pthread_detach(pthread_self());
//	//return (void*)10;
//	pthread_exit((void*)10);
//}
//int main()
//{
//	pthread_t tid;
//	pthread_create(&tid, NULL, thread_run, (void*)"thread 1");
//	printf("i am main pthread,pid: %d,mytid:%p \n", getpid(), pthread_self());
//
//	pthread_cancel(tid);
//	pthread_detach(tid);
//	void* ret = 0;
//	pthread_join(tid, &ret);
//	printf("thread 1 exit code %d\n", (int)ret);
//	return 0;
//}

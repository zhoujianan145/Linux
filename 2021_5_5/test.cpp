////class Foo {
////public:
////	Foo()��counter(1) {
////	}
////	public void one() { print("one"); }
////	public void two() { print("two"); }
////	public void three() { print("three"); }
////	void one(function<void()> printFirst) {
////		//unique_lock�ṩ�Զ�����/��������
////		std::unique_lock<std::mutex> lk(g_mutex);
////		// ��һ���̴߳�ӡone
////		print("one");
////		// ֪ͨǰ����ֶ��������Ա���ȴ��̲߳ű����Ѿ�������ϸ�ڼ� notify_one ��
////		counter++;
////		cv1.notify_one();
////	}
////	void two(function<void()> printSecond) {
////		std::unique_lock<std::mutex> lk(g_mutex);
////		// ������ǰ�߳�,ֱ��������������һ���̻߳��� 
////		//[this](){return counter == 2;} ����������������ѭ�������ж�;Ϊ��������
////		cv1.wait(lk, [this](){return counter == 2; });
////		// �ڶ����̴߳�ӡtwo
////		print("two");
////		counter++;
////		cv2.notify_one();
////	}
////	void three(function<void()> printThird) {
////		std::unique_lock<std::mutex> lk(g_mutex);
////		// ������ǰ�߳�,ֱ�������������ڶ����̻߳��� 
////		cv2.wait(lk, [this](){return counter == 3; });
////		//�������̴߳�ӡthree
////		print("three");
////	}
////private:
////	int counter;//�������������������жϲ�����������ʱ������
////	std::condition_variable cv1;//�����߳�2�ĵȴ��Լ�����
////	std::condition_variable cv2;//�����߳�2�ĵȴ��Լ�����
////	// ʹ��lock��unlock�ֶ�����
////	std::mutex g_mutex;
////};
//#include <semaphore.h>
//class H2O {
//public:
//	H2O() {
//		sem_init(&h_limit, 0, 2);
//		sem_init(&o_limit, 0, 1);
//	}
//	void hydrogen(function<void()> releaseHydrogen) {
//		// releaseHydrogen() outputs "H". Do not change or remove this line.
//		sem_wait(&h_limit);
//		releaseHydrogen();
//		count_h++;
//		if (count_h == 2){//ÿ����ӡ����H��Żỽ��oxygen��ӡO
//			count_h = 0;
//			sem_post(&o_limit);
//		}
//	}
//	void oxygen(function<void()> releaseOxygen) {
//		// releaseOxygen() outputs "O". Do not change or remove this line.
//		sem_wait(&o_limit);
//		releaseOxygen();
//		sem_post(&h_limit);//��ӡ��O֮����Ҫ����H�ļ���������Ϊ2
//		sem_post(&h_limit);
//	}
//private:
//	int count_h = 0;
//	sem_t h_limit;
//	sem_t o_limit;
//};

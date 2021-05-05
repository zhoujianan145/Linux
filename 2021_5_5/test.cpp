////class Foo {
////public:
////	Foo()：counter(1) {
////	}
////	public void one() { print("one"); }
////	public void two() { print("two"); }
////	public void three() { print("three"); }
////	void one(function<void()> printFirst) {
////		//unique_lock提供自动加锁/解锁功能
////		std::unique_lock<std::mutex> lk(g_mutex);
////		// 第一个线程打印one
////		print("one");
////		// 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
////		counter++;
////		cv1.notify_one();
////	}
////	void two(function<void()> printSecond) {
////		std::unique_lock<std::mutex> lk(g_mutex);
////		// 阻塞当前线程,直到条件变量被第一个线程唤醒 
////		//[this](){return counter == 2;} 匿名函数的作用是循环条件判断;为假则阻塞
////		cv1.wait(lk, [this](){return counter == 2; });
////		// 第二个线程打印two
////		print("two");
////		counter++;
////		cv2.notify_one();
////	}
////	void three(function<void()> printThird) {
////		std::unique_lock<std::mutex> lk(g_mutex);
////		// 阻塞当前线程,直到条件变量被第二个线程唤醒 
////		cv2.wait(lk, [this](){return counter == 3; });
////		//第三个线程打印three
////		print("three");
////	}
////private:
////	int counter;//用于条件变量的条件判断不满足条件的时候阻塞
////	std::condition_variable cv1;//用于线程2的等待以及唤醒
////	std::condition_variable cv2;//用于线程2的等待以及唤醒
////	// 使用lock和unlock手动加锁
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
//		if (count_h == 2){//每当打印两次H后才会唤醒oxygen打印O
//			count_h = 0;
//			sem_post(&o_limit);
//		}
//	}
//	void oxygen(function<void()> releaseOxygen) {
//		// releaseOxygen() outputs "O". Do not change or remove this line.
//		sem_wait(&o_limit);
//		releaseOxygen();
//		sem_post(&h_limit);//打印完O之后需要将将H的计数器增加为2
//		sem_post(&h_limit);
//	}
//private:
//	int count_h = 0;
//	sem_t h_limit;
//	sem_t o_limit;
//};

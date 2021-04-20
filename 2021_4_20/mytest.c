1 #include<stdio.h>
2 #include<signal.h>
3 #include<unistd.h>
4 void show_pending(sigset_t *pending)
5 {
	6   int i = 1;
	7   //只阻塞了2号信号
		8   for (; i <= 31; i++)
		9   {
		10     //i=2时，判断2号信号是否在pending表中
			11      if (sigismember(pending, i))
			12      {
			13        printf("1 ");
			14      }
		15      else{
			16        printf("0 ");
			17
		}
		18   }
	19   printf("\n");
	20 }
21 void handler(int sig)
22 {
	23   printf("%d signal was catched\n", sig);
	24 }
25 int main()
26 {
	27
		28     signal(2, handler);
	29     sigset_t block, o_block;
	30     //初始化
		31     sigemptyset(&block);
	32     sigemptyset(&o_block);
	33     //向我们的变量添加2号信号被阻塞
		34     sigaddset(&block, 2);
	35     //把我们设置好的传给pcb中，pcb为改变之前给到o_block
		36     sigprocmask(SIG_SETMASK, &block, &o_block);
	37     int count = 0;
	38     //不断获取pending表，键盘输入2号信号，过10秒之后解除屏蔽，进程就结束了
		39     while (1)
		40     {
		41     //初始化
			42     sigset_t pending;
		43     sigemptyset(&pending);
		44     //pcb中的pending，传给我们的变量
			45     sigpending(&pending);
		46     //先输出全0，当在这10s内通过键盘输入2号信号，2号信号比特位输出1，10s到达进程停止
			47     show_pending(&pending);
		48     sleep(1);
		49     count++;
		50     if (count == 10)
			51     {
			52       printf("the process will destory\n");
			53       //把他以前的经过初始化全0的block表给他，代表10s过后此时没有阻塞
				54       sigprocmask(SIG_SETMASK, &o_block, NULL);
			55     }
		56     }
	57   return 0;
	58 }
```
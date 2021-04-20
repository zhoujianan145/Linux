1 #include<stdio.h>
2 #include<signal.h>
3 #include<unistd.h>
4 void show_pending(sigset_t *pending)
5 {
	6   int i = 1;
	7   //ֻ������2���ź�
		8   for (; i <= 31; i++)
		9   {
		10     //i=2ʱ���ж�2���ź��Ƿ���pending����
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
	30     //��ʼ��
		31     sigemptyset(&block);
	32     sigemptyset(&o_block);
	33     //�����ǵı������2���źű�����
		34     sigaddset(&block, 2);
	35     //���������úõĴ���pcb�У�pcbΪ�ı�֮ǰ����o_block
		36     sigprocmask(SIG_SETMASK, &block, &o_block);
	37     int count = 0;
	38     //���ϻ�ȡpending����������2���źţ���10��֮�������Σ����̾ͽ�����
		39     while (1)
		40     {
		41     //��ʼ��
			42     sigset_t pending;
		43     sigemptyset(&pending);
		44     //pcb�е�pending���������ǵı���
			45     sigpending(&pending);
		46     //�����ȫ0��������10s��ͨ����������2���źţ�2���źű���λ���1��10s�������ֹͣ
			47     show_pending(&pending);
		48     sleep(1);
		49     count++;
		50     if (count == 10)
			51     {
			52       printf("the process will destory\n");
			53       //������ǰ�ľ�����ʼ��ȫ0��block�����������10s�����ʱû������
				54       sigprocmask(SIG_SETMASK, &o_block, NULL);
			55     }
		56     }
	57   return 0;
	58 }
```
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class udpServer
{
private:
	std::string _ip;  //ip��ַ
	int _port; //�˿ں�
	int _sock; //�׽����ļ�������
public:
	//���캯��
	udpServer(std::string ip = "127.0.0.1", int port = 8080)
		:_ip(ip)
		, _port(port)
	{}
	//��ʼ��������
	void initServer()
	{
		//1.�����׽���
		_sock = socket(AF_INET, SOCK_DGRAM, 0);
		std::cout << "sock:" << _sock << std::endl;
		//2.���ؽṹ��Э�飬ip��_port
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = inet_addr(_ip.c_str());
		local.sin_port = htons(_port);
		//3.�󶨶˿�,ʧ��ֱ�ӽ�������
		if (bind(_sock, (struct sockaddr*)&local, sizeof(local)) < 0)
		{
			std::cerr << "bind failed!" << std::endl;
			exit(1);

		}
	}
	//����������
	void start()
	{
		//1.�����ַ�����������
		std::cout << "---";
		char msg[64] = "\0";
		while (1)
		{
			//����Զ��addr�ṹ�����ڽ���ip��ַ��
			struct sockaddr_in end_point;
			socklen_t len = sizeof(end_point);
			ssize_t s = recvfrom(_sock, msg, sizeof(msg), 0, (struct sockaddr*)&end_point, &len);
			if (s > 0)
			{
				std::cout << "client#" << msg << std::endl;
				std::string echo_string = msg;
				echo_string += "[server echo!]";
				sendto(_sock, echo_string.c_str(), echo_string.size(), 0, (struct sockaddr*)&end_point, len);

			}

		}
	}
	//��������
	~udpServer()
	{
		close(_sock);
	}
};


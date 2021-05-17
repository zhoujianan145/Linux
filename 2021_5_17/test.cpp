//
//#include<iostream>
//#include<vector>
//using namespace std;
//struct TreeNode {
//	int val;
//	TreeNode *left;
//	TreeNode *right;
//	TreeNode() : val(0), left(nullptr), right(nullptr) {}
//	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//	
//};
//class Solution {
//public:
//	TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, int& prei, int left, int right)
//	{
//		if (prei > preorder.size())
//			return nullptr;
//		if (left>right)
//			return nullptr;
//		
//
//		int index = 0;
//		TreeNode* node = new TreeNode(preorder[prei]);
//		while (prei<preorder.size())
//		{
//			if (inorder[index] == preorder[prei])
//			{
//				break;
//			}
//			++index;
//		}
//
//		++prei;
//		node->left = _buildTree(preorder, inorder, prei, left, index - 1);
//		node->right = _buildTree(preorder, inorder, prei, index + 1, right);
//
//		return node;
//
//
//	}
//
//	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//		int prei = 0;
//		int left = 0;
//		int right = inorder.size() - 1;
//		TreeNode* root = _buildTree(preorder, inorder, prei, left, right);
//		return root;
//
//	}
//};
//
//int main()
//{
//	vector<int> v1 = { 3, 9, 20, 15, 7 };
//	vector<int> v2 = { 9, 3, 15, 20, 7 };
//	Solution().buildTree(v1, v2);
//	return 0;
//}
```cpp
#pragma once 

#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;

class udpClient
{
private:
	string ip;
	int port;

	int sock;
public:
	//���ӷ�������������ip��port��
	udpClient(string _ip = "127.0.0.1", int _port = 8080)
		:ip(_ip)
		, port(_port)
	{}
	void initClient()
	{
		//����socket������,Ĭ��Ϊ3
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		cout << "sock:" << sock << endl;

		//�ͻ��˲���Ҫ��
		//�����Ϣ��sockaddr _in��
		//struct sockaddr_in local;
		//local.sin_family=AF_INET;
		//ת�ɴ��
		//local.sin_port=htons(port);
		//sockaddr����һ��sin_addr�ṹ�壬�ṹ���е�saddrΪip
		//��ipתΪchar*
		//local.sin_addr.s_addr=inet_addr(ip.c_str());


		//�󶨶˿ں�
		//�����ò�ͬ�����׽��֣�ʹ��ͬһ�׽ӿڣ�����Ҫǿת
		//Ϊʲô����void*�أ��׽��ֳ��ֽ��磬void*��û���塣��Ҫ��ǰ���ݣ������޸ġ�
		// if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
		// {
		// cerr<<"bind error!\n"<<endl;
		// _exit(1);
		//}
	}
	void strat()
	{

		string msg;
		struct sockaddr_in peer;
		peer.sin_family = AF_INET;
		peer.sin_port = htons(port);
		//���ʮ����ת��4�ֽڣ���������ת����������
		peer.sin_addr.s_addr = inet_addr(ip.c_str());
		for (;;)
		{

			cout << "������" << endl;
			cin >> msg;
			if (msg == "quit")
			{
				break;
			}
			//��ȥ������
			sendto(sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));
			char echo[128];
			ssize_t s = recvfrom(sock, echo, sizeof(echo)-1, 0, nullptr, nullptr);

			if (s>0)
			{
				echo[s] = '\0';
				cout << "server###" << echo << endl;
			}

		}
	}



	~udpClient()
	{
		close(sock);
	}
};

```
main�г�ʼ����Ȼ������
```cpp
#include"udpClient.hpp"

int main()
{
	udpClient uc;
	uc.initClient();
	uc.strat();
	return 0;
}
#pragma once 

#include<iostream>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;

class udpServer
{
private:
	string ip;
	int port;

	int sock;
public:
	udpServer(string _ip = "127.0.0.1", int _port = 8080)
		:ip(_ip)
		, port(_port)
	{}
	void initServer()
	{
		//����socket������,Ĭ��Ϊ3
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		cout << "sock:" << sock << endl;
		//�����Ϣ��sockaddr _in��
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		//ת�ɴ��
		local.sin_port = htons(port);
		//sockaddr����һ��sin_addr�ṹ�壬�ṹ���е�saddrΪip
		//��ipתΪchar*
		local.sin_addr.s_addr = inet_addr(ip.c_str());


		//�󶨶˿ں�
		//�����ò�ͬ�����׽��֣�ʹ��ͬһ�׽ӿڣ�����Ҫǿת
		//Ϊʲô����void*�أ��׽��ֳ��ֽ��磬void*��û���塣��Ҫ��ǰ���ݣ������޸ġ�
		if (bind(sock, (struct sockaddr*)&local, sizeof(local))<0)
		{
			cerr << "bind error!\n" << endl;
			exit(1);
		}
	}
	void strat()
	{
		char msg[64] = { 0 };
		for (;;)
		{
			//Զ�˵���Ϣ

			struct sockaddr_in end_point;
			socklen_t len = sizeof(end_point);

			//������������ݣ�Ȼ���ӡ��ƴ��һ�·��ظ������
			ssize_t s = recvfrom(sock, msg, sizeof(msg)-1, 0, (struct sockaddr*)&end_point, &len);
			if (s>0)
			{
				msg[s] = '\0';
				cout << "client##" << msg << endl;
				string echo_string = msg;
				echo_string += "[ע������������]";
				sendto(sock, echo_string.c_str(), echo_string.size(), 0, (struct sockaddr*)&end_point, len);

			}

		}
	}



	~udpServer()
	{
		close(sock);
	}
};
```
main����ֻ��Ҫ�򵥵���������

```cpp
#include"udpServer.hpp"

int main()
{
	udpServer *up = new udpServer;
	up->initServer();
	up->strat();
	delete up;
	return 0;
}
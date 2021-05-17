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
	//连接服务器，服务器ip，port。
	udpClient(string _ip = "127.0.0.1", int _port = 8080)
		:ip(_ip)
		, port(_port)
	{}
	void initClient()
	{
		//创建socket描述符,默认为3
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		cout << "sock:" << sock << endl;

		//客户端不需要绑定
		//填充信息到sockaddr _in中
		//struct sockaddr_in local;
		//local.sin_family=AF_INET;
		//转成大端
		//local.sin_port=htons(port);
		//sockaddr中有一个sin_addr结构体，结构体中的saddr为ip
		//将ip转为char*
		//local.sin_addr.s_addr=inet_addr(ip.c_str());


		//绑定端口号
		//可以让不同类型套接字，使用同一套接口，所以要强转
		//为什么不用void*呢，套接字出现较早，void*还没定义。需要向前兼容，不能修改。
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
		//点分十进制转成4字节，主机序列转成网络序列
		peer.sin_addr.s_addr = inet_addr(ip.c_str());
		for (;;)
		{

			cout << "请输入" << endl;
			cin >> msg;
			if (msg == "quit")
			{
				break;
			}
			//发去服务器
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
main中初始化，然后启动
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
		//创建socket描述符,默认为3
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		cout << "sock:" << sock << endl;
		//填充信息到sockaddr _in中
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		//转成大端
		local.sin_port = htons(port);
		//sockaddr中有一个sin_addr结构体，结构体中的saddr为ip
		//将ip转为char*
		local.sin_addr.s_addr = inet_addr(ip.c_str());


		//绑定端口号
		//可以让不同类型套接字，使用同一套接口，所以要强转
		//为什么不用void*呢，套接字出现较早，void*还没定义。需要向前兼容，不能修改。
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
			//远端的信息

			struct sockaddr_in end_point;
			socklen_t len = sizeof(end_point);

			//从网络接收数据，然后打印，拼凑一下返回给服务端
			ssize_t s = recvfrom(sock, msg, sizeof(msg)-1, 0, (struct sockaddr*)&end_point, &len);
			if (s>0)
			{
				msg[s] = '\0';
				cout << "client##" << msg << endl;
				string echo_string = msg;
				echo_string += "[注：服务器回显]";
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
main函数只需要简单的启动即可

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
#pragma once
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#include<string.h>
using namespace std;
#define _TIME_MAX_ 200		//超时等待默认为 200 秒

//处理通信以及客户端
class TcpSocket
{
public:
	TcpSocket();
	TcpSocket(int connfd);
	~TcpSocket();

	//申请连接服务器
	int connectToHost(string ip, unsigned short port, int timeout = _TIME_MAX_);//超时等待默认为_TIME_MAX_秒
	//发送数据
	int sendMsg(string data, int timeout = _TIME_MAX_);//超时等待默认为_TIME_MAX_秒
	//接受数据
	string recvMsg(int timeout = _TIME_MAX_);//超时等待默认为_TIME_MAX_秒

	//释放
	void disConnect();

private:
	int m_socket;
};
#pragma once
#include<iostream>
#include<WinSock2.h>
#include<string.h>
#include "TcpSocket.h"

using namespace std;
#define _TIME_MAX_ 200		//超时等待默认为 200 秒

//服务器端
class TcpServer
{
public:
	TcpServer();
	~TcpServer();
	
	//创建 绑定 监听
	int setListen(unsigned short port);
	//处理客户端连接请求
	TcpSocket* acceptConn(int timeout= _TIME_MAX_);	//超时等待默认为_TIME_MAX_秒

private:
	int m_lfd;
};
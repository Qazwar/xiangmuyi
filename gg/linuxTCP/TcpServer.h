#pragma once
#include<iostream>
#include<WinSock2.h>
#include<string.h>
#include "TcpSocket.h"

using namespace std;
#define _TIME_MAX_ 200		//��ʱ�ȴ�Ĭ��Ϊ 200 ��

//��������
class TcpServer
{
public:
	TcpServer();
	~TcpServer();
	
	//���� �� ����
	int setListen(unsigned short port);
	//����ͻ�����������
	TcpSocket* acceptConn(int timeout= _TIME_MAX_);	//��ʱ�ȴ�Ĭ��Ϊ_TIME_MAX_��

private:
	int m_lfd;
};
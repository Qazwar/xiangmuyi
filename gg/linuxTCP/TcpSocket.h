#pragma once
#include<iostream>
#include<WinSock2.h>
#include<string.h>
using namespace std;
#define _TIME_MAX_ 200		//��ʱ�ȴ�Ĭ��Ϊ 200 ��

//����ͨ���Լ��ͻ���
class TcpSocket
{
public:
	TcpSocket();
	TcpSocket(int connfd);
	~TcpSocket();

	//�������ӷ�����
	int connectToHost(string ip, unsigned short port, int timeout = _TIME_MAX_);//��ʱ�ȴ�Ĭ��Ϊ_TIME_MAX_��
	//��������
	int sendMsg(string data, int timeout = _TIME_MAX_);//��ʱ�ȴ�Ĭ��Ϊ_TIME_MAX_��
	//��������
	string recvMsg(int timeout = _TIME_MAX_);//��ʱ�ȴ�Ĭ��Ϊ_TIME_MAX_��

	//�ͷ�
	void disConnect();

private:
	int m_socket;
};
#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include"Hash.h"
#include"RsaCrypto.h"
#include"Request.h"
#include"Factory.h"
#include"Codec.h"
#include"TcpSocket.h"

using namespace std;

//�ͻ���ִ�нṹ��
struct  ClientInfo
{
	int maxNode;		//ͨ������
	string shmKey;		//�ڴ��ַ
	string clientID;	//�ͻ���ID
	string serverID;	//������ID
	string serverIP;	//������IP
	unsigned int  serverPort;	//�������˿ں�

};


//�ͻ���ִ����
class ClientOP
{
public:
	//��Ҫ.json�������ļ�
	ClientOP(string fileName);
	~ClientOP();

	//API
	//��ԿЭ��
	bool seckeyAgree();
	//��ԿУ��
	void seckeyCheck();
	//��Կע��
	void seckeyWriteOff();

private:
	ClientInfo m_info;
};


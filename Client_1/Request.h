#pragma once
#include"Codec.h"
#include"msg.pb.h"
#include<iostream>
using namespace std;

//�ͻ������л��ṹ��
struct RequestInfo
{
	int cmd;			//1. �������� 
		//1: ��ԿЭ��
		//2����ԿУ��
		//3����Կע��
	string clientID;	//2. �ͻ��˵���ݣ���ţ�
	string serverID;	//3. ����������ݣ���ţ�
	string sign;		//4. Я�������ݣ�ǩ����
	string data;		//5. ����
};

//�ͻ������л�
class RequestCodec :
	public Codec
{
public:
	RequestCodec();
	//��Ҫ���������
	RequestCodec(string encstr);
	//��Ҫ����Ľṹ��
	RequestCodec(RequestInfo* info);

	//��ʼ������
	void initMessage(string encstr);
	//��ʼ���ṹ��
	void initMessage(RequestInfo* info);

	//��дCodec�麯��
	//����
	string encodeMsg();
	//����
	void* decodeMsg();
	~RequestCodec();

private:
	string m_encstr;
	RequestMsg m_msg;
};
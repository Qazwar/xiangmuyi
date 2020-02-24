#pragma once
#include"Codec.h"
#include"msg.pb.h"
#include<iostream>
using namespace std;

//��������л��ṹ��
struct RespondInfo
{
	int status;				//����ֵ
	int seckeyID;		//�Գ���Կ���� keysn
	string clientID;	//�ͻ��˱��
	string serverID;	//���������
	string data;		//�������������

};


//��������л���
class ResponseCode :
	public Codec
{
public:
	ResponseCode();
	//���������
	ResponseCode(string encstr);
	//���������
	ResponseCode(RespondInfo* info);
	void initMessage(string encstr);
	void initMessage(RespondInfo* info);

	//����
	string encodeMsg();
	//����
	void* decodeMsg();
	~ResponseCode();

private:
	string m_encstr;
	RespondMsg m_msg;
};
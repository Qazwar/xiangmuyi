#pragma once
#include"Request.h"
#include"Response.h"
#include<iostream>

using namespace std;
//���������
class BaseFactory
{
public:
	BaseFactory();
	~BaseFactory();
	//��������������Codec����
	virtual Codec* createFactory();
};

//����1
class RequestFactory :
	public BaseFactory
{
public:
	RequestFactory();
	//����һ���������
	RequestFactory(string enc);
	//����һ���������
	RequestFactory(RequestInfo* info);
	~RequestFactory();
	//��д����
	//��������������Request   Codec����
	Codec* createFactory();
private:
	bool m_flag;
	string m_encStr;
	RequestInfo* m_info;
};

//����2
class RespondFactory :
	public BaseFactory
{
public:
	RespondFactory();
	//����һ���������
	RespondFactory(string enc);
	//����һ���������
	RespondFactory(RespondInfo* info);
	~RespondFactory();
	//��д����
	//��������������Respond   Codec����
	Codec* createFactory();
private:
	bool m_flag;
	string m_encStr;
	RespondInfo* m_info;
};

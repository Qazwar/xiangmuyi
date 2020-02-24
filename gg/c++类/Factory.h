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

	virtual Codec* createFactory();
};

//����1
class RequestFactory :
	public BaseFactory
{
public:
	RequestFactory();
	RequestFactory(string enc);
	RequestFactory(RequestInfo* info);
	~RequestFactory();
	//��д����
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
	RespondFactory(string enc);
	RespondFactory(RespondInfo* info);
	~RespondFactory();
	//��д����
	Codec* createFactory();
private:
	bool m_flag;
	string m_encStr;
	RespondInfo* m_info;
};

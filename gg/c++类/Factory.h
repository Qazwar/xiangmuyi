#pragma once
#include"Request.h"
#include"Response.h"
#include<iostream>

using namespace std;
//工厂类基类
class BaseFactory
{
public:
	BaseFactory();
	~BaseFactory();

	virtual Codec* createFactory();
};

//子类1
class RequestFactory :
	public BaseFactory
{
public:
	RequestFactory();
	RequestFactory(string enc);
	RequestFactory(RequestInfo* info);
	~RequestFactory();
	//重写创建
	Codec* createFactory();
private:
	bool m_flag;
	string m_encStr;
	RequestInfo* m_info;
};

//子类2
class RespondFactory :
	public BaseFactory
{
public:
	RespondFactory();
	RespondFactory(string enc);
	RespondFactory(RespondInfo* info);
	~RespondFactory();
	//重写创建
	Codec* createFactory();
private:
	bool m_flag;
	string m_encStr;
	RespondInfo* m_info;
};

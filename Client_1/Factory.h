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
	//创建出编解码对象Codec基类
	virtual Codec* createFactory();
};

//子类1
class RequestFactory :
	public BaseFactory
{
public:
	RequestFactory();
	//创建一个解码对象
	RequestFactory(string enc);
	//创建一个编码对象
	RequestFactory(RequestInfo* info);
	~RequestFactory();
	//重写创建
	//创建出编解码对象Request   Codec基类
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
	//创建一个解码对象
	RespondFactory(string enc);
	//创建一个编码对象
	RespondFactory(RespondInfo* info);
	~RespondFactory();
	//重写创建
	//创建出编解码对象Respond   Codec基类
	Codec* createFactory();
private:
	bool m_flag;
	string m_encStr;
	RespondInfo* m_info;
};

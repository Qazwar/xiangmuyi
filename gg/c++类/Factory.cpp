#include "Factory.h"

//基类
BaseFactory::BaseFactory()
{
}

BaseFactory::~BaseFactory()
{
}

Codec* BaseFactory::createFactory()
{
	return NULL;
}

//子类1
RequestFactory::RequestFactory()
{	//构造

}

RequestFactory::RequestFactory(string enc)
{	//反序列数据
	m_flag = true;
	m_encStr = enc;
}

RequestFactory::RequestFactory(RequestInfo* info)
{	//序列化数据
	m_flag = false;
	m_info = info;
}

RequestFactory::~RequestFactory()
{	//析构
}

Codec* RequestFactory::createFactory()
{
	Codec* c = NULL;
	if (m_flag)
	{
		c = new RequestCodec(m_info);
	}
	else
	{
		c = new RequestCodec(m_encStr);
	}
	return c;
}

//子类2
RespondFactory::RespondFactory()
{	//构造
}

RespondFactory::RespondFactory(string enc)
{	//反序列化数据
	m_flag = false;
	m_encStr = enc;
}

RespondFactory::RespondFactory(RespondInfo* info)
{	//序列化数据
	m_flag = true;
	m_info = info;
}

RespondFactory::~RespondFactory()
{	//析构
}

Codec* RespondFactory::createFactory()
{
	Codec* c = NULL;
	if (m_flag)
	{
		c = new ResponseCode(m_info);
	}
	else
	{
		c = new ResponseCode(m_encStr);
	}
	return c;
}

#include "Factory.h"

//����
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

//����1
RequestFactory::RequestFactory()
{	//����

}

RequestFactory::RequestFactory(string enc)
{	//����������
	m_flag = true;
	m_encStr = enc;
}

RequestFactory::RequestFactory(RequestInfo* info)
{	//���л�����
	m_flag = false;
	m_info = info;
}

RequestFactory::~RequestFactory()
{	//����
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

//����2
RespondFactory::RespondFactory()
{	//����
}

RespondFactory::RespondFactory(string enc)
{	//�����л�����
	m_flag = false;
	m_encStr = enc;
}

RespondFactory::RespondFactory(RespondInfo* info)
{	//���л�����
	m_flag = true;
	m_info = info;
}

RespondFactory::~RespondFactory()
{	//����
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

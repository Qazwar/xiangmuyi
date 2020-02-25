#include "Response.h"

ResponseCode::ResponseCode()
{
}

ResponseCode::ResponseCode(string encstr)
{
	initMessage(encstr);
}

ResponseCode::ResponseCode(RespondInfo* info)
{
	initMessage(info);
}

void ResponseCode::initMessage(string encstr)
{
	m_encstr = encstr;
}

void ResponseCode::initMessage(RespondInfo* info)
{
	m_msg.set_status(info->status);
	m_msg.set_seckeyid(info->seckeyID);
	m_msg.set_clientid(info->clientID);
	m_msg.set_serverid(info->serverID);
	m_msg.set_data(info->data);
}

string ResponseCode::encodeMsg()
{
	string output;
	m_msg.SerializeToString(&output);
	return output;
}

void* ResponseCode::decodeMsg()
{
	m_msg.ParseFromString(m_encstr);
	return &m_msg;
}

ResponseCode::~ResponseCode()
{
}

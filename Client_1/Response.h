#pragma once
#include"Codec.h"
#include"msg.pb.h"
#include<iostream>
using namespace std;

//服务端序列化结构体
struct RespondInfo
{
	int status;				//返回值
	int seckeyID;		//对称密钥编码 keysn
	string clientID;	//客户端编号
	string serverID;	//服务器编号
	string data;		//服务器端随机数

};


//服务端序列化类
class ResponseCode :
	public Codec
{
public:
	ResponseCode();
	//解码的数据
	ResponseCode(string encstr);
	//编码的数据
	ResponseCode(RespondInfo* info);
	void initMessage(string encstr);
	void initMessage(RespondInfo* info);

	//编码
	string encodeMsg();
	//解码
	void* decodeMsg();
	~ResponseCode();

private:
	string m_encstr;
	RespondMsg m_msg;
};
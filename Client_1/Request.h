#pragma once
#include"Codec.h"
#include"msg.pb.h"
#include<iostream>
using namespace std;

//客户端序列化结构体
struct RequestInfo
{
	int cmd;			//1. 报文类型 
		//1: 密钥协商
		//2：密钥校验
		//3：密钥注销
	string clientID;	//2. 客户端的身份（编号）
	string serverID;	//3. 服务器的身份（编号）
	string sign;		//4. 携带的数据（签名）
	string data;		//5. 数据
};

//客户端序列化
class RequestCodec :
	public Codec
{
public:
	RequestCodec();
	//需要解码的数据
	RequestCodec(string encstr);
	//需要编码的结构体
	RequestCodec(RequestInfo* info);

	//初始化数据
	void initMessage(string encstr);
	//初始化结构体
	void initMessage(RequestInfo* info);

	//重写Codec虚函数
	//编码
	string encodeMsg();
	//解码
	void* decodeMsg();
	~RequestCodec();

private:
	string m_encstr;
	RequestMsg m_msg;
};
#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include"Hash.h"
#include"RsaCrypto.h"
#include"Request.h"
#include"Factory.h"
#include"Codec.h"
#include"TcpSocket.h"

using namespace std;

//客户端执行结构体
struct  ClientInfo
{
	int maxNode;		//通信类型
	string shmKey;		//内存地址
	string clientID;	//客户端ID
	string serverID;	//服务器ID
	string serverIP;	//服务器IP
	unsigned int  serverPort;	//服务器端口号

};


//客户端执行类
class ClientOP
{
public:
	//需要.json的配置文件
	ClientOP(string fileName);
	~ClientOP();

	//API
	//密钥协商
	bool seckeyAgree();
	//密钥校验
	void seckeyCheck();
	//密钥注销
	void seckeyWriteOff();

private:
	ClientInfo m_info;
};


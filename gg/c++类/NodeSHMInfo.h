#pragma once
#include<iostream>
using namespace std;

//共享内存子类结构体
struct NodeSHMInfo
{
	int status;			//返回状态
	int seckeyID;		//
	string clientID;	//客户端ID
	string serverID;	//服务器ID
	string seckey;		//钥匙
	string pubkey;		//钥匙
};
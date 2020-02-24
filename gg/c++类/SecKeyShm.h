#pragma once
#include<iostream>
#include<string.h>
#include"NodeSHMInfo.h"
#include"BaseShm.h"
using namespace std;

//共享内存子类
class SecKeyShm:
	public BaseShm
{
public:
	//构造
	SecKeyShm(int key);
	SecKeyShm(int key, int maxNode);
	SecKeyShm(string name);
	SecKeyShm(string name, int maxNode);
	~SecKeyShm();

	//API
	//读操作
	int shmWrite(NodeSHMInfo* pNodeInfo);	
	//写操作
	int shmRead(string clientID, string serverID, NodeSHMInfo* pNodeInfo);	

private:
	int m_maxNode;
};
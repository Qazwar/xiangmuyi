#pragma once
#include<iostream>
#include<string.h>
#include"NodeSHMInfo.h"
#include"BaseShm.h"
using namespace std;

//�����ڴ�����
class SecKeyShm:
	public BaseShm
{
public:
	//����
	SecKeyShm(int key);
	SecKeyShm(int key, int maxNode);
	SecKeyShm(string name);
	SecKeyShm(string name, int maxNode);
	~SecKeyShm();

	//API
	//������
	int shmWrite(NodeSHMInfo* pNodeInfo);	
	//д����
	int shmRead(string clientID, string serverID, NodeSHMInfo* pNodeInfo);	

private:
	int m_maxNode;
};
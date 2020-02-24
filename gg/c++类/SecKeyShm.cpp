#include "SecKeyShm.h"

SecKeyShm::SecKeyShm(int key):BaseShm(key)
{

}

SecKeyShm::SecKeyShm(int key, int maxNode)
	: BaseShm(key,maxNode* sizeof(NodeSHMInfo))
	,m_maxNode(maxNode)
{
}

SecKeyShm::SecKeyShm(string name) : BaseShm(name)
{
}

SecKeyShm::SecKeyShm(string name, int maxNode) 
	: BaseShm(name,maxNode*sizeof(NodeSHMInfo))
	,m_maxNode(maxNode)
{
}

SecKeyShm::~SecKeyShm()
{
}

int SecKeyShm::shmWrite(NodeSHMInfo* pNodeInfo)
{
	int ret = -1;
	//���������ڴ�
	NodeSHMInfo* pAddr = static_cast<NodeSHMInfo*>(mapShm());
	if (pAddr == NULL)
	{
		return ret;
	}

	//ѭ�����ҽڵ��Ƿ����
	NodeSHMInfo* p = NULL;
	int i;
	for (i = 0; i < m_maxNode; ++i)
	{
		//��ȡ�½ڵ��ַ
		p = pAddr + 1;
		if(strcmp(p->clientID.c_str(),pAddr->clientID.c_str())==0&&
			strcmp(p->serverID.data(), pAddr->serverID.data()) == 0)
		{
			//���ڸĽڵ���Կ	������Կ
			memcpy(p, pNodeInfo, sizeof(NodeSHMInfo));
			break;
		}
	}
	//���û�иýڵ���Կ��Ѱ�ҿ�λ
	if (i == m_maxNode)
	{
		//������
		NodeSHMInfo tmpNodeInfo;
		memset(&tmpNodeInfo, 0, sizeof(NodeSHMInfo));
		//Ѱ�ҿ�λ
		for (i = 0; i < m_maxNode; ++i)
		{
			//��ȡ�½ڵ��ַ
			p = pAddr + 1;
			if (memcmp(&tmpNodeInfo,p,sizeof(NodeSHMInfo))==0)
			{
				ret = 0;
				//���ڿսڵ�	д����Կ
				memcpy(p, pNodeInfo, sizeof(NodeSHMInfo));
				break;
			}
		}
	}
	//û�з�����Կ
	if (i == m_maxNode)
	{
		ret = -1;
	}
	//�黹��Կ
	unmapShm();
	return ret;
}

int SecKeyShm::shmRead(string clientID, string serverID, NodeSHMInfo* pNodeInfo)
{
	int ret = -1;
	//���������ڴ�
	NodeSHMInfo* pAddr = static_cast<NodeSHMInfo*>(mapShm());
	if (pAddr == NULL)
	{
		return ret;
	}
	//Ѱ����Կ�Ƿ����
	int i;
	NodeSHMInfo* p;
	for (i = 0; i < m_maxNode; ++i)
	{
		//���½ڵ�
		p = pAddr + 1;
		if (strcmp(p->clientID.data(), clientID.data()) == 0 &&
			strcmp(p->serverID.data(), serverID.data()) == 0)
		{
			//���ڸýڵ�	������������ֵ
			memcpy(pNodeInfo, p, sizeof(NodeSHMInfo));
			break;
		}
	}
	//��������ڴ���
	if (i == m_maxNode)
	{
		ret = -1;
	}
	//�黹�����ڴ�
	unmapShm();
	return ret;
}

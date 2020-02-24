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
	//关联共享内存
	NodeSHMInfo* pAddr = static_cast<NodeSHMInfo*>(mapShm());
	if (pAddr == NULL)
	{
		return ret;
	}

	//循环查找节点是否存在
	NodeSHMInfo* p = NULL;
	int i;
	for (i = 0; i < m_maxNode; ++i)
	{
		//获取新节点地址
		p = pAddr + 1;
		if(strcmp(p->clientID.c_str(),pAddr->clientID.c_str())==0&&
			strcmp(p->serverID.data(), pAddr->serverID.data()) == 0)
		{
			//存在改节点密钥	更新密钥
			memcpy(p, pNodeInfo, sizeof(NodeSHMInfo));
			break;
		}
	}
	//如果没有该节点密钥就寻找空位
	if (i == m_maxNode)
	{
		//空数据
		NodeSHMInfo tmpNodeInfo;
		memset(&tmpNodeInfo, 0, sizeof(NodeSHMInfo));
		//寻找空位
		for (i = 0; i < m_maxNode; ++i)
		{
			//获取新节点地址
			p = pAddr + 1;
			if (memcmp(&tmpNodeInfo,p,sizeof(NodeSHMInfo))==0)
			{
				ret = 0;
				//存在空节点	写入密钥
				memcpy(p, pNodeInfo, sizeof(NodeSHMInfo));
				break;
			}
		}
	}
	//没有放入密钥
	if (i == m_maxNode)
	{
		ret = -1;
	}
	//归还密钥
	unmapShm();
	return ret;
}

int SecKeyShm::shmRead(string clientID, string serverID, NodeSHMInfo* pNodeInfo)
{
	int ret = -1;
	//关联共享内存
	NodeSHMInfo* pAddr = static_cast<NodeSHMInfo*>(mapShm());
	if (pAddr == NULL)
	{
		return ret;
	}
	//寻找密钥是否存在
	int i;
	NodeSHMInfo* p;
	for (i = 0; i < m_maxNode; ++i)
	{
		//更新节点
		p = pAddr + 1;
		if (strcmp(p->clientID.data(), clientID.data()) == 0 &&
			strcmp(p->serverID.data(), serverID.data()) == 0)
		{
			//存在该节点	给传出参数赋值
			memcpy(pNodeInfo, p, sizeof(NodeSHMInfo));
			break;
		}
	}
	//如果不存在存在
	if (i == m_maxNode)
	{
		ret = -1;
	}
	//归还共享内存
	unmapShm();
	return ret;
}

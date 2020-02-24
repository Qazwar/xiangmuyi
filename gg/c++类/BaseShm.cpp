#include "BaseShm.h"

const char Rand = 'g';
BaseShm::BaseShm(int key)
{
    getShmID(key, 0, 0);
}

BaseShm::BaseShm(int key, int size)
{
    //创建共享内存
    getShmID(key,size,IPC_CREAT|0664);
}

BaseShm::BaseShm(string name)
{
    //根据名字获得key
    int key=ftok(name.data(), Rand);
    //创建共享内存
    getShmID(key, 0, 0);
}

BaseShm::BaseShm(string name, int size)
{
    int key=ftok(name.data(), Rand);
    getShmID(key,size,IPC_CREAT|0664);
}

BaseShm::~BaseShm()
{
}

void* BaseShm::mapShm()
{
    //获得共享内存地址 并且设置读写权限
    m_shmAddr=shmat(m_shmID,NULL,0);
    if (m_shmAddr == (void*)-1)
    {
        return NULL;
    }
	return m_shmAddr;
}

int BaseShm::unmapShm()
{
    //归还
    int ret=shmdt(m_shmAddr);
	return ret;
}

int BaseShm::delShm()
{
    //标记即将删除
    int ret=shmctl(m_shmID,IPC_RMID,NULL);
	return ret;
}

int BaseShm::getShmID(key_t key, int shmSize, int flag)
{
    cout << "share memory size: " << shmSize << endl;
    m_shmID=shmget(key,shmSize,flag);
    if (m_shmID == -1)
    {
        //写log日志
        cout << "shmat 失败" << endl;
    }
    //共享内存地址初始化
    if (shmSize > 0)
    {
        void* addr = shmat(m_shmID, NULL, 0);
        memset(addr, 0, shmSize);
        shmdt(addr);
    }
	return m_shmID;
}

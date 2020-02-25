#pragma once
#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define _SIZE_ 1024
using namespace std;

//共享内存父类
class BaseShm
{
public:
	//构造
	//通过key打开共享内存
	BaseShm(int key);
	// 通过传递进来的key创建/打开共享内存
	BaseShm(int key, int size);
	// 通过路径打开共享内存
	BaseShm(string name);
	// 通过路径创建/打开共享内存
	BaseShm(string name, int size);
	~BaseShm();

	//API
	//获得共享内存首地址
	void* mapShm();	
	//归还共享内存首地址
	int unmapShm();	
	//标记删除
	int delShm();	

private:
	//内部API
	int getShmID(key_t key, int shmSize, int flag);

private:
	int m_shmID;
	void* m_shmAddr;
};

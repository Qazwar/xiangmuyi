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

//�����ڴ游��
class BaseShm
{
public:
	//����
	//ͨ��key�򿪹����ڴ�
	BaseShm(int key);
	// ͨ�����ݽ�����key����/�򿪹����ڴ�
	BaseShm(int key, int size);
	// ͨ��·���򿪹����ڴ�
	BaseShm(string name);
	// ͨ��·������/�򿪹����ڴ�
	BaseShm(string name, int size);
	~BaseShm();

	//API
	//��ù����ڴ��׵�ַ
	void* mapShm();	
	//�黹�����ڴ��׵�ַ
	int unmapShm();	
	//���ɾ��
	int delShm();	

private:
	//�ڲ�API
	int getShmID(key_t key, int shmSize, int flag);

private:
	int m_shmID;
	void* m_shmAddr;
};

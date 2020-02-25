#pragma once
#include<string>
#include<openssl/aes.h>
using namespace std;
class AesCrypto
{
public:
	// ��ʹ�� 16byte, 24byte, 32byte ����Կ
	AesCrypto(string key);
	~AesCrypto();

	//API
	//����
	string aesCBCEncrypt(string data);
	//����
	string aesCBCDecrypt(string encStr);

private:
	//�ڲ�����API
	//����
	string aesCrypto(string data, int crypto);
	//�㷨
	void generateIvec(unsigned char* ivec);

private:
	//������Կ
	AES_KEY m_encKey;
	//������Կ
	AES_KEY m_decKey;
	//��Կ�ַ���
	string m_key;
};
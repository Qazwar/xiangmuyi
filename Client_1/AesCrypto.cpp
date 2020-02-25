#include "AesCrypto.h"

AesCrypto::AesCrypto(string key)
{
	//����ַ����ĳ���
	int bits = key.size();
	//����Ϸ���
	if (bits == 16 || bits == 24 || bits == 32)
	{
		const unsigned char* aesKey = (const unsigned char*)key.data();
		AES_set_encrypt_key(aesKey, bits * 8, &m_encKey);
		AES_set_decrypt_key(aesKey, bits * 8, &m_decKey);
		m_key = key;
	}

}

AesCrypto::~AesCrypto()
{
}

string AesCrypto::aesCBCEncrypt(string data)
{
	return aesCrypto(data, AES_ENCRYPT);
	//return string();
}

string AesCrypto::aesCBCDecrypt(string encStr)
{
	//return string();
	return aesCrypto(encStr, AES_DECRYPT);
}

string AesCrypto::aesCrypto(string data, int crypto)
{
	//�ж��Ǽ��ܻ��ǽ���
	AES_KEY* key = crypto == AES_DECRYPT ? &m_decKey : &m_encKey;

	//�����ַ�������
	int len = data.size();
	if (len % 16 != 0)
	{
		len = (len / 16 + 1) * 16;
	}
	//׼���㷨
	unsigned char ivec[AES_BLOCK_SIZE];
	generateIvec(ivec);
	//׼��ʢ�ŵĿռ�
	char* buf = new char[len];

	//��ʼ����
	AES_cbc_encrypt((const unsigned char*)data.c_str(), 
		(unsigned char*)buf, len, key, ivec, crypto);

	string tmp = string(buf, len);
	delete[]buf;
	return string(tmp);
}

void AesCrypto::generateIvec(unsigned char* ivec)
{
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
	{
		ivec[i] = m_key.at(AES_BLOCK_SIZE - 2 - i);
	}
}

#include "AesCrypto.h"

AesCrypto::AesCrypto(string key)
{
	//获得字符串的长度
	int bits = key.size();
	//检验合法性
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
	//判断是加密还是解密
	AES_KEY* key = crypto == AES_DECRYPT ? &m_decKey : &m_encKey;

	//计算字符串长度
	int len = data.size();
	if (len % 16 != 0)
	{
		len = (len / 16 + 1) * 16;
	}
	//准备算法
	unsigned char ivec[AES_BLOCK_SIZE];
	generateIvec(ivec);
	//准备盛放的空间
	char* buf = new char[len];

	//开始加密
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

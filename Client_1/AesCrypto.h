#pragma once
#include<string>
#include<openssl/aes.h>
using namespace std;
class AesCrypto
{
public:
	// 可使用 16byte, 24byte, 32byte 的秘钥
	AesCrypto(string key);
	~AesCrypto();

	//API
	//加密
	string aesCBCEncrypt(string data);
	//解密
	string aesCBCDecrypt(string encStr);

private:
	//内部调用API
	//加密
	string aesCrypto(string data, int crypto);
	//算法
	void generateIvec(unsigned char* ivec);

private:
	//加密密钥
	AES_KEY m_encKey;
	//解密密钥
	AES_KEY m_decKey;
	//密钥字符串
	string m_key;
};
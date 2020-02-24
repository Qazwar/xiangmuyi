#include "RsaCrypto.h"

Cryptographic::Cryptographic()
{
	m_privateKey = RSA_new();
	m_publicKey = RSA_new();
}

Cryptographic::Cryptographic(string fileName, bool isPrivate)
{
	m_privateKey = RSA_new();
	m_publicKey = RSA_new();
	if (isPrivate)
	{
		initprivateKey(fileName);
	}
	else
	{
		initpublicKey(fileName);
	}
}

Cryptographic::~Cryptographic()
{
}

void Cryptographic::rsaGenerateKey(int bits, string pub, string pri)
{
	RSA* rsa = RSA_new();
	//准备BIGNUM对象
	BIGNUM* bn = BN_new();
	//初始化BIGNUM
	BN_set_word(bn, 753159);

	//生产密钥
	RSA_generate_key_ex(rsa, bits, bn, NULL);

	//保存公钥
	BIO* bio = BIO_new_file(pub.c_str(), "w");
	PEM_write_bio_RSAPublicKey(bio, rsa);
	BIO_flush(bio);
	BIO_free(bio);

	//保存私钥
	BIO* bio1 = BIO_new_file(pri.c_str(), "w");
	PEM_write_bio_RSAPrivateKey(bio1, rsa,NULL,NULL,0,NULL,NULL);
	BIO_flush(bio1);
	BIO_free(bio1);

	//获得密钥对
	m_privateKey = RSAPrivateKey_dup(rsa);
	m_publicKey = RSAPublicKey_dup(rsa);

	RSA_free(rsa);
	BN_free(bn);
}

string Cryptographic::rsaEncryptPublicKey(string data)
{
	//计算数据长度
	int len = data.size();
	//准备加密后空间
	char* buf = new char[1024];

	//加密数据
	int ret=RSA_public_encrypt(len, (const unsigned char*)data.c_str(), (unsigned char*)buf, 
					m_publicKey, RSA_PKCS1_PADDING);
	if (ret == -1)
	{
		//失败
	}
	string tmp = string(buf, ret);
	delete[]buf;
	return string(tmp);
}

string Cryptographic::rsaDecryptPublicKey(string data)
{
	//计算数据长度
	int len = data.size();
	char* buf = new char[1024];

	//解密
	int ret=RSA_private_decrypt(len, (const unsigned char*)data.c_str(),
			(unsigned char*)buf, m_privateKey, RSA_PKCS1_PADDING);
	if (ret == -1)
	{
		//失败
	}

	string tmp = string(buf, ret);
	delete[]buf;

	return string(tmp);
}

string Cryptographic::signPrivateKey(string data)
{
	//准备签名后的数据空间
	char* buf = new char[1024];
	unsigned int len;
	//签名
	RSA_sign(NID_sha1, (const unsigned char*)data.c_str(), data.size(), 
		(unsigned char*)buf, &len, m_privateKey);
	
	string tmp = string(buf, len);
	delete[]buf;
	return string(tmp);
}

bool Cryptographic::verifyPublicKey(string data, string sigbuf)
{

	//签名
	int ret=RSA_verify(NID_sha1, (const unsigned char*)data.c_str(), data.size(),
		(const unsigned char*)sigbuf.c_str(), sigbuf.size(),m_publicKey);
	if (ret != 1)
	{
		return false;
	}
	
	return true;
}

bool Cryptographic::initpublicKey(string fileName)
{
	//加载公钥信息
	BIO* bio = BIO_new_file(fileName.data(), "r");
	if (!PEM_read_bio_RSAPublicKey(bio, &m_publicKey, NULL, NULL))
	{
		//失败
		return false;
	}
	BIO_free(bio);
	return true;
}

bool Cryptographic::initprivateKey(string fileName)
{
	//加载私钥信息
	BIO* bio = BIO_new_file(fileName.data(), "r");
	if (!PEM_read_bio_RSAPrivateKey(bio, &m_privateKey, NULL, NULL))
	{
		//失败
		return false;
	}
	BIO_free(bio);
	return true;
}

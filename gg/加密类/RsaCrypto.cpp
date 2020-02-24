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
	//׼��BIGNUM����
	BIGNUM* bn = BN_new();
	//��ʼ��BIGNUM
	BN_set_word(bn, 753159);

	//������Կ
	RSA_generate_key_ex(rsa, bits, bn, NULL);

	//���湫Կ
	BIO* bio = BIO_new_file(pub.c_str(), "w");
	PEM_write_bio_RSAPublicKey(bio, rsa);
	BIO_flush(bio);
	BIO_free(bio);

	//����˽Կ
	BIO* bio1 = BIO_new_file(pri.c_str(), "w");
	PEM_write_bio_RSAPrivateKey(bio1, rsa,NULL,NULL,0,NULL,NULL);
	BIO_flush(bio1);
	BIO_free(bio1);

	//�����Կ��
	m_privateKey = RSAPrivateKey_dup(rsa);
	m_publicKey = RSAPublicKey_dup(rsa);

	RSA_free(rsa);
	BN_free(bn);
}

string Cryptographic::rsaEncryptPublicKey(string data)
{
	//�������ݳ���
	int len = data.size();
	//׼�����ܺ�ռ�
	char* buf = new char[1024];

	//��������
	int ret=RSA_public_encrypt(len, (const unsigned char*)data.c_str(), (unsigned char*)buf, 
					m_publicKey, RSA_PKCS1_PADDING);
	if (ret == -1)
	{
		//ʧ��
	}
	string tmp = string(buf, ret);
	delete[]buf;
	return string(tmp);
}

string Cryptographic::rsaDecryptPublicKey(string data)
{
	//�������ݳ���
	int len = data.size();
	char* buf = new char[1024];

	//����
	int ret=RSA_private_decrypt(len, (const unsigned char*)data.c_str(),
			(unsigned char*)buf, m_privateKey, RSA_PKCS1_PADDING);
	if (ret == -1)
	{
		//ʧ��
	}

	string tmp = string(buf, ret);
	delete[]buf;

	return string(tmp);
}

string Cryptographic::signPrivateKey(string data)
{
	//׼��ǩ��������ݿռ�
	char* buf = new char[1024];
	unsigned int len;
	//ǩ��
	RSA_sign(NID_sha1, (const unsigned char*)data.c_str(), data.size(), 
		(unsigned char*)buf, &len, m_privateKey);
	
	string tmp = string(buf, len);
	delete[]buf;
	return string(tmp);
}

bool Cryptographic::verifyPublicKey(string data, string sigbuf)
{

	//ǩ��
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
	//���ع�Կ��Ϣ
	BIO* bio = BIO_new_file(fileName.data(), "r");
	if (!PEM_read_bio_RSAPublicKey(bio, &m_publicKey, NULL, NULL))
	{
		//ʧ��
		return false;
	}
	BIO_free(bio);
	return true;
}

bool Cryptographic::initprivateKey(string fileName)
{
	//����˽Կ��Ϣ
	BIO* bio = BIO_new_file(fileName.data(), "r");
	if (!PEM_read_bio_RSAPrivateKey(bio, &m_privateKey, NULL, NULL))
	{
		//ʧ��
		return false;
	}
	BIO_free(bio);
	return true;
}

#pragma once
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<string>
using namespace std;


class RsaCrypto
{
public:
	RsaCrypto();
	RsaCrypto(string fileName,bool isPrivate = true);
	~RsaCrypto();

	//AIP�ӿ�

	//�����ǶԳ���Կ��
	void rsaGenerateKey(int bits,string pub = "public.pem" , string pri = "private.pem");

	//��Կ����
	string rsaEncryptPublicKey(string data);
	//˽Կ����
	string rsaDecryptPublicKey(string data);
	//˽Կ ����ǩ��
	string signPrivateKey(string data);
	//��Կ У��ǩ��
	bool verifyPublicKey(string data, string sigbuf);
private:
	//��ʼ����Կ
	bool initpublicKey(string fileName);
	bool initprivateKey(string fileName);

	RSA* m_publicKey;	//��Կ
	RSA* m_privateKey;	//˽Կ
};
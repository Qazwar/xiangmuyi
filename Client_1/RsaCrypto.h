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

	//AIP接口

	//产生非对称密钥对
	void rsaGenerateKey(int bits,string pub = "public.pem" , string pri = "private.pem");

	//公钥加密
	string rsaEncryptPublicKey(string data);
	//私钥解密
	string rsaDecryptPublicKey(string data);
	//私钥 数字签名
	string signPrivateKey(string data);
	//公钥 校验签名
	bool verifyPublicKey(string data, string sigbuf);
private:
	//初始化公钥
	bool initpublicKey(string fileName);
	bool initprivateKey(string fileName);

	RSA* m_publicKey;	//公钥
	RSA* m_privateKey;	//私钥
};
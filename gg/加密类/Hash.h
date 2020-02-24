#pragma once
#include<openssl/md5.h>
#include<openssl/sha.h>
#include<iostream>
#include<string.h>
using namespace std;

enum HashType
{
	G_MD5,
	G_SHA1,
	G_SHA224,
	G_SHA256,
	G_SHA384,
	G_SHA512
};

class Hash
{
public:
	Hash(HashType type);
	~Hash();

	//API
	void addData(string data);	//添加数据
	string result();			//计算哈希值
private:
	//每种不同哈希运算
	//MD5
	inline void md5Init();
	inline void md5AddData(string data);
	inline string md5Result();

	//sha1
	inline void sha1Init();
	inline void sha1AddData(string data);
	inline string sha1Result();

	//sha224
	inline void sha224Init();
	inline void sha224AddData(string data);
	inline string sha224Result();

	//sha256
	inline void sha256Init();
	inline void sha256AddData(string data);
	inline string sha256Result();

	//sha384
	inline void sha384Init();
	inline void sha384AddData(string data);
	inline string sha384Result();

	//sha512
	inline void sha512Init();
	inline void sha512AddData(string data);
	inline string sha512Result();

private:
	HashType m_type;
	MD5_CTX m_md5;
	SHA_CTX m_sha1;
	SHA256_CTX m_sha224;
	SHA256_CTX m_sha256;
	SHA512_CTX m_sha384;
	SHA512_CTX m_sha512;
};
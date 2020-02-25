#include "Hash.h"

Hash::Hash(HashType type)
{
	m_type = type;
	switch (m_type)
	{
	case G_MD5:md5Init();
		break;
	case G_SHA1:sha1Init();
		break;
	case G_SHA224:sha224Init();
		break;
	case G_SHA256:sha256Init();
		break;
	case G_SHA384:sha384Init();
		break;
	case G_SHA512:sha512Init();
		break;
	}
}

Hash::~Hash()
{
}

void Hash::addData(string data)
{
	switch (m_type)
	{
	case G_MD5:md5AddData(data);
		break;
	case G_SHA1:sha1AddData(data);
		break;
	case G_SHA224:sha224AddData(data);
		break;
	case G_SHA256:sha256AddData(data);
		break;
	case G_SHA384:sha384AddData(data);
		break;
	case G_SHA512:sha512AddData(data);
		break;
	}
}

string Hash::result()
{
	string tmp;
	switch (m_type)
	{
	case G_MD5:tmp = md5Result();
		break;
	case G_SHA1:tmp = sha1Result();
		break;
	case G_SHA224:tmp = sha224Result();
		break;
	case G_SHA256:tmp = sha256Result();
		break;
	case G_SHA384:tmp = sha384Result();
		break;
	case G_SHA512:tmp = sha512Result();
		break;
	}
	return string(tmp);
}

inline void Hash::md5Init()
{
	MD5_Init(&m_md5);
}

inline void Hash::md5AddData(string data)
{
	MD5_Update(&m_md5, data.data(), strlen(data.data()));
}

inline string Hash::md5Result()
{
	unsigned char md[MD5_DIGEST_LENGTH];
	char tmp[MD5_DIGEST_LENGTH * 2 + 1];
	MD5_Final(md, &m_md5);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		sprintf(&tmp[i * 2], "%02x", md[i]);
	}
	return string(tmp);
}


inline void Hash::sha1Init()
{
	SHA1_Init(&m_sha1);
}

inline void Hash::sha1AddData(string data)
{
	
	SHA1_Update(&m_sha1, data.data(), strlen(data.data()));
}

inline string Hash::sha1Result()
{
	unsigned char md[SHA_DIGEST_LENGTH];
	char tmp[SHA_DIGEST_LENGTH * 2 + 1];
	SHA1_Final(md, &m_sha1);
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		sprintf(&tmp[i * 2], "%02x", md[i]);
	}
	return string(tmp);
}


inline void Hash::sha224Init()
{
	SHA224_Init(&m_sha224);
}

inline void Hash::sha224AddData(string data)
{
	SHA224_Update(&m_sha224, data.data(), strlen(data.data()));
}

inline string Hash::sha224Result()
{
	unsigned char md[SHA224_DIGEST_LENGTH];
	char tmp[SHA224_DIGEST_LENGTH * 2 + 1];
	SHA224_Final(md, &m_sha224);
	for (int i = 0; i < SHA224_DIGEST_LENGTH; i++)
	{
		sprintf(&tmp[i * 2], "%02x", md[i]);
	}

	return string(tmp);
}

inline void Hash::sha256Init()
{
	SHA256_Init(&m_sha256);
}

inline void Hash::sha256AddData(string data)
{
	SHA256_Update(&m_sha256, data.data(), strlen(data.data()));
}

inline string Hash::sha256Result()
{
	unsigned char md[SHA256_DIGEST_LENGTH];
	char tmp[SHA256_DIGEST_LENGTH * 2 + 1];
	SHA256_Final(md, &m_sha256);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(&tmp[i * 2], "%02x", md[i]);
	}
	return string(tmp);
}

inline void Hash::sha384Init()
{
	SHA384_Init(&m_sha384);
}

inline void Hash::sha384AddData(string data)
{
	SHA384_Update(&m_sha384, data.data(), strlen(data.data()));
}

inline string Hash::sha384Result()
{
	unsigned char md[SHA384_DIGEST_LENGTH];
	char tmp[SHA384_DIGEST_LENGTH * 2 + 1];
	SHA384_Final(md, &m_sha384);
	for (int i = 0; i < SHA384_DIGEST_LENGTH; i++)
	{
		sprintf(&tmp[i * 2], "%02x", md[i]);
	}
	return string(tmp);
}

inline void Hash::sha512Init()
{
	SHA512_Init(&m_sha512);
}

inline void Hash::sha512AddData(string data)
{
	SHA512_Update(&m_sha512, data.data(), strlen(data.data()));
}

inline string Hash::sha512Result()
{
	unsigned char md[SHA512_DIGEST_LENGTH];
	char tmp[SHA512_DIGEST_LENGTH * 2 + 1];
	SHA512_Final(md, &m_sha512);
	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
	{
		sprintf(&tmp[i * 2], "%02x", md[i]);
	}
	return string(tmp);
}

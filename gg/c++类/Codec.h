#pragma once
#include"msg.pb.h"
#include<sstream>
using namespace std;

//���л�����
class Codec
{
public:
	Codec();

	//API
	//�������л�
	virtual std::string encodeMsg();
	//�����л�
	virtual void* decodeMsg();

	virtual ~Codec();
};

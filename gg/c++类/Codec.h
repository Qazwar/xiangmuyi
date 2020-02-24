#pragma once
#include"msg.pb.h"
#include<sstream>
using namespace std;

//序列化基类
class Codec
{
public:
	Codec();

	//API
	//数据序列化
	virtual std::string encodeMsg();
	//反序列化
	virtual void* decodeMsg();

	virtual ~Codec();
};

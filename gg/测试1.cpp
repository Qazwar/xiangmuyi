#include<iostream>
#include"msg.pb.h"
#include"Codec.h"
#include"Request.h"

int main()
{

	RequestMsg reqMsg;
	reqMsg.set_clientid("���");
	reqMsg.set_serverid("������");

	return 0;
}
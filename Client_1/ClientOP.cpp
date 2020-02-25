#include "ClientOP.h"

ClientOP::ClientOP(string fileName)
{
	//读磁盘中的Json文件
	//使用CJson Reader -> Value
	//将VAlue填写到结构体
}

ClientOP::~ClientOP()
{
}

bool ClientOP::seckeyAgree()
{
	//生产密钥
	RsaCrypto rsa;
	rsa.rsaGenerateKey(1024);
	//打开公钥文件
	ifstream ifs;
	ifs.open("public.pem");
	stringstream buffer;
	buffer << ifs.rdbuf();

	//计算公钥的哈希值
	string pubKey = buffer.str();
	Hash hash(G_SHA1);
	hash.addData(pubKey);

	//对哈希值进行签名
	string signPub=rsa.signPrivateKey(hash.result());
	
	//创建工厂对象
	RequestInfo reqInfo;	
	reqInfo.sign = signPub;				//数字签名
	reqInfo.data = pubKey;				//公钥
	reqInfo.cmd = 1;					//通信类型
	reqInfo.clientID = m_info.clientID;	//客户端ID
	reqInfo.serverID = m_info.serverID;	//服务器ID
	BaseFactory* factory = new RequestFactory(&reqInfo);
	//创建出编解码对象Codec基类
	Codec* code=factory->createFactory();
	//数据序列化
	string encodeMsg=code->encodeMsg();

	//开始通信
	TcpSocket* cSocek = new TcpSocket();
	//申请连接
	cSocek->connectToHost(m_info.serverIP, m_info.serverPort);
	//发送数据
	cSocek->sendMsg(encodeMsg);
	//等待回收
	string recvMsg=cSocek->recvMsg();

	//解码数据
	factory = new RespondFactory(recvMsg);
	code = factory->createFactory();
	RespondMsg* resMsg = (RespondMsg*)code->decodeMsg();

	//判断是否成功
	if (resMsg->status() == 0)
	{
		//失败
		return false;
	}

	//把对称密钥数据读出来保存到磁盘文件
	string aesKey=rsa.rsaDecryptPublicKey(resMsg->data());
	cout << "sss:" << aesKey;
	//存储到共享内存

	//释放资源

	//关闭套接字

}


void ClientOP::seckeyCheck()
{
}

void ClientOP::seckeyWriteOff()
{
}

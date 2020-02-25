#include "ClientOP.h"

ClientOP::ClientOP(string fileName)
{
	//�������е�Json�ļ�
	//ʹ��CJson Reader -> Value
	//��VAlue��д���ṹ��
}

ClientOP::~ClientOP()
{
}

bool ClientOP::seckeyAgree()
{
	//������Կ
	RsaCrypto rsa;
	rsa.rsaGenerateKey(1024);
	//�򿪹�Կ�ļ�
	ifstream ifs;
	ifs.open("public.pem");
	stringstream buffer;
	buffer << ifs.rdbuf();

	//���㹫Կ�Ĺ�ϣֵ
	string pubKey = buffer.str();
	Hash hash(G_SHA1);
	hash.addData(pubKey);

	//�Թ�ϣֵ����ǩ��
	string signPub=rsa.signPrivateKey(hash.result());
	
	//������������
	RequestInfo reqInfo;	
	reqInfo.sign = signPub;				//����ǩ��
	reqInfo.data = pubKey;				//��Կ
	reqInfo.cmd = 1;					//ͨ������
	reqInfo.clientID = m_info.clientID;	//�ͻ���ID
	reqInfo.serverID = m_info.serverID;	//������ID
	BaseFactory* factory = new RequestFactory(&reqInfo);
	//��������������Codec����
	Codec* code=factory->createFactory();
	//�������л�
	string encodeMsg=code->encodeMsg();

	//��ʼͨ��
	TcpSocket* cSocek = new TcpSocket();
	//��������
	cSocek->connectToHost(m_info.serverIP, m_info.serverPort);
	//��������
	cSocek->sendMsg(encodeMsg);
	//�ȴ�����
	string recvMsg=cSocek->recvMsg();

	//��������
	factory = new RespondFactory(recvMsg);
	code = factory->createFactory();
	RespondMsg* resMsg = (RespondMsg*)code->decodeMsg();

	//�ж��Ƿ�ɹ�
	if (resMsg->status() == 0)
	{
		//ʧ��
		return false;
	}

	//�ѶԳ���Կ���ݶ��������浽�����ļ�
	string aesKey=rsa.rsaDecryptPublicKey(resMsg->data());
	cout << "sss:" << aesKey;
	//�洢�������ڴ�

	//�ͷ���Դ

	//�ر��׽���

}


void ClientOP::seckeyCheck()
{
}

void ClientOP::seckeyWriteOff()
{
}

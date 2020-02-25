#include"TcpSocket.h"

TcpSocket::TcpSocket()
{
}

TcpSocket::TcpSocket(int connfd)
{
	m_socket = connfd;
}

TcpSocket::~TcpSocket()
{
}
//�������ӷ�����
int TcpSocket::connectToHost(string ip, unsigned short port, int timeout)	//��ʱ�ȴ�Ĭ��Ϊ_TIME_MAX_��
{
	int ret;
	//��д�ͻ��˵�ַ�ṹ
	struct sockaddr_in serv;
	socklen_t len = sizeof(serv);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	//�ж��Ƿ������ӳ�ʱ
	if (timeout > 0)
	{
		//�����ļ�������Ϊ������ģʽ
		int f1 = fcntl(m_socket, F_GETFL);
		f1 |= O_NONBLOCK;
		fcntl(m_socket, F_SETFL, f1);

		//��ʼ���ӷ�����
		ret = connect(m_socket, (struct sockaddr*) & serv, len);
		//����-1������ʧ�� errno==EINPROGRESS ˵�������ӹ�����
		if (ret == -1 && errno == EINPROGRESS)
		{
			//����������

			//�����ļ���������������
			fd_set wrset;
			FD_ZERO(&wrset);
			FD_SET(m_socket, &wrset);

			//������ʱ
			struct timeval time { timeout, 0 };

			//�����ļ�����������
			ret = select(m_socket + 1, NULL, &wrset, NULL, &time);
			if (ret < 0)
			{
				if (ret == -1 && errno == ETIMEDOUT)	//��ʱ�ź�
				{
					//��ʱ
					ret = errno;
					return ret;
				}
				else	//�����ź�
				{
					//�����쳣
					return ret;
				}
			}
			else if(ret>0)
			{
				//д����������,��Ҫ��һ���ж��ǳɹ�����ʧ��
				int op;
				socklen_t len=sizeof(op);
				//����getsockopt�鿴״̬
				getsockopt(m_socket,SOL_SOCKET,SO_ERROR,&op,&len);
				if(op==0)
				{
					//��������
				}
				else if(op==-1)
				{
					//��������
					ret=errno;
					return ret;
				}
			}

		}

		//�������ӵ�������
		//�ļ����������û�����״̬
		f1 &= ~O_NONBLOCK;
		fcntl(m_socket, F_SETFL, f1);

	}


	return 0;
}
//��������
int TcpSocket::sendMsg(string data, int timeout)	//��ʱ�ȴ�Ĭ��Ϊ_TIME_MAX_��
{
	int ret;
	// 1	�����ļ���������������
	fd_set wrset;
	FD_ZERO(&wrset);
	FD_SET(m_socket, &wrset);

	// 2	���ó�ʱʱ��
	struct timeval time { timeout, 0 };

	// 3	ί���ں˰�æ����ļ�����������
	do
	{
		ret = select(m_socket + 1, NULL, &wrset, NULL, &time);
	} while (ret == -1 && errno == EINTR);			//�������źŴ�ϣ��������
	//��ʱ
	if (ret == -1)
	{
		ret = errno;
		return ret;
	}

	//����д��
	send(m_socket, data.c_str(), sizeof(data.c_str()), 0);
	return 0;
}
//��������
string TcpSocket::recvMsg(int timeout)	//��ʱ�ȴ�Ĭ��Ϊ_TIME_MAX_��
{
	int ret;
	// 1	�����ļ���������������
	fd_set rdset;
	FD_ZERO(&rdset);
	FD_SET(m_socket, &rdset);

	// 2	���ó�ʱʱ��
	struct timeval time { timeout, 0 };

	// 3	ί���ں˰�æ����ļ�����������
	do
	{
		ret = select(m_socket + 1, NULL, &rdset, NULL, &time);
	} while (ret == -1 && errno == EINTR);			//�������źŴ�ϣ��������
	//��ʱ
	if (ret == -1)
	{
		//��ʱ����
		return NULL;
	}

	//��������ɶ�
	char buf[1024];
	recv(m_socket, buf, sizeof(buf), 0);

	return buf;
}
//�ͷ�
void TcpSocket::disConnect()
{
	close(m_socket);
}

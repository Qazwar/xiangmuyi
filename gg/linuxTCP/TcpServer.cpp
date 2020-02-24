#include "TcpServer.h"
#include <sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{
}
//���� �� ����
int TcpServer::setListen(unsigned short port)
{
	// 1	�����׽���
	int ret = 0;
	m_lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_lfd == -1)
	{
		//perror("TcpServer setListen socket:");
		ret = errno;
		return ret;
	}

	//	���ö˿ڸ���
	int no = 1;
	if (setsockopt(m_lfd, SOL_SOCKET, SO_REUSEADDR, &no, sizeof(no)))
	{
		//perror("TcpServer setListen setsockopt:");
		ret = errno;
		return ret;
	}

	// 2	�󶨷���˵�ַ�ṹ
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if ((bind(m_lfd, (sockaddr*)&serv, sizeof(serv))) == -1)
	{
		//perror("TcpServer setListen bind:");
		ret = errno;
		return ret;
	}

	// 3	���ü���
	if (listen(m_lfd, 128) == -1)
	{
		//perror("TcpServer setListen listen:");
		ret = errno;
		return ret;
	}
	return ret;
}
//����ͻ�����������
TcpSocket* TcpServer::acceptConn(int timeout)
{
	int ret;
	//���ӳ�ʱ����
	if (timeout > 0)
	{
		//���ü����ļ�����������
		fd_set rdset;
		FD_ZERO(&rdset);
		FD_SET(m_lfd, &rdset);

		struct timeval time{timeout,0};
		//�����ں�ȥ����
		
		do 
		{
			ret = select(m_lfd + 1, &rdset, NULL, NULL, &time);
		} while (ret < 0 && errno == EINTR);
		if (ret <= 0)
		{
			//��ʱ�ˣ����ȴ���
			return NULL;
		}
	}
	
	//һ��select��⵽�ļ��������Ķ�����˵���ڹ涨ʱ���������TCP��������
	//��ʱ��accept��������
	struct sockaddr_in client;
	int clen = sizeof(client);
	int cfd;
	if ((cfd = accept(m_lfd, (sockaddr*)&client, &clen)) == -1)
	{
		//perror("TcpServer acceptConn accept:");
		return NULL;
	}
	TcpSocket* sock = new TcpSocket(cfd);

	return sock;
}

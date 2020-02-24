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
//创建 绑定 监听
int TcpServer::setListen(unsigned short port)
{
	// 1	创建套接字
	int ret = 0;
	m_lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_lfd == -1)
	{
		//perror("TcpServer setListen socket:");
		ret = errno;
		return ret;
	}

	//	设置端口复用
	int no = 1;
	if (setsockopt(m_lfd, SOL_SOCKET, SO_REUSEADDR, &no, sizeof(no)))
	{
		//perror("TcpServer setListen setsockopt:");
		ret = errno;
		return ret;
	}

	// 2	绑定服务端地址结构
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

	// 3	设置监听
	if (listen(m_lfd, 128) == -1)
	{
		//perror("TcpServer setListen listen:");
		ret = errno;
		return ret;
	}
	return ret;
}
//处理客户端连接请求
TcpSocket* TcpServer::acceptConn(int timeout)
{
	int ret;
	//连接超时处理
	if (timeout > 0)
	{
		//设置监听文件描述符集合
		fd_set rdset;
		FD_ZERO(&rdset);
		FD_SET(m_lfd, &rdset);

		struct timeval time{timeout,0};
		//交给内核去监听
		
		do 
		{
			ret = select(m_lfd + 1, &rdset, NULL, NULL, &time);
		} while (ret < 0 && errno == EINTR);
		if (ret <= 0)
		{
			//超时了，不等待了
			return NULL;
		}
	}
	
	//一旦select检测到文件描述符的动静，说明在规定时间内完成了TCP三次握手
	//这时候accept不在阻塞
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

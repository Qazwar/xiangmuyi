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
//申请连接服务器
int TcpSocket::connectToHost(string ip, unsigned short port, int timeout)	//超时等待默认为_TIME_MAX_秒
{
	int ret;
	//填写客户端地址结构
	struct sockaddr_in serv;
	socklen_t len = sizeof(serv);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	//判断是否有连接超时
	if (timeout > 0)
	{
		//设置文件描述符为非阻塞模式
		int f1 = fcntl(m_socket, F_GETFL);
		f1 |= O_NONBLOCK;
		fcntl(m_socket, F_SETFL, f1);

		//开始连接服务器
		ret = connect(m_socket, (struct sockaddr*) & serv, len);
		//返回-1：连接失败 errno==EINPROGRESS 说明在连接过程种
		if (ret == -1 && errno == EINPROGRESS)
		{
			//正在连接中

			//创建文件描述符监听集合
			fd_set wrset;
			FD_ZERO(&wrset);
			FD_SET(m_socket, &wrset);

			//监听超时
			struct timeval time { timeout, 0 };

			//设置文件描述符监听
			ret = select(m_socket + 1, NULL, &wrset, NULL, &time);
			if (ret < 0)
			{
				if (ret == -1 && errno == ETIMEDOUT)	//超时信号
				{
					//超时
					ret = errno;
					return ret;
				}
				else	//其他信号
				{
					//其他异常
					return ret;
				}
			}
			else if(ret>0)
			{
				//写缓冲区可用,需要进一步判断是成功还是失败
				int op;
				socklen_t len=sizeof(op);
				//调用getsockopt查看状态
				getsockopt(m_socket,SOL_SOCKET,SO_ERROR,&op,&len);
				if(op==0)
				{
					//连接正常
				}
				else if(op==-1)
				{
					//错误连接
					ret=errno;
					return ret;
				}
			}

		}

		//正常连接到服务器
		//文件描述符设置回阻塞状态
		f1 &= ~O_NONBLOCK;
		fcntl(m_socket, F_SETFL, f1);

	}


	return 0;
}
//发送数据
int TcpSocket::sendMsg(string data, int timeout)	//超时等待默认为_TIME_MAX_秒
{
	int ret;
	// 1	创建文件描述符监听集合
	fd_set wrset;
	FD_ZERO(&wrset);
	FD_SET(m_socket, &wrset);

	// 2	设置超时时间
	struct timeval time { timeout, 0 };

	// 3	委托内核帮忙监测文件描述符集合
	do
	{
		ret = select(m_socket + 1, NULL, &wrset, NULL, &time);
	} while (ret == -1 && errno == EINTR);			//被其他信号打断，继续监测
	//超时
	if (ret == -1)
	{
		ret = errno;
		return ret;
	}

	//正常写入
	send(m_socket, data.c_str(), sizeof(data.c_str()), 0);
	return 0;
}
//接受数据
string TcpSocket::recvMsg(int timeout)	//超时等待默认为_TIME_MAX_秒
{
	int ret;
	// 1	创建文件描述符监听集合
	fd_set rdset;
	FD_ZERO(&rdset);
	FD_SET(m_socket, &rdset);

	// 2	设置超时时间
	struct timeval time { timeout, 0 };

	// 3	委托内核帮忙监测文件描述符集合
	do
	{
		ret = select(m_socket + 1, NULL, &rdset, NULL, &time);
	} while (ret == -1 && errno == EINTR);			//被其他信号打断，继续监测
	//超时
	if (ret == -1)
	{
		//超时返回
		return NULL;
	}

	//监测正常可读
	char buf[1024];
	recv(m_socket, buf, sizeof(buf), 0);

	return buf;
}
//释放
void TcpSocket::disConnect()
{
	close(m_socket);
}

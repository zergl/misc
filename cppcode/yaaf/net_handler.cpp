#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "proto/hello.pb.h"

#include "net_handler.h"

NetHandler *NetHandler::_inst = NULL;

int NetHandler::add_handle(socket_t &s, bool oneshot)
{
	struct epoll_event ev;
	ev.data.fd	= s;
	ev.events	= EPOLLIN|EPOLLET;
	if(oneshot)
	{
		ev.events |= EPOLLONESHOT;
	}

	int ret = epoll_ctl(m_epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);
	fprintf(stdout, 
		"add_handle() -- ret: %d fd: %d /%s\n", 
		ret, s, s == m_listen_fd ? "LISTENING" : "CONNECTED");

	return ret;
}

int NetHandler::del_handle(socket_t &s)
{
	return epoll_ctl(m_epfd, EPOLL_CTL_DEL, s, NULL);
}

int NetHandler::accept_new_connection()
{
	struct	sockaddr remote_addr;
	socklen_t	sockaddr_len;
	int conn_fd = accept(m_listen_fd, (sockaddr *)&remote_addr, &sockaddr_len);
	return conn_fd <= 0 ? conn_fd : add_handle(conn_fd);
}

int NetHandler::run_loop(const uint32_t timeout_ms)
{
	static const uint16_t MAX_EVENT_NUM = 1024;
	struct epoll_event m_events[MAX_EVENT_NUM];

    while(true)
    {
        int nfds = ::epoll_wait(m_epfd, m_events, MAX_EVENT_NUM, timeout_ms);
        if(nfds <= 0)
			continue;

		for(auto i = 0; i < nfds; i++)
        {
            if(m_events[i].data.fd == m_listen_fd)
			{
				accept_new_connection();
            }
			else if(m_events[i].events & EPOLLIN) 
			{
                do_read(m_events[i].data.fd);
            } 
			else if(m_events[i].events & EPOLLOUT) 
			{
                do_write();
            } 
			else if(m_events[i].events & EPOLLERR) 
			{
                do_except();
            }
        }
    }
}

int NetHandler::Serve(const std::string &svc_ip, const uint16_t svc_port, const uint32_t timeout_ms, int backlog)
{
	m_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(m_listen_fd <= 0)
	{
		fprintf(stderr, "socket() failed, ret=%d\n", m_listen_fd);
		return -1;
	}
	
	struct sockaddr_in svc_addr;
	memset(&svc_addr, 0, sizeof(svc_addr)); //string.h
	svc_addr.sin_family			= AF_INET;
	svc_addr.sin_addr.s_addr	= svc_ip.size() > 0 ? inet_addr(svc_ip.c_str()) : htonl(INADDR_ANY);
	svc_addr.sin_port			= htons(svc_port);

	int ret = bind(m_listen_fd, (sockaddr *)&svc_addr, sizeof(svc_addr));
	if(ret < 0)
	{
		fprintf(stderr, "bind() failed, ret=%d\n", ret);
		return -1;
	}

	//port reused
	const int reuse = 1;
	setsockopt(m_listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

	// nonblocking
	int flag;
	fcntl(m_listen_fd, F_GETFL, &flag);
	fcntl(m_listen_fd, F_SETFL, flag | O_NONBLOCK);

	ret = listen(m_listen_fd, backlog);
	if(ret < 0)
	{
		fprintf(stderr, "listen() failed, ret=%d\n", ret);
		return -1;
	}

	fprintf(stdout, "  *** Serving on %s:%u listen_fd:%d\n", 
		svc_ip.c_str(), svc_port, m_listen_fd);
	
	//epoll fd
	m_epfd = epoll_create(64);
	if(m_epfd <= 0)
	{
		fprintf(stderr, "epoll_create() failed, ret=%d\n", m_epfd);
		return -1;
	}
	fprintf(stdout, " -- m_epfd=%d\n", m_epfd);

	//add listen_fd to epoll
	add_handle(m_listen_fd, true);

	return run_loop(timeout_ms);
}

int NetHandler::do_read(const socket_t &s) 
{
	static char buffer[4096] = {0};
	int ret = read(s, &buffer, 4097);
	fprintf(stdout, "RECV[%d]:\n%s\n", ret, buffer);
	if(ret <= 0) 
	{
		return ret;
	}

	helloworld::HeartbeatSync sync;
	sync.set_seq_(1);

	return 0;
};

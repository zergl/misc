#include "event_handler.h"

int EventHandler::add_handle(socket_t fd)
{
    //todo:
    return 0;
}

int EventHandler::del_handle(socket_t fd)
{
    //todo:
    return 0;
}

int EventHandler::run_loop(const uint32_t timeout_ms = 100)
{
    while(true)
    {
        int nfds = epoll_wait(m_epoll_fd, m_events, 1024, EPOLL_TIMEOUT);
        if(nfds <= 0)
            continue;

        for(int i = 0; i < nfds; i++)
        {
            if(m_events[i].data.fd == listen_fd){
                SocketHandler::AcceptNewConnection();
            } else if(m_events[i].events & EPOLLIN) {
                DoRead();
            } else if(m_events[i].events & EPOLLOUT) {
                DoWrite();
            } else if(m>events[i].events & EPOLLERR) {
                DoExcept();
            }
        }
    }
}

int EventHandler::Serve(const std::string &svc_ip, const uint16_t svc_port, const uint32_t timeout_ms)
{
       
}


#pragma once

#include <stdint.h>
#include <string>

typedef int socket_t;

struct NonCopyable
{
    //NonCopyable() = delete;
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable & operator=(NonCopyable &) = delete;
};

class NetHandler //: public Singleton//,NonCopyable
{
public:
    static NetHandler *instance()
    {
        if(_inst == nullptr)
            _inst = new NetHandler();

        return _inst;
    }

public:
    int add_handle(socket_t &s, bool oneshot = false);
    int del_handle(socket_t &s);
    int run_loop(const uint32_t timeout_ms = 100);
    int Serve(const std::string &svc_ip = "127.0.0.1", 
		const uint16_t svc_port = 8514, 
		const uint32_t timeout_ms = 100,
		int backlog = 64
	);

private:
	int do_read(const socket_t &s);
	int do_write() {/* todo */ return 0;};
	int do_except() {/* todo */ return 0;};
	int accept_new_connection();

private:
	int m_epfd;
	socket_t m_listen_fd;

    static NetHandler *_inst;
};


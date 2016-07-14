#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

struct NonCopyable
{
    NonCopyable() = delete;
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable & operator=(NonCopyable &) = delete;
};

class EventHandler : public Singleton, public NonCopyable
{
public:
    static EventHandler *instance()
    {
        if(_inst == nullptr)
            _inst = new EventHandler();

        return _inst;
    }

public:
    int add_handle(socket_t &fd);
    int del_handle(socket_t &fd);
    int run_loop(const uint32_t timeout_ms = 100);
    int Serve(const std::string svc_ip, const uint16_t svc_port, const uint32_T timeout_ms = 10);

private:
    static EventHandler *_inst;
};

#endif // _EVENT_HANDLER_H_


#pragma once
#include "observer.h"
#include "output_observer.h"
#include "record_observer.h"

using handle_t = void *;

class owner
{
private:
    std::size_t N{0};
    int bkt{0};
    std::string sys_time;
    std::string str;
    std::vector<std::string> v;
    static std::unique_ptr<handler> ob;
    static std::mutex mx;

    owner(){};
    owner(const owner&);
    owner& operator=( owner& );
public:
    owner(std::size_t bulk);
    ~owner(){}
    static void init();
    void receive(const char *data, std::size_t size);
    void disconnect();
};


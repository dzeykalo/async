#include "owner.h"

std::unique_ptr<handler> owner::ob;
std::mutex owner::mx;

owner::owner(std::size_t bulk)
{
    N = bulk;
    if (!owner::ob)
    {
        std::lock_guard<std::mutex> lock(owner::mx);
        if (!owner::ob)
        {
            owner::ob = std::make_unique<handler>();
            owner::ob->subscribe(std::make_unique<output_observer>());
            owner::ob->subscribe(std::make_unique<record_observer>());
        }
    }
}

void owner::receive(const char *data, std::size_t size)
{
    owner::ob->line_count();

    for(std::size_t i = 0; i < size; ++i)
    {
        switch (bkt)
        {
        case 0:
            if (data[i]  == '{'){
                ++bkt;
                owner::ob->push(str, v, sys_time);
            }
            else if(data[i]  == '\n'){
                owner::ob->push(str, v, sys_time);
            }
            else{
                str.push_back(data[i]);
            }
                

            if ( v.size() >= N || bkt > 0)
                owner::ob->show(v, sys_time);
            break;

        default:
            if (data[i]  == '{')
            {
                ++bkt;
                v.push_back(str);
                str.clear();
            }
            else if (data[i]  == '}')
            {
                v.push_back(str);
                str.clear();
                if (--bkt < 1 )
                {
                    owner::ob->show(v, sys_time);
                    bkt = 0;
                }
            }
            else 
            {
                if (data[i]  == '\n')
                    owner::ob->push(str, v, sys_time);
                else
                    str.push_back(data[i]);
            }
            break;
        }
    }
}

void owner::disconnect()
{
    if (bkt == 0)
        owner::ob->show(v, sys_time);
}

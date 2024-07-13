#include "zinxtimer.h"
#include<sys/timerfd.h>

timermanager timermanager::m;
bool zinxtimerchannel::Init()
{
    bool retflag = false;
    int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if(fd >= 0){
        struct itimerspec p = {
            {1,0}, {1,0}
        };
        if(timerfd_settime(fd, 0, &p, nullptr) == 0)
        {
            tfd = fd;
            retflag = true;
        }
    }

    return retflag;
}

bool zinxtimerchannel::ReadFd(std::string &_input)
{
    bool retflag = false;
    char buf[8] = {0};
    if(read(tfd, buf, sizeof(buf)) == sizeof(buf))
    {
        retflag = true;
        _input.assign(buf, 8);
    }


    return retflag;
}

bool zinxtimerchannel::WriteFd(std::string &_output)
{
    return false;
}

void zinxtimerchannel::Fini()
{
    close(tfd);
    tfd = -1;
}

int zinxtimerchannel::GetFd()
{
    return tfd;
}
helloworld *hello = new helloworld;

AZinxHandler *zinxtimerchannel::GetInputNextStage(BytesMsg &_oInput)
{
    return &timermanager::getInstance();
}

IZinxMsg *helloworld::InternelHandle(IZinxMsg &_oInput)
{
    auto out = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
    string s = "hello world";
    ZinxKernel::Zinx_SendOut(s, *out);
    return nullptr;
}

AZinxHandler *helloworld::GetNextHandler(IZinxMsg &_oNextMsg)
{
    return nullptr;
}
std::string zinxtimerchannel::GetChannelInfo()
{
    return "timerfd";
}

timermanager::timermanager()
{

    for(int i = 0; i < 10; ++i)
    {
        std::list<timerProc*> l;
        tpl.push_back(l);
    }
}

IZinxMsg *timermanager::InternelHandle(IZinxMsg &_oInput)
{
    m_currenindex++;
    m_currenindex %= 10;
    // for(auto &i : tpl[m_currenindex])
    // {
    //     if(i->count<=0){
    //         i->Proc();
    //     }
    //     else
    //         i->count--;
    // }

    for(auto it = tpl[m_currenindex].begin(); it != tpl[m_currenindex].end();)
    {
        if((*it)->count <= 0){
            (*it)->Proc();
            // timermanager::getInstance().delTimerProc(*it);
            auto t = *it;
            it = tpl[m_currenindex].erase(it);
            timermanager::getInstance().addTimerProc(t);
        }
        else{
            (*it)->count--;
            ++it;
        }
        
    }
    return nullptr;
}

	
AZinxHandler *timermanager::GetNextHandler(IZinxMsg &_oNextMsg)
{
    return nullptr;
}

void timermanager::addTimerProc(timerProc *t)
{
    int index = (m_currenindex+t->getTimerSeconds())%10;
    tpl[index].push_back(t);
    t->count = t->getTimerSeconds()/10;
}
void timermanager::delTimerProc(timerProc *t)
{
    for(auto &p:tpl)
        for(auto i:p)
        {
            if(i == t)
            {
                p.remove(t);
                return;
            }
        }
}
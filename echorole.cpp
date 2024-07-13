#include "echorole.h"
#include"cmdmsg.h"
#include"cmdcheck.h"
#include<ctime>
echo::echo()
{
    
}
echo::~echo()
{

}
bool echo::Init()
{
    return true;
}

UserData *echo::ProcMsg(UserData &_poUserData)
{
    GET_REF2DATA(cmdmsg,input, _poUserData);
    cmdmsg *temp = new cmdmsg(input);
    ZinxKernel::Zinx_SendOut(*temp, *(cmdcheck::getInstance()));
    return nullptr;//返回的是下一个处理环节，这里暂时不需要返回nullptr
}

void echo::Fini()
{
}

bool inoutcontrol::Init()
{
    return true;
}

UserData *inoutcontrol::ProcMsg(UserData &_poUserData)
{
    GET_REF2DATA(cmdmsg, info, _poUserData);
    if(info.isopen)
    {

        ZinxKernel::Zinx_Add_Channel(*inout);
    }
    else
    {
        auto p = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        inout = p;
        ZinxKernel::Zinx_Del_Channel(*p);

    }

    return nullptr;
}

void inoutcontrol::Fini()
{
}

bool dateecho::Init()
{
    Irole *ir = nullptr;
    for(auto &i:ZinxKernel::Zinx_GetAllRole())
    {
        if(dynamic_cast<echo*>(i) != nullptr)
        {
            ir = i;
        }
    }

    SetNextProcessor(*ir);
    return true;
}

UserData *dateecho::ProcMsg(UserData &_poUserData)
{
    GET_REF2DATA(cmdmsg, msg, _poUserData);

    if(msg.iscmd && msg.isdate)
    {
        time_t cctime = time(nullptr);
        tm* ttime = localtime(&cctime);


        string curtime = string(asctime(ttime)) + msg.msg;
        auto mmsg = new cmdmsg;
        mmsg->msg = curtime;
        return mmsg;
    }
    else
    {
        auto mmsg = new cmdmsg;
        mmsg->msg = msg.msg;
        return mmsg;
    }

    return nullptr;
}

void dateecho::Fini()
{
}

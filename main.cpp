#include <zinx.h>
#include "echorole.h"
#include "cmdcheck.h"
#include "stdinout.h"
#include "zinxtimer.h"

class _hello : public timerProc
{
public:
    virtual void Proc()
    {
        auto out = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        string s = "_hello world";
        ZinxKernel::Zinx_SendOut(s, *out);
    }
    virtual int getTimerSeconds()
    {
        return 3;
    }
};

class __hello : public timerProc
{
public:
    virtual void Proc()
    {
        auto out = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        string s = "__hello world";
        ZinxKernel::Zinx_SendOut(s, *out);
    }
    virtual int getTimerSeconds()
    {
        return 5;
    }
};


int main()
{



    ZinxKernel::ZinxKernelInit();
    timermanager::getInstance().addTimerProc(new _hello);
    timermanager::getInstance().addTimerProc(new __hello);

    ZinxKernel::Zinx_Add_Channel(*(new inputchannel()));
    ZinxKernel::Zinx_Add_Channel(*(new outputchannel()));
    ZinxKernel::Zinx_Add_Channel(*(new ZinxTCPListen(6666, new mytcpfact)));
    ZinxKernel::Zinx_Add_Role(*(new echo()));
    ZinxKernel::Zinx_Add_Role(*(new inoutcontrol()));
    ZinxKernel::Zinx_Add_Role(*(new dateecho()));
    ZinxKernel::Zinx_Add_Channel(*(new zinxtimerchannel));
    ZinxKernel::Zinx_Run();
    ZinxKernel::ZinxKernelFini();

    return 0;
}
#include "cmdcheck.h"
#include"cmdmsg.h"
#include"echorole.h"

cmdcheck *cmdcheck::_cmdcheck = new cmdcheck();
UserData *cmdcheck::raw2request(std::string _szInput)
{
    if(_szInput == "exit")
    {
        ZinxKernel::Zinx_Exit();
        return nullptr;
    }
    auto p = new cmdmsg();
    p->msg = _szInput;
    if(_szInput == "open")
     {
        p->isopen = true;
        p->iscmd = true;
        p->isioc = true;

     }
    else if(_szInput == "close")
     {
        p->isopen = false;
        p->iscmd = true;
        p->isioc = true;
     }
     else if(_szInput == "date")
     {
        p->iscmd = true;
        p->isdate = true;
        p->isioc = false;
     }
     else if(_szInput == "cleardate")
     {
        p->iscmd = true;
        p->isdate = false;
        p->isioc = false;
     }

    return p;
}

std::string *cmdcheck::response2raw(UserData &_oUserData)
{
    GET_REF2DATA(cmdmsg, output, _oUserData);
    return new string(output.msg);
}

Irole *cmdcheck::GetMsgProcessor(UserDataMsg &_oUserDataMsg)
{
    channelname = _oUserDataMsg.szInfo;
    if(channelname == "stdin")
        channelname = "stdout";
    auto list = ZinxKernel::Zinx_GetAllRole();
    auto p = dynamic_cast<cmdmsg*>(_oUserDataMsg.poUserData);
    bool iscmd = p->iscmd;
    for(auto i : list)
    {
        if(p->isioc)
        {
            auto retrole = dynamic_cast<inoutcontrol *>(i);
            if(retrole != nullptr)
                return retrole;
        }
        else
        {
            auto retrole = dynamic_cast<dateecho*>(i);
            if(retrole != nullptr)
                return retrole;
        } 
            
    }
    return nullptr;

}

Ichannel *cmdcheck::GetMsgSender(BytesMsg &_oBytes)
{
    return ZinxKernel::Zinx_GetChannel_ByInfo(channelname);
}

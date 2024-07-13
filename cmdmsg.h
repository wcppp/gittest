#pragma once
#include<zinx.h>
#include<string>

using namespace std;
class cmdmsg:public UserData
{
public:
    string msg;
    bool isopen = false;
    bool needopen = false;
    bool isioc = false;
    bool iscmd = false;
    bool isdate = false;
    cmdmsg(){}
    ~cmdmsg(){}
    //cmdmsg



};
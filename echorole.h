#pragma once
#include<zinx.h>

class echo:public Irole
{
public:
    echo();
    virtual ~echo();
    virtual bool Init();

	/*处理信息函数，重写该方法可以对业务数据进行处理，若还需要后续处理流程，则应返回相关数据信息（堆对象）*/
	virtual UserData *ProcMsg(UserData &_poUserData);

	/*去初始化函数，类似初始化函数，该函数会在role对象摘除出zinxkernel时调用*/
	virtual void Fini();
};


class inoutcontrol:public Irole
{
public:
	Ichannel *inout = nullptr;
	virtual bool Init();
	virtual UserData *ProcMsg(UserData &_poUserData);

	/*去初始化函数，类似初始化函数，该函数会在role对象摘除出zinxkernel时调用*/
	virtual void Fini();

};

class dateecho:public Irole
{
public:
	//Ichannel *inout = nullptr;
	virtual bool Init();
	virtual UserData *ProcMsg(UserData &_poUserData);

	/*去初始化函数，类似初始化函数，该函数会在role对象摘除出zinxkernel时调用*/
	virtual void Fini();
};
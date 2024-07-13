#pragma once
#include<zinx.h>
#include<iostream>
#include<ZinxTCP.h>
using namespace std;

class inputchannel:public Ichannel
{
public:
    inputchannel();
    virtual ~inputchannel();

	virtual bool Init();

	virtual bool ReadFd(std::string &_input);

	virtual bool WriteFd(std::string &_output);


	virtual void Fini();

	
	virtual int GetFd();

	virtual std::string GetChannelInfo();

	virtual AZinxHandler *GetInputNextStage(BytesMsg &_oInput);

};


class outputchannel:public Ichannel
{
public:
    outputchannel();
    ~outputchannel();
	virtual bool Init();

	virtual bool ReadFd(std::string &_input);

	virtual bool WriteFd(std::string &_output);


	virtual void Fini();

	
	virtual int GetFd();

	virtual std::string GetChannelInfo();

	virtual AZinxHandler *GetInputNextStage(BytesMsg &_oInput);

};

class mytcpdata:public ZinxTcpData{
public:
	mytcpdata(int _fd):ZinxTcpData(_fd){}
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput);

};

class mytcpfact:public IZinxTcpConnFact{
public:
	virtual ZinxTcpData *CreateTcpDataChannel(int _fd);

};

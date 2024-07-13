#pragma once
#include<zinx.h>
#include<iostream>
#include<vector>

using namespace std;

class zinxtimerchannel:public Ichannel
{
private:
    int tfd = -1;
public:
    virtual bool Init();

	/*读取数据， 开发者应该根据目标文件不同，重写这个函数，以实现将fd中的数据读取到参数_string中
	该函数会在数据源所对应的文件有数据到达时被调用*/
	virtual bool ReadFd(std::string &_input);

	/*写出数据， 开发者应该将数据写出的操作通过重写该函数实现
	该函数会在调用zinxkernel::sendout函数后被调用（通常不是直接调用而是通过多路复用的反压机制调用）*/
	virtual bool WriteFd(std::string &_output);

	/*通道去初始化，开发者应该在该函数回收相关资源
	该函数会在通道对象从zinxkernel中摘除时调用*/
	virtual void Fini();

	/*获取文件描述符函数， 开发者应该在该函数返回当前关心的文件，
	一般地，开发者应该在派生类中定义属性用来记录数据来记录当前IO所用的文件，在此函数中只是返回该属性*/
	virtual int GetFd();
	virtual std::string GetChannelInfo();
 


	


	virtual AZinxHandler *GetInputNextStage(BytesMsg &_oInput);

};

class helloworld : public AZinxHandler
{
public:

	virtual IZinxMsg *InternelHandle(IZinxMsg &_oInput);

	/*获取下一个处理环节函数，开发者重写该函数，可以指定当前处理环节结束后下一个环节是什么，通过参数信息对象，可以针对不同情况进行分别处理*/
	virtual AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg);

};

class timerProc{
public:
	virtual void Proc() = 0;
	virtual int getTimerSeconds() = 0;
	int count = -1;

};

class timermanager:public AZinxHandler{
private:
	std::vector<list<timerProc*>> tpl;
	int m_currenindex;
	static timermanager m;
public:
	timermanager();
	virtual IZinxMsg *InternelHandle(IZinxMsg &_oInput);

	/*获取下一个处理环节函数，开发者重写该函数，可以指定当前处理环节结束后下一个环节是什么，通过参数信息对象，可以针对不同情况进行分别处理*/
	virtual AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg);
	void addTimerProc(timerProc *t);
	void delTimerProc(timerProc *t);
	static timermanager &getInstance()
	{
		return m;
	}
};


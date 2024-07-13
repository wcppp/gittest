#include "stdinout.h"
#include"cmdcheck.h"
inputchannel::inputchannel()
{
}
inputchannel::~inputchannel()
{
}
bool inputchannel::Init()
{
    return true;
}

bool inputchannel::ReadFd(std::string &_input)
{
    cin >> _input;
    return true;
}

bool inputchannel::WriteFd(std::string &_output)
{
    return false;
}

void inputchannel::Fini()
{
}

int inputchannel::GetFd()
{
    return 0;
}

std::string inputchannel::GetChannelInfo()
{
    return std::string("stdin");
}

AZinxHandler *inputchannel::GetInputNextStage(BytesMsg &_oInput)
{
    return cmdcheck::getInstance();
}

outputchannel::outputchannel()
{
}

outputchannel::~outputchannel()
{
}

bool outputchannel::Init()
{
    return true;
}

bool outputchannel::ReadFd(std::string &_input)
{
    return false;
}

bool outputchannel::WriteFd(std::string &_output)
{
    cout << _output << endl;
    return true;
}

void outputchannel::Fini()
{
}

int outputchannel::GetFd()
{
    return 1;
}

std::string outputchannel::GetChannelInfo()
{
    return string("stdout");
}

AZinxHandler *outputchannel::GetInputNextStage(BytesMsg &_oInput)
{
    return nullptr;
}

AZinxHandler *mytcpdata::GetInputNextStage(BytesMsg &_oInput)
{

    return cmdcheck::getInstance();
}

ZinxTcpData *mytcpfact::CreateTcpDataChannel(int _fd)
{

    return new mytcpdata(_fd);
}

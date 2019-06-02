#include "Client.h"
#include"NetCommand.h"

Client::Client():io(),ep(ip::address::from_string("127.0.0.1"), 6688),sock(nullptr){}

Client::~Client()
{
	delete instance;
}

Client* Client::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Client();
	}
	return instance;
}

bool Client::connectWithServer()
{
	try
	{
		sock = std::make_shared<ip::tcp::socket>(io);
		sock->connect(ep);
		isConnected = true;
		return true;
	}
	catch (std::exception& e)
	{
		sock = nullptr;
		isConnected = false;
		return false;
	}
}
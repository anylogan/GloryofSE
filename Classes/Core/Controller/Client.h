#ifndef __CLIENT_GAME_H__
#define __CLIENT_GAME_H__

#include <boost/asio.hpp>
#include <vector>
#include <string>
#include<thread>
using namespace boost::asio;

class Client
{
private:
	//单例设计，构造隐藏
	Client();
	~Client();
	Client& operator=(const Client &) = delete;

	static Client *instance;
	//client中的数据
	io_service io;
	ip::tcp::endpoint ep; //连接地址
	std::shared_ptr<ip::tcp::socket> sock;  //套接字指针
public:
	bool isConnected; //是否连接成功的标记
	static Client* getInstance(); //获取单例
	bool connectWithServer(); //建立连接

};

#endif
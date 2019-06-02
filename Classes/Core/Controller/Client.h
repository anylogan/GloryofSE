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
	//������ƣ���������
	Client();
	~Client();
	Client& operator=(const Client &) = delete;

	static Client *instance;
	//client�е�����
	io_service io;
	ip::tcp::endpoint ep; //���ӵ�ַ
	std::shared_ptr<ip::tcp::socket> sock;  //�׽���ָ��
public:
	bool isConnected; //�Ƿ����ӳɹ��ı��
	static Client* getInstance(); //��ȡ����
	bool connectWithServer(); //��������

};

#endif
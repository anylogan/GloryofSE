#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
using namespace boost::asio;
class talk_to_client;
typedef std::shared_ptr<talk_to_client> client_ptr;
client_ptr player1;
client_ptr player2;
client_ptr message_player1;
client_ptr message_player2;
io_service io;
ip::tcp::endpoint ep(ip::tcp::v4(), 6688);
ip::tcp::acceptor acceptor(io, ep);
ip::tcp::endpoint message_ep(ip::tcp::v4(), 5566);
ip::tcp::acceptor message_acceptor(io, message_ep);

class talk_to_client :public boost::enable_shared_from_this<talk_to_client>
{
public:
	talk_to_client() :sock_(io) {};
	ip::tcp::socket & sock() { return sock_; }
private:
	ip::tcp::socket sock_;
};
class command
{
public:
	bool use_flag;        //标记是否为有效信息
	int command_type;    //标记信息种类
	bool connected;      //连接信息
	int hero_type;       //英雄种类信息
	bool hero_attack;    //英雄攻击信息
	float click_x;        //鼠标点击位置
	float click_y;
	int player_type;      //区分客户端
	command() :use_flag(false), command_type(-1), connected(false), hero_type(-1), hero_attack(false), click_x(0.0), click_y(0.0), player_type(0) {}
};
enum CommandType { connection = 0, heroInform, attackInform, clickInform, exitConnect，stopAction };

void handle_chat()
{
	while (true)
	{
		if (message_player1 != nullptr&&message_player1->sock().available())
		{
			auto text = std::string();
			auto buf = std::string(1, '\0');
			while (true)
			{
				message_player1->sock().read_some(buffer(buf));
				if (*buf.begin() == '\n') break;
				text += buf;
			}
			text += "\n";
			if (message_player2 != nullptr)
				message_player2->sock().write_some(buffer(text));
		}
		if (message_player2 != nullptr&&message_player2->sock().available())
		{
			auto text = std::string();
			auto buf = std::string(1, '\0');
			while (true)
			{
				message_player2->sock().read_some(buffer(buf));
				if (*buf.begin() == '\n') break;
				text += buf;
			}
			text += "\n";
			if (message_player1 != nullptr)
				message_player1->sock().write_some(buffer(text));
		}
		if (player1 == nullptr&&player2 == nullptr) break;      //当两个客户端都退出时，服务端才结束发送和读取消息的循环
	}
}

int main()
{
	std::cout << "waiting for all clients..." << std::endl;
	//与客户端建立连接
	try
	{
		//player 1
		player1 = std::make_shared<talk_to_client>();
		acceptor.accept(player1->sock());
		std::cout << "client 1:" << player1->sock().remote_endpoint().address() << std::endl;
		message_player1 = std::make_shared<talk_to_client>();
		message_acceptor.accept(message_player1->sock());
		std::cout << "client 1 message connected" << std::endl;
        //player 2
		player2 = std::make_shared<talk_to_client>();
		acceptor.accept(player2->sock());
		std::cout << "client 2:" << player2->sock().remote_endpoint().address() << std::endl;
		message_player2 = std::make_shared<talk_to_client>();
		message_acceptor.accept(message_player2->sock());
		std::cout << "client 2 message connected" << std::endl;
	}
	catch (std::exception& e)
	{
		player1 = nullptr;
		player2 = nullptr;
		message_player1 = nullptr;
		message_player2 = nullptr;
		std::cout << e.what() << std::endl;
	}
	//若连接成功则发送成功信息否则发送失败消息   (Note::第一次发送！！)
	if (player1 != nullptr&&player2 != nullptr)
	{
		std::vector<command> sends;
		command send;
		send.use_flag = true;
		send.command_type = 0;
		send.connected = true;
		sends.push_back(send);
		player1->sock().write_some(buffer(sends));    //send information
		player2->sock().write_some(buffer(sends));    //send information
		std::cout << "send connection success" << std::endl;
	}
	else
	{
		std::vector<command> sends;
		command send;
		send.use_flag = true;
		send.command_type = 0;
		send.connected = false;
		sends.push_back(send);
		if(player1!=nullptr)
		player1->sock().write_some(buffer(sends)); //send information
		if(player2!=nullptr)
		player2->sock().write_some(buffer(sends));    //send information
		std::cout << "send connection failed" << std::endl;
	}
	//建立新线程处理聊天信息
	if (player1 != nullptr&&player2 != nullptr)
	{
		std::thread message_thread(&handle_chat);
		message_thread.detach();
	}
	//开始从两个客户端接收消息并发送的循环
	//服务器接收指令，根据客户端给定的指令类型分类处理，并统一集中到一个发送指令的vector里
	if (player1 != nullptr&&player2 != nullptr)
	{
		while (true)
		{
			std::vector<command> loopbuff;
			if (player1!=nullptr&&player1->sock().available())
			{
				std::vector<command> buf(player1->sock().available() / sizeof(command));
				player1->sock().read_some(buffer(buf));
				for (auto i = buf.begin(); i != buf.end(); ++i)
				{
					if (i->use_flag == false) break;
					switch (i->command_type)
					{
					case 1:
					{
						command m;
						m.use_flag = true;
						m.command_type = 1;
						m.hero_type = i->hero_type;
						m.player_type = 1;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 1,command type: " << m.command_type << std::endl;
						break;
					}
					case 2:
					{
						command m;
						m.use_flag = true;
						m.command_type = 2;
						m.hero_attack = true;
						m.player_type = 1;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 1,command type: " << m.command_type << std::endl;
						break;
					}
					case 3:
					{
						command m;
						m.use_flag = true;
						m.command_type = 3;
						m.click_x = i->click_x;
						m.click_y = i->click_y;
						m.player_type = 1;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 1,command type: " << m.command_type << std::endl;
						break;
					}
					case 4:
					{
						command m;
						m.use_flag = true;
						m.command_type = 4;
						m.connected = false;
						m.player_type = 1;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 1,exit " << m.command_type << std::endl;
						player1 = nullptr;
						break;
					}
					case 5:
					{
						command m;
						m.use_flag = true;
						m.command_type = 5;
						m.player_type = 1;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 1,command type " << m.command_type << std::endl;
						break;
					}
					default:
						std::cout << "wrong message from 1" << std::endl;
					}
				}
			}
			if (player2!=nullptr&&player2->sock().available())
			{
				std::vector<command> buf(player2->sock().available() / sizeof(command));
				player2->sock().read_some(buffer(buf));
				for (auto i = buf.begin(); i != buf.end(); ++i)
				{
					if (i->use_flag == false) break;
					switch (i->command_type)
					{
					case 1:
					{
						command m;
						m.use_flag = true;
						m.command_type = 1;
						m.hero_type = i->hero_type;
						m.player_type = 2;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 2,command type: " << m.command_type << std::endl;
						break;
					}
					case 2:
					{
						command m;
						m.use_flag = true;
						m.command_type = 2;
						m.hero_attack = true;
						m.player_type = 2;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 2,command type: " << m.command_type << std::endl;
						break;
					}
					case 3:
					{
						command m;
						m.use_flag = true;
						m.command_type = 3;
						m.click_x = i->click_x;
						m.click_y = i->click_y;
						m.player_type = 2;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 2,command type: " << m.command_type << std::endl;
						break;
					}
					case 4:
					{
						command m;
						m.use_flag = true;
						m.command_type = 4;
						m.connected = false;
						m.player_type = 2;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 2,exit " << m.command_type << std::endl;
						player2 = nullptr;
						break;
					}
					case 5:
					{
						command m;
						m.use_flag = true;
						m.command_type = 5;
						m.player_type = 2;
						loopbuff.push_back(m);
						std::cout << "sever receive command from 2,command type " << m.command_type << std::endl;
						break;
					}
					default:
						std::cout << "wrong message from 2" << std::endl;
					}
				}
			}

			for (auto i = loopbuff.begin(); i != loopbuff.end(); ++i)
			{
				if (i->player_type == 1)
				{
					std::vector<command> sends;
					command send;
					send = *i;
					sends.push_back(send);
					if (player2 != nullptr)
					{
						player2->sock().write_some(buffer(sends));
						std::cout << 1 << "send command type " << i->command_type << "to" << 2 << std::endl;
					}

				}
				else
					if (i->player_type == 2)
					{
						std::vector<command> sends;
						command send;
						send = *i;
						sends.push_back(send);
						if (player1 != nullptr)
						{
							player1->sock().write_some(buffer(sends));
							std::cout << 2 << "send command type " << i->command_type << "to" << 1 << std::endl;
						}
					}
			}
			if (player1 == nullptr&&player2 == nullptr) break;      //当两个客户端都退出时，服务端才结束发送和读取消息的循环
		}
	}
	return 0;
}
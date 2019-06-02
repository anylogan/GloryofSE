#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
using namespace boost::asio;
class talk_to_client;
typedef std::shared_ptr<talk_to_client> client_ptr;
client_ptr player1;
client_ptr player2;
io_service io;
ip::tcp::endpoint ep(ip::tcp::v4(), 6688);
ip::tcp::acceptor acceptor(io, ep);

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
	bool use_flag;        //����Ƿ�Ϊ��Ч��Ϣ
	int command_type;    //�����Ϣ����
	bool connected;      //������Ϣ
	int hero_type;       //Ӣ��������Ϣ
	bool hero_attack;    //Ӣ�۹�����Ϣ
	float click_x;        //�����λ��
	float click_y;
	int player_type;      //���ֿͻ���
	command() :use_flag(false), command_type(-1), connected(false), hero_type(-1), hero_attack(false), click_x(0.0), click_y(0.0), player_type(0) {}
};
enum CommandType { connection = 0, heroInform, attackInform, clickInform , exitConnect};

int main()
{
	std::cout << "waiting for all clients..." << std::endl;
	//��ͻ��˽�������
	try
	{
		player1 = std::make_shared<talk_to_client>();
		acceptor.accept(player1->sock());
		std::cout << "client:" << player1->sock().remote_endpoint().address() << std::endl;
		player2 = std::make_shared<talk_to_client>();
		acceptor.accept(player2->sock());
		std::cout << "client:" << player2->sock().remote_endpoint().address() << std::endl;
	}
	catch (std::exception& e)
	{
		player1 = nullptr;
		player2 = nullptr;
		std::cout << e.what() << std::endl;
	}
	//�����ӳɹ����ͳɹ���Ϣ   (Note::��һ�η��ͣ���)
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
	//��ʼ�������ͻ��˽�����Ϣ�����͵�ѭ��
	//����������ָ����ݿͻ��˸�����ָ�����ͷ��ദ����ͳһ���е�һ������ָ���vector��
	while (true)
	{
		std::vector<command> loopbuff;
		if (player1->sock().available())
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
					std::cout << "sever receive command from 1,command type: " << m.command_type << std::endl;
					break;
				}
				default:
					std::cout << "wrong message from 1" << std::endl;
				}
			}
		}
		if (player2->sock().available())
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
					std::cout << "sever receive command from 2,command type: " << m.command_type << std::endl;
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
				player2->sock().write_some(buffer(sends));
				std::cout << 1 << "send command type " << i->command_type << "to" << 2 << std::endl;

			}
			else
				if (i->player_type == 2)
				{
					std::vector<command> sends;
					command send;
					send = *i;
					sends.push_back(send);
					player1->sock().write_some(buffer(sends));
					std::cout << 2 << "send command type " << i->command_type << "to" << 1 << std::endl;
				}
		}
	}
	return 0;
}
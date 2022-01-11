#pragma once
#include "Network.h"
#include "Joueur.h"
#include "Packet.h"
#include "AT_Joueur.h"

class Host final : public Network
{
public:
	~Host();

private:
	struct sClient
	{
		sf::TcpSocket socket;
		int id{ -1 };
		float timeout{ 0.f };
		bool disconnected{ false };
	};

	std::vector<sClient*> ClientList;
	sf::TcpListener listener;
	sf::SocketSelector selector;

	int id_gen{ 0 };
	const size_t MaxSize = 7;

	sf::Packet refactore_Packet(sf::Packet packet);

	void AcceptNewConnection();
	void RefuseNewConnection();

	void ClientDisconnect(sClient* current);

	void SendNewConnection(sClient* current);
	void Send_Add_Other_Player(sClient* current);
	void SendDeconnection(sClient* current);

	void Send_Other(sClient* current, sf::Packet packet, PacketType type);

	void update(float dt);

public:
	virtual void connect(std::string ip) override;
	virtual void run(float dt) override;
	virtual const char* type() override;

	virtual void processEvents(Map& map) override;
	virtual void processEvents(std::map<int, ConnectionPlayer>&) override;
	virtual void processEvents(std::map<int, Main_Joueur*>&, Map& map, Map::BoutonMG& bouton,
		ManagerBonus& bonus, Draw& drawables, FSM_Manager& fsm, Game& g) override;
	virtual void processEvents(std::map<int, TC_Joueur*>&) override;
	virtual void processEvents(std::map<int, BR_Joueur*>&, std::vector< Projectiles_BR>&) override;
	virtual void processEvents(std::map<int, AT_Joueur*>&, AT_Joueur* you, const float& dt) override;

	virtual const sf::IpAddress getRemoteAddress() { return sf::IpAddress::getLocalAddress(); }
};
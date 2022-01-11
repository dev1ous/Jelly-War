#pragma once
#include "Network.h"
#include "AT_Joueur.h"

class Client final : public Network
{
public:
	Client();
	~Client();

private:
	sf::TcpSocket socket;
	float serverTimeout{ 0.f };

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

	virtual const sf::IpAddress getRemoteAddress() { return socket.getRemoteAddress(); }
};
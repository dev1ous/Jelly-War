#pragma once
#include "SFML/Network.hpp"
#include "Time.h"
#include "Joueur.h"
#include "Main_Joueur.h"
#include "TC_Joueur.h"
#include "BR_Joueur.h"
#include "Projectiles_BR.h"
#include "Map.h"

#include <thread>
#include <atomic>
#include <mutex>

using Draw = std::list<std::pair<bool, sf::Sprite*>>;

class AT_Joueur;
class FSM_Manager;
class Game;
class ManagerBonus;
struct ConnectionPlayer;

class Network
{
public:
	struct BrInfos {
		sf::Vector2f pos;
		int score;
		bool invincible;
		float rotation;

		Projectiles_BR* newProj{ nullptr };
	};

	struct TcInfos {
		sf::Vector2f TcPos;
		sf::Color tcColor;
		int tcScore;
	};

	struct ATInfos {
		sf::Vector2f pos, velocity;
		bool alive;
		std::map<int, sf::Vector2f> bumps;
		float rotation;
		int color;
		int score;
	};

	struct thisInfos {
		Bonus::Type Bonus_to_win{ Bonus::Type::None };
		Map::Nodes* newNode{ nullptr };
		Bonus* newBonus[3]{ nullptr };
		bool ready{ false };
		Joueur::Couleur color{ Joueur::Couleur::One };
		int id{ -1 };
		int Current_State{ 0 };
		sf::Vector2f NodeRessourceRemove{ -1,-1 };

		sf::Vector2f GamePos;
		sf::IntRect Anim;
		float XScale{ 1.f };
		bool Tacle{ false };
		bool Check{ false };
		bool UseBonus{ false };
		float progress{ 0.f };
		bool won{ false };
		float timerbouton{ 0 };
		bool MinijeuReady{ false };

		Bonus::Type CurrentBonus{ Bonus::Type::None };

		std::list<Map::Nodes>* nodes{ nullptr };
		BrInfos br;
		TcInfos tc;
		ATInfos at;

		std::string Pseudo;
	};


	enum class NetworkStyle { Waiting, Game, BR, TC, AT };

protected:
	NetworkStyle style{ NetworkStyle::Waiting };
	bool closed{ true };
	const short int port{ 13579 };
	std::vector<std::pair<int, std::unique_ptr<sf::Packet>>> eventsList;
	thisInfos thisInfo;

	float sendTimer{ 0.f };
	const float timeToSend{ 0.02f };
	bool launched{ false };

	std::mutex lock;
	std::thread th;
public:
	virtual ~Network();

	void disconnect();
	const bool isOpen() const;
	const thisInfos& youInfos() const { return thisInfo; }

	void updateInfos(Map& map);
	void updateInfos(Map::Nodes* node);
	void updateInfos(Projectiles_BR* proj);
	void updateInfos(Bonus* bonus[3]);
	void updateInfos(bool Ready, Joueur::Couleur color);
	void updateInfos(TC_Joueur* you);
	void updateInfos(BR_Joueur* you);
	void updateInfos(AT_Joueur* you);
	void updateInfos(int id, AT_Joueur* you);
	void updateInfos(Main_Joueur* you, const float& timer, bool& ready);
	void updateInfos(Joueur* you);
	void updateInfosState(int currentstate, Map::BoutonMG& bouton);
	void updateInfosRemoveTraps(sf::Vector2f pos);
	void setWinBonus(Bonus::Type bonus) { thisInfo.Bonus_to_win = bonus; }
	void win();
	void setPseudo(std::string pseudo) { thisInfo.Pseudo = pseudo; }
	const std::string getPseudo() const { return thisInfo.Pseudo; }

	const size_t UnprocessedPackets() const;
	const NetworkStyle getStyle() const { return style; }
	virtual void connect(std::string ip = "") = 0;
	virtual void run(float dt) = 0;

	virtual void processEvents(Map& map) = 0;
	virtual void processEvents(std::map<int, ConnectionPlayer>&) = 0;
	virtual void processEvents(std::map<int, Main_Joueur*>&, Map& map, Map::BoutonMG& bouton,
		ManagerBonus& bonus, Draw& drawables, FSM_Manager& fsm, Game& g) = 0;
	virtual void processEvents(std::map<int, TC_Joueur*>&) = 0;
	virtual void processEvents(std::map<int, BR_Joueur*>&, std::vector< Projectiles_BR>&) = 0;
	virtual void processEvents(std::map<int, AT_Joueur*>&, AT_Joueur* you, const float& dt) = 0;

	virtual const char* type() = 0;
	virtual const sf::IpAddress getRemoteAddress() = 0;
};
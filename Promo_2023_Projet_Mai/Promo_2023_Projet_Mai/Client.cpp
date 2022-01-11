#include "Client.h"
#include "Packet.h"
#include <iostream>
#include "Main_Joueur.h"
#include "FSM_Manager.h"
#include "Game.h"
#include "Battle_Royal.h"
#include "Auto_tamponneuse.h"
#include "TerritoryConquest.h"
#include "ConnectionScreen.h"

Client::Client()
{
}

Client::~Client()
{
	closed = true;
	if (th.joinable()) {
		th.join();
	}
}

void Client::update(float dt)
{
	sendTimer += dt;
	serverTimeout += dt;

	if (sendTimer > timeToSend) {
		sf::Packet sendPacket;
		thisInfo.nodes = nullptr;

		if (style == NetworkStyle::Waiting)
			sendPacket << PacketType::WAITING_PACKET << thisInfo.ready << static_cast<int>(thisInfo.color) << thisInfo.Pseudo;
		else if (style == NetworkStyle::Game) {
			sendPacket << PacketType::UPDATE_PACKET << thisInfo.GamePos << thisInfo.Anim << thisInfo.XScale
				<< thisInfo.Tacle << static_cast<int>(thisInfo.color) << thisInfo.Check <<
				thisInfo.UseBonus << (int)thisInfo.CurrentBonus << thisInfo.progress <<
				thisInfo.timerbouton << thisInfo.MinijeuReady;
		}
		else if (style == NetworkStyle::BR)
			sendPacket << PacketType::BR_UPDATE << static_cast<int>(thisInfo.color) << thisInfo.br.pos << thisInfo.br.invincible << thisInfo.br.score << thisInfo.br.rotation;
		else if (style == NetworkStyle::TC)
			sendPacket << PacketType::TC_UPDATE << static_cast<int>(thisInfo.color) << thisInfo.tc.TcPos << thisInfo.tc.tcColor << thisInfo.tc.tcScore;
		else if (style == NetworkStyle::AT)
			sendPacket << PacketType::AT_UPDATE << static_cast<int>(thisInfo.color) << thisInfo.at.pos << thisInfo.at.velocity << thisInfo.at.alive << thisInfo.at.rotation << thisInfo.at.score;

		if (socket.send(sendPacket) == sf::Socket::Status::Done) {
			serverTimeout = 0.f;
			sendTimer = 0.0f;
		}

		if (style == NetworkStyle::Game && thisInfo.newNode != nullptr) {
			sendPacket.clear();
			sendPacket << PacketType::NODE_PACKET << thisInfo.newNode->Minerais.getPosition();

			if (socket.send(sendPacket) == sf::Socket::Status::Done) {
				serverTimeout = 0.f;
				sendTimer = 0.0f;
			}

			thisInfo.newNode = nullptr;
		}
		if (style == NetworkStyle::Game && thisInfo.newBonus[0] != nullptr) {
			sendPacket.clear();

			sendPacket << PacketType::SpawnBonus;

			int it = 0;
			for (int i = 0; i < 3; i++) {
				if (thisInfo.newBonus[i] != nullptr) {
					it++;
				}
			}

			sendPacket << it;

			for (int i = 0; i < it; i++) {
				sendPacket << thisInfo.newBonus[i]->GetSprite().getPosition() << (int)thisInfo.newBonus[i]->GetType();
				thisInfo.newBonus[i] = nullptr;
			}

			if (socket.send(sendPacket) == sf::Socket::Status::Done) {
				serverTimeout = 0.f;
				sendTimer = 0.0f;
			}
		}
		if (style == NetworkStyle::BR && thisInfo.br.newProj != nullptr) {
			sendPacket.clear();
			sendPacket << PacketType::BR_PROJECTILE << thisInfo.br.newProj->GetPos() << thisInfo.br.newProj->GetAngle();

			if (socket.send(sendPacket) == sf::Socket::Status::Done) {
				serverTimeout = 0.f;
				sendTimer = 0.0f;
			}

			thisInfo.br.newProj = nullptr;
		}
		if (style == NetworkStyle::AT && !thisInfo.at.bumps.empty()) {
			for (auto& [id, vel] : thisInfo.at.bumps) {
				sendPacket.clear();
				sendPacket << PacketType::AT_BUMP << vel << id;

				if (socket.send(sendPacket) == sf::Socket::Status::Done) {
					serverTimeout = 0.f;
					sendTimer = 0.0f;
				}
			}

			thisInfo.at.bumps.clear();
		}
		if (thisInfo.Current_State != 0) {
			sendPacket.clear();
			sendPacket << PacketType::SwitchMiniGame << thisInfo.Current_State;

			if (socket.send(sendPacket) == sf::Socket::Status::Done) {
				serverTimeout = 0.f;
				sendTimer = 0.0f;
			}

			thisInfo.Current_State = 0;
		}
		if (thisInfo.won) {
			sendPacket.clear();
			sendPacket << PacketType::WON_PACKET;

			if (socket.send(sendPacket) == sf::Socket::Status::Done) {
				serverTimeout = 0.f;
				sendTimer = 0.0f;
			}

			thisInfo.won = false;
		}
		if (thisInfo.NodeRessourceRemove != sf::Vector2f(-1, -1)) {
			sendPacket.clear();
			sendPacket << PacketType::REMOVE_TRAP << thisInfo.NodeRessourceRemove;

			if (socket.send(sendPacket) == sf::Socket::Status::Done) {
				serverTimeout = 0.f;
				sendTimer = 0.0f;
			}

			thisInfo.NodeRessourceRemove = sf::Vector2f(-1, -1);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		std::unique_ptr<sf::Packet> recievePacket = std::make_unique<sf::Packet>();
		if (socket.receive(*recievePacket) == sf::Socket::Status::Done) {
			serverTimeout = 0.f;

			lock.lock();
			eventsList.emplace_back(-1, std::move(recievePacket));
			lock.unlock();
		}
		else
			break;
	}

	if (serverTimeout >= 5.f) {
		closed = true;
		std::cout << "connection lost" << "\n";
	}
}

void Client::connect(std::string ip)
{
	if (socket.connect(ip, port, sf::seconds(2)) == sf::Socket::Done)
	{
		std::cout << "Connecte au serveur" << "\n";
		socket.setBlocking(false);
		closed = false;
	}
	else
	{
		std::cout << "Serveur down" << "\n";
	}
}

void Client::run(float dt)
{
	if (!launched) {
		launched = true;
		th = std::thread([&] {
			auto Clock = std::chrono::high_resolution_clock::now();
			while (!closed) {
				const auto tmp = std::chrono::high_resolution_clock::now();
				const auto m_fDeltaTime = tmp - Clock;
				Clock = tmp;

				update(std::chrono::duration<float>{m_fDeltaTime}.count());

				std::this_thread::sleep_for(std::chrono::milliseconds(1) - m_fDeltaTime);
			}

			launched = false;
			});
	}
}

const char* Client::type()
{
	return "Client";
}

void Client::processEvents(Map& map)
{
	bool got{ false };

	while (!got)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(100));

		lock.lock();

		for (auto it = std::begin(eventsList); it != std::end(eventsList); ++it) {
			sf::Packet& packet = *(it->second);

			PacketType packetType;
			packet >> packetType;

			if (packetType == PacketType::MAP_PACKET) {
				size_t _size{ 0 };
				packet >> _size;

				for (size_t i = 0; i < _size; i++)
				{
					sf::Vector2f _pos;
					int _type;
					packet >> _pos >> _type;

					map.getNode(_pos)->type = _type;
				}

				map.ChangeTexture();
				got = true;
			}
		}

		lock.unlock();
	}
}

void Client::processEvents(std::map<int, ConnectionPlayer>& players)
{
	lock.lock();
	for (auto it = std::begin(eventsList); it != std::end(eventsList); ++it) {
		//int _id = (*it).first;
		sf::Packet& packet = *(it->second);

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::YOUR_CONNECTION) {
			int id;
			packet >> id;
			thisInfo.id = id;
		}
		if (packetType == PacketType::NEW_CONNECTION) {
			int id;
			packet >> id;
			std::cout << "new connection : " << id << "\n";
		}
		else if (packetType == PacketType::EXISTING_CONNECTION) {
			int id;
			packet >> id;
			std::cout << "old connection : " << id << "\n";
		}
		else if (packetType == PacketType::CLIENT_DISCONNECTED) {
			int id;
			packet >> id;
			if (players.find(id) != players.end()) {
				players.erase(id);
				std::cout << "deconnection : " << id << "\n";
			}
		}
		else if (packetType == PacketType::SERVER_FULL) {
			std::cout << "Serveur full" << "\n";
			closed = true;
		}
		else if (packetType == PacketType::WAITING_PACKET) {
			int id;
			bool _ready;
			int _color;
			std::string _pseudo;

			packet >> id >> _ready >> _color >> _pseudo;

			if (players[id].ready != _ready) {
				if (_ready) {
					std::cout << id << " : is not ready" << "\n";
				}
				else {
					std::cout << id << " : is ready" << "\n";
				}
			}

			players[id].ready = _ready;
			players[id].color = static_cast<Joueur::Couleur>(_color);
			players[id].pseudo = _pseudo;
		}
	}

	eventsList.clear();
	lock.unlock();
}

void Client::processEvents(std::map<int, Main_Joueur*>& players, Map& map, Map::BoutonMG& bouton,
	ManagerBonus& bonus, Draw& drawables, FSM_Manager& fsm, Game& g)
{
	lock.lock();
	for (auto it = std::begin(eventsList); it != std::end(eventsList); ++it) {
		//int _id = (*it).first;
		sf::Packet& packet = *(it->second);
		int id;

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			packet >> id;
			if (players.find(id) != players.end()) {
				drawables.erase(std::remove_if(std::begin(drawables), std::end(drawables),
					[&players, &id](std::pair<bool, sf::Sprite*> d) {return d.second == &players[id]->GetSprite(); }));

				delete players[id];
				players.erase(id);
				std::cout << "deconnection : " << id << "\n";
			}
		}
		else if (packetType == PacketType::SERVER_FULL) {
			std::cout << "Serveur full" << "\n";
			closed = true;
		}
		else if (packetType == PacketType::UPDATE_PACKET) {
			sf::Vector2f _pos;
			sf::IntRect _rect;
			float _XScale, _progress;
			bool _Tacle;
			bool _check;
			bool _use;
			int _bonus;
			int _color;
			float timer;
			bool ready;

			packet >> id >> _pos >> _rect >> _XScale >> _Tacle >> _color >>
				_check >> _use >> _bonus >> _progress >> timer >> ready;

			if (players.find(id) == std::end(players)) {
				players[id] = new Main_Joueur();
			}

			players[id]->SetTextureRect(_rect);
			players[id]->setOrigin();
			players[id]->SetPos(_pos);
			players[id]->SetScale(_XScale, 1.f);
			players[id]->SetTacle(_Tacle);
			players[id]->SetColor(static_cast<Joueur::Couleur>(_color));
			players[id]->SetCheck(_check);
			players[id]->SetUseBonus(_use);
			players[id]->SetBonus((Bonus::Type)_bonus);
			players[id]->setProgress(_progress);
			bouton.timer = timer;

			if (ready)
				bouton.start = ready;
		}
		else if (packetType == PacketType::NODE_PACKET) {
			sf::Vector2f _pos;
			packet >> id >> _pos;

			map.getNode(_pos)->owner = players[id];
		}
		else if (packetType == PacketType::SpawnBonus) {
			sf::Vector2f _pos[3];
			int type[3];
			int it;

			packet >> id >> it;

			if (it == 1) {

				packet >> _pos[0] >> type[0];

				bonus.AddBonus(_pos[0], static_cast<Bonus::Type>(type[0]), drawables);
			}
			else {
				int y = it;
				for (auto& it : bonus.GetBonusMap()) {
					if (it.GetType() != Bonus::Type::None) {
						y++;
					}
				}

				if (y > 12) {
					for (int i = 0; i < y - 12; i++) {
						drawables.erase(std::remove_if(std::begin(drawables), std::end(drawables),
							[&bonus](std::pair<bool, sf::Sprite*> d) {return d.second == &bonus.GetBonusMap().begin()->GetSprite(); }));
						bonus.GetBonusMap().erase(bonus.GetBonusMap().begin());
					}
				}

				for (int i = 0; i < it; i++) {
					packet >> _pos[i] >> type[i];

					bonus.AddBonus(_pos[i], static_cast<Bonus::Type>(type[i]), drawables);
				}
			}
		}
		else if (packetType == PacketType::SwitchMiniGame) {
			int state;
			packet >> id >> state;

			if (state == 1) {
				fsm.AddState(FSM_Manager::create<Battle_Royal>(fsm, g.GetWindow(), g.GetFont(), true));
			}
			if (state == 2) {
				fsm.AddState(FSM_Manager::create<Auto_tamponneuse>(fsm, g.GetWindow(), g.GetFont(), true));
			}
			if (state == 3) {
				fsm.AddState(FSM_Manager::create<TerritoryConquest>(fsm, g.GetWindow(), g.GetFont(), true));
			}

			thisInfo.MinijeuReady = false;
			map.ResetBouton();
		}
		else if (packetType == PacketType::WON_PACKET) {
			packet >> id;
			g.loose();
		}
		else if (packetType == PacketType::REMOVE_TRAP) {
			sf::Vector2f _pos;
			packet >> id >> _pos;

			map.RemoveTrapsRessources(_pos, drawables);
		}
	}

	eventsList.clear();
	lock.unlock();
}

void Client::processEvents(std::map<int, TC_Joueur*>& players)
{
	lock.lock();

	for (auto it = std::begin(eventsList); it != std::end(eventsList); ++it) {
		//int _id = (*it).first;
		sf::Packet& packet = *(it->second);

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			int id;
			packet >> id;
			if (players.find(id) != players.end()) {
				delete players[id];
				players.erase(id);
				std::cout << "deconnection : " << id << "\n";
			}
		}
		else if (packetType == PacketType::SERVER_FULL) {
			std::cout << "Serveur full" << "\n";
			closed = true;
		}
		else if (packetType == PacketType::TC_UPDATE) {
			int id;
			sf::Vector2f _tcpos;
			sf::Color _color;
			int color;
			int _score;

			packet >> id >> color >> _tcpos >> _color >> _score;

			if (players.find(id) == std::end(players)) {
				players[id] = new TC_Joueur();
			}

			players[id]->SetColor(static_cast<Joueur::Couleur>(color));
			players[id]->SetPos(_tcpos);
			players.at(id)->SetFillColor(_color);
			players.at(id)->setScore(_score);
			//players[id]->SetColor(static_cast<Joueur::Couleur>(_color));
		}
	}

	eventsList.clear();
	lock.unlock();
}

void Client::processEvents(std::map<int, BR_Joueur*>& players, std::vector< Projectiles_BR>& projectiles)
{
	lock.lock();
	for (auto it = std::begin(eventsList); it != std::end(eventsList); ++it) {
		//int _id = (*it).first;
		sf::Packet& packet = *(it->second);

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			int id;
			packet >> id;
			if (players.find(id) != players.end()) {
				delete players[id];
				players.erase(id);
				std::cout << "deconnection : " << id << "\n";
			}
		}
		else if (packetType == PacketType::SERVER_FULL) {
			std::cout << "Serveur full" << "\n";
			closed = true;
		}
		else if (packetType == PacketType::BR_UPDATE) {
			int id;
			sf::Vector2f _pos;
			bool _inv;
			int _score;
			int _color;
			float _rotation;

			packet >> id >> _color >> _pos >> _inv >> _score >> _rotation;

			if (players.find(id) == std::end(players)) {
				players[id] = new BR_Joueur();
			}

			players[id]->SetColor(static_cast<Joueur::Couleur>(_color));
			players[id]->SetPos(_pos);
			players[id]->setInvinsible(_inv);
			players[id]->setScore(_score);
			players[id]->setAngle(_rotation);
		}
		else if (packetType == PacketType::BR_PROJECTILE) {
			int id;
			sf::Vector2f _pos;
			float _angle;

			packet >> id >> _pos >> _angle;
			projectiles.push_back(Projectiles_BR(_angle, _pos, players[id]));
		}
	}

	eventsList.clear();
	lock.unlock();
}

void Client::processEvents(std::map<int, AT_Joueur*>& players, AT_Joueur* you, const float& dt)
{
	lock.lock();

	for (auto it = std::begin(eventsList); it != std::end(eventsList); ++it) {
		//int _id = (*it).first;
		sf::Packet& packet = *(it->second);

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			int id;
			packet >> id;
			if (players.find(id) != players.end()) {
				delete players[id];
				players.erase(id);
				std::cout << "deconnection : " << id << "\n";
			}
		}
		else if (packetType == PacketType::SERVER_FULL) {
			std::cout << "Serveur full" << "\n";
			closed = true;
		}
		else if (packetType == PacketType::AT_UPDATE) {
			int id;
			sf::Vector2f _pos, _vel;
			bool _alive;
			int _color;
			float _rotation;
			int _score;

			packet >> id >> _color >> _pos >> _vel >> _alive >> _rotation >> _score;

			if (players.find(id) == std::end(players)) {
				players[id] = new AT_Joueur(_pos, _color);
			}

			players[id]->SetColor(static_cast<Joueur::Couleur>(_color));
			players[id]->SetPosition(_pos);
			players[id]->SetVelocity(_vel);
			players[id]->SetAlive(_alive);
			players[id]->setAngle(_rotation);
			players[id]->Set_Score(_score);
		}
		else if (packetType == PacketType::AT_BUMP) {
			int id, _touchid;
			sf::Vector2f _vel;
			packet >> id >> _vel >> _touchid;

			//you->Moveshape(_vel * dt * 2.33f);
			if (_touchid == thisInfo.id) {
				you->setVelocity(-_vel);
			}
		}
	}

	eventsList.clear();
	lock.unlock();

}
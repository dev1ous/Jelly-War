#include "host.h"
#include "Packet.h"
#include <iostream>
#include <chrono>
#include "Main_Joueur.h"
#include "Game.h"
#include "Battle_Royal.h"
#include "Auto_tamponneuse.h"
#include "TerritoryConquest.h"
#include "FSM_Manager.h"
#include "ConnectionScreen.h"

#pragma warning(disable : 26812)

Host::~Host()
{
	std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* current)
		{
			delete current;
		});

	closed = true;
	if (th.joinable()) {
		th.join();
	}
}

void Host::AcceptNewConnection()
{
	sClient* last = ClientList.emplace_back(new sClient());
	last->id = ++id_gen;
	last->socket.setBlocking(false);
	listener.accept(last->socket);
	selector.add(last->socket);

	sf::Packet tmp;
	tmp << PacketType::YOUR_CONNECTION << last->id;
	last->socket.send(tmp);

	SendNewConnection(last);
	Send_Add_Other_Player(last);


	std::cout << "id : " << last->id << " vient de se connecter." << std::endl;

	if (ClientList.size() == MaxSize) {
		std::cout << "stop accepting new connection" << std::endl;
	}
}

void Host::RefuseNewConnection()
{
	sf::TcpSocket socket;
	listener.accept(socket);

	sf::Packet sendPacket;
	sendPacket << PacketType::SERVER_FULL;

	socket.send(sendPacket);
	std::cout << "send full" << std::endl;
}

void Host::ClientDisconnect(sClient* current)
{
	SendDeconnection(current);
	current->disconnected = true;

	std::unique_ptr<sf::Packet> tmpPacket = std::make_unique<sf::Packet>();
	*tmpPacket << PacketType::CLIENT_DISCONNECTED;
	eventsList.emplace_back(current->id, std::move(tmpPacket));
}

void Host::SendNewConnection(sClient* current)
{
	sf::Packet sendPacket;
	sendPacket << PacketType::NEW_CONNECTION << current->id;

	std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
		{
			if (sending != current) {
				sending->socket.send(sendPacket);
			}
		});
}

void Host::Send_Add_Other_Player(sClient* current)
{
	std::for_each(std::begin(ClientList), std::end(ClientList), [current](sClient* sending)
		{
			sf::Packet sendPacket;
			sendPacket << PacketType::EXISTING_CONNECTION << sending->id;

			if (sending != current) {
				current->socket.send(sendPacket);
			}
		});
}

void Host::SendDeconnection(sClient* current)
{
	sf::Packet sendPacket;
	sendPacket << PacketType::CLIENT_DISCONNECTED << current->id;

	std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
		{
			if (sending != current) {
				sending->socket.send(sendPacket);
			}
		});
}

sf::Packet Host::refactore_Packet(sf::Packet packet)
{
	sf::Packet returnedPacket;

	PacketType packetType;
	packet >> packetType;

	if (packetType == PacketType::WAITING_PACKET) {
		bool ready;
		int color;
		std::string _pseudo;
		packet >> ready >> color >> _pseudo;

		returnedPacket << ready << color << _pseudo;
	}
	if (packetType == PacketType::UPDATE_PACKET) {
		sf::Vector2f _pos;
		sf::IntRect _anim;
		float _xScale, _progress;
		bool _tacle;
		bool _check;
		bool _use;
		int _bonus;
		int _color;
		float timer;
		bool ready;

		packet >> _pos >> _anim >> _xScale >> _tacle >> _color >>
			_check >> _use >> _bonus >> _progress >> timer >> ready;

		returnedPacket << _pos << _anim << _xScale << _tacle <<
			_color << _check << _use << _bonus << _progress << timer << ready;
	}
	if (packetType == PacketType::TC_UPDATE) {
		sf::Vector2f _pos;
		sf::Color _color;
		int color;
		int score;

		packet >> color >> _pos >> _color >> score;

		returnedPacket << color << _pos << _color << score;
	}
	if (packetType == PacketType::BR_UPDATE) {
		sf::Vector2f _pos;
		bool _inv;
		int _score;
		int _color;
		int _rotation;

		packet >> _color >> _pos >> _inv >> _score >> _rotation;

		returnedPacket << _color << _pos << _inv << _score << _rotation;
	}
	if (packetType == PacketType::AT_UPDATE) {
		sf::Vector2f _pos, vel;
		bool _alive;
		int _color;
		int _rotation;
		int _score;

		packet >> _color >> _pos >> vel >> _alive >> _rotation >> _score;

		returnedPacket << _color << _pos << vel << _alive << _rotation << _score;
	}
	if (packetType == PacketType::NODE_PACKET) {
		sf::Vector2f pos;
		packet >> pos;

		returnedPacket << pos;
	}
	if (packetType == PacketType::REMOVE_TRAP) {
		sf::Vector2f pos;
		packet >> pos;

		returnedPacket << pos;
	}
	if (packetType == PacketType::SpawnBonus) {
		sf::Vector2f pos[3];
		int type[3];
		int it;

		packet >> it;

		for (int i = 0; i < it; i++) {
			packet >> pos[i] >> type[i];
		}

		packet << it;

		for (int i = 0; i < it; i++) {
			returnedPacket << pos[i] << type[i];
		}
	}
	if (packetType == PacketType::BR_PROJECTILE) {
		sf::Vector2f pos;
		float angle;
		packet >> pos >> angle;

		returnedPacket << pos << angle;
	}
	if (packetType == PacketType::AT_BUMP) {
		sf::Vector2f vel;
		packet >> vel;

		returnedPacket << vel;
	}
	if (packetType == PacketType::SwitchMiniGame) {
		int state;
		packet >> state;

		returnedPacket << state;
	}

	return returnedPacket;
}

void Host::Send_Other(sClient* current, sf::Packet packet, PacketType type)
{
	sf::Packet sendPacket;
	sendPacket << type << current->id;
	sf::Packet reFactoredPacket(refactore_Packet(packet));
	sendPacket.append(reFactoredPacket.getData(), reFactoredPacket.getDataSize());

	std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
		{
			if (sending != current) {
				sending->socket.send(sendPacket);
			}
		});
}

void Host::update(float dt)
{
	size_t lastSize = ClientList.size();

	ClientList.erase(std::remove_if(std::begin(ClientList), std::end(ClientList),
		[&](sClient* current) {
			if (current != nullptr && current->disconnected) {
				selector.remove(current->socket);
				return true;
			}

			return false;
		}), std::end(ClientList));

	if (lastSize >= this->MaxSize && lastSize != ClientList.size() && ClientList.size() < this->MaxSize) {
		std::cout << "Restart accepting new connection" << std::endl;
	}

	sendTimer += dt;

	if (sendTimer > timeToSend) {
		sf::Packet sendPacket;

		if (style == NetworkStyle::Waiting) {
			sendPacket << PacketType::WAITING_PACKET << 0 << thisInfo.ready << static_cast<int>(thisInfo.color) << thisInfo.Pseudo;
		}
		else if (style == NetworkStyle::Game) {
			sendPacket << PacketType::UPDATE_PACKET << 0 << thisInfo.GamePos << thisInfo.Anim << thisInfo.XScale
				<< thisInfo.Tacle << static_cast<int>(thisInfo.color) << thisInfo.Check <<
				thisInfo.UseBonus << static_cast<int>(thisInfo.CurrentBonus) << thisInfo.progress <<
				thisInfo.timerbouton << thisInfo.MinijeuReady;
		}
		else if (style == NetworkStyle::TC) {
			sendPacket << PacketType::TC_UPDATE << 0 << static_cast<int>(thisInfo.color) << thisInfo.tc.TcPos << thisInfo.tc.tcColor << thisInfo.tc.tcScore;
		}
		else if (style == NetworkStyle::BR) {
			sendPacket << PacketType::BR_UPDATE << 0 << static_cast<int>(thisInfo.color) << thisInfo.br.pos << thisInfo.br.invincible << thisInfo.br.score << thisInfo.br.rotation;
		}
		else if (style == NetworkStyle::AT) {
			sendPacket << PacketType::AT_UPDATE << 0 << static_cast<int>(thisInfo.color) << thisInfo.at.pos << thisInfo.at.velocity << thisInfo.at.alive << thisInfo.at.rotation << thisInfo.at.score;
		}

		std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
			{
				sending->socket.send(sendPacket);
			});

		if (style == NetworkStyle::Game && thisInfo.newNode != nullptr) {
			sendPacket.clear();
			sendPacket << PacketType::NODE_PACKET << 0 << thisInfo.newNode->Minerais.getPosition();

			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
				{
					sending->socket.send(sendPacket);
				});

			thisInfo.newNode = nullptr;
		}
		if (style == NetworkStyle::Game && thisInfo.newBonus[0] != nullptr) {
			sendPacket.clear();

			sendPacket << PacketType::SpawnBonus << 0;

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

			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
				{
					sending->socket.send(sendPacket);
				});
		}
		if (style == NetworkStyle::BR && thisInfo.br.newProj != nullptr) {
			sendPacket.clear();
			sendPacket << PacketType::BR_PROJECTILE << 0 << thisInfo.br.newProj->GetPos() << thisInfo.br.newProj->GetAngle();

			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
				{
					sending->socket.send(sendPacket);
				});

			thisInfo.br.newProj = nullptr;
		}
		if (style == NetworkStyle::AT && !thisInfo.at.bumps.empty()) {
			for (auto& [id, vel] : thisInfo.at.bumps) {
				sendPacket.clear();
				sendPacket << PacketType::AT_BUMP << 0 << vel << id;

				std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
					{
						if (sending->id == id) {
							sending->socket.send(sendPacket);
						}
					});
			}

			thisInfo.at.bumps.clear();
		}
		if (thisInfo.Current_State != 0) {
			sendPacket.clear();
			sendPacket << PacketType::SwitchMiniGame << 0 << thisInfo.Current_State;

			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
				{
					sending->socket.send(sendPacket);
				});

			thisInfo.Current_State = 0;
		}
		if (thisInfo.nodes != nullptr) {
			sendPacket.clear();
			sendPacket << PacketType::MAP_PACKET;
			sendPacket << thisInfo.nodes->size();

			for (auto& node : *thisInfo.nodes) {
				sendPacket << node.Minerais.getPosition();
				sendPacket << node.type;
			}

			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
				{
					sending->socket.send(sendPacket);
				});

			thisInfo.nodes = nullptr;
		}
		if (thisInfo.won) {
			sendPacket.clear();
			sendPacket << PacketType::WON_PACKET << 0;

			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
				{
					sending->socket.send(sendPacket);
				});

			thisInfo.won = false;
		}
		if (thisInfo.NodeRessourceRemove != sf::Vector2f(-1, -1)) {
			sendPacket.clear();
			sendPacket << PacketType::REMOVE_TRAP << 0 << thisInfo.NodeRessourceRemove;

			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* sending)
				{
					sending->socket.send(sendPacket);
				});

			thisInfo.NodeRessourceRemove = sf::Vector2f(-1, -1);
		}
		sendTimer = 0.0f;
	}

	int packetproccesed = 0;
	while (packetproccesed < 20 && selector.wait(sf::microseconds(1))) { // don't stuck in loop
		packetproccesed++;

		if (selector.isReady(listener)) {
			if (ClientList.size() < MaxSize && style == NetworkStyle::Waiting) {
				this->AcceptNewConnection();
			}
			else {
				this->RefuseNewConnection();
			}
		}
		else {
			std::for_each(std::begin(ClientList), std::end(ClientList), [&](sClient* current) {
				current->timeout += dt;

				if (selector.isReady(current->socket)) {
					std::unique_ptr<sf::Packet> recievePacket = std::make_unique<sf::Packet>();
					sf::Socket::Status recieveStatut{ current->socket.receive(*recievePacket) };

					if (recieveStatut == sf::Socket::Status::Done) {
						current->timeout = 0.f;

						sf::Packet tmpPacket(*recievePacket);

						PacketType packetType;
						tmpPacket >> packetType;

						Send_Other(current, *recievePacket, packetType);

						lock.lock();
						eventsList.emplace_back(current->id, std::move(recievePacket));
						lock.unlock();
					}
					else if (recieveStatut == sf::Socket::Status::Disconnected && !current->disconnected) {

						lock.lock();
						ClientDisconnect(current);
						lock.unlock();
						std::cout << "id : " << current->id << " vient de se deco." << std::endl;
					}
				}

				if (current->timeout >= 5.f && !current->disconnected) {
					lock.lock();
					ClientDisconnect(current);
					lock.unlock();
					std::cout << "id : " << current->id << " vient de se faire timeout." << std::endl;
				}
				});
		}
	}
}

void Host::connect(std::string ip)
{
	if (listener.listen(port) == sf::Socket::Done) {
		selector.add(listener);
		std::cout << "Serveur en ligne" << std::endl;
		closed = false;
	}

	listener.setBlocking(false);
}

void Host::run(float dt)
{
	if (!launched) {
		launched = true;
		th = std::thread([this] {
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

const char* Host::type()
{
	return "Host";
}

void Host::processEvents(Map& map)
{
}

void Host::processEvents(std::map<int, ConnectionPlayer>& players)
{
	lock.lock();
	for (auto it = std::begin(eventsList); it != std::end(eventsList); it++) {
		int id = (*it).first;
		sf::Packet& packet = *(*it).second;

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			players.erase(id);
		}
		else if (packetType == PacketType::WAITING_PACKET) {
			bool _ready;
			int _color;
			std::string _pseudo;

			packet >> _ready >> _color >> _pseudo;

			if (players[id].ready != _ready) {
				if (_ready) {
					std::cout << id << " : is not ready" << std::endl;
				}
				else {
					std::cout << id << " : is ready" << std::endl;
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

void Host::processEvents(std::map<int, Main_Joueur*>& players, Map& map, Map::BoutonMG& bouton,
	ManagerBonus& bonus, Draw& drawables, FSM_Manager& fsm, Game& g)
{
	lock.lock();
	for (auto it = std::begin(eventsList); it != std::end(eventsList); it++) {
		int id = (*it).first;
		sf::Packet& packet = *(*it).second;

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			drawables.erase(std::remove_if(std::begin(drawables), std::end(drawables),
				[&players, &id](std::pair<bool, sf::Sprite*> d) {return d.second == &players[id]->GetSprite(); }));
			players.erase(id);
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

			packet >> _pos >> _rect >> _XScale >> _Tacle >> _color >>
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

			if (ready)
				bouton.start = ready;
		}
		else if (packetType == PacketType::NODE_PACKET) {
			sf::Vector2f _pos;
			packet >> _pos;

			map.getNode(_pos)->owner = players[id];
		}
		else if (packetType == PacketType::SpawnBonus) {
			sf::Vector2f _pos[3];
			int type[3];
			int it;

			packet >> it;
			for (int i = 0; i < it; i++) {
				packet >> _pos[i] >> type[i];

				bonus.AddBonus(_pos[i], static_cast<Bonus::Type>(type[i]), drawables);
			}
		}
		else if (packetType == PacketType::SwitchMiniGame) {
			int state;
			packet >> state;

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
			g.loose();
		}
		else if (packetType == PacketType::REMOVE_TRAP) {
			sf::Vector2f _pos;
			packet >> _pos;

			map.RemoveTrapsRessources(_pos, drawables);
		}
	}

	eventsList.clear();
	lock.unlock();
}

void Host::processEvents(std::map<int, TC_Joueur*>& players)
{
	lock.lock();

	std::for_each(std::begin(eventsList), std::end(eventsList), [&players](const auto& eL) {
		int id = eL.first;
		sf::Packet& packet = *eL.second;

		auto [it, result] = players.try_emplace(id, nullptr);
		if (result)
			it->second = new TC_Joueur();

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED)
			players.erase(id);
		else if (packetType == PacketType::TC_UPDATE) {
			sf::Vector2f _tcpos;
			sf::Color _color;
			int color;
			int score;

			packet >> color >> _tcpos >> _color >> score;

			players.at(id)->SetPos(_tcpos);
			players.at(id)->SetColor(static_cast<Joueur::Couleur>(color));
			players.at(id)->SetFillColor(_color); //?????????????
			players.at(id)->setScore(score);
		}
		});

	eventsList.clear();
	lock.unlock();
}

void Host::processEvents(std::map<int, BR_Joueur*>& players, std::vector< Projectiles_BR>& projectiles)
{
	lock.lock();
	for (auto it = std::begin(eventsList); it != std::end(eventsList); it++) {
		int id = (*it).first;
		sf::Packet& packet = *(*it).second;

		if (players.find(id) == std::end(players)) {
			players[id] = new BR_Joueur();
		}

		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			players.erase(id);
		}
		else if (packetType == PacketType::BR_UPDATE) {
			sf::Vector2f _pos;
			bool _inv;
			int _score;
			int _color;
			float _rotation;
			packet >> _color >> _pos >> _inv >> _score >> _rotation;

			players.at(id)->SetColor(static_cast<Joueur::Couleur>(_color));
			players[id]->SetPos(_pos);
			players[id]->setInvinsible(_inv);
			players[id]->setScore(_score);
			players[id]->setAngle(_rotation);
		}
		else if (packetType == PacketType::BR_PROJECTILE) {
			sf::Vector2f _pos;
			float _angle;

			packet >> _pos >> _angle;
			projectiles.push_back(Projectiles_BR(_angle, _pos, players[id]));
		}
	}

	eventsList.clear();
	lock.unlock();
}

void Host::processEvents(std::map<int, AT_Joueur*>& players, AT_Joueur* you, const float& dt)
{
	lock.lock();
	for (auto it = std::begin(eventsList); it != std::end(eventsList); it++) {
		int id = (*it).first;
		sf::Packet& packet = *(*it).second;



		PacketType packetType;
		packet >> packetType;

		if (packetType == PacketType::CLIENT_DISCONNECTED) {
			players.erase(id);
		}
		else if (packetType == PacketType::AT_UPDATE) {
			sf::Vector2f _pos, _vel;
			bool _alive;
			int _color;
			float _rotation;
			int _score;

			packet >> _color >> _pos >> _vel >> _alive >> _rotation >> _score;

			if (players.find(id) == std::end(players)) {
				players[id] = new AT_Joueur(Vector2f(0, 0), _color);
			}

			players.at(id)->SetColor(static_cast<Joueur::Couleur>(_color));
			players[id]->SetPosition(_pos);
			players[id]->SetVelocity(_vel);
			players[id]->SetAlive(_alive);
			players[id]->setAngle(_rotation);
			players[id]->Set_Score(_score);
		}
		else if (packetType == PacketType::AT_BUMP) {
			sf::Vector2f _vel;
			int _otherid;
			packet >> _vel >> _otherid;

			//you->Moveshape(_vel * dt * 2.33f);
			if (_otherid == 0) {
				you->setVelocity(-_vel);
			}
		}
	}

	eventsList.clear();
	lock.unlock();
}
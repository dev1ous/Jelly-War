#include "Main_Joueur.h"
#include "Cache.h"
#include "Gamepad.h"
#include "Functions.h"
#include "Options.h"
#include "Hud_MainGame.h"
#include "Network.h"

template <typename T>
short int getSigne(T value) {
	if (value > 0) {
		return 1;
	}
	else if (value < 0) {
		return -1;
	}

	return 0;
}

Main_Joueur::Main_Joueur() : Joueur()
{
	Sprite.setPosition(500, 500);
	Hitbox.setSize(sf::Vector2f(115, 45));
	Hitbox.setOrigin(Hitbox.getSize().x / 2, Hitbox.getSize().y / 2);

	m_bufferTacle.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Tacle.wav");
	m_SoundTacle.setBuffer(m_bufferTacle);

	m_bufferCheck.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Check.wav");
	m_SoundCheck.setBuffer(m_bufferCheck);

	m_bufferAntiCheck.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Anti_Check.wav");
	m_soundAntiCheck.setBuffer(m_bufferAntiCheck);

	m_bufferAntiTacle.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Anti_Tacle.wav");
	m_soundAntiTacle.setBuffer(m_bufferAntiTacle);

	m_bufferTp.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Anti_Check.wav");
	m_soundTp.setBuffer(m_bufferTp);

	m_bufferslow.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Anti_Tacle.wav");
	m_soundslow.setBuffer(m_bufferslow);

	m_bufferConfusion.loadFromFile("../Ressources/Sons/FinalVersionSons/BonusEtInteractions/Anti_Check.wav");
	m_soundConfusion.setBuffer(m_bufferConfusion);

	m_bufferMove.loadFromFile("../Ressources/Sons/Main-game/Perso/Deplacement_1.wav");
	m_soundMove.setBuffer(m_bufferMove);

	//MyBonus.push_back(Bonus::Type::LeurreZone);
	MyBonus.push_back(Bonus::Type::MapScan);
}

Map::Nodes* Main_Joueur::LookingAt(Map& map, const float& dt)
{
	Map::Nodes* ptr = nullptr;

	ptr = map.getNode(sf::Vector2f(Sprite.getPosition()));

	return ptr;
}

void Main_Joueur::SetFeedback(Statut feedback)
{
	switch (feedback)
	{
	case Main_Joueur::Statut::Check:
		if (FeedBacks.find(Statut::Check) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Check, std::make_pair(
				Feedback("Check fb", { GetPos().x,GetPos().y + 1 }, { 0,0,558,294 },
					11, 1.5f / 11.f, -Hitbox.getGlobalBounds().height / 2), 10.f)));
		}
		break;
	case Main_Joueur::Statut::Etourdit:
		if (FeedBacks.find(Statut::Etourdit) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Etourdit, std::make_pair(
				Feedback("Etourdit fb", { GetPos().x,GetPos().y + 1 }, { 0,0,115,45 },
					21, 2.5f / 21.f, -Hitbox.getGlobalBounds().height / 2), 3.f)));
		}
		break;
	case Main_Joueur::Statut::Enerver:
		if (FeedBacks.find(Statut::Enerver) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Enerver, std::make_pair(
				Feedback("Enervé fb", { GetPos().x,GetPos().y + 1 }, { 0,0,85,79 },
					25, 1.5f / 25.f, -Hitbox.getGlobalBounds().height / 2), 0.f)));
		}
		break;
	case Main_Joueur::Statut::Diabolique:
		if (FeedBacks.find(Statut::Diabolique) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Diabolique, std::make_pair(
				Feedback("Demon fb", { GetPos().x,GetPos().y + 1 }, { 0,0,252,106 },
					22, 1.5f / 22.f, -Hitbox.getGlobalBounds().height / 2), 0.f)));
		}
		break;
	case Main_Joueur::Statut::Fausse_Ressources:
		if (FeedBacks.find(Statut::Fausse_Ressources) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Fausse_Ressources, std::make_pair(
				Feedback("Fause_Ressource fb", { GetPos().x,GetPos().y + 1 }, { 0,0,33,54 },
					16, 2.f / 16.f, -Hitbox.getGlobalBounds().height / 2), 0.f)));
		}

		break;
	case Main_Joueur::Statut::faux_Bonus:
		if (FeedBacks.find(Statut::faux_Bonus) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::faux_Bonus, std::make_pair(
				Feedback("Faux_Bonus fb", { GetPos().x,GetPos().y + 1 }, { 0,0,96,95 },
					10, 2.f / 10.f, -Hitbox.getGlobalBounds().height / 2), 0.f)));
		}
		break;
	case Main_Joueur::Statut::Contre_Tacle:
		if (FeedBacks.find(Statut::Contre_Tacle) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Contre_Tacle, std::make_pair(
				Feedback("Contre_Tacle fb", { GetPos().x,GetPos().y + 1 }, { 0,0,38,43 },
					45, 3.f / 45.f,	-Hitbox.getGlobalBounds().height / 2), 0.f)));
		}
		break;
	case Main_Joueur::Statut::Ralenti:
		if (FeedBacks.find(Statut::Ralenti) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Ralenti, std::make_pair(
				Feedback("Slow fb", { GetPos().x,GetPos().y + 1 }, { 0,0,130,72 },
					18, 1.5f / 18.f, -Hitbox.getGlobalBounds().height / 2), 10.f)));
		}
		break;
	case Main_Joueur::Statut::Axe_Inversé:
		if (FeedBacks.find(Statut::Axe_Inversé) == FeedBacks.end()) {
			FeedBacks.emplace(std::make_pair(Statut::Axe_Inversé, std::make_pair(
				Feedback("Axe_Inverse fb", { GetPos().x,GetPos().y + 1 }, { 0,0,112,58 },
					26, 2.f / 26.f,	-Hitbox.getGlobalBounds().height / 2), 10.f)));
		}
		break;
	}
}

void Main_Joueur::SetColor(Couleur color)
{
	if (MyColor != color || !onepass) {
		onepass = true;
		MyColor = color;

		switch (MyColor)
		{
		case Joueur::Couleur::One:
			Cache::GetRessources<sf::Texture>("Gudublob").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Gudublob"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 110, 159),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 159, 102, 95),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 254, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		case Joueur::Couleur::Two:
			Cache::GetRessources<sf::Texture>("Belzeblob").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Belzeblob"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 106, 159),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 159, 89, 90),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 249, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		case Joueur::Couleur::Three:
			Cache::GetRessources<sf::Texture>("Tahiti Blob").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Tahiti Blob"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 109, 160),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 160, 94, 90),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 250, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		case Joueur::Couleur::Four:
			Cache::GetRessources<sf::Texture>("Blobillon").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Blobillon"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 109, 155),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 155, 100, 84),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 239, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		case Joueur::Couleur::Five:
			Cache::GetRessources<sf::Texture>("Blobic").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Blobic"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 123, 160),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 160, 96, 93),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 253, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		case Joueur::Couleur::Six:
			Cache::GetRessources<sf::Texture>("Mamiblob").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Mamiblob"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 110, 158),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 158, 90, 89),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 247, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		case Joueur::Couleur::Seven:
			Cache::GetRessources<sf::Texture>("Arliblob").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Arliblob"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 105, 159),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 159, 108, 92),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 251, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		case Joueur::Couleur::Height:
			Cache::GetRessources<sf::Texture>("Lapiblob").setSmooth(true);
			Sprite.setTexture(Cache::GetRessources<sf::Texture>("Lapiblob"));

			Anim["Anim"] = Animator(sf::IntRect(0, 0, 112, 159),
				27, 0.03f, Hitbox.getSize().y / 2);
			Anim["Idle"] = Animator(sf::IntRect(0, 159, 100, 93),
				20, 0.03f, Hitbox.getSize().y / 2);
			Anim["Tp"] = Animator(sf::IntRect(0, 252, 200, 200),
				32, 2.2f / 32, Hitbox.getSize().y / 2);
			break;
		default:
			break;
		}

		Anim["Idle"].Animation(Sprite, 0.f);
	}
}

Bonus& Main_Joueur::GetFirstBonus()
{
	if (MyBonus.size() > 0) {
		return MyBonus[0];
	}
	
	Bonus tmp;
	return tmp;
}

void Main_Joueur::SetBonus(Bonus::Type first)
{
	if (MyBonus.size() < 1) {
		MyBonus.push_back(Bonus(first));
	}
	else {
		MyBonus[0] = Bonus(first);
	}
}

void Main_Joueur::InteractionBonus(std::list<Bonus>& bonus, Draw& Drawable, sf::Sprite& m_BonusExplication, float& m_BonusExplication_timer, const bool effect)
{
	for (auto it = bonus.begin(); it != bonus.end(); it++) {
		if (Collisions::Intersect(Hitbox, it->GetHitbox())) {
			if (effect) {
				if (it->GetType() != Bonus::Type::None) {
					if (MyBonus.size() > 2) {
						MyBonus[2] = MyBonus[1];
						MyBonus[1] = MyBonus[0];
						MyBonus[0] = Bonus(it->GetType());
					}
					else {
						MyBonus.push_back(Bonus(it->GetType()));
					}
					m_BonusExplication_timer = 0.f;

					switch (it->GetType())
					{
					case Bonus::Type::Contre:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_contre_tacle"), true);
						break;
					case Bonus::Type::AntiCheck:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_Anti_Check"), true);
						break;
					case Bonus::Type::Ralentissement:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_Ralentissement"), true);
						break;
					case Bonus::Type::AxeInversé:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_Axe_inverse"), true);
						break;
					case Bonus::Type::TirTP:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_Teleportation"), true);
						break;
					case Bonus::Type::MachineBoost:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_machine_boost"), true);
						break;
					case Bonus::Type::Piratage:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_piratage"), true);
						break;
					case Bonus::Type::MapScan:
						//m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_piratage"), true);
						break;
					case Bonus::Type::LeurreZone:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_fausse_ressource"), true);
						break;
					case Bonus::Type::LeurreBonus:
						m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_faux_bonus"), true);
						break;
					default: break;
					}
				}
				else if (MyBonus.size() > 0) {
					
					MyBonus.erase(MyBonus.begin());
				}
			}

			if (it->GetType() == Bonus::Type::None) {
				SetFeedback(Statut::faux_Bonus);
			}

			Drawable.erase(std::remove_if(std::begin(Drawable), std::end(Drawable),
				[&it](std::pair<bool, sf::Sprite*> d) {return d.second == &it->GetSprite(); }));
			bonus.erase(it);
			break;
		}
	}
}

void Main_Joueur::Interaction(std::map<int, Joueur*>& joueurs)
{
	m_SoundTacle.setVolume(Options::volumeBruitages);
	m_SoundCheck.setVolume(Options::volumeBruitages);
	m_soundAntiCheck.setVolume(Options::volumeBruitages);
	m_soundAntiTacle.setVolume(Options::volumeBruitages);
	m_soundMove.setVolume(Options::volumeBruitages);
	m_soundConfusion.setVolume(Options::volumeBruitages);
	m_soundslow.setVolume(Options::volumeBruitages);
	m_soundTp.setVolume(Options::volumeBruitages);

	for (auto& it : joueurs) {
		Main_Joueur* tmp = static_cast<Main_Joueur*>(it.second);

		if (tmp != this) {
			if (tmp->UseBonus) {

				switch (tmp->MyBonus.begin()->GetType())
				{
				case Bonus::Type::AxeInversé:
					if (m_soundConfusion.getStatus() != sf::Sound::Status::Playing)
						m_soundConfusion.play();
					SetFeedback(Statut::Axe_Inversé);
					tmp->SetFeedback(Statut::Diabolique);
					break;
				case Bonus::Type::Ralentissement:
					if (m_soundslow.getStatus() != sf::Sound::Status::Playing)
						m_soundslow.play();
					Slow = 0.5f;
					SetFeedback(Statut::Ralenti);
					tmp->SetFeedback(Statut::Diabolique);
					break;
				}
			}

			if (Collisions::Between2Circles(GetPos(), tmp->GetPos(), 150)) {

				if (tmp->Check && Check) {
					if (tmp->UseBonus && tmp->GetFirstBonus().GetType() == Bonus::Type::AntiCheck) {
						if (m_soundAntiCheck.getStatus() != sf::Sound::Status::Playing)
							m_soundAntiCheck.play();

						SetFeedback(Statut::Enerver);
						tmp->SetFeedback(Statut::Diabolique);
						tmp->SetFeedback(Statut::Check);
					}
					else {
						if (m_SoundCheck.getStatus() != sf::Sound::Status::Playing)
							m_SoundCheck.play();

						Speed = 1.5f;
						SetFeedback(Statut::Check);
						tmp->SetFeedback(Statut::Check);
					}

					if (UseBonus && GetFirstBonus().GetType() == Bonus::Type::AntiCheck) {
						if (m_soundAntiCheck.getStatus() != sf::Sound::Status::Playing)
							m_soundAntiCheck.play();

						tmp->SetFeedback(Statut::Enerver);
						SetFeedback(Statut::Diabolique);
						SetFeedback(Statut::Check);
					}
				}
				if (tmp->Tacle && Invulnérable < 0.f) {
					if (UseBonus && MyBonus.begin()->GetType() == Bonus::Type::Contre) {

						if (m_soundAntiTacle.getStatus() != sf::Sound::Status::Playing)
							m_soundAntiTacle.play();

						SetFeedback(Statut::Contre_Tacle);
						tmp->SetFeedback(Statut::Etourdit);
					}
					else {
						if (m_SoundTacle.getStatus() != sf::Sound::Status::Playing)
							m_SoundTacle.play();

						SetFeedback(Statut::Etourdit);
						tmp->SetFeedback(Statut::Diabolique);
						Tacle = false;
						Invulnérable = 6.f;
					}
				}
				if (Tacle) {
					if (tmp->UseBonus && tmp->MyBonus.begin()->GetType() == Bonus::Type::Contre) {

						if (m_soundAntiTacle.getStatus() != sf::Sound::Status::Playing)
							m_soundAntiTacle.play();

						tmp->SetFeedback(Statut::Contre_Tacle);
						SetFeedback(Statut::Etourdit);
					}
					else {
						if (m_SoundTacle.getStatus() != sf::Sound::Status::Playing)
							m_SoundTacle.play();

						tmp->SetFeedback(Statut::Etourdit);
						SetFeedback(Statut::Diabolique);
					}
				}
			}
			if (Collisions::Between2Circles(GetPos(), tmp->GetPos(), 200)) {
				if (tmp->UseBonus && Invulnérable < 0.f &&
					tmp->MyBonus.begin()->GetType() == Bonus::Type::TirTP) {

					if (m_soundTp.getStatus() != sf::Sound::Status::Playing)
						m_soundTp.play();
					tmp->SetFeedback(Statut::Diabolique);
					Tp = true;
					Anim["Tp"].Restart_Anim();
					Invulnérable = 6.f;
				}
			}
		}
	}
}

void Main_Joueur::Controle(const float& dt, Network* network, ManagerBonus& bonus, Draw& Drawable)
{
	Gamepads g;

	if (FeedBacks.find(Statut::Axe_Inversé) != FeedBacks.end()) {
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Left)) {
			Velocity.x = 500 * Speed * Slow * dt;
			m_dir = Direction::Right;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Right)) {
			Velocity.x = -500 * Speed * Slow * dt;
			m_dir = Direction::Left;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Up)) {
			Velocity.y = 500 * Speed * Slow * dt;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Down)) {
			Velocity.y = -500 * Speed * Slow * dt;
		}
	}
	else {
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Left)) {
			Velocity.x = -500 * Speed * Slow * dt;
			m_dir = Direction::Left;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Right)) {
			Velocity.x = 500 * Speed * Slow * dt;
			m_dir = Direction::Right;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Up)) {
			Velocity.y = -500 * Speed * Slow * dt;
		}
		if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Down)) {
			Velocity.y = 500 * Speed * Slow * dt;
		}
	}

	if (g.on_pressed(0, Xbox::Button::B) && !Tacle) {
		Tacle = true;
	}
	if (g.on_pressed(0, Xbox::Button::X) && !Check) {
		Check = true;
	}
	if (g.on_pressed(0, Xbox::Button::Y) && !UseBonus && MyBonus.size() > 0) {
		if (MyBonus[0].GetType() == Bonus::Type::LeurreBonus) {
			if (m_dir == Direction::Right)
				bonus.AddBonus(GetPos() + sf::Vector2f(150, 0), Bonus::Type::None, Drawable);
			if (m_dir == Direction::Left)
				bonus.AddBonus(GetPos() + sf::Vector2f(-150, 0), Bonus::Type::None, Drawable);
			MyBonus.erase(MyBonus.begin());

			Bonus* b[3] = { &bonus.GetBonusMap().back() , nullptr, nullptr };

			network->updateInfos(b);
		}
		else if (MyBonus[0].GetType() == Bonus::Type::MapScan) {
			SeeOthersTimer = 15.f;

			MyBonus.erase(MyBonus.begin());
		}
		else {
			UseBonus = true;

			if (MyBonus[0].GetType() == Bonus::Type::AxeInversé ||
				MyBonus[0].GetType() == Bonus::Type::TirTP ||
				MyBonus[0].GetType() == Bonus::Type::LeurreBonus ||
				MyBonus[0].GetType() == Bonus::Type::Ralentissement ||
				MyBonus[0].GetType() == Bonus::Type::LeurreZone ||
				MyBonus[0].GetType() == Bonus::Type::Piratage) {
				SetFeedback(Statut::Diabolique);
			}
		}
	}

	if (g.on_pressed(0, Xbox::Button::RB) && MyBonus.size() > 1) {
		if (MyBonus.size() == 2) {
			Bonus tmp = MyBonus[1];
			MyBonus[1] = MyBonus[0];
			MyBonus[0] = tmp;
		}

		if (MyBonus.size() == 3) {
			Bonus tmp = MyBonus[2];
			MyBonus[2] = MyBonus[1];
			MyBonus[1] = MyBonus[0];
			MyBonus[0] = tmp;
		}
	}
	if (g.on_pressed(0, Xbox::Button::LB) && MyBonus.size() > 1) {
		if (MyBonus.size() == 2) {
			Bonus tmp = MyBonus[1];
			MyBonus[1] = MyBonus[0];
			MyBonus[0] = tmp;
		}

		if (MyBonus.size() == 3) {
			Bonus tmp = MyBonus[1];
			MyBonus[1] = MyBonus[2];
			MyBonus[2] = MyBonus[0];
			MyBonus[0] = tmp;
		}
	}


	if (!g.is_pressed(0, Xbox::Axis::LeftJoystick_Left) && !g.is_pressed(0, Xbox::Axis::LeftJoystick_Right) || Tp) {
		Velocity.x = 0;
	}
	if (!g.is_pressed(0, Xbox::Axis::LeftJoystick_Up) && !g.is_pressed(0, Xbox::Axis::LeftJoystick_Down) || Tp) {
		Velocity.y = 0;
	}

	if (Velocity.x != 0.f && Velocity.y != 0.f) {
		Velocity *= 0.709f;
	}

	if (abs(CurrentSpeed.x) < abs(Velocity.x))
		CurrentSpeed.x += getSigne(Velocity.x) * 5.f * dt;
	if (abs(CurrentSpeed.y) < abs(Velocity.y))
		CurrentSpeed.y += getSigne(Velocity.y) * 5.f * dt;
	if ((int)Velocity.x == 0) {
		if (CurrentSpeed.x < 0.f)
			CurrentSpeed.x += dt * 5.f;
		if (CurrentSpeed.x > 0.f)
			CurrentSpeed.x -= dt * 5.f;
	}
	if ((int)Velocity.y == 0) {
		if (CurrentSpeed.y < 0.f)
			CurrentSpeed.y += dt * 5.f;
		if (CurrentSpeed.y > 0.f)
			CurrentSpeed.y -= dt * 5.f;
	}
}

void Main_Joueur::Update(const float& dt, sf::Image& image, Map& map)
{
	if (SeeOthersTimer >= 0.f) {
		SeeOthersTimer -= dt;
	}

	Hitbox.setPosition(Sprite.getPosition() + Velocity);

	if (Velocity != sf::Vector2f(0.f, 0.f)) {
		if (abs(Velocity.x) >= abs(Velocity.y)) {
			if (Velocity.x != 0) {
				m_look = (Velocity.x < 0) ? Looking::Left : Looking::Right;
			}
		}
		else {
			if (Velocity.y != 0) {
				m_look = (Velocity.y < 0) ? Looking::Up : Looking::Down;
			}
		}
	}

	if (FeedBacks.find(Statut::Check) == FeedBacks.end()) {
		Speed = 1;
	}
	if (FeedBacks.find(Statut::Ralenti) == FeedBacks.end()) {
		Slow = 1;
	}

	Get_NextPos2(dt, image, map);

	sf::Vector2f nextpos = Sprite.getPosition();
	
	if (nextpos.x + Sprite.getGlobalBounds().width / 2 > image.getSize().x && Velocity.x > 0)
		ColDroite = true;
	else if (nextpos.x - Sprite.getGlobalBounds().width / 2 < 0 && Velocity.x < 0)
		ColGauche = true;
	else if (nextpos.y - Sprite.getGlobalBounds().height / 2 < 0 && Velocity.y < 0)
		ColHaut = true;
	else if (nextpos.y + Sprite.getGlobalBounds().height / 2 > image.getSize().y && Velocity.y > 0)
		ColBas = true;

	if (ColBas || ColHaut) {
		Velocity.y = 0;
	}
	if (ColDroite || ColGauche) {
		Velocity.x = 0;
	}

	if (Tacle) {
		TimerTacle += dt;

		if (TimerTacle > 0.5f) {
			TimerTacle = 0;
			Tacle = false;
		}
	}
	if (UseBonus) {
		TimerUseBonus += dt;

		if (TimerUseBonus > 2.5f) {
			TimerUseBonus = 0;
			MyBonus.erase(MyBonus.begin());
			UseBonus = false;
		}
	}
	if (Check) {
		TimerCheck += dt;

		if (TimerCheck > 0.5f) {
			Check = false;
			TimerCheck = 0;
		}
	}
	if (FeedBacks.find(Statut::Etourdit) != FeedBacks.end()) {
		Velocity.y = 0;
		Velocity.x = 0;
	}

	Move();

	if (m_dir == Direction::Left) {
		Sprite.setScale(-1.f, 1.f);
	}
	if (m_dir == Direction::Right) {
		Sprite.setScale(1.f, 1.f);
	}
}

void Main_Joueur::Animation(const float& dt)
{
	if (Tp) {
		Anim["Tp"].Animation_NoRestart(Sprite, dt);

		if (Anim["Tp"].Get_End()) {
			SetPos({ random::RandomFloat(50,7950),random::RandomFloat(50,7950) });
			Tp = false;
		}
	}
	else
	{
		if (GetIddle() && Anim["Anim"].Get_End()) {
			Anim["Idle"].Animation(Sprite, dt);
		}
		else {
			Anim["Anim"].Animation(Sprite, dt);
		}
	}
}

void Main_Joueur::FeedBackAnim(const float& dt)
{
	if (Invulnérable >= 0) {
		Invulnérable -= dt;
	}

	if (Anim["Anim"].Get_Frame() == 25) {
		if (m_soundMove.getStatus() != sf::Sound::Status::Playing)
			m_soundMove.play();
	}

	for (auto it = FeedBacks.begin(); it != FeedBacks.end();) {
		it->second.second -= dt;

		if (it->first == Statut::Axe_Inversé && it->first == Statut::Etourdit &&
			it->first == Statut::Ralenti) {

			it->second.first.Animation({ GetPos().x, GetPos().y + 1 }, dt);
			if (it->second.second <= 0) {
				it = FeedBacks.erase(it);
			}
			else {
				it++;
			}
		}
		else {
			it->second.first.Animation_NoRestart({GetPos().x, GetPos().y + 1}, dt);
			if (it->second.first.Get_End() && it->second.second <= 0) {
				it = FeedBacks.erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void Main_Joueur::DisplayFeedback(WindowManager& window)
{
	for (auto& it : FeedBacks) {
		window.draw(it.second.first.GetSprite());
	}
}

bool CollideMap(Map& map, sf::Vector2f pos) {
	for (auto& node : map.getNodes()) {
		if (node.Minerais.getGlobalBounds().contains(pos)) {
			return true;
		}
	}

	return false;
}

void Main_Joueur::Get_NextPos2(const float& dt, sf::Image& image, Map& map)
{
	ColGauche = false;
	ColDroite = false;
	ColHaut = false;
	ColBas = false;

	sf::Vector2f Next = Hitbox.getPosition();
	Next.y -= Hitbox.getGlobalBounds().height / 2;
	if (Velocity.x < 0) {
		Next.x -= Hitbox.getGlobalBounds().width / 2;

		for (int i = 5; i < (int)Hitbox.getGlobalBounds().height - 5; i++) {
			for (float y = 0; y < (double)-Velocity.x * dt; y += (double)0.1f) {
				sf::Vector2f test(Next.x - y, Next.y + i);
				if (CheckCollid(test, image) || CollideMap(map, test)) {
					ColGauche = true;
					break;
				}
			}
		}
	}
	else if (Velocity.x > 0) {
		Next.x += Hitbox.getGlobalBounds().width / 2;

		for (int i = 5; i < (int)Hitbox.getGlobalBounds().height - 5; i++) {
			for (float y = 0; y < (double)Velocity.x * dt; y += (double)0.1f) {
				sf::Vector2f test(Next.x + y, Next.y + i);
				if (CheckCollid(test, image) || CollideMap(map, test)) {
					ColDroite = true;
					break;
				}
			}
		}
	}

	Next = Hitbox.getPosition();
	Next.x -= Hitbox.getGlobalBounds().width / 2;

	if (Velocity.y < 0) {
		Next.y -= Hitbox.getGlobalBounds().height / 2;

		for (int i = 2; i < (int)Hitbox.getGlobalBounds().width - 2; i++) {
			for (float y = 0; y < (double)-Velocity.y * dt + 0.1; y += (double)0.1f) {
				sf::Vector2f test(Next.x + i, Next.y - y - 1);
				if (CheckCollid(test, image) || CollideMap(map, test)) {
					ColHaut = true;
					break;
				}
			}
		}
	}
	else if (Velocity.y > 0) {
		Next.y += Hitbox.getGlobalBounds().height / 2;
		for (int i = 2; i < (int)Hitbox.getGlobalBounds().width - 2; i++) {
			for (float y = 0; y < (double)Velocity.y * dt + 0.1; y += (double)0.1f) {
				sf::Vector2f test(Next.x + i, Next.y + y);
				if (CheckCollid(test, image) || CollideMap(map, test)) {
					ColBas = true;
					break;
				}
			}
		}
	}
}
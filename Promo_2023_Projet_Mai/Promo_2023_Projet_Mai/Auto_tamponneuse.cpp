#include "Auto_tamponneuse.h"
#include "Cache.h"
#include "Functions.h"
#include <random>
#include "Gamepad.h"
#include "MenuIG.h"
#include "Transition.h"
#include "Options.h"
#include "Game.h"

Auto_tamponneuse::Auto_tamponneuse(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change)
	: FSM{ mgr,window,font,change }
{
	m_musicAT.openFromFile("../Ressources/Sons/MinijeuxdeGroupeJW.wav");
	m_musicAT.setLoop(true);
	m_musicAT.setVolume(Options::volumeSound);
	m_musicAT.play();
	Game::m_gameMusic.stop();

	//////////////////////ScoreBoard///////////////
	sc.bc.setTexture(&Cache::GetRessources<sf::Texture>("fenetre_score"));
	sc.bc.setSize(Vector2f(1920, 1080));
	sc.bc.setOrigin(sc.bc.getGlobalBounds().width / 2, sc.bc.getGlobalBounds().height / 2);
	sc.bc.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

	/////////////////////Map//////////////////////
	map.bc.setTexture(&Cache::GetRessources<sf::Texture>("Arene"));
	map.bc.setSize(Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	map.bc.setOrigin(map.bc.getGlobalBounds().width / 2, map.bc.getGlobalBounds().height / 2);
	map.bc.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

	map.bounds.setRadius(495.f);
	map.bounds.setOrigin(map.bounds.getGlobalBounds().width / 2, map.bounds.getGlobalBounds().height / 2);
	map.bounds.setFillColor(Color::Transparent);
	map.bounds.setOutlineColor(Color::Red);
	map.bounds.setOutlineThickness(-1.f);
	map.bounds.setPosition(map.bc.getPosition());

	map.weel.setTexture(&Cache::GetRessources<sf::Texture>("WeelV2"));
	map.weel.setSize(Vector2f(static_cast<float>(map.weel.getTextureRect().width), static_cast<float>(map.weel.getTextureRect().height)));
	map.weel.setOrigin(map.weel.getGlobalBounds().width / 2.f, map.weel.getGlobalBounds().height / 2.f);
	map.weel.setPosition(Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

	map.glasse.setTexture(&Cache::GetRessources<sf::Texture>("arene_verre"));
	map.glasse.setRadius(map.glasse.getTextureRect().height / 2.f);
	map.glasse.setOrigin(map.glasse.getGlobalBounds().width / 2.f, map.glasse.getGlobalBounds().height / 2.f);
	map.glasse.setPosition(map.bc.getPosition());

	////////////////////Player//////////////////////
	std::mt19937 mt(std::random_device{}());
	std::uniform_real_distribution<float> distx{ 600.f , static_cast<float>(window.getSize().x) - 600.f };
	std::uniform_real_distribution<float> disty{ 250.f , static_cast<float>(window.getSize().y) - 250.f };

	if (m_mgr.Network() != nullptr) {
		player = new AT_Joueur(Vector2f(distx(mt), disty(mt)), static_cast<int>(m_mgr.Network()->youInfos().color));
	}
	else {
		player = new AT_Joueur(Vector2f(distx(mt), disty(mt)), 0);
	}

	////////////////////HUD///////////////////////
	hud.setTexture(&Cache::GetRessources<sf::Texture>("HUD-miniJeu(" + std::to_string(player->GetColor()) + ")"));
	hud.setSize(Vector2f(static_cast<float>(hud.getTextureRect().width), static_cast<float>(hud.getTextureRect().height)));
	huds.emplace("PLAYER", hud);

	Tete2.setTexture(Cache::GetRessources<sf::Texture>("(" + std::to_string(player->GetColor()) + ")PersoFACE"));

	place.setTexture(Cache::GetRessources<sf::Texture>("place_joueur"));
	loterie.setTexture(Cache::GetRessources<sf::Texture>("loterie"));
	Ecran_Explication.setTexture(Cache::GetRessources<sf::Texture>("explication_autotamponneuse"));
	Tete.setTexture(Cache::GetRessources<sf::Texture>("tete_fin_mini_jeu"));
	Lueur.setTexture(Cache::GetRessources<sf::Texture>("LueurBonus"));


	place.setPosition(sf::Vector2f(1130.f, 250.f));
	Ecran_Explication.setPosition(sf::Vector2f(0.f, 0));
	loterie.setPosition(sf::Vector2f(1100.f, 600.f));
	Tete.setPosition(sf::Vector2f(1350.f, 240.f));
	Tete2.setPosition(1433.f, 327.f);

	anim = Animator(sf::IntRect(0, 0, 378, 378), 26, 0.1f, Lueur.getGlobalBounds().height, false);

	Tclassement.setFont(font);
	Tclassement.setCharacterSize(40);
	Tclassement.setFillColor(sf::Color::White);

	Tclassement.setString(text_class);
	Tclassement.setPosition(sf::Vector2f(1182.f, 300.f));

	Lueur.setPosition(1160, 590);

	state = State_MJ::EXPLICATION;

	//player->Set_Score(2);
}

void Auto_tamponneuse::processEvents(const sf::Event&)
{
}

void Auto_tamponneuse::update(const float& _dt)
{
	if (m_musicAT.getStatus() != sf::Sound::Status::Playing)
	{
		Game::m_gameMusic.stop();
		m_musicAT.play();
	}

	m_musicAT.setVolume(Options::volumeSound);

	switch (state)
	{
	case State_MJ::EXPLICATION:
		timer_ecran -= _dt;

		if (timer_ecran <= 0.f)
		{
			state = State_MJ::JEU;
			timer_ecran = 10.f;
		}
		break;
	case State_MJ::JEU:
		if (m_window.hasFocus())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				//m_mgr.goBackState();
				m_mgr.SoftGoBackTransition<Transition<Auto_tamponneuse>>(m_mgr, m_window, m_font, true);
			}
			Gamepads g;


			if (g.on_pressed(0, Xbox::Button::Select))
				m_mgr.AddState(FSM_Manager::create<MenuIG>(m_mgr, m_window, m_font, true));

		}

		this->GivePoint();

		if (m_mgr.Network() != nullptr)
		{
			m_mgr.Network()->updateInfos(player);
			m_mgr.Network()->processEvents(others, player, _dt);
		}

		this->HudUpdate();

		if (!isWin) {
			player->Update(_dt, map.bounds, m_window.hasFocus());
		}

		/*if (m_window.hasFocus())
		{*/
		if ((onePass && player->IsAlive() && this->CheckOthers() <= 0) ||
			(onePass && !player->IsAlive() && this->CheckOthers() == 1))
		{
			this->UpdateScoreBoard();
			isWin = true;

			state = State_MJ::VICTOIRE;
			if (player->GetScore() < 3)
				bonuswin = Bonus(sf::Vector2f(1340, 770));
		}

		if (!isWin)
		{
			std::map<int, Joueur*> tmp;
			for (auto& [i, current_player] : others) {
				tmp[i] = current_player;
			}
			player->Interaction(tmp, _dt, m_mgr.Network());
		}
		//}

		this->Spin(_dt);

		break;

	case State_MJ::VICTOIRE:
		if (m_mgr.Network() != nullptr)
		{
			m_mgr.Network()->updateInfos(player);
			m_mgr.Network()->processEvents(others, player, _dt);
		}

		anim.Animation(Lueur, _dt);
		timer_ecran -= _dt;
		if (timer_ecran <= 0.f)
		{
			if (player->GetScore() < 3)
				m_mgr.Network()->setWinBonus(bonuswin.GetType());
			else
				m_mgr.Network()->setWinBonus(Bonus::Type::None);

			m_mgr.SoftGoBackTransition<Transition<Auto_tamponneuse>>(m_mgr, m_window, m_font, true);
			//m_mgr.goBackState();
		}
		break;
	}
}

void Auto_tamponneuse::draw()
{
	switch (state)
	{
	case State_MJ::EXPLICATION:
		m_window.draw(map.bc);
		m_window.draw(map.weel);
		m_window.draw(map.glasse);

		m_window.draw(Ecran_Explication);
		break;
	case State_MJ::JEU:
		m_window.draw(map.bc);
		m_window.draw(map.weel);
		m_window.draw(map.glasse);

		player->Display(m_window);

		for (auto& [id, other] : others)
			other->Display(m_window);

		if (!isWin)
		{
			for (auto& it : huds)
				m_window.draw(it.second);
		}
		break;
	case State_MJ::VICTOIRE:
		m_window.draw(sc.bc);

		for (auto& it : sc.portrait)
			m_window.draw(it);

		m_window.draw(place);
		m_window.draw(loterie);

		if (player->GetScore() < 2)
		{
			m_window.draw(Lueur);
			bonuswin.Display(m_window);
		}

		m_window.draw(Tete);
		m_window.draw(Tete2);
		text_class = std::to_string(player->GetScore());
		Tclassement.setString(text_class);
		m_window.draw(Tclassement);

		break;
	}

}

void Auto_tamponneuse::Spin(const float& dt)
{
	map.weel.rotate(10 * dt);
}

void Auto_tamponneuse::HudUpdate()
{
	if (!player->IsAlive())
		huds["PLAYER"].setFillColor(Color(255, 255, 255, 100));
	else
		huds["PLAYER"].setFillColor(Color::White);

	if (others.size() > 0)
	{
		for (auto& [id, pl] : others)
		{
			cpt++;
			hud.setTexture(&Cache::GetRessources<sf::Texture>("HUD-miniJeu(" + std::to_string(pl->GetColor()) + ")"));

			if (cpt == 1)
				hud.setPosition(Vector2f(0.f, static_cast<float>(hud.getTextureRect().height)));
			else if (cpt == 2)
				hud.setPosition(Vector2f(0.f, hud.getTextureRect().height * 2.f));
			else if (cpt == 3)
				hud.setPosition(Vector2f(0.f, hud.getTextureRect().height * 3.f));
			else if (cpt == 4)
				hud.setPosition(Vector2f(1080.f - static_cast<float>(hud.getTextureRect().width), 0.f));
			else if (cpt == 5)
				hud.setPosition(Vector2f(1080.f - static_cast<float>(hud.getTextureRect().width), static_cast<float>(hud.getTextureRect().height)));
			else if (cpt == 6)
				hud.setPosition(Vector2f(1080.f - static_cast<float>(hud.getTextureRect().width), hud.getTextureRect().height * 2.f));
			else if (cpt == 7)
				hud.setPosition(Vector2f(1080.f - static_cast<float>(hud.getTextureRect().width), hud.getTextureRect().height * 3.f));
			else if (cpt == 8)
				hud.setPosition(Vector2f(1080.f - static_cast<float>(hud.getTextureRect().width), hud.getTextureRect().height * 4.f));

			hud.setSize(Vector2f(167.f, 177.f));
			huds.emplace("OTHER_" + std::to_string(id), hud);
		}

		onePass = true;
		cpt = 0;

		if (huds.size() > 0)
		{
			for (auto& [id, pl] : others)
			{
				if (!others[id]->IsAlive())
					huds["OTHER_" + std::to_string(id)].setFillColor(Color(255, 255, 255, 100));
				else
					huds["OTHER_" + std::to_string(id)].setFillColor(Color::White);
			}
		}
	}
}

int Auto_tamponneuse::CheckOthers()
{
	int otherAlive = 0;

	for (auto& it : others)
	{
		if (it.second->IsAlive())
			otherAlive++;
	}

	return otherAlive;
}

void Auto_tamponneuse::GivePoint()
{
	if (player->IsAlive())
		player->Set_Score(CheckOthers() + 1);

}

void Auto_tamponneuse::UpdateScoreBoard()
{
	if (end == false)
	{
		if (player->IsAlive() && this->CheckOthers() <= 0)
			player->Set_Score(1);

		RectangleShape tmp;
		tmp.setTexture(&Cache::GetRessources<sf::Texture>("InconiBlob"));
		tmp.setSize(Vector2f(96, 98));
		tmp.setOrigin(tmp.getGlobalBounds().width / 2, tmp.getGlobalBounds().height / 2);

		sc.classement.resize(others.size() + 1);

		for (int i = 0; i < sc.classement.size(); ++i)
		{
			if (i == 0)
				tmp.setPosition(Vector2f(870.f, 245.f));
			else if (i == 1)
				tmp.setPosition(Vector2f(870.f, 340.f));
			else if (i == 2)
				tmp.setPosition(Vector2f(870.f, 430.f));
			else if (i == 3)
				tmp.setPosition(Vector2f(870.f, 520.f));
			else if (i == 4)
				tmp.setPosition(Vector2f(870.f, 615.f));
			else if (i == 5)
				tmp.setPosition(Vector2f(870.f, 705.f));
			else if (i == 6)
				tmp.setPosition(Vector2f(870.f, 795.f));
			else if (i == 7)
				tmp.setPosition(Vector2f(870.f, 890.f));

			sc.portrait.push_back(tmp);
		}

		for (auto& it : others)
			players.push_back(it.second);

		players.push_back(player);

		std::sort(players.begin(), players.end(), [](AT_Joueur* a, AT_Joueur* b) { return a->GetScore() < b->GetScore(); });

		for (int i = 0; i < players.size(); ++i)
			sc.portrait[i].setTexture(&Cache::GetRessources<sf::Texture>("(" + std::to_string(players[i]->GetColor()) + ")PersoFACE"));

		end = true;
	}
}

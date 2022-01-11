#include "Battle_Royal.h"
#include "Cache.h"
#include <string>
#include "Functions.h"
#include "Gamepad.h"
#include "MenuIG.h"
#include "Transition.h"
#include "Options.h"
#include "Game.h"

Battle_Royal::Battle_Royal(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change) : FSM{ mgr,window,font,change }
{
	m_musicBR.openFromFile("../Ressources/Sons/MinijeuxdeGroupeJW.wav");
	m_musicBR.setLoop(true);
	m_musicBR.setVolume(Options::volumeSound);
	m_musicBR.play();
	Game::m_gameMusic.stop();

	fond.setTexture(Cache::GetRessources<sf::Texture>("mapBR"));
	Ecran_Victoire.setTexture(Cache::GetRessources<sf::Texture>("fenetre_mini_jeu2"));
	Ecran_Explication.setTexture(Cache::GetRessources<sf::Texture>("fenetre_mini_jeu"));

	place.setTexture(Cache::GetRessources<sf::Texture>("place_joueur"));
	loterie.setTexture(Cache::GetRessources<sf::Texture>("loterie"));
	Tete.setTexture(Cache::GetRessources<sf::Texture>("tete_fin_mini_jeu"));
	HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score1"));
	Ecran.setTexture(Cache::GetRessources<sf::Texture>("fond_timer"));
	image.loadFromFile("../Ressources/MiniJeuBR/level design arene.png");

	Lueur.setTexture(Cache::GetRessources<sf::Texture>("LueurBonus"));

	Cam.setSize(1920, 1080);

	state = State_MJ::EXPLICATION;

	Ecran.setPosition(sf::Vector2f(910.f, 0.f));
	place.setPosition(sf::Vector2f(1130.f, 250.f));
	Ecran_Explication.setPosition(sf::Vector2f(0.f, 0));
	Ecran_Victoire.setPosition(sf::Vector2f(0.f, 0));
	loterie.setPosition(sf::Vector2f(1100.f, 600.f));
	Tete.setPosition(sf::Vector2f(1350.f, 240.f));

	Tclassement.setFont(font);
	Tclassement.setCharacterSize(40);
	Tclassement.setFillColor(sf::Color::White);

	text_class = std::to_string(classement);
	Tclassement.setString(text_class);
	Tclassement.setPosition(sf::Vector2f(1182.f, 300.f));

	Score.setFont(Cache::GetRessources<sf::Font>("Linebeam"));
	Score.setCharacterSize(50);
	Score.setFillColor(sf::Color::White);

	Timer.setFont(Cache::GetRessources<sf::Font>("Linebeam"));
	Timer.setCharacterSize(80);
	Timer.setFillColor(sf::Color::White);

	timer_text = std::to_string(timer_jeu);
	Timer.setString(text_class);
	Timer.setPosition(sf::Vector2f(995.f, 80.f));

	if (m_mgr.Network() != nullptr) {
		player.SetColor(m_mgr.Network()->youInfos().color);
	}

	player.Set_spawn();

	anim = Animator(sf::IntRect(0, 0, 378, 378), 26, 0.1f, Lueur.getGlobalBounds().height, false);

	Lueur.setPosition(1160, 590);
}

void Battle_Royal::processEvents(const sf::Event& e)
{
}

void Battle_Royal::update(const float& dt)
{
	if (m_musicBR.getStatus() != sf::Sound::Status::Playing)
	{
		Game::m_gameMusic.stop();
		m_musicBR.play();
	}

	m_musicBR.setVolume(Options::volumeSound);

	switch (state) {

	case State_MJ::EXPLICATION:
		Explication(dt);
		break;
	case State_MJ::JEU:
		Timer.setOrigin(func::GetMiddle(Timer));
		for (auto& [id, pl] : others) {
			pl->Controle(dt);
		}
		UpdateGame(dt);
		break;
	case State_MJ::VICTOIRE:
		anim.Animation(Lueur, dt);
		Victoire(dt);
		break;
	}

}

void Battle_Royal::draw()
{
	m_window.setView(Cam);
	m_window.draw(fond);

	int tmp = 533;
	switch (state) {

	case State_MJ::EXPLICATION:
		m_window.setView(m_window.getDefaultView());
		m_window.draw(Ecran_Explication);
		if (player.GetPos().x < 960)
		{
			PosCam.x = 960;
		}
		else if (player.GetPos().x > 2040)
		{
			PosCam.x = 2040;
		}
		else
		{
			PosCam.x = player.GetPos().x;
		}
		if (player.GetPos().y < 540)
		{
			PosCam.y = 540;
		}
		else if (player.GetPos().y > 2460)
		{
			PosCam.y = 2460;
		}
		else
		{
			PosCam.y = player.GetPos().y;
		}
		Cam.setCenter(PosCam);
		m_window.setView(Cam);
		break;
	case State_MJ::JEU:
		for (int i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].Display(m_window);
		}
		player.Display(m_window);

		for (auto& [id, pl] : others) {

			pl->Display_Inv(m_window, pl->is_invincible());
		}

		m_window.setView(m_window.getDefaultView());

		HUD_self();
		HUD.setPosition(sf::Vector2f(20.f, 20.f));
		m_window.draw(HUD);
		m_window.draw(Ecran);
		text_score = std::to_string(player.Get_score());
		Score.setString(text_score);
		Score.setPosition(sf::Vector2f(40.f + 20.f, 50.f + 20.f));
		m_window.draw(Score);
		m_window.draw(Score);

		t = static_cast<int>(timer_jeu);
		timer_text = std::to_string(t);
		Timer.setString(timer_text);
		m_window.draw(Timer);
		if (t < 10)
		{
			Ecran.setColor(sf::Color(253, 58, 58));
			Timer.setFillColor(sf::Color::Red);
		}
		Display_HUD();
		break;
	case State_MJ::VICTOIRE:
		m_window.setView(m_window.getDefaultView());
		m_window.draw(Ecran_Victoire);
		m_window.draw(place);
		m_window.draw(loterie);
		if (player.Get_Classement() < 2)
		{
			m_window.draw(Lueur);
			bonuswin.Display(m_window);
		}
		for (auto& [id, pl] : others) {
			pl->Display_Victoire(m_window);
		}
		m_window.draw(Tete);
		player.Display_Victoire(m_window);
		text_class = std::to_string(player.Get_Classement());
		Tclassement.setString(text_class);
		m_window.draw(Tclassement);
		//Cam.setCenter(player.GetPos());
		//m_window.setView(Cam);
		break;
	}
}

void Battle_Royal::Explication(const float& dt)
{
	timer_ecran -= dt;

	if (timer_ecran <= 0.f)
	{
		state = State_MJ::JEU;
		timer_ecran = 10.f;
	}
}

void Battle_Royal::UpdateGame(const float& dt)
{
	timer_jeu -= dt;

	Gamepads g;

	player.Update(dt, image, projectiles, m_mgr.Network(), m_window.hasFocus());
	if (m_window.hasFocus()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			//m_mgr.goBackState();
			m_mgr.SoftGoBackTransition<Transition<Battle_Royal>>(m_mgr, m_window, m_font, true);
		}
		if (g.on_pressed(0, Xbox::Button::Select))
			m_mgr.AddState(FSM_Manager::create<MenuIG>(m_mgr, m_window, m_font, true));

	}

	if (m_mgr.Network() != nullptr) {
		m_mgr.Network()->updateInfos(&player);
		m_mgr.Network()->processEvents(others, projectiles);
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].Update(dt, image, player, others);
		if (projectiles[i].Get_Vie() <= 0)
		{
			if (projectiles[i].owner != nullptr && projectiles[i].owner == &player && projectiles[i].Get_Vie() == -1 && !projectiles[i].get_used()) {
				player.setScore(player.Get_score() + 10);
				projectiles[i].set_used();
			}

			if (projectiles[i].get_finExplo())
			{
				projectiles.erase(projectiles.begin() + i);
			}

		}
	}

	Velocity.y = 0;
	Velocity.x = 0;

	if (g.is_pressed(0, Xbox::LeftJoystick_Up) && g.is_pressed(0, Xbox::LeftJoystick_Right))
	{
		if (PosCam.y > 540 && PosCam.y >= player.GetPos().y)
		{
			Velocity.y = -(speed - 50);;
		}

		if (PosCam.x < 2040 && PosCam.x <= player.GetPos().x)
		{
			Velocity.x = speed;
		}


	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Up) && g.is_pressed(0, Xbox::LeftJoystick_Left))
	{
		if (PosCam.y > 540 && PosCam.y >= player.GetPos().y)
		{
			Velocity.y = -(speed - 50);;
		}
		if (PosCam.x > 960 && PosCam.x >= player.GetPos().x)
		{
			Velocity.x = -(speed - 50);
		}
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Down) && g.is_pressed(0, Xbox::LeftJoystick_Right))
	{
		if (PosCam.y < 2460 && PosCam.y <= player.GetPos().y)
		{
			Velocity.y = speed;
		}
		if (PosCam.x < 2040 && PosCam.x <= player.GetPos().x)
		{
			Velocity.x = speed;
		}
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Down) && g.is_pressed(0, Xbox::LeftJoystick_Left))
	{
		if (PosCam.y < 2460 && PosCam.y <= player.GetPos().y)
		{
			Velocity.y = speed;
		}
		if (PosCam.x > 960 && PosCam.x >= player.GetPos().x)
		{
			Velocity.x = -(speed - 50);
		}
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Up))
	{
		if (PosCam.y > 540 && PosCam.y >= player.GetPos().y)
		{
			Velocity.y = -speed;
		}
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Down))
	{
		if (PosCam.y < 2460 && PosCam.y <= player.GetPos().y)
		{
			Velocity.y = speed;
		}
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Right))
	{
		if (PosCam.x < 2040 && PosCam.x <= player.GetPos().x)
		{
			Velocity.x = speed;
		}
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Left))
	{
		if (PosCam.x > 960 && PosCam.x >= player.GetPos().x)
		{
			Velocity.x = -speed;
		}
	}


	PosCam.x += Velocity.x * dt;
	PosCam.y += Velocity.y * dt;

	Cam.setCenter(PosCam);

	if (timer_jeu <= 0.f)
	{
		Set_Classement();
		randombonus();
		state = State_MJ::VICTOIRE;
	}
}

void Battle_Royal::Victoire(const float& dt)
{

	timer_ecran -= dt;

	if (timer_ecran <= 0.f)
	{
		if (player.Get_Classement() < 2)
		{
			m_mgr.Network()->setWinBonus(bonuswin.GetType());
		}
		else
		{
			m_mgr.Network()->setWinBonus(Bonus::Type::None);
		}

		//m_mgr.goBackState();
		m_mgr.SoftGoBackTransition<Transition<Battle_Royal>>(m_mgr, m_window, m_font, true);
	}
}

void Battle_Royal::Set_Classement()
{
	for (int i = 0; i < 8; i++)
	{
		tab[i] = true;
	}

	for (auto& [id, pl] : others) {

		tabscore.push_back(pl->Get_score());
	}

	tabscore.push_back(player.Get_score());

	std::sort(tabscore.begin(), tabscore.end(), [](int a, int b) {
		return a > b;
		});

	for (int i = 0; i < tabscore.size(); i++)
	{
		if (player.Get_score() == tabscore[i])
		{
			player.Set_Classement(i + 1);

		}
	}

	for (auto& [id, pl] : others) {

		for (int i = 0; i < tabscore.size(); i++)
		{
			if (pl->Get_score() == tabscore[i])
			{
				pl->Set_Classement(i + 1);
			}
		}
	}

	for (auto& [id, pl] : others)
	{
		for (auto& [ido, plo] : others)
		{

			if (plo->Get_Classement() == player.Get_Classement())
			{
				if (plo->Get_ID() > player.Get_ID())
				{
					plo->Set_Classement(plo->Get_Classement() - 1);
				}
				else
				{
					player.Set_Classement(player.Get_Classement() - 1);
				}
			}
			if (id != ido)
			{
				if (pl->Get_Classement() == plo->Get_Classement())
				{
					if (pl->Get_ID() > plo->Get_ID())
					{
						pl->Set_Classement(pl->Get_Classement() - 1);
					}
					else
					{
						plo->Set_Classement(plo->Get_Classement() - 1);
					}

				}

			}

		}
	}



}

void Battle_Royal::Display_HUD()
{
	for (auto& [id, pl] : others) {
		if (pl->Get_ID() == 1)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score1"));
		}
		else if (pl->Get_ID() == 2)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score2"));
		}
		else if (pl->Get_ID() == 3)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score3"));
		}
		else if (pl->Get_ID() == 4)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score4"));
		}
		else if (pl->Get_ID() == 5)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score5"));
		}
		else if (pl->Get_ID() == 6)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score6"));
		}
		else if (pl->Get_ID() == 7)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score7"));
		}
		else if (pl->Get_ID() == 8)
		{
			HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score8"));
		}

		compteur++;
		if (compteur == 1)
		{
			PosHUD = sf::Vector2f(370, 0);
		}
		else if (compteur == 2)
		{
			PosHUD = sf::Vector2f(1237, 0);
		}
		else if (compteur == 3)
		{
			PosHUD = sf::Vector2f(1587, 0);
		}
		else if (compteur == 4)
		{
			PosHUD = sf::Vector2f(20, 880);
		}
		else if (compteur == 5)
		{
			PosHUD = sf::Vector2f(370, 880);
		}
		else if (compteur == 6)
		{
			PosHUD = sf::Vector2f(1237, 880);
		}
		else if (compteur == 7)
		{
			PosHUD = sf::Vector2f(1587, 880);
		}

		HUD.setPosition(PosHUD);
		m_window.draw(HUD);

		text_score = std::to_string(pl->Get_score());
		Score.setString(text_score);
		Score.setPosition(sf::Vector2f(40.f + PosHUD.x, 50.f + PosHUD.y));
		m_window.draw(Score);
	}

	compteur = 0;
}

void Battle_Royal::HUD_self()
{
	if (player.Get_ID() == 1)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score1"));
	}
	else if (player.Get_ID() == 2)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score2"));
	}
	else if (player.Get_ID() == 3)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score3"));
	}
	else if (player.Get_ID() == 4)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score4"));
	}
	else if (player.Get_ID() == 5)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score5"));
	}
	else if (player.Get_ID() == 6)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score6"));
	}
	else if (player.Get_ID() == 7)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score7"));
	}
	else if (player.Get_ID() == 8)
	{
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score8"));
	}


}

void Battle_Royal::randombonus()
{
	if (player.Get_Classement() < 2)
	{
		bonuswin = Bonus(sf::Vector2f(1340, 770));
	}

}


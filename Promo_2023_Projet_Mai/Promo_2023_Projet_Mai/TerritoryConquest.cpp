#include "TerritoryConquest.h"
#include "Functions.h"
#include "Cache.h"
#include <sstream>
#include "Options.h"
#include "Gamepad.h"
#include "MenuIG.h"
#include "Transition.h"
#include "Game.h"

TerritoryConquest::TerritoryConquest(FSM_Manager& mgr, WindowManager& w, sf::Font& font, const bool change)
	: FSM{ mgr, w, font,change }, m_grid{ forms::Grid(0,2000,2000,100,{105,105,105,255}) },
	m_arene{ forms::CreateSprite({ 0,0 }, Cache::GetRessources<sf::Texture>("arene")) },
	m_expli{ forms::CreateSprite({0,0}, Cache::GetRessources<sf::Texture>("explication_conquetedeterritoire")) }
{
	m_musicTC.openFromFile("../Ressources/Sons/MinijeuxdeGroupeJW.wav");
	m_musicTC.setLoop(true);
	m_musicTC.setVolume(Options::volumeSound);
	m_musicTC.play();
	Game::m_gameMusic.stop();

	m_arrayTexture.at(0) = { Cache::GetRessources<sf::Texture>("cose_1"), Cache::GetRessources<sf::Texture>("cose_2"), Cache::GetRessources<sf::Texture>("cose_3") };
	m_arrayTexture.at(1) = { Cache::GetRessources<sf::Texture>("cose_4"),Cache::GetRessources<sf::Texture>("cose_5"),Cache::GetRessources<sf::Texture>("cose_6") };
	m_arrayTexture.at(7) = { Cache::GetRessources<sf::Texture>("cose_7"), Cache::GetRessources<sf::Texture>("cose_8"),Cache::GetRessources<sf::Texture>("cose_9") };
	m_arrayTexture.at(3) = { Cache::GetRessources<sf::Texture>("cose_10"),Cache::GetRessources<sf::Texture>("cose_11"),Cache::GetRessources<sf::Texture>("cose_12") };
	m_arrayTexture.at(4) = { Cache::GetRessources<sf::Texture>("cose_13"),Cache::GetRessources<sf::Texture>("cose_14"),Cache::GetRessources<sf::Texture>("cose_15") };
	m_arrayTexture.at(5) = { Cache::GetRessources<sf::Texture>("cose_16"),Cache::GetRessources<sf::Texture>("cose_17"),Cache::GetRessources<sf::Texture>("cose_18") };
	m_arrayTexture.at(2) = { Cache::GetRessources<sf::Texture>("cose_19"),Cache::GetRessources<sf::Texture>("cose_20"),Cache::GetRessources<sf::Texture>("cose_21") };
	m_arrayTexture.at(6) = { Cache::GetRessources<sf::Texture>("cose_22"),Cache::GetRessources<sf::Texture>("cose_23"),Cache::GetRessources<sf::Texture>("cose_24") };

	m_window.TerritoryConquestView();
	
	place.setTexture(Cache::GetRessources<sf::Texture>("place_joueur"));
	loterie.setTexture(Cache::GetRessources<sf::Texture>("loterie"));
	Tete.setTexture(Cache::GetRessources<sf::Texture>("tete_fin_mini_jeu"));
	perso_colo.setTexture(Cache::GetRessources<sf::Texture>("perso_colo"));
	Ecran_Victoire.setTexture(Cache::GetRessources<sf::Texture>("fenetre_mini_jeu2"));
	Ecran.setTexture(Cache::GetRessources<sf::Texture>("fond_timer"));
	Lueur.setTexture(Cache::GetRessources<sf::Texture>("LueurBonus"));

	Lueur.setPosition(1160, 590);

	font2.loadFromFile("../Ressources/Linebeam.ttf");

	Tclassement.setFont(font);
	Tclassement.setCharacterSize(40);
	Tclassement.setFillColor(sf::Color::White);

	Tclassement.setString(text_class);
	Tclassement.setPosition(sf::Vector2f(1182.f, 300.f));

	place.setPosition(sf::Vector2f(1130.f, 250.f));
	Ecran_Victoire.setPosition(sf::Vector2f(0.f, 0));
	loterie.setPosition(sf::Vector2f(1100.f, 600.f));
	Tete.setPosition(sf::Vector2f(1350.f, 240.f));
	perso_colo.setPosition(sf::Vector2f(1433.f, 327.f));

	anim2 = Animator(sf::IntRect(0, 0, 378, 378), 26, 0.1f, Lueur.getGlobalBounds().height, false);

	if (m_mgr.Network() != nullptr) {
		m_joueur.SetColor(m_mgr.Network()->youInfos().color);
	}
}

//La collision du démon
bool TerritoryConquest::Collision(TC_Joueur* joueur)
{
	if (m_grid.getBounds().left + m_grid.getBounds().width >= joueur->GetSprite().getGlobalBounds().left
		&& m_grid.getBounds().left <= joueur->GetSprite().getGlobalBounds().left + joueur->GetSprite().getGlobalBounds().width
		&& m_grid.getBounds().top + m_grid.getBounds().height >= joueur->GetSprite().getGlobalBounds().top
		&& m_grid.getBounds().top <= joueur->GetSprite().getGlobalBounds().top + joueur->GetSprite().getGlobalBounds().height)
		return true;
	return false;
}

void TerritoryConquest::AssigningColor(TC_Joueur* joueur, const float& dt)
{
	for (auto& it : m_cases.GetVectorOfCases())
	{
		if (it.GetTextureIndex() == 0)
		{
			if(it.GetRect().left < 500)
			{
				m_timer_anim += dt;
				if (m_timer_anim > 0.1f) {
					it.GetRect().left += it.GetRect().width;
					m_timer_anim = 0.f;
				}
				it.GetSprite().setTextureRect(it.GetRect());
			}

		}
		else
		{
			if (it.GetRect().left < 400)
			{
				m_timer_anim_2 += dt;
				if (m_timer_anim_2 > 0.1f) {
					it.GetRect().left += it.GetRect().width;
					m_timer_anim_2 = 0.f;
				}
				it.GetSprite().setTextureRect(it.GetRect());
			}

		}
	}

	int RNG_texture = random::RandomInt(min, max);

	if (joueur->getcolor() == Joueur::Couleur::One)
	{
		if (Collision(joueur)) {
			m_cases.AddCases(Cases(m_arrayTexture.at(0).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 1, RNG_texture));

		}
	}
	else if (joueur->getcolor() == Joueur::Couleur::Two)
	{
		if (Collision(joueur))
		{
			m_cases.AddCases(Cases(m_arrayTexture.at(1).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 2, RNG_texture));

		}
	}
	else if (joueur->getcolor() == Joueur::Couleur::Three)
	{
		if (Collision(joueur))
		{ 
			m_cases.AddCases(Cases(m_arrayTexture.at(2).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 3, RNG_texture));

		}
	}
	else if (joueur->getcolor() == Joueur::Couleur::Four)
	{
		if (Collision(joueur))
		{ 
			m_cases.AddCases(Cases(m_arrayTexture.at(3).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 4, RNG_texture));

		}
	}
	else if (joueur->getcolor() == Joueur::Couleur::Six)
	{
		if (Collision(joueur))
		{ 
			m_cases.AddCases(Cases(m_arrayTexture.at(4).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 6, RNG_texture));

		}
	}
	else if (joueur->getcolor() == Joueur::Couleur::Height)
	{
		if (Collision(joueur))
		{ 
			m_cases.AddCases(Cases(m_arrayTexture.at(5).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 8, RNG_texture));

		}
	}
	else if (joueur->getcolor() == Joueur::Couleur::Five)
	{
		if (Collision(joueur))
		{ 
			m_cases.AddCases(Cases(m_arrayTexture.at(6).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 5, RNG_texture));

		}
	}
	else if (joueur->getcolor() == Joueur::Couleur::Seven)
	{
		if (Collision(joueur))
		{
			m_cases.AddCases(Cases(m_arrayTexture.at(7).at(RNG_texture),
				sf::Vector2f((static_cast<sf::Vector2i>(joueur->GetPos()) / SizeCase) * SizeCase), { 0,0,100,100 }, 7, RNG_texture));

		}
	}
}


void TerritoryConquest::scores_result(TC_Joueur* joueur)
{
	joueur->score = 0;

	std::for_each(std::begin(m_cases.GetVectorOfCases()), std::end(m_cases.GetVectorOfCases()), [&joueur](std::vector<Cases>::iterator::value_type it) {
		if (it.GetId() == joueur->GetID())
			joueur->score++;
		});
}

//StreamSkill
sf::Text TerritoryConquest::printTimer()
{
	std::ostringstream sstr;
	sstr << std::setw(2) << std::setfill('0') << static_cast<int>(timer);

	sf::Text text;
	text.setString(sstr.str());
	text.setFont(font2);
	text.setCharacterSize(80);



	if (timer < 10)
	{
		text.setFillColor(sf::Color::Red);
		Ecran.setColor(sf::Color(253, 58, 58));
	}
	else
	{
		text.setFillColor(sf::Color::White);
	}
	Ecran.setPosition(sf::Vector2f(m_window.getTCView().getCenter().x - 50, m_window.getTCView().getCenter().y - 540));
	text.setPosition({ m_window.getTCView().getCenter().x - 20, m_window.getTCView().getCenter().y - 510 });

	return text;
}

void TerritoryConquest::RunningTimer(const float& dt)
{
	timer -= dt;
	if (timer < 1.f)
		timer = 0.f;
}

void TerritoryConquest::processEvents(const sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::KeyPressed:
		switch (e.key.code)
		{
		case sf::Keyboard::Key::Escape:
			m_mgr.SoftGoBackTransition<Transition<TerritoryConquest>>(m_mgr, m_window, m_font, true);
			//m_mgr.goBackState();
			break;
		}
		[[fallthrough]];
	default:
		break;
	}
}

void TerritoryConquest::update(const float& dt)
{
	if (m_musicTC.getStatus() != sf::Sound::Status::Playing)
	{
		Game::m_gameMusic.stop();
		m_musicTC.play();
	}

	m_musicTC.setVolume(Options::volumeSound);

	Gamepads g;

	if (m_window.hasFocus())
	{
		if (g.on_pressed(0, Xbox::Button::Select))
			m_mgr.AddState(FSM_Manager::create<MenuIG>(m_mgr, m_window, m_font, true));
	}

	switch (m_stateTC)
	{
	case State_TC::Expli:
	{
		timer_expli -= dt;
		if (timer_expli <= 0.f) {
			m_stateTC = State_TC::Game;
			timer_expli = 10.f;
		}
		break;
	}
	case State_TC::Game:
	{
		scores_result(&m_joueur);

		std::for_each(std::begin(m_joueurs), std::end(m_joueurs), [&dt, this](const auto& j) {
			j.second->AnimUpdate(dt);
			});

		if (m_window.hasFocus()) {
			m_joueur.update(dt);
			m_joueur.AnimUpdate(dt);
		}
		std::map<int, Joueur*> tmp;
		for (auto& [i, current_player] : m_joueurs) {
			tmp[i] = current_player;
		}

		m_window.getTCView().setCenter(std::clamp(m_joueur.GetPos().x, m_window.getTCView().getSize().x / 2.f, m_arene.getGlobalBounds().width - m_window.getTCView().getSize().x / 2.f),
			std::clamp(m_joueur.GetPos().y, m_window.getTCView().getSize().y / 2.f, m_arene.getGlobalBounds().height - m_window.getTCView().getSize().y / 2.f));

		AssigningColor(&m_joueur, dt);
		std::for_each(std::begin(m_joueurs), std::end(m_joueurs), [&dt, this](const auto& j) {
			AssigningColor(j.second, dt);
			});

		RunningTimer(dt);

		if (m_mgr.Network() != nullptr) {
			m_mgr.Network()->updateInfos(&m_joueur);
			m_mgr.Network()->processEvents(m_joueurs);
		}

		if (timer <= 0.f) {
			Set_Classement();
			if (m_joueur.Get_Classement() < 2)
			{
				bonuswin = Bonus(sf::Vector2f(1340, 770));
			}
			m_stateTC = State_TC::Win;
		}
		break;
	}
	case State_TC::Win:
		anim2.Animation(Lueur, dt);
		Victoire(dt);
		break;
	}
}

void TerritoryConquest::draw()
{
	switch (m_stateTC)
	{
	case State_TC::Expli: 
	{
		m_window.draw(m_arene);
		m_window.draw(m_expli);
		break;
	}
	case State_TC::Game:
	{
		m_window.setView(m_window.getTCView());

		m_window.draw(m_grid);
		m_window.draw(m_arene);
		m_cases.draw(m_window.getRenderWindow(), sf::BlendMode{});


		m_joueur.Display(m_window);
		std::for_each(std::begin(m_joueurs), std::end(m_joueurs), [this](const auto& j) { 
			j.second->Display(m_window); 
			});


		m_window.draw(Ecran);
		m_window.getRenderWindow().draw(printTimer());

		m_window.setDefaultView();


		hud_others(&m_joueur);
		for (auto& [it, current] : m_joueurs) {
			hud_others(current);
		}
		break;
	}
	case State_TC::Win:
	{
		m_window.draw(m_arene);
		m_window.setView(m_window.getDefaultView());
		m_window.draw(Ecran_Victoire);
		m_window.draw(place);
		m_window.draw(loterie);
		if (m_joueur.Get_Classement() < 2)
		{
			m_window.draw(Lueur);
			bonuswin.Display(m_window);
		}
		for (auto& [id, pl] : m_joueurs) {
			pl->Display_Victoire(m_window);
		}
		m_window.draw(Tete);
		m_joueur.Display_Victoire(m_window);
		text_class = std::to_string(m_joueur.Get_Classement());
		Tclassement.setString(text_class);
		m_window.draw(Tclassement);
		break;
	}
	}
}

void TerritoryConquest::hud_others(TC_Joueur* joueur)
{
	switch (joueur->GetID())
	{
	case 1:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score1"));
		posHUD = sf::Vector2f(370, 0);
		break;
	case 2:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score2"));
		posHUD = sf::Vector2f(1237, 0);
		break;
	case 3:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score3"));
		posHUD = sf::Vector2f(1587, 0);
		break;
	case 4:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score4"));
		posHUD = sf::Vector2f(20, 880);
		break;
	case 5:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score5"));
		posHUD = sf::Vector2f(370, 880);
		break;
	case 6:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score6"));
		posHUD = sf::Vector2f(1237, 880);
		break;
	case 7:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score7"));
		posHUD = sf::Vector2f(1587, 880);
		break;
	case 8:
		HUD.setTexture(Cache::GetRessources<sf::Texture>("sprite_hud_groupe_score8"));
		break;
	}

	HUD.setPosition(posHUD);
	m_window.draw(HUD);
	ScoreText = func::CreateText(std::to_string(joueur->score), font2, 30, { 60.f + posHUD.x, 65.f + posHUD.y }, sf::Color::White);
	m_window.draw(ScoreText);
}

void TerritoryConquest::Victoire(const float& dt)
{

	timer_expli -= dt;

	if (timer_expli <= 0.f)
	{
		if (m_joueur.Get_Classement() < 3)
		{
			m_mgr.Network()->setWinBonus(bonuswin.GetType());
		}
		else
		{
			m_mgr.Network()->setWinBonus(Bonus::Type::None);
		}

		m_mgr.SoftGoBackTransition<Transition<TerritoryConquest>>(m_mgr, m_window, m_font, true);
		//m_mgr.goBackState();
	}

}

void TerritoryConquest::Set_Classement()
{

	for (auto& [id, pl] : m_joueurs) {

		tabscore.push_back(pl->score);
	}

	tabscore.push_back(m_joueur.score);

	std::sort(tabscore.begin(), tabscore.end(), [](int a, int b) {
		return a > b;
		});

	for (int i = 0; i < tabscore.size(); i++)
	{
		if (m_joueur.score == tabscore[i])
		{
			m_joueur.Set_Classement(i + 1);

		}
	}

	for (auto& [id, pl] : m_joueurs) {

		for (int i = 0; i < tabscore.size(); i++)
		{
			if (pl->score == tabscore[i])
			{
				pl->Set_Classement(i + 1);
			}
		}
	}

	for (auto& [id, pl] : m_joueurs)
	{
		for (auto& [ido, plo] : m_joueurs)
		{

			if (plo->Get_Classement() == m_joueur.Get_Classement())
			{
				if (plo->GetID() > m_joueur.GetID())
				{
					plo->Set_Classement(plo->Get_Classement() - 1);
				}
				else
				{
					m_joueur.Set_Classement(m_joueur.Get_Classement() - 1);
				}
			}
			if (id != ido)
			{
				if (pl->Get_Classement() == plo->Get_Classement())
				{
					if (pl->GetID() > plo->GetID())
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

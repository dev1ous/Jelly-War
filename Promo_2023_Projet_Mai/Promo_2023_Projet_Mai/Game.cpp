#include "Game.h"
#include "Cache.h"
#include "Functions.h"
#include "Overload.h"
#include "Gamepad.h"
#include "Battle_Royal.h"
#include "Auto_tamponneuse.h"
#include "TerritoryConquest.h"
#include "Menu.h"
#include "MenuIG.h"
#include "ConnectionScreen.h"
#include "Options.h"
#include "Cinematiques.h"
#include "Transition.h"

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

Game::Game(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change) : FSM{ mgr,window,font,change }, m_miniJeuxGames(nullptr, sf::RectangleShape())
{

	m_gameMusic.openFromFile("../Ressources/Sons/MainGameJW.wav");
	m_gameMusic.setVolume(Options::volumeSound);
	m_gameMusic.setLoop(true);
	m_gameMusic.play();
	Menu::m_mainMusic.stop();

	m_window.MovingView();
	m_fsmG.init();

	m_fond.setTexture(Cache::GetRessources<sf::Texture>("map_fond"), true);
	m_Goal.setTexture(Cache::GetRessources<sf::Texture>("BUT_DU_JEU"), true);
	m_A_button.setTexture(Cache::GetRessources<sf::Texture>("petita"), true);
	m_A_button.setTextureRect(sf::IntRect(0, 0, 56, 57));
	m_A_button.setOrigin(28, 28);
	m_BonusExplication.setTexture(Cache::GetRessources<sf::Texture>("Desc_Anti_Check"), true);
	m_BonusExplication.setPosition(0, 175);

	if (m_mgr.Network() != nullptr) {
		m_mgr.Network()->updateInfos(m_map);
		m_mgr.Network()->processEvents(m_map);
	}

	if (m_mgr.Network()->type() == "Host") {
		BonusMap.Apparition(Drawable, m_mgr.Network());
	}

	m_map.ResetBouton();

	Drawable.emplace_back(std::make_pair(true, &player->GetSprite()));
	Assets.AddInDrawable(Drawable);

	if (m_mgr.Network() != nullptr) {
		switch (m_mgr.Network()->youInfos().color)
		{
		case Joueur::Couleur::One:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(-150.f, -150.f)));	break;
		case Joueur::Couleur::Two:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(0.f, -150.f)));	break;
		case Joueur::Couleur::Three:	player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(150.f, -150.f)));	break;
		case Joueur::Couleur::Four:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(150.f, 0.f)));		break;
		case Joueur::Couleur::Five:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(150.f, 150.f)));	break;
		case Joueur::Couleur::Six:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(0.f, 150.f)));		break;
		case Joueur::Couleur::Seven:	player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(-150.f, 150.f)));	break;
		case Joueur::Couleur::Height:	player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(-150.f, 0.f)));	break;
		default: break;
		}
	}

	Minimapfond.setTexture(Cache::GetRessources<sf::Texture>("carte 280"));
	MinimapJoueur.setTexture(Cache::GetRessources<sf::Texture>("joueur_minimap"));
	MinimapJoueur.setOrigin(MinimapJoueur.getGlobalBounds().width / 2, MinimapJoueur.getGlobalBounds().height / 2);
	MinimapOthers.setTexture(Cache::GetRessources<sf::Texture>("Others_minimap"));
	MinimapOthers.setOrigin(MinimapOthers.getGlobalBounds().width / 2, MinimapOthers.getGlobalBounds().height / 2);
	MinimapBouton.setTexture(Cache::GetRessources<sf::Texture>("bouton_mini_map"));
	MinimapBouton.setOrigin(MinimapBouton.getGlobalBounds().width / 2, MinimapBouton.getGlobalBounds().height / 2);
	MinimapBouton.setPosition(m_map.BoutonGame.sprite.getPosition() / (8000.f / 280.f));

	Minimap.create(280, 280);

	// preloading
	Cache::GetRessources<sf::Texture>("Desc_contre_tacle");
	Cache::GetRessources<sf::Texture>("Desc_Anti_Check");
	Cache::GetRessources<sf::Texture>("Desc_Ralentissement");
	Cache::GetRessources<sf::Texture>("Desc_Axe_inverse");
	Cache::GetRessources<sf::Texture>("Desc_Teleportation");
	Cache::GetRessources<sf::Texture>("Desc_machine_boost");
	Cache::GetRessources<sf::Texture>("Desc_piratage");
	Cache::GetRessources<sf::Texture>("Desc_fausse_ressource");
	Cache::GetRessources<sf::Texture>("Desc_faux_bonus");
}

void Game::win()
{
	m_BaseState = FSM_Manager::create<Cinematique<ConnectionScreen>>(m_mgr, m_window, m_font, true, "VICTOIRE");
}

void Game::loose()
{
	m_BaseState = FSM_Manager::create<Cinematique<ConnectionScreen>>(m_mgr, m_window, m_font, true, "DEFAITE");
}

void Game::Resume()
{
	if (m_mgr.Network() != nullptr && (m_mgr.Network()->getStyle() == Network::NetworkStyle::AT || m_mgr.Network()->getStyle() == Network::NetworkStyle::TC || m_mgr.Network()->getStyle() == Network::NetworkStyle::BR)) {
		if (m_mgr.Network()->type() == "Host") {
			BonusMap.Apparition(Drawable, m_mgr.Network());
		}

		m_map.ResetBouton();

		switch (m_mgr.Network()->youInfos().color)
		{
		case Joueur::Couleur::One:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(-150.f, -150.f)));	break;
		case Joueur::Couleur::Two:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(0.f, -150.f)));	break;
		case Joueur::Couleur::Three:	player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(150.f, -150.f)));	break;
		case Joueur::Couleur::Four:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(150.f, 0.f)));		break;
		case Joueur::Couleur::Five:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(150.f, 150.f)));	break;
		case Joueur::Couleur::Six:		player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(0.f, 150.f)));		break;
		case Joueur::Couleur::Seven:	player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(-150.f, 150.f)));	break;
		case Joueur::Couleur::Height:	player->SetPos(sf::Vector2f(m_map.BoutonGame.sprite.getPosition() + sf::Vector2f(-150.f, 0.f)));	break;
		default: break;
		}
	}

	m_fsmG.changeState<std::monostate>();
}

void Game::processEvents(const sf::Event& e)
{
	m_fsmG.handleEvents(e);

	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Key::Escape) {
			m_BaseState = FSM_Manager::create<Menu>(m_mgr, m_window, m_font, true);
		}
	}
}

void Game::update(const float& dt)
{
	TerritoryConquest::m_musicTC.stop();
	Battle_Royal::m_musicBR.stop();
	Auto_tamponneuse::m_musicAT.stop();

	m_gameMusic.setVolume(Options::volumeSound);

	if (m_gameMusic.getStatus() != sf::Music::Playing) {
		m_gameMusic.play();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace) ||
		player->GetEtourdit() || player->GetTp())
		m_fsmG.changeState<std::monostate>();

	if (player->GetUseBonus() && player->GetFirstBonus().GetType() == Bonus::Type::Piratage) {
		m_fsmG.changeState<PieceManager>(2);
		player->SetUseBonus(false);
		player->DeleteBonus();
	}

	if (player->GetUseBonus() && player->GetFirstBonus().GetType() == Bonus::Type::LeurreZone) {

		if (player->GetScale().x == -1.f) {
			m_map.AddtrapsRessource(player->GetPos() - sf::Vector2f(200, 0), Drawable, player);
		}
		if (player->GetScale().x == 1.f) {
			m_map.AddtrapsRessource(player->GetPos() + sf::Vector2f(100, 0), Drawable, player);
		}

		player->DeleteBonus();
		player->SetUseBonus(false);
	}

	for (auto& [i, current] : players) {
		if (current->GetUseBonus() && current->GetFirstBonus().GetType() == Bonus::Type::LeurreZone) {
			if (current->GetScale().x == -1.f) {
				m_map.AddtrapsRessource(current->GetPos() - sf::Vector2f(200, 0), Drawable, current);
			}
			if (current->GetScale().x == 1.f) {
				m_map.AddtrapsRessource(current->GetPos() + sf::Vector2f(100, 0), Drawable, current);
			}

			current->DeleteBonus();
			current->SetUseBonus(false);
		}
	}

	if (m_fsmG.GetVariantState().index() == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad0)) {
			m_fsmG.changeState<SkillCheckManager>();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad1)) {
			m_fsmG.changeState<PieceManager>(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2)) {
			m_fsmG.changeState<Combinaison>();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad3)) {
			m_fsmG.changeState<Peche>();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4)) {
			m_fsmG.changeState<Torche>();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad5)) {
			m_fsmG.changeState<Puzzle>();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6)) {
			m_fsmG.changeState<Memory>();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
			m_mgr.SoftAddTransition<Transition<Battle_Royal>>(m_mgr, m_window, m_font, true);
			//m_mgr.AddState(FSM_Manager::create<Battle_Royal>(m_mgr, m_window, m_font, true));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8)) {
			m_mgr.SoftAddTransition<Transition<Auto_tamponneuse>>(m_mgr, m_window, m_font, true);
			//m_mgr.AddState(FSM_Manager::create<Auto_tamponneuse>(m_mgr, m_window, m_font, true));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
			m_mgr.SoftAddTransition<Transition<TerritoryConquest>>(m_mgr, m_window, m_font, true);
			//m_mgr.AddState(FSM_Manager::create<TerritoryConquest>(m_mgr, m_window, m_font, true));
		}
	}

	for (Map::Nodes& n : m_map.getNodes()) {
		if (n.owner == player && n.type != 4) {
			if (n.Bonus) {
				player->addRessource(n.type, 1.f * dt);
			}
			else {
				player->addRessource(n.type, 0.5f * dt);
			}
		}
	}

	std::map<int, Joueur*> tmp;
	tmp[0] = player;
	for (auto& [i, current_player] : players) {
		tmp[i] = current_player;
	}

	for (auto& [i, current_player] : players) {
		current_player->Interaction(tmp);
		current_player->InteractionBonus(BonusMap.GetBonusMap(), Drawable, m_BonusExplication, m_BonusExplication_timer, false);
	}

	player->Interaction(tmp);

	if (player->GetTp()) {
		sf::Vector2f Center = sf::Vector2f(
			std::clamp<float>(player->GetPos().x, m_window.getMovingView().getSize().x / 2.f,
				m_fond.getGlobalBounds().width - m_window.getMovingView().getSize().x / 2.f),
			std::clamp<float>(player->GetPos().y, m_window.getMovingView().getSize().y / 2.f,
				m_fond.getGlobalBounds().height - m_window.getMovingView().getSize().y / 2.f)
		);

		m_window.getMovingView().setCenter(Center);
	}

	TextureMinimap();
	m_hud.SetTextureMinimap(&Minimap.getTexture());

	BonusMap.Update(dt);


	if (m_fsmG.GetVariantState().index() == 0) {
		Gamepads g;
		player->InteractionBonus(BonusMap.GetBonusMap(), Drawable, m_BonusExplication, m_BonusExplication_timer);

		if (m_window.hasFocus()) {

			if (g.on_pressed(0, Xbox::Button::Select))
				m_mgr.AddState(FSM_Manager::create<MenuIG>(m_mgr, m_window, m_font, true));

			if (!player->GetEtourdit()) {
				player->Controle(dt, m_mgr.Network(), BonusMap, Drawable);
			}
		}

		player->Update(dt, m_map.getImage(), m_map);

		if (m_window.hasFocus()) {
			lookingAt = player->LookingAt(m_map, dt);
			if (g.on_pressed(0, Xbox::Button::A)) {
				if (lookingAt != nullptr && lookingAt->owner != player) {
					if (lookingAt->owner == nullptr) {
						if (lookingAt->type == 0)
							m_fsmG.changeState<Combinaison>();
						if (lookingAt->type == 1)
							m_fsmG.changeState<SkillCheckManager>();
						if (lookingAt->type == 2)
							m_fsmG.changeState<Peche>();
					}
					else {
						switch (random::RandomInt(0, 2))
						{
						case 0:
							m_fsmG.changeState<Torche>();
							break;
						case 1:
							m_fsmG.changeState<Memory>();
							break;
						case 2:
							m_fsmG.changeState<Puzzle>();
							break;
						}
					}
				}
			}
		}
	}
	else {
		if (m_fsmG.won())
		{
			if (m_fsmG.GetVariantState().index() == 2) {
				if (best == m_mgr.Network()->youInfos().id) {
					if (players.find(secondplayer) != players.end()) {
						int i = 0;
						for (auto& it : m_map.getNodes()) {
							if (it.owner == players[secondplayer]) {
								i++;
							}
						}
						if (i > 0) {
							int rand = random::RandomInt(1, i);

							int y = 0;
							for (auto& it : m_map.getNodes()) {
								if (it.owner == players[secondplayer]) {
									y++;
									if (i == y) {
										it.owner = player;
										if (m_mgr.Network() != nullptr) {
											m_mgr.Network()->updateInfos(&it);
										}
									}
								}
							}
						}
					}
				}
				else {
					if (players.find(best) != players.end()) {
						int i = 0;
						for (auto& it : m_map.getNodes()) {
							if (it.owner == players[best]) {
								i++;
							}
						}
						if (i > 0) {
							int rand = random::RandomInt(1, i);

							int y = 0;
							for (auto& it : m_map.getNodes()) {
								if (it.owner == players[best]) {
									y++;
									if (i == y) {
										it.owner = player;
										if (m_mgr.Network() != nullptr) {
											m_mgr.Network()->updateInfos(&it);
										}
									}
								}
							}
						}
					}
				}
			}
			else if (lookingAt != nullptr) {
				if (lookingAt->type == 4) {
					player->addRessource(0, -5.f);
					player->addRessource(1, -5.f);
					player->addRessource(2, -5.f);

					player->SetFeedback(Main_Joueur::Statut::Fausse_Ressources);
					m_mgr.Network()->updateInfosRemoveTraps(lookingAt->BasePos);
					m_map.RemoveTrapsRessources(lookingAt->BasePos, Drawable);
				}
				else {
					lookingAt->owner = player;
					if (m_mgr.Network() != nullptr) {
						m_mgr.Network()->updateInfos(lookingAt);
					}
				}
			}

			m_fsmG.changeState<std::monostate>();
		}
		else {
			if (m_window.hasFocus()) {
				m_fsmG.update(dt, m_window);
			}
		}
	}


	m_map.ReceiveBonus(player, players);

	sf::Vector2f PosCenter = player->GetPos() + player->GetSpeed() * 50.f;

	sf::Vector2f Center = sf::Vector2f(
		std::clamp<float>(PosCenter.x, m_window.getMovingView().getSize().x / 2.f,
			m_fond.getGlobalBounds().width - m_window.getMovingView().getSize().x / 2.f),
		std::clamp<float>(PosCenter.y, m_window.getMovingView().getSize().y / 2.f,
			m_fond.getGlobalBounds().height - m_window.getMovingView().getSize().y / 2.f)
	);

	m_window.getMovingView().setCenter(Center);

	m_map.UpdateBouton(dt, player, m_mgr.Network(), m_mgr, *this);
	m_map.Update(dt);
	Assets.Update(dt);
	player->Animation(dt);
	player->FeedBackAnim(dt);
	m_hud.Update(dt, m_map.BoutonGame);
	m_hud.SetCurrentPlayer(player->getcolor());

	for (auto& [i, current_player] : players) {
		current_player->FeedBackAnim(dt);
	}

	if (m_mgr.Network() != nullptr) {
		if (m_mgr.Network()->getStyle() == Network::NetworkStyle::AT || m_mgr.Network()->getStyle() == Network::NetworkStyle::BR || m_mgr.Network()->getStyle() == Network::NetworkStyle::TC) {
			if (m_mgr.Network()->youInfos().Bonus_to_win != Bonus::Type::None) {
				player->SetBonus(m_mgr.Network()->youInfos().Bonus_to_win);

				m_BonusExplication_timer = 0.f;

				switch (m_mgr.Network()->youInfos().Bonus_to_win)
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
		}

		m_mgr.Network()->updateInfos(player, m_map.BoutonGame.timer, m_map.BoutonGame.start);
		m_mgr.Network()->processEvents(players, m_map, m_map.BoutonGame, BonusMap, Drawable, m_mgr, *this);
		player->SetColor(m_mgr.Network()->youInfos().color);

		Classement();

		if (best == m_mgr.Network()->youInfos().id) {
			m_hud.SetFirstPlayer(player->getcolor());
		}
		else {
			m_hud.SetFirstPlayer(players[best]->getcolor());
		}
	}

	m_goal_timer += dt;
	m_BonusExplication_timer += dt;
}

void Game::draw()
{
	for (auto& [i, current_player] : players) {
		auto it = std::find(std::begin(Drawable), std::end(Drawable), std::make_pair(true, &current_player->GetSprite()));
		if (it == std::end(Drawable)) {
			Drawable.emplace_back(std::make_pair(true, &current_player->GetSprite()));
		}
	}

	Drawable.sort([](std::pair<bool, const sf::Sprite*> one, std::pair<bool, const sf::Sprite*> two) {
		return one.second->getPosition().y + one.second->getGlobalBounds().height - one.second->getOrigin().y <
			two.second->getPosition().y + two.second->getGlobalBounds().height - two.second->getOrigin().y; });

	m_window.setView(m_window.getMovingView());
	m_window.draw(m_fond);

	m_map.display(m_window);

	for (auto& sprite : Drawable) {
		m_window.getRenderWindow().draw(*sprite.second);

		if (sprite.second == &m_map.BoutonGame.sprite) {
			m_map.DisplayTimer(m_window, Cache::GetRessources<sf::Font>("Linebeam"));
		}

		for (auto& it : m_map.getNodes()) {
			if (sprite.second == &it.machine_sprite) {
				it.Display(m_window);
			}
		}

		if (sprite.second == &player->GetSprite()) {
			player->DisplayFeedback(m_window);
		}

		for (auto& [i, current_player] : players) {
			if (sprite.second == &current_player->GetSprite()) {
				current_player->DisplayFeedback(m_window);
			}
		}
	}

	if (auto node = player->LookingAt(m_map, 0.f); node != nullptr) {
		m_A_button.setPosition(node->Beam.getPosition() + sf::Vector2f(node->Beam.getGlobalBounds().width / 2.f, 150.f));
		m_window.draw(m_A_button);
	}

	m_window.setView(m_window.getDefaultView());

	if (m_fsmG.GetVariantState().index() == 0) {
		m_hud.Display(m_window);
		m_window.setView(m_window.getDefaultView());
	}

	if (m_BonusExplication_timer <= 10.f) {
		m_window.draw(m_BonusExplication);
	}
	if (m_goal_timer <= 10.f) {
		m_window.draw(m_Goal);
	}

	m_fsmG.draw(m_window, m_font);
}

void Game::TextureMinimap()
{
	MinimapJoueur.setPosition(player->GetPos() / (8000.f / 280.f));

	Minimap.clear(sf::Color::Transparent);

	Minimap.draw(Minimapfond);

	if (player->SeeOthers()) {
		for (auto& p : players) {
			MinimapOthers.setPosition(p.second->GetPos() / (8000.f / 280.f));
			Minimap.draw(MinimapOthers);
		}
	}

	Minimap.draw(MinimapJoueur);
	Minimap.draw(MinimapBouton);

	Minimap.display();
}

void Game::Classement()
{
	best = m_mgr.Network()->youInfos().id;
	secondplayer = m_mgr.Network()->youInfos().id;

	for (auto& [it, current] : players)
		current->restartClassement();

	player->restartClassement();

	for (auto& [it, current] : players) {

		if (m_mgr.Network()->youInfos().progress < current->getProgress()) {
			player->addclassement();
		}
		if (m_mgr.Network()->youInfos().progress >= current->getProgress()) {
			current->addclassement();
		}

		for (auto& [it2, current2] : players) {

			if (it != it2) {
				if (current2->getProgress() < current->getProgress()) {
					current2->addclassement();
				}
				if (current2->getProgress() == current->getProgress() &&
					current2->GetClassement() == current->GetClassement())
				{
					current2->addclassement();
				}
			}
		}
	}

	for (auto& [it, current] : players) {
		if (current->GetClassement() == 1) {
			best = it;
		}
		if (current->GetClassement() == 2) {
			secondplayer = it;
		}
	}
}
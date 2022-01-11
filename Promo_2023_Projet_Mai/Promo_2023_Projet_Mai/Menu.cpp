#include "Menu.h"
#include "Functions.h"
#include "Game.h"
#include "Options.h"
#include "Cache.h"
#include "Client.h"
#include "Host.h"
#include "ConnectionScreen.h"
#include "Gamepad.h"
#include "Transition.h"
#include "Auto_tamponneuse.h"
#include "Battle_Royal.h"
#include "TerritoryConquest.h"
#include <fstream>
#include "Cinematiques.h"
#include "File_Reader.h"

void Menu::SavePseudo()
{
	char* userpath = getenv("APPDATA");
	if (userpath == nullptr)
	{
		std::cout << "user path undefined";
		return;
	}
	std::string path(std::string(userpath) + "/Game Academy/Jelly War");

	std::replace(path.begin(), path.end(), '\\', '/');
	fs::create_directories(path);

	path += "/Settings.txt";

	File_Reader file(File_Reader::Read_And_Write);
	file.Bind(path);
	file["Pseudo"] << m_pseudonyme;
}

Menu::Menu(FSM_Manager& mgr, WindowManager& window, sf::Font& font,
	const bool change)
	: FSM{ mgr, window, font, change },
	menu_buttons{ nullptr, forms::rectangle({545, 120}, {400, 50}, sf::Color::White,sf::Color::Transparent, 0.f) },
	m_play{ forms::CreateSprite({650, 124 + 40}, Cache::GetRessources<sf::Texture>("jouer_E")) },
	m_join{ forms::CreateSprite({650, 282 + 40}, Cache::GetRessources<sf::Texture>("rejoindre_E")) },
	m_pseudo{ forms::CreateSprite({650, 440 + 40}, Cache::GetRessources<sf::Texture>("pseudo_E")) },
	m_options{ forms::CreateSprite({650 ,598 + 40}, Cache::GetRessources<sf::Texture>("options_E")) },
	m_credits{ forms::CreateSprite({650 ,756 + 40}, Cache::GetRessources<sf::Texture>("credits_E")) },
	m_quit{ forms::CreateSprite({650, 914 + 40},Cache::GetRessources<sf::Texture>("quitter_E")) },

	m_logo{ forms::CreateSprite({ 1090, 290}, Cache::GetRessources<sf::Texture>("Logo")) },
	m_Textip{ "", Cache::GetRessources<sf::Font>("Linebeam"), 50 },
	m_TextPseudo{ "", Cache::GetRessources<sf::Font>("Linebeam"), 50 },
	m_TextPseudo2{ "", Cache::GetRessources<sf::Font>("Linebeam"), 50 },
	m_BlackBackground{ {1920.f, 1080.f} },
	m_pad{ {{"1", Cache::GetRessources<sf::Font>("Linebeam"), 50},{"2", Cache::GetRessources<sf::Font>("Linebeam"), 50},
		{"3", Cache::GetRessources<sf::Font>("Linebeam"), 50},{"4", Cache::GetRessources<sf::Font>("Linebeam"), 50},
		{"5", Cache::GetRessources<sf::Font>("Linebeam"), 50},{"6", Cache::GetRessources<sf::Font>("Linebeam"), 50},
		{"7", Cache::GetRessources<sf::Font>("Linebeam"), 50},{"8", Cache::GetRessources<sf::Font>("Linebeam"), 50},
		{"9", Cache::GetRessources<sf::Font>("Linebeam"), 50},{"0", Cache::GetRessources<sf::Font>("Linebeam"), 50},
		{".", Cache::GetRessources<sf::Font>("Linebeam"), 50}} }
{
	m_logo.setScale(0.3f, 0.3f);

	m_mainMusic.openFromFile("../Ressources/Sons/MenuJW.wav");
	m_mainMusic.setLoop(true);
	m_mainMusic.setVolume(Options::volumeSound);
	m_mainMusic.play();
	Game::m_gameMusic.stop();

	m_pseudo.setOrigin(m_pseudo.getGlobalBounds().width / 2, m_pseudo.getGlobalBounds().height / 2);
	m_play.setOrigin(m_play.getGlobalBounds().width / 2, m_play.getGlobalBounds().height / 2);
	m_join.setOrigin(m_join.getGlobalBounds().width / 2, m_join.getGlobalBounds().height / 2);
	m_options.setOrigin(m_options.getGlobalBounds().width / 2, m_options.getGlobalBounds().height / 2);
	m_credits.setOrigin(m_credits.getGlobalBounds().width / 2, m_credits.getGlobalBounds().height / 2);
	m_quit.setOrigin(m_quit.getGlobalBounds().width / 2, m_quit.getGlobalBounds().height / 2);

	m_background.openFromFile("../Ressources/videos/Video_menu.mp4");
	m_BlackBackground.setFillColor(sf::Color(0, 0, 0, 175));
	m_IpBackground.setTexture(Cache::GetRessources<sf::Texture>("pop_up"));
	m_PseudoBackground.setTexture(Cache::GetRessources<sf::Texture>("pop_up_name"));
	m_IpBackground.setPosition(0.f, -1000.f);
	m_PseudoBackground.setPosition(0.f, -1000.f);
	m_SelectedNumber.setTexture(Cache::GetRessources<sf::Texture>("SelectionIp"));
	m_SelectedNumberFeedBack.setTexture(Cache::GetRessources<sf::Texture>("SelectionIpFeedback"));

	m_arrowDown.setTexture(Cache::GetRessources<sf::Texture>("fleche_pseudo"));
	m_arrowUp.setTexture(Cache::GetRessources<sf::Texture>("fleche_pseudo"));
	m_arrowDown.setOrigin(m_arrowDown.getGlobalBounds().width / 2.f, m_arrowDown.getGlobalBounds().height / 2.f);
	m_arrowUp.setOrigin(m_arrowUp.getGlobalBounds().width / 2.f, m_arrowUp.getGlobalBounds().height / 2.f);
	m_arrowUp.setRotation(180.f);


	menu_buttons.setTexture(Cache::GetRessources<sf::Texture>("sprite_bouton_1E")).setTextureState("sprite_bouton_1E", "sprite_bouton_1A", "sprite_bouton_1A").setOrigin().Resize();
	menu_buttons.CreateFunctionCall([this]
		{
			if (!m_pseudonyme.empty()) {
				m_mgr.SetNetworkType<Host>();
				m_mgr.Network()->setPseudo(m_pseudonyme);
				m_mgr.Network()->connect();
				m_mgr.Network()->run(0);
				m_mgr.SoftChangeTransition<Transition<ConnectionScreen>>(m_mgr, m_window, m_font, true);
				//m_BaseState = FSM_Manager::create<ConnectionScreen>(m_mgr, m_window, m_font, true);
			}
		}
	);

	Button& connect = menu_buttons.Add("networkID", forms::rectangle({ 545, 278 }, { 400,50 }, sf::Color::White, sf::Color::Transparent, 0.f));
	connect.setTexture(Cache::GetRessources<sf::Texture>("sprite_bouton_2E")).setTextureState("sprite_bouton_2E", "sprite_bouton_2A", "sprite_bouton_2A").setOrigin().Resize();
	connect.CreateFunctionCall([this]
		{
			if (!m_pseudonyme.empty()) {
				m_typing = true;
			}
		}
	);

	Button& Pseudo = menu_buttons.Add("PseudoID", forms::rectangle({ 545, 436 }, { 400,50 }, sf::Color::White, sf::Color::Transparent, 0.f));
	Pseudo.setTexture(Cache::GetRessources<sf::Texture>("sprite_bouton_4E")).setTextureState("sprite_bouton_4E", "sprite_bouton_4A", "sprite_bouton_4A").setOrigin().Resize();
	Pseudo.CreateFunctionCall([this]
		{
			m_pseudo_typing = true;
			cpseudo = 'a';
		}
	);

	Button& options = menu_buttons.Add("optionsID", forms::rectangle({ 545,594 }, { 400,50 }, sf::Color::White, sf::Color::Transparent, 0.f));
	options.setTexture(Cache::GetRessources<sf::Texture>("sprite_bouton_3E")).setTextureState("sprite_bouton_3E", "sprite_bouton_3A", "sprite_bouton_3A").setOrigin().Resize();
	options.CreateFunctionCall([this]
		{
			//m_BaseState = FSM_Manager::create<Options>(m_mgr, m_window, m_font, true);
			m_mgr.SoftChangeTransition<Transition<Options>>(m_mgr, m_window, m_font, true);
		}
	);

	Button& credits = menu_buttons.Add("creditsID", forms::rectangle({ 545,752 }, { 400,50 }, sf::Color::White, sf::Color::Transparent, 0.f));
	credits.setTexture(Cache::GetRessources<sf::Texture>("sprite_bouton_1E")).setTextureState("sprite_bouton_1E", "sprite_bouton_1A", "sprite_bouton_1A").setOrigin().Resize();
	credits.CreateFunctionCall([this]
		{
			m_mainMusic.setVolume(0.f);
			m_BaseState = FSM_Manager::create<Cinematique<Menu>>(m_mgr, m_window, m_font, true, "credits", true);
		}
	);

	Button& quit = menu_buttons.Add("quitterID", forms::rectangle({ 545,910 }, { 400,50 }, sf::Color::White, sf::Color::Transparent, 0.f));
	quit.setTexture(Cache::GetRessources<sf::Texture>("sprite_bouton_4E")).setTextureState("sprite_bouton_4E", "sprite_bouton_4A", "sprite_bouton_4A").setOrigin().Resize();
	quit.CreateFunctionCall([&window]
		{ window.close(); }
	);


	m_background.play();

	m_mgr.RemoveNetwork();

	char* userpath = getenv("APPDATA");
	if (userpath == nullptr)
	{
		std::cout << "user path undefined";
		return;
	}
	std::string path(std::string(userpath) + "/Game Academy/Jelly War/Settings.txt");

	std::replace(path.begin(), path.end(), '\\', '/');

	File_Reader file(File_Reader::Read_Only);
	file.Bind(path);
	if (file["Pseudo"].found()) {
		file["Pseudo"] >> m_pseudonyme;
	}
}

void Menu::processEvents(const sf::Event& e)
{
	/*if (Timer < 0 && !m_typing && !m_pseudo_typing)
		menu_buttons.processEvents(e);*/
}

void Menu::update(const float& dt)
{
	m_mainMusic.setVolume(Options::volumeSound);

	if (Timer >= 0)
		Timer -= dt;

	if (m_window.hasFocus()) {
		Gamepads g;

		if (!m_typing && !m_pseudo_typing) {
			if (g.on_pressed(0, Xbox::LeftJoystick_Down))
			{
				selected++;
				if (selected > 5) {
					selected = 0;
				}
			}
			if (g.on_pressed(0, Xbox::LeftJoystick_Up))
			{
				selected--;
				if (selected < 0) {
					selected = 5;
				}
			}

			menu_buttons.DesactivateHover();
			menu_buttons.get("networkID").DesactivateHover();
			menu_buttons.get("PseudoID").DesactivateHover();
			menu_buttons.get("optionsID").DesactivateHover();
			menu_buttons.get("creditsID").DesactivateHover();
			menu_buttons.get("quitterID").DesactivateHover();

			if (selected != 0)
				m_play.setTexture(Cache::GetRessources<sf::Texture>("jouer_E"));
			if (selected != 1)
				m_join.setTexture(Cache::GetRessources<sf::Texture>("rejoindre_E"));
			if (selected != 2)
				m_pseudo.setTexture(Cache::GetRessources<sf::Texture>("pseudo_E"));
			if (selected != 3)
				m_options.setTexture(Cache::GetRessources<sf::Texture>("options_E"));
			if (selected != 4)
				m_credits.setTexture(Cache::GetRessources<sf::Texture>("credits_E"));
			if (selected != 5)
				m_quit.setTexture(Cache::GetRessources<sf::Texture>("quitter_E"));

			if (selected == 0) {
				menu_buttons.ForceHover();
				m_play.setTexture(Cache::GetRessources<sf::Texture>("jouer_A"));
			}
			else if (selected == 1) {
				menu_buttons.get("networkID").ForceHover();
				m_join.setTexture(Cache::GetRessources<sf::Texture>("rejoindre_A"));
			}
			else if (selected == 2) {
				menu_buttons.get("PseudoID").ForceHover();
				m_pseudo.setTexture(Cache::GetRessources<sf::Texture>("pseudo_A"));
			}
			else if (selected == 3) {
				menu_buttons.get("optionsID").ForceHover();
				m_options.setTexture(Cache::GetRessources<sf::Texture>("options_A"));
			}
			else if (selected == 4) {
				menu_buttons.get("creditsID").ForceHover();
				m_credits.setTexture(Cache::GetRessources<sf::Texture>("credits_A"));
			}
			else if (selected == 5) {
				menu_buttons.get("quitterID").ForceHover();
				m_quit.setTexture(Cache::GetRessources<sf::Texture>("quitter_A"));
			}

			if (g.on_pressed(0, Xbox::A)) {
				switch (selected)
				{
				case 0: 
					menu_buttons.ForceActivation(); 
					break;
				case 1: 
					menu_buttons.get("networkID").ForceActivation();
					break;
				case 2:
					menu_buttons.get("PseudoID").ForceActivation();
					break;
				case 3:
					menu_buttons.get("optionsID").ForceActivation();
					break;
				case 4: 
					menu_buttons.get("creditsID").ForceActivation();
					break;
				case 5: 
					menu_buttons.get("quitterID").ForceActivation();
					break;

				default: break;
				}
			}


			m_IpBackground.setPosition(0.f, std::clamp<float>(m_IpBackground.getPosition().y - 600.f * dt, -1000.f, 0.f));
			m_PseudoBackground.setPosition(0.f, std::clamp<float>(m_PseudoBackground.getPosition().y - 600.f * dt, -1000.f, 0.f));
		}
		else if (m_typing) {
			m_IpBackground.setPosition(0.f, std::clamp<float>(m_IpBackground.getPosition().y + 600.f * dt, -1000.f, 0.f));

			if (g.on_pressed(0, Xbox::X)) {
				m_typing = false;
			}

			if (g.on_pressed(0, Xbox::A)) {
				m_ip.append(m_pad.at(m_ISelectedNumber).getString());
				m_SelectedNumberFeedBack.setPosition(m_pad.at(m_ISelectedNumber).getPosition() - sf::Vector2f(35, 20));
				m_SelectionFeedbackTimer = 0.25f;
			}

			if (g.on_pressed(0, Xbox::B)) {
				if (!m_ip.empty()) {
					m_ip.pop_back();
				}
			}

			if (g.on_pressed(0, Xbox::Start)) {
				m_mgr.SetNetworkType<Client>();
				m_mgr.Network()->connect(m_ip);
				if (m_mgr.Network()->isOpen()) {
					m_mgr.Network()->setPseudo(m_pseudonyme);
					m_mgr.Network()->run(0);
					m_mgr.SoftChangeTransition<Transition<ConnectionScreen>>(m_mgr, m_window, m_font, true);
					//m_BaseState = FSM_Manager::create<ConnectionScreen>(m_mgr, m_window, m_font, true);
				}
				// else don't find server
			}

			if (g.on_pressed(0, Xbox::LeftJoystick_Down)) {
				m_ISelectedNumber = std::clamp(m_ISelectedNumber + 3, 0, 10);
			}
			if (g.on_pressed(0, Xbox::LeftJoystick_Up)) {
				m_ISelectedNumber = std::clamp(m_ISelectedNumber - 3, 0, 10);
			}
			if (g.on_pressed(0, Xbox::LeftJoystick_Left)) {
				m_ISelectedNumber = std::clamp(m_ISelectedNumber - 1, 0, 10);
			}
			if (g.on_pressed(0, Xbox::LeftJoystick_Right)) {
				m_ISelectedNumber = std::clamp(m_ISelectedNumber + 1, 0, 10);
			}
		}
		else if (m_pseudo_typing) {
			m_PseudoBackground.setPosition(0.f, std::clamp<float>(m_PseudoBackground.getPosition().y + 600.f * dt, -1000.f, 0.f));

			if (g.on_pressed(0, Xbox::X)) {
				m_pseudo_typing = false;

				if (m_pseudonyme.empty()) {
					m_pseudonyme = "Player";
				}
				this->SavePseudo();
			}

			if (g.on_pressed(0, Xbox::A) && m_pseudonyme.size() < 10) {
				m_pseudonyme.push_back(cpseudo);
				cpseudo = 'a';
			}

			if (g.on_pressed(0, Xbox::Cross_Up) || g.on_pressed(0, Xbox::Cross_Down)) {
				if (cpseudo >= 'A' && cpseudo <= 'Z') {
					cpseudo += 32;
				}
				else {
					cpseudo -= 32;
				}
			}

			if (g.on_pressed(0, Xbox::B)) {
				if (!m_pseudonyme.empty()) {
					m_pseudonyme.pop_back();
					cpseudo = 'a';
				}
			}

			if (g.on_pressed(0, Xbox::Start)) {
				m_pseudo_typing = false;

				if (m_pseudonyme.empty()) {
					m_pseudonyme = "Player";
				}
				this->SavePseudo();
			}

			m_PseudoTimer += dt;
			if (g.is_pressed(0, Xbox::LeftJoystick_Down) && m_PseudoTimer >= 0.15) {
				if (cpseudo >= 'A' && cpseudo <= 'Z') {
					if (cpseudo < 'Z') {
						cpseudo++;
						m_PseudoTimer = 0.f;
					}
				}
				else {
					if (cpseudo < 'z') {
						cpseudo++;
						m_PseudoTimer = 0.f;
					}
				}
			}
			if (g.is_pressed(0, Xbox::LeftJoystick_Up) && m_PseudoTimer >= 0.15) {
				if (cpseudo >= 'A' && cpseudo <= 'Z') {
					if (cpseudo > 'A') {
						cpseudo--;
						m_PseudoTimer = 0.f;
					}
				}
				else {
					if (cpseudo > 'a') {
						cpseudo--;
						m_PseudoTimer = 0.f;
					}
				}
			}
		}
	}


	m_background.update();
	m_Textip.setPosition(m_IpBackground.getPosition() + sf::Vector2f(845, 250));
	m_TextPseudo.setPosition(m_PseudoBackground.getPosition() + sf::Vector2f(845, 500));
	m_TextPseudo2.setPosition(m_TextPseudo.getPosition() + sf::Vector2f(m_TextPseudo.getLocalBounds().width, 0));
	m_arrowUp.setPosition(m_TextPseudo2.getPosition() + sf::Vector2f(20, -10));
	m_arrowDown.setPosition(m_TextPseudo2.getPosition() + sf::Vector2f(20, 85));



	m_pad.at(0).setPosition(m_IpBackground.getPosition() + sf::Vector2f(864 - 23, 450));
	m_pad.at(1).setPosition(m_IpBackground.getPosition() + sf::Vector2f(971 - 23, 450));
	m_pad.at(2).setPosition(m_IpBackground.getPosition() + sf::Vector2f(1078 - 23, 450));

	m_pad.at(3).setPosition(m_IpBackground.getPosition() + sf::Vector2f(864 - 23, 559));
	m_pad.at(4).setPosition(m_IpBackground.getPosition() + sf::Vector2f(971 - 23, 559));
	m_pad.at(5).setPosition(m_IpBackground.getPosition() + sf::Vector2f(1078 - 23, 559));

	m_pad.at(6).setPosition(m_IpBackground.getPosition() + sf::Vector2f(864 - 23, 665.5f));
	m_pad.at(7).setPosition(m_IpBackground.getPosition() + sf::Vector2f(971 - 23, 665.5f));
	m_pad.at(8).setPosition(m_IpBackground.getPosition() + sf::Vector2f(1078 - 23, 665.5f));

	m_pad.at(9).setPosition(m_IpBackground.getPosition() + sf::Vector2f(864 - 23, 774.5f));
	m_pad.at(10).setPosition(m_IpBackground.getPosition() + sf::Vector2f(1078 - 23, 774.5f));

	if (lerpTimer.first) {
		m_TextPseudo2.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(std::lerp(0, 255, lerpTimer.second += dt * 2))));
	}
	else {
		m_TextPseudo2.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(std::lerp(0, 255, lerpTimer.second -= dt * 2))));
	}

	if (lerpTimer.first && lerpTimer.second >= 1.f) {
		lerpTimer.first = false;
	}
	else if (!lerpTimer.first && lerpTimer.second <= 0.f) {
		lerpTimer.first = true;
	}

	m_Textip.setString(m_ip);
	m_TextPseudo.setString(m_pseudonyme);
	m_TextPseudo2.setString(cpseudo);
	m_SelectedNumber.setPosition(m_pad.at(m_ISelectedNumber).getPosition() - sf::Vector2f(35, 20));

	if (m_background.getStatus() != sfe::Status::Playing) {
		m_background.play();
	}

	m_SelectionFeedbackTimer -= dt;
}

void Menu::draw()
{
	m_window.draw(m_background);
	menu_buttons.draw(m_window.getRenderWindow());
	m_window.draw(m_logo);
	m_window.draw(m_pseudo);
	m_window.draw(m_play);
	m_window.draw(m_join);
	m_window.draw(m_options);
	m_window.draw(m_credits);
	m_window.draw(m_quit);

	if (m_IpBackground.getPosition().y > -1000.f || m_PseudoBackground.getPosition().y > -1000.f) {
		m_window.draw(m_BlackBackground);
	}

	m_window.draw(m_IpBackground);
	m_window.draw(m_PseudoBackground);
	m_window.draw(m_Textip);
	m_window.draw(m_TextPseudo);
	if (m_pseudonyme.size() < 10) {
		m_window.draw(m_TextPseudo2);
		m_window.draw(m_arrowUp);
		m_window.draw(m_arrowDown);
	}

	m_window.draw(m_SelectedNumber);

	if (m_SelectionFeedbackTimer > 0) {
		m_window.draw(m_SelectedNumberFeedBack);
	}

	ShortDraw::Span(std::span(m_pad.data(), m_pad.size()), m_window.getRenderWindow());
}

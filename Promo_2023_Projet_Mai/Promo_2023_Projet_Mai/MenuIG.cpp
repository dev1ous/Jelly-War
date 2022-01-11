#include "MenuIG.h"
#include "Functions.h"
#include "Cache.h"
#include "Gamepad.h"
#include "Options.h"
#include "Menu.h"
#include "Game.h"
#include "TerritoryConquest.h"
#include "Auto_tamponneuse.h"
#include "Battle_Royal.h"
#include "File_Reader.h"
#include "Transition.h"

MenuIG::MenuIG(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change) :FSM{ mgr,window,font,change }, m_optionsButton{ nullptr, sf::RectangleShape() },
m_ecranO{ forms::CreateSprite({ 0,0 }, Cache::GetRessources<sf::Texture>("paneau1(1920X1080)")) },
m_sprite{ forms::CreateSprite({800,360},Cache::GetRessources<sf::Texture>("barre012")) },
m_volume{ forms::CreateSprite({ (m_sprite.getPosition().x + 5) + (m_sprite.getGlobalBounds().width - 15) * (Options::volumeSound / MAX_VOLUME) - m_volume.getGlobalBounds().width / 2.f,m_sprite.getPosition().y - 60 }, Cache::GetRessources<sf::Texture>("curseur_musique")) },
m_sprite2{ forms::CreateSprite({800,500}, Cache::GetRessources<sf::Texture>("barre_pleine2")) },
m_volume2{ forms::CreateSprite({ (m_sprite2.getPosition().x + 5) + (m_sprite2.getGlobalBounds().width - 15) * (Options::volumeBruitages / Max_volume) - m_volume2.getGlobalBounds().width / 2.f,m_sprite2.getPosition().y - 60 }, Cache::GetRessources<sf::Texture>("curseur_musique")) },
m_VSyncText{ forms::CreateSprite({550,780},Cache::GetRessources<sf::Texture>("VSyncCurrent")) },
m_volumeTex{ forms::CreateSprite({550,360},Cache::GetRessources<sf::Texture>("VolumeCurrent")) },
m_volumeTex2{ forms::CreateSprite({550,500}, Cache::GetRessources<sf::Texture>("SFXCurrent")) },
m_windowedText{ forms::CreateSprite({550,640}, Cache::GetRessources<sf::Texture>("pleinEcranCurrent")) },
m_indicateur{ forms::CreateSprite({1150,750},Cache::GetRessources<sf::Texture>("panneau_fond_selection_slimes(259X99)")) },
m_indicateur2{ forms::CreateSprite({1150,600},Cache::GetRessources<sf::Texture>("panneau_fond_selection_slimes(259X99)")) },
current_bar{ forms::CreateSprite({0,0},Cache::GetRessources<sf::Texture>("selection_panneau(1105X100)")) },
retour_menu{ forms::CreateSprite({1758,0},Cache::GetRessources<sf::Texture>("retour_au_menu (199X201)")) },
retour_jeu{ forms::CreateSprite({0,0},Cache::GetRessources<sf::Texture>("retour_au_jeu(199X201)")) }
{
	Game::m_gameMusic.play();

	Button& b1 = m_optionsButton.Add("SoundButton", forms::CreateSprite({ 345,274 }, Cache::GetRessources<sf::Texture>("selection_eteint")));
	b1.setTexture(Cache::GetRessources<sf::Texture>("selection_eteint")).setTextureState("selection_eteint", "selection_allume", "selection_allume");
	b1.CreateFunctionCall([this] {
		m_status = Status::Sound;
		});

	Button& b2 = m_optionsButton.Add("BruitagesButton", forms::CreateSprite({ 345,413 }, Cache::GetRessources<sf::Texture>("selection_eteint")));
	b2.setTexture(Cache::GetRessources<sf::Texture>("selection_eteint")).setTextureState("selection_eteint", "selection_allume", "selection_allume");
	b2.CreateFunctionCall([this] {
		m_status = Status::Bruitages;
		});

	Button& b3 = m_optionsButton.Add("FenetresButton", forms::CreateSprite({ 345,552 }, Cache::GetRessources<sf::Texture>("selection_eteint")));
	b3.setTexture(Cache::GetRessources<sf::Texture>("selection_eteint")).setTextureState("selection_eteint", "selection_allume", "selection_allume");
	b3.CreateFunctionCall([this] {
		m_status = Status::Fenetres;
		});

	Button& b4 = m_optionsButton.Add("VSYNC", forms::CreateSprite({ 345,692 }, Cache::GetRessources<sf::Texture>("selection_eteint")));
	b4.setTexture(Cache::GetRessources<sf::Texture>("selection_eteint")).setTextureState("selection_eteint", "selection_allume", "selection_allume");
	b4.CreateFunctionCall([this] {
		m_status = Status::VSync;
		});

	m_VSyncOff = forms::CreateSprite({ 1150,740 }, Cache::GetRessources<sf::Texture>("selection_non_off(134X134)"));
	m_VSyncOn = forms::CreateSprite({ 1275,740 }, Cache::GetRessources<sf::Texture>("selection_oui_off(134X134)"));
	m_VSyncOffLu = forms::CreateSprite({ 1150,740 }, Cache::GetRessources<sf::Texture>("selection_non_on(134X134)"));
	m_VSyncOnLu = forms::CreateSprite({ 1275,740 }, Cache::GetRessources<sf::Texture>("selection_oui_on(134X134)"));

	FullScreenOff = forms::CreateSprite({ 1150,590 }, Cache::GetRessources<sf::Texture>("selection_non_off(134X134)"));
	FullScreenOn = forms::CreateSprite({ 1275,590 }, Cache::GetRessources<sf::Texture>("selection_oui_off(134X134)"));
	FullScreenOffLu = forms::CreateSprite({ 1150,590 }, Cache::GetRessources<sf::Texture>("selection_non_on(134X134)"));
	FullScreenOnLu = forms::CreateSprite({ 1275,590 }, Cache::GetRessources<sf::Texture>("selection_oui_on(134X134)"));

	m_background.openFromFile("../Ressources/videos/Video_menu.mp4");
	m_background.play();
}

void MenuIG::processEvents(const sf::Event& e)
{
	//m_optionsButton.processEvents(e);
}

void MenuIG::update(const float& dt)
{
	TerritoryConquest::m_musicTC.stop();
	Battle_Royal::m_musicBR.stop();
	Auto_tamponneuse::m_musicAT.stop();

	Gamepads g;

	m_volume.setPosition({ (m_sprite.getPosition().x + 5) + (m_sprite.getGlobalBounds().width - 15) * (Options::volumeSound / MAX_VOLUME) - m_volume.getGlobalBounds().width / 2.f, 360 - 60 });
	m_volume2.setPosition({ (m_sprite.getPosition().x + 5) + (m_sprite.getGlobalBounds().width - 15) * (Options::volumeBruitages / Max_volume) - m_volume2.getGlobalBounds().width / 2.f, 500 - 60 });

	m_VSyncText.setTexture(Cache::GetRessources<sf::Texture>("VSyncCurrent"));
	m_windowedText.setTexture(Cache::GetRessources<sf::Texture>("pleinEcranCurrent"));
	m_volumeTex.setTexture(Cache::GetRessources<sf::Texture>("VolumeCurrent"));
	m_volumeTex2.setTexture(Cache::GetRessources<sf::Texture>("SFXCurrent"));

	if (m_window.hasFocus())
	{
		if (g.on_pressed(0, Xbox::LeftJoystick_Down))
		{
			o_selected++;
			if (o_selected > 3) {
				o_selected = 0;
			}
		}
		if (g.on_pressed(0, Xbox::LeftJoystick_Up))
		{
			o_selected--;
			if (o_selected < 0) {
				o_selected = 3;
			}
		}

		m_optionsButton.get("SoundButton").DesactivateHover();
		m_optionsButton.get("BruitagesButton").DesactivateHover();
		m_optionsButton.get("FenetresButton").DesactivateHover();
		m_optionsButton.get("VSYNC").DesactivateHover();

		if (o_selected == 0) {
			m_optionsButton.get("SoundButton").ForceHover();
			m_status = Status::Sound;
		}
		if (o_selected == 1) {
			m_optionsButton.get("BruitagesButton").ForceHover();
			m_status = Status::Bruitages;
		}
		if (o_selected == 2) {
			m_optionsButton.get("FenetresButton").ForceHover();
			m_status = Status::Fenetres;
		}
		if (o_selected == 3) {
			m_optionsButton.get("VSYNC").ForceHover();
			m_status = Status::VSync;
		}

		if (g.on_pressed(0, Xbox::Button::B)) {
			this->Save();
			m_mgr.goBackState();
		}
		else if (g.on_pressed(0, Xbox::Button::X)) {
			this->Save();
			//m_BaseState = FSM_Manager::create<Menu>(m_mgr, m_window, m_font, true);
			m_mgr.SoftChangeTransition<Transition<Menu>>(m_mgr, m_window, m_font, true);
		}
	}

	switch (m_status)
	{
	case Status::Empty:
		break;
	case Status::Bruitages:
		m_VSyncText.setTexture(Cache::GetRessources<sf::Texture>("VSyncCurrent"));
		m_windowedText.setTexture(Cache::GetRessources<sf::Texture>("pleinEcranCurrent"));
		m_volumeTex.setTexture(Cache::GetRessources<sf::Texture>("VolumeCurrent"));
		m_volumeTex2.setTexture(Cache::GetRessources<sf::Texture>("SFXLu"));
		current_bar.setPosition({ 390,468 });

		if (m_window.hasFocus())
		{
			if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Left))
				Options::volumeBruitages -= 15 * dt;
			else if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Right))
				Options::volumeBruitages += 15 * dt;
		}

		Options::volumeBruitages = std::clamp(Options::volumeBruitages, 0.f, 100.f);

		m_volumeText2 = func::CreateText(std::to_string(static_cast<int>(Options::volumeBruitages)), Cache::GetRessources<sf::Font>("Linebeam"), 30, { m_volume2.getPosition().x + 30,m_volume2.getPosition().y + 30 }, sf::Color::White);
		break;
	case Status::Sound:
		m_VSyncText.setTexture(Cache::GetRessources<sf::Texture>("VSyncCurrent"));
		m_windowedText.setTexture(Cache::GetRessources<sf::Texture>("pleinEcranCurrent"));
		m_volumeTex.setTexture(Cache::GetRessources<sf::Texture>("VolumeLu"));
		m_volumeTex2.setTexture(Cache::GetRessources<sf::Texture>("SFXCurrent"));
		current_bar.setPosition({ 390,328 });

		if (m_window.hasFocus())
		{
			if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Left))
				Options::volumeSound -= 15 * dt;
			else if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Right))
				Options::volumeSound += 15 * dt;
		}
		Options::volumeSound = std::clamp(Options::volumeSound, 0.f, 100.f);

		m_volumeText = func::CreateText(std::to_string(static_cast<int>(Options::volumeSound)), Cache::GetRessources<sf::Font>("Linebeam"), 30, { m_volume.getPosition().x + 30, m_volume.getPosition().y + 30 }, sf::Color::White);
		break;
	case Status::Fenetres:
		m_VSyncText.setTexture(Cache::GetRessources<sf::Texture>("VSyncCurrent"));
		m_windowedText.setTexture(Cache::GetRessources<sf::Texture>("pleinEcranLu"));
		m_volumeTex.setTexture(Cache::GetRessources<sf::Texture>("VolumeCurrent"));
		m_volumeTex2.setTexture(Cache::GetRessources<sf::Texture>("SFXCurrent"));
		current_bar.setPosition({ 390,608 });

		if (m_window.hasFocus())
		{
			if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Right) && !m_Fenetre)
			{
				m_window.changeFullScreen(sf::VideoMode::getDesktopMode(), "Jelly War", sf::Style::Fullscreen);
				m_Fenetre = true;
			}
			else if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Left) && m_Fenetre)
			{
				m_window.changeFullScreen(sf::VideoMode::getDesktopMode(), "Jelly War", sf::Style::Default);
				m_Fenetre = false;
			}
		}
		break;
	case Status::VSync:
		m_VSyncText.setTexture(Cache::GetRessources<sf::Texture>("VSyncLu"));
		m_windowedText.setTexture(Cache::GetRessources<sf::Texture>("pleinEcranCurrent"));
		m_volumeTex.setTexture(Cache::GetRessources<sf::Texture>("VolumeCurrent"));
		m_volumeTex2.setTexture(Cache::GetRessources<sf::Texture>("SFXCurrent"));
		current_bar.setPosition({ 390,748 });

		if (m_window.hasFocus())
		{
			if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Right))
			{
				V_Sync = true;
				m_window.setVerticalSyncEnabled(true);
			}
			else if (g.is_pressed(0, Xbox::Axis::LeftJoystick_Left))
			{
				V_Sync = false;
				m_window.setVerticalSyncEnabled(false);
			}
		}
		break;
	}

	m_background.update();

	if (m_background.getStatus() != sfe::Status::Playing) {
		m_background.play();
	}
}

void MenuIG::draw()
{
	m_window.draw(m_background);
	if (m_status == Status::Bruitages || m_status == Status::Fenetres || m_status == Status::Sound || m_status == Status::VSync)
		m_window.draw(current_bar);
	m_window.draw(m_ecranO);
	m_window.draw(retour_jeu);
	m_window.draw(retour_menu);
	m_window.draw(m_indicateur);
	m_window.draw(m_indicateur2);

	m_sprite.setPosition(800, 360);
	m_sprite2.setPosition(800, 360);
	m_sprite2.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_volume.getPosition().x - m_sprite2.getPosition().x + m_volume.getGlobalBounds().width / 2.f), 29));
	m_window.draw(m_sprite);
	m_window.draw(m_sprite2);
	m_window.draw(m_volume);

	m_sprite.setPosition(800, 500);
	m_sprite2.setPosition(800, 500);
	m_sprite2.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_volume2.getPosition().x - m_sprite2.getPosition().x + m_volume2.getGlobalBounds().width / 2.f), 29));
	m_window.draw(m_sprite);
	m_window.draw(m_sprite2);
	m_window.draw(m_volume2);

	if (V_Sync == false) {
		m_window.draw(m_VSyncOn);
		m_window.draw(m_VSyncOffLu);
	}
	else if (V_Sync == true)
	{
		m_window.draw(m_VSyncOff);
		m_window.draw(m_VSyncOnLu);
	}
	if (m_Fenetre == false)
	{
		m_window.draw(FullScreenOn);
		m_window.draw(FullScreenOffLu);
	}
	else if (m_Fenetre == true)
	{
		m_window.draw(FullScreenOff);
		m_window.draw(FullScreenOnLu);
	}

	m_window.draw(m_VSyncText);
	m_optionsButton.draw(m_window.getRenderWindow());

	m_window.draw(m_volumeText);
	m_window.draw(m_volumeText2);
	m_window.draw(m_volumeTex);
	m_window.draw(m_volumeTex2);
	m_window.draw(m_windowedText);
}

void MenuIG::Save()
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
	file["volumeSound"] << Options::volumeSound;
	file["volumeBruitages"] << Options::volumeBruitages;
}

#include "Application.h"
#include <chrono>
#include "Menu.h"
#include "Cache.h"
#include <future>
#include "Functions.h"
#include "Gamepad.h"
#include "SFML/Audio.hpp"
#include "Options.h"
#include "Cinematiques.h"
#include "File_Reader.h"

void Application::InitLoader()
{
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
	if (file["volumeSound"].found()) {
		file["volumeSound"] >> Options::volumeSound;
	}

	if (file["volumeBruitages"].found()) {
		file["volumeBruitages"] >> Options::volumeBruitages;
	}
}

void Application::run()
{
	this->InitLoader();
	WindowManager w{ sf::VideoMode::getDesktopMode(), "Jelly War",8,"../Ressources/pour_le_exe.png",64,64 };
	FSM_Manager mgr;
	sf::Font font{ Cache::GetRessources<sf::Font>("MaFont") };

	mgr.AddState(FSM_Manager::create<Cinematique<Menu>>(mgr, w, font, true, "anim_GA", true));

	auto Clock = std::chrono::high_resolution_clock::now();

	while (w.isOpen())
	{
		Gamepads g;
		g.update();

		const auto tmp = std::chrono::high_resolution_clock::now();
		const auto m_fDeltaTime = tmp - Clock;
		Clock = tmp;

		mgr.updateState();

		for (sf::Event e = sf::Event{}; w.pollEvent(e);)
		{
			if (e.type == sf::Event::EventType::Closed)
				w.close();

			if (e.type == sf::Event::KeyPressed)
			{
				if (e.type == sf::Event::KeyPressed)
					if (e.key.code == sf::Keyboard::Key::F1)
						w.toggleFullScreen(8, "../Ressources/pour_le_exe.png", 64, 64);

			}
			mgr.processEvents(e);
		}
		mgr.update(std::chrono::duration<float>{m_fDeltaTime}.count());

		w.clear();
		w.setDefaultView();
		mgr.draw();
		w.display();

		//TEST TIMER A REALISER
		//std::cout << std::to_string(10000 / std::chrono::duration<float>{m_fDeltaTime}.count() * 10000) << "\n";
	}
}

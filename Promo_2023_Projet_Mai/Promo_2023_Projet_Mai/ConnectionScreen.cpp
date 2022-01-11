#include "ConnectionScreen.h"
#include "Cache.h"
#include "Gamepad.h"
#include "Menu.h"
#include "Game.h"
#include <numbers>
#include "Functions.h"
#include "Loading.h"
#include "Cinematiques.h"

bool ConnectionScreen::can_switch(Joueur::Couleur color)
{
	for (auto& [id, other] : others) {
		if (other.color == color) {
			return false;
		}
	}

	return true;
}

ConnectionScreen::ConnectionScreen(FSM_Manager& mgr, WindowManager& window, sf::Font& font, const bool change)
	: FSM{ mgr,window,font,change }
{
	m_background.openFromFile("../Ressources/videos/Video_menu.mp4");
	m_fond.setTexture(Cache::GetRessources<sf::Texture>("lobby v666"));

	m_play.setTexture(Cache::GetRessources<sf::Texture>("jouer_1"));
	m_play.setOrigin(m_play.getGlobalBounds().width / 2, m_play.getGlobalBounds().height / 2);
	m_play.setPosition(1675, 935);

	En_Attente.setTexture(Cache::GetRessources<sf::Texture>("en_attente_de_joueurs"));
	En_Attente.setOrigin(En_Attente.getGlobalBounds().width / 2, En_Attente.getGlobalBounds().height / 2);
	En_Attente.setPosition(500, 70);

	m_quit.setTexture(Cache::GetRessources<sf::Texture>("quitter_1"));
	m_quit.setOrigin(m_quit.getGlobalBounds().width / 2, m_quit.getGlobalBounds().height / 2);
	m_quit.setPosition(230, 935);

	Personnage[0].setTexture(Cache::GetRessources<sf::Texture>("Gudublob FACE"));
	Personnage[1].setTexture(Cache::GetRessources<sf::Texture>("Belzeblob FACE"));
	Personnage[2].setTexture(Cache::GetRessources<sf::Texture>("Tahiti Blob FACE"));
	Personnage[3].setTexture(Cache::GetRessources<sf::Texture>("Blobillon FACE"));
	Personnage[4].setTexture(Cache::GetRessources<sf::Texture>("Blobic FACE"));
	Personnage[5].setTexture(Cache::GetRessources<sf::Texture>("Mamiblob FACE"));
	Personnage[6].setTexture(Cache::GetRessources<sf::Texture>("Arliblob FACE"));
	Personnage[7].setTexture(Cache::GetRessources<sf::Texture>("Lapiblob FACE"));
	Personnage[8].setTexture(Cache::GetRessources<sf::Texture>("InconiBlob"));

	m_colors[0].setTexture(Cache::GetRessources<sf::Texture>("Color1"));
	m_colors[1].setTexture(Cache::GetRessources<sf::Texture>("Color2"));
	m_colors[2].setTexture(Cache::GetRessources<sf::Texture>("Color3"));
	m_colors[3].setTexture(Cache::GetRessources<sf::Texture>("Color4"));
	m_colors[4].setTexture(Cache::GetRessources<sf::Texture>("Color5"));
	m_colors[5].setTexture(Cache::GetRessources<sf::Texture>("Color6"));
	m_colors[6].setTexture(Cache::GetRessources<sf::Texture>("Color7"));
	m_colors[7].setTexture(Cache::GetRessources<sf::Texture>("Color8"));

	m_colors[0].setPosition(460, 933);
	m_colors[1].setPosition(588, 933);
	m_colors[2].setPosition(717, 933);
	m_colors[3].setPosition(847, 933);
	m_colors[4].setPosition(975, 933);
	m_colors[5].setPosition(1105, 933);
	m_colors[6].setPosition(1233, 933);
	m_colors[7].setPosition(1363, 933);

	circleFilling.setPrimitiveType(sf::PrimitiveType::LinesStrip);

	for (float i = 0; i < 2 * std::numbers::pi_v<float>; i += (std::numbers::pi_v<float> / 180.f)) {
		circleFilling.append(sf::Vertex(sf::Vector2f(1700 + 50 * cos(i), 750 + 50 * sin(i))));
		circleFilling.append(sf::Vertex(sf::Vector2f(1700 + 51 * cos(i), 750 + 51 * sin(i))));
		circleFilling.append(sf::Vertex(sf::Vector2f(1700 + 52 * cos(i), 750 + 52 * sin(i))));
		circleFilling.append(sf::Vertex(sf::Vector2f(1700 + 53 * cos(i), 750 + 53 * sin(i))));
	}

	m_background.play();

	m_lobbyip.setFont(Cache::GetRessources<sf::Font>("Choko"));
	m_lobbyip.setCharacterSize(45);
	m_lobbyip.setOutlineThickness(4);
	m_lobbyip.setFillColor(sf::Color(41, 211, 161));
	m_lobbyip.setOutlineColor(sf::Color::White);
}

void ConnectionScreen::processEvents(const sf::Event&)
{
}

void ConnectionScreen::update(const float& dt)
{
	if (m_window.hasFocus())
	{
		Gamepads g;

		if (g.on_pressed(0, Xbox::Axis::LeftJoystick_Right) || g.on_pressed(0, Xbox::Button::Cross_Right)) {
			m_choice++;

			if (m_choice > 9)
				m_choice = 0;

			m_BlobName.setColor(sf::Color::White);
			switch (m_choice)
			{
			case 1: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Gudublob"));
				break;
			}
			case 2: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Belzeblob"));
				break;
			}
			case 3: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Tahiti Blob"));
				break;
			}
			case 4: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Blobillon"));
				break;
			}
			case 5: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Blobic"));
				break;
			}
			case 6: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Mamiblob"));
				break;
			}
			case 7: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_arliblob"));
				break;
			}
			case 8: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Lapiblob"));
				break;
			}

			default:
				m_BlobName.setColor(sf::Color::Transparent);
				break;
			}
		}
		if (g.on_pressed(0, Xbox::Axis::LeftJoystick_Left) || g.on_pressed(0, Xbox::Button::Cross_Left)) {
			m_choice--;

			if (m_choice < 0)
				m_choice = 9;

			m_BlobName.setColor(sf::Color::White);
			switch (m_choice)
			{
			case 1: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Gudublob"));
				break;
			}
			case 2: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Belzeblob"));
				break;
			}
			case 3: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Tahiti Blob"));
				break;
			}
			case 4: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Blobillon"));
				break;
			}
			case 5: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Blobic"));
				break;
			}
			case 6: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Mamiblob"));
				break;
			}
			case 7: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_arliblob"));
				break;
			}
			case 8: {
				m_BlobName.setTexture(Cache::GetRessources<sf::Texture>("Txt_Lapiblob"));
				break;
			}

			default:
				m_BlobName.setColor(sf::Color::Transparent);
				break;
			}
		}

		m_play.setTexture(Cache::GetRessources<sf::Texture>("jouer_1"));
		m_quit.setTexture(Cache::GetRessources<sf::Texture>("quitter_1"));

		m_colors[0].setColor(sf::Color(125, 125, 125, 255));
		m_colors[1].setColor(sf::Color(125, 125, 125, 255));
		m_colors[2].setColor(sf::Color(125, 125, 125, 255));
		m_colors[3].setColor(sf::Color(125, 125, 125, 255));
		m_colors[4].setColor(sf::Color(125, 125, 125, 255));
		m_colors[5].setColor(sf::Color(125, 125, 125, 255));
		m_colors[6].setColor(sf::Color(125, 125, 125, 255));
		m_colors[7].setColor(sf::Color(125, 125, 125, 255));

		switch (m_choice)
		{
		case 0: {
			m_quit.setTexture(Cache::GetRessources<sf::Texture>("quitter_2"));
			break;
		}
		case 1: {
			m_colors[0].setColor(sf::Color::White);
			break;
		}
		case 2: {
			m_colors[1].setColor(sf::Color::White);
			break;
		}
		case 3: {
			m_colors[2].setColor(sf::Color::White);
			break;
		}
		case 4: {
			m_colors[3].setColor(sf::Color::White);
			break;
		}
		case 5: {
			m_colors[4].setColor(sf::Color::White);
			break;
		}
		case 6: {
			m_colors[5].setColor(sf::Color::White);
			break;
		}
		case 7: {
			m_colors[6].setColor(sf::Color::White);
			break;
		}
		case 8: {
			m_colors[7].setColor(sf::Color::White);
			break;
		}
		case 9: {
			m_play.setTexture(Cache::GetRessources<sf::Texture>("jouer_2"));
			break;
		}

		default:
			break;
		}

		if (g.on_pressed(0, Xbox::Button::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
			switch (m_choice)
			{
			case 0: {
				m_BaseState = FSM_Manager::create<Menu>(m_mgr, m_window, m_font, true);
				break;
			}
			case 1: {
				if (can_switch(Joueur::Couleur::One)) {
					MyColor = Joueur::Couleur::One;
				}
				break;
			}
			case 2: {
				if (can_switch(Joueur::Couleur::Two)) {
					MyColor = Joueur::Couleur::Two;
				}
				break;
			}
			case 3: {
				if (can_switch(Joueur::Couleur::Three)) {
					MyColor = Joueur::Couleur::Three;
				}
				break;
			}
			case 4: {
				if (can_switch(Joueur::Couleur::Four)) {
					MyColor = Joueur::Couleur::Four;
				}
				break;
			}
			case 5: {
				if (can_switch(Joueur::Couleur::Five)) {
					MyColor = Joueur::Couleur::Five;
				}
				break;
			}
			case 6: {
				if (can_switch(Joueur::Couleur::Six)) {
					MyColor = Joueur::Couleur::Six;
				}
				break;
			}
			case 7: {
				if (can_switch(Joueur::Couleur::Seven)) {
					MyColor = Joueur::Couleur::Seven;
				}
				break;
			}
			case 8: {
				if (can_switch(Joueur::Couleur::Height)) {
					MyColor = Joueur::Couleur::Height;
				}
				break;
			}
			case 9: {
				if (MyColor != Joueur::Couleur::None) {
					ready = !ready;
				}
				break;
			}

			default:
				break;
			}
		}
	}

	m_background.update();

	if (m_background.getStatus() != sfe::Status::Playing) {
		m_background.play();
	}

	if (m_mgr.Network() != nullptr) {
		m_mgr.Network()->updateInfos(ready, MyColor);
		m_mgr.Network()->processEvents(others);
	}
	if (ready && std::count_if(std::begin(others), std::end(others), [](const auto& b) {return b.second.ready; }) == others.size()) {
		launch_timer += dt;
	}
	else {
		launch_timer = 0.f;
	}

	if (launch_timer > 1.f) {
		m_BaseState = FSM_Manager::create<Cinematique<Loading<Game>>>(m_mgr, m_window, m_font, true, "VideoIntro");
		Menu::m_mainMusic.stop();
		launch_timer = 0.f;
	}

	m_connected.setTexture(Cache::GetRessources<sf::Texture>("_" + std::to_string(others.size() + 1)), true);
	m_connected.setOrigin(0, m_connected.getGlobalBounds().height / 2.f);
	m_connected.setPosition(1150, 48);

	auto iready = std::count_if(std::begin(others), std::end(others), [](const auto& b) {return b.second.ready; });
	if (ready) {
		iready++;
	}


	m_ready.setTexture(Cache::GetRessources<sf::Texture>("_" + std::to_string(iready)), true);
	m_ready.setOrigin(m_ready.getGlobalBounds().width, m_ready.getGlobalBounds().height / 2.f);
	m_ready.setPosition(1100, 48);
}

void ConnectionScreen::draw()
{
	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_background);
	m_window.draw(m_fond);

	for (auto& ColorIcon : m_colors) {
		m_window.draw(ColorIcon);
	}

	sf::Text pseudo("", Cache::GetRessources<sf::Font>("Choko"));
	pseudo.setFillColor(sf::Color::Black);

	if (MyColor == Joueur::Couleur::None) {
		size_t tmpchoice = std::clamp<int>(m_choice - 1, 0, 7);
		Personnage[tmpchoice].setPosition(475, 275);
		Personnage[tmpchoice].setColor(sf::Color::Black);

		m_window.draw(Personnage[tmpchoice]);
	}
	else {
		Personnage[static_cast<size_t>(MyColor) - 1].setPosition(475, 275);
		Personnage[static_cast<size_t>(MyColor) - 1].setColor((ready) ? sf::Color::White : sf::Color(175, 175, 175, 255));

		m_window.draw(Personnage[static_cast<size_t>(MyColor) - 1]);
	}

	if (m_mgr.Network() != nullptr) {
		pseudo.setString(m_mgr.Network()->getPseudo());
	}
	pseudo.setPosition(500, 400);
	m_window.draw(pseudo);

	int i = 0;
	for (auto& [id, other] : others) {
		++i;
		pseudo.setString(other.pseudo);

		if (i < 4) {
			Personnage[static_cast<size_t>(other.color) - 1].setPosition(475.f + (288.f * i), 275.f);
			pseudo.setPosition(500.f + 288.f * i, 400);
		}
		else {
			Personnage[static_cast<size_t>(other.color) - 1].setPosition(475.f + ((i - 4) * 288.f), 575.f);
			pseudo.setPosition(500.f + 288.f * (i - 4), 700);
		}

		Personnage[static_cast<size_t>(other.color) - 1].setColor((other).ready ? sf::Color::White : sf::Color(175, 175, 175, 255));
		m_window.draw(Personnage[static_cast<size_t>(other.color) - 1]);
		m_window.draw(pseudo);
	}

	m_lobbyip.setPosition(1535, 60);
	if (m_mgr.Network() != nullptr) {
		m_lobbyip.setString(m_mgr.Network()->getRemoteAddress().toString());
	}

	m_BlobName.setOrigin(m_BlobName.getGlobalBounds().width / 2.f, m_BlobName.getGlobalBounds().height / 2.f);
	m_BlobName.setPosition(960, 885);
	m_window.draw(m_BlobName);
	m_window.draw(m_connected);
	m_window.draw(m_ready);
	m_window.draw(m_play);
	m_window.draw(m_quit);
	m_window.draw(En_Attente);
	m_window.draw(m_lobbyip);

	sf::VertexArray tmp(sf::PrimitiveType::LinesStrip);

	for (int i = 0; i < (360 * 4) * std::clamp<float>(launch_timer / 1.f, 0.f, 1.f); i++) {
		tmp.append(circleFilling[i]);
	}

	m_window.getRenderWindow().draw(tmp);
}
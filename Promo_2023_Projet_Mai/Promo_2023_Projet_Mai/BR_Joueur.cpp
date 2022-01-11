#include "BR_Joueur.h"
#include "Cache.h"
#include "Gamepad.h"
#include <math.h>
#include <numbers>
#include "Projectiles_BR.h"
#include "Network.h"
#include "Options.h"

BR_Joueur::BR_Joueur()
{
	m_bufferTir.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxdeGroupe/JellyBall/JBTir.wav");
	m_soundTir.setBuffer(m_bufferTir);
	Velocity.x = 0;
	Velocity.y = 0;
	Hitbox.setSize(sf::Vector2f(90, 90));
	Hitbox.setOrigin(45, 45);
	Sprite.setOrigin(45, 45);
	Sprite.setPosition(sf::Vector2f(900, 300));
	Hitbox.setPosition(GetPos());

	anim = Animator(sf::IntRect(0,0,90,90), 20, 0.05f);
}

BR_Joueur::~BR_Joueur()
{
}

void BR_Joueur::Controles(const float& dt, std::vector< Projectiles_BR>& projectiles, Network* network, bool focus)
{
	timer_tir += dt;

	if (focus) {
		Gamepads g;

		angle = atan2(g.axis_pression(0, Xbox::Axis::RightJoystick_Left), g.axis_pression(0, Xbox::Axis::RightJoystick_Down));
		angle -= std::numbers::pi_v<float> / 2.f;


		if (g.is_pressed(0, Xbox::RT) && timer_tir > 0.7f && !invinsible)
		{
			m_soundTir.play();
			auto& last = projectiles.emplace_back(angle, GetPos(), this);
			if (network != nullptr) {
				network->updateInfos(&last);
			}
			timer_tir = 0.f;
		}


		angle += std::numbers::pi_v<float> / 2.f;
		angle = angle * 180.f / std::numbers::pi_v<float>;

		Sprite.setRotation(angle);
		Velocity.x = 0;
		Velocity.y = 0;
		if (g.is_pressed(0, Xbox::LeftJoystick_Up) && g.is_pressed(0, Xbox::LeftJoystick_Right))
		{
			Velocity.y = -(speed - 50);;
			Velocity.x = speed;
		}
		else if (g.is_pressed(0, Xbox::LeftJoystick_Up) && g.is_pressed(0, Xbox::LeftJoystick_Left))
		{
			Velocity.y = -(speed - 50);;
			Velocity.x = -(speed - 50);;
		}
		else if (g.is_pressed(0, Xbox::LeftJoystick_Down) && g.is_pressed(0, Xbox::LeftJoystick_Right))
		{
			Velocity.y = speed;
			Velocity.x = speed;
		}
		else if (g.is_pressed(0, Xbox::LeftJoystick_Down) && g.is_pressed(0, Xbox::LeftJoystick_Left))
		{
			Velocity.y = speed;
			Velocity.x = -(speed - 50);
		}
		else if (g.is_pressed(0, Xbox::LeftJoystick_Up))
		{
			Velocity.y = -speed;
		}
		else if (g.is_pressed(0, Xbox::LeftJoystick_Down))
		{
			Velocity.y = speed;
		}
		else if (g.is_pressed(0, Xbox::LeftJoystick_Right))
		{
			Velocity.x = speed;
		}
		else if (g.is_pressed(0, Xbox::LeftJoystick_Left))
		{
			Velocity.x = -speed;
		}
	}
	else {
		Velocity.x = 0;
		Velocity.y = 0;
	}

}

void BR_Joueur::Interaction(std::map<int, Joueur*>& joueurs)
{
}

void BR_Joueur::Controle(const float& dt)
{
	anim.Animation(Sprite, dt);
}

void BR_Joueur::Update(const float& dt, sf::Image& image, std::vector< Projectiles_BR>& projectiles, Network* network, bool focus)
{
	m_soundTir.setVolume(Options::volumeBruitages);


	Controle(dt);
	Get_NextPos(dt, image);

	timer_invinsible += dt;

	if (ColDroite)
	{
		Velocity.x = 0;
	}
	if (ColGauche)
	{
		Velocity.x = 0;
	}
	if (ColHaut)
	{
		Velocity.y = 0;
	}
	if (ColBas)
	{
		Velocity.y = 0;
	}

	Move(Velocity * dt);


	Hitbox.setPosition(GetPos());
	Controles(dt, projectiles, network, focus);

	Go_invisible(dt);
}

void BR_Joueur::setInvinsible(bool b)
{
	invinsible = b;
}

void BR_Joueur::setScore(int _score)
{
	score = _score;
}

void BR_Joueur::Go_invisible(const float& dt)
{
	if (invinsible)
	{
		timer_IsInvinsible += dt;

		if (timer_invinsible < 0.1f)
		{
			Sprite.setColor(sf::Color(255, 255, 255, 180));
		}
		else
		{
			Sprite.setColor(sf::Color(255, 255, 255, 255));
		}

		if (timer_invinsible > 0.2f)
		{
			timer_invinsible = 0.f;
		}

		if (timer_IsInvinsible > 3.f)
		{
			invinsible = false;
			timer_IsInvinsible = 0.f;
		}
	}
	else
	{
		Sprite.setColor(sf::Color(255, 255, 255, 255));
	}
}

void BR_Joueur::SetColor(Couleur color)
{
	MyColor = color;

	switch (MyColor)
	{
	case Joueur::Couleur::One:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer1"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Gudublob FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_turquoise"));
		id = 1;
		classement = 1;
		break;
	case Joueur::Couleur::Two:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer2"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Belzeblob FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_rouge"));
		id = 2;
		classement = 2;
		break;
	case Joueur::Couleur::Three:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer3"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Tahiti Blob FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_magenta"));
		id = 3;
		classement = 3;
		break;
	case Joueur::Couleur::Four:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer4"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Blobillon FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_bleu"));
		id = 4;
		classement = 4;
		break;
	case Joueur::Couleur::Five:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer5"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Blobic FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_orange"));
		id = 5;
		classement = 5;
		break;
	case Joueur::Couleur::Six:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer6"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Mamiblob FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_jaune"));
		id = 6;
		classement = 6;
		break;
	case Joueur::Couleur::Seven:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer7"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Arliblob FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_violet"));
		id = 7;
		classement = 7;
		break;
	case Joueur::Couleur::Height:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer8"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Lapiblob FACE"));
		m_arrow.setTexture(Cache::GetRessources<sf::Texture>("direction_vert"));
		id = 8;
		classement = 8;
		break;
	default:
		break;
	}
}

void BR_Joueur::Set_spawn()
{
	if (id == 1)
	{
		Sprite.setPosition(sf::Vector2f(900,300));
	}
	else if (id == 2)
	{
		Sprite.setPosition(sf::Vector2f(2000, 300));
	}
	else if (id == 3)
	{
		Sprite.setPosition(sf::Vector2f(300, 900));
	}
	else if (id == 4)
	{
		Sprite.setPosition(sf::Vector2f(2600, 900));
	}
	else if (id == 5)
	{
		Sprite.setPosition(sf::Vector2f(300, 2000));
	}
	else if (id == 6)
	{
		Sprite.setPosition(sf::Vector2f(2600, 2000));
	}
	else if (id == 7)
	{
		Sprite.setPosition(sf::Vector2f(900, 2600));
	}
	else if (id == 8)
	{
		Sprite.setPosition(sf::Vector2f(2000, 2600));
	}
}

void BR_Joueur::Display_Inv(WindowManager& window, bool inv)
{
	if (inv)
	{
		if (timer_invinsible < 0.1f)
		{
			Sprite.setColor(sf::Color(255, 255, 255, 150));
		}
		else
		{
			Sprite.setColor(sf::Color(255, 255, 255, 255));
		}

		if (timer_invinsible > 0.2f)
		{
			timer_invinsible = 0.f;
		}

		if (timer_IsInvinsible > 3.f)
		{
			invinsible = false;
			timer_IsInvinsible = 0.f;
		}
	}
	else
	{
		Sprite.setColor(sf::Color(255, 255, 255, 255));
	}


	window.draw(Sprite);
}

void BR_Joueur::Display_Victoire(WindowManager& window)
{
	if (classement == 1)
	{
		tete.setPosition(sf::Vector2f(730, 210));
	}
	else if (classement == 2)
	{
		tete.setPosition(sf::Vector2f(730, 300));
	}
	else if (classement == 3)
	{
		tete.setPosition(sf::Vector2f(730, 390));
	}
	else if (classement == 4)
	{
		tete.setPosition(sf::Vector2f(730, 480));
	}
	else if (classement == 5)
	{
		tete.setPosition(sf::Vector2f(730, 570));
	}
	else if (classement == 6)
	{
		tete.setPosition(sf::Vector2f(730, 660));
	}
	else if (classement == 7)
	{
		tete.setPosition(sf::Vector2f(730, 750));
	}
	else if (classement == 8)
	{
		tete.setPosition(sf::Vector2f(730, 840));
	}
	window.draw(tete);
	tete.setPosition(1433.f, 327.f);
	window.draw(tete);
}

void BR_Joueur::Display(WindowManager& window)
{
	m_arrow.setOrigin(m_arrow.getGlobalBounds().width / 2.f, m_arrow.getGlobalBounds().height / 2.f);
	m_arrow.setPosition(Sprite.getPosition().x + (75.f * cos((Sprite.getRotation() - 90.f) * std::numbers::pi_v<float> / 180.f)), 
						Sprite.getPosition().y + (75.f * sin((Sprite.getRotation() - 90.f) * std::numbers::pi_v<float> / 180.f)));

	m_arrow.setRotation((Sprite.getRotation()));

	window.draw(m_arrow);
	window.draw(Sprite);
}

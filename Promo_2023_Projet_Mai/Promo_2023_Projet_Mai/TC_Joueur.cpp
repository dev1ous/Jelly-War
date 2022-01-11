#include "TC_Joueur.h"
#include "Cache.h"
#include "Functions.h"
#include "Gamepad.h"
#include <numbers>

TC_Joueur::TC_Joueur()
{
	Velocity.x = 0.f;
	Velocity.y = 0.f;
	Sprite.setPosition({ 100,100 });
	Hitbox.setSize({ 82.f,82.f });
	Hitbox.setOrigin(42.5f, 42.5f);
	Sprite.setOrigin(42.5f, 42.5f);

	anim = Animator(sf::IntRect(0, 0, 90, 90), 20, 0.05f);
}

void TC_Joueur::Interaction(std::map<int, Joueur*>& joueurs, const float& dt)
{
	std::for_each(std::begin(joueurs), std::end(joueurs), [&dt, this](const auto& it) {

		if (collidesWith(*it.second, dt)) {
			Velocity.x = 0.f;
			Velocity.y = 0.f;
			it.second->setVelocity({ 0,0 });
		}
		});
}

void TC_Joueur::Controle(const float& dt)
{
	Gamepads g;

	angle = std::atan2(g.axis_pression(0, Xbox::Axis::LeftJoystick_Left), g.axis_pression(0, Xbox::Axis::LeftJoystick_Down));
	angle -= std::numbers::pi_v<float> / 2.f;

	angle += std::numbers::pi_v<float> / 2.f;
	angle = angle * 180.f / std::numbers::pi_v<float>;

	Sprite.setRotation(angle);
	Velocity.x = 0;
	Velocity.y = 0;

	if (g.is_pressed(0, Xbox::LeftJoystick_Up) && g.is_pressed(0, Xbox::LeftJoystick_Right))
	{
		if (GetPos().y > 0 + Sprite.getGlobalBounds().height / 2)
			Velocity.y = -(m_speed - 10);
		if (GetPos().x < 2000 - Sprite.getGlobalBounds().width / 2)
			Velocity.x = m_speed;
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Up) && g.is_pressed(0, Xbox::LeftJoystick_Left))
	{
		if(GetPos().y > 0 + Sprite.getGlobalBounds().height / 2)
			Velocity.y = -(m_speed - 10);
		if(GetPos().x > 0 + Sprite.getGlobalBounds().width / 2)
			Velocity.x = -(m_speed - 10);
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Down) && g.is_pressed(0, Xbox::LeftJoystick_Right))
	{
		if (GetPos().y < 2000 - Sprite.getGlobalBounds().height / 2)
			Velocity.y = m_speed;
		if (GetPos().x < 2000 - Sprite.getGlobalBounds().width / 2)
			Velocity.x = m_speed;
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Down) && g.is_pressed(0, Xbox::LeftJoystick_Left))
	{
		if (GetPos().y < 2000 - Sprite.getGlobalBounds().height / 2)
			Velocity.y = m_speed;
		if (GetPos().x > 0 + Sprite.getGlobalBounds().width / 2)
			Velocity.x = -(m_speed - 10);
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Up) && GetPos().y > 0 + Sprite.getGlobalBounds().height / 2)
	{
		Velocity.y = -m_speed;
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Down) && GetPos().y < 2000 - Sprite.getGlobalBounds().height / 2)
	{
		Velocity.y = m_speed;
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Right) && GetPos().x < 2000 - Sprite.getGlobalBounds().width / 2)
	{
		Velocity.x = m_speed;
	}
	else if (g.is_pressed(0, Xbox::LeftJoystick_Left) && GetPos().x > 0 + Sprite.getGlobalBounds().width / 2)
	{
		Velocity.x = -m_speed;
	}

	if (ColBas || ColHaut)
		Velocity.y = 0;
	if (ColDroite || ColGauche)
		Velocity.x = 0;

	Hitbox.setPosition(GetPos());
}

void TC_Joueur::Update(const float& dt, sf::Image& image)
{
}

void TC_Joueur::update(const float& dt)
{
	Move(Velocity * dt);
	Hitbox.setPosition(GetPos());
	Controle(dt);
}

void TC_Joueur::Display(WindowManager& window)
{
	window.draw(Sprite);
}

void TC_Joueur::Display_Victoire(WindowManager& window)
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

void TC_Joueur::SetColor(Couleur color)
{
	MyColor = color;

	switch (MyColor)
	{
	case Joueur::Couleur::One:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer1"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Gudublob FACE"));
		id = 1;
		classement = 1;
		break;
	case Joueur::Couleur::Two:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer2"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Belzeblob FACE"));
		id = 2;
		classement = 2;
		break;
	case Joueur::Couleur::Three:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer3"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Tahiti Blob FACE"));
		id = 3;
		classement = 3;
		break;
	case Joueur::Couleur::Four:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer4"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Blobillon FACE"));
		id = 4;
		classement = 4;
		break;
	case Joueur::Couleur::Five:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer5"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Blobic FACE"));
		id = 5;
		classement = 5;
		break;
	case Joueur::Couleur::Six:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer6"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Mamiblob FACE"));
		id = 6;
		classement = 6;
		break;
	case Joueur::Couleur::Seven:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer7"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Arliblob FACE"));
		id = 7;
		classement = 7;
		break;
	case Joueur::Couleur::Height:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("BRPlayer8"));
		tete.setTexture(Cache::GetRessources<sf::Texture>("Lapiblob FACE"));
		id = 8;
		classement = 8;
		break;
	default:
		break;
	}
}

bool TC_Joueur::collidesWith(Joueur& j, const float& dt)
{
	auto d(static_cast<TC_Joueur*>(&j));
	
	if (d)
	{

		sf::Vector2f nextPos = GetPos() + Velocity * dt;
		sf::Vector2f nextPosOther = j.GetPos() + j.GetVelocity() * dt;
		
		sf::FloatRect rectToMove(nextPos.x, nextPos.y, Sprite.getGlobalBounds().left, Sprite.getGlobalBounds().top);
		sf::FloatRect rectToMoveOther(nextPosOther.x, nextPosOther.y, j.GetSprite().getGlobalBounds().left, j.GetSprite().getGlobalBounds().top);

		if (rectToMove.intersects(rectToMoveOther))
			return true;
	}
	return false;
}

double TC_Joueur::getDistanceEuclidean(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
	double x = pos1.x - pos2.x;
	double y = pos1.y - pos2.y;

	double dist;

	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);
	return dist;
}

void TC_Joueur::AnimUpdate(const float& dt)
{
	anim.Animation(Sprite, dt);
}
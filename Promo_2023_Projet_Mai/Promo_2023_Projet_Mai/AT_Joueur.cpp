#include "AT_Joueur.h"
#include "Functions.h"
#include "Gamepad.h"
#include "Cache.h"
#include "Options.h"
#include <numbers>


AT_Joueur::AT_Joueur(Vector2f _pos, int _color)
	: color(_color)
{
	if (!m_bufferAT.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxdeGroupe/AutoTamponneuse/ATChute.wav"))
		exit(0);
	m_soundAT.setBuffer(m_bufferAT);

	if (!m_bufferATCol.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxdeGroupe/AutoTamponneuse/ATCollision.wav"))
		exit(0);
	m_soundATCol.setBuffer(m_bufferATCol);

	m_dir = Direction::None;

	switch (color)
	{
	case 1:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(1)gudu"));
		break;
	case 2:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(2)Belz"));
		break;
	case 3:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(3)TB"));
		break;
	case 4:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(4)Blobillon"));
		break;
	case 5:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(5)Blobic"));
		break;
	case 6:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(6)Cinnamon"));
		break;
	case 7:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(7)Arli"));
		break;
	case 8:
		shape.setTexture(&Cache::GetRessources<sf::Texture>("(8)Lapi"));
		break;
	default:
		break;
	}

	shape.setSize(Vector2f(static_cast<float>(shape.getTextureRect().width), static_cast<float>(shape.getTextureRect().height)));
	shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
	shape.setPosition(Vector2f(_pos.x, _pos.y));

	/////////////////////////Hitbox/////////////////////////
	hitbox.setRadius(shape.getGlobalBounds().height / 2);
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineColor(Color::Red);
	hitbox.setOutlineThickness(-1.f);
	hitbox.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
	hitbox.setPosition(shape.getPosition());
}

void AT_Joueur::Interaction(std::map<int, Joueur*>& joueurs, const float& dt, Network* network)
{
	for (auto& it : joueurs)
	{
		AT_Joueur* tmp = static_cast<AT_Joueur*>(it.second);
		Vector2f normalized;

		Vector2f prevVel;
		Vector2f prevVelTmp;

		Vector2f finalvel;

		bool hit = Collisions::Between2Circles(hitbox.getPosition(), tmp->GetHitBox().getPosition(), hitbox.getRadius(), tmp->GetHitBox().getRadius());

		if (hit)
		{
			m_soundATCol.play();

			if (!catchPrevVel)
			{
				prevVel = this->Velocity;
				prevVelTmp = tmp->GetVelocity();
			}

			if (this->Velocity == Vector2f(0, 0))
			{
				this->Velocity.x = prevVelTmp.x / 2;
				this->Velocity.y = prevVelTmp.y / 2;
			}
			else if (this->Velocity.x >= 0.f && this->Velocity.y >= 0.f)
			{
				this->Velocity = (prevVel + prevVelTmp) * dt;

				normalized = math::normalize(math::difference(this->GetPosition(), tmp->GetPosition()));

				finalvel = Vector2f(prevVelTmp.x + (-prevVel.x), prevVelTmp.y + (-prevVel.y));
				/*finalvel.x = std::clamp(finalvel.x, -500.f, 500.f);
				finalvel.y = std::clamp(finalvel.y, -500.f, 500.f);*/

				this->Velocity.x += finalvel.x;
				this->Velocity.y += finalvel.y;

				float l = math::length(math::difference(this->GetPosition(), tmp->GetPosition()));
				l = (hitbox.getRadius() * 2) - l;

				shape.move(-normalized * l);
			}
			else
			{
				this->Velocity = (prevVel + prevVelTmp) * dt;

				normalized = math::normalize(math::difference(this->GetPosition(), tmp->GetPosition()));

				finalvel = Vector2f(prevVelTmp.x + (-prevVel.x), prevVelTmp.y + (-prevVel.y));
				/*finalvel.x = std::clamp(finalvel.x, -500.f, 500.f);
				finalvel.y = std::clamp(finalvel.y, -500.f, 500.f);*/

				this->Velocity.x += finalvel.x;
				this->Velocity.y += finalvel.y;

				float l = math::length(math::difference(this->GetPosition(), tmp->GetPosition()));
				l = (hitbox.getRadius() * 2) - l;

				shape.move(-normalized * l);
			}

			if (network != nullptr)
				network->updateInfos(it.first, this);

			this->Velocity.x = std::clamp(this->Velocity.x, -250.f, 250.f);
			this->Velocity.y = std::clamp(this->Velocity.y, -250.f, 250.f);
		}
		else
		{
			prevVel = Vector2f(0, 0);
			prevVelTmp = Vector2f(0, 0);

			catchPrevVel = false;
		}
	}
}

void AT_Joueur::Controle(const float& dt, bool focus)
{
	Gamepads Pad;

	angle = atan2(Velocity.x, -Velocity.y);
	angle -= std::numbers::pi_v<float> / 2.f;

	if (focus) {
		///////////////////Mouvement////////////////////////////////////
		if (Pad.is_pressed(0, Xbox::Axis::LeftJoystick_Up))
			this->Velocity.y += -speed * dt;

		if (Pad.is_pressed(0, Xbox::Axis::LeftJoystick_Down))
			this->Velocity.y += speed * dt;

		if (Pad.is_pressed(0, Xbox::Axis::LeftJoystick_Left))
			this->Velocity.x += -speed * dt;

		if (Pad.is_pressed(0, Xbox::Axis::LeftJoystick_Right))
			this->Velocity.x += speed * dt;
	}

	angle += std::numbers::pi_v<float> / 2.f;
	angle = angle * 180.f / std::numbers::pi_v<float>;

	if (Velocity != Vector2f(0, 0))
	{
		prevAngle = angle;
		shape.setRotation(angle);
	}
	else if (Velocity == Vector2f(0, 0))
		shape.setRotation(prevAngle);

}

void AT_Joueur::Update(const float& dt, CircleShape& bounds, bool focus)
{
	m_soundAT.setVolume(Options::volumeBruitages);
	m_soundATCol.setVolume(Options::volumeBruitages);

	timerInteract += dt;

	if (Collisions::Between2Circles(shape.getPosition(), bounds.getPosition(), hitbox.getRadius(), bounds.getRadius()))
	{
		if (this->Velocity.x <= -.1f && this->Velocity.x >= .1f)
			this->Velocity.x = 0.f;

		if (this->Velocity.y <= -.1f && this->Velocity.y >= .1f)
			this->Velocity.y = 0.f;

		this->UpdateMouvement(dt);
		this->Controle(dt, focus);

		shape.move(this->Velocity * dt);

		//////////////////////HitboxUpdate////////////////////////////////
		hitbox.setPosition(shape.getPosition());
	}
	else
	{
		m_soundAT.play();
		canScore = false;
		shape.setPosition(Vector2f(5000, 5000));
		isAlive = false;
	}
}

void AT_Joueur::Display(WindowManager& window)
{
	if (isAlive)
	{
		window.draw(shape);
		//window.draw(hitbox);
	}
}

void AT_Joueur::UpdateMouvement(const float& dt)
{
	if (this->Velocity.x < 0)
		this->Velocity.x += speed / 5 * dt;
	if (this->Velocity.x > 0)
		this->Velocity.x += -speed / 5 * dt;
	if (this->Velocity.y < 0)
		this->Velocity.y += speed / 5 * dt;
	if (this->Velocity.y > 0)
		this->Velocity.y += -speed / 5 * dt;
}
//
//bool AT_Joueur::IsDead(CircleShape& bounds)
//{
//	bool hit = Collisions::Between2Circles(shape.getPosition(), bounds.getPosition(), hitbox.getRadius(), bounds.getRadius());
//
//	if (hit)
//		return false;
//	else
//		return true;
//}
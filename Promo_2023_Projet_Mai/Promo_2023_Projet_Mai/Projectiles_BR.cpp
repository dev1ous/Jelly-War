#include "Projectiles_BR.h"
#include "Cache.h"
#include <math.h>
#include "Functions.h"
#include "Options.h"

Projectiles_BR::Projectiles_BR()
{

	Hitbox.setSize(sf::Vector2f(45, 45));
	Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_bleu"));
}

Projectiles_BR::Projectiles_BR(float _angle, sf::Vector2f _pos, BR_Joueur* _owner)
{
	m_bufferTouche.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxdeGroupe/JellyBall/JBTouche.wav");
	m_soundTouche.setBuffer(m_bufferTouche);

	angle = _angle;
	owner = _owner;
	Hitbox.setSize(sf::Vector2f(45, 45));


	MyColor = _owner->getcolor();
	
	switch (MyColor)
	{
	case Joueur::Couleur::One:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_turquoise"));
		break;
	case Joueur::Couleur::Two:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_rouge"));
		break;
	case Joueur::Couleur::Three:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_magenta"));
		break;
	case Joueur::Couleur::Four:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_bleu"));
		break;
	case Joueur::Couleur::Five:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_orange"));
		break;
	case Joueur::Couleur::Six:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_jaune"));
		break;
	case Joueur::Couleur::Seven:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_violet"));
		break;
	case Joueur::Couleur::Height:
		Sprite.setTexture(Cache::GetRessources<sf::Texture>("sprite_tir_vert"));
		break;
	default:
		break;
	}

	Velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
	Pos = _pos;
	Hitbox.setPosition(Pos);
	Sprite.setPosition(Pos);

	rect.left = 0;
	rect.top = 0;
	rect.width = 45;
	rect.height = 45;

	Sprite.setTextureRect(rect);

	Hitbox.setOrigin(Hitbox.getGlobalBounds().width / 2, Hitbox.getGlobalBounds().width / 2);

	anim = Animator(rect, 3, 0.08f);
	
}

Projectiles_BR::~Projectiles_BR()
{
}

void Projectiles_BR::Update(const float& dt, sf::Image& image, BR_Joueur& you, std::map<int, BR_Joueur*>& others)
{
	m_soundTouche.setVolume(Options::volumeBruitages);
	anim.Animation(Sprite, dt);

	for (auto& [id, player] : others) 
	{

		if (owner != player && Collisions::Between2Circles(this->GetPos(), player->GetPos(), Sprite.getGlobalBounds().width / 2 , 30.f)) 
		{

			if (player->is_invincible())
			{
				vie = 0;
				go_explo = true;
			}
			else
			{
				vie = -1;
				go_explo = true;
				player->setInvinsible(true);
			}			
		}
	}
	if (owner != &you && Collisions::Between2Circles(this->GetPos(), you.GetPos(), Sprite.getGlobalBounds().width / 2, 30.f)) {

		vie = -1;
		go_explo = true;
		you.setInvinsible(true);
	}

	if (vie > 0) {
		Get_NextPos(dt, image);
	}


	Pos.x += Velocity.x * dt;
	Pos.y += Velocity.y * dt;

	if (!go_explo)
	{
		Hitbox.setPosition(Pos);
		Sprite.setPosition(Pos);
	}
	else
	{
		if (m_soundTouche.getStatus() != sf::Sound::Status::Playing)
			m_soundTouche.play();
		timer_explo += dt;
		if (one_pass)
		{
			rect.left = 0;
			rect.top = 45;
			rect.width = 80;
			rect.height = 80;
			explo = Animator(rect, 5, 0.05f);
			one_pass = false;
		}

		explo.Animation_NoRestart(Sprite, dt);

		if (timer_explo > 0.3f)
		{
			finExplo = true;
		}
	}


}

void Projectiles_BR::Display(WindowManager& window)
{
	window.draw(Sprite);
}

void Projectiles_BR::Get_NextPos(const float& dt, sf::Image& image)
{

	sf::Vector2f Next = Hitbox.getPosition();
	Next.y -= Hitbox.getGlobalBounds().height / 2;
	if (Velocity.x < 0) {
		Next.x -= Hitbox.getGlobalBounds().width / 2;

		for (int i = 0; i < (int)Hitbox.getGlobalBounds().height; i++) {
			for (float y = 0; y < (double)-Velocity.x * dt; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x - y, Next.y + i), image)) {
					vie = 0;
					go_explo = true;
					break;
				}
			}
		}
	}
	else if (Velocity.x > 0) {
		Next.x += Hitbox.getGlobalBounds().width / 2;

		for (int i = 0; i < (int)Hitbox.getGlobalBounds().height; i++) {
			for (float y = 0; y < (double)Velocity.x * dt; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x + y, Next.y + i), image)) {
					vie = 0;
					go_explo = true;
					break;
				}
			}
		}
	}

	Next = Hitbox.getPosition();
	Next.x -= Hitbox.getGlobalBounds().width / 2;

	if (Velocity.y < 0) {
		Next.y -= Hitbox.getGlobalBounds().height / 2;

		for (int i = 1; i < (int)Hitbox.getGlobalBounds().width; i++) {
			for (float y = 0; y < (double)-Velocity.y * dt + 0.1; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x + i, Next.y - y), image)) {
					vie = 0;
					go_explo = true;
					break;
				}
			}
		}
	}
	else if (Velocity.y > 0) {
		Next.y += Hitbox.getGlobalBounds().height / 2;
		for (int i = 1; i < (int)Hitbox.getGlobalBounds().width; i++) {
			for (float y = 0; y < (double)Velocity.y * dt + 0.1; y += (double)0.1f) {
				if (CheckCollid(sf::Vector2f(Next.x + i, Next.y + y), image)) {
					vie = 0;
					go_explo = true;
					break;
				}
			}
		}
	}
}



bool Projectiles_BR::CheckCollid(sf::Vector2f _pos, sf::Image& image)
{
	if (sf::FloatRect(0.f, 0.f, static_cast<float>(image.getSize().x), static_cast<float>(image.getSize().y)).contains(_pos)) {
		return image.getPixel(static_cast<int>(_pos.x), static_cast<int>(_pos.y)) == sf::Color::Black;
	}

	return false;
}

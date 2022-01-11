#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "BR_Joueur.h"
#include "SFML/Audio.hpp"

class Projectiles_BR
{
public:

	Projectiles_BR();
	Projectiles_BR(float angle, sf::Vector2f _pos, BR_Joueur* _owner);
	~Projectiles_BR();

	void Update(const float& dt, sf::Image& image, BR_Joueur& you, std::map<int, BR_Joueur*>& others);
	void Display(WindowManager& window);

	inline void Move() { Sprite.move(Velocity); }
	inline void Move(sf::Vector2f move) { Sprite.move(move); }

	inline const sf::Vector2f& GetPos() const { return Sprite.getPosition(); }
	inline const sf::Vector2f& GetVel() const { return Velocity; }
	inline const float& GetAngle() const { return angle; }

	void Get_NextPos(const float& dt, sf::Image& image);

	bool get_finExplo() { return finExplo; }
	void set_used() {used = true; }
	bool get_used() { return used; }
	inline int Get_Vie() { return vie; }

	BR_Joueur* owner{ nullptr };

	Joueur::Couleur MyColor;
private:

	sf::Vector2f Velocity;
	sf::Sprite Sprite;
	sf::RectangleShape Hitbox;

	sf::SoundBuffer  m_bufferTouche;
	sf::Sound  m_soundTouche;

	bool CheckCollid(sf::Vector2f _pos, sf::Image& image);
	int vie = 1;
	float speed = 900.f;
	float angle{ 0.f };

	sf::Vector2f Pos;
	sf::IntRect rect;
	bool finExplo = false;
	bool go_explo = false;
	bool one_pass = true;
	bool used = false;
	Animator anim;
	Animator explo;

	float timer_explo = 0.f;
};


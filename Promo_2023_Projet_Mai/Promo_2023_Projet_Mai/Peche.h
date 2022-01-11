#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include <vector>
#include "Animator.h"
#include "SFML/Audio.hpp"

using namespace sf;
class Plasma
{
public:

	Plasma();
	~Plasma();

	void Update(const float& dt);
	void Display(RenderWindow& app);
	bool Get_text() { return text; }
	Sprite Get_Sprite() { return sprite; }
	void Set_Texture(Texture* texture) { sprite.setTexture(*texture); text = false; }
	int Get_Vie() { return vie; }
	void Set_Vie();
	bool Get_Clickable() { return clickable; }
	Vector2f Get_Pos() { return Pos; }
private:

	Animator anim;
	Texture texture;
	Sprite sprite;
	Vector2f Pos;
	Vector2f Base_pos;
	int random;
	int speed = 300;
	int vie = 1;
	bool text = true;
	float transparence = 0;
	bool go_tranparence = false;
	bool clickable = true;
	bool death = false;
};


class Peche
{
public:

	Peche();
	~Peche();

	void Update(const float& dt);
	void Display(RenderWindow& app);
	void Spawn(const float& dt);
	void Go_Jauge();
	bool Get_Win() { return win; }
	void Go_debut(const float& dt);
	void Go_fin(const float& dt);
private:

	Vector2f PosMouse;

	Sprite curseur;
	Sprite fond;
	Sprite ecran;
	Sprite Jauge;
	Sprite Tuyaux;

	Animator anim;
	Animator anim2;

	sf::IntRect Rec_Jauge;
	Vector2f Pos;
	std::vector<Plasma> plasma;
	int score = 0;
	float timer_spawn = 0.f;
	float timer_jauge = 0.f;
	float timer_anim = 0.f;
	int frame = 0;
	int vie = 3;
	bool win = false;
	bool prewin = false;
	float timer_fin = 0.f;
	bool anim_bool = false;
	bool debut = true;
	float posx = 1980;

	sf::SoundBuffer m_bufferPlasma, m_bufferJauge, m_bufferEnd;
	sf::Sound m_soundPlasma, m_soundJauge, m_soundEnd;
};


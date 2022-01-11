#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include <vector>
#include "Animator.h"
#include "SFML/Audio.hpp"

using namespace sf;

class Torche
{

public:

	Torche();
	~Torche();

	void Update(const float& dt);
	void Display(RenderWindow & app);
	void Change(const float& dt);
	void Rand_Pos();
	void Do_Lueur();
	bool  Get_Win() { return win; }

	void Go_debut(const float& dt);
	void Go_fin(const float& dt);

private:
	sf::SoundBuffer m_bufferTorche;
	sf::Sound m_soundTorche;

	Sprite fond;
	Sprite lueur;
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	Sprite sprite4;
	Sprite sprite5;
	Sprite sprite6;
	Sprite lueurwin;
	Sprite PorteClé;


	Sprite FBbouton;
	Vector2f PosMouse;
	Vector2f Poslueur;

	Animator anim;

	bool allumé1 = false;
	bool allumé2 = false;
	bool allumé3 = false;
	bool allumé4 = false;
	bool allumé5 = false;
	bool allumé6 = false;
	
	bool select1 = true;
	bool select2 = false;
	bool select3 = false;
	bool select4 = false;
	bool select5 = false;
	bool select6 = false;


	Vector2f Pos1;
	Vector2f Pos2;
	Vector2f Pos3;
	Vector2f Pos4;
	Vector2f Pos5;
	Vector2f Pos6;

	Vector2f PosStock1;
	Vector2f PosStock2;
	Vector2f PosStock3;
	Vector2f PosStock4;
	Vector2f PosStock5;
	Vector2f PosStock6;
	int random = 0;
	int random2 = 0;
	bool tableau[6];
	int compteur = 0;
	bool win = false;
	bool prewin = false;
	float timer_cligne = 0.f;
	float timer_fin = 0.f;
	float timer_anim = 0.f;
	float timer_change = 0.f;
	bool debut = true;
	float posy = 1080;
};



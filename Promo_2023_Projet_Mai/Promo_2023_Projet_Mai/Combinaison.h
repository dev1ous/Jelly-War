#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include <vector>
#include <random>
#include "Animator.h"
#include "SFML/Audio.hpp"

using namespace sf;


class Bouton
{
public:

	Bouton() = default;
	Bouton(int _type, sf::Vector2f _pos);
	~Bouton();

	void Update(const float& dt);
	Sprite Get_Sprite() { return sprite; }
	Vector2f Get_Pos() { return Pos; }
	bool Get_Reussi() { return reussi; }
	bool Get_Erreur() { return erreur; }
	bool Get_First() { return first; }
	void Set_Texture(Texture* texture) { sprite.setTexture(*texture); }
	void Set_Position(Vector2f _pos) { Pos.x = _pos.x; Pos.y = _pos.y; }
	void Set_Reussi() { reussi = false; }
	void Reset_timer() { timer = 0; }
	void Reset_erreur() { erreur = false; }
	void Set_First(bool _first) { first = _first; }
	void Display(RenderWindow& app);
	void Cligne();


private:

	sf::SoundBuffer m_bufferReussi;
	sf::Sound m_soundReussi;
	Sprite sprite;

	int type;
	Vector2f Pos;
	bool reussi = false;
	bool first = false;
	bool erreur = false;
	float timer = 0.f;
	float timer_grosfb = 0.f;
	bool win = false;
};

class Combinaison
{
public:

	Combinaison();
	~Combinaison();

	void Update(const float& dt);
	void Set_Position(Vector2f _pos) { Pos.x = _pos.x; Pos.y = _pos.y; }
	void Display(RenderWindow & app);
	void New_Combinaison(); 
	void Fin_Classe(const float& dt);
	void IsFirst();
	void Win(const float& dt);

	bool Get_Win() { return win; }
	template<typename R>
	int RandomSpeed(R&& r)
	{
		std::uniform_int_distribution<> dist{ 1 ,4 };
		return int(dist(std::forward<R>(r)));
	}

	void Feedback();
	void Remplir(const float& dt);
	void Go_debut(const float& dt);
	void Go_fin(const float& dt);

private:
	sf::SoundBuffer m_bufferRate, m_bufferRemplissage, m_bufferReussi;
	sf::Sound m_soundRate, m_soundRemplissage, m_soundReussi;

	Sprite sprite;
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	Sprite sprite4;
	
	Sprite eau1;
	Sprite eau2;
	Sprite eau3;

	Sprite eau1_1;
	Sprite eau2_2;
	Sprite eau3_3;

	Sprite eau1_1_1;
	Sprite eau2_2_1;
	Sprite eau3_3_1;


	Sprite tuyau;
	Sprite Porteclé;
	Sprite Demarrage;
	Vector2f Pos;
	int type;
	int random;
	bool one_pass = true;
	int compteur_win = 0;
	std::vector<Bouton> boutons; 
	std::mt19937 RandInt{ std::random_device{}() };
	bool win = false;
	bool fb = false;
	float timer_fb = 0.f;
	int compteur_fb = 0;
	int go_eau = 0;
	bool go_fin = false;
	bool fin_c = true;
	float timer_fin = 0.16f;
	float timer_win = 0.f;
	int compteur_fin = 0;
	float color = 0.f;


	Vector2f Pos1;
	Vector2f Pos2;
	Vector2f Pos3;

	Vector2f Pos1_1;
	Vector2f Pos2_2;
	Vector2f Pos3_3;

	Vector2f Pos1_1_1;
	Vector2f Pos2_2_2;
	Vector2f Pos3_3_3;

	Animator anim;
	Animator anim_clé;
	float posy = 1080;
	bool debut = true;
};


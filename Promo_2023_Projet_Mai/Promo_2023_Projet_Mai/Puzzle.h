#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include <vector>
#include <random>
#include "Animator.h"
#include "SFML/Audio.hpp"

using namespace sf;

class Pieces
{
public :


	Pieces() = default;
	Pieces(int _id, sf::Vector2f _pos);
	~Pieces();

	void Update();
	void Set_Sprite(sf::Color color) { sprite.setColor(color); }
	sf::Sprite Get_Sprite() { return sprite; }
	sf::Vector2f Get_Pos() { return Pos; }
	sf::Vector2f Get_Pos_Base() { return Base_pos; }
	void SetColor(float alpha) { sprite.setColor(Color(255, 255, 255, static_cast<sf::Uint8>(alpha))); }
	void Set_Position(sf::Vector2f _pos) { Pos.x = _pos.x; Pos.y = _pos.y; }
	void Display(sf::RenderWindow& app);
private:

	sf::Sprite sprite;
	int id;
	sf::Vector2f Pos;
	sf::Vector2f Base_pos;
	

};

class Puzzle
{

public:

	Puzzle();
	~Puzzle();

	void Init();
	void Update(const float& dt);
	void Display(sf::RenderWindow& app);
	void Switch(const float& dt);
	void Win(const float& dt);
	bool Get_Win() { return win; }
	void smooth_switch(int i, const float& dt);
	void Go_debut(const float& dt);
	void Go_fin(const float& dt);

	template<typename R>
	int RandomSpeed(R&& r)
	{
		std::uniform_int_distribution<> dist{ 5 ,15 };
		return int(dist(std::forward<R>(r)));
	}


private:

	sf::SoundBuffer m_bufferPuzzle;
	sf::Sound m_soundPuzzle;
	sf::SoundBuffer m_BufferEndPuzzle;
	sf::Sound m_SoundEndPuzzle;

	std::vector <Pieces> pieces;

	sf::Sprite Fond;

	sf::Sprite JolieAnim;
	sf::Sprite Ecran;
	sf::Sprite Joystick;

	Animator anim;
	Animator anim_joy;
	

	sf::Vector2f Pos1;
	sf::Vector2f Pos2;
	sf::Vector2f Pos3;
	sf::Vector2f Pos4;
	sf::Vector2f Pos5;
	sf::Vector2f Pos6;
	sf::Vector2f Pos7;
	sf::Vector2f Pos8;
	sf::Vector2f Pos9;

	sf::Vector2f PosMouse;
	bool tableau[9];
	float timer_switch = 2.f;
	int random = 0;
	bool go_random = false;
	bool one_pass = true;
	int compteur = 0;
	bool go_switch = false;
	int id = 0;
	int soluce;
	std::mt19937 RandInt{ std::random_device{}() };
	bool win = false;
	float color = 0;
	bool go_anim = false;
	float timer_win = 0.f;
	bool debut = true;
	float posy = 1080;
	float alpha = 0;
};


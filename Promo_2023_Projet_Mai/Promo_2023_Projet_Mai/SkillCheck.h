#ifndef SKILLCHECK_H
#define SKILLCHECK_H

#include "WindowManager.h"
#include <random>
#include "SFML/Audio.hpp"

class SkillCheck
{
public:

	enum class direction : char { droite, gauche };

	template<typename Random>
	direction RandomDir(Random&& r)
	{
		std::uniform_int_distribution<> dist{ static_cast<int>(direction::droite),static_cast<int>(direction::gauche) };
		return direction(dist(std::forward<Random>(r)));
	}

	template<typename Rand>
	float RandomTimer(Rand&& r)
	{
		std::uniform_real_distribution<float> dist{ 0.5f,1.5f };
		return float(dist(std::forward<Rand>(r)));
	}

	template<typename R>
	int RandomSpeed(R&& r)
	{
		std::uniform_int_distribution<> dist{ 20 ,50 };
		return int(dist(std::forward<R>(r)));
	}

	constexpr int GetSpeed()const { return m_Speed; }

	void InitSkillCheck();
	void RunSkillCheck(const float&);
	void MovingSkillCheckBar(const float&);
	void GenerateRandomMove(const float&);
	void Progression(const float&);
	void AnimProgressBar(const float&);
	void drawBars(WindowManager&);
	void Go_debut(const float& dt);
	void Go_fin(const float& dt);


	bool Get_Win() { return win; }


private:

	direction m_Dir;

	sf::Sprite m_separate;
	sf::Sprite m_SpriteSkillCheckBar;
	sf::RectangleShape m_SkillCheckBar;
	sf::RectangleShape m_ProgressBar;
	sf::RectangleShape m_MovingBar;
	sf::Sprite m_OtherBar;
	sf::IntRect m_rectProgressBar{ 0,0,0,65 };
	sf::Sprite m_ProgressionOtherBar;
	sf::Sprite m_ecran;
	sf::RectangleShape m_fond;
	sf::Sprite m_feedBack, m_feedBack_A, m_feedBackLumineux_A;

	std::mt19937 m_RngDir{ std::random_device{}() };
	std::mt19937 m_RngTimer{ std::random_device{}() };
	std::mt19937 m_RngSpeed{ std::random_device{}() };

	float m_timerRect{ 0.f };
	float m_velocity{ 50.f };
	float m_multiplier{ 12.f };
	float m_decreaser{ 12.f };
	float m_multiplierMovingBox{ 10.f };
	int m_Speed;
	float m_Timer;
	float m_CurrentScore{ 0.f };
	float m_ScoreNeeded{ 100.f };
	bool m_SwitchDir{ false };
	
	bool debut = true;
	float posy = 1080;
	bool win = false;
	bool fin = false;

	sf::SoundBuffer m_bufferSkillCheck;
	sf::Sound m_soundSkillCheck;
};
#endif


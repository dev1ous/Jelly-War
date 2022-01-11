#pragma once
#include "Joueur.h"
#include <vector>
#include "SFML/Audio.hpp"

class Projectiles_BR;
class Network;

class BR_Joueur : public Joueur
{

public:

	BR_Joueur();
	~BR_Joueur();

	virtual void Controle(const float& dt);
	void Controles(const float& dt, std::vector< Projectiles_BR>& projectiles, Network* network, bool focus);
	virtual void Interaction(std::map<int, Joueur*>& joueurs);
	virtual void Update(const float& dt, sf::Image& image) {}
	virtual void Display(WindowManager& window);
	void Update(const float& dt, sf::Image& image, std::vector< Projectiles_BR>& projectiles, Network* network, bool focus);

	void setInvinsible(bool b);
	void setScore(int score);

	bool is_invincible() const { return invinsible; }
	int Get_score() { return score; }
	int Get_ID() { return id; }
	void Go_invisible(const float& dt);
	void SetColor(Couleur color) override;
	void Set_Classement(int c) { classement = c; }
	int Get_Classement() { return classement; }
	float Get_Angle() { return angle; }
	void setAngle(float _angle) { angle = _angle; Sprite.setRotation(angle);}
	void Set_spawn();
	sf::Vector2f Get_Velocité() { return Velocity; }

	void Display_Inv(WindowManager& window, bool inv);
	void Display_Victoire(WindowManager& window);
private:

	sf::SoundBuffer m_bufferTir;
	sf::Sound m_soundTir;

	sf::Sprite m_arrow;
	float angle{ 0.f };
	float speed = 350.f;
	int score = 0;
	int id = 0;
	bool invinsible = false;
	int classement = 0;
	float timer_invinsible = 0.f;
	float timer_IsInvinsible = 0.f;
	float timer_tir = 0.f;
	Animator anim;

	
	sf::Sprite tete;
};
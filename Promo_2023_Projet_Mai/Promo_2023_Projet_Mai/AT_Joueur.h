#pragma once
#include "Joueur.h"
#include "Network.h"

using namespace sf;

class AT_Joueur :
	public Joueur
{
private:
	int color;
	bool canScore{ true };
	long score{ 0 };

	Texture shapeTexture;
	RectangleShape shape;
	CircleShape hitbox;

	bool isAlive{ true };
	float speed{ 300.f };

	float angle{ 0.0f };
	float prevAngle{ 0.0f };

	float timerInteract{ 0.0f };

	bool catchPrevVel{ false };

	sf::SoundBuffer m_bufferAT;
	sf::Sound m_soundAT;
	sf::SoundBuffer m_bufferATCol;
	sf::Sound m_soundATCol;
public:
	AT_Joueur(Vector2f _pos, int _color);
	~AT_Joueur() = default;

	virtual void Interaction(std::map<int, Joueur*>& joueurs, const float& dt, Network*);
	virtual void Controle(const float& dt, bool focus);
	virtual void Update(const float& dt, CircleShape& bounds, bool focus);
	virtual void Display(WindowManager& window);

	void UpdateMouvement(const float& dt);
	bool IsDead(CircleShape& bounds);
	bool IsAlive() { return isAlive; }

	inline Vector2f GetVelocity() { return this->Velocity; }
	inline Vector2f const GetPosition() const { return this->shape.getPosition(); }
	inline float GetRadius() { return this->hitbox.getRadius(); }
	inline CircleShape GetHitBox() { return this->hitbox; }
	inline void Moveshape(sf::Vector2f move) { shape.move(move); }
	float Get_Angle() { return angle; }
	int GetColor() { return color; }
	int GetScore() { return score; }

	inline void SetPosition(Vector2f _pos) { this->shape.setPosition(_pos); this->hitbox.setPosition(_pos); }
	inline void SetVelocity(Vector2f _vel) { this->Velocity = _vel; }
	inline void addVelocity(Vector2f _vel) { this->Velocity += _vel; }
	inline void SetAlive(bool _alive) { this->isAlive = _alive; }
	void setAngle(float _angle) { angle = _angle; shape.setRotation(angle); }
	void AddScore(int _score) {
		if (canScore)
			score -= _score;
	};
	void Set_Score(int _score) { score = _score; }
};
#pragma once
#include "SFML/Graphics.hpp"
#include "WindowManager.h"
#include "Animator.h"
#include <map>

class Joueur
{
public:
	enum class Couleur
	{
		One = 1,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Height,
		None
	};
	enum class Direction { None, Top, Bot, Left, Right };

protected:
	sf::Sprite Sprite;
	sf::Vector2f Velocity;
	sf::RectangleShape Hitbox;
	std::map<std::string, Animator> Anim;
	int Id{ 0 };
	Direction m_dir{ Direction::Right };

	Couleur MyColor{ Couleur::One };
	bool ColDroite{ false };
	bool ColGauche{ false };
	bool ColHaut{ false };
	bool ColBas{ false };


	void Get_NextPos(const float& dt, sf::Image& image);
	bool CheckCollid(sf::Vector2f _pos, sf::Image& image);

public:
	Joueur() = default;
	~Joueur() = default;

	inline void SetPos(sf::Vector2f pos) {
		Sprite.setPosition(pos);
		Hitbox.setPosition(pos);
	}

	void setVelocity(sf::Vector2f vel) { Velocity = vel; }
	void SetScale(float x, float y) { Sprite.setScale(x, y); }
	void SetTextureRect(sf::IntRect rect) { Sprite.setTextureRect(rect); }
	virtual void SetColor(Couleur color) { MyColor = color; }
	inline bool GetIddle() { return Velocity == sf::Vector2f(0, 0); }
	inline sf::Vector2f GetScale() { return Sprite.getScale(); }
	const sf::Vector2f& getSpriteCenter() const;
	inline void Move() { Sprite.move(Velocity); }
	inline void Move(sf::Vector2f move) { Sprite.move(move); }

	inline sf::RectangleShape& GetHitbox() { return Hitbox; }
	inline sf::Sprite& GetSprite() { return Sprite; }
	inline const sf::Vector2f& GetVelocity() const { return Velocity; }
	inline const sf::Vector2f& GetPos() const { return Sprite.getPosition(); }
	inline const sf::IntRect& GetTextureRect() const { return Sprite.getTextureRect(); }
	const Couleur getcolor() const { return MyColor; }
	inline Direction GetDir() const { return m_dir; }

	template<class ...Args>
	void Controle(Args&&...);
	template<class ...Args>
	void Update(Args&&...);
	virtual void Animation(const float& dt) {};
	template<class ...Args>
	void Display(WindowManager& window, Args&&...);
};

template<class ...Args>
inline void Joueur::Controle(Args&& ...args)
{
	Controle(std::forward<Args>(args)...);
}

template<class ...Args>
inline void Joueur::Update(Args&& ...args)
{
	Update(std::forward<Args>(args)...);
}

template<class ...Args>
inline void Joueur::Display(WindowManager& window, Args&& ...args)
{
	Display(window, std::forward<Args>(args)...);
}
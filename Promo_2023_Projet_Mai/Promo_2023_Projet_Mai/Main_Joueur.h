#pragma once
#include "Joueur.h"
#include "ManagerBonus.h"
#include "Map.h"
#include <array>
#include "Feedback.h"
#include "WindowManager.h"
#include <list>
#include "SFML/Audio.hpp"

using Draw = std::list<std::pair<bool, sf::Sprite*>>;

class Hud_MainGame;
class Network;

class Main_Joueur final : public Joueur
{
public:
	enum class Statut
	{
		Check,
		Etourdit,
		Enerver,
		Diabolique,
		Fausse_Ressources,
		faux_Bonus,
		Contre_Tacle,
		Ralenti,
		Axe_Inversé
	};

private:
	std::vector<Bonus> MyBonus;

	sf::Vector2f CurrentSpeed{ 0,0 };

	bool Tacle{ false };
	float TimerTacle{ 0 };

	bool UseBonus{ false };
	float TimerUseBonus{ 0 };

	bool Check{ false };
	float TimerCheck{ 0 };
	float Speed{ 1 };

	float Invulnérable{ 0 };
	bool Tp{ false };

	float Slow{ 1 };
	bool onepass{ false };

	int classement{ 1 };
	float SeeOthersTimer{ 0.f };

	std::array<float, 3> ressources;
	std::map<Statut, std::pair<Feedback, float>> FeedBacks;

	sf::SoundBuffer m_bufferTacle, m_bufferCheck;
	sf::SoundBuffer m_bufferAntiTacle, m_bufferAntiCheck;
	sf::SoundBuffer m_bufferTp, m_bufferslow, m_bufferConfusion;
	sf::SoundBuffer m_bufferMove;

	sf::Sound m_SoundTacle, m_SoundCheck;
	sf::Sound m_soundAntiTacle, m_soundAntiCheck;
	sf::Sound m_soundTp, m_soundslow, m_soundConfusion;
	sf::Sound m_soundMove;


	float m_progress{ 0.f };

	void Get_NextPos2(const float& dt, sf::Image& image, Map& map);

public:
	Main_Joueur();
	~Main_Joueur() = default;

	enum class Looking { Left, Right, Up, Down } m_look{ Looking::Right };

	Map::Nodes* LookingAt(Map& map, const float& dt);

	void setOrigin() { Sprite.setOrigin(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height - Hitbox.getSize().y / 2); }
	void addRessource(const unsigned short type, const float toAdd) { ressources[type] = std::clamp(ressources[type] + toAdd, 0.f, 100.f); }
	const float getRessource(const unsigned short type) const { return ressources[type]; }
	const float getProgress() const { return m_progress; }
	void setProgress(float _progress) { m_progress = _progress; }

	inline void SetTacle(bool _tacle) { Tacle = _tacle; }
	inline bool GetTacle() { return Tacle; }
	inline bool GetTp() { return Tp; }
	inline const sf::Vector2f& GetSpeed()const { return CurrentSpeed; }
	inline void DeleteBonus() { MyBonus.erase(MyBonus.begin()); }

	inline bool GetEtourdit() { return FeedBacks.find(Statut::Etourdit) != FeedBacks.end(); }

	void restartClassement() { classement = 1; }
	void addclassement() { classement++; }
	int GetClassement() { return classement; }

	void SetFeedback(Statut feedback);

	inline void SetUseBonus(bool _usebonus) { UseBonus = _usebonus; }
	inline bool GetUseBonus() { return UseBonus; }

	inline void SetCheck(bool _check) { Check = _check; }
	inline bool GetCheck() { return Check; }

	void SetColor(Couleur color) override;

	inline std::vector<Bonus>& GetMyBonus() { return MyBonus; }
	Bonus& GetFirstBonus();
	void SetBonus(Bonus::Type first);

	void InteractionBonus(std::list<Bonus>& bonus, Draw& Drawable, sf::Sprite& m_BonusExplication, float& m_BonusExplication_timer, const bool effect = true);

	void Interaction(std::map<int, Joueur*>& joueurs);
	void Controle(const float& dt, Network* network, ManagerBonus& bonus, Draw& Drawable);
	void Update(const float& dt, sf::Image& image, Map& map);
	void Animation(const float& dt);
	void FeedBackAnim(const float& dt);
	bool SeeOthers() const { return SeeOthersTimer > 0.f; }
	void DisplayFeedback(WindowManager& window);
};
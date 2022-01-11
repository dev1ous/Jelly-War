#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "WindowManager.h"
#include "Feedback.h"
#include "AssetManager.h"
#include <list>

using Draw = std::list<std::pair<bool, sf::Sprite*>>;

const float TimerRestart = 60.f;

class Main_Joueur;
class Network;
class FSM_Manager;
class Game;

class Map
{
public:
	Map(AssetManager& assets, Draw& Drawable);

	class Nodes
	{
	public:
		int type{ 0 };
		sf::Sprite Minerais;
		sf::Sprite Beam;
		sf::Sprite machine_sprite;
		sf::Sprite machine_fx_sprite;

		Animator machine_anim_spawn;
		Animator machine_anim;

		Animator machine_fx_anim_spawn;
		Animator machine_fx_anim;

		Animator Ressources_anim;
		Animator Rayon_anim;

		sf::Vector2f BasePos;
		sf::Vector2f offset_anim;
		sf::Vector2f offset_anim_spawn;
		sf::Vector2f offset_fx_anim_spawn;
		sf::Vector2f offset_beam;

		Main_Joueur* owner{ nullptr };
		Feedback Boost;
		float TimerBoost{ 0 };
		bool Bonus{ false };

		void Display(WindowManager& window);
	};

	class BoutonMG
	{
	public:
		float timer{ TimerRestart };
		sf::Sprite sprite;
		sf::IntRect Rect{ 0,0,170,280 };
		bool Ready{ false };

		float timerminijeu{ 0 };
		bool start{ false };

		void operator=(BoutonMG& b) {
			Ready = b.Ready;
			Rect = b.Rect;
			timer = b.timer;
			timerminijeu = b.timerminijeu;
			start = b.start;
		}
	};

private:
	sf::Image m_cols;
	std::list<Nodes> m_nodesGenerated;
	sf::SoundBuffer SBboost;
	sf::Sound Sboost;

	int Minijeu{ 1 };

public:
	BoutonMG BoutonGame;
	sf::Image& getImage() { return m_cols; }
	Nodes* getNode(sf::Vector2f pos);
	std::list<Nodes>& getNodes() { return m_nodesGenerated; }

	void ResetBouton();
	void AddtrapsRessource(sf::Vector2f pos, Draw& Drawable, Main_Joueur* joueur);
	void RemoveTrapsRessources(sf::Vector2f pos, Draw& Drawable);
	void ChangeTexture();
	void ReceiveBonus(Main_Joueur* joueur, std::map<int, Main_Joueur*> others);
	void UpdateBouton(const float& dt, Main_Joueur* joueur, Network* network,
		FSM_Manager& fsm, Game& game);
	void Update(float dt);
	void DisplayTimer(WindowManager& window, sf::Font& font);
	void display(WindowManager& window);
};
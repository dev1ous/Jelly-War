#pragma once
#include "Main_Joueur.h"
#include "WindowManager.h"
#include "Feedback.h"

class Hud_MainGame
{
private:
	sf::Sprite Fond[3];
	sf::Sprite Y;
	sf::Sprite BoutonReady;
	sf::Sprite BoutonStart;
	bool start{ false };

	sf::Sprite m_plasmaBar;
	sf::Sprite m_liquideBar;
	sf::Sprite m_crystalBar;

	sf::Sprite interaction[2];
	sf::Sprite touche[2];

	sf::Sprite ResFull[3];

	sf::RectangleShape Minimap;

	Main_Joueur* Joueur;

	Feedback AnnonceMinijeu;
	sf::Sprite CurrentPlayer;
	sf::Sprite FirstPlayer;
	sf::Sprite TmpPlayer;
	Joueur::Couleur couleur[2];

	void RecupTexture(Joueur::Couleur couleur,
		sf::Sprite& sprite);

public:
	Hud_MainGame(Main_Joueur* joueur);
	~Hud_MainGame() = default;

	void SetTextureMinimap(const sf::Texture* texture) { Minimap.setTexture(texture); }

	void SetCurrentPlayer(Joueur::Couleur currentplayer);
	void SetFirstPlayer(Joueur::Couleur firstplayer);

	void Update(const float& dt, Map::BoutonMG& bouton);
	void Display(WindowManager& window);
};
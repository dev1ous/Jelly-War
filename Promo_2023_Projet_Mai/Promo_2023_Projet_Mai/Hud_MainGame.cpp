#include "Hud_MainGame.h"
#include "Cache.h"

Hud_MainGame::Hud_MainGame(Main_Joueur* joueur)
	: Joueur{ joueur }
{
	Fond[0].setTexture(Cache::GetRessources<sf::Texture>("HUD_joueur_" + std::to_string((int)joueur->getcolor())));
	Fond[1].setTexture(Cache::GetRessources<sf::Texture>("tete_1"));
	Fond[2].setTexture(Cache::GetRessources<sf::Texture>("mini_map_" + std::to_string((int)joueur->getcolor())));

	Fond[2].setPosition(1920 - Fond[2].getGlobalBounds().width, 0);
	Fond[1].setPosition(Fond[2].getPosition().x, 0);

	BoutonStart.setTexture(Cache::GetRessources<sf::Texture>("banderole"));
	BoutonStart.setPosition(-BoutonStart.getGlobalBounds().width, 250);

	SetCurrentPlayer(Joueur::Couleur::One);
	SetFirstPlayer(Joueur::Couleur::One);
	BoutonReady.setTexture(Cache::GetRessources<sf::Texture>("bouton_eteint"));
	BoutonReady.setPosition(1920 - BoutonReady.getGlobalBounds().width, Fond[2].getGlobalBounds().height - 70);

	Minimap.setSize({ 275, 275 });
	Minimap.setPosition(Fond[2].getPosition().x + 27, 0);

	Cache::GetRessources<sf::Texture>("Y hud").setSmooth(true);
	Y.setTexture(Cache::GetRessources<sf::Texture>("Y hud"));
	Y.setPosition(127, 239);
	Y.setScale(0.5f, 0.5f);

	AnnonceMinijeu = Feedback("notif_minijeu", { 1920 - 190, BoutonReady.getPosition().y},
		sf::IntRect(0, 0, 400, 250), 19, 3.f / 19.f, 250);
	AnnonceMinijeu.End();
	AnnonceMinijeu.Animation({ 960,0 }, 0.f);

	m_plasmaBar.setTexture(Cache::GetRessources<sf::Texture>("palsma_bar"));
	m_liquideBar.setTexture(Cache::GetRessources<sf::Texture>("liquide_bar"));
	m_crystalBar.setTexture(Cache::GetRessources<sf::Texture>("crystal_bar"));

	m_plasmaBar.setTextureRect(sf::IntRect(0, 0, 0, static_cast<int>(m_plasmaBar.getGlobalBounds().height)));
	m_liquideBar.setTextureRect(sf::IntRect(0, 0, 0, static_cast<int>(m_liquideBar.getGlobalBounds().height)));
	m_crystalBar.setTextureRect(sf::IntRect(0, 0, 0, static_cast<int>(m_crystalBar.getGlobalBounds().height)));

	m_plasmaBar.setPosition(176, 34);
	m_liquideBar.setPosition(176, 61);
	m_crystalBar.setPosition(176, 93);

	ResFull[0].setTexture(Cache::GetRessources<sf::Texture>("light_verte"));
	ResFull[0].setOrigin(ResFull[0].getGlobalBounds().width / 2, ResFull[0].getGlobalBounds().height / 2);
	ResFull[0].setPosition(468.f, m_plasmaBar.getPosition().y + m_plasmaBar.getGlobalBounds().height / 2);

	ResFull[1].setTexture(Cache::GetRessources<sf::Texture>("light_rose"));
	ResFull[1].setOrigin(ResFull[1].getGlobalBounds().width / 2, ResFull[1].getGlobalBounds().height / 2);
	ResFull[1].setPosition(468.f, m_liquideBar.getPosition().y + m_liquideBar.getGlobalBounds().height / 2);

	ResFull[2].setTexture(Cache::GetRessources<sf::Texture>("light_bleu"));
	ResFull[2].setOrigin(ResFull[2].getGlobalBounds().width / 2, ResFull[2].getGlobalBounds().height / 2);
	ResFull[2].setPosition(468.f, m_crystalBar.getPosition().y + m_crystalBar.getGlobalBounds().height / 2);

	interaction[0].setTexture(Cache::GetRessources<sf::Texture>("tacle"));
	interaction[0].setPosition(25, 825);
	interaction[1].setTexture(Cache::GetRessources<sf::Texture>("check"));
	interaction[1].setPosition(125, 925);

	touche[0].setTexture(Cache::GetRessources<sf::Texture>("B_"));
	touche[0].setOrigin(touche[0].getGlobalBounds().width / 2, touche[0].getGlobalBounds().height / 2);
	touche[0].setScale(0.5f, 0.5f);
	touche[0].setPosition(interaction[0].getPosition() + sf::Vector2f(100, 100));

	touche[1].setTexture(Cache::GetRessources<sf::Texture>("X_"));
	touche[1].setOrigin(touche[1].getGlobalBounds().width / 2, touche[1].getGlobalBounds().height / 2);
	touche[1].setScale(0.5f, 0.5f);
	touche[1].setPosition(interaction[1].getPosition() + sf::Vector2f(100, 100));
}

void Hud_MainGame::RecupTexture(Joueur::Couleur couleur, sf::Sprite& sprite)
{
	sf::Sprite tmp;
	switch (couleur)
	{
	case Joueur::Couleur::One:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("gudublob"));
		break;
	case Joueur::Couleur::Two:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("belzeblob"));
		break;
	case Joueur::Couleur::Three:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("tahiti_blob"));
		break;
	case Joueur::Couleur::Four:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("blobillon"));
		break;
	case Joueur::Couleur::Five:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("blobic"));
		break;
	case Joueur::Couleur::Six:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("mamiblob"));
		break;
	case Joueur::Couleur::Seven:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("arliblob"));
		break;
	case Joueur::Couleur::Height:
		sprite.setTexture(Cache::GetRessources<sf::Texture>("lapiblob"));
		break;
	}

	sprite.setOrigin(61, 61);
	sprite.setTextureRect({ 0,0,122,122 });
}

void Hud_MainGame::SetCurrentPlayer(Joueur::Couleur currentplayer)
{
	if (couleur[1] != currentplayer) {
		couleur[1] = currentplayer;
		RecupTexture(currentplayer, CurrentPlayer);
		CurrentPlayer.setPosition({ 95,115 });

		Fond[0].setTexture(Cache::GetRessources<sf::Texture>("HUD_joueur_" + std::to_string((int)currentplayer)));
		Fond[2].setTexture(Cache::GetRessources<sf::Texture>("mini_map_" + std::to_string((int)currentplayer)));
		CurrentPlayer.setPosition(92, 92);
	}
}

void Hud_MainGame::SetFirstPlayer(Joueur::Couleur firstplayer)
{
	if (couleur[0] != firstplayer) {
		couleur[0] = firstplayer;
		RecupTexture(firstplayer, TmpPlayer);
		TmpPlayer.setPosition({ Fond[1].getPosition().x + 125,92 });
	}
}

void Hud_MainGame::Update(const float& dt, Map::BoutonMG& bouton)
{
	if (bouton.Ready) {
		BoutonReady.setTexture(Cache::GetRessources<sf::Texture>("bouton_allume"));

		if (AnnonceMinijeu.Get_Frame() < 20) {
			AnnonceMinijeu.Animation_NoRestart({ 1920 - 190, BoutonReady.getPosition().y }, dt);
		}
	}
	else {
		if (AnnonceMinijeu.Get_Frame() > 19) {
			AnnonceMinijeu.Restart_Anim();
		}

		BoutonReady.setTexture(Cache::GetRessources<sf::Texture>("bouton_eteint"));
	}

	if (start != bouton.start)
		start = bouton.start;

	if (start) {
		if (BoutonStart.getPosition().x + BoutonStart.getGlobalBounds().width / 2 < 960)
			BoutonStart.move(sf::Vector2f(800 * dt, 0));
	}
	if (!start) {
		BoutonStart.setPosition(-BoutonStart.getGlobalBounds().width, 250);
	}

	if (TmpPlayer.getTexture() != FirstPlayer.getTexture()) {
		Fond[1].move(100.f * dt, 0);

		if (Fond[1].getPosition().x > Fond[2].getPosition().x) {
			FirstPlayer = TmpPlayer;
			Fond[1].setTexture(Cache::GetRessources<sf::Texture>("tete_" + std::to_string((int)couleur[0])));
		}

		FirstPlayer.setPosition(Fond[1].getPosition().x + 125, 92);
	}
	else if (Fond[1].getPosition().x > Fond[2].getPosition().x - Fond[1].getGlobalBounds().width) {
		Fond[1].move(-100.f * dt, 0);
		FirstPlayer.setPosition(Fond[1].getPosition().x + 125, 92);
	}

	CurrentPlayer.setTextureRect(sf::IntRect(122 * (Joueur->GetClassement() - 1), 0, 122, 122));

	m_plasmaBar.setTextureRect(sf::IntRect(0, 0, static_cast<int>(262.f * std::clamp((Joueur->getRessource(2) / 100.f), 0.f, 1.f)), static_cast<int>(m_plasmaBar.getGlobalBounds().height)));
	m_liquideBar.setTextureRect(sf::IntRect(0, 0, static_cast<int>(260.f * std::clamp((Joueur->getRessource(0) / 100.f), 0.f, 1.f)), static_cast<int>(m_liquideBar.getGlobalBounds().height)));
	m_crystalBar.setTextureRect(sf::IntRect(0, 0, static_cast<int>(260.f * std::clamp((Joueur->getRessource(1) / 100.f), 0.f, 1.f)), static_cast<int>(m_crystalBar.getGlobalBounds().height)));

	for (int i = 0; i < Joueur->GetMyBonus().size(); i++) {
		if (i == 0) {
			Joueur->GetMyBonus()[i].SetPos({ 128.f, 218.f });
			Joueur->GetMyBonus()[i].SetScale({ 1.f,1.f });
		}
		if (i == 1) {
			Joueur->GetMyBonus()[i].SetPos({ 235.f, 174.5f });
			Joueur->GetMyBonus()[i].SetScale({ 0.75f,0.75f });
		}
		if (i == 2) {
			Joueur->GetMyBonus()[i].SetPos({ 326.f, 175.f });
			Joueur->GetMyBonus()[i].SetScale({ 0.75f,0.75f });
		}
	}
}

void Hud_MainGame::Display(WindowManager& window)
{
	window.draw(m_plasmaBar);
	window.draw(m_liquideBar);
	window.draw(m_crystalBar);

	window.draw(FirstPlayer);
	window.draw(Fond[1]);

	for (int i = 0; i < Joueur->GetMyBonus().size(); i++)
		Joueur->GetMyBonus()[i].Display(window);

	for (int i = 0; i < 2; i++) {
		window.draw(interaction[i]);
		window.draw(touche[i]);
	}


	window.draw(CurrentPlayer);
	if (Joueur->getRessource(0) == 100.f) {
		window.draw(ResFull[1]);
	}
	if (Joueur->getRessource(1) == 100.f) {
		window.draw(ResFull[2]);
	}
	if (Joueur->getRessource(2) == 100.f) {
		window.draw(ResFull[0]);
	}
	window.draw(Fond[0]);

	if (AnnonceMinijeu.Get_Frame() < 20)
		window.draw(AnnonceMinijeu.GetSprite());
	window.draw(Minimap);
	window.draw(BoutonReady);
	window.draw(Fond[2]);

	window.draw(Y);

	if (start) {
		window.draw(BoutonStart);
	}
}
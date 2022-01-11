#include "Combinaison.h"
#include "Cache.h"
#include "Gamepad.h"
#include "Options.h"

Bouton::Bouton(int _type,Vector2f _pos): type(_type), Pos(_pos)
{
	if (type == 1)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("A"));
	}
	else if (type == 2)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("B"));
	}
	else if (type == 3)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("X"));
	}
	else if (type == 4)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("Y"));
	}

	sprite.setTextureRect(IntRect(0, 0, 135, 135));
	sprite.setPosition(Pos);

	m_bufferReussi.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/CombinaisonLiquide/Reussi.wav");
	m_soundReussi.setBuffer(m_bufferReussi);
}

Bouton::~Bouton()
{
}

void Bouton::Update(const float& dt)
{ 
	m_soundReussi.setVolume(Options::volumeBruitages);

	timer_grosfb += dt;

	Gamepads g;


	if (g.on_pressed(0, Xbox::A) && first)
	{
		if (type == 1)
		{
			m_bufferReussi.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/CombinaisonLiquide/Reussi.wav");
			m_soundReussi.setBuffer(m_bufferReussi);
			m_soundReussi.play();
			reussi = true;
		}
		else
		{
			erreur = true;
		}
		
	}
	else if (g.on_pressed(0, Xbox::B) && first)
	{
		if (type == 2)
		{
			m_bufferReussi.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/CombinaisonLiquide/Reussi.wav");
			m_soundReussi.setBuffer(m_bufferReussi);
			m_soundReussi.play();
			reussi = true;
		}
		else
		{
			erreur = true;
		}
	}
	else if (g.on_pressed(0, Xbox::X) && first )
	{
		if (type == 3)
		{
			m_bufferReussi.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/CombinaisonLiquide/Reussi.wav");
			m_soundReussi.setBuffer(m_bufferReussi);
			m_soundReussi.play();
			reussi = true;
		}
		else
		{
			erreur = true;
		}
	}
	else if (g.on_pressed(0, Xbox::Y) && first )
	{
		if (type == 4)
		{
			m_bufferReussi.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/CombinaisonLiquide/Reussi.wav");
			m_soundReussi.setBuffer(m_bufferReussi);
			m_soundReussi.play();
			reussi = true;
		}
		else
		{
			erreur = true;
		}
	}

	sprite.setPosition(Pos);

}

void Bouton::Display(RenderWindow& app)
{
	if (!win)
	{
		if (reussi)
		{
				
			sprite.setTextureRect(IntRect(135, 0, 135, 135));

		}
		else
		{
			sprite.setTextureRect(IntRect(0, 0, 135, 135));

		}
	}

	app.draw(sprite);
}

void Bouton::Cligne()
{
	win = true;

	if (timer_grosfb > 0.2f)
	{
		timer_grosfb = 0.f;

	}

	if (timer_grosfb < 0.1f)
	{
		sprite.setTextureRect(IntRect(135, 0, 135, 135));
	}
	else if (timer_grosfb >= 0.1f)
	{
		sprite.setTextureRect(IntRect(0, 0, 135, 135));

	}

}




Combinaison::Combinaison()
{
	m_bufferRate.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/CombinaisonLiquide/Rate.wav");
	m_soundRate.setBuffer(m_bufferRate);
	m_bufferRemplissage.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/CombinaisonLiquide/Remplissage.wav");
	m_soundRemplissage.setBuffer(m_bufferRemplissage);


	Pos.x = 500.f;
	Pos.y = 380.f;
	
	sprite.setTexture(Cache::GetRessources<sf::Texture>("MiniQTE"));

	sprite1.setTexture(Cache::GetRessources<sf::Texture>("petita"));
	sprite2.setTexture(Cache::GetRessources<sf::Texture>("petitb"));
	sprite3.setTexture(Cache::GetRessources<sf::Texture>("petitx"));
	sprite4.setTexture(Cache::GetRessources<sf::Texture>("petity"));

	eau1.setTexture(Cache::GetRessources<sf::Texture>("eau 1"));
	eau2.setTexture(Cache::GetRessources<sf::Texture>("eau 2"));
	eau3.setTexture(Cache::GetRessources<sf::Texture>("eau 3"));

	eau1_1.setTexture(Cache::GetRessources<sf::Texture>("eau 1"));
	eau2_2.setTexture(Cache::GetRessources<sf::Texture>("eau 2"));
	eau3_3.setTexture(Cache::GetRessources<sf::Texture>("eau 3"));

	eau1_1_1.setTexture(Cache::GetRessources<sf::Texture>("eau 1"));
	eau2_2_1.setTexture(Cache::GetRessources<sf::Texture>("eau 2"));
	eau3_3_1.setTexture(Cache::GetRessources<sf::Texture>("eau 3"));


	tuyau.setTexture(Cache::GetRessources<sf::Texture>("tuyaubas"));

	Porteclé.setTexture(Cache::GetRessources<sf::Texture>("porteclé"));

	Demarrage.setTexture(Cache::GetRessources<sf::Texture>("texte"));

	sprite1.setTextureRect(sf::IntRect(0, 0, 56, 57));
	sprite2.setTextureRect(sf::IntRect(0, 0, 64, 65));
	sprite3.setTextureRect(sf::IntRect(0, 0, 59, 59));
	sprite4.setTextureRect(sf::IntRect(0, 0, 61, 61));

	sprite1.setPosition(sf::Vector2f(288, 284));
	sprite2.setPosition(sf::Vector2f(284, 443));
	sprite3.setPosition(sf::Vector2f(1522, 281));
	sprite4.setPosition(sf::Vector2f(1520, 443));

	Pos1 = sf::Vector2f(500, 1080);
	Pos2 = sf::Vector2f(735, 1080);
	Pos3 = sf::Vector2f(1272, 1080);

	Pos1_1 = sf::Vector2f(500, 1446);
	Pos2_2 = sf::Vector2f(735, 1446);
	Pos3_3 = sf::Vector2f(1272, 1446);

	Pos1_1_1 = sf::Vector2f(500, 1812);
	Pos2_2_2 = sf::Vector2f(735, 1812);
	Pos3_3_3 = sf::Vector2f(1272, 1812);

	eau1.setPosition(500, 1080);
	eau2.setPosition(735, 1080);
	eau3.setPosition(1272, 1080);

	eau1_1.setPosition(500, 1446);
	eau2_2.setPosition(735, 1446);
	eau3_3.setPosition(1272, 1446);


	eau1_1_1.setPosition(500, 1812);
	eau2_2_1.setPosition(735, 1812);
	eau3_3_1.setPosition(1272, 1812);

	Demarrage.setPosition(703, 205);
	anim = Animator(sf::IntRect(0, 0, 1920, 1080), 3, 0.1f, sprite.getGlobalBounds().height, false);
	anim_clé = Animator(sf::IntRect(0, 0, 221, 158), 16, 0.1f, Porteclé.getGlobalBounds().height, false);

	Demarrage.setColor(sf::Color::Transparent);

	Porteclé.setPosition(1711, 795);
}

Combinaison::~Combinaison()
{

	
}

void Combinaison::Update(const float& dt)
{
	m_soundRate.setVolume(Options::volumeBruitages);
	m_soundRemplissage.setVolume(Options::volumeBruitages);


	timer_fb += dt;
	
	anim.Animation(sprite, dt);
	anim_clé.Animation(Porteclé, dt);
	if (!debut)
	{


		if (one_pass)
		{
			New_Combinaison();
			one_pass = false;
		}
		Win(dt);

		Remplir(dt);
		if (go_eau < 3)
		{
			if (boutons[5].Get_Reussi())
			{
				compteur_win++;
				fb = true;
				timer_fb = 0;
				go_eau++;
				New_Combinaison();
			}
		}

		if (go_eau != 3)
		{
			IsFirst();
			for (int i = 0; i < boutons.size(); i++)
			{
				boutons[i].Update(dt);
				if (boutons[i].Get_Erreur())
				{
					m_soundRate.play();
					for (int y = 0; y < boutons.size(); y++)
					{
						boutons[y].Set_Reussi();
						boutons[y].Set_First(false);
						boutons[y].Reset_timer();
						boutons[y].Reset_erreur();
					}

				}
			}			
		}
		else
		{
			for (int i = 0; i < boutons.size(); i++)
			{
				boutons[i].Cligne();
			}

			Fin_Classe(dt);
		}
		Feedback();
	}
	else
	{
		Go_debut(dt);
	}

}

void Combinaison::Display(RenderWindow& app)
{
	app.draw(Porteclé);

	app.draw(tuyau);

	

	app.draw(eau1);
	app.draw(eau2);
	app.draw(eau3);


	app.draw(eau1_1);
	app.draw(eau2_2);
	app.draw(eau3_3);


	app.draw(eau1_1_1);
	app.draw(eau2_2_1);
	app.draw(eau3_3_1);




	app.draw(sprite);

	app.draw(Demarrage);



	app.draw(sprite1);
	app.draw(sprite2);
	app.draw(sprite3);
	app.draw(sprite4);

	for (int i = 0; i < boutons.size(); i++)
	{
		boutons[i].Display(app);
		
	}

}

void Combinaison::New_Combinaison()
{
	Pos.x = 500.f;
	boutons.clear();
	for (int i = 0; i < 6; i++)
	{
		random = RandomSpeed(RandInt);

		if (random == 1)
		{
			boutons.push_back(Bouton(1, Pos));
		}
		else if (random == 2)
		{
			boutons.push_back(Bouton(2, Pos));
		}
		else if (random == 3)
		{
			boutons.push_back(Bouton(3, Pos));
		}
		else if (random == 4)
		{
			boutons.push_back(Bouton(4, Pos));
		}
		Pos.x += 150;
	}

}

void Combinaison::Fin_Classe(const float& dt)
{
	timer_win += dt;

	Demarrage.setColor(Color(255, 255, 255, static_cast<sf::Uint8>(color)));

	if (color <= 254)
	{
		color += 200 * dt;
	}

	if (fin_c)
	{
		boutons.clear();
		fin_c = false;
		compteur_fin = 0;
		Pos.x = 500.f;		
	}
	
	timer_fin += dt;


	random = RandomSpeed(RandInt);
	if (compteur_fin < 6)
	{
		if (timer_fin > 0.16f)
		{
			if (random == 1)
			{		
				boutons.clear();
				boutons.push_back(Bouton(1, Vector2f(Pos.x,Pos.y + posy)));
				Pos.x += 150;
				compteur_fin++;
				timer_fin = 0;
			}
			else if (random == 2)
			{
				boutons.clear();
				boutons.push_back(Bouton(2, Vector2f(Pos.x, Pos.y + posy)));
				Pos.x += 150;
				compteur_fin++;
				timer_fin = 0;
			}
			else if (random == 3)
			{
				boutons.clear();
				boutons.push_back(Bouton(3, Vector2f(Pos.x, Pos.y + posy)));
				Pos.x += 150;
				compteur_fin++;
				timer_fin = 0;
			}
			else if (random == 4)
			{
				boutons.clear();
				boutons.push_back(Bouton(4, Vector2f(Pos.x, Pos.y + posy)));
				Pos.x += 150;
				compteur_fin++;
				timer_fin = 0;
			}
		}
	}
	else if(timer_fin > 0.16f)
	{
		fin_c = true;
	}
	if (timer_win > 4.8f)
	{
		boutons.clear();
	}
	if (timer_win > 5.f)
	{
		go_fin = true;
	}
	


}
 
void Combinaison::IsFirst()
{
	if (boutons.size() > 0)
	{
		if (!boutons[0].Get_Reussi())
		{
			boutons[0].Set_First(true);
		}
		else if (!boutons[1].Get_Reussi())
		{
			boutons[0].Set_First(false);
			boutons[1].Set_First(true);
		}
		else if (!boutons[2].Get_Reussi())
		{
			boutons[0].Set_First(false);
			boutons[1].Set_First(false);
			boutons[2].Set_First(true);
		}
		else if (!boutons[3].Get_Reussi())
		{
			boutons[0].Set_First(false);
			boutons[1].Set_First(false);
			boutons[2].Set_First(false);
			boutons[3].Set_First(true);
		}
		else if (!boutons[4].Get_Reussi())
		{
			boutons[0].Set_First(false);
			boutons[1].Set_First(false);
			boutons[2].Set_First(false);
			boutons[3].Set_First(false);
			boutons[4].Set_First(true);
		}
		else if (!boutons[5].Get_Reussi())
		{
			boutons[0].Set_First(false);
			boutons[1].Set_First(false);
			boutons[2].Set_First(false);
			boutons[3].Set_First(false);
			boutons[4].Set_First(false);
			boutons[5].Set_First(true);
		}
	}
}

void Combinaison::Win(const float& dt)
{
	if (compteur_win == 3 && go_fin )
	{
		Go_fin(dt);
	}

}

void Combinaison::Feedback()
{
	if (fb && timer_fb < 0.1f)
	{
		sprite1.setTextureRect(sf::IntRect(56, 0, 56, 57));
		sprite2.setTextureRect(sf::IntRect(64, 0, 64, 65));
		sprite3.setTextureRect(sf::IntRect(59, 0, 59, 59));
		sprite4.setTextureRect(sf::IntRect(61, 0, 61, 61));
	}
	else if (fb && timer_fb >= 0.1f)
	{
		sprite1.setTextureRect(sf::IntRect(0, 0, 56, 57));
		sprite2.setTextureRect(sf::IntRect(0, 0, 64, 65));
		sprite3.setTextureRect(sf::IntRect(0, 0, 59, 59));
		sprite4.setTextureRect(sf::IntRect(0, 0, 61, 61));

	}

	if (fb && timer_fb > 0.2f)
	{
		timer_fb = 0.f;
		compteur_fb++;
	}

	if (compteur_fb == 5)
	{
		compteur_fb = 0;
		fb = false;
	}
}

void Combinaison::Remplir(const float& dt)
{

	if (go_eau >=1)
	{
		if (m_soundRemplissage.getStatus() != sf::Sound::Playing) {
			m_soundRemplissage.play();
		}

		if (Pos1.y <= 268)
		{
			Pos1.y = 1366;
		}
		
		if (Pos1_1.y <= 268)
		{
			Pos1_1.y = 1366;
		}

		if (Pos1_1_1.y <= 268)
		{
			Pos1_1_1.y = 1366;
		}

		Pos1.y -= 120 * dt;
		Pos1_1.y -= 120 * dt;
		Pos1_1_1.y -= 120 * dt;

		eau1.setPosition(Pos1.x,Pos1.y + posy);
		eau1_1.setPosition(Pos1_1.x, Pos1_1.y + posy);
		eau1_1_1.setPosition(Pos1_1_1.x, Pos1_1_1.y + posy);
		
	}
	if (go_eau >= 2 )
	{
		if (Pos2.y <= 268)
		{
			Pos2.y = 1366;
		}

		if (Pos2_2.y <= 268)
		{
			Pos2_2.y = 1366;
		}
		if (Pos2_2_2.y <= 268)
		{
			Pos2_2_2.y = 1366;
		}

		Pos2.y -= 120 * dt;
		Pos2_2.y -= 120 * dt;
		Pos2_2_2.y -= 120 * dt;

		eau2.setPosition(Pos2.x, Pos2.y + posy);
		eau2_2.setPosition(Pos2_2.x, Pos2_2.y + posy);
		eau2_2_1.setPosition(Pos2_2_2.x, Pos2_2_2.y + posy);
	}
	if (go_eau >= 3)
	{
		if (Pos3.y <= 268)
		{
			Pos3.y = 1366;
		}

		if (Pos3_3.y <= 268)
		{
			Pos3_3.y = 1366;
		}

		if (Pos3_3_3.y <= 268)
		{
			Pos3_3_3.y = 1366;
		}

		Pos3.y -= 120 * dt;
		Pos3_3.y -= 120 * dt;
		Pos3_3_3.y -= 120 * dt;

		eau3.setPosition(Pos3.x, Pos3.y + posy);
		eau3_3.setPosition(Pos3_3.x, Pos3_3.y + posy);
		eau3_3_1.setPosition(Pos3_3_3.x, Pos3_3_3.y + posy);

	}



	


}

void Combinaison::Go_debut(const float& dt)
{
	sprite.setPosition(Vector2f(0, 0 + posy));

	sprite1.setPosition(sf::Vector2f(288, 284 + posy));


	sprite2.setPosition(sf::Vector2f(284, 443 + posy));

	sprite3.setPosition(sf::Vector2f(1522, 281 + posy));


	sprite4.setPosition(sf::Vector2f(1520, 443 + posy));

	tuyau.setPosition(Vector2f(0,0 + posy));

	Porteclé.setPosition(Vector2f(1711, 795 + posy));


	posy -= 600.f * dt;

	if (posy <= 0)
	{
		posy = 0;
		sprite.setPosition(Vector2f(0, 0 + posy));

		sprite1.setPosition(sf::Vector2f(288, 284 + posy));


		sprite2.setPosition(sf::Vector2f(284, 443 + posy));

		sprite3.setPosition(sf::Vector2f(1522, 281 + posy));


		sprite4.setPosition(sf::Vector2f(1520, 443 + posy));

		tuyau.setPosition(Vector2f(0, 0 + posy));

		Porteclé.setPosition(Vector2f(1711, 795 + posy));

		debut = false;
	}
}

void Combinaison::Go_fin(const float& dt)
{
	sprite.setPosition(Vector2f(0, 0 + posy));

	sprite1.setPosition(sf::Vector2f(288, 284 + posy));


	sprite2.setPosition(sf::Vector2f(284, 443 + posy));

	sprite3.setPosition(sf::Vector2f(1522, 281 + posy));


	sprite4.setPosition(sf::Vector2f(1520, 443 + posy));

	tuyau.setPosition(Vector2f(0, 0 + posy));

	Porteclé.setPosition(Vector2f(1711, 795 + posy));


	Demarrage.setPosition(703, 205 + posy);

	posy += 600.f * dt;

	if (posy >= 1080)
	{
		posy = 1080;
		sprite.setPosition(Vector2f(0, 0 + posy));

		sprite1.setPosition(sf::Vector2f(288, 284 + posy));


		sprite2.setPosition(sf::Vector2f(284, 443 + posy));

		sprite3.setPosition(sf::Vector2f(1522, 281 + posy));


		sprite4.setPosition(sf::Vector2f(1520, 443 + posy));

		tuyau.setPosition(Vector2f(0, 0 + posy));

		Porteclé.setPosition(Vector2f(1711, 795 + posy));


		Demarrage.setPosition(703, 205 + posy);
		win = true;
	}
}


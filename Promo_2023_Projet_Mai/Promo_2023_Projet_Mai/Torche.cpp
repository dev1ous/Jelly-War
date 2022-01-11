#include "Torche.h"
#include "Gamepad.h"
#include "Cache.h"
#include "Options.h"

Torche::Torche()
{
	m_bufferTorche.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/Torche/BoutonPress.wav");
	m_soundTorche.setBuffer(m_bufferTorche);

	fond.setTexture(Cache::GetRessources<sf::Texture>("jeu_torche"));

	lueur.setTexture(Cache::GetRessources<sf::Texture>("lueur"));
	lueur.setTextureRect(IntRect(0, 0, 136, 136));
	sprite1.setTexture(Cache::GetRessources<sf::Texture>("torche"));
	sprite1.setTextureRect(IntRect(0, 0, 136, 136));
	sprite1.setPosition(Vector2f(300, 100));

	sprite2.setTexture(Cache::GetRessources<sf::Texture>("torche"));
	sprite2.setTextureRect(IntRect(0, 0, 136, 136));
	sprite2.setPosition(Vector2f(700, 100));

	sprite3.setTexture(Cache::GetRessources<sf::Texture>("torche"));
	sprite3.setTextureRect(IntRect(0, 0, 136, 136));
	sprite3.setPosition(Vector2f(300, 500));

	sprite4.setTexture(Cache::GetRessources<sf::Texture>("torche"));
	sprite4.setTextureRect(IntRect(0, 0, 136, 136));
	sprite4.setPosition(Vector2f(700, 500));

	sprite5.setTexture(Cache::GetRessources<sf::Texture>("torche"));
	sprite5.setTextureRect(IntRect(0, 0, 136, 136));
	sprite5.setPosition(Vector2f(300, 900));

	sprite6.setTexture(Cache::GetRessources<sf::Texture>("torche"));
	sprite6.setTextureRect(IntRect(0, 0, 136, 136));
	sprite6.setPosition(Vector2f(700, 900));

	lueurwin.setTexture(Cache::GetRessources<sf::Texture>("bouton_victoire_2"));

	PorteClé.setTexture(Cache::GetRessources<sf::Texture>("Pclé"));

	FBbouton.setTexture(Cache::GetRessources<sf::Texture>("petita"));

	FBbouton.setTextureRect(sf::IntRect(0, 0, 56, 57));
	FBbouton.setPosition(Vector2f(Pos1.x + 30, Pos1.y + 140));

	random = rand() % 6;


	anim = Animator(sf::IntRect(0, 0, 116, 75), 16, 0.1f, PorteClé.getGlobalBounds().height, false);

	Pos1 = Vector2f(689, 332);
	Pos2 = Vector2f(897, 332);
	Pos3 = Vector2f(1105, 332);
	Pos4 = Vector2f(689, 538);
	Pos5 = Vector2f(897, 538);
	Pos6 = Vector2f(1105, 538);

	for (int i = 0; i < 6; i++)
	{
		tableau[i] = true;
	}

	Rand_Pos();

	Poslueur = Pos1;
	lueur.setPosition(Poslueur);

	PorteClé.setPosition(244, 565);
}

Torche::~Torche()
{
}

void Torche::Update(const float& dt)
{
	m_soundTorche.setVolume(Options::volumeBruitages);

	if (!prewin && !debut)
	{
		Change(dt);
		Do_Lueur();
		FBbouton.setPosition(Vector2f(Poslueur.x + 40, Poslueur.y + 145));

	}

	if (debut)
	{
		Go_debut(dt);
	}
	timer_anim += dt;
	
	if (timer_anim > 0.1f)
	{
		FBbouton.setTextureRect(sf::IntRect(0, 0, 56, 57));
	}
	else
	{
		FBbouton.setTextureRect(sf::IntRect(57, 0, 56, 57));
	}
	
	if (timer_anim > 1.f)
	{
		timer_anim = 0.f;
	}



	if (!allumé1)
	{
		sprite1.setTextureRect(IntRect(0, 0, 136, 136));
	}
	else
	{
		sprite1.setTextureRect(IntRect(136, 0, 136, 136));
	}
	if (!allumé2)
	{
		sprite2.setTextureRect(IntRect(0, 0, 136, 136));
	}
	else
	{
		sprite2.setTextureRect(IntRect(136, 0, 136, 136));
	}
	if (!allumé3)
	{
		sprite3.setTextureRect(IntRect(0, 0, 136, 136));
	}
	else
	{
		sprite3.setTextureRect(IntRect(136, 0, 136, 136));
	}
	if (!allumé4)
	{
		sprite4.setTextureRect(IntRect(0, 0, 136, 136));
	}
	else
	{
		sprite4.setTextureRect(IntRect(136, 0, 136, 136));
	}
	if (!allumé5)
	{
		sprite5.setTextureRect(IntRect(0, 0, 136, 136));
	}
	else
	{
		sprite5.setTextureRect(IntRect(136, 0, 136, 136));
	}
	if (!allumé6)
	{
		sprite6.setTextureRect(IntRect(0, 0, 136, 136));
	}
	else
	{
		sprite6.setTextureRect(IntRect(136, 0, 136, 136));
	}

	if (allumé1 && allumé2 && allumé3 && allumé4 && allumé5 && allumé6)
	{
		prewin = true;
		timer_cligne += dt;
		timer_fin += dt;
	}

	if (timer_fin > 4.f)
	{
		Go_fin(dt);
		
	}

	
	anim.Animation(PorteClé,dt);
}

void Torche::Display(RenderWindow& app)
{
	app.draw(fond);
	app.draw(sprite1);
	app.draw(sprite2);
	app.draw(sprite3);
	app.draw(sprite4);
	app.draw(sprite5);
	app.draw(sprite6);

	app.draw(PorteClé);
	
	if (!prewin)
	{
		if (!debut) {
			app.draw(FBbouton);
			app.draw(lueur);
		}
	}
	else
	{
		if (timer_cligne > 0.2f)
		{

		}
		else
		{
			lueurwin.setPosition(Vector2f(Pos1.x,Pos1.y - posy));
			app.draw(lueurwin);
			lueurwin.setPosition(Vector2f(Pos2.x, Pos2.y - posy));
			app.draw(lueurwin);
			lueurwin.setPosition(Vector2f(Pos3.x, Pos3.y - posy));
			app.draw(lueurwin);
			lueurwin.setPosition(Vector2f(Pos4.x, Pos4.y - posy));
			app.draw(lueurwin);
			lueurwin.setPosition(Vector2f(Pos5.x, Pos5.y - posy));
			app.draw(lueurwin);
			lueurwin.setPosition(Vector2f(Pos6.x, Pos6.y - posy));
			app.draw(lueurwin);
		}
		if (timer_cligne > 0.4f)
		{
			timer_cligne = 0;
		}
		
	}
}

void Torche::Change(const float& dt)
{
	Gamepads g;

	if (g.on_pressed(0, Xbox::A))
	{
		m_soundTorche.play();

		if (Poslueur == Pos1)
		{
			if (PosStock1 == Poslueur)
			{
				allumé1 = !allumé1;
			}
			else if (PosStock2 == Poslueur)
			{
				allumé2 = !allumé2;
				allumé4 = !allumé4;

			}
			else if (PosStock3 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé3 = !allumé3;

			}
			else if (PosStock4 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé5 = !allumé5;

			}
			else if (PosStock5 == Poslueur)
			{
				allumé5 = !allumé5;
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
			else if (PosStock6 == Poslueur)
			{
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
		}
		else if (Poslueur == Pos2)
		{
			if (PosStock1 == Poslueur)
			{
				allumé1 = !allumé1;
			}
			else if (PosStock2 == Poslueur)
			{
				allumé2 = !allumé2;
				allumé4 = !allumé4;

			}
			else if (PosStock3 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé3 = !allumé3;

			}
			else if (PosStock4 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé5 = !allumé5;

			}
			else if (PosStock5 == Poslueur)
			{
				allumé5 = !allumé5;
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
			else if (PosStock6 == Poslueur)
			{
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
		}
		else if (Poslueur == Pos3)
		{
			if (PosStock1 == Poslueur)
			{
				allumé1 = !allumé1;
			}
			else if (PosStock2 == Poslueur)
			{
				allumé2 = !allumé2;
				allumé4 = !allumé4;

			}
			else if (PosStock3 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé3 = !allumé3;

			}
			else if (PosStock4 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé5 = !allumé5;

			}
			else if (PosStock5 == Poslueur)
			{
				allumé5 = !allumé5;
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
			else if (PosStock6 == Poslueur)
			{
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
		}
		else if (Poslueur == Pos4)
		{
			if (PosStock1 == Poslueur)
			{
				allumé1 = !allumé1;
			}
			else if (PosStock2 == Poslueur)
			{
				allumé2 = !allumé2;
				allumé4 = !allumé4;

			}
			else if (PosStock3 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé3 = !allumé3;

			}
			else if (PosStock4 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé5 = !allumé5;

			}
			else if (PosStock5 == Poslueur)
			{
				allumé5 = !allumé5;
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
			else if (PosStock6 == Poslueur)
			{
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
		}
		else if (Poslueur == Pos5)
		{
			if (PosStock1 == Poslueur)
			{
				allumé1 = !allumé1;
			}
			else if (PosStock2 == Poslueur)
			{
				allumé2 = !allumé2;
				allumé4 = !allumé4;

			}
			else if (PosStock3 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé3 = !allumé3;

			}
			else if (PosStock4 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé5 = !allumé5;

			}
			else if (PosStock5 == Poslueur)
			{
				allumé5 = !allumé5;
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
			else if (PosStock6 == Poslueur)
			{
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
		}
		else if (Poslueur == Pos6)
		{
			if (PosStock1 == Poslueur)
			{
				allumé1 = !allumé1;
			}
			else if (PosStock2 == Poslueur)
			{
				allumé2 = !allumé2;
				allumé4 = !allumé4;

			}
			else if (PosStock3 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé3 = !allumé3;

			}
			else if (PosStock4 == Poslueur)
			{
				allumé4 = !allumé4;
				allumé5 = !allumé5;

			}
			else if (PosStock5 == Poslueur)
			{
				allumé5 = !allumé5;
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
			else if (PosStock6 == Poslueur)
			{
				allumé6 = !allumé6;
				allumé3 = !allumé3;

			}
		}
	}

	timer_change += dt;

	if (timer_change > 0.07f)
	{
		if (Poslueur == Pos1)
		{
			if (g.on_pressed(0, Xbox::LeftJoystick_Up) || g.on_pressed(0, Xbox::LeftJoystick_Down))
			{
				Poslueur = Pos4;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Right))
			{
				Poslueur = Pos2;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Left))
			{
				Poslueur = Pos3;
				timer_change = 0.f;
			}
		}
		else if (Poslueur == Pos2)
		{
			if (g.on_pressed(0, Xbox::LeftJoystick_Up) || g.on_pressed(0, Xbox::LeftJoystick_Down))
			{
				Poslueur = Pos5;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Right))
			{
				Poslueur = Pos3;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Left))
			{
				Poslueur = Pos1;
				timer_change = 0.f;
			}
		}
		else if (Poslueur == Pos3)
		{
			if (g.on_pressed(0, Xbox::LeftJoystick_Up) || g.on_pressed(0, Xbox::LeftJoystick_Down))
			{
				Poslueur = Pos6;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Right))
			{
				Poslueur = Pos1;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Left))
			{
				Poslueur = Pos2;
				timer_change = 0.f;
			}
		}
		else if (Poslueur == Pos4)
		{
			if (g.on_pressed(0, Xbox::LeftJoystick_Up) || g.on_pressed(0, Xbox::LeftJoystick_Down))
			{
				Poslueur = Pos1;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Right))
			{
				Poslueur = Pos5;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Left))
			{
				Poslueur = Pos6;
				timer_change = 0.f;
			}
		}
		else if (Poslueur == Pos5)
		{
			if (g.on_pressed(0, Xbox::LeftJoystick_Up) || g.on_pressed(0, Xbox::LeftJoystick_Down))
			{
				Poslueur = Pos2;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Right))
			{
				Poslueur = Pos6;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Left))
			{
				Poslueur = Pos4;
				timer_change = 0.f;
			}
		}
		else if (Poslueur == Pos6)
		{
			if (g.on_pressed(0, Xbox::LeftJoystick_Up) || g.on_pressed(0, Xbox::LeftJoystick_Down))
			{
				Poslueur = Pos3;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Right))
			{
				Poslueur = Pos4;
				timer_change = 0.f;
			}
			else if (g.on_pressed(0, Xbox::LeftJoystick_Left))
			{
				Poslueur = Pos5;
				timer_change = 0.f;
			}
		}
	}
	lueur.setPosition(Poslueur);

}

void Torche::Rand_Pos()
{
	while (compteur != 7)
	{
		random = rand() % 6 + 1;

		Vector2f tmp;
		bool suite = true;
		if (random == 1 && tableau[0])
		{
			tmp = Pos1;
			tableau[0] = false;
			compteur++;
		}
		else if (random == 2 && tableau[1])
		{
			tmp = Pos2;
			tableau[1] = false;
			compteur++;
		}
		else if (random == 3 && tableau[2])
		{
			tmp = Pos3;
			tableau[2] = false;
			compteur++;
		}
		else if (random == 4 && tableau[3])
		{
			tmp = Pos4;
			tableau[3] = false;
			compteur++;
		}
		else if (random == 5 && tableau[4])
		{
			tmp = Pos5;
			tableau[4] = false;
			compteur++;
		}
		else if (random == 6 && tableau[5])
		{
			tmp = Pos6;
			tableau[5] = false;
			compteur++;

		}
		else
		{
			suite = false;
		}

		if (suite)
		{
			if (compteur == 1)
			{
				sprite1.setPosition(tmp);
				PosStock1 = tmp;
			}
			else if (compteur == 2)
			{
				sprite2.setPosition(tmp);
				PosStock2 = tmp;
			}
			else if (compteur == 3)
			{
				sprite3.setPosition(tmp);
				PosStock3 = tmp;
			}
			else if (compteur == 4)
			{
				sprite4.setPosition(tmp);
				PosStock4 = tmp;
			}
			else if (compteur == 5)
			{
				sprite5.setPosition(tmp);
				PosStock5 = tmp;
			}
			else if (compteur == 6)
			{
				compteur++;
				sprite6.setPosition(tmp);
				PosStock6 = tmp;
			}
		}

	}

}

void Torche::Do_Lueur()
{
	if (Poslueur == Pos1)
	{
		if (PosStock1 == Poslueur)
		{
			if (allumé1)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}
		}
		else if (PosStock2 == Poslueur)
		{
			if (allumé2)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock3 == Poslueur)
		{
			if (allumé3)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock4 == Poslueur)
		{
			if (allumé4)
			{

				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock5 == Poslueur)
		{
			if (allumé5)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));

			}

		}
		else if (PosStock6 == Poslueur)
		{
			if (allumé6)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
	}
	else if (Poslueur == Pos2)
	{
		if (PosStock1 == Poslueur)
		{
			if (allumé1)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}
		}
		else if (PosStock2 == Poslueur)
		{
			if (allumé2)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock3 == Poslueur)
		{
			if (allumé3)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock4 == Poslueur)
		{
			if (allumé4)
			{

				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock5 == Poslueur)
		{
			if (allumé5)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));

			}

		}
		else if (PosStock6 == Poslueur)
		{
			if (allumé6)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
	}
	else if (Poslueur == Pos3)
	{
		if (PosStock1 == Poslueur)
		{
			if (allumé1)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}
		}
		else if (PosStock2 == Poslueur)
		{
			if (allumé2)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock3 == Poslueur)
		{
			if (allumé3)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock4 == Poslueur)
		{
			if (allumé4)
			{

				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock5 == Poslueur)
		{
			if (allumé5)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));

			}

		}
		else if (PosStock6 == Poslueur)
		{
			if (allumé6)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
	}
	else if (Poslueur == Pos4)
	{
		if (PosStock1 == Poslueur)
		{
			if (allumé1)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}
		}
		else if (PosStock2 == Poslueur)
		{
			if (allumé2)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock3 == Poslueur)
		{
			if (allumé3)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock4 == Poslueur)
		{
			if (allumé4)
			{

				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock5 == Poslueur)
		{
			if (allumé5)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));

			}

		}
		else if (PosStock6 == Poslueur)
		{
			if (allumé6)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
	}
	else if (Poslueur == Pos5)
	{
		if (PosStock1 == Poslueur)
		{
			if (allumé1)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}
		}
		else if (PosStock2 == Poslueur)
		{
			if (allumé2)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock3 == Poslueur)
		{
			if (allumé3)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock4 == Poslueur)
		{
			if (allumé4)
			{

				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock5 == Poslueur)
		{
			if (allumé5)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));

			}

		}
		else if (PosStock6 == Poslueur)
		{
			if (allumé6)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
	}
	else if (Poslueur == Pos6)
	{
		if (PosStock1 == Poslueur)
		{
			if (allumé1)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}
		}
		else if (PosStock2 == Poslueur)
		{
			if (allumé2)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock3 == Poslueur)
		{
			if (allumé3)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock4 == Poslueur)
		{
			if (allumé4)
			{

				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
		else if (PosStock5 == Poslueur)
		{
			if (allumé5)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));
			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));

			}

		}
		else if (PosStock6 == Poslueur)
		{
			if (allumé6)
			{
				lueur.setTextureRect(IntRect(136, 0, 136, 136));

			}
			else
			{
				lueur.setTextureRect(IntRect(0, 0, 136, 136));
			}

		}
	}
}

void Torche::Go_debut(const float& dt)
{
	fond.setPosition(Vector2f (0, 0 - posy));

	//lueur.setPosition(Vector2f(0, 0 - posy));
	sprite1.setPosition(Vector2f(PosStock1.x, PosStock1.y - posy));


	sprite2.setPosition(Vector2f(PosStock2.x, PosStock2.y - posy));

	sprite3.setPosition(Vector2f(PosStock3.x, PosStock3.y - posy));


	sprite4.setPosition(Vector2f(PosStock4.x, PosStock4.y - posy));


	sprite5.setPosition(Vector2f(PosStock5.x, PosStock5.y - posy));


	sprite6.setPosition(Vector2f(PosStock6.x, PosStock6.y - posy));

	lueurwin.setPosition(Vector2f(Poslueur.x, Poslueur.y - posy));

	PorteClé.setPosition(Vector2f(244, 565 - posy));

	FBbouton.setPosition(Vector2f(Poslueur.x + 40, Poslueur.y + 145 - 1080));


	posy -= 600.f * dt;

	if (posy <= 0)
	{
		posy = 0;

		fond.setPosition(Vector2f(0, 0 - posy));

		//lueur.setPosition(Vector2f(0, 0 - posy));
		sprite1.setPosition(Vector2f(PosStock1.x, PosStock1.y - posy));


		sprite2.setPosition(Vector2f(PosStock2.x, PosStock2.y - posy));

		sprite3.setPosition(Vector2f(PosStock3.x, PosStock3.y - posy));


		sprite4.setPosition(Vector2f(PosStock4.x, PosStock4.y - posy));


		sprite5.setPosition(Vector2f(PosStock5.x, PosStock5.y - posy));


		sprite6.setPosition(Vector2f(PosStock6.x, PosStock6.y - posy));

		lueurwin.setPosition(Vector2f(Poslueur.x, Poslueur.y - posy));

		PorteClé.setPosition(Vector2f(244, 565 - posy));

		FBbouton.setPosition(Vector2f(Poslueur.x + 40, Poslueur.y + 145 - 1080));
		debut = false;
	}
}

void Torche::Go_fin(const float& dt)
{
	

	fond.setPosition(Vector2f(0, 0 - posy));

	//lueur.setPosition(Vector2f(PosStock1.x, PosStock1.y - posy));
	sprite1.setPosition(Vector2f(PosStock1.x, PosStock1.y - posy));


	sprite2.setPosition(Vector2f(PosStock2.x, PosStock2.y - posy));

	sprite3.setPosition(Vector2f(PosStock3.x, PosStock3.y - posy));


	sprite4.setPosition(Vector2f(PosStock4.x, PosStock4.y - posy));


	sprite5.setPosition(Vector2f(PosStock5.x, PosStock5.y - posy));


	sprite6.setPosition(Vector2f(PosStock6.x, PosStock6.y - posy));

	lueurwin.setPosition(Vector2f(Poslueur.x, Poslueur.y - posy));

	PorteClé.setPosition(Vector2f(244, 565 - posy));

	FBbouton.setPosition(Vector2f(Poslueur.x + 40, Poslueur.y + 145 - 1080));


	posy += 600.f * dt;

	if (posy >= 1080)
	{
		posy = 1080;
		fond.setPosition(Vector2f(0, 0 - posy));

		//lueur.setPosition(Vector2f(0, 0 - posy));
		sprite1.setPosition(Vector2f(PosStock1.x, PosStock1.y - posy));


		sprite2.setPosition(Vector2f(PosStock2.x, PosStock2.y - posy));

		sprite3.setPosition(Vector2f(PosStock3.x, PosStock3.y - posy));


		sprite4.setPosition(Vector2f(PosStock4.x, PosStock4.y - posy));


		sprite5.setPosition(Vector2f(PosStock5.x, PosStock5.y - posy));


		sprite6.setPosition(Vector2f(PosStock6.x, PosStock6.y - posy));

		lueurwin.setPosition(Vector2f(Poslueur.x, Poslueur.y - posy));

		PorteClé.setPosition(Vector2f(244, 565 - posy));

		FBbouton.setPosition(Vector2f(Poslueur.x + 40, Poslueur.y + 145 - 1080));

		win = true;
	}
}



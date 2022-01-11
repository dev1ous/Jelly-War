#include "Peche.h"
#include "Cache.h"
#include "Gamepad.h"
#include "Options.h"

Plasma::Plasma()
{
	sprite.setTexture(Cache::GetRessources<sf::Texture>("plasmaMJ"));

	random = rand() % 6 + 1;

	speed = rand() % 200 + 100;

	Pos.x = static_cast<float>(rand() % 900 + 550);
	Pos.y = static_cast<float>(rand() % 450 + 100);
		
	sprite.setColor(sf::Color(255, 255, 255, 0));

	Base_pos.x = Pos.x;
	Base_pos.y = Pos.y;

	sprite.setPosition(Pos);

	anim = Animator(sf::IntRect(0, 0, 117, 117), 11, 0.1f, sprite.getGlobalBounds().height, false);
	sprite.setTextureRect(sf::IntRect(0, 0, 117, 117));
}

Plasma::~Plasma()
{
}

void Plasma::Update(const float& dt)
{
	if (transparence < 250 && !go_tranparence)
	{
		transparence += 550 * dt;
	}
	
	sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(transparence)));

	if (random == 1)
	{
		Pos.x += speed * dt;
		Pos.y -= speed * dt;
	}
	else if (random == 2)
	{
		Pos.x += speed * dt;
		Pos.y += speed * dt;
	}
	else if (random == 3)
	{
		Pos.x -= speed * dt;
		Pos.y -= speed * dt;
	}
	else if (random == 4)
	{
		Pos.x -= speed * dt;
		Pos.y += speed * dt;
	}
	else if (random == 5)
	{
		Pos.x += speed * dt;
	}
	else if (random == 6)
	{
		Pos.y -= speed * dt;
	}
	

	if (Pos.x < 510 || Pos.y < 90 || Pos.x > 1620 || Pos.y > 600)
	{
		go_tranparence = true;
		if (transparence > 0 && go_tranparence)
		{
			transparence -= 550 * dt;
			clickable = false;
			
		}
		if (transparence < 10)
		{
			vie = 0;
		}
		
	}
	else if(clickable)
	{
		sprite.setPosition(Pos);
	}

	if (death)
	{
		anim.Animation_NoRestart(sprite,dt);

		if (anim.Get_End())
		{
			vie = 0;
		}
	}
	
}

void Plasma::Display(RenderWindow& app)
{
	app.draw(sprite);
}

void Plasma::Set_Vie()
{
	death = true;
	clickable = false;
}

Peche::Peche()
{
	m_bufferPlasma.loadFromFile(/*"../Ressources/Sons/capEtVol/Peche/Recuperation_plasma.wav"*/"../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/Peche/TirPeche.wav");
	m_soundPlasma.setBuffer(m_bufferPlasma);
	m_bufferJauge.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/Peche/BarreAugmente.wav");
	m_soundJauge.setBuffer(m_bufferJauge);
	m_bufferEnd.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/Peche/EndMiniGame.wav");
	m_soundEnd.setBuffer(m_bufferEnd);

	fond.setTexture(Cache::GetRessources<sf::Texture>("jeu plasma"));

	curseur.setTexture(Cache::GetRessources<sf::Texture>("curseurMJ"));

	Jauge.setTexture(Cache::GetRessources<sf::Texture>("chargement"));

	ecran.setTexture(Cache::GetRessources<sf::Texture>("ecran"));

	Tuyaux.setTexture(Cache::GetRessources<sf::Texture>("Tuyaux"));

	ecran.setPosition(sf::Vector2f(524, 103));

	Jauge.setPosition(sf::Vector2f(357, 286 + 344));

	curseur.setOrigin(32, 32);

	Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
	Rec_Jauge.height = 0;
	Rec_Jauge.width = 105;
	Rec_Jauge.top = 0;
	Rec_Jauge.left = 0;
	Jauge.setTextureRect(Rec_Jauge);

	PosMouse.x = 1120;
	PosMouse.y = 427;
	curseur.setPosition(Vector2f(1120, 427));

	Tuyaux.setTextureRect(sf::IntRect(0, 0, 1735, 511));
	anim = Animator(sf::IntRect(0, 0, 1735, 511), 8, 0.1f,Tuyaux.getGlobalBounds().height,false);
	anim2 = Animator(sf::IntRect(0, 0, 64, 64), 17, 0.03f);

	Tuyaux.setPosition(-2, 349);

	anim2.Animation_NoRestart(curseur, 0.f);
		
}

Peche::~Peche()
{
}

void Peche::Update(const float& dt)
{
	timer_anim += dt;

	m_soundPlasma.setVolume(Options::volumeBruitages);
	m_soundJauge.setVolume(Options::volumeBruitages);
	m_soundEnd.setVolume(Options::volumeBruitages);

	Gamepads g;

	if (debut)
	{
		Go_debut(dt);
	}
	if (!prewin && !debut)
	{
		if (g.is_pressed(0, Xbox::LeftJoystick_Up) && PosMouse.y > 160 && !anim_bool)
		{
			PosMouse.y -= 500 * dt;
		}

		if (g.is_pressed(0, Xbox::LeftJoystick_Down) && PosMouse.y < 697 && !anim_bool)
		{
			PosMouse.y += 500 * dt;
		}
		if (g.is_pressed(0, Xbox::LeftJoystick_Right) && PosMouse.x < 1705 && !anim_bool)
		{
			PosMouse.x += 500 * dt;
		}
		if (g.is_pressed(0, Xbox::LeftJoystick_Left) && PosMouse.x > 565 && !anim_bool)
		{
			PosMouse.x -= 500 * dt;
		}

		Go_Jauge();

		Spawn(dt);

		for (int i = 0; i < plasma.size(); i++)
		{

			if (g.on_pressed(0, Xbox::A))
			{
				anim_bool = true;

				if (plasma[i].Get_Sprite().getGlobalBounds().contains(curseur.getPosition()) && plasma[i].Get_Clickable())
				{
					m_soundPlasma.play();
					plasma[i].Set_Vie();
					score++;
					if (m_soundJauge.getStatus() != sf::Sound::Status::Playing)
						m_soundJauge.play();
				}
				else
				{
					vie--;

				}
			}

			plasma[i].Update(dt);

		}
		curseur.setPosition(Vector2f(PosMouse.x, PosMouse.y));
	}

	if (anim_bool)
	{	
		anim2.Animation_NoRestart(curseur, dt);
		if (anim2.Get_End())
		{
			anim_bool = false;
			anim2.Restart_Anim();
		}
	}

	
	for (int i = 0; i < plasma.size(); i++)
	{

		if (plasma[i].Get_Vie() == 0 || prewin)
		{
			plasma.erase(plasma.begin() + i);
		}
	}




	if (timer_anim > 0.1f && prewin)
	{
		if (frame >= 9) {
			frame = 0;
			timer_anim = 0;
		}
		else {
			timer_anim = 0;
			Rec_Jauge.left = 105 * frame;
		}
		frame++;
	}

	
	Jauge.setTextureRect(Rec_Jauge);

	if (prewin)
	{
		m_soundEnd.play();
		timer_fin += dt;
		anim.Animation(Tuyaux, dt);
	}

	if (timer_fin > 5.f)
	{
		Go_fin(dt);
	}
}

void Peche::Display(RenderWindow& app)
{

	app.draw(fond);
	app.draw(ecran);
	for (int i = 0; i < plasma.size(); i++)
	{
		plasma[i].Display(app);
	}



	app.draw(Jauge);
	app.draw(curseur);
	app.draw(Tuyaux);
}

void Peche::Spawn(const float& dt)
{
	timer_spawn += dt;
	timer_jauge += dt;

	if (timer_spawn > 0.7f)
	{
		timer_spawn = 0;
		plasma.push_back(Plasma());
	}

}

void Peche::Go_Jauge()
{

	if (score == 1 && Rec_Jauge.height < 30 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 2 && Rec_Jauge.height < 60 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 3 && Rec_Jauge.height < 90 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 4 && Rec_Jauge.height < 120 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 5 && Rec_Jauge.height < 150 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 6 && Rec_Jauge.height < 180 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 7 && Rec_Jauge.height < 210 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 8 && Rec_Jauge.height < 240 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 9 && Rec_Jauge.height < 270 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 10 && Rec_Jauge.height < 300 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}
	else if (score >= 11 && Rec_Jauge.height < 345 && timer_jauge > 0.02f)
	{
		Rec_Jauge.height++;
		Jauge.setTextureRect(Rec_Jauge);
		Jauge.setOrigin(0, Jauge.getGlobalBounds().height);
		timer_jauge = 0.f;
	}

	if (Rec_Jauge.height >= 344)
	{
		prewin = true;
	}
}

void Peche::Go_debut(const float& dt)
{
	fond.setPosition(sf::Vector2f(0 - posx,0));

	ecran.setPosition(sf::Vector2f(524 - posx, 103));

	Jauge.setPosition(sf::Vector2f(357 - posx, 286 + 344));

	curseur.setPosition(Vector2f(1120 - posx, 427));

	Tuyaux.setPosition(-2 - posx, 349);

	posx -= 600.f * dt;

	if (posx <= 0)
	{
		posx = 0;
		fond.setPosition(sf::Vector2f(0 - posx, 0));

		ecran.setPosition(sf::Vector2f(524 - posx, 103));

		Jauge.setPosition(sf::Vector2f(357 - posx, 286 + 344));

		curseur.setPosition(Vector2f(1120 - posx, 427));

		Tuyaux.setPosition(-2 - posx, 349);
		debut = false;
	}
}

void Peche::Go_fin(const float& dt)
{
	fond.setPosition(sf::Vector2f(0 - posx, 0));

	ecran.setPosition(sf::Vector2f(524 - posx, 103));

	Jauge.setPosition(sf::Vector2f(357 - posx, 286 + 344));

	curseur.setPosition(Vector2f(1120 - posx, 427));

	Tuyaux.setPosition(-2 - posx, 349);

	posx += 600.f * dt;

	if (posx >= 1980)
	{
		posx = 1980;
		fond.setPosition(sf::Vector2f(0 - posx, 0));

		ecran.setPosition(sf::Vector2f(524 - posx, 103));

		Jauge.setPosition(sf::Vector2f(357 - posx, 286 + 344));

		curseur.setPosition(Vector2f(1120 - posx, 427));

		Tuyaux.setPosition(-2 - posx, 349);
		win = true;
	}
}



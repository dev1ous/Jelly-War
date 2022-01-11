#include "Puzzle.h"
#include "Cache.h"
#include "Gamepad.h"
#include "Options.h"

Pieces::Pieces(int _id, sf::Vector2f _pos) : id(_id), Pos(_pos)
{

	Base_pos.x = _pos.x;
	Base_pos.y = _pos.y;

	if (id == 1)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("1"));
	}
	else if (id == 2)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("2"));
	}
	else if (id == 3)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("3"));
	}
	else if (id == 4)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("4"));
	}
	else if (id == 5)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("5"));
	}
	else if (id == 6)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("6"));
	}
	else if (id == 7)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("7"));
	}
	else if (id == 8)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("8"));
	}
	else if (id == 9)
	{
		sprite.setTexture(Cache::GetRessources<sf::Texture>("9"));

	}


}

Pieces::~Pieces()
{

}

void Pieces::Update()
{
	sprite.setPosition(Pos);
}


void Pieces::Display(sf::RenderWindow& app)
{
	app.draw(sprite);
}

Puzzle::Puzzle()
{
	Fond.setTexture(Cache::GetRessources<sf::Texture>("jeu"));


	Ecran.setTexture(Cache::GetRessources<sf::Texture>("écran_puzzle"));

	JolieAnim.setTexture(Cache::GetRessources<sf::Texture>("JolieAnim"));

	Joystick.setTexture(Cache::GetRessources<sf::Texture>("Joystick"));

	anim = Animator(sf::IntRect(0, 0, 705, 706), 4, 0.1f, JolieAnim.getGlobalBounds().height, false);
	anim_joy = Animator(sf::IntRect(0, 0, 145, 145), 16, 0.1f, Joystick.getGlobalBounds().height, false);

	Pos1.x = 578.f;
	Pos1.y = 199.f;

	Pos2.x = 823.f;
	Pos2.y = 199.f;

	Pos3.x = 1068.f;
	Pos3.y = 199.f;

	Pos4.x = 578.f;
	Pos4.y = 444.f;

	Pos5.x = 823.f;
	Pos5.y = 444.f;

	Pos6.x = 1068.f;
	Pos6.y = 444.f;

	Pos7.x = 578.f;
	Pos7.y = 689.f;

	Pos8.x = 823.f;
	Pos8.y = 689.f;

	Pos9.x = 1068.f;
	Pos9.y = 689.f;

	pieces.push_back(Pieces(1, Pos1));
	pieces.push_back(Pieces(2, Pos2));
	pieces.push_back(Pieces(3, Pos3));
	pieces.push_back(Pieces(4, Pos4));
	pieces.push_back(Pieces(5, Pos5));
	pieces.push_back(Pieces(6, Pos6));
	pieces.push_back(Pieces(7, Pos7));
	pieces.push_back(Pieces(8, Pos8));
	pieces.push_back(Pieces(9, Pos9));

	pieces[8].Set_Sprite(sf::Color::Transparent);


	Ecran.setPosition(Pos1);
	JolieAnim.setPosition(Vector2f(593.f, 218.f));
	Joystick.setPosition(Vector2f(279.f, 621.f));
}

Puzzle::~Puzzle()
{


}

void Puzzle::Init()
{
	m_bufferPuzzle.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/Puzzle/deplacementPiece.wav");
	m_soundPuzzle.setBuffer(m_bufferPuzzle);
	m_BufferEndPuzzle.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/Puzzle/Reussite.wav");
	m_SoundEndPuzzle.setBuffer(m_BufferEndPuzzle);

	for (int i = 0; i < 9; i++)
	{
		tableau[i] = true;
	}

	compteur = 0;
	random = RandomSpeed(RandInt);
	while (compteur != random)
	{
		for (int i = 0; i < pieces.size() - 1; i++)
		{
			if (pieces[8].Get_Pos().y == Pos1.y)
			{
				if (pieces[8].Get_Pos().x == Pos1.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos1.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos2.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
				}
				else if (pieces[8].Get_Pos().x == Pos2.x)
				{
					if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos1.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos3.x )
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos2.x )
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
				}
				else if (pieces[8].Get_Pos().x == Pos3.x)
				{
					if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos2.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;

					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos3.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}

				}
			}
			else if (pieces[8].Get_Pos().y == 444.f)
			{
				if (pieces[8].Get_Pos().x == Pos1.x)
				{
					if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos1.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos1.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos2.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
				}
				else if (pieces[8].Get_Pos().x == Pos2.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos1.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos3.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos2.x )
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;

					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos2.x )
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
				}
				else if (pieces[8].Get_Pos().x == Pos3.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos2.x )
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;

					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos3.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos3.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
				}
			}
			else if (pieces[8].Get_Pos().y == 689.f)
			{
				if (pieces[8].Get_Pos().x == Pos1.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos1.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;

					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos2.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}

				}
				else if (pieces[8].Get_Pos().x == Pos2.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos2.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;

					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos1.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos3.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}
				}
				else if (pieces[8].Get_Pos().x == Pos3.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos3.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;

					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos2.x)
					{
						Vector2f tmp = pieces[8].Get_Pos();
						pieces[8].Set_Position(pieces[i].Get_Pos());
						pieces[i].Set_Position(tmp);
						timer_switch = 0.f;
					}

				}
			}
		}
		compteur++;
	}

}

void Puzzle::Update(const float& dt)
{
	if (one_pass)
	{
		Init();
		one_pass = false;
		for (int i = 0; i < pieces.size() - 1 ; i++)
		{
			pieces[i].SetColor(0);

		}
	}

	m_soundPuzzle.setVolume(Options::volumeBruitages);
	m_SoundEndPuzzle.setVolume(Options::volumeBruitages);

	timer_switch += dt;

	if (!debut)
	{
		if (alpha < 255)
		{
			for (int i = 0; i < pieces.size() - 1; i++)
			{
				pieces[i].SetColor(alpha);

			}
			alpha += 400 * dt;
		}

		if (!win)
		{
			if (timer_switch > 0.3f)
			{
				Switch(dt);
			}
			for (int i = 0; i < pieces.size(); i++)
			{
				pieces[i].Update();
			}
		}		

		Win(dt);
	}
	else
	{
		Go_debut(dt);
	}
	anim_joy.Animation(Joystick, dt);
}

void Puzzle::Display(sf::RenderWindow& app)
{

	app.draw(Fond);
	app.draw(Joystick);
	
	

	if (go_anim)
	{
		app.draw(Ecran);
		app.draw(JolieAnim);
	}
	else
	{
		for (int i = 0; i < pieces.size(); i++)
		{
			pieces[i].Display(app);
		}
	}

}

void Puzzle::Switch(const float& dt)
{
	Gamepads g;


	if (!go_switch)
	{
		for (int i = 0; i < pieces.size() - 1; i++)
		{
			if (pieces[8].Get_Pos().y == Pos1.y)
			{
				if (pieces[8].Get_Pos().x == Pos1.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos1.x && g.on_pressed(0, Xbox::RightJoystick_Up))
					{
						go_switch = true;
						id = i;
						soluce = 1;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Left))
					{
						go_switch = true;
						id = i;
						soluce = 2;
						m_soundPuzzle.play();
					}
				}
				else if (pieces[8].Get_Pos().x == Pos2.x)
				{
					if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos1.x && g.on_pressed(0, Xbox::RightJoystick_Right))
					{
						go_switch = true;
						id = i;
						soluce = 3;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos3.x && g.on_pressed(0, Xbox::RightJoystick_Left))
					{
						go_switch = true;
						id = i;
						soluce = 4;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Up))
					{
						go_switch = true;
						id = i;
						soluce = 5;
						m_soundPuzzle.play();
					}
				}
				else if (pieces[8].Get_Pos().x == Pos3.x)
				{
					if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Right))
					{
						go_switch = true;
						id = i;
						soluce = 6;
						m_soundPuzzle.play();

					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos3.x && g.on_pressed(0, Xbox::RightJoystick_Up))
					{
						go_switch = true;
						id = i;
						soluce = 7;
						m_soundPuzzle.play();
					}

				}
			}
			else if (pieces[8].Get_Pos().y == 444.f)
			{
				if (pieces[8].Get_Pos().x == Pos1.x)
				{
					if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos1.x && g.on_pressed(0, Xbox::RightJoystick_Down))
					{
						go_switch = true;
						id = i;
						soluce = 8;
						m_soundPuzzle.play();

					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos1.x && g.on_pressed(0, Xbox::RightJoystick_Up))
					{
						go_switch = true;
						id = i;
						soluce = 9;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Left))
					{
						go_switch = true;
						id = i;
						soluce = 10;
						m_soundPuzzle.play();
					}
				}
				else if (pieces[8].Get_Pos().x ==Pos2.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos1.x && g.on_pressed(0, Xbox::RightJoystick_Right))
					{

						go_switch = true;
						id = i;
						soluce = 11;
						m_soundPuzzle.play();

					}
					else if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos3.x && g.on_pressed(0, Xbox::RightJoystick_Left))
					{
						go_switch = true;
						id = i;
						soluce = 12;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Down))
					{
						go_switch = true;
						id = i;
						soluce = 13;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Up))
					{
						go_switch = true;
						id = i;
						soluce = 14;
						m_soundPuzzle.play();
					}
				}
				else if (pieces[8].Get_Pos().x == Pos3.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Right))
					{
						go_switch = true;
						id = i;
						soluce = 15;
						m_soundPuzzle.play();

					}
					else if (pieces[i].Get_Pos().y == 199.f && pieces[i].Get_Pos().x == Pos3.x && g.on_pressed(0, Xbox::RightJoystick_Down))
					{
						go_switch = true;
						id = i;
						soluce = 16;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos3.x && g.on_pressed(0, Xbox::RightJoystick_Up))
					{
						go_switch = true;
						id = i;
						soluce = 17;
						m_soundPuzzle.play();
					}
				}
			}
			else if (pieces[8].Get_Pos().y == 689.f)
			{
				if (pieces[8].Get_Pos().x == Pos1.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos1.x && g.on_pressed(0, Xbox::RightJoystick_Down))
					{
						go_switch = true;
						id = i;
						soluce = 18;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Left))
					{
						go_switch = true;
						id = i;
						soluce = 19;
						m_soundPuzzle.play();
					}

				}
				else if (pieces[8].Get_Pos().x ==Pos2.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Down))
					{
						go_switch = true;
						id = i;
						soluce = 20;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos1.x && g.on_pressed(0, Xbox::RightJoystick_Right))
					{
						go_switch = true;
						id = i;
						soluce = 21;
						m_soundPuzzle.play();
					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x == Pos3.x && g.on_pressed(0, Xbox::RightJoystick_Left))
					{
						go_switch = true;
						id = i;
						soluce = 22;
						m_soundPuzzle.play();
					}
				}
				else if (pieces[8].Get_Pos().x == Pos3.x)
				{
					if (pieces[i].Get_Pos().y == 444.f && pieces[i].Get_Pos().x == Pos3.x && g.on_pressed(0, Xbox::RightJoystick_Down))
					{
						go_switch = true;
						id = i;
						soluce = 23;
						m_soundPuzzle.play();

					}
					else if (pieces[i].Get_Pos().y == 689.f && pieces[i].Get_Pos().x ==Pos2.x && g.on_pressed(0, Xbox::RightJoystick_Right))
					{
						go_switch = true;
						id = i;
						soluce = 24;
						m_soundPuzzle.play();

					}

				}
			}


		}
	}
	else
	{
		smooth_switch(id, dt);
	}
}

void Puzzle::Win(const float& dt)
{
	int compteur = 0;

	for (int i = 0; i < 9; i++)
	{
		if (pieces[i].Get_Pos().x == pieces[i].Get_Pos_Base().x && pieces[i].Get_Pos().y == pieces[i].Get_Pos_Base().y)
		{
			compteur++;
		}
	}

	if (compteur == 9)
	{
		pieces[8].Set_Sprite(Color(255,255,255, static_cast<sf::Uint8>(color)));
		if (color <= 254)
		{
			color += 200 * dt;
		}
		
	}
	if (go_anim)
	{
		m_SoundEndPuzzle.play();
		anim.Animation(JolieAnim, dt);
	}

	if (color > 254)
	{
		timer_win += dt;
		go_anim = true;
	}
	if (timer_win > 3.f)
	{
		Go_fin(dt);
	}



}

void Puzzle::smooth_switch(int i, const float& dt)
{

	if (soluce == 1)
	{
		if (pieces[i].Get_Pos().y < 199.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos4);
			pieces[i].Set_Position(Pos1);

		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 2)
	{
		if (pieces[i].Get_Pos().x < Pos1.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos2);
			pieces[i].Set_Position(Pos1);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 3)
	{
		if (pieces[i].Get_Pos().x >Pos2.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos1);
			pieces[i].Set_Position(Pos2);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 4)
	{
		if (pieces[i].Get_Pos().x <Pos2.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos3);
			pieces[i].Set_Position(Pos2);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 5)
	{
		if (pieces[i].Get_Pos().y < 199.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos5);
			pieces[i].Set_Position(Pos2);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 6)
	{
		if (pieces[i].Get_Pos().x > Pos3.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos2);
			pieces[i].Set_Position(Pos3);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 7)
	{
		if (pieces[i].Get_Pos().y < 199.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos6);
			pieces[i].Set_Position(Pos3);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 8)
	{
		if (pieces[i].Get_Pos().y > 444.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos1);
			pieces[i].Set_Position(Pos4);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 9)
	{
		if (pieces[i].Get_Pos().y < 444.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos7);
			pieces[i].Set_Position(Pos4);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 10)
	{
		if (pieces[i].Get_Pos().x < Pos1.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos5);
			pieces[i].Set_Position(Pos4);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 11)
	{
		if (pieces[i].Get_Pos().x >Pos2.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos4);
			pieces[i].Set_Position(Pos5);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 12)
	{
		if (pieces[i].Get_Pos().x <Pos2.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos6);
			pieces[i].Set_Position(Pos5);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 13)
	{
		if (pieces[i].Get_Pos().y > 444.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos2);
			pieces[i].Set_Position(Pos5);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 14)
	{
		if (pieces[i].Get_Pos().y < 444.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos8);
			pieces[i].Set_Position(Pos5);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}
	}
	else if (soluce == 15)
	{
		if (pieces[i].Get_Pos().x > Pos3.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos5);
			pieces[i].Set_Position(Pos6);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 16)
	{
		if (pieces[i].Get_Pos().y > 444.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos3);
			pieces[i].Set_Position(Pos6);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 17)
	{
		if (pieces[i].Get_Pos().y < 444.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos9);
			pieces[i].Set_Position(Pos6);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 18)
	{
		if (pieces[i].Get_Pos().y > 689.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos4);
			pieces[i].Set_Position(Pos7);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 19)
	{
		if (pieces[i].Get_Pos().x < Pos1.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos8);
			pieces[i].Set_Position(Pos7);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 20)
	{
		if (pieces[i].Get_Pos().y > 689.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos5);
			pieces[i].Set_Position(Pos8);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 21)
	{
		if (pieces[i].Get_Pos().x >Pos2.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos7);
			pieces[i].Set_Position(Pos8);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 22)
	{
		if (pieces[i].Get_Pos().x <Pos2.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos9);
			pieces[i].Set_Position(Pos8);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x += 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x -= 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else if (soluce == 23)
	{
		if (pieces[i].Get_Pos().y > 689.f)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos6);
			pieces[i].Set_Position(Pos9);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.y -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.y += 600.f * dt;
			pieces[i].Set_Position(tmp2);
		}
	}
	else if (soluce == 24)
	{
		if (pieces[i].Get_Pos().x > Pos3.x)
		{
			go_switch = false;
			pieces[8].Set_Position(Pos8);
			pieces[i].Set_Position(Pos9);
		}
		else
		{
			Vector2f tmp = pieces[8].Get_Pos();
			tmp.x -= 600.f * dt;
			Vector2f tmp2 = pieces[i].Get_Pos();
			tmp2.x += 600.f * dt;
			pieces[i].Set_Position(tmp2);

		}

	}
	else
	{
		go_switch = false;
	}




}

void Puzzle::Go_debut(const float& dt)
{

	Fond.setPosition(Vector2f(0, 0 - posy));

	Joystick.setPosition(Vector2f(279.f, 621.f - posy));

	posy -= 600.f * dt;

	if (posy <= 0)
	{
		posy = 0;
		Fond.setPosition(Vector2f(0, 0 - posy));

		Joystick.setPosition(Vector2f(279.f, 621.f - posy));
		debut = false;
	}
}

void Puzzle::Go_fin(const float& dt)
{

	Fond.setPosition(Vector2f(0, 0 - posy));

	Ecran.setPosition(Vector2f(Pos1.x, Pos1.y - posy));

	Joystick.setPosition(Vector2f(279.f, 621.f - posy));

	JolieAnim.setPosition(Vector2f(593.f, 218.f - posy));

	posy += 600.f * dt;

	if (posy >= 1080)
	{
		posy = 1080;
		Fond.setPosition(Vector2f(0, 0 - posy));

		Ecran.setPosition(Vector2f(Pos1.x, Pos1.y - posy));

		Joystick.setPosition(Vector2f(279.f, 621.f - posy));

		JolieAnim.setPosition(Vector2f(593.f, 218.f - posy));
		win = true;
	}
}



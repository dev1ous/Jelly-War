#include "Memory.h"
#include "Gamepad.h"
#include "Cache.h"
#include "Options.h"
#include <random>

Memory::Memory()
{
	m_bufferComplete.loadFromFile("../Ressources/Sons/capEtVol/Memory/completetask.wav");
	m_soundComplete.setBuffer(m_bufferComplete);

	m_bufferFail.loadFromFile("../Ressources/Sons/capEtVol/Memory/failed.wav");
	m_soundFail.setBuffer(m_bufferFail);

	///////////////////BackGround////////////////////////
	bc.setSize(Vector2f(1920, 1080));
	bc.setTexture(&Cache::GetRessources<sf::Texture>("memoryBc"));
	bc.setOrigin(bc.getGlobalBounds().width / 2, bc.getGlobalBounds().height);
	bc.setPosition(1920 / 2, 0);

	//////////////////////////////////////////////////////////////////////////////
	std::mt19937 mt(std::random_device{}());

	for (int k = 0; coords.size() <= nbRound; k++)
	{
		std::uniform_int_distribution<> randRow{ 0 , nbRow - 1 };
		std::uniform_int_distribution<> randCol{ 0 , nbColumn - 1 };

		if (coords.size() > 0)
		{
			for (int j = 0; j < coords.size(); j++)
			{
				place = false;

				if ((randRow(mt) == coords[j].x && randCol(mt) == coords[j].y))
				{
					place = false;
					k--;
					break;
				}
				else
					place = true;
			}

			if (place)
				coords.push_back(Vector2i(randRow(mt), randCol(mt)));
		}
		else
			coords.push_back(Vector2i(randRow(mt), randCol(mt)));
	}

	/////////////////////////////////////////////////////////////


	std::map<int, RectangleShape> tmp;
	RectangleShape touche;

	touche.setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));

	for (int i = 0; i < nbColumn; i++)
	{
		tmp.clear();

		for (int j = 0; j < nbRow; j++)
		{
			touche.setSize(Vector2f(254.f, 201.f));
			touche.setPosition(Vector2f(offset.x + i * touche.getGlobalBounds().width + 2, offset.y + j * touche.getGlobalBounds().height));
			touche.setFillColor(Color::Transparent);

			tmp.emplace(j, touche);
		}

		keyboard.emplace(i, tmp);
	}
	////////////////////////////////////////

	selector.setTexture(&Cache::GetRessources<sf::Texture>("curseur"));
	selector.setSize(Vector2f(364, 309));
	selector.setOrigin(selector.getGlobalBounds().width / 2, selector.getGlobalBounds().height / 2);
	selectorCoord = Vector2i( static_cast<int>(offset.x + selector.getGlobalBounds().width / 2 - 55), static_cast<int>(offset.y + selector.getGlobalBounds().height / 2 - 56));

	//////////////////////////////////////////////
	CircleShape light;

	light.setTexture(&Cache::GetRessources<sf::Texture>("neutre_vert"));
	light.setRadius(light.getTextureRect().height / 2.f);
	light.setOrigin(light.getGlobalBounds().width / 2.f, light.getGlobalBounds().height / 2.f);
	light.setPosition(Vector2f(340.f, 450.f));

	lights.push_back(light);

	light.setTexture(&Cache::GetRessources<sf::Texture>("neutre_rouge"));
	light.setRadius(light.getTextureRect().height / 2.f);
	light.setOrigin(light.getGlobalBounds().width / 2.f, light.getGlobalBounds().height / 2.f);
	light.setPosition(Vector2f(340.f, 720.f));

	lights.push_back(light);

	//////////////////////////////////////////////////////
	gridSize = Vector2f(
		touche.getSize().x,
		touche.getSize().y);
}

void Memory::Update(const float& _dt, RenderWindow& _window)
{
	m_soundComplete.setVolume(Options::volumeBruitages);
	m_soundFail.setVolume(Options::volumeBruitages);

	if (!isPlaced)
	{
		Vector2f goTo = Vector2f(1920 / 2, 1080);

		this->direction = goTo - this->bc.getPosition();

		this->normailizeDir.x = this->direction.x / sqrtf(powf(this->direction.x, 2) + powf(this->direction.y, 2));
		this->normailizeDir.y = this->direction.y / sqrtf(powf(this->direction.x, 2) + powf(this->direction.y, 2));

		this->velocity = this->normailizeDir * this->speed;

		this->bc.move(velocity * _dt);
		if (bc.getPosition().y >= goTo.y) {
			isPlaced = true;
			bc.setPosition(goTo);
		}
		lights[0].setPosition(bc.getPosition() - bc.getOrigin() + Vector2f(340.f, 450.f));
		lights[1].setPosition(bc.getPosition() - bc.getOrigin() + Vector2f(340.f, 720.f));
	}
	else
	{
		Gamepads g;

		keyTime += _dt;
		timer += _dt;
		timerLight += _dt;


		if (currentRound > nbRound)
		{
			if (timer > 0.f && timer <= .1f)
			{
				keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
				keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
				keyboard[coords[3].x][coords[3].y].setFillColor(Color::Transparent);
				keyboard[coords[4].x][coords[4].y].setFillColor(Color::Transparent);
				keyboard[coords[5].x][coords[5].y].setFillColor(Color::Transparent);
			}
			else if (timer > 0.1f && timer <= .4f)
				keyboard[coords[1].x][coords[1].y].setFillColor(Color::White);
			else if (timer > .4f && timer <= .9f)
				keyboard[coords[2].x][coords[2].y].setFillColor(Color::White);
			else if (timer > .9f && timer <= 1.4f)
				keyboard[coords[3].x][coords[3].y].setFillColor(Color::White);
			else if (timer > 1.4f && timer <= 1.9f)
				keyboard[coords[4].x][coords[4].y].setFillColor(Color::White);
			else if (timer > 1.9f && timer <= 2.4f)
				keyboard[coords[5].x][coords[5].y].setFillColor(Color::White);
			else if (timer > 2.4f)
			{
				keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
				keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
				keyboard[coords[3].x][coords[3].y].setFillColor(Color::Transparent);
				keyboard[coords[4].x][coords[4].y].setFillColor(Color::Transparent);
				keyboard[coords[5].x][coords[5].y].setFillColor(Color::Transparent);

				display = true;
				Vector2f goTo = Vector2f(1920 / 2, 0);

				this->direction = goTo - this->bc.getPosition();

				this->normailizeDir.x = this->direction.x / sqrtf(powf(this->direction.x, 2) + powf(this->direction.y, 2));
				this->normailizeDir.y = this->direction.y / sqrtf(powf(this->direction.x, 2) + powf(this->direction.y, 2));

				this->velocity = this->normailizeDir * this->speed;

				this->bc.move(velocity * _dt);

				if (bc.getPosition().y <= goTo.y)
					done = true;

				lights[0].setPosition(bc.getPosition() - bc.getOrigin() + Vector2f(340.f, 450.f));
				lights[1].setPosition(bc.getPosition() - bc.getOrigin() + Vector2f(340.f, 720.f));
			}

		}

		if (!done)
		{
			//UpdateSelector

			if (g.on_pressed(0, Xbox::Axis::LeftJoystick_Right))
				selectorCoord.x += static_cast<int>(gridSize.x);

			if (g.on_pressed(0, Xbox::Axis::LeftJoystick_Left))
				selectorCoord.x -= static_cast<int>(gridSize.x);

			if (g.on_pressed(0, Xbox::Axis::LeftJoystick_Up))
				selectorCoord.y -= static_cast<int>(gridSize.y);

			if (g.on_pressed(0, Xbox::Axis::LeftJoystick_Down))
				selectorCoord.y += static_cast<int>(gridSize.y);

			if (selectorCoord.x < offset.x)
				selectorCoord.x = static_cast<int>(offset.x + selector.getGlobalBounds().width / 2 - 55.f);

			if (selectorCoord.x > offset.x + 3 * gridSize.x)
				selectorCoord.x = static_cast<int>(offset.x + 3 * gridSize.x + selector.getGlobalBounds().width / 2 - 53.f);

			if (selectorCoord.y < offset.y)
				selectorCoord.y = static_cast<int>(offset.y + selector.getGlobalBounds().height / 2 - 55.f);

			if (selectorCoord.y > offset.y + 3 * gridSize.y)
				selectorCoord.y = static_cast<int>(offset.y + 3 * gridSize.y + selector.getGlobalBounds().height / 2 - 55.f);

			this->selector.setPosition(static_cast<float>(selectorCoord.x), static_cast<float>(selectorCoord.y));

			///////////////////////////////////////////////////////////////////////////////////

			if (!isOnGuessPart)
			{
				if (i == 1)
				{
					if (timer > .0f && timer <= .5f)
					{
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::White);
					}
					else if (timer > .5f && timer <= .6f)
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
					else if (timer > .6f)
					{
						isOnGuessPart = true;
						i++;
					}
				}
				else if (i == 2)
				{
					if (timer > .0f && timer <= .6f)
					{
						keyboard[coords[1].x][coords[1].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));

						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
					}
					else if (timer > 0.6f && timer <= 1.f)
					{
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::White);
					}
					else if (timer > 1.f && timer <= 1.1f)
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
					else if (timer > 1.1f && timer <= 1.6f)
					{
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::White);
					}
					else if (timer > 1.6f && timer <= 1.7f)
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
					else if (timer > 1.7f && timer <= 2.2f)
					{
						isOnGuessPart = true;
						i++;
					}
				}
				else if (i == 3)
				{
					if (timer > .0f && timer <= .6f)
					{
						keyboard[coords[1].x][coords[1].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));
						keyboard[coords[2].x][coords[2].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));

						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
					}
					else if (timer > 0.6f && timer <= 1.f)
					{
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::White);
					}
					else if (timer > 1.f && timer <= 1.1f)
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
					else if (timer > 1.1f && timer <= 1.6f)
					{
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::White);
					}
					else if (timer > 1.6f && timer <= 1.7f)
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
					else if (timer > 1.7f && timer <= 2.2f)
					{
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::White);
					}
					else if (timer > 2.2f && timer <= 2.3f)
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::Transparent);
					else if (timer > 2.3f)
					{
						isOnGuessPart = true;
						i++;
					}
				}
				else if (i == 4)
				{
					if (timer > .0f && timer <= .6f)
					{
						keyboard[coords[1].x][coords[1].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));
						keyboard[coords[2].x][coords[2].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));
						keyboard[coords[3].x][coords[3].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));

						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::Transparent);
					}
					else if (timer > 0.6f && timer <= 1.f)
					{
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::White);
					}
					else if (timer > 1.f && timer <= 1.1f)
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
					else if (timer > 1.1f && timer <= 1.6f)
					{
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::White);
					}
					else if (timer > 1.6f && timer <= 1.7f)
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
					else if (timer > 1.7f && timer <= 2.2f)
					{
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::White);
					}
					else if (timer > 2.2f && timer <= 2.3f)
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::Transparent);
					else if (timer > 2.3f && timer <= 2.8f)
					{
						keyboard[coords[4].x][coords[4].y].setFillColor(Color::White);
					}
					else if (timer > 2.8f && timer <= 2.9f)
						keyboard[coords[4].x][coords[4].y].setFillColor(Color::Transparent);
					else if (timer > 2.9f)
					{
						isOnGuessPart = true;
						i++;
					}
				}
				else if (i == 5)
				{
					if (timer > .0f && timer <= .6f)
					{
						keyboard[coords[1].x][coords[1].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));
						keyboard[coords[2].x][coords[2].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));
						keyboard[coords[3].x][coords[3].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));
						keyboard[coords[4].x][coords[4].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-allume"));

						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::Transparent);
						keyboard[coords[4].x][coords[4].y].setFillColor(Color::Transparent);
					}
					else if (timer > 0.6f && timer <= 1.f)
					{
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::White);
					}
					else if (timer > 1.f && timer <= 1.1f)
						keyboard[coords[1].x][coords[1].y].setFillColor(Color::Transparent);
					else if (timer > 1.1f && timer <= 1.6f)
					{
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::White);
					}
					else if (timer > 1.6f && timer <= 1.7f)
						keyboard[coords[2].x][coords[2].y].setFillColor(Color::Transparent);
					else if (timer > 1.7f && timer <= 2.2f)
					{
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::White);
					}
					else if (timer > 2.2f && timer <= 2.3f)
						keyboard[coords[3].x][coords[3].y].setFillColor(Color::Transparent);
					else if (timer > 2.3f && timer <= 2.8f)
					{
						keyboard[coords[4].x][coords[4].y].setFillColor(Color::White);
					}
					else if (timer > 2.8f && timer <= 2.9f)
						keyboard[coords[4].x][coords[4].y].setFillColor(Color::Transparent);
					else if (timer > 2.9f && timer <= 3.4f)
					{
						keyboard[coords[5].x][coords[5].y].setFillColor(Color::White);
					}
					else if (timer > 3.4f && timer <= 3.5f)
						keyboard[coords[5].x][coords[5].y].setFillColor(Color::Transparent);
					else if (timer > 3.5f)
					{
						isOnGuessPart = true;
						i++;
					}
				}
			}
			else
			{
				if (g.on_pressed(0, Xbox::Button::A) && keyboard[coords[j].x][coords[j].y].getGlobalBounds().contains(Vector2f(selector.getPosition().x, selector.getPosition().y)))
				{
					keyTime = 0.0f;

					if (j == currentRound)
					{
						keyboard[coords[j].x][coords[j].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-vrai"));
						keyboard[coords[j].x][coords[j].y].setFillColor(Color::White);

						lights[0].setTexture(&Cache::GetRessources<sf::Texture>("bouton_vert"));
						lights[1].setTexture(&Cache::GetRessources<sf::Texture>("neutre_rouge"));
						currentRound++;
						timer = 0.f;
						timerLight = 0;
						isValid = true;
					}
					else
					{
						keyboard[coords[j].x][coords[j].y].setTexture(&Cache::GetRessources<sf::Texture>("bouton-vrai"));
						keyboard[coords[j].x][coords[j].y].setFillColor(Color::White);
						j++;
					}
				}
				else if (g.on_pressed(0, Xbox::Button::A) && !keyboard[coords[j].x][coords[j].y].getGlobalBounds().contains(Vector2f(selector.getPosition().x, selector.getPosition().y)))
				{
					isWrong = true;
				}

				if (timerLight >= 0.3f)
				{
					lights[0].setTexture(&Cache::GetRessources<sf::Texture>("neutre_vert"));
					lights[1].setTexture(&Cache::GetRessources<sf::Texture>("neutre_rouge"));
				}

				if (isValid)
				{
					m_soundComplete.play();
					timerGood += _dt;

					if (timerGood >= .3f)
					{
						keyboard[coords[j].x][coords[j].y].setFillColor(Color::Transparent);
						j = 1;
						timerGood = 0.f;
						isValid = false;
						isOnGuessPart = false;
					}
				}

				if (isWrong)
				{
					m_soundFail.play();

					timerWrong += _dt;

					selector.setTexture(&Cache::GetRessources<sf::Texture>("curseur-red"));
					selector.setFillColor(Color::White);

					if (timerWrong >= .3f)
					{
						timer = 0.f;
						keyTime = 0.0f;
						currentRound = 1;

						i = 1;
						j = 1;
						lights[0].setTexture(&Cache::GetRessources<sf::Texture>("neutre_vert"));
						lights[1].setTexture(&Cache::GetRessources<sf::Texture>("bouton_rouge"));

						timerLight = 0;
						for (int i = 0; i < nbColumn; i++)
						{
							for (int j = 0; j < nbRow; j++)
							{
								selector.setTexture(&Cache::GetRessources<sf::Texture>("curseur"));
								keyboard[i][j].setFillColor(Color::Transparent);
							}
						}

						isWrong = false;
						timerWrong = 0.f;
						isOnGuessPart = false;
					}
				}
			}
		}
	}
}

void Memory::Render(RenderWindow& _target)
{
	_target.draw(bc);

	for (int i = 0; i < nbColumn; i++)
	{
		for (int j = 0; j < nbRow; j++)
			_target.draw(keyboard[i][j]);
	}

	for (auto it : lights)
		_target.draw(it);

	if (isPlaced && !display)
	{
		if (isOnGuessPart)
			_target.draw(selector);
	}
}
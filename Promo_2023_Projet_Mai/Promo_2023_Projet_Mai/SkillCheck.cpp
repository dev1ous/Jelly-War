#include "SkillCheck.h"
#include "Functions.h"
#include "Cache.h"
#include "Gamepad.h"
#include "Options.h"

void SkillCheck::InitSkillCheck()
{
	m_bufferSkillCheck.loadFromFile("../Ressources/Sons/FinalVersionSons/MiniJeuxCaptureEtVol/TestHabilite/remplissage.wav");
	m_soundSkillCheck.setBuffer(m_bufferSkillCheck);

	m_ecran.setTexture(Cache::GetRessources<sf::Texture>("jeuHabilite"));
	m_fond.setPosition({ 0,0 });
	m_fond.setSize({ 1920,1080 });
	m_fond.setFillColor(sf::Color::White);

	m_feedBack.setTexture(Cache::GetRessources<sf::Texture>("emplacement_atyr"));
	m_feedBack_A.setTexture(Cache::GetRessources<sf::Texture>("a_bon2"));
	m_feedBackLumineux_A.setTexture(Cache::GetRessources<sf::Texture>("A_bon3"));

	//m_feedBack.setPosition({ 915, 557.5f });
	//m_feedBack_A.setPosition({ m_feedBack.getPosition().x + 15,m_feedBack.getPosition().y + 15 });
	//m_feedBackLumineux_A.setPosition(m_feedBack.getPosition().x +10, m_feedBack.getPosition().y +10);

	m_separate.setTexture(Cache::GetRessources<sf::Texture>("greg"));
	m_separate.setPosition({ 673.f,850.f });

	m_SpriteSkillCheckBar.setTexture(Cache::GetRessources<sf::Texture>("barre"));
	m_SpriteSkillCheckBar.setPosition({ 350.f,400.f });

	m_SkillCheckBar.setSize({ 881.f, 138.f });
	m_SkillCheckBar.setFillColor(sf::Color::Transparent);
	m_SkillCheckBar.setPosition(525.f, 403.f);
	m_SkillCheckBar.setOutlineColor(sf::Color::Transparent);
	m_SkillCheckBar.setOutlineThickness(-2.f);

	m_ProgressBar.setSize({ 50.f,138.f });
	m_ProgressBar.setTexture(&Cache::GetRessources<sf::Texture>("joueur"));
	m_ProgressBar.setPosition(526.f, 404.f);

	m_MovingBar.setSize({ 150.f,138.f });
	m_MovingBar.setTexture(&Cache::GetRessources<sf::Texture>("ia_sprite"));
	m_MovingBar.setTextureRect(sf::IntRect(0, 0, 150, 138));
	m_MovingBar.setPosition(m_SkillCheckBar.getPosition().x + 50, m_SkillCheckBar.getPosition().y);

	m_OtherBar.setTexture(Cache::GetRessources<sf::Texture>("chargement_check"));
	m_OtherBar.setPosition(600.f, 850.f);

	m_ProgressionOtherBar.setTextureRect(m_rectProgressBar);
	m_ProgressionOtherBar.setTexture(Cache::GetRessources<sf::Texture>("uyop"));
	m_ProgressionOtherBar.setPosition(m_OtherBar.getPosition().x + 2, m_OtherBar.getPosition().y + 2);

	m_Dir = this->RandomDir(m_RngDir);
	m_Timer = this->RandomTimer(m_RngTimer);
	m_Speed = this->RandomSpeed(m_RngSpeed);
};


void SkillCheck::RunSkillCheck(const float& dt)
{
	Gamepads g;
	if (!debut && !fin)
	{
		if ((g.is_pressed(0, Xbox::Button::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
		{
			m_ProgressBar.move(m_velocity * m_multiplier * dt, 0);
		}
		else
		{
			m_ProgressBar.move(-m_velocity * m_decreaser * dt, 0);
		}

		m_ProgressBar.setPosition(
			std::clamp(m_ProgressBar.getPosition().x, m_SkillCheckBar.getPosition().x + 1, m_SkillCheckBar.getGlobalBounds().left + m_SkillCheckBar.getGlobalBounds().width - 50.f),
			m_ProgressBar.getPosition().y
		);
	}
}

void SkillCheck::MovingSkillCheckBar(const float& dt)
{
	if (!debut && !fin)
	{
		m_Dir == direction::gauche ? m_MovingBar.move(-m_Speed * m_multiplierMovingBox * dt, 0) : m_MovingBar.move(m_Speed * m_multiplierMovingBox * dt, 0);

		if (!m_SkillCheckBar.getGlobalBounds().contains(m_MovingBar.getGlobalBounds().left + m_MovingBar.getGlobalBounds().width, m_MovingBar.getGlobalBounds().top) && m_Dir == direction::droite)
		{
			m_MovingBar.move(-m_Speed * m_multiplierMovingBox * dt, 0);
			m_Timer = this->RandomTimer(m_RngDir);
			m_Dir = this->RandomDir(m_RngTimer);
			m_Speed = this->RandomSpeed(m_RngSpeed);
		}
		else if (!m_SkillCheckBar.getGlobalBounds().contains(m_MovingBar.getPosition()) && m_Dir == direction::gauche)
		{
			m_MovingBar.move(m_Speed * m_multiplierMovingBox * dt, 0);
			m_Timer = this->RandomTimer(m_RngDir);
			m_Dir = this->RandomDir(m_RngTimer);
			m_Speed = this->RandomSpeed(m_RngSpeed);
		}
	}
}

void SkillCheck::GenerateRandomMove(const float& dt)
{
	if (!debut && !fin)
	{
		if (m_Timer <= 0.f)
			m_SwitchDir = true;

		if (!m_SwitchDir)
			m_Timer -= dt;
		else
		{
			m_Timer = this->RandomTimer(m_RngDir);
			m_Dir = this->RandomDir(m_RngTimer);
			m_Speed = this->RandomSpeed(m_RngSpeed);

			m_SwitchDir = false;
		}
	}
}

void SkillCheck::Progression(const float& dt)
{
	m_soundSkillCheck.setVolume(Options::volumeBruitages);
	if (!debut && !fin)
	{
		AnimProgressBar(dt);

		if (m_MovingBar.getGlobalBounds().intersects(m_ProgressBar.getGlobalBounds()))
		{
			m_CurrentScore += 16.f * dt;
			m_rectProgressBar.width = static_cast<int>(std::lerp(0.f, m_OtherBar.getGlobalBounds().width - 4.f, std::clamp(m_CurrentScore / m_ScoreNeeded, 0.f, 1.f)));
			m_rectProgressBar.height = static_cast<int>(m_OtherBar.getGlobalBounds().height - 4.f);
			m_ProgressionOtherBar.setTextureRect(m_rectProgressBar);
			m_MovingBar.setTextureRect(sf::IntRect(150, 0, 150, 138));
			if (m_soundSkillCheck.getStatus() != sf::Sound::Status::Playing)
				m_soundSkillCheck.play();
		}
		else
		{
			if (m_CurrentScore > 0)
			{
				m_CurrentScore -= 8.f * dt;
				m_rectProgressBar.width = static_cast<int>(std::lerp(0.f, m_OtherBar.getGlobalBounds().width - 4.f, std::clamp(m_CurrentScore / m_ScoreNeeded, 0.f, 1.f)));
				m_rectProgressBar.height = static_cast<int>(m_OtherBar.getGlobalBounds().height - 4.f);
				m_ProgressionOtherBar.setTextureRect(m_rectProgressBar);
				m_MovingBar.setTextureRect(sf::IntRect(0, 0, 150, 138));
			}
		}
	}
	else if (!fin)
	{
		Go_debut(dt);
	}
	if (m_CurrentScore >= 100.f)
	{
		fin = true;
		Go_fin(dt);
	}

}

void SkillCheck::AnimProgressBar(const float& dt)
{
	if (m_rectProgressBar.left >= 4614) {
		m_rectProgressBar.left = 0;
		m_timerRect = 0.f;
	}
	else
	{
		m_timerRect += dt;
		if (m_timerRect > 0.1f) {
			m_rectProgressBar.left += 769;
			m_timerRect = 0.f;
		}
	}

	m_ProgressionOtherBar.setTextureRect(m_rectProgressBar);
}

void SkillCheck::drawBars(WindowManager& w)
{
	Gamepads g;
	//w.draw(m_fond);
	w.draw(m_ecran);
	w.draw(m_SkillCheckBar);
	w.draw(m_SpriteSkillCheckBar);
	w.draw(m_MovingBar);
	w.draw(m_ProgressBar);
	w.draw(m_ProgressionOtherBar);
	w.draw(m_feedBack);
	if (g.is_pressed(0, Xbox::Button::A))
		w.draw(m_feedBackLumineux_A);
	else
		w.draw(m_feedBack_A);
	w.draw(m_OtherBar);
	w.draw(m_separate);
}

void SkillCheck::Go_debut(const float& dt)
{
	m_ecran.setPosition({ 0,0 - posy });
	m_fond.setPosition({ 0,0 - posy });

	m_separate.setPosition({ 673.f,850.f - posy });

	m_feedBack.setPosition({ 915, 557.5f - posy });
	m_feedBack_A.setPosition({ m_feedBack.getPosition().x + 15,(m_feedBack.getPosition().y + 15) });
	m_feedBackLumineux_A.setPosition({ m_feedBack.getPosition().x + 10,(m_feedBack.getPosition().y + 10) });


	m_MovingBar.setPosition(525.f + 50, 403.f - posy);


	m_SpriteSkillCheckBar.setPosition({ 350.f,400.f - posy });


	m_SkillCheckBar.setPosition(525.f, 403.f - posy);

	m_ProgressBar.setPosition(526.f, 404.f - posy);

	m_OtherBar.setPosition(600.f, 850.f - posy);

	m_ProgressionOtherBar.setPosition(m_OtherBar.getPosition().x + 2, m_OtherBar.getPosition().y + 2);

	posy -= 600.f * dt;

	if (posy <= 0)
	{
		posy = 0;

		m_ecran.setPosition({ 0,0 - posy });
		m_fond.setPosition({ 0,0 - posy });

		m_separate.setPosition({ 673.f,850.f - posy });

		m_feedBack.setPosition({ 915, 557.5f - posy });
		m_feedBack_A.setPosition({ m_feedBack.getPosition().x + 15,(m_feedBack.getPosition().y + 15) });
		m_feedBackLumineux_A.setPosition({ m_feedBack.getPosition().x + 10,(m_feedBack.getPosition().y + 10) });


		m_MovingBar.setPosition(525.f + 50, 403.f - posy);


		m_SpriteSkillCheckBar.setPosition({ 350.f,400.f - posy });


		m_SkillCheckBar.setPosition(525.f, 403.f - posy);

		m_ProgressBar.setPosition(526.f, 404.f - posy);

		m_OtherBar.setPosition(600.f, 850.f - posy);

		m_ProgressionOtherBar.setPosition(m_OtherBar.getPosition().x + 2, m_OtherBar.getPosition().y + 2);
		debut = false;
	}
}

void SkillCheck::Go_fin(const float& dt)
{
	m_ecran.setPosition({ 0,0 - posy });
	m_fond.setPosition({ 0,0 - posy });

	m_separate.setPosition({ m_separate.getPosition().x ,850.f - posy });

	m_feedBack.setPosition({ m_feedBack.getPosition().x, 557.5f - posy });
	m_feedBack_A.setPosition({ m_feedBack.getPosition().x + 15,(m_feedBack.getPosition().y + 15) });
	m_feedBackLumineux_A.setPosition({ m_feedBack.getPosition().x + 10,(m_feedBack.getPosition().y + 10) });

	m_MovingBar.setPosition(m_MovingBar.getPosition().x, 400.f - posy);


	m_SpriteSkillCheckBar.setPosition({ m_SpriteSkillCheckBar.getPosition().x,400.f - posy });


	m_SkillCheckBar.setPosition(m_SkillCheckBar.getPosition().x, 403.f - posy);

	m_ProgressBar.setPosition(m_ProgressBar.getPosition().x, 404.f - posy);

	m_OtherBar.setPosition(m_OtherBar.getPosition().x, 850.f - posy);

	m_ProgressionOtherBar.setPosition(m_ProgressionOtherBar.getPosition().x, 850.f + 2 - posy);

	posy += 600.f * dt;

	if (posy >= 1080)
	{
		posy = 1080;
		m_ecran.setPosition({ 0,0 - posy });
		m_fond.setPosition({ 0,0 - posy });

		m_separate.setPosition({ m_separate.getPosition().x, 850.f - posy });

		m_feedBack.setPosition({ m_feedBack.getPosition().x, 557.5f - posy });
		m_feedBack_A.setPosition({ m_feedBack.getPosition().x + 15,(m_feedBack.getPosition().y + 15) });
		m_feedBackLumineux_A.setPosition({ m_feedBack.getPosition().x + 10,(m_feedBack.getPosition().y + 10) });

		m_MovingBar.setPosition(m_MovingBar.getPosition().x, 400.f - posy);


		m_SpriteSkillCheckBar.setPosition({ m_SpriteSkillCheckBar.getPosition().x,400.f - posy });


		m_SkillCheckBar.setPosition(m_SkillCheckBar.getPosition().x, 403.f - posy);

		m_ProgressBar.setPosition(m_ProgressBar.getPosition().x, 404.f - posy);

		m_OtherBar.setPosition(m_OtherBar.getPosition().x, 850.f - posy);

		m_ProgressionOtherBar.setPosition(m_ProgressionOtherBar.getPosition().x, 850.f + 2 - posy);
		win = true;
	}
}

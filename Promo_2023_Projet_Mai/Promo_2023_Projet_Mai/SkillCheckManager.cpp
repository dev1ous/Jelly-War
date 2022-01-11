#include "SkillCheckManager.h"

SkillCheckManager::SkillCheckManager()
{
	m_sc.InitSkillCheck();
}

void SkillCheckManager::processEvents(const sf::Event& e)
{
}

void SkillCheckManager::update(const float& dt)
{
	m_sc.GenerateRandomMove(dt);
	m_sc.MovingSkillCheckBar(dt);
	m_sc.RunSkillCheck(dt);
	m_sc.Progression(dt);
}

void SkillCheckManager::draw(WindowManager& window)
{
	m_sc.drawBars(window);
}

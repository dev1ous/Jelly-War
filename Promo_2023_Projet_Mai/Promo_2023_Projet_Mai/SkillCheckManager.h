#ifndef SKILLCHECKMANAGER_H
#define SKILLCHECKMANAGER_H

#include "SkillCheck.h"

class SkillCheckManager
{
	SkillCheck m_sc;

	SkillCheckManager(const SkillCheckManager&) = delete;
	SkillCheckManager& operator=(const SkillCheckManager&) = delete;

	
public:

	SkillCheckManager();
	~SkillCheckManager() = default;

	void processEvents(const sf::Event&);
	void update(const float&);
	void draw(WindowManager&);

	inline bool Get_Win() { return m_sc.Get_Win(); }
};
#endif

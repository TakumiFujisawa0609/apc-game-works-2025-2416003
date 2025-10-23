#include "SkillManager.h"
#include "../Object/Skill/SkillBase.h"
#include "../Object/Skill/SlashSkill.h"


SkillManager::SkillManager(void)
{
}

SkillManager::~SkillManager(void)
{
}

void SkillManager::Init(void)
{
}

void SkillManager::Update(void)
{
	for (const auto skill : skills_)
	{
		skill->Update();
	}
}

void SkillManager::Draw(void)
{
	for (const auto skill : skills_)
	{
		skill->Draw();
	}
}

void SkillManager::Release(void)
{

}

void SkillManager::SlashSkill(void)
{
	//SkillBase* skill = 

	
}

std::list<SkillBase*> SkillManager::GetSkills(void)
{
	return skills_;
}

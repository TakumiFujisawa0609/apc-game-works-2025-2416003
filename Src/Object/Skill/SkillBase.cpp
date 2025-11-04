#include "SkillBase.h"

SkillBase::SkillBase(SKILL_KIND skillKind)
{
	skillData_.id = skillTable[static_cast<int>(skillKind)].id;
	skillData_.mp = skillTable[static_cast<int>(skillKind)].mp;
	skillData_.name = skillTable[static_cast<int>(skillKind)].name;
	skillData_.power = skillTable[static_cast<int>(skillKind)].power;
	skillData_.type = skillTable[static_cast<int>(skillKind)].type;
}

SkillBase::~SkillBase()
{
}

void SkillBase::Init(void)
{
}

void SkillBase::Update(void)
{

}

void SkillBase::Draw(void)
{

}

void SkillBase::Release(void)
{

}

void SkillBase::Attack(ActorBase* attacker, ActorBase* target)
{

	switch (skillData_.type)
	{
	case SKILL_TYPE::NON:
		break;
	case SKILL_TYPE::ATTACK:
		break;
	case SKILL_TYPE::DEFENSE:
		break;
	case SKILL_TYPE::HEAL:
		break;
	case SKILL_TYPE::BUFF:
		break;
	case SKILL_TYPE::DEBUFF:
		break;
	default:
		break;
	}
}

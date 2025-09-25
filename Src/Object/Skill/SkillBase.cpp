#include "SkillBase.h"

void SkillBase::Init(SKILLTYPE skill_type)
{
	skill_type_ = skill_type;

	Load();

	SetParam();
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

SkillBase::SKILLTYPE SkillBase::GetSkill(void)
{
	return skill_type_;
}

void SkillBase::Load(void)
{
}

void SkillBase::SetParam(void)
{
	skill_name_ = "í èÌçUåÇ";
	skill_Atk_Power_ = 1;
}

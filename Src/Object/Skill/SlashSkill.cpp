#include "SlashSkill.h"

void SlashSkill::Update(void)
{
	SkillBase::Update();
}

void SlashSkill::Draw(void)
{
	SkillBase::Draw();
}

void SlashSkill::Release(void)
{
	SkillBase::Release();
}

void SlashSkill::InitLoad(void)
{
}

void SlashSkill::SetParam(void)
{

	//スキルタイプ
	skillType_ = SKILLTYPE::ATTACK;
	//スキル
	skill_ = SKILL::SLASH;
	//スキル名
	skillName_ = "斬撃（SLASH）";
	//スキルごとのスキル固定ダメージ倍率
	baseDamege_ = 1.0f;
}









#include "LimitBreakSkill.h"


void LimitBreakSkill::Update(void)
{
	SkillBase::Update();
}

void LimitBreakSkill::Draw(void)
{
	SkillBase::Draw();
}

void LimitBreakSkill::Release(void)
{
	SkillBase::Release();
}

void LimitBreakSkill::InitLoad(void)
{
}

void LimitBreakSkill::SetParam(void)
{

	//スキルタイプ
	skillType_ = SKILLTYPE::ATTACK;
	//スキル
	skill_ = SKILL::LIMIT_BREAK;
	//スキル名
	skillName_ = "リミットブレイク";
	//スキルごとのスキル固定ダメージ倍率
	baseDamege_ = 1.0f;
}









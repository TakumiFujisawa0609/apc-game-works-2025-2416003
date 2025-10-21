#include "LimitBreak.h"

LimitBreak::LimitBreak(void)
{
}

LimitBreak::~LimitBreak(void)
{
}

void LimitBreak::Update(void)
{
}

void LimitBreak::Draw(void)
{
}

void LimitBreak::Release(void)
{
}

void LimitBreak::InitLoad(void)
{
}

void LimitBreak::SetParam(void)
{
	//スキル名
	skillName_ = "リミットブレイク";
	//スキルタイプ
	skillType_ = SKILLTYPE::ATTACK;
}

void LimitBreak::SkillProcess(int atk, int def, int intel)
{
	skillDamege_ =  LIMITBREAK_MAGNIFICATION;
}

void LimitBreak::Damege(int hp, int dmg, int def)
{
	damege_ = hp - (skillDamege_ - def);
}

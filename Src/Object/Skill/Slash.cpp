#include "Slash.h"


Slash::Slash(void)
{
}

Slash::~Slash(void)
{
}

void Slash::Update(void)
{
	

	SkillBase::Update();
}

void Slash::Draw(void)
{
	SkillBase::Draw();
}

void Slash::Release(void)
{
	SkillBase::Release();
}

void Slash::InitLoad(void)
{
}

void Slash::SetParam(void)
{

	skillName_ = "ƒXƒ‰ƒbƒVƒ…";
}

void Slash::SkillProcess(int atk, int def, int intel)
{
	skillDamege_ = atk * SLASH_MAGNIFICATION;
}

void Slash::Damege(int hp, int dmg, int def)
{
	damege_ = hp - (skillDamege_ - def);
}



#include "ActorBase.h"


void ActorBase::Init(void)
{
}

void ActorBase::Update(void)
{
}

void ActorBase::Draw(void)
{
}

void ActorBase::Release(void)
{
}

int ActorBase::costMp(int costMp, int mp)
{
	//Šù‚ÉMP‚ª‚O‚Ìê‡
	if (mp == 0)
	{
		return mp;
	}

	mp = mp - costMp;

	//MÁ”ï‚µ‚Ä‚O‚É‚È‚Á‚½ê‡
	if (mp <= 0)
	{	
		mp = 0;
	}

	return mp;
}

int ActorBase::addMp(int addMp, int targetMp, int targetMaxMp)
{
	if (targetMp >= targetMaxMp)
	{

	}

	targetMp = targetMp + addMp;

	if (targetMp >= targetMaxMp)
	{
		targetMp = targetMaxMp;
	}

	return targetMp;
}

void ActorBase::addHp(int addHp, int targetHp)
{
	targetHp = addHp + targetHp;
}

int ActorBase::PhysicsDamage(float skillPow, int attckerAtk, int targetDef, int targetHp)
{
	int damege;

	damege = (attckerAtk* skillPow) - targetDef;

	targetHp = targetHp - damege;

	return targetHp;
}

int ActorBase::MagicDamage(float skillPow, int attckerWis, int targetWis, int targetHp)
{
	int damage;

	damage = (attckerWis * skillPow) - targetWis;

	targetHp = targetHp - damage;

	return targetHp;
}











#include "ActorBase.h"


void ActorBase::Init(void)
{
	SetParam();
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

int ActorBase::SetHp()
{
	return hp_;
}

int ActorBase::SetMaxHp()
{
	return maxHp_;
}

int ActorBase::SetMp()
{
	return mp_;
}

int ActorBase::SetMaxMp()
{
	return maxMp_;
}

int ActorBase::SetAtk()
{
	return atk_;
}

int ActorBase::SetDef()
{
	return def_;
}

int ActorBase::SetWis()
{
	return wis_;
}

int ActorBase::addHp(float skillPow, int attckerWis,  int attckerHp , int attckerMaxHp)
{
	int addHp_ = skillPow * attckerWis;

	if (attckerHp <= attckerMaxHp)
	{
		attckerHp = attckerHp * addHp_;

		//HPÇÃç≈ëÂílÇí¥Ç¶Ç»Ç¢ÇÊÇ§Ç…
		if (attckerHp > attckerMaxHp)
		{
			attckerHp == attckerMaxHp;
		}
	}

	return attckerHp;
}

int ActorBase::costMp(int costMp, int mp)
{
	//ä˘Ç…MPÇ™ÇOÇÃèÍçá
	if (mp == 0)
	{
		return mp;
	}

	mp = mp - costMp;

	//Mè¡îÔÇµÇƒÇOÇ…Ç»Ç¡ÇΩèÍçá
	if (mp <= 0)
	{	
		mp = 0;
	}

	return mp;
}

int ActorBase::addMp(int addMp, int targetMp, int targetMaxMp)
{

	targetMp = targetMp + addMp;

	if (targetMp >= targetMaxMp)
	{
		targetMp = targetMaxMp;
	}

	return targetMp;
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











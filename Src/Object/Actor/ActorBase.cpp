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

void ActorBase::SlashAttack(int atkPower,int defPower,int hp)
{
	int atk_ = atkPower;
	int def_ = defPower;
	int hp_ = hp;

	hp_ = hp_ - (atk_ - def_);
}

void ActorBase::StatusLoadData(void)
{
}

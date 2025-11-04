#include "Player.h"

void Player::Init(void)
{
	LoadStatusData();
}

void Player::Update(void)
{
}

void Player::Draw(void)
{
}

void Player::Release(void)
{
}

void Player::SelectSkill(SKILL skill)
{
}

void Player::UseSkill(void)
{
}

void Player::ProcessSkill(SKILL skill)
{
}

void Player::LoadStatusData(void)
{
	PlayerData Status;

	Status.hp_ = 100;
	Status.atk_ = 20;
	Status.def_ = 5;
	Status.speed_ = 5;
	Status.intel_ = 5;

	Status.maxHp_ = 200;
	Status.dex_ = 10;
	Status.collectExp_ = 0;

}

#include "Player.h"

void Player::Init(void)
{
	
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

void Player::SetStatus()
{
	 status.hp_ = 100;		//体力
	 status.maxHp_ = 100;	//最大体力

	 status.sp_ = 50;		//スキルポイント
	 status.maxSp_ = 50;	//最大スキルポイント

	 status.atk_  = 30;		//攻撃力
	 status.def_ = 30;		//防御力
	 status.speed_ = 20;	//すばやさ
	 status.wisdom_ = 20;	//かしこさ
}






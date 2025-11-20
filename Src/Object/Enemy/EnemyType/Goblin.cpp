#include "Goblin.h"
#include"../../../Common/AnimationController.h"
#include "../../../Application.h"

Goblin::Goblin(void)
{
}

Goblin::~Goblin(void)
{
}

void Goblin::Update()
{
	
}

void Goblin::Draw()
{
	
}

void Goblin::Release(void)
{
	
}

void Goblin::InitLoad()
{
}

void Goblin::InitTransform()
{
	/// @init transform 座標
	pos_ = DEFAULT_ENEMY_POS;
	/// @init transform 大きさ
	scl_ = { 1.0f,1.0f,1.0f };
	/// @init transform 角度
	angles_ = { 0.0f,0.0f,0.0f };
}

void Goblin::InitAnimation()
{
	

}

void Goblin::InitPost()
{
}

void Goblin::SetParam()
{
	status.hp_ = 60;		//体力
	status.maxHp_ = 60;		//最大体力

	status.sp_ = 50;		//スキルポイント
	status.maxSp_ = 50;		//最大スキルポイント

	status.atk_ = 30;		//攻撃力
	status.def_ = 10;		//防御力
	status.speed_ = 10;		//すばやさ
	status.wisdom_ = 5;		//かしこさ
}


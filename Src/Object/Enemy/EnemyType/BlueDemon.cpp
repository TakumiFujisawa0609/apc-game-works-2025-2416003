#include <DxLib.h>
#include "BlueDemon.h"
#include "../../../Application.h"

BlueDemon::BlueDemon(void)
{
}

BlueDemon::~BlueDemon(void)
{
}

void BlueDemon::Init(void)
{

	//ベースマネージャー忘れて一旦
	/// @init transform 座標
	pos_ = DEFAULT_ENEMY_POS;
	/// @init transform 大きさ
	scl_ = { 1.0f,1.0f,1.0f };
	/// @init transform 角度
	angles_ = { 0.0f,0.0f,0.0f };


	MV1LoadModel((Application::PATH_MODEL + "Enemy/Goblin.mv1").c_str());

	MV1SetPosition(modelId, pos_);
}

void BlueDemon::Update(void)
{
}

void BlueDemon::Draw(void)
{
	MV1DrawModel(modelId);
}

void BlueDemon::Release(void)
{
	MV1DeleteModel(modelId);
}


void BlueDemon::SetParam()
{
	status.hp_ = 50;		//体力
	status.maxHp_ = 50;		//最大体力

	status.sp_ = 50;		//スキルポイント
	status.maxSp_ = 50;		//最大スキルポイント

	status.atk_ = 40;		//攻撃力
	status.def_ = 10;		//防御力
	status.speed_ = 10;		//すばやさ
	status.wisdom_ = 5;		//かしこさ
}

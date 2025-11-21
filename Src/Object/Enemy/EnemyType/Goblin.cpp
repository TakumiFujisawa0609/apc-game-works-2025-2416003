#include <DxLib.h>
#include "Goblin.h"
#include"../../../Common/AnimationController.h"
#include "../../../Application.h"

Goblin::Goblin(void)
{
}

Goblin::~Goblin(void)
{
}

void Goblin::Init(void)
{
	//ベースマネージャー忘れて一旦
	/// @init transform 座標
	pos_ = DEFAULT_ENEMY_POS;
	/// @init transform 大きさ
	scl_ = { 1.0f,1.0f,1.0f };
	/// @init transform 角度
	angles_ = { 0.0f,0.0f,0.0f };

	modelId = MV1LoadModel((Application::PATH_MODEL + "Enemy/Goblin.mv1").c_str());

	MV1SetScale(modelId, scl_);
	MV1SetPosition(modelId, pos_);
	MV1SetRotationXYZ(modelId, angles_);

	//ステータス読みこみ
	SetParam();
}

void Goblin::Update()
{
	MV1SetPosition(modelId, pos_);
}

void Goblin::Draw()
{
	MV1DrawModel(modelId);
}


void Goblin::Release(void)
{
	MV1DeleteModel(modelId);
}

VECTOR Goblin::GetPos()
{
	return pos_;
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


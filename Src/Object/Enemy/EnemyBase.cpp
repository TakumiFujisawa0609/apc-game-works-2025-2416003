#include "EnemyBase.h"
#include "../../Common/AnimationController.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Utility/AsoUtility.h"



void EnemyBase::Init(TYPE type, int baseModelId)
{
	//エネミーの種別
	type_ = type;
	
	//modelId_ = MV1LoadModel(baseModelId);
	
	//座標の設定
	pos_ = DEFAULT_ENEMY_POS;
	//モデルの角度設定
	angles_ = { 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f };

	//パラメーター設定
	SetParam();
	//モデルの大きさ
	MV1SetScale(modelId_, scl_);
	// 角度
	MV1SetRotationXYZ(modelId_, angles_);

	
	
	// モデルアニメーション制御の初期化
	animationController_ = new AnimationController(modelId_);

	for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
	{
		animationController_->AddInFbx(i, 30.0f, i);
	}
	// 初期アニメーション再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));

	//初期状態
	ChangeState(STATE::STANBY);
}

void EnemyBase::Update()
{
	MV1SetPosition(modelId_, pos_);
	switch (state_)
	{
	case EnemyBase::STATE::STANBY:
		UpdateStandby();
		break;
	case EnemyBase::STATE::DEAD:
		UpdateDeadReact();
		break;
	case EnemyBase::STATE::END:
		UpdateEnd();
		break;
	}

	// アニメーションの更新
	animationController_->Update();
	
}

void EnemyBase::Draw()
{

	switch (state_)
	{
	case EnemyBase::STATE::STANBY:
		DrawStandby();
		break;
	case EnemyBase::STATE::DEAD:
		DrawDeadReact();
		break;
	case EnemyBase::STATE::END:
		DrawEnd();
		break;
	}

	// モデルの描画
	MV1DrawModel(modelId_);
	
}

void EnemyBase::Release()
{
	MV1DeleteModel(modelId_);
	delete animationController_;
}

void EnemyBase::ChangeState(STATE state)
{
	state_ = state;
	switch (state_)
	{
	case EnemyBase::STATE::STANBY:
		ChangeStandby();
		break;
	case EnemyBase::STATE::HIT:
		ChangeStandby();
		break;
	case EnemyBase::STATE::DEAD:
		ChangeDeadReact();
		break;
	case EnemyBase::STATE::END:
		ChangeEnd();
		break;
	}
}

VECTOR EnemyBase::GetPos(void)
{
	return pos_;
}


int EnemyBase::GetHp(void)
{
	return hp_;
}

void EnemyBase::HitDamage(int damage)
{
	if (hp_ <= 0)
	{
		hp_ = 0;
		ChangeState(STATE::DEAD);
	}
}

void EnemyBase::ChangeStandby(void)
{	
	//拡散光を標準に戻す
	MV1SetMaterialDifColor(modelId_, 0, COLOR_DIF_DEFAULT);
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
}
void EnemyBase::ChangeDeadReact(void)
{
	// DEATHアニメーションを再生すること！(ループ無し)
	animationController_->Play(static_cast<int>(ANIM_TYPE::DEATH), false);
}
void EnemyBase::ChangeEnd(void)
{
}
void EnemyBase::UpdateStandby(void)
{

}
void EnemyBase::UpdateDeadReact(void)
{
	cntDamaged_--;
	if (cntDamaged_ < 0 && animationController_->IsEnd())
	{
		ChangeState(STATE::END);
	}
}

void EnemyBase::UpdateEnd(void)
{
}
void EnemyBase::DrawStandby(void)
{
	MV1DrawModel(modelId_);
}
void EnemyBase::DrawDeadReact(void)
{
	if (cntDamaged_ % TERM_BLINK == 0)
	{
		MV1SetMaterialDifColor(modelId_, 0, COLOR_DIF_DEFAULT);
	}
	else
	{
		MV1SetMaterialDifColor(modelId_, 0, COLOR_DIF_BLINK);
	}
	//モデルの描画
	MV1DrawModel(modelId_);
}
void EnemyBase::DrawEnd(void)
{
}
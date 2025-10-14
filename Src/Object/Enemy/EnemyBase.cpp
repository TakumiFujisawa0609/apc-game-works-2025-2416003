#include "EnemyBase.h"
#include "../../Manager/EnemyStatusManager.h"
#include "../../Common/AnimationController.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Utility/AsoUtility.h"




void EnemyBase::Init(TYPE type)
{
	
	//モデル等の読み込み
	InitLoad();
	// Transform初期化
	InitTransform();
	// 大きさ、回転、座標のモデル設定
	InitTransformPost();
	// アニメーションの初期化
	InitAnimation();
	// 初期化後の個別処理
	InitPost();

	SetParam();
	/// @Init エネミー種別
	type_ = type;

	ChangeState(STATE::STANBY);
	EnemyStatusManager::Getinstance();
	
	const EnemyData& baseData = EnemyStatusManager::Getinstance()->GetEnemyData(type_);

	//数値変化可能なパラメータ
	hp_ =  baseData.hp_;
	atk_ = baseData.atk_;
	def_= baseData.def_;
	speed_ = baseData.speed_ ;
	intel_ = baseData.intel_ ;
	
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



void EnemyBase::HitDamage(int damage)
{
	hp_ -= damage - def_;
	if (hp_ <= 0)
	{
		hp_ = 0;
		ChangeState(STATE::DEAD);
	}
}

void EnemyBase::InitTransformPost(void)
{
	// 大きさをモデルに反映
	MV1SetScale(modelId_, scl_);

	// 角度から方向に変換する
	moveDir_ = { sinf(angles_.y), 0.0f, cosf(angles_.y) };
	preInputDir_ = moveDir_;

	// 行列の合成(子, 親と指定すると親⇒子の順に適用される)
	MATRIX mat = MatrixUtility::Multiplication(localAngles_, angles_);
	// 回転行列をモデルに反映
	MV1SetRotationMatrix(modelId_, mat);

	// 座標をモデルに反映
	MV1SetPosition(modelId_, pos_);
}

void EnemyBase::DelayRotate(void)
{
	// 移動方向から角度に変換する
	float goal = atan2f(moveDir_.x, moveDir_.z);

	// 常に最短経路で補間
	angles_.y = AsoUtility::LerpAngle(angles_.y, goal, 0.2f);
}

void EnemyBase::ChangeStandby(void)
{
	// 歩くアニメーションを再生すること！(ループ再生有り)
	animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
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
	if (animationController_->IsEnd())
	{
		ChangeState(STATE::END);
	}
}
void EnemyBase::UpdateEnd(void)
{
}
void EnemyBase::DrawStandby(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}
void EnemyBase::DrawDeadReact(void)
{
	MV1DrawModel(modelId_);
}
void EnemyBase::DrawEnd(void)
{
}
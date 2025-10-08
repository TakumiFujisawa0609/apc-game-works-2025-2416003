#include "EnemyBase.h"
#include "../../Common/AnimationController.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Utility/AsoUtility.h"


void EnemyBase::Init()
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
}

void EnemyBase::Update()
{
	MV1SetPosition(modelId_, pos_);
	// アニメーションの更新
	animationController_->Update();
	
}

void EnemyBase::Draw()
{

	MV1DrawModel(modelId_);
}

void EnemyBase::Release()
{
	MV1DeleteModel(modelId_);
	delete animationController_;
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


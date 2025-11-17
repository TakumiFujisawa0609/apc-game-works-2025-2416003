#include "EnemyBase.h"
#include "../Enemy/Manger/EnemyStatusManager.h"
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

	EnemyStatusManager::Getinstance();
	
	//
	const EnemyData& baseData = EnemyStatusManager::Getinstance()->GetEnemyData(type_);

	//数値変化可能なパラメータ
	hp_ =  baseData.hp_;
	atk_ = baseData.atk_;
	def_= baseData.def_;
	speed_ = baseData.speed_ ;
	wisdom_ = baseData.intel_ ;
	
}

void EnemyBase::Update()
{
	
	// アニメーションの更新
	animationController_->Update();
	
}

void EnemyBase::Draw()
{

	

	// モデルの描画
	MV1DrawModel(modelId_);
	
}

void EnemyBase::Release()
{
	MV1DeleteModel(modelId_);
	delete animationController_;
}


VECTOR EnemyBase::GetPos(void)
{
	return pos_;
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




#pragma once
#include <DxLib.h>
class AnimationController;

class EnemyBase
{
public:

	//アニメーション種別
	enum class ANIM_TYPE
	{
		ATTACK,
		DEATH,
		HIT_REACT,
		IDLE,
		JUMP,
		RUN,
		WALK,
		MAX,
	};

	// エネミー種別
	enum class TYPE
	{
		SLIME,
		GOBLIN,
	};

	//敵の行動状態
	enum class STATE
	{
		NONE,
		STANBY,
		ATTACK,
		HIT,
		DEAD,
		END,
	};

	void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	

protected:

	// アニメーション制御
	AnimationController* animationController_;

	// アニメーション種別
	int animType_;
	// モデル情報
	int modelId_;


	VECTOR pos_;
	VECTOR angles_;
	VECTOR scl_;
	VECTOR localAngles_;

	// 移動方向
	VECTOR moveDir_;
	VECTOR preInputDir_;

	//エネミーステータス
	virtual void  SetParam() = 0;

	// リソースロード
	virtual void InitLoad(void) = 0;

	// 大きさ、回転、座標の初期化
	virtual void InitTransform(void) = 0;

	// 大きさ、回転、座標のモデル設定
	virtual void InitTransformPost(void);

	// アニメーションの初期化
	virtual void InitAnimation(void) = 0;

	// 初期化後の個別処理
	virtual void InitPost(void) = 0;

	// 移動処理
	//virtual void Move(void);

	// 遅延回転処理
	void DelayRotate(void);

private:

	
	
	
};


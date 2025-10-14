#pragma once
#include <DxLib.h>
#include "ActorBase.h"
class AnimationController;
class MatrixUtility;
class Camera;

class MapPlayer : public ActorBase
{
public:

	// アニメーションの再生速度
	static constexpr float SPEED_ANIM = 40.0f;

	// 回避移動スピード
	static constexpr float SPEED_DODGE = 20.0f;
	// プレイヤーの初期座標
	static constexpr VECTOR DEFAULT_PLAYER_POS = { 0.0f, 45.0f, 0.0f };

	static constexpr float ENCOUNT_RANGE = 100.0f;
	//最大エンカウント回数
	static constexpr int  ENCOUNT_COUNT = 5;

	//距離の単位
	static constexpr float STEP_DISTANCE = 1.0f;
	// 次のエンカウントまでの歩数初期値
	static constexpr int  ENCOUNT_MAX_STEPS = 500;
	static constexpr int  ENCOUNT_MIN_STEPS = 10;

	// アニメーション種別
	enum class ANIM_TYPE
	{
		IDLE,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		DAMAGE,
		MAX,
	};

	// コンストラクタ
	MapPlayer(void);
	// デストラクタ
	~MapPlayer(void) override;

	// 更新
	void Update(void) override;
	// 描画
	void Draw(void) override;
	void Release(void) override;

protected:

	// リソースロード
	void InitLoad(void) override;

	// 大きさ、回転、座標の初期化
	void InitTransform(void) override;

	// アニメーションの初期化
	void InitAnimation(void) override;

	// 初期化後の個別処理
	void InitPost(void) override;

	// 移動処理
	void Move(void) override;

private:

	// カメラ
	Camera* camera_;
	// matrixUtility制御
	MatrixUtility* matrixUtility_;


	bool isMoving_ = false;

	//現在の座標
	VECTOR nowPos_;
	//前回の座標
	VECTOR prePos_;

	float countPos_ = 0.0f;
	int count_ = 0;
	float accumulatedDistance_ = 0.0f; // 実際に歩いた距離の累計
	int remainingSteps_ = 0;          // 次のエンカウントまでの残り歩数
	          // プレイヤーが移動しているか（アニメーション制御用

	void enCount(void);
;

	//void playerAttack(void);
	//void playerDamage(void);

};



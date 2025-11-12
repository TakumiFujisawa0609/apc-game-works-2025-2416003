#pragma once
#include <DxLib.h>
#include "MapPlayerBase.h"
class AnimationController;
class MatrixUtility;
class Camera;

class MapPlayer : public MapPlayerBase
{
public:

	// アニメーションの再生速度
	static constexpr float SPEED_ANIM = 40.0f;

	// 回避移動スピード
	static constexpr float SPEED_DODGE = 20.0f;
	// プレイヤーの初期座標
	static constexpr VECTOR DEFAULT_PLAYER_POS = { 0.0f, 45.0f, 0.0f };



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

	void enCount(void);

	VECTOR GetPos(void);

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
	          

	
;

	//void playerAttack(void);
	//void playerDamage(void);

};



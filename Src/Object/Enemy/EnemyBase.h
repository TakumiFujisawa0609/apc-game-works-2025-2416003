#pragma once
#include <DxLib.h>
#include <vector>
#include"../../Common/Transform.h"
#include "../../Object/Status/StatusTbl.h"
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
		BLUEDEMON,
		GOBLIN,
	};

	//敵の行動状態
	enum class STATE
	{
		STANBY,
		HIT,
		DEAD,
		END,
	};

	// 標準の拡散光色
	static constexpr COLOR_F COLOR_DIF_DEFAULT = { 0.4f, 0.4f, 0.4f, 1.0f };
	// 点滅時の拡散光色
	static constexpr COLOR_F COLOR_DIF_BLINK = { 1.0f, 0.2f, 0.2f, 1.0f };
	// 点滅間隔
	static constexpr int TERM_BLINK = 8;

	void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	// 大きさ、回転、座標等の取得
	const Transform& GetTransform(void) const;


	//HPの取得
	int GetHp();

	
protected:

	static constexpr VECTOR DEFAULT_ENEMY_POS = { 0.0f, 45.0f, 0.0f };

	// アニメーション制御
	AnimationController* animationController_;
	//モデル制御の基本情報
	Transform transform_;
	//ステータス
	StatusData status;

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
	virtual void SetParam()= 0 ;
	// リソースロード
	virtual void InitLoad(void) = 0;
	// 大きさ、回転、座標の初期化
	virtual void InitTransform(void) = 0;

	// アニメーションの初期化
	virtual void InitAnimation(void) = 0;
	// 初期化後の個別処理
	virtual void InitPost(void) = 0;


private:

	//敵の行動状態
	STATE state_;
	//エネミー種別
	TYPE type_;
	///エネミーのアニメーション
	ANIM_TYPE animationType_;


};


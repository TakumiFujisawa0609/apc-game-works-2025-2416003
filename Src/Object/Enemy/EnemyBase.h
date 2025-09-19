#pragma once
#include <DxLib.h>
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
	void Update();
	void Draw();
	void Release();

	void ChageState(STATE state);

private:

	STATE state_;
	VECTOR pos_;
	VECTOR rot;
	VECTOR scl_;
	
};


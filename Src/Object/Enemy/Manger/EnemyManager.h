#pragma once
#include <vector>

class EnemyBase;

class EnemyManager
{
public:
	enum class WAVE
	{
		WAVE1,
		WAVE2,
		LASTWAVE,
	};
	// コンストラクタ
	EnemyManager(void);
	// デストラクタ
	~EnemyManager(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void ChangeWave(WAVE wave);

	void UpdateWave1(void);
	void UpdateWave2(void);
	void UpdateLastWave(void);
	


	// エネミーの取得
	const std::vector<EnemyBase*>& GetEnemys(void) const;


private:

	// エネミー
	std::vector<EnemyBase*> enemys_;
	//エネミー用のモデルハンドルID
	std::vector<int> enemyModelIds_;
	// 攻撃エフェクト用のモデルハンドルID
	std::vector<int> attackEffectModelIds_;

	WAVE wave_;
	


};


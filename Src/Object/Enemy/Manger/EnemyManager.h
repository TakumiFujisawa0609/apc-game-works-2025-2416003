#pragma once
#include <vector>
#include "../EnemyBase.h"
class EnemyBase;

class EnemyManager
{
public:


	// コンストラクタ
	EnemyManager(void);
	// デストラクタ
	~EnemyManager(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// エネミーの取得
	const std::vector<EnemyBase*>& GetEnemys(void) const;


private:

	//enemyBaseの種類
	EnemyBase::TYPE  type_;
	// エネミー
	std::vector<EnemyBase*> enemys_;
	// エネミー用のモデルハンドルID
	//std::vector<int> enemyModelIds_;

	//ゴブリンモデルID
	int goblinModelId;
	//スライムモデルID
	int blueDemonModelId;
	

	//エネミーの描画
	void GoblinDraw(void);

	void BlueDemonDraw(void);

	

};


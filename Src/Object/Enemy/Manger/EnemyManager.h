#pragma once
#include <vector>
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

	// エネミー用のモデルハンドルID
	//std::vector<int> enemyModelIds_;
	
	// エネミー
	std::vector<EnemyBase*> enemys_;

};


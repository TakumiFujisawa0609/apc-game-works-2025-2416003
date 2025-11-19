#pragma once
#include <vector>
class EnemyBase;

class EnemyManager
{
public:

	enum class ENEMY_BATTLE
	{
		GOBLIN,

	};
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

	// エネミー
	std::vector<EnemyBase*> enemys_;
	// エネミー用のモデルハンドルID
	std::vector<int> enemyModelIds_;
	
	//エネミー編成
	ENEMY_BATTLE enemy_Battle;


	void GoblinParty(void);

	bool spaw_ = false;

	int count_;

};


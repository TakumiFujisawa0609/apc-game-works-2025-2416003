#pragma once
class EnemyStatusManager
{
public:
	static void CreateInstance(void);///インスタンスの生成
	static EnemyStatusManager* Getinstance(void);///インスタンスの取得
	
	EnemyStatusManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void DeleteInstance();


	//// エネミーの最大体力取得
	//int GetEnemyMaxHp(int enemyId) const;
	//// エネミーの最大体力取得
	//int GetEnemyHp(int enemyId) const;
	//// エネミーの攻撃力取得
	//int GetEnemyAttack(int enemyId) const;
	//// エネミーの防御力取得
	//int GetEnemyDefense(int enemyId) const;
	//// エネミーの素早さ取得
	//int GetEnemyAgility(int enemyId) const;
	//// エネミーの経験値取得
	//int GetEnemyExp(int enemyId) const;
	//// エネミーのお金取得
	//int GetEnemyMoney(int enemyId) const;

private:

	static EnemyStatusManager* instance_;


	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	// コンストラクタ
	EnemyStatusManager(const EnemyStatusManager& instance) = default;
	// デストラクタ
	~EnemyStatusManager(void) = default;

};
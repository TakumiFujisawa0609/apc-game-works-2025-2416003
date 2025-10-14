#pragma once
#include <map>
#include "../Object/Enemy/EnemyBase.h"


struct EnemyData
{
	int hp_;
	int speed_;///素早さ
	int atk_;///攻撃力
	int def_;///防御力
	int intel_;///かしこさ

	int maxHp_;
	int dex_;///回避率
	int exp_;//経験値
};

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

	const EnemyData& GetEnemyData(EnemyBase::TYPE type) const;

	// 次の戦闘の種類を設定する
	void SetNextEncounterType(EnemyBase::TYPE type);


	// 次の戦闘の種類を取得する
	EnemyBase::TYPE GetNextEncounterType() const;


	void LoadStatusData(void);


	

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
	//次に戦闘する敵の変数
	EnemyBase::TYPE nextEncounterType_;
	std::map < EnemyBase::TYPE, EnemyData> enemyStatusMap_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	// コンストラクタ
	EnemyStatusManager(const EnemyStatusManager& instance) = default;
	// デストラクタ
	~EnemyStatusManager(void) = default;

};
#pragma once
#include <map>
struct PlayerData
{
	int hp_;
	int speed_;///素早さ
	int atk_;///攻撃力
	int def_;///防御力
	int intel_;///かしこさ

	int maxHp_;
	int dex_;///回避率
	int getexp_;//獲得した経験値 
};
class PlayerManger
{
	static void CreateInstance(void);///インスタンスの生成
	static PlayerManger* Getinstance(void);///インスタンスの取得

	PlayerManger(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void DeleteInstance();

	const PlayerData& GetEnemyData() const;

	void LoadStatusData(void);

private:

	static PlayerManger* instance_;
	

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	// コンストラクタ
	PlayerManger(const PlayerManger& instance) = default;
	// デストラクタ
	~PlayerManger(void) = default;

};


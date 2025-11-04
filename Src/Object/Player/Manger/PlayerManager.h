#pragma once
#include <map>
#include <vector>
#include <string>
#include "../../../Object/Player/Manger/PlayerManager.h"


struct PlayerData
{
	int hp_;
	int speed_;///素早さ
	int atk_;///攻撃力
	int def_;///防御力
	int intel_;///かしこさ

	int maxHp_;
	int  dex_;///回避率
	int collectExp_;//経験値
};

class PlayerManager
{
public:



	static void CreateInstance(void);///インスタンスの生成
	static PlayerManager* Getinstance(void);///インスタンスの取得

	PlayerManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void DeleteInstance();

	
	const PlayerData& GetPlayerData() const;

	void LoadStatusData(void);

	

private:

	static PlayerManager* instance_;
	/// @brief 
	std::map<std::string, PlayerData> playerStatusMap_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	// コンストラクタ
	PlayerManager(const PlayerManager& instance) = default;
	// デストラクタ
	~PlayerManager(void) = default;

};


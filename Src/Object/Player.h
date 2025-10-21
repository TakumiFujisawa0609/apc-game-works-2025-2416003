#pragma once
#include <list>
#include <map>

class Player
{


public:


	struct PlayerData
	{
		int hp_;
		int speed_;///素早さ
		int atk_;///攻撃力
		int def_;///防御力
		int intel_;///かしこさ

		int maxHp_;
		int dex_;///回避率
		int collectExp_;//経験値
	};

	enum class SKILL //プレイヤーから持ってこないといけないんだけど一旦仮で
	{
		SLASH,//斬撃
		PROTECT,//防御
		HEAL,//回復
		POISON,//毒
		LIMIT_BREAK,//リミットブレイク

	};

	void Init(void);
	// 更新
	void Update(void);
	// デバッグ用描画
	void Draw(void);
	// 解放
	void Release(void);

	//スキル選択関連palyer
	void SelectSkill(SKILL skill);
	void UseSkill(void);
	void ProcessSkill(SKILL skill);
	void LoadStatusData(void);
	
private:

	



};


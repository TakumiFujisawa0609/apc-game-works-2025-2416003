#pragma once
#include <list>
#include <map>

class Player
{


public:

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

	//スキル選択関連
	void SelectSkill(SKILL skill);
	void UseSkill(void);
	void ProcessSkill(SKILL skill);
	
private:

	std::list<SKILL> selectedSkills_;



};


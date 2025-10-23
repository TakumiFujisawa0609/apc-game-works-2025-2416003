#pragma once
#include <list>
#include <string>
#include <DxLib.h>
#include "../Actor/ActorSkill.h"
using  namespace std;

class SkillBase
{
public:
	//スキル種別（ピースの色を識別する時にも利用する）
	enum class SKILLTYPE
	{
		ATTACK,
		DEFENSE,
		HEAL,
		BUFF,
		DEBUFF,

	};

	//スキル追加をここに
	enum class SKILL
	{
		SLASH,//斬撃
		LIMIT_BREAK,//リミットブレイク
	};

	void Init(SKILLTYPE type,SKILL skill);
	// 更新
	virtual void Update(void);
	// デバッグ用描画
	virtual void Draw(void);
	// 解放
	virtual void Release(void);

protected:
	/// @brief 技
	SKILL skill_;

	//スキル種別
	SKILLTYPE skillType_;

	//スキル名
	string skillName_;

	float baseDamege_;

	//リリースロード
	 virtual void InitLoad(void) = 0;

	//スキルに必要な情報を入れる
	 virtual void SetParam(void) = 0;
	
	 int CalculateDamege(int attackerAtk, int targetDef) ;
	 //攻撃スキルのダメージ処理
	 void SkillProcess(const ActorSkill& user, ActorSkill& target);

private:

	int playerHp_;
	int playerAtk_;
	int playerDef_;
	int playerIntel_;

	int enemyHp_;
	int enemyDef_;

};




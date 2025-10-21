#pragma once
#include <list>
#include <string>
#include <DxLib.h>

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


	void Init(void);
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
	//ダメージ
	int damege_;
	//スキル処理のダメージ
	int skillDamege_;


	int playerHp_;
	int playerAtk_;
	int playerDef_;
	int playerIntel_;

	//リリースロード
	 virtual void InitLoad(void) = 0;
	//スキルに必要な情報を入れる
	 virtual void SetParam(void) = 0;
	 //スキルごとの必要な処理
	 virtual void  SkillProcess(int atk ,int def, int intel) = 0;
	 //攻撃スキルのダメージ処理
	 virtual void Damege(int hp, int dmg, int def) = 0;

private:

	

};




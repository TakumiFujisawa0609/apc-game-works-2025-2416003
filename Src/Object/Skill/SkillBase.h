#pragma once
#include <list>
#include <string>
#include <DxLib.h>



class SkillBase
{
public:
	enum class SKILLTYPE
	{
		ATTACK,
		DEFENSE,
		HEAL,
		BUFF,
		DEBUFF,

	};

	enum class SKILL
	{
		SLASH,//斬撃
		LIMIT_BREAK,//リミットブレイク
	};


	void Init(SKILL skill);
	// 更新
	void Update(void);
	// デバッグ用描画
	void Draw(void);
	// 解放
	void Release(void);



protected:
	 virtual void SetParam(void) = 0;

	 int skillName_;

private:
	/// @brief 技
	SKILL skill_;

	//スキル種別
	SKILLTYPE skillType_;
};




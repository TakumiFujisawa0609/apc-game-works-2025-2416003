#pragma once
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


	void Init(SKILLTYPE skill_type);
	// 更新
	void Update(void);
	// デバッグ用描画
	virtual void Draw(void);
	// 解放
	virtual void Release(void);

	SKILLTYPE GetSkill(void);

protected:

	
	//スキル種別
	SKILLTYPE skill_type_;
	//スキル名
	std::string skill_name_;

	int modelId_;
	VECTOR pos_;
	VECTOR rot_;
	VECTOR scl_;
	VECTOR moveDir_;

	float speed_;
	bool isAlive_;

	int size_;
	//スキル攻撃力
	int skill_Atk_Power_;
	//スキル防御力
	int skill_Def_Power_;
	//スキル回復力
	int skill_Heal_Power_;
	//スキルバフ力
	int skill_Buff_Power_;
	//スキルデバフ力
	int skill_Debuff_Power_;


	virtual void Load(void);
	virtual void SetParam(void);
	
};




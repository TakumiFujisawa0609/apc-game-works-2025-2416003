#pragma once

#include "SkillTbl.h"

class ActorBase;

class SkillBase
{
public:
	SkillBase(SKILL_KIND skillKind);	// コンストラクタ
	~SkillBase();	// デストラクタ

	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Release(void);	// 解放

	void Attack(ActorBase* attacker, ActorBase* target);

protected:
	SkillData skillData_;		// スキル情報

	ActorBase* actorBase_;
};

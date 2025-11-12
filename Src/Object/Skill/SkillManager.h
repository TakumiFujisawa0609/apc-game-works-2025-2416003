#pragma once
#include <list>

#include "SkillTbl.h"

class SkillBase;

class SkillManager
{
public:
	
	SkillManager(void);		// コンストラクタ
	~SkillManager(void);	// デストラクタ

	void Init(void);		// 初期化
	void Update(void);		// 更新
	void Draw(void);		// 描画
	void Release(void);		// 解放

	// スキルを末尾追加する
	void PushSkillList(SKILL_KIND skillKind);

	// 末尾のスキルを削除する
	void PopSkillList(void);

	// 全てのスキルを取得する
	std::list<SkillBase*>GetSkills(void) { return skills_; };


private:


	// スキルの配列
	std::list<SkillBase*> skills_;
};


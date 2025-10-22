#pragma once
#include <list>

class SkillBase;

class SkillManager
{
	// コンストラクタ
	SkillManager(void);
	// デストラクタ
	~SkillManager(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	std::list<SkillBase*>GetSkills(void);

private:
	std::list<SkillBase*> skills_;
};


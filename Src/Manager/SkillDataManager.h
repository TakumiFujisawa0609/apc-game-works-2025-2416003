#pragma once
#include<list>
#include <vector>
#include <string>    
class SkillBase;

//スキル読み込み専用
class SkillDataManager
{

public:

	SkillDataManager();
	~SkillDataManager();







private:

	//スキルの定義を管理する（可変長配列）
	std::vector<SkillBase*> skill_definitions_;
	
};


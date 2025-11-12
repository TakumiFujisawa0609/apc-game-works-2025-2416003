#include "SkillManager.h"
#include "SkillBase.h"



SkillManager::SkillManager(void)
{
}

SkillManager::~SkillManager(void)
{
}


void SkillManager::Init(void)
{
	// 配列を全て回す
	for (const auto skill : skills_)
	{
		// 初期化
		skill->Init();
	}
}

void SkillManager::Update(void)
{
	// 配列が空なら処理しない
	if (skills_.empty()) return;

	// 配列を全て回す
	for (const auto skill : skills_)
	{
		// 更新
		skill->Update();
	}
}

void SkillManager::Draw(void)
{
	// 配列が空なら処理しない
	if (skills_.empty()) return;

	// 配列を全て回す
	for (const auto skill : skills_)
	{
		// 描画
		skill->Draw();
	}
}

void SkillManager::Release(void)
{
	// 配列を全て回す
	for (const auto skill : skills_)
	{
		// 解放
		skill->Release();
		delete skill;
	}
	// 配列をクリア
	skills_.clear();
}

void SkillManager::PushSkillList(SKILL_KIND skillKind)
{
	// スキルを生成
	SkillBase* addSkill = new SkillBase(skillKind);

	// 作成したスキルを配列に追加
	skills_.push_back(addSkill);
}

void SkillManager::PopSkillList(void)
{
	// スキルを削除
	skills_.pop_back();
}



#include "SkillBase.h"
#include "../../Manager/PlayerManager.h"
#include "../../Manager/EnemyStatusManager.h"

void SkillBase::Init(SKILLTYPE type,SKILL skill)
{
	//スキルタイプとスキル名の種別
	skillType_ = type;
	skill_ = skill;

	InitLoad();
	SetParam();
}

void SkillBase::Update(void)
{

}

void SkillBase::Draw(void)
{
}

void SkillBase::Release(void)
{
}

int SkillBase::CalculateDamege(int attackerAtk, int targetDef)
{
	int damege = baseDamege_ * +-( attackerAtk - targetDef);

	if (damege < 1)damege = 1;

	return damege;

	
}

void SkillBase::SkillProcess(const ActorSkill& user, ActorSkill& target)
{
	//ダメージ計算
	int damege = CalculateDamege(user.getAtk(), target.getDef());
	//計算結果を適用させる
	target.takeDamage(damege);
}

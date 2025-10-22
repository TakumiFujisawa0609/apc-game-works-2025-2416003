#include "SkillBase.h"
#include "../../Manager/PlayerManager.h"
#include "../../Manager/EnemyStatusManager.h"

void SkillBase::Init(void)
{

	InitLoad();


	/*PlayerManager::Getinstance();

	const PlayerData& playerData_ = PlayerManager::Getinstance()->GetPlayerData();
	
	playerAtk_ = playerData_.atk_;
	playerDef_ = playerData_.def_;
	playerIntel_ = playerData_.intel_;
	playerHp_ = playerData_.hp_;

	EnemyStatusManager::Getinstance();*/


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


void SkillBase::SetParam(void)
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

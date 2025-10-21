#include "SkillBase.h"
#include "../../Manager/PlayerManager.h"
#include "../../Manager/EnemyStatusManager.h"
void SkillBase::Init(void)
{

	InitLoad();
	SetParam();

	PlayerManager::Getinstance();

	const PlayerData& playerData_ = PlayerManager::Getinstance()->GetPlayerData();
	
	playerAtk_ = playerData_.atk_;
	playerDef_ = playerData_.def_;
	playerIntel_ = playerData_.intel_;
	playerHp_ = playerData_.hp_;

	EnemyStatusManager::Getinstance();


}

void SkillBase::Update(void)
{

	SkillProcess(playerAtk_, playerDef_, playerIntel_);

	//Damege(playerHp_);

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

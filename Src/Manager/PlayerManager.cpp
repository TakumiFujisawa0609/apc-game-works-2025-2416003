#include "PlayerManager.h"
#include <DxLib.h>
#include <chrono>

PlayerManager* PlayerManager::instance_ = nullptr;


void PlayerManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new PlayerManager();
	}
	instance_->Init();
}

PlayerManager* PlayerManager::Getinstance(void)
{

	if (instance_ == nullptr)
	{
		CreateInstance();
	}
	return instance_;
}


void PlayerManager::DeleteInstance()
{
	if (instance_ != nullptr)
	{
		delete instance_;
	}
	instance_ = nullptr;
}

PlayerManager::PlayerManager(void)
{
	
}

void PlayerManager::Init(void)
{
	LoadStatusData();
}

void PlayerManager::Update(void)
{
}

void PlayerManager::Draw(void)
{
}

void PlayerManager::Release(void)
{

}



const PlayerData& PlayerManager::GetPlayerData() const
{

	return playerStatusMap_.at("Player");
}

void PlayerManager::LoadStatusData(void)
{
	PlayerData playerStatus;

	//戦闘中に変化があるステータス
	playerStatus.hp_ = 10;
	playerStatus.atk_ = 5;
	playerStatus.def_ = 3;
	playerStatus.speed_ = 10;
	playerStatus.intel_ = 10;

	//数値固定のステータス
	playerStatus.maxHp_ = 10;
	playerStatus.dex_ = 5;
	playerStatus.collectExp_ = 0;

	playerStatusMap_["Player"] = playerStatus;
}

#include <chrono>
#include <DxLib.h>
#include "EnemyStatusManager.h"

EnemyStatusManager* EnemyStatusManager::instance_ = nullptr;

void EnemyStatusManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new EnemyStatusManager();
	}
	instance_->Init();
}

EnemyStatusManager* EnemyStatusManager::Getinstance(void)
{
	if(instance_ == nullptr)
	{
		CreateInstance();
	}
    return instance_;
}

EnemyStatusManager::EnemyStatusManager(void)
{
}

void EnemyStatusManager::Init(void)
{
	LoadStatusData();
}

void EnemyStatusManager::Update(void)
{
}

void EnemyStatusManager::Draw(void)
{
}

void EnemyStatusManager::Release(void)
{
}

void EnemyStatusManager::DeleteInstance()
{

	if (instance_ != nullptr)
	{
		delete instance_;
	}	instance_ = nullptr;
	
}

const EnemyData& EnemyStatusManager::GetEnemyData(EnemyBase::TYPE type) const
{
	// TODO: return ステートメントをここに挿入します
	auto  it = enemyStatusMap_.find(type);
	if (it == enemyStatusMap_.end())
	{
		static EnemyData dummy{};
		return dummy;
	}

	return it->second;
}

void EnemyStatusManager::SetNextEncounterType(EnemyBase::TYPE type)
{
	nextEncounterType_ = type;
}

EnemyBase::TYPE EnemyStatusManager::GetNextEncounterType() const
{
	return nextEncounterType_;
};

void EnemyStatusManager::LoadStatusData(void)
{
	EnemyData GoblinData;

	//戦闘中に変化があるステータス
	GoblinData.hp_ = 20;
	GoblinData.atk_ = 2;
	GoblinData.def_ = 5;
	GoblinData.speed_ = 5;
	GoblinData.intel_ = 5;

	//数値固定のステータス
	GoblinData.maxHp_ = 20;
	GoblinData.dex_ = 0;
	GoblinData.exp_ = 10;

	enemyStatusMap_[EnemyBase::TYPE::GOBLIN] = GoblinData;
}





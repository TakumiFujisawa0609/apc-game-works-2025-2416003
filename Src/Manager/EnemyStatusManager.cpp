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
    return instance_;
}

EnemyStatusManager::EnemyStatusManager(void)
{
}

void EnemyStatusManager::Init(void)
{
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
	}
	
}

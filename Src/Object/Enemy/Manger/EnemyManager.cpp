#include <DxLib.h>
#include "EnemyManager.h"
#include "../Goblin.h"

EnemyManager::EnemyManager(void)
{
}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(void)
{
	//“G‚Ìƒ‚ƒfƒ‹“Ç‚Ýž‚Ý
	EnemyBase* enemy = new Goblin();

	enemy->Init(EnemyBase::TYPE::GOBLIN);
	enemys_.push_back(enemy);
}



void EnemyManager::Update(void)
{
	for (const auto enemy : enemys_)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	for (const auto enemy : enemys_)
	{
		enemy->Draw();
	}
}

void EnemyManager::Release(void)
{
	
}

const std::vector<EnemyBase*>& EnemyManager::GetEnemys(void) const
{
	return enemys_;
}





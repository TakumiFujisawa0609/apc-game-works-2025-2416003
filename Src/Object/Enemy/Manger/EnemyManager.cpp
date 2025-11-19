#include <DxLib.h>
#include "EnemyManager.h"
#include "../EnemyBase.h"
#include "../Goblin.h"
#include "../../../Application.h"

EnemyManager::EnemyManager(void)
{

}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(void)
{
	//エネミーのモデルロード
	//ゴブリンモデルロード
	enemyModelIds_.emplace_back(
		MV1LoadModel((Application::PATH_MODEL + "Enemy/Goblin.mv1").c_str()));

}



void EnemyManager::Update(void)
{
	//敵編成
	switch (enemy_Battle)
	{
	case EnemyManager::ENEMY_BATTLE::GOBLIN:

		if (enemys_.empty())
		{
			GoblinParty();
		}
		
		break;
	default:
		break;
	}

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
	for (int id : enemyModelIds_)
	{
		MV1DeleteModel(id);
	}
}

const std::vector<EnemyBase*>& EnemyManager::GetEnemys(void) const
{
	return enemys_;
}

void EnemyManager::GoblinParty(void)
{
	EnemyBase* enemy = new Goblin();
	enemy->Init(EnemyBase::TYPE::GOBLIN,
		enemyModelIds_[0]);

	enemys_.push_back(enemy);
}





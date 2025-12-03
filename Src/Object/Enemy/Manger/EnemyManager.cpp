#include <DxLib.h>
#include "EnemyManager.h"
#include "../../../Application.h"
#include "../Goblin.h"

EnemyManager::EnemyManager(void)
{
}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(void)
{
	// エネミーモデルのロード
	enemyModelIds_.emplace_back(
		MV1LoadModel((Application::PATH_MODEL + "Enemy/Goblin.mv1").c_str()));

	

	ChangeWave(WAVE::WAVE1);
}



void EnemyManager::Update(void)
{
	//WAVE処理
	switch (wave_)
	{
	case EnemyManager::WAVE::WAVE1:
		UpdateWave1();
		break;
	case EnemyManager::WAVE::WAVE2:
		UpdateWave1();
		break;
	case EnemyManager::WAVE::LASTWAVE:
		UpdateWave1();
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

void EnemyManager::ChangeWave(WAVE wave)
{
	wave_ = wave;
	
	switch (wave)
	{
	case EnemyManager::WAVE::WAVE1:
		break;
	case EnemyManager::WAVE::WAVE2:
		break;
	case EnemyManager::WAVE::LASTWAVE:
		break;
	case EnemyManager::WAVE::END:
		break;
	default:
		break;
	}


}

void EnemyManager::UpdateWave1(void)
{
	if (wave_ == WAVE::WAVE1)
	{
		EnemyBase* enemy = new Goblin();

		enemy->Init(EnemyBase::TYPE::GOBLIN,
			enemyModelIds_[static_cast<int>(EnemyBase::TYPE::GOBLIN)]);

		enemys_.emplace_back(enemy);

	}

	 
	
}

void EnemyManager::UpdateWave2(void)
{
	if (wave_ == WAVE::WAVE2)
	{

	}
}

void EnemyManager::UpdateLastWave(void)
{
	if (wave_ == WAVE::LASTWAVE)
	{

	}
}

const std::vector<EnemyBase*>& EnemyManager::GetEnemys(void) const
{
	return enemys_;
}





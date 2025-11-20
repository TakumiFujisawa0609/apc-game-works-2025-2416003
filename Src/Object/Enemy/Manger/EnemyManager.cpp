#include <DxLib.h>
#include "EnemyManager.h"
#include "../EnemyBase.h"
#include "../EnemyType/Goblin.h"
#include "../EnemyType/BlueDemon.h"
#include "../../../Application.h"

EnemyManager::EnemyManager(void)
{

}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(void)
{

	/*enemyModelIds_.emplace_back(
		MV1LoadModel((Application::PATH_MODEL + "Enemy/Goblin.mv1").c_str()));*/
	
	//ゴブリンモデルロード
	goblinModelId = MV1LoadModel((Application::PATH_MODEL + "Enemy/Goblin.mv1").c_str()); 
	//スライムモデルロード
	blueDemonModelId = MV1LoadModel((Application::PATH_MODEL + "Enemy/BlueDemon.mv1").c_str());

	//戦う敵の抽選
	type_ = EnemyBase::TYPE::GOBLIN;//一旦仮
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
	
	//敵編成
	switch (type_)
	{
	case EnemyBase::TYPE::BLUEDEMON:
		BlueDemonDraw();
		break;
	case EnemyBase::TYPE::GOBLIN:
		GoblinDraw();
		break;
	default:
		break;
	}
}

void EnemyManager::Release(void)
{
	MV1DeleteModel(goblinModelId);
	MV1DeleteModel(blueDemonModelId);
}

const std::vector<EnemyBase*>& EnemyManager::GetEnemys(void) const
{
	return enemys_;
}

void EnemyManager::GoblinDraw(void)
{
	MV1DrawModel(goblinModelId);
}

void EnemyManager::BlueDemonDraw(void)
{
	MV1DrawModel(blueDemonModelId);
}






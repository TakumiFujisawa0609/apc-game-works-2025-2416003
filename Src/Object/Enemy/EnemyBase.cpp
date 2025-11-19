#include "EnemyBase.h"
#include "../../Common/AnimationController.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Utility/AsoUtility.h"


void EnemyBase::Init(TYPE type,int baseModelId)
{
	
	//エネミー種別
	type_ = type;

	modelId_ = baseModelId;
	
}

void EnemyBase::Update()
{
	
	
}

void EnemyBase::Draw()
{
	MV1DrawModel(modelId_);
}

void EnemyBase::Release()
{
	
}

const Transform& EnemyBase::GetTransform(void) const
{
	return transform_;
}

int EnemyBase::GetHp()
{
	return hp_;
}





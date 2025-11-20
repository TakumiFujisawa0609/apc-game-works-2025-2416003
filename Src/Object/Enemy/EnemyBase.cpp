#include "EnemyBase.h"
#include "../../Common/AnimationController.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Utility/AsoUtility.h"


void EnemyBase::Init()
{
	SetParam();
}

void EnemyBase::Update()
{
	
}

void EnemyBase::Draw()
{
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
	return status.hp_;
}





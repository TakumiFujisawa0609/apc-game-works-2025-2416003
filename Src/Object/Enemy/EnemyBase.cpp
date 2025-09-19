#include <DxLib.h>
#include "EnemyBase.h"


void EnemyBase::Init()
{
	pos_ = { 0,0,0 };
	scl_ = { 0, 0, 0 };
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()
{
	DrawSphere3D(pos_, 1.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0),true;
	
}

void EnemyBase::Release()
{
}

void EnemyBase::ChageState(STATE state)
{
}

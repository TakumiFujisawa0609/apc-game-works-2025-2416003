#include "Goblin.h"
#include"../../Common/AnimationController.h"
#include "../../Application.h"

Goblin::Goblin(void)
{
}

Goblin::~Goblin(void)
{
}

void Goblin::Update()
{
	EnemyBase::Update();
}

void Goblin::Draw()
{
	EnemyBase::Draw();
}

void Goblin::Release(void)
{
	EnemyBase::Release();
}

void Goblin::InitLoad()
{
	modelId_ = MV1LoadModel((Application::PATH_MODEL+"Enemy/Goblin.mv1").c_str());
}

void Goblin::InitTransform()
{
	/// @init transform ç¿ïW
	pos_ = DEFAULT_ENEMY_POS;
	/// @init transform ëÂÇ´Ç≥
	scl_ = { 1.0f,1.0f,1.0f };
	/// @init transform äpìx
	angles_ = { 0.0f,0.0f,0.0f };
}

void Goblin::InitAnimation()
{
	/// @init animation
	animationController_ = new AnimationController(modelId_);

	/// @add animation

}

void Goblin::InitPost()
{
}

void Goblin::SetParam()
{

}

void Goblin::ProcessAction()
{
}

#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "GameScene.h"
#include "../Manager/Camera.h"
#include "../Object/Grid.h"
#include "SearchScene.h"

SearchScene::SearchScene(void)
{
}

SearchScene::~SearchScene(void)
{
}

void SearchScene::Init(void)
{
	//カメラモード変更
	Camera* camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FREE);

	grid_ = new Grid();
	grid_->Init();



}

void SearchScene::Update(void)
{
	grid_->Update();

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);
	}
}

void SearchScene::Draw(void)
{

	grid_->Draw();
	DrawString(0, 0, "SearchScene", 0xffffff);
}

void SearchScene::Release(void)
{
	grid_->Release();
	delete grid_;
}

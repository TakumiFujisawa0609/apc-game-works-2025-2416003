#include <string>
#include <DxLib.h>
#include "../..//Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Object/Grid.h"
#include "../../Manager/Camera.h"
#include "GameScene.h"
#include "../../Sound/AudioManager.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	

	//カメラモード変更
	Camera* camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FREE);

}

void GameScene::Update(void)
{

	grid_->Update();

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_X))
	{
		
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
	}


}

void GameScene::Draw(void)
{
	grid_->Draw();

	DrawString(0, 0, "GameScene", 0xffffff);
	DrawString(0, 80, "スペースでサーチシーン", 0xffffff);

	//モデルテスト
	DrawSphere3D(testPos, 10, 32, 0xffffff, 0xffffff, true);


	//DrawBox(10,100)


}

void GameScene::Release(void)
{
	grid_->Release();
	delete grid_;
}






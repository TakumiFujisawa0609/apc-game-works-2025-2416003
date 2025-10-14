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
#include "../Object/Actor/MapPlayer.h"

SearchScene::SearchScene(void)
{
}

SearchScene::~SearchScene(void)
{
}

void SearchScene::Init(void)
{


	grid_ = new Grid();
	grid_->Init();

	stageId_ = MV1LoadModel("Data/Model/Stage/Stage.mv1");
	MV1SetPosition(stageId_, VGet(0.0f, 180.0f, 0.0f));


	player_ = new MapPlayer();
	player_->Init();

	Camera* camera = SceneManager::GetInstance().GetCamera();
	camera->SetFollow(player_);
	camera->ChangeMode(Camera::MODE::FOLLOW);

	
}

void SearchScene::Update(void)
{
	

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	//if (ins.IsTrgDown(KEY_INPUT_SPACE))
	//{
	//	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	//}
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);


	}

	grid_->Update();
	player_->Update();
}

void SearchScene::Draw(void)
{

	//MV1DrawModel(stageId_);
	grid_->Draw();
	player_->Draw();


	DrawString(0, 0, "SearchScene", 0xffffff);
	DrawString(0, 80, "Nキーでバトルシーン", 0xffffff);

}

void SearchScene::Release(void)
{
	grid_->Release();
	delete grid_;

	player_->Release();
	delete player_;
}

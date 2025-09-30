#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Grid.h"
#include "../Manager/Camera.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	testPos = { 0,0,50 };
	playscene_ = PLAYSCENE::PREPARATION;
	grid_ = new Grid();
	grid_->Init();

	//カメラモード変更
	Camera* camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FREE);

}

void GameScene::Update(void)
{

	grid_->Update();

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	//仮の探索シーンへの遷移
	if (ins.IsTrgDown(KEY_INPUT_Z))
	{
		ChangeScene(PLAYSCENE::BATTLE);
	}

	//仮の戦闘シーンへの遷移
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		ChangeScene(PLAYSCENE::SEARCH);
	}



}

void GameScene::Draw(void)
{
	grid_->Draw();

	DrawString(0, 0, "GameScene", 0xffffff);
	DrawString(0, 80, "スペースでタイトルへ：Nキーでサーチシーン", 0xffffff);

	//モデルテスト
	DrawSphere3D(testPos, 10, 32, 0xffffff, 0xffffff, true);
}

void GameScene::Release(void)
{
	grid_->Release();
	delete grid_;
}

void GameScene::ChangeScene(PLAYSCENE playscene)
{
	playscene_ = playscene;
	switch (playscene_)
	{
		//準備シーンへ
	case GameScene::PLAYSCENE::PREPARATION:
		break;
		//探索シーンへ
	case GameScene::PLAYSCENE::SEARCH:
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
		break;
		//戦闘シーンへ
	case GameScene::PLAYSCENE::BATTLE:
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);
		break;
	default:
		break;
	}
}

void GameScene::ChangePretaration(void)
{
}

void GameScene::ChangeSearch(void)
{
}

void GameScene::ChangeBattle(void)
{
}





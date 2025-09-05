#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
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
}

void GameScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);
	}

	if (ins.IsTrgDown(KEY_INPUT_Z))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
	}

}

void GameScene::Draw(void)
{
	DrawString(0, 0, "GameScene", 0xffffff);

	//モデルテスト
	DrawSphere3D(testPos, 10, 32, 0xffffff, 0xffffff, true);
}

void GameScene::Release(void)
{
}

#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "GameClear.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
}

void GameClear::Update(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		ChangeTitle();
	}
}

void GameClear::Draw(void)
{
	DrawString(320, 240, "ゲームクリア！", GetColor(255, 255, 255));
}

void GameClear::Release(void)
{
}

void GameClear::ChangeTitle(void)
{
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
}

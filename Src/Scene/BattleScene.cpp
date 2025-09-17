#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "GameScene.h"
#include "BattleScene.h"

BattleScene::BattleScene(void)
{
}

BattleScene::~BattleScene(void)
{
}

void BattleScene::Init(void)
{

	cursorIndx_ = 0;
	command_ = COMMAND::BATTLE;

}

void BattleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
	}

	if (ins.IsTrgDown(KEY_INPUT_UP))
	{
		cursorIndx_--;
		
		if (cursorIndx_ < 0)
		{
			cursorIndx_ = static_cast<int>(COMMAND::MAX) - 1;
		}
	}

	if (ins.IsTrgDown(KEY_INPUT_DOWN))
	{
		cursorIndx_++;

		if (cursorIndx_  > (int) COMMAND::MAX)
		{
			cursorIndx_ = 0;
		}
	}

}

void BattleScene::Draw(void)
{
	DrawString(0, 0, "BattleScene", 0xffffff);

	const char* commands[] =
	{
		"たたかう",
		"アイテム",
		"にげる"
	};

	for (int i = 0; i < (int)COMMAND::MAX; i++)
	{
		int color = 0xffffff;
		DrawString(100, 100 + i * 30, commands[i], color);
	}
}

void BattleScene::Release(void)
{
}

void BattleScene::ChangeCommand(COMMAND command)
{
	command_ = command;

	switch (command_)
	{
		//コマンド選択						
	case BattleScene::COMMAND::BATTLE: //戦う
		printfDx("たたかった\n");
		break;


	case BattleScene::COMMAND::TOOl: //道具
		printfDx("アイテム\n");
		break;


	case BattleScene::COMMAND::ESCAPE:  //逃げる
		printfDx("逃げる\n");

		break;


	default:
		break;
	}

}

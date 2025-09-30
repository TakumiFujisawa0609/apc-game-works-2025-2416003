#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	imgTitle_ = LoadGraph((Application::PATH_IMAGE + "Title.png").c_str());
}

void TitleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		ChangeGame();
	}

	if (ins.IsTrgDown(KEY_INPUT_UP))
	{
		cursorIndx_--;

		if (cursorIndx_ < 0)
		{
			cursorIndx_ = static_cast<int>(STATE::MAX) - 1;
		}
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN))
	{
		cursorIndx_++;

		if (cursorIndx_ > (int)STATE::MAX -1)
		{
			cursorIndx_ = 0;
		}
	}

	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		ChagneState((STATE)cursorIndx_);
		state_ = STATE::GAME;
		
	}

}

void TitleScene::Draw(void)
{

	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgTitle_, true);

	DrawString(0, 0, "TitleScene", 0xffffff);
	DrawString(0, 80, "シーン移動はスペース：シーン選択は→キーで", 0xffffff);




	DrawCommand((STATE)cursorIndx_);

}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
}

void TitleScene::ChangeExit(void)
{
	SceneManager::GetInstance().SetGameEnd();
}

void TitleScene::ChangeGame(void)
{
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
}

void TitleScene::ChagneState(STATE next)
{
	state_ = next;

	switch (next)
	{
	case TitleScene::STATE::GAME:
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		break;
	case TitleScene::STATE::EXIT:
		isEnd_ = true;

		if (isEnd_ == true)
		{
			Application::GetInstance().End();
		}
		break;

	}
}

void TitleScene::DrawCommand(STATE next)
{
	const char* name = "";

	if (next == STATE::GAME) name = "ゲームスタート";
	else if (next == STATE::EXIT) name = "おわり";
	
		DrawFormatString(100, 100, GetColor(255, 255, 255), "選択中: %s", name);

}


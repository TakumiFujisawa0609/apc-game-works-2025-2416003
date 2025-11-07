#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
	//SoundManager::GetInstance().Play(SoundManager::SRC::GAME_BGM, Sound::TIMES::LOOP);
}

TitleScene::~TitleScene(void)
{
	//SoundManager::GetInstance().Stop(SoundManager::SRC::GAME_BGM);
}

void TitleScene::Init(void)
{
	imgTitle_ = LoadGraph((Application::PATH_IMAGE + "Title.png").c_str());


}

void TitleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

 

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

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		ChagneState((STATE)cursorIndx_);
		
	} 
	

}

void TitleScene::Draw(void)
{

	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgTitle_, true);
	DrawString(0, 0, "TitleScene", 0xffffff);
	DrawString(0, 80, "スペース：決定：→キーで：選択", 0xffffff);
	

	// 2. 「GAME START」の描画
	if (cursorIndx_ == (int)STATE::GAME)
	{

		// 選択中の場合、色を変えてカーソルを付ける
		DrawString(300, GAME_POS_Y, CURSOR_CHAR, GetColor(255, 255, 0)); // 黄色のカーソル
		DrawString(330, GAME_POS_Y, "GAME START", GetColor(255, 255, 0)); // 黄色
	}
	else
	{
		// 非選択中の場合
		DrawString(330, GAME_POS_Y, "GAME START", GetColor(200, 200, 200)); // グレー
	}

	
	// 3. 「EXIT」の描画
	if (cursorIndx_ == (int)STATE::EXIT)
	{
		// 選択中の場合、色を変えてカーソルを付ける
		DrawString(300, EXIT_POS_Y, CURSOR_CHAR, GetColor(255, 255, 0)); // 黄色のカーソル
		DrawString(330, EXIT_POS_Y, "EXIT", GetColor(255, 255, 0)); // 黄色
	}
	else
	{
		// 非選択中の場合
		DrawString(330, EXIT_POS_Y, "EXIT", GetColor(200, 200, 200)); // グレー
	}
	
	
}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
	DeleteSoundMem(titleHundle_);
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






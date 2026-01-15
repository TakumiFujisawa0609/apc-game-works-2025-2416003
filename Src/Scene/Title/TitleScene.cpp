#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Sound/AudioManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
	gameImg_ = -1;
	exitImg_ = -1;
	gameOffImg_ = -1;
	exitOffImg_ = -1;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	imgTitle_ = LoadGraph((Application::PATH_IMAGE + "Title.png").c_str());
	gameImg_ = LoadGraph((Application::PATH_IMAGE + "GameStart.png").c_str());
	exitImg_ = LoadGraph((Application::PATH_IMAGE + "Exit.png").c_str());
	gameOffImg_ =  LoadGraph((Application::PATH_IMAGE + "GameStart_Off.png").c_str());
	exitOffImg_ = LoadGraph((Application::PATH_IMAGE + "Exit_Off.png").c_str());

	selectImg_ = LoadGraph((Application::PATH_IMAGE + "Command/Select.png").c_str());

	gameImgPos_X = 300;
	gameImgpos_Y = 350;

	exitImgPos_X = 300;
	exitImgPos_Y = 450;

	selectImgPos_X = 200;
	
	AudioManager::GetInstance()->LoadSceneSound(LoadScene::TITLE);
	AudioManager::GetInstance()->PlayBGM(SoundID::BGM);
	AudioManager::GetInstance()->SetBgmVolume(150);
}


void TitleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	VECTOR dir = AsoUtility::VECTOR_ZERO;
 

	if (ins.IsTrgDown(KEY_INPUT_UP))
	{
		AudioManager::GetInstance()->SetSeVolume(150);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_TITLE_COMMAND);
		cursorIndx_--;

		if (cursorIndx_ < 0)
		{

			cursorIndx_ = static_cast<int>(STATE::MAX) - 1;
		}
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN))
	{
		AudioManager::GetInstance()->SetSeVolume(150);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_TITLE_COMMAND);
		cursorIndx_++;

		if (cursorIndx_ > (int)STATE::MAX - 1)
		{
			cursorIndx_ = 0;
		}
	}

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		AudioManager::GetInstance()->SetBgmVolume(100);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_TITLE_DECISION);
		ChagneState((STATE)cursorIndx_);

	}
	//わからない
	if (GetJoypadNum() == 0)
	{
		
	}
	else
	{
		//PAD操作

		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
		ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1,InputManager::JOYPAD_BTN::LEFT);
	}
	

}

void TitleScene::Draw(void)
{

	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgTitle_, true);

	//DrawString(0, 0, "TitleScene", 0xffffff);
	//DrawString(0, 80, "スペース：決定：→キーで：選択", 0xffffff);
	

	/*DrawGraph(gameImgPos_X, gameImgpos_Y, gameImg_, true);
	DrawGraph(exitImgPos_X, exitImgPos_Y, exitImg_, true);*/


	// 「GAME START」の描画を画像で切り替える
	if (cursorIndx_ == (int)STATE::GAME)
	{
		// 選択中
		DrawGraph(gameImgPos_X, gameImgpos_Y, gameImg_, true);
		
		DrawGraph(selectImgPos_X , gameImgpos_Y +20, selectImg_, true);
	}
	else
	{
		// 非選択中
		DrawGraph(gameImgPos_X, gameImgpos_Y, gameOffImg_, true);
	}

	// 「EXIT」の描画を画像で切り替える
	if (cursorIndx_ == (int)STATE::EXIT)
	{
		// 選択中
		DrawGraph(exitImgPos_X, exitImgPos_Y, exitImg_, true);

		DrawGraph(selectImgPos_X , exitImgPos_Y +20, selectImg_, true);
	}
	else
	{
		// 非選択中
		DrawGraph(exitImgPos_X, exitImgPos_Y, exitOffImg_, true);
	}
	
}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(gameImg_);
	DeleteGraph(exitImg_);
	DeleteGraph(exitOffImg_);
	DeleteGraph(gameOffImg_);
	DeleteSoundMem(titleHundle_);
}

void TitleScene::ChangeExit(void)
{
	SceneManager::GetInstance().SetGameEnd();
}

void TitleScene::ChangeGame(void)
{
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);
}

void TitleScene::ChagneState(STATE next)
{
	state_ = next;

	switch (next)
	{
	case TitleScene::STATE::GAME:

		AudioManager::GetInstance()->StopBGM();
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);

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






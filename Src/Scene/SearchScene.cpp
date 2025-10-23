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

	isPauseAlive_ = false;
	
}

void SearchScene::Update(void)
{
	//ポーズ処理を行う
	Pause();

	//ポーズがオンの状態
	if(isPauseAlive_)
	{
		return;
	}



	// シーン遷移
	InputManager& ins = InputManager::GetInstance();




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
	DrawString(0, 80, "PADを接続してる場合はPADで移動", 0xffffff);
	DrawString(0, 120, "PADを接続してない場合はWASDで移動", 0xffffff);

	if (isPauseAlive_)
	{
		PauseDraw();
		DrawCommand();
	}
}

void SearchScene::Release(void)
{
	grid_->Release();
	delete grid_;

	player_->Release();
	delete player_;
}

void SearchScene::Pause(void)
{

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_ESCAPE))
	{
		isPauseAlive_ = !isPauseAlive_;
	}

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_UP))
	{
		cursorIndx_--;

		if (cursorIndx_ < 0)
		{
			cursorIndx_ = static_cast<int>(STATE::MAX) - 1;
		}
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_DOWN))
	{
		cursorIndx_++;

		if (cursorIndx_ > (int)STATE::MAX - 1)
		{
			cursorIndx_ = 0;
		}
	}

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		ChagneState((STATE)cursorIndx_);

	}

}

void SearchScene::PauseDraw(void)
{
	int screenWidth = Application::SCREEN_SIZE_X;
	int screenHeight = Application::SCREEN_SIZE_Y;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, screenWidth, screenHeight, 0x000000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを元に戻す

	// ポーズ画面のテキスト描画
	const char* pauseMessage = "PAUSE";

	int white = GetColor(255, 255, 255);

	// PAUSE メッセージを画面中央に大きく表示
	DrawFormatString(screenWidth / 2 - 50, screenHeight / 3 - 50, white, "%s", pauseMessage);

	
}

void SearchScene::ChangeExit(void)
{
	SceneManager::GetInstance().SetGameEnd();
}

void SearchScene::ChangeGame(void)
{
	isPauseAlive_ = !isPauseAlive_;
}

void SearchScene::ChagneState(STATE next)
{
	state_ = next;

	switch (next)
	{
	case SearchScene::STATE::GAME:
		isPauseAlive_ = !isPauseAlive_;
		break;
	case SearchScene::STATE::EXIT:
		isEnd_ = true;

		if (isEnd_ == true)
		{
			Application::GetInstance().End();
		}
		break;

	}
}

void SearchScene::DrawCommand()
{
	// 2. 「GAME START」の描画
	if (cursorIndx_ == (int)STATE::GAME)
	{

		// 選択中の場合、色を変えてカーソルを付ける
		DrawString(300, RETUTN_GAME_POS_Y, CURSOR_CHAR, GetColor(255, 255, 0)); // 黄色のカーソル
		DrawString(330, RETUTN_GAME_POS_Y, "GAME START", GetColor(255, 255, 0)); // 黄色
	}
	else
	{
		// 非選択中の場合
		DrawString(330, RETUTN_GAME_POS_Y, "GAME START", GetColor(200, 200, 200)); // グレー
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

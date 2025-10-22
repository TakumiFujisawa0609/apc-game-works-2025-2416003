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

}

void SearchScene::PauseDraw(void)
{
	int screenWidth = Application::SCREEN_SIZE_X;
	int screenHeight = Application::SCREEN_SIZE_Y;

	SetDrawBlendMode(DX_BLEND_SRC_ALPHA, 128);
	DrawBox(0, 0, screenWidth, screenHeight, 0x000000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを元に戻す

	// ポーズ画面のテキスト描画
	const char* pauseMessage = "PAUSE";
	const char* resumeMessage = "Press ESC to Resume";
	int white = GetColor(255, 255, 255);

	// PAUSE メッセージを画面中央に大きく表示
	DrawFormatString(screenWidth / 2 - 50, screenHeight / 2 - 50, white, "%s", pauseMessage);

	// 再開メッセージ
	DrawFormatString(screenWidth / 2 - 100, screenHeight / 2 + 50, white, "%s", resumeMessage);

}

#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../Game/GameScene.h"
#include "../../Manager/Camera.h"
#include "../../Object/Grid.h"
#include "SearchScene.h"
#include "../../Object/MapPlayer/MapPlayer.h"
#include "../../Sound/AudioManager.h"
#include "../../Object/Enemy/EnemyBase.h"

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


	remainingSteps_ = GetRand(ENCOUNT_MAX_STEPS - ENCOUNT_MIN_STEPS) + ENCOUNT_MIN_STEPS;
	accumulatedDistance_ = 0.0f;


	AudioManager::GetInstance()->LoadSceneSound(LoadScene::GAME);
	AudioManager::GetInstance()->PlayBGM(SoundID::BGM_SEARCH);
	AudioManager::GetInstance()->SetBgmVolume(150);
	
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



	// シーン遷
	InputManager& ins = InputManager::GetInstance();


	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		AudioManager::GetInstance()->StopBGM();
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);

	}


	nowPos_ = player_->GetPos();
	EnCount();
	prePos_ = nowPos_;

	

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

	// 1. ポーズON/OFF切り替えと音量調整
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_ESCAPE))
	{
		isPauseAlive_ = !isPauseAlive_;

		// 音量調整
		if (isPauseAlive_ == false)
		{
			AudioManager::GetInstance()->SetBgmVolume(BGM_SOUND_VOLUME);
		}

		if (isPauseAlive_)
		{
			AudioManager::GetInstance()->SetBgmVolume(BGM_SOUND_VOLUME_ZERO);
		}
	}

	// 2. ポーズ中のメニュー操作 (isPauseAlive_がtrueのときのみ実行)
	if (isPauseAlive_)
	{
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
			// ここで ChagneState((STATE)cursorIndx_) が呼ばれ、
			// STATE::GAMEが選択されていれば isPauseAlive_ が反転し、ポーズが解除されます。
			ChagneState(static_cast<STATE>(cursorIndx_));
		}
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
		AudioManager::GetInstance()->PlayBGM(SoundID::BGM_SEARCH);
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

void SearchScene::EnCount(void)
{
	VECTOR diff = VSub(nowPos_, prePos_);
	diff.y = 0.0f; // Y軸(高さ)の差分は無視

	float distanceMoved = VSize(diff);

	if (distanceMoved < 0.01f)
	{
		return;
	}

	accumulatedDistance_ = distanceMoved;

	while (accumulatedDistance_ >= STEP_DISTANCE)
	{
		accumulatedDistance_ -= STEP_DISTANCE; // 1歩分消費
		remainingSteps_--;                           // 残りエンカウント歩数を減らす

		// 4. エンカウント判定
		if (remainingSteps_ <= 0)
		{
			EnemyBase::TYPE enemyType = EnemyBase::TYPE::GOBLIN;

			

			// エンカウント発生！
			AudioManager::GetInstance()->PlaySE(SoundID::SE_ENCOUNT);//エンカウントSE再生
			AudioManager::GetInstance()->StopBGM();
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);

			// 次のエンカウント歩数を再設定
			remainingSteps_ = GetRand(ENCOUNT_MAX_STEPS - ENCOUNT_MIN_STEPS) + ENCOUNT_MIN_STEPS;
			accumulatedDistance_ = 0.0f; // 蓄積距離もリセット

			// 戦闘に移行するため、ここで処理を終了
			return;
		}
	}
}

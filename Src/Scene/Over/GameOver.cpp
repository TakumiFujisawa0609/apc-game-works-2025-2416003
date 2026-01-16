#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Sound/AudioManager.h"
#include "GameOver.h"

GameOver::GameOver(void)
{
}

GameOver::~GameOver(void)
{
}

void GameOver::Init(void)
{
	gameOverImg_ = LoadGraph((Application::PATH_IMAGE + "GameOver.png").c_str());
	pushImg_ = LoadGraph((Application::PATH_IMAGE + "Push.png").c_str());

	AudioManager::GetInstance()->LoadSceneSound(LoadScene::TITLE);
	AudioManager::GetInstance()->PlayBGM(SoundID::BGM_GAMEOVER);
	AudioManager::GetInstance()->SetBgmVolume(200);
}

void GameOver::Update(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{

		ChangeTitle();
	}
}

void GameOver::Draw(void)
{
	//DrawString(320, 240, "ゲームクリア！", GetColor(255, 255, 255));
	DrawGraph(260, 200, gameOverImg_, true);

	DrawGraph(200, 500, pushImg_, true);

}

void GameOver::Release(void)
{
	DeleteGraph(gameOverImg_);
	DeleteGraph(pushImg_);
}

void GameOver::ChangeTitle(void)
{

	AudioManager::GetInstance()->StopBGM();
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
}

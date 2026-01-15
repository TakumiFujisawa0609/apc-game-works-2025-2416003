#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Sound/AudioManager.h"
#include "GameClear.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
	gameClearImg_ = LoadGraph((Application::PATH_IMAGE + "GameClear.png").c_str());
	pushImg_ = LoadGraph((Application::PATH_IMAGE + "Push.png").c_str());

	AudioManager::GetInstance()->LoadSceneSound(LoadScene::TITLE);
	AudioManager::GetInstance()->PlayBGM(SoundID::BGM);
	AudioManager::GetInstance()->SetBgmVolume(150);
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
	//DrawString(320, 240, "ゲームクリア！", GetColor(255, 255, 255));
	DrawGraph(210, 100, gameClearImg_, true);

	DrawGraph(200, 500, pushImg_, true);

}

void GameClear::Release(void)
{
	DeleteGraph(gameClearImg_);
	DeleteGraph(pushImg_);
}

void GameClear::ChangeTitle(void)
{

	AudioManager::GetInstance()->StopBGM();
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
}

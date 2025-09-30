#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "GameScene.h"
#include "../Object/Enemy/EnemyBase.h"
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
	state_ = STATE::SELECT;

	actionTime_ = 0;

	enemy_ = new EnemyBase();
	enemy_->Init();


}

void BattleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

	switch (state_)
	{
	case BattleScene::STATE::SELECT://コマンド選択
		
		firstcommand_ = true;
		
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

			if (cursorIndx_ > (int)COMMAND::MAX)
			{
				cursorIndx_ = 0;
			}
		}

		if (ins.IsTrgDown(KEY_INPUT_RETURN))
		{
			ChangeCommand((COMMAND)cursorIndx_);
			state_ = STATE::ACTION;
			firstcommand_ = false;
		}
		break;

		//コマンド選択状態
	case BattleScene::STATE::ACTION:
		if (--actionTime_ <= 0)
		{
			firstcommand_ = false;
			state_ = STATE::SELECT;
		}
		break;
	}
	
	
	//強制戦闘終了
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
		firstcommand_ = false;
	}

	//強制戦闘終了
	if (isDamege_ == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
		firstcommand_ = false;
	}
}

void BattleScene::Draw(void)
{

	DrawFormatString(400, 100, 0xffffff, "EnemyHp:%d", enemyHp_);
	enemy_->Draw();


	DrawString(0, 0, "BattleScene", 0xffffff);
	if (firstcommand_ == true)
	{
		const char* commands[] =
		{
			"たたかう",
			"アイテム",
			"にげる"
		};

		CreateBox(80, 450, 200, 150, GetColor(0, 0, 255));

		for (int i = 0; i < (int)COMMAND::MAX; i++)
		{
			int color = (i == cursorIndx_) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
			DrawString(100, 470 + i * 30, commands[i], color);

		}
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
		Damage();
		//printfDx("たたかった\n");
		break;


	case BattleScene::COMMAND::TOOl: //道具
		//printfDx("アイテム\n");
		break;


	case BattleScene::COMMAND::ESCAPE:  //逃げる
		//printfDx("逃げる\n");
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);

		break;


	default:
		break;
	}

}

void BattleScene::ChagneState(STATE next)
{
	state_ = next;

	switch (state_)
	{
	case BattleScene::STATE::SELECT:
		
		break;
	case BattleScene::STATE::ACTION:
		break;
	case BattleScene::STATE::END:
		
		break;

	}
}

void BattleScene::CreateBox(int x, int y, int width, int height, int color)
{
	DrawBox(x, y, x + width, y + height, color, true);
}

void BattleScene::Damage(void)
{

	if (enemyHp_ > 0)
	{

		enemyHp_ = enemyHp_ - damege_;
	}

	if (enemyHp_ <= 0)
	{
		isDamege_ = true;
	}
	
}




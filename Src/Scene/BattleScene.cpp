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

	cursorIndx_ = 0;//選択コマンド初期状態
	turnIndx_ = 0;//ターン最初の状態
	endIndx_ = 0;//戦闘終了状態

	command_ = COMMAND::BATTLE;
	//state_ = STATE::SELECT;

	actionTime_ = 0;

	enemy_ = new EnemyBase();
	enemy_->Init();
}

void BattleScene::Update(void)
{
	


	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

	//勝利で戦闘終了
	if (isDamege_ == true)
	{
		endIndx_ = int(END::WIN);
	}

	if (isDamege_ == false)
	{
		//ゲームフローの切り替え
		if (int(TURN::MAX) >= turnIndx_)
		{
			if (ins.IsTrgDown(KEY_INPUT_RETURN))
			{
				turnIndx_++;
			}
		}
		if (int(TURN::MAX) == turnIndx_)
		{
			turnIndx_ = 0;
		}

		//ターンがプレイヤーの時のみアクションコマンド選択可能

		//アクションコマンド選択
		if (int(TURN::SELECT) == turnIndx_)
		{
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

			//各コマンド選択(後でchangecommandにまとめる)
			//選択コマンド決定（仮）（攻撃）
			if (int(COMMAND::BATTLE) == cursorIndx_)
			{
				if (ins.IsTrgDown(KEY_INPUT_SPACE))
				{
					Damage();
					turnIndx_++;
				
				}
			}
			//選択コマンド決定（仮）（逃げる）
			if (int(COMMAND::ESCAPE) == cursorIndx_)
			{
				if (ins.IsTrgDown(KEY_INPUT_SPACE))
				{
					SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
					firstcommand_ = false;
				}
			}
			//選択コマンド決定（仮）（攻撃）
			if (int(COMMAND::TOOl) == cursorIndx_)
			{
				if (ins.IsTrgDown(KEY_INPUT_SPACE))
				{
					turnIndx_++;
					
				}
			}


		}
	}

	//強制戦闘終了
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
		firstcommand_ = false;
	}

	//戦闘終了後のリザルト
	if (endIndx_ == int(END::WIN))
	{
		actionTime_++;
		if (actionTime_ > 120)
		{
			rewordIndx++;
			actionTime_ = 0;
		}

		if (int(END_REWARD::MONEY) == rewordIndx)
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
			firstcommand_ = false;
		}
	}
	
}

void BattleScene::Draw(void)
{

	DrawFormatString(400, 100, 0xffffff, "EnemyHp:%d", enemyHp_);
	enemy_->Draw();
	DrawString(0, 80, "Nキーまたは逃げるコマンドでサーチシーン　コマンドは→キーで決定はエンターキー", 0xffffff);

	DrawString(0, 0, "BattleScene", 0xffffff);

	DrawTurn((TURN)turnIndx_);
	DrawCommand((COMMAND)cursorIndx_);
	DrawEnd((END)endIndx_);
	if (isDamege_ == true)
	{
		DrawReword((END_REWARD)rewordIndx);
	}

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

		break;
	//case BattleScene::COMMAND::SKILL: //道具

	//	break;
	case BattleScene::COMMAND::TOOl: //道具
	
		break;
	case BattleScene::COMMAND::ESCAPE:  //逃げる
		
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);

		break;

	}

}

void BattleScene::ChangeTurn(TURN turn)
{
	turn_ = turn;

	switch (turn_)
	{
	case BattleScene::TURN::TURN_START:
		break;
	case BattleScene::TURN::SELECT:
		break;
	case BattleScene::TURN::PLAYER:
		break;
	case BattleScene::TURN::PLAYER_ACTION:
		break;
	case BattleScene::TURN::ENEMY:
		break;
	case BattleScene::TURN::ENEMY_ACTION:
		break;
	case BattleScene::TURN::TURN_END:
		break;
	case BattleScene::TURN::MAX:
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

void BattleScene::DrawTurn(TURN turn)
{
	const char* name = "";

	if (turn == TURN::TURN_START) name = "ターンスタート";
	else if (turn == TURN::SELECT) name = "コマンド選択中";
	else if (turn == TURN::PLAYER) name = "プレイヤーターン";
	else if (turn == TURN::ENEMY) name = "エネミーターン";
	else if (turn == TURN::PLAYER_ACTION) name = "行動中";
	else if (turn == TURN::ENEMY_ACTION) name = "敵行動中";
	else if (turn == TURN::TURN_END) name = "ターンエンド";


	DrawFormatString(100, 100, GetColor(255, 255, 255), ": %s", name);
}

void BattleScene::DrawCommand(COMMAND command)
{
	const char* name = "";

	if (command == COMMAND::BATTLE) name = "たたかう";
	else if (command == COMMAND::TOOl) name = "道具";
	else if (command == COMMAND::ESCAPE) name = "にげる";


	DrawFormatString(100, 130, GetColor(255, 255, 255), ": %s", name);
}

void BattleScene::DrawEnd(END end)
{
	const char* name = "";

	if (end == END::WIN) name = "WIN";
	else if (end == END::IN_BATTLE) name = "戦闘中";
	else if (end == END::LOSE) name = "LOSE";
	else if (end == END::ESCAPE) name = "にげる";


	DrawFormatString(100, 160, GetColor(255, 255, 255), ": %s", name);
}

void BattleScene::DrawReword(END_REWARD endreword)
{
	const char* name = "";

	if (endreword == END_REWARD::EXP) name = "経験値";
	else if (endreword == END_REWARD::ITEM) name = "アイテム";
	else if (endreword == END_REWARD::MONEY) name = "お金";


	DrawFormatString(100, 190, GetColor(255, 255, 255), ": %s", name);
}




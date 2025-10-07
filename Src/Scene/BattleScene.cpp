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

	if (endIndx_ == (int)END::WIN)
	{
		//勝利判定が取れたら、戦闘終了
		state_ = STATE::BATTLE_END;
		actionTime_ = 0;
	}
	// Nキーでの強制終了（デバッグ用）
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
		firstcommand_ = false;
		return; // シーン遷移後は以降の処理をスキップ
	}
	switch (state_)
	{
	case BattleScene::STATE::TURN_START:

		state_ = STATE::COMMAND_SELECT;
		break;
	case BattleScene::STATE::COMMAND_SELECT:
		HandleCommandSelectInput();

		//決定処理
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			ExecuteCommand(static_cast<COMMAND>(cursorIndx_));
		}
		break;
	case BattleScene::STATE::SKILL_SELECT:

		// 現在の isSelectingSkill_ のブロック
		HandleSkillSelectInput();
		break;
	case BattleScene::STATE::PLAYER_ACTION:
		// プレイヤーの行動（アニメーション、ダメージ計算など）
		// プレイヤーの行動アニメーションやダメージ表示の待機
		actionTime_++;
		if (actionTime_ > 60) // 1秒(60フレーム)待機
		{
			actionTime_ = 0;

			if (endIndx_ == (int)END::WIN)
			{
				// 敵を倒した場合は、この後 BATTLE_END に移行（共通ロジックで処理）
			}
			else
			{
				// 敵が生きている場合は、敵のターンへ
				state_ = STATE::ENEMY_ACTION;
			}
		}
		break;
	case BattleScene::STATE::ENEMY_ACTION:

		// 敵の行動処理（AI、アニメーション、ダメージ計算など）
  
		actionTime_++;
		if (actionTime_ > 60) // 敵の行動時間待機
		{
			actionTime_ = 0;
			state_ = STATE::TURN_END;
		}
		break;
	case BattleScene::STATE::TURN_END:
		// ターン終了時のクリーンアップやメッセージ表示
		state_ = STATE::TURN_START;
		break;
	case BattleScene::STATE::BATTLE_END:
		// 戦闘終了後の待機時間処理
			// endIndx_ == (int)END::WIN の判定でここに到達している
		actionTime_++;
		if (actionTime_ > 120) // 2秒待機
		{
			// 報酬表示フェーズへ移行（現在のコードの DrawReword へ繋ぐ）
			state_ = STATE::REWARD_VIEW;
			actionTime_ = 0; // actionTime_を再利用するためにリセット
		}

		break;
	case BattleScene::STATE::REWARD_VIEW:
		// 報酬の段階的表示
		if (ins.IsTrgDown(KEY_INPUT_RETURN) || actionTime_ == 0) // 最初の1回またはエンターキー
		{
			rewordIndx++;
			if (rewordIndx >= (int)END_REWARD::MAX)
			{
				// 報酬表示が完了したらシーン遷移
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
				firstcommand_ = false;
				return;
			}
		}
		actionTime_++; // 報酬表示中の待機
		break;

	}
	

}


void BattleScene::Draw(void)
{

	DrawFormatString(400, 100, 0xffffff, "EnemyHp:%d", enemyHp_);
	enemy_->Draw();
	DrawString(0, 80, "Nキーまたは逃げるコマンドでサーチシーン　コマンドは→キーで決定はエンターキー", 0xffffff);

	DrawString(0, 0, "BattleScene", 0xffffff);


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

		CreateBox(90, 450, 150, 150, GetColor(0, 0, 128));

		for (int i = 0; i < (int)COMMAND::MAX; i++)
		{
			int color = (i == cursorIndx_) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
			DrawString(100, 470 + i * 30, commands[i], color);

		}

		DrawSkill();
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

		break;
	
	case BattleScene::COMMAND::TOOl: //道具
	
		break;
	case BattleScene::COMMAND::ESCAPE:  //逃げる
		
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);

		break;

	}

}


void BattleScene::CreateBox(int x, int y, int width, int height, int color)
{
	DrawBox(x, y, x + width, y + height, color, true);
}

void BattleScene::SelectSkill(SKILL skill)
{
	if (selectedSkills_.size() < 2)
	{
		selectedSkills_.push_back(skill);
	}
}

void BattleScene::UseSkill(void)
{
	for (auto skill : selectedSkills_)
	{
		ProcessSkill(skill);
	}

	// 実行後にリセット
	selectedSkills_.clear();
}

void BattleScene::ProcessSkill(SKILL skill)
{

	//各スキルの処理をここで入力
	switch (skill_)
	{
	case BattleScene::SKILL::SLASH:
		damageAmount = 10;
		break;
	case BattleScene::SKILL::PROTECT:
		break;
	case BattleScene::SKILL::HEAL:
		break;
	case BattleScene::SKILL::LIMIT_BREAK:
		damageAmount = 50;
		break;

	}

	// ダメージ適用
	enemyHp_ -= damageAmount;

	// 敵HPが0以下になったかチェック
	if (enemyHp_ <= 0)
	{
		enemyHp_ = 0; // HPがマイナスにならないように
		isDamege_ = true; // 敵撃破フラグを立てる
		endIndx_ = (int)END::WIN; // 勝利状態も同時に設定
	}
}

void BattleScene::Damage(void)
{

	
	if (enemyHp_ <= 0)
	{
		isDamege_ = true;
	}
	
}



void BattleScene::DrawCommand(COMMAND command)
{
	const char* name = "";

	if (command == COMMAND::BATTLE) name = "たたかう";
	else if (command == COMMAND::TOOl) name = "道具";
	else if (command == COMMAND::ESCAPE) name = "にげる";


	DrawFormatString(100, 140, GetColor(255, 255, 255), ": %s", name);
}

void BattleScene::DrawEnd(END end)
{
	const char* name = "";

	if (end == END::WIN) name = "WIN";
	else if (end == END::IN_BATTLE) name = "戦闘中";
	else if (end == END::LOSE) name = "LOSE";
	else if (end == END::ESCAPE) name = "にげる";


	DrawFormatString(100, 170, GetColor(255, 255, 255), ": %s", name);
}

void BattleScene::DrawReword(END_REWARD endreword)
{
	const char* name = "";

	if (endreword == END_REWARD::EXP) name = "経験値";
	else if (endreword == END_REWARD::ITEM) name = "アイテム";
	else if (endreword == END_REWARD::MONEY) name = "お金";


	DrawFormatString(100, 200, GetColor(255, 255, 255), ": %s", name);
}

void BattleScene::DrawSkill(void)
{
	const char* skillNames[] =
	{
		"斬撃",
		"防御",
		"回復",
		"毒",
		"リミットブレイク"
	};

	CreateBox(350, 350, 250, 220, GetColor(0, 0, 128));
	DrawString(360, 360, "スキルを2つ選んでください", GetColor(255, 255, 0));

	for (int i = 0; i < 5; i++)
	{
		int color = (i == skillIndx_) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
		DrawString(380, 390 + i * 30, skillNames[i], color);
	}

	DrawFormatString(380, 570, GetColor(200, 200, 200), "選択中：%d / 2", (int)selectedSkills_.size());
}

void BattleScene::HandleCommandSelectInput()
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	// カーソル移動 (修正後の範囲チェック)
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
		// 修正: MAX自体は有効なインデックスではないので、等号を含める
		if (cursorIndx_ >= (int)COMMAND::MAX)
		{
			cursorIndx_ = 0;
		}
	}
}

void BattleScene::ExecuteCommand(COMMAND command)
{
	// 各コマンド決定処理を switch で統一
	switch (command)
	{
	case COMMAND::BATTLE:
		// スキル選択状態へ移行
		state_ = STATE::SKILL_SELECT;
		skillIndx_ = 0;
		selectedSkills_.clear();
		// スキル選択画面への遷移時に入力スキップは不要になることが多い
		break;
	case COMMAND::TOOl:
		// 道具使用処理。終了後 PLAYER_ACTION または ENEMY_ACTION へ
		state_ = STATE::PLAYER_ACTION;
		break;
	case COMMAND::ESCAPE:
		// 逃走成功判定などを経てシーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
		firstcommand_ = false;
		break;
	default:
		break;
	}
}

void BattleScene::HandleSkillSelectInput()
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

	const int skillCount = 5; // SKILL::MAXに置き換えるのが望ましい

	// カーソル移動
	if (ins.IsTrgDown(KEY_INPUT_UP))
	{
		skillIndx_--;
		if (skillIndx_ < 0)
		{
			skillIndx_ = skillCount - 1;
		}
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN))
	{
		skillIndx_++;
		if (skillIndx_ >= skillCount)
		{
			skillIndx_ = 0;
		}
	}

	// スキル決定
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SelectSkill(static_cast<SKILL>(skillIndx_));

		if (selectedSkills_.size() >= 2)
		{
			UseSkill();
			state_ = STATE::PLAYER_ACTION; // 行動処理フェーズへ
		}
	}

	// キャンセル処理
	if (ins.IsTrgDown(KEY_INPUT_X))
	{
		selectedSkills_.clear();
		state_ = STATE::COMMAND_SELECT; // コマンド選択へ戻る
	}
}




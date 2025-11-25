#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../Game/GameScene.h"
#include "../../Object/Enemy/EnemyBase.h"
#include "BattleScene.h"
#include "../../Object/Enemy/Manger/EnemyManager.h"
#include "../../Object/Enemy/Manger/EnemyStatusManager.h"
#include "../../Object/Skill/SkillManager.h"
#include "../../Manager/Camera.h"
#include "../../Sound/AudioManager.h"




BattleScene::BattleScene(void)
{

}

BattleScene::~BattleScene(void)
{
}

void BattleScene::Init(void)
{	

	

	//シングルトンからインスタンスを取得
	EnemyStatusManager* statusManager = EnemyStatusManager::Getinstance();
	//敵の種類を取得
	EnemyBase::TYPE enemyType = statusManager->GetNextEncounterType();
	//敵のデータ取得
	const EnemyData& baseData = statusManager->GetEnemyData(enemyType);

	enemyHp_ = baseData.hp_;

	enemyManager_ = new EnemyManager();
	enemyManager_->Init();

	SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

	BattleInit();

	AudioManager::GetInstance()->LoadSceneSound(LoadScene::GAME);
	AudioManager::GetInstance()->LoadSceneSound(LoadScene::SKILL);
	AudioManager::GetInstance()->PlayBGM(SoundID::BGM_BATTLE);
	AudioManager::GetInstance()->SetBgmVolume(150);
	

	skillManger_ = new SkillManager();
	skillManger_->Init();
	
	backImg = LoadGraph((Application::PATH_IMAGE + "BackStage.jpg").c_str());

}

void BattleScene::Update(void)
{

	//ポーズ処理を行う
	Pause();

	//ポーズがオンの状態
	if (isPauseAlive_)
	{
		//AudioManager::GetInstance()->StopBGM();
		return;
	}

	enemyManager_->Update();

	//シーン遷移
	InputManager& ins = InputManager::GetInstance();

	//テスト
	if (ins.IsTrgDown(KEY_INPUT_2))
	{
		test++;
	}
	if (ins.IsTrgDown(KEY_INPUT_3))
	{
		test--;
	}
	if (ins.IsTrgDown(KEY_INPUT_4))
	{
		
	}
	




	skillManger_->Update();
	

	// シーン遷移
	//InputManager& ins = InputManager::GetInstance();

	if (endIndx_ == (int)END::WIN)
	{
		//勝利判定が取れたら、戦闘終了
		state_ = STATE::BATTLE_END;
		actionTime_ = 0;
	}
	// Nキーでの強制終了（デバッグ用）
	if (ins.IsTrgDown(KEY_INPUT_N))
	{
		AudioManager::GetInstance()->StopBGM();
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
			AudioManager::GetInstance()->SetSeVolume(100);
			AudioManager::GetInstance()->PlaySE(SoundID::SE_COMMAND_DECISION);
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
		if (actionTime_ > ONE_SECOND) // 1秒(60フレーム)待機
		{
			actionTime_ = 0;

			if (isDamege_)
			{
				//endIndx_ = (int)END::WIN
				// 敵を倒した場合は、この後 BATTLE_END に移行（共通ロジックで処理）
				state_ = STATE::BATTLE_END;
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

		// 敵の攻撃計算（1回だけ）
		if (actionTime_ == 0)
		{
			EnemyAttack();
		}

		actionTime_++;

		if (actionTime_ > ONE_SECOND)
		{
			actionTime_ = 0;

			if (playerDead_)
			{
				state_ = STATE::BATTLE_END;
			}
			else
			{
				state_ = STATE::TURN_END;
			}
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
		if (actionTime_ > ONE_SECOND) // 1秒待機
		{
			AudioManager::GetInstance()->SetSeVolume(300);
			AudioManager::GetInstance()->PlaySE(SoundID::SE_WIN);

			// 報酬表示フェーズへ移行（現在のコードの DrawReword へ繋ぐ）
			state_ = STATE::REWARD_VIEW;
			actionTime_ = 0; // actionTime_を再利用するためにリセット
		}

	
		break;
	case BattleScene::STATE::REWARD_VIEW:
		
		rewordIndx++;

		if (rewordIndx >= (int)END_REWARD::MAX)
		{
			int count = SceneManager::GetInstance().GetDefeatedEnemyCount();

			if (count >= CLEAR_ENEMY_COUNT)
			{
				AudioManager::GetInstance()->StopBGM();
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
				return;
			}
		
			AudioManager::GetInstance()->StopBGM();
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
			firstcommand_ = false;
			return;
			
		}

	}
	
	

}


void BattleScene::Draw(void)
{

 	//DrawGraph(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, backImg,false);
	//DrawRotaGraph(400 ,300,1.0f, 0.0, backImg, true);
	DrawExtendGraph(0,0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, backImg, true);

	DrawFormatString(900, 140, 0xffffff, "PlayerHp:%d", playerHp_);
	DrawFormatString(900, 100, 0xffffff, "EnemyHp:%d", enemyHp_);

	//DrawString(0, 80, "Nキーまたは逃げるコマンドでサーチシーン　コマンドは→キーで決定はエンターキー", 0xffffff);

	int offsetX = 0;
	int offsetY = 0;

	// 揺れ中ならランダムでオフセットを作る
	if (shakeDuration_ > 0)
	{
		offsetX = rand() % (shakeMagnitude_ * 2 + 1) - shakeMagnitude_;
		offsetY = rand() % (shakeMagnitude_ * 2 + 1) - shakeMagnitude_;
		shakeDuration_--;
	}

	// 例えば背景描画
	DrawExtendGraph(0 + offsetX, 0 + offsetY,
		Application::SCREEN_SIZE_X + offsetX,
		Application::SCREEN_SIZE_Y + offsetY,
		backImg, true);

	
	
	//敵の描画
	if (isDamege_ == false)
	{
		enemyManager_->Draw();


		DrawHpBar(700, 100, 100, 15, enemyHp_, enemyHpMax_);
		SetFontSize(10);
		DrawString(700, 80, "HP", GetColor(255, 255, 255));
		SetFontSize(15);
	}

	//HPUIの描画
	DrawHpBar(100, 400, 120, 20, playerHp_, playerHpMax_);
	DrawFormatString(100, 380, 0xffffff, "HP: %d / %d", playerHp_, playerHpMax_);


	//コマンド描画
	//DrawCommand((COMMAND)cursorIndx_);

	//DrawStates((STATE)state_);
	//((END)endIndx_);
	/*if (state_ == STATE::REWARD_VIEW)
	{
		DrawReword((END_REWARD)rewordIndx);
	}*/




	if (firstcommand_ == true)
	{
		const char* commands[] =
		{
			"たたかう",
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

	if (isPauseAlive_)
	{
		//ポーズ画面の描画
		PauseDraw();
	}
	
	
}
	

void BattleScene::Release(void)
{

	skillManger_->Release();
	enemyManager_->Release();
	delete enemyManager_;
}


void BattleScene::ChangeCommand(COMMAND command)
{
	command_ = command;

	switch (command_)
	{
		//コマンド選択						
	case BattleScene::COMMAND::BATTLE: //戦う
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

void BattleScene::Pause(void)
{

	// Nキーでの強制終了（デバッグ用）
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_N))
	{
		AudioManager::GetInstance()->StopBGM();
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SEARCH);
		firstcommand_ = false;
		return; // シーン遷移後は以降の処理をスキップ
	}

	//ESCキーが押されたらポーズ状態を切り替え
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_ESCAPE))
	{

		isPauseAlive_ = !isPauseAlive_;

		if (isPauseAlive_ == false)
		{
			AudioManager::GetInstance()->SetBgmVolume(BGM_SOUND_VOLUME);
		}

		if (isPauseAlive_)
		{
			AudioManager::GetInstance()->SetBgmVolume(BGM_SOUND_VOLUME_ZERO);
		}

	}
}

void BattleScene::PauseDraw(void)
{
	int screenWidth = Application::SCREEN_SIZE_X;
	int screenHeight = Application::SCREEN_SIZE_Y;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//DX_BLEND_SRC_ALPHA
	DrawBox(0, 0, screenWidth, screenHeight, 0x000000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを元に戻す

	// ポーズ画面のテキスト描画
	const char* pauseMessage = "PAUSE";
	const char* resumeMessage = "Press ESC to Resume";
	int white = GetColor(255, 255, 255);

	// PAUSE メッセージを画面中央に大きく表示
	DrawFormatString(screenWidth / 2 - 50, screenHeight / 2 - 50, white, "%s", pauseMessage);

	// 再開メッセージ
	DrawFormatString(screenWidth / 2 - 100, screenHeight / +50, white, "%s", resumeMessage);
}

void BattleScene::BattleInit(void)
{
	cursorIndx_ = 0;//選択コマンド初期状態
	turnIndx_ = 0;//ターン最初の状態
	endIndx_ = 0;//戦闘終了状態
	rewordIndx = 0;//戦闘報酬状態

	actionTime_ = 0;

	command_ = COMMAND::BATTLE;
}

void BattleScene::SelectSkill(SKILL skill)
{
	if (selectedSkills_.size() < 1)
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
	
	damageAmount = 0;


	//各スキルの処理をここで入力
	switch (skill)
	{
	case BattleScene::SKILL::SLASH:
		damageAmount = 10;
		Damage();
		break;
	case BattleScene::SKILL::FLAME:
		damageAmount = 20;
		Flame();
		break;
	case BattleScene::SKILL::HEAL:
		Hell();
		break;
	case BattleScene::SKILL::LIMIT_BREAK:
		damageAmount = 30;
		Damage();
		break;

	}

	

	// 敵HPが0以下になったかチェック
	if (enemyHp_ <= 0)
	{
		enemyHp_ = 0; // HPがマイナスにならないように
		isDamege_ = true; // 敵撃破フラグを立てる
		state_ = STATE::BATTLE_END;

		SceneManager::GetInstance().AddDefeatedEnemy();
	}
}

void BattleScene::Damage(void)
{
	// ダメージ適用
	AudioManager::GetInstance()->PlaySE(SoundID::SKILL_SE_SLASH);

	enemyHp_ -= damageAmount;

	if (enemyHp_ <= 0)
	{
		isDamege_ = true;
	}
}

void BattleScene::Hell(void)
{
	AudioManager::GetInstance()->PlaySE(SoundID::SKILL_SE_HELL);
	if (playerHp_ < playerHpMax_)
	{
		playerHp_ += 30;

		if (playerHp_ >= playerHpMax_)
		{
			playerHp_ = playerHpMax_;
		}
	}
}

void BattleScene::Flame(void)
{
	// ダメージ適用
	AudioManager::GetInstance()->PlaySE(SoundID::SKILL_SE_SLASH);

	enemyHp_ -= damageAmount;

	if (enemyHp_ <= 0)
	{
		isDamege_ = true;
	}
}



void BattleScene::EnemyAttack(void)
{
	int enemyDamage = 10;

	playerHp_ -= enemyDamage;

	AudioManager::GetInstance()->PlaySE(SoundID::SKILL_SE_DAMEGE);

	 // 画面揺れ開始
	shakeDuration_ = 15; // 15フレーム揺れる

	if (playerHp_ <= 0)
	{
		playerHp_ = 0;
		playerDead_ = true;
		endIndx_ = (int)END::LOSE;
		state_ = STATE::BATTLE_END;
	}
}

void BattleScene::DrawCommand(COMMAND command)
{
	const char* name = "";

	if (command == COMMAND::BATTLE) name = "たたかう";
	//else if (command == COMMAND::TOOl) name = "アイテム";
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
		"炎",
		"回復",
		"リミットブレイク",
	};

	CreateBox(350, 350, 250, 220, GetColor(0, 0, 128));
	DrawString(360, 360, "スキルを選んでください", GetColor(255, 255, 0));

	for (int i = 0; i < 4; i++)
	{
		int color = (i == skillIndx_) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
		DrawString(380, 390 + i * 30, skillNames[i], color);
	}

	//DrawFormatString(380, 570, GetColor(200, 200, 200), "選択中：%d / 2", (int)selectedSkills_.size());
}

void BattleScene::DrawStates(STATE state)
{
	const char* name = "";
	if (state == STATE::TURN_START) name = "TURN_START";
	else if (state == STATE::COMMAND_SELECT) name = "COMMAND_SELECT";
	else if (state == STATE::SKILL_SELECT) name = "SKILL_SELECT";
	else if (state == STATE::PLAYER_ACTION) name = "PLAYER_ACTION";
	else if (state == STATE::ENEMY_ACTION) name = "ENEMY_ACTION";
	else if (state == STATE::TURN_END) name = "TURN_END";
	else if (state == STATE::BATTLE_END) name = "BATTLE_END";
	else if (state == STATE::REWARD_VIEW) name = "REWARD_VIEW";
	DrawFormatString(100, 230, GetColor(255, 255, 255), ": %s", name);
}

void BattleScene::HandleCommandSelectInput()
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	// カーソル移動 (修正後の範囲チェック)
	if (ins.IsTrgDown(KEY_INPUT_UP))
	{
		AudioManager::GetInstance()->SetSeVolume(100);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_COMMAND_SELECT);
		cursorIndx_--;
		if (cursorIndx_ < 0)
		{
			cursorIndx_ = static_cast<int>(COMMAND::MAX) - 1;
		}
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN))
	{
		AudioManager::GetInstance()->SetSeVolume(100);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_COMMAND_SELECT);
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
	//case COMMAND::TOOl:
	//	// 道具使用処理。終了後 PLAYER_ACTION または ENEMY_ACTION へ
	//	state_ = STATE::PLAYER_ACTION;
	//	break;
	case COMMAND::ESCAPE:
		// 逃走成功判定などを経てシーン遷移
		AudioManager::GetInstance()->StopBGM();
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

	const int skillCount = (int)SKILL::MAX; // SKILL::MAXに置き換えるのが望ましい

	// カーソル移動
	if (ins.IsTrgDown(KEY_INPUT_UP))
	{
		AudioManager::GetInstance()->SetSeVolume(100);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_COMMAND_SELECT);
		skillIndx_--;
		if (skillIndx_ < 0)
		{
			skillIndx_ = skillCount - 1;
		}
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN))
	{
		AudioManager::GetInstance()->SetSeVolume(100);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_COMMAND_SELECT);
		skillIndx_++;
		if (skillIndx_ >= skillCount)
		{
			skillIndx_ = 0;
		}
	}

	// スキル決定
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{

		AudioManager::GetInstance()->SetSeVolume(100);
		AudioManager::GetInstance()->PlaySE(SoundID::SE_COMMAND_DECISION);
		SelectSkill(static_cast<SKILL>(skillIndx_));

		//行動回数処理
		if (selectedSkills_.size() >= 1)
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

void BattleScene::DrawHpBar(int x, int y, int width, int height, int currentHp, int maxHp)
{


	float rate = (float)currentHp / maxHp;
	int barW = (int)(width * rate);

	// 背景枠（少し大きめ）
	int outerMargin = 3; // 外側の余白
	// 外側白
	DrawBox(x - outerMargin, y - outerMargin, x + width + outerMargin, y + height + outerMargin, GetColor(255, 255, 255), TRUE);
	// 内側黒
	DrawBox(x - outerMargin + 1, y - outerMargin + 1, x + width + outerMargin - 1, y + height + outerMargin - 1, GetColor(0, 0, 0), TRUE);

	for (int i = 0; i < barW; i++)
	{
		float t = (float)i / barW; // 0.0~1.0 横位置割合

		int r, g, b;

		// 緑→黄→赤
		if (rate > 0.5f)
		{
			// 緑→黄
			r = (int)(255 * (1.0f - rate) * 2 + 0 * t);
			g = 255;
		}
		else
		{
			// 黄→赤
			r = 255;
			g = (int)(255 * rate * 2);
		}
		b = 0;

		// 1px幅ずつ描画
		DrawBox(x + i, y, x + i + 1, y + height, GetColor(r, g, b), TRUE);
	}

}


unsigned int BattleScene::GetHPColor(float rate)
{
	int r, g, b = 0;

	if (rate > 0.5f)
	{
		// 緑 (0,255,0) → 黄 (255,255,0)
		float t = (rate - 0.5f) / 0.5f;  // 0～1
		r = (int)(255 * t);
		g = 255;
	}
	else
	{
		// 黄 (255,255,0) → 赤 (255,0,0)
		float t = rate / 0.5f;           // 0～1
		r = 255;
		g = (int)(255 * (1.0f - t));
	}

	return GetColor(r, g, b);
}






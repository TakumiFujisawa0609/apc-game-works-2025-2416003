#include <DxLib.h>
#include <cmath>
#include "../../Application.h"
#include "../../Common/AnimationController.h"
#include "../../Manager/Camera.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Utility/AsoUtility.h"
#include "../../Utility/MatrixUtility.h"

#include "MapPlayer.h"

MapPlayer::MapPlayer(void)
{
}

MapPlayer::~MapPlayer(void)
{
}


void MapPlayer::Update(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();


	ActorBase::Update();
	nowPos_ = pos_;
	enCount();
	prePos_ = nowPos_;
}

void MapPlayer::Draw(void)
{

	// デバッグ表示
	DrawFormatString(
		0, 100, 0xffffff,
		"サイコロ角度　 ：(% .1f, % .1f, % .1f)",
		pos_.x, pos_.y, pos_.z);
	
	ActorBase::Draw();
}

void MapPlayer::Release(void)
{
	ActorBase::Release();
}

void MapPlayer::InitLoad(void)
{
	// モデル読み込み
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());
}

void MapPlayer::InitTransform(void)
{
	// モデルの位置設定
	pos_ = DEFAULT_PLAYER_POS;

	// モデルの角度
	angles_ = { 0.0f, 0.0f, 0.0f };
	localAngles_ = { 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f };

	// モデルの大きさ設定
	scales_ = { 0.45f, 0.45f, 0.45f };

	// 角度から方向に変換する
	moveDir_ = { sinf(angles_.y), 0.0f, cosf(angles_.y) };
}

void MapPlayer::InitAnimation(void)
{
	// モデルアニメーション制御の初期化
	animationController_ = new AnimationController(modelId_);

	animationController_->Add(
		static_cast<int>(ANIM_TYPE::IDLE), 30.0f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(
		static_cast<int>(ANIM_TYPE::WALK), 30.0f, Application::PATH_MODEL + "Player/Walk.mv1");
	animationController_->Add(
		static_cast<int>(ANIM_TYPE::RUN), 30.0f, Application::PATH_MODEL + "Player/Run.mv1");
}

void MapPlayer::InitPost(void)
{

	remainingSteps_ = GetRand(ENCOUNT_MAX_STEPS - ENCOUNT_MIN_STEPS) + ENCOUNT_MIN_STEPS;
	accumulatedDistance_ = 0.0f;
	
}

void MapPlayer::Move(void)
{
	auto& ins = InputManager::GetInstance();

	// 攻撃中かチェック
	int currentAnim = animationController_->GetPlayType();
	bool isAttacking = (currentAnim == static_cast<int>(ANIM_TYPE::ATTACK));
	bool isJumping = (currentAnim == static_cast<int>(ANIM_TYPE::JUMP));

	// 攻撃アニメーションが終わったらIDLEに戻す
	if (isAttacking)
	{
		if (animationController_->IsEnd())
		{
			animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
		}
		return;  // 攻撃中は移動処理をスキップ
	}

	// ジャンプアニメーションが終わったらIDLEに戻す
	if (isJumping)
	{
		if (animationController_->IsEnd())
		{
			animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
		}
		return;  // ジャンプ中は移動処理をスキップ
	}

	// カメラの角度を取得
	VECTOR camAngles =
		SceneManager::GetInstance().GetCamera()->GetAngles();

	VECTOR dir = AsoUtility::VECTOR_ZERO;
	// ダッシュ判定
	bool isDash_ = false;

	// ゲームパッドが接続されている数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// キーボード操作
		if (ins.IsNew(KEY_INPUT_W)) { dir = AsoUtility::DIR_F; }
		if (ins.IsNew(KEY_INPUT_A)) { dir = AsoUtility::DIR_L; }
		if (ins.IsNew(KEY_INPUT_S)) { dir = AsoUtility::DIR_B; }
		if (ins.IsNew(KEY_INPUT_D)) { dir = AsoUtility::DIR_R; }

		// ダッシュキー
		isDash_ = ins.IsNew(KEY_INPUT_LSHIFT);
	}
	else
	{
		// ゲームパッド操作
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);

		isDash_ = ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1,
			InputManager::JOYPAD_BTN::LEFT);
	}

	// ダッシュ速度を歩行速度の2倍にする(書き方が違うけどif文と同じ意味)
	float movePow = isDash_ ? 6.0f : 3.0f;

	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZの回転行列
		// XZ平面移動にする場合は、XZの回転を考慮しないようにする
		MATRIX mat = MGetIdent();
		//mat = MMult(mat, MGetRotX(camAngles.x));
		mat = MMult(mat, MGetRotY(camAngles.y));
		//mat = MMult(mat, MGetRotZ(camAngles.z));

		// 回転行列を使用して、ベクトルを回転させる
		moveDir_ = VTransform(dir, mat);

		// 移動方向から角度に変換する
		//angles_.y = atan2f(moveDir_.x, moveDir_.z);

		// 方向×スピードで移動量を作って、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir_, movePow));

		if (isDash_)
		{
			// アニメーションを走りにする
			animationController_->Play(static_cast<int>(ANIM_TYPE::RUN));
		}
		else
		{
			// アニメーションを歩きにする
			animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
		}
	}
	else
	{

		// アニメーションをIDLEにする
		animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));

	}

}

void MapPlayer::enCount(void)
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
			// エンカウント発生！
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);

			// 次のエンカウント歩数を再設定
			remainingSteps_ = GetRand(ENCOUNT_MAX_STEPS - ENCOUNT_MIN_STEPS) + ENCOUNT_MIN_STEPS;
			accumulatedDistance_ = 0.0f; // 蓄積距離もリセット

			// 戦闘に移行するため、ここで処理を終了
			return;
		}
	}

	//動いた分エンカウントポイントを加算
	countPos_ += nowPos_.x - prePos_.x;
	countPos_ += nowPos_.y - prePos_.y;
	//既定の距離を超えたらエンカウントポイントをリセットし、エンカウント回数を加算
	if (countPos_ > ENCOUNT_RANGE)
	{
		countPos_ = 0.0f;
		count_ = count_ + 1;

		if (ENCOUNT_COUNT == count_)
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BATTLE);
			count_ = 0;
		}
	}

}

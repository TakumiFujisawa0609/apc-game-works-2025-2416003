#include <vector>
#include <list>
#include "../SceneBase.h"
class SceneManager;
class AnimationController;

class BattleScene : public SceneBase
{

public:


	static constexpr int ONE_SECOND = 60;

	static constexpr int CLEAR_ENEMY_COUNT = 2;
	//ポーズ中のBGMボリューム
	static constexpr int PAUSE_SOUND_VOLUME = 50;
	//通常BGMボリューム
	static constexpr int BGM_SOUND_VOLUME = 150;
	//ボリュームゼロ
	static constexpr int BGM_SOUND_VOLUME_ZERO = 0;

	//敵のデフォルト座標
	static constexpr VECTOR DEFAULT_ENEMY_POS = { 0.0f, 45.0f, 0.0f };
	//デフォルトサイズ
	static constexpr VECTOR DEFAULT_ENEMY_SCL = { 0.5f, 0.5f, 0.5f };

	//アニメーション種別
	enum class ANIM_TYPE
	{
		ATTACK,
		DEATH,
		HIT_REACT,
		IDLE,
		JUMP,
		MAX,
	};

	enum class SKILL //プレイヤーから持ってこないといけないんだけど一旦仮で
	{
		SLASH,//斬撃
		FLAME,//炎
		HEAL,//回復
		LIMIT_BREAK,//リミットブレイク
		MAX
	};

	enum class WAVE
	{
		WAVE1,
		WAVE2,
		LASTWAVE,
		END
	};


	//戦闘終了状態
	enum class END
	{
		IN_BATTLE,//戦闘中
		WIN,//勝利
		LOSE,//敗北
		ESCAPE,//逃げる
	};

	enum class END_REWARD
	{
		EXP,//経験値
		ITEM,//アイテム
		MONEY,//お金
		MAX
	};

	//コマンド選択
	enum class COMMAND
	{
		BATTLE, //たたかう
		ESCAPE, //逃げる
		MAX
	};

	enum class STATE
	{
		// 戦闘開始/ターン開始時の準備
		TURN_START,
		// プレイヤーが「たたかう」「アイテム」「にげる」を選ぶ
		COMMAND_SELECT,
		// プレイヤーが「たたかう」を選んだ後にスキルを選んでいる状態
		SKILL_SELECT,
		// プレイヤーの行動処理（スキル実行、アイテム使用など）
		PLAYER_ACTION,
		// 敵の行動処理
		ENEMY_ACTION,
		// ターン終了後の処理や待機
		TURN_END,
		// 戦闘終了（勝利または敗北）
		BATTLE_END,
		// リザルト表示中
		REWARD_VIEW,
	};



	// コンストラクタ
	BattleScene(void);
	// デストラクタ
	~BattleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//コマンド選択
	void ChangeCommand(COMMAND command);
	void CreateBox(int x, int y, int width, int height, int color);
	//ポーズ
	void Pause(void);
	void PauseDraw(void);


private:

	

	
	const char* SkillName;//テスト
	int test = 1;

	std::list<SKILL> selectedSkills_;

	// アニメーション制御
	AnimationController* animationController_;
	// アニメーション種別
	int animType_;

	//コマンド選択
	COMMAND command_;
	//スキル選択
	SKILL skill_;
	//戦闘状態
	STATE state_;
	//敵のwave
	WAVE wave_;
	//背景
	int backImg;

	//ゴブリンモデルハンドル
	int goblinModelId_;
	//ブルーデーモンモデルハンドル
	int blueDemonModellId_;
	//
	int yetiModelId_;

	int cursorIndx_; //選択しているコマンド
	int actionTime_; //処理待機時間
	int endIndx_; // 戦闘終了状態
	int rewordIndx = 0; //戦闘報酬状態
	int turnIndx_; //ターン状態カウント
	int skillIndx_ = 0; //選択しているスキル

	int enemyCount_ = 0;
;

	// ダメージ時の画面揺れ用
	int shakeDuration_ = 0;      // 揺れ継続フレーム数
	int shakeMagnitude_ = 5;

	bool firstcommand_ = true;
	bool isEnd_ = false; //戦闘終了フラグ
	bool isSelectingSkill_ = false;
	bool skipSkillInput_ = false; //
	//ポーズ判定
	bool isPauseAlive_;

	//敵のHP
	int enemyHpMax_ = 50;
	int enemyHp_;

	//プレイヤーのHP
	int playerHp_ = 200;
	int playerHpMax_ = 200;

	bool playerDead_ = false;

	int currentHp;
	int maxHp;

	// ダメージ量を格納する変数(攻撃時）
	int damageAmount = 0;

	bool isDamege_ = false;

	void BattleInit(void);

	//スキル選択関連
	void SelectSkill(SKILL skill);
	void UseSkill(void);
	void ProcessSkill(SKILL skill);

	//攻撃系
	void Damage(void);
	void Hell(void);
	void Flame(void);

	//敵の処理系
	void EnemyAttack(void);

	void DrawCommand(COMMAND command);
	void DrawEnd(END end);
	void DrawReword(END_REWARD endreward);

	void DrawSkill(void);
	void DrawStates(STATE state);

	void HandleCommandSelectInput(void);
	void ExecuteCommand(COMMAND command);
	void HandleSkillSelectInput(void);

	void DrawHpBar(int x, int y, int width, int height, int currentHp, int maxHp);

	unsigned int GetHPColor(float rate);
	//waveの管理
	void StartWave(WAVE wave);
	//waveごとの敵の描画
	void WaveDraw(WAVE wave);
	
};

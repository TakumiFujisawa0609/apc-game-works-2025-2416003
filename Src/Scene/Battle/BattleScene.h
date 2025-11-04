#include <vector>
#include <list>
#include "../SceneBase.h"
class SceneManager;
class EnemyBase;
class EnemyManager;

class BattleScene : public SceneBase
{

public:


	static constexpr int ONE_SECOND = 60;

	static constexpr int CLEAR_ENEMY_COUNT = 2;

	enum class SKILL //プレイヤーから持ってこないといけないんだけど一旦仮で
	{
		SLASH,//斬撃
		PROTECT,//防御
		HEAL,//回復
		POISON,//毒
		LIMIT_BREAK,//リミットブレイク

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
		//SKILL,//スキル
		TOOl, //道具
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

	void Pause(void);
	void PauseDraw(void);


private:

	std::list<SKILL> selectedSkills_;

	EnemyBase* enemyBase_;
	EnemyManager* enemyManager_;

	//コマンド選択
	COMMAND command_;

	//スキル選択
	SKILL skill_;
	
	STATE state_;

	int cursorIndx_; //選択しているコマンド
	int actionTime_; //処理待機時間
	int endIndx_; // 戦闘終了状態
	int rewordIndx = 0; //戦闘報酬状態
	int turnIndx_; //ターン状態カウント
	int skillIndx_ = 0; //選択しているスキル

	int enemyCount_ = 0;
;

	bool firstcommand_ = true;
	bool isEnd_ = false; //戦闘終了フラグ
	bool isSelectingSkill_ = false;
	bool skipSkillInput_ = false; //
	//ポーズ判定
	bool isPauseAlive_;


	//αの仮攻撃
	int enemyHp_;
	// ダメージ量を格納する変数
	int damageAmount = 0;

	bool isDamege_ = false;

	void BattleInit(void);

	//スキル選択関連
	void SelectSkill(SKILL skill);
	void UseSkill(void);
	void ProcessSkill(SKILL skill);

	void Damage(void);

	void DrawCommand(COMMAND command);
	void DrawEnd(END end);
	void DrawReword(END_REWARD endreward);

	void DrawSkill(void);
	void DrawState(STATE state);

	void HandleCommandSelectInput(void);
	void ExecuteCommand(COMMAND command);
	void HandleSkillSelectInput(void);
};

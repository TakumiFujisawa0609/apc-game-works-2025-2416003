
#include "SceneBase.h"
class SceneManager;
class EnemyBase;

class BattleScene : public SceneBase
{

public:

	//ターン状態
	enum class TURN
	{
		TURN_START,//ターン開始
		SELECT,//コマンドの選択
		PLAYER,//プレイヤーのターン
		PLAYER_ACTION,//コマンドの実行
		ENEMY,//敵のターン
		ENEMY_ACTION,//コマンドの実行
		TURN_END,//ターン終了
		MAX
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
	};

	//コマンド選択
	enum class COMMAND
	{
		BATTLE, //たたかう
		TOOl, //道具
		ESCAPE, //逃げる
		MAX
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
	void ChangeTurn(TURN turn);

	void CreateBox(int x, int y, int width, int height, int color);


private:

	EnemyBase* enemy_;

	//コマンド選択
	COMMAND command_;


	//ターン状態
	TURN turn_;

	int cursorIndx_; //選択しているコマンド
	int actionTime_; //処理待機時間
	int endIndx_; // 戦闘終了状態
	int rewordIndx = 0; //戦闘報酬状態
	 
	int turnIndx_; //ターン状態カウント

	bool firstcommand_ = true;
	bool isEnd_ = false; //戦闘終了フラグ

	//αの仮攻撃
	int enemyHp_ = 10;
	int damege_ = 10;

	bool isDamege_ = false;

	void Damage(void);
	void DrawTurn(TURN turn);
	void DrawCommand(COMMAND command);
	void DrawEnd(END end);
	void DrawReword(END_REWARD endreward);

};

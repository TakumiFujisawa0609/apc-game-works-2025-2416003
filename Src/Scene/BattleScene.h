
#include "SceneBase.h"
class SceneManager;

class BattleScene : public SceneBase
{

public:


	//コマンド選択
	enum class COMMAND
	{
		BATTLE, //たたかう
		TOOl, //道具
		ESCAPE, //逃げる
		MAX
	};

	//コマンド状態
	enum class STATE
	{
		SELECT,//コマンドの選択
		ACTION,//コマンド
		END//コマンド終了
	};

	//ターン状態
	enum class TURN
	{
		PLAYER,//プレイヤーのターン
		ENEMY,//敵のターン
		TURN_END//ターン終了
	};
	// コンストラクタ
	BattleScene(void);

	// デストラクタ
	~BattleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void ChangeCommand(COMMAND command);

	void ChagneState(STATE next);

	void CreateBox(int x, int y, int width, int height, int color);


private:

	//コマンド選択
	COMMAND command_;

	//コマンド状態
	STATE state_;

	//ターン状態
	TURN turn_;

	int cursorIndx_; //選択しているコマンド
	int actionTime_; //処理待機時間

	bool textFlag_ = true;


};

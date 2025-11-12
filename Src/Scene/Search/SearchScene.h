#include "../SceneBase.h"
class SceneManager;
class Grid;
class MapPlayer;

class SearchScene : public SceneBase
{

public:

	//ポーズ画面
	enum class STATE
	{
		GAME,
		EXIT,
		MAX
	};

	// 選択肢の描画座標（仮定）
	static const int RETUTN_GAME_POS_Y = 350;
	static const int EXIT_POS_Y = 450;



	// 選択中のカーソル文字（DxLibの描画を想定）
	const char* CURSOR_CHAR = "→ ";

	// コンストラクタ
	SearchScene(void);

	// デストラクタ
	~SearchScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void Pause(void);
	void PauseDraw(void);

private:

	static constexpr int BGM_SOUND_VOLUME = 150;
	static constexpr int BGM_SOUND_VOLUME_ZERO = 0;


	static constexpr float ENCOUNT_RANGE = 100.0f;
	//最大エンカウント回数
	static constexpr int  ENCOUNT_COUNT = 5;

	//距離の単位
	static constexpr float STEP_DISTANCE = 1.0f;
	// 次のエンカウントまでの歩数初期値
	static constexpr int  ENCOUNT_MAX_STEPS = 600;
	static constexpr int  ENCOUNT_MIN_STEPS = 50;

	//ステージハンドル
	int stageId_;
	//ポーズフラグ
	bool isPauseAlive_ ;

	bool isEnd_ = false;

	int cursorIndx_ = 0; //選択しているコマンド

	float countPos_ = 0.0f;
	int count_ = 0;
	float accumulatedDistance_ = 0.0f; // 実際に歩いた距離の累計
	int remainingSteps_ = 0;          // 次のエンカウントまでの残り歩数

	Grid* grid_;
	MapPlayer* player_;
	STATE state_;


	//現在の座標
	VECTOR nowPos_;
	//前回の座標
	VECTOR prePos_;


	void ChangeExit(void);
	void ChangeGame(void);

	void ChagneState(STATE next);
	void DrawCommand();

	void EnCount(void);
};

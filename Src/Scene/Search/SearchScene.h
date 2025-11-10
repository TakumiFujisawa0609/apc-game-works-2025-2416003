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

	//ステージハンドル
	int stageId_;
	//ポーズフラグ
	bool isPauseAlive_ ;

	bool isEnd_ = false;

	int cursorIndx_ = 0; //選択しているコマンド

	Grid* grid_;
	MapPlayer* player_;
	STATE state_;


	void ChangeExit(void);
	void ChangeGame(void);

	void ChagneState(STATE next);
	void DrawCommand();
};

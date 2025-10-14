#pragma once
#include "SceneBase.h"
#define TITLE_SE_PATH "Data/Sound/TitleSe.wav"

class SceneManager;

class TitleScene : public SceneBase
{

public:

	static constexpr int BGM1_VOLUME = 150;		// BGMの音量

	// 選択肢の描画座標（仮定）
	static const int GAME_POS_Y = 350;
	static const int EXIT_POS_Y = 450;
	// 選択中のカーソル文字（DxLibの描画を想定）
	const char* CURSOR_CHAR = ">> ";

	enum class STATE
	{
		GAME,
		EXIT,
		MAX
	};

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void ChangeExit(void);
	void ChangeGame(void);

	void ChagneState(STATE next);
	void DrawCommand(STATE next);

	void TitleSE(void);
	

private:

	

	STATE state_;

	bool isEnd_ = false;

	// 画像
	int imgTitle_;
	int cursorIndx_ = 0; //選択しているコマンド

	int titleHundle_;
};

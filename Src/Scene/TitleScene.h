#pragma once
#include "SceneBase.h"
class SceneManager;

class TitleScene : public SceneBase
{

public:

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

private:


	STATE state_;

	bool isEnd_ = false;

	// 画像
	int imgTitle_;
	int cursorIndx_ = 0; //選択しているコマンド

	
};

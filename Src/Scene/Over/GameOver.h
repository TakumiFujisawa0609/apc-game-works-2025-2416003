#pragma once
#include "../SceneBase.h"
class SceneManager;
class Grid;
class Camera;

class GameOver : public SceneBase
{

public:



	// コンストラクタ
	GameOver(void);

	// デストラクタ
	~GameOver(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void ChangeTitle(void);

private:

	int stageId_;

	int gameOverImg_;
	int pushImg_;

	Grid* grid_;
	Camera* camera_;
};

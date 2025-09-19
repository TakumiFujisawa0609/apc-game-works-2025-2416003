#pragma once
#include "SceneBase.h"
class SceneManager;

class TitleScene : public SceneBase
{

public:

	enum class TITLE
	{
		GAME,
		EXIT,
	};

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;



private:

	TITLE title_;

	// 画像
	int imgTitle_;

};


#include "SceneBase.h"
class SceneManager;
class Grid;
class Camera;


class GameScene : public SceneBase
{


public:

	enum class PLAYSCENE
	{
		PREPARATION,
		SEARCH,
		BATTLE,
	};


	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void ChangeScene(PLAYSCENE playscene);

	void ChangePretaration(void);
	void ChangeSearch(void);
	void ChangeBattle(void);



private:

	Grid* grid_;
	Camera* camera_;

	// 画像
	int imgTitle_;

	VECTOR testPos;

	PLAYSCENE playscene_;
};


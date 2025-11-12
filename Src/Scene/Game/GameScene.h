#include "../SceneBase.h"

class SceneManager;
class Grid;
class Camera;

class GameScene : public SceneBase
{


public:


	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	



private:

	Grid* grid_;
	Camera* camera_;

	// 画像
	int imgTitle_;

	VECTOR testPos;

};


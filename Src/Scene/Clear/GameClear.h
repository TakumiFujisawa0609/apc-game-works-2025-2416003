#include "../SceneBase.h"
class SceneManager;
class Grid;
class Camera;

class GameClear : public SceneBase
{

public:



	// コンストラクタ
	GameClear(void);

	// デストラクタ
	~GameClear(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void ChangeTitle(void);

private:

	int stageId_;

	Grid* grid_;
	Camera* camera_;
};

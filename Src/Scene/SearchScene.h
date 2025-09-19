#include "SceneBase.h"
class SceneManager;
class Grid;
class Camera;

class SearchScene : public SceneBase
{

public:



	// コンストラクタ
	SearchScene(void);

	// デストラクタ
	~SearchScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	Grid* grid_;
	Camera* camera_;
};

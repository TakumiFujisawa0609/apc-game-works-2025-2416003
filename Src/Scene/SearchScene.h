#include "SceneBase.h"
class SceneManager;
class Grid;
class MapPlayer;

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

	int stageId_;

	Grid* grid_;
	MapPlayer* player_;
};

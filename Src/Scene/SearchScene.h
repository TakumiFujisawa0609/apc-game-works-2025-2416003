#include "SceneBase.h"
class SceneManager;

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

};

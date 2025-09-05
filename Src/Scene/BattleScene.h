
#include "SceneBase.h"
class SceneManager;

class BattleScene : public SceneBase
{

public:

	// コンストラクタ
	BattleScene(void);

	// デストラクタ
	~BattleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

};

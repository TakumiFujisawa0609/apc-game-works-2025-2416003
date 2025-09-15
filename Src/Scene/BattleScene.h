
#include "SceneBase.h"
class SceneManager;

class BattleScene : public SceneBase
{

public:


	//コマンド選択
	enum class COMMAND
	{
		BATTLE, //たたかう
		TOOl, //道具
		ESCAPE, //逃げる
	};

	// コンストラクタ
	BattleScene(void);

	// デストラクタ
	~BattleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void ChangeCommand(COMMAND command);


private:


	COMMAND command_;
};

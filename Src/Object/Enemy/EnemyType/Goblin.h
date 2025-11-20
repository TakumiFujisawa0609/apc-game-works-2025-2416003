#pragma once
#include "../EnemyBase.h"
class AnimatarionController;

class Goblin : public EnemyBase

{
public:

	Goblin(void);
	~Goblin(void);

	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

protected://継承する際に必要な情報

	//リソースロード
	void InitLoad(void)override;
	//大きさ、回転、座標設定
	void InitTransform(void)override;
	//アニメーション初期化
	void InitAnimation(void)override;
	//初期化後の個別処理
	void InitPost(void)override;
	//ステータス入力
	void SetParam()override;


private:

};


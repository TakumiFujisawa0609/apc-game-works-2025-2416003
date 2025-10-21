
#pragma once
#include <DxLib.h>
#include "SkillBase.h"
class LimitBreak : public SkillBase
{
public:
	static constexpr float LIMITBREAK_MAGNIFICATION = 200;

	//コンストラクタ
	LimitBreak(void);
	//デストラクタ
	~LimitBreak(void);


	// 更新
	void Update(void) override;
	// 描画
	void Draw(void) override;
	void Release(void) override;


protected:
	//初期化
	void  InitLoad(void)override;
	//初期化
	void SetParam(void)override;
	//スキル行動処理
	void  SkillProcess(int atk, int def, int intel)override;
	//攻撃スキルの場合のダメージ処理
	virtual void Damege(int hp, int dmg, int def)override;
private:


};


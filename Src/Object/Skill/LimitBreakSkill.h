#pragma once
#include <DxLib.h>
#include "SkillBase.h"
class LimitBreakSkill : public SkillBase
{
public:

	//スキル固定倍率
	static constexpr float SLASH_MAGNIFICATION = 3.0f;

	// コンストラクタ（スキルの基本情報を設定）
	LimitBreakSkill() { SetParam(); }


	// 更新
	void Update(void) override;
	// 描画
	void Draw(void) override;
	void Release(void) override;


protected:
	//初期化
	virtual void  InitLoad(void)override;
	//初期化
	virtual void SetParam(void)override;
	//スキル処理

private:


};



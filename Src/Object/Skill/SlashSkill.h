#pragma once
#include <DxLib.h>
#include "SkillBase.h"
class SlashSkill : public SkillBase
{
public:
	static constexpr float SLASH_MAGNIFICATION = 1.1f;

	// コンストラクタ（スキルの基本情報を設定）
	SlashSkill() { SetParam(); }


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
	
	
private:


};


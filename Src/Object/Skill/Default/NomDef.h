#pragma once
#include <DxLib.h>
#include "../SkillBase.h"

class NomDef : public SkillBase
{
public:
	// コンストラクタ
	NomDef(void);
	// デストラクタ
	~NomDef(void);

	// デバッグ用描画
	void Draw(void) override;
	// 解放
	void Release(void) override;

protected:

	//モデル等の読み込み
	void Load(void) override;
	//スキルパラメータの設定
	void SetParam(void) override;

private:
};


#pragma once
#include <DxLib.h>
#include "SkillBase.h"
class Slash : public SkillBase
{
public:
	static constexpr float SLASH_MAGNIFICATION = 1.1f;

	//コンストラクタ
	Slash(void);
	//デストラクタ
	~Slash(void);


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


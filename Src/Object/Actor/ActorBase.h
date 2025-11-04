#pragma once
#include <string>
#include <DxLib.h>

class SkillManager;
class AnimationController;

class ActorBase
{
public:

	void Init(void);		// 初期化
	virtual void Update(void);		// 更新
	virtual void Draw(void);		// 描画
	virtual void Release(void); 	// 解放
	
	void SlashAttack(int atkPower, int defPower, int hp);//スラッシュ攻撃
protected://派生クラスから持ってくる情報
	

	

	void StatusLoadData(void);//ステータスデータ読み込み


private:



};
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


	/// @brief HP情報
	/// @return HP
	virtual int SetHp();
	/// @brief 最大HP情報
	/// @return 最大HP
	virtual int SetMaxHp();
	/// @brief MP情報
	/// @return MP
	virtual int SetMp();
	/// @brief 最大MP情報
	/// @return 最大MP
	virtual int SetMaxMp();
	/// @brief ATK情報
	/// @return ATK
	virtual int SetAtk();
	/// @brief DEF情報
	/// @return DEF
	virtual int SetDef();
	/// @brief WIS情報
	/// @return WIS
	virtual int SetWis();

	/// @brief HP増加処理
	/// @param addHp 回復する量（魔法）
	/// @param hp 使用される体力
	int  addHp(float skillPow,int attckerWis , int attckerHp,int attckerMaxHp);

	/// @brief  MP消費処理
	/// @param costMp 消費するMP
	/// @param mp 使用する人のMP残量(attkerで統一）
	int costMp(int costMp, int mp);//MP消費処理

	/// @brief 
	/// @param addMp 
	/// @param targetMp 
	/// @param targetMaxMp 
	/// @return 
	int addMp(int addMp, int targetMp ,int targetMaxMp);

	/// @brief 物理攻撃処理
	/// @param skillPow スキル倍率
	/// @param attkerAtkPow	スキル攻撃力
	/// @param targetDefPow	防御力
	/// @param hp		ダメージ処理後HP
	int PhysicsDamage(float skillPow,int attckerAtk,int targetDef,int targetHp);
	/// @brief 魔法攻撃処理
	/// @param skillPow スキルの攻撃力
	/// @param tatgetWisPoe ダメージを受ける側のかしこさ（知恵）
	/// @param attckerWis 攻撃側のかしこさ
	/// @param hp 体力
	/// @return ダメージ処理後HP
	int MagicDamage(float skillPow,int attckerWis, int targetWis,int targetHp);

	
	


protected://派生クラスから持ってくる情報
	
	

	int hp_;
	int mp_;
	int maxHp_;
	int maxMp_;

	int atk_;
	int def_;
	int wis_;

	virtual void SetParam(void) = 0;

private:



};
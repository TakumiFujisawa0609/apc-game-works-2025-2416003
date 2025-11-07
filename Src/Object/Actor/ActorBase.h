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
	int SetHp();
	/// @brief 最大HP情報
	/// @return 最大HP
	int SetMaxHp();
	/// @brief MP情報
	/// @return MP
	int SetMp();
	/// @brief 最大MP情報
	/// @return 最大MP
	int SetMaxMp();
	/// @brief ATK情報
	/// @return ATK
	int SetAtk();
	/// @brief DEF情報
	/// @return DEF
	int SetDef();
	/// @brief WIS情報
	/// @return WIS
	int SetWis();
	

	/// @brief HP増加処理
	/// @param addHp 回復する量（魔法、アイテム等）
	/// @param hp 使用される体力
	int  addHp(int addHp, int targetHp);

	/// @brief  MP消費処理
	/// @param costMp 消費するMP
	/// @param mp 使用する人のMP残量
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
	

private:



};
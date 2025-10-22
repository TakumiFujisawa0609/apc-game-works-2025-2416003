#pragma once
#include<string>
#include <DxLib.h>
class ActorSkill
{
public:

	ActorSkill(const std::string& name, int hp, int atk, int def, int intel);

	int getHp() const { return hp_; }
    // 攻撃力を取得
    int getAtk() const { return atk_; }
    // 防御力を取得
    int getDef() const { return def_; }
    //名前取得
    std::string getName() const { return name_; }

    // HPを変更する ステータスの数値が変化する
    void takeDamage(int damage) { hp_ -= damage; if (hp_ < 0) hp_ = 0; }
    //void heal(int amount) { hp_ += amount; /* 最大HPの制限などは省略 */ }

private:

    std::string name_;
    int hp_;
    int atk_;
    int def_;
    int intel_;
};
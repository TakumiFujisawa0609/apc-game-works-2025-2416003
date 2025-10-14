#pragma once
#include "../Enemy/EnemyBase.h"


class  BattleEnemy
{
public:
    // コンストラクタ、デストラクタ
    BattleEnemy();
    ~BattleEnemy();

    // 唯一の初期化メソッド。設計図（EnemyData）を受け取る。
    // ※EnemyData構造体とInitの引数は、以前の回答で推奨した形を想定
    void Init();

    // メインループから呼ばれる処理
    void Update();
    void Draw();

    // 戦闘ロジック関連のメソッド
    void TakeDamage(int damage);        // ダメージを受ける処理
    bool IsDead() const { return currentHp_ <= 0; } // 死亡判定

    // (必要に応じて) 行動を決定するAIメソッド
    // BattleSceneから呼ばれる
    void DecidAction();

private:
    
    int currentHp_ = 0;       // 現在のHP (ダメージで減る)
    int maxHp_ = 0;           // 最大HP
    int attackPower_ = 0;     // 攻撃力
    int defense_ = 0;         // 防御力

    // 敵の種類
    EnemyBase::TYPE type_;

    // モデル、アニメーション関連
    int modelId_ = -1;
    // AnimationController* animController_;

    // その他
    int experienceValue_ = 0; // 撃破時に得られる経験値
};


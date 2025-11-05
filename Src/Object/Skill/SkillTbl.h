#pragma once

#include <string>

// スキルの種別
//(ここに追加していくスキルを入れていく）
enum SKILL_KIND
{
	NON,			// なし

	// 魔法スキル
	FIRE,			// 炎
	THUNDER,		// 雷
	ICE,			// 氷

	// 物理スキル
	SLASH,			// スラッシュ
	LIMIT_BREAK,	// リミットブレイク	

	MAX,
};

//スキル種別（ピースの色を識別する時にも利用する）
enum class SKILL_TYPE
{
	NON,		// なし
	ATTACK,		// 攻撃
	DEFENSE,	// 防御
	HEAL,		// 回復
	BUFF,		// バフ
	DEBUFF,		// デバフ
};

// スキルのパラメータ
struct SkillData
{
	SKILL_KIND id;		// スキルID
	SKILL_TYPE type;	// スキルタイプ
	std::string name;	// 名前 (文字列)
	float power;			// 威力
	int mp;				// 消費MP
};

// ↓csv等で外部ファイルから受け取れるようにする。
// スキルテーブル（配列）
const SkillData skillTable[] =
{
	// スキルID					// スキルタイプ 		// スキル名				// 威力倍率		// 消費MP
	{ SKILL_KIND::NON			,SKILL_TYPE::NON		, "なし"				, 0.0f			, 0		},
	{ SKILL_KIND::FIRE			,SKILL_TYPE::ATTACK		, "ファイア"			, 1.2f			, 3		},
	{ SKILL_KIND::THUNDER		,SKILL_TYPE::ATTACK		, "サンダー"			, 1.2f			, 3		},
	{ SKILL_KIND::ICE			,SKILL_TYPE::ATTACK		, "ブリザド"			, 1.2f			, 3		},
	{ SKILL_KIND::SLASH			,SKILL_TYPE::ATTACK		, "スラッシュ"			, 1.5f			, 10	},
	{ SKILL_KIND::LIMIT_BREAK	,SKILL_TYPE::ATTACK		, "リミットブレイク"	, 3.0f			, 15	},
};

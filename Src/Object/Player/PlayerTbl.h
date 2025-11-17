#pragma once

#include <string>

// レベル	
//(ここに追加していくスキルを入れていく）
enum PLAYER_LEVEL
{
	NON,			// なし

	ONE,
	
	MAX,
};


// スキルのパラメータ
struct PlayerData
{
	PLAYER_LEVEL level; //レベル
	std::string  levelName;//レベル表示
	//ステータス
	int hp;				// HP
	int maxHp;			// 最大HP
	int mp;				// MP
	int maxMp;			// 最大MP
	int atk;			// 攻撃力
	int def;			// 防御力
	int wis;
};

// ↓csv等で外部ファイルから受け取れるようにする。
// プレイヤーレベルテーブル（配列）
const PlayerData PlayerStatusTable[] =
{
	// プレイヤーレベル		//レベル	//HP	//MAXHP		//MP	//MAXMP		//ATK	//DEF	//WIS
	{ PLAYER_LEVEL::ONE	,	"Lv .1",	100,	100,		100,	100,		10		,10		,10},

};


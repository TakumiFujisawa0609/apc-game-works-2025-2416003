#pragma once
#include <string>
#include <unordered_map>

// サウンドID
enum class SoundID
{

	BGM_TITLE,		//タイトルBGM
	BGM,
	BGM_BATTLE,		//バトルBGM
	BGM_SEARCH,		//サーチシーンBGM
	BGM_BOSS,
	SE_BUTTON,		//ボタンSE
	SE_RUN,			//走り状態SE
	SE_ATTACK,		
	SE_COMMAND_SELECT,		//コマンド選択SE
	SE_COMMAND_DECISION,	//コマンド決定SE
	SE_TITLE_DECISION,		//タイトルコマンド決定SE
	SE_TITLE_COMMAND,
	SE_ENCOUNT,				//エンカウントSE
	SE_WIN,					//勝利SE
	SE_LOSE,
	SKILL_SE_SLASH,			//スラッシュSE
	SKILL_SE_HELL,			//ヒールSE
	SKILL_SE_FIRE,
	SE_DAMEGE,
	MAX

};

// 読み込むシーン
enum class LoadScene
{
	SYSTEM,		// システム
	TITLE,		// タイトル
	GAME,		// ゲーム
	SKILL,
};

// サウンド属性
struct SoundData
{
	std::string path;	// サウンドのパス
};

// サウンドテーブル（名称被りや拡張性の為にクラス化)
class SoundTable
{
public:
	// サウンドテーブルのマップ
	// サウンドID から サウンドパスを取得
	static const std::unordered_map<SoundID, SoundData> Table;
};

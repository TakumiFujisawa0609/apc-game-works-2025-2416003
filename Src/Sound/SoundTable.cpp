#include "SoundTable.h"
#include "../Application.h"

// サウンドID から サウンドパスを取得

// システム用
namespace SoundTable_System 
{
	static const std::unordered_map<SoundID, std::string> Table = 
	{
		{ SoundID::BGM_TITLE, "Data/Sound/BGM/system.mp3" },
		{ SoundID::SE_BUTTON, "Data/Sound/SE/system.mp3" },
	};
}

// タイトル画面用
namespace SoundTable_Title
{
	static const std::unordered_map<SoundID, std::string> Table =
	{
		{ SoundID::BGM_TITLE, Application::PATH_SOUND_BGM + "GameBgm.wav" },
		{ SoundID::BGM, Application::PATH_SOUND_BGM + "TitleBgm.wav" },
		{ SoundID::BGM_GAMEOVER, Application::PATH_SOUND_BGM + "Over_BGM.wav" },
		{ SoundID::SE_TITLE_DECISION, Application::PATH_SOUND_SE + "Title_Decision.wav" },
		{ SoundID::SE_TITLE_DECISION, Application::PATH_SOUND_SE + "Title_Decision.wav" },
		{ SoundID::SE_TITLE_COMMAND, Application::PATH_SOUND_SE + "Command_Select.wav" },

	};
}

// ゲーム画面用
namespace SoundTable_Game 
{
	static const std::unordered_map<SoundID, std::string> Table = 
	{
		{ SoundID::BGM_BATTLE, Application::PATH_SOUND_BGM + "GameBgm.wav" },
		{ SoundID::SE_GAMEOVER, Application::PATH_SOUND_SE + "GameOver.wav" },
		{ SoundID::SE_COMMAND_SELECT,	Application::PATH_SOUND_SE + "Select.wav" },
		{ SoundID::SE_COMMAND_DECISION, Application::PATH_SOUND_SE + "Command_Decision.wav" },
		{ SoundID::SE_ENCOUNT, Application::PATH_SOUND_SE + "EnCount.wav" },
		{ SoundID::SE_WIN, Application::PATH_SOUND_SE + "Battle_Win.wav" },
		{ SoundID::SKILL_SE_SLASH, Application::PATH_SOUND_SE + "Slash_Se.wav" },
		{ SoundID::SE_DAMEGE, Application::PATH_SOUND_SE + "Damage.wav" },
		{ SoundID::SKILL_SE_HELL,	Application::PATH_SOUND_SE + "Hell_Se.wav" },
		{ SoundID::SKILL_SE_FIRE,	Application::PATH_SOUND_SE + "Flame_Se.wav" },
		{ SoundID::BGM_BOSS,	Application::PATH_SOUND_BGM + "Boss.wav" },
		{ SoundID::SE_LOSE,	Application::PATH_SOUND_SE + "Flame_Se.wav" },
		
	};
}

// システム用
namespace SoundTable_Skill
{
	static const std::unordered_map<SoundID, std::string> Table =
	{

		
	};
}

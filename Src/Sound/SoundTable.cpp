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
		{ SoundID::BGM_TITLE, Application::PATH_SOUND_SE + "TitleBgm.wav" },
		{ SoundID::SE_TITLE_DECISION, Application::PATH_SOUND_SE + "Title_Decision.wav" },
	};
}

// ゲーム画面用
namespace SoundTable_Game 
{
	static const std::unordered_map<SoundID, std::string> Table = 
	{
		{ SoundID::BGM_BATTLE, Application::PATH_SOUND_BGM + "GameBgm.wav" },
		{ SoundID::BGM_SEARCH, Application::PATH_SOUND_BGM + "SearchScene.wav" },
		{ SoundID::SE_COMMAND_SELECT,	Application::PATH_SOUND_SE + "Command_Select.wav" },
		{ SoundID::SE_COMMAND_DECISION, Application::PATH_SOUND_SE + "Command_Decision.wav" },

		
	};
}

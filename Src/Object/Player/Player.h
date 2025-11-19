#pragma once
#include <map>

#include "../Status/StatusTbl.h"
class SkillManager;

class Player
{
public:

	void Init(void);			// 初期化
	void Update(void) ;			// 更新
	void Draw(void) ;			// 描画
	void Release(void) ;		// 解放

	

	
private:

	SkillManager* skillManager_;
	
	StatusData status;
	//ステータス入力
	void SetStatus();
	
};


#pragma once
#include <map>
#include "../../Actor/ActorBase.h"

class SkillManager;

class TestGoblin: public ActorBase
{
public:

	void Init(void);					// ‰Šú‰»
	void Update(void) override;			// XV
	void Draw(void) override;			// •`‰æ
	void Release(void) override;		// ‰ğ•ú


protected:

	int hp_ = 50;
	int mp_ = 100;
	int maxHp_ = 50;
	int maxMp_ = 100;

	int atk_ = 30;
	int def_ = 10;
	int wis_ = 5;



private:
	SkillManager* skillManager_;


};


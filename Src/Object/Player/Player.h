#pragma once
#include <list>
#include <map>
#include "../Actor/ActorBase.h"
class SkillManager;

class Player : public ActorBase
{
public:

	void Init(void);					// ‰Šú‰»
	void Update(void) override;			// XV
	void Draw(void) override;			// •`‰æ
	void Release(void) override;		// ‰ğ•ú


	
	
private:
	SkillManager* skillManager_;

	
};


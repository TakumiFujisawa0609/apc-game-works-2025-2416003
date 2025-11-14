#pragma once
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


protected:

	void SetParam(void) override;


	
private:
	SkillManager* skillManager_;

	
};


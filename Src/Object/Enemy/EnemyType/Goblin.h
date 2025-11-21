#pragma once
#include "../../Status/StatusTbl.h"
class AnimatarionController;

class Goblin

{
public:

	Goblin(void);
	~Goblin(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos();

private:
	//デフォルトの座標
	static constexpr VECTOR DEFAULT_ENEMY_POS = { 0.0f, 50.0f, -520.0f };

	int modelId;//モデルハンドル

	VECTOR pos_;
	VECTOR angles_;
	VECTOR scl_;
	VECTOR localAngles_;

	//ステータス
	StatusData status;

	void SetParam(void);


};








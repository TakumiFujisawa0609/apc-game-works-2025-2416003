#pragma once
class AnimatarionController;
#include "../../Status/StatusTbl.h"
class BlueDemon

{
public:

	BlueDemon(void);
	~BlueDemon(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

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




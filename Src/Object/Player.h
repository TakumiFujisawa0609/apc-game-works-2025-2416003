#pragma once
class Player
{
public:

	void Init(void);
	// 更新
	void Update(void);
	// デバッグ用描画
	void Draw(void);
	// 解放
	void Release(void);
	
private:

	int hp_;
	int exp_;
	int level_;
	int attack_;
	int defense_;
	int speed_;

};


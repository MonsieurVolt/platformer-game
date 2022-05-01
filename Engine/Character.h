#pragma once
#include "Animation.h"
class Character
{
public:
	enum class Movements {
		Run,
		Stand,
		End
	};
	Character(VecF2& pos);
	void SetDirection(VecF2& dir,int X);
	void Draw(Graphics& gfx)const ;
	void Update(VecF2& dir,float dt);
	VecF2 GetNextPos(VecF2& dir, float dt) const;
	VecF2 GetPos() const;
	bool IsJumping() const;
	float GetTimeJump() const;
	void SetJump(bool j);
private:
	Surface sprite = Surface("good_one.bmp");
	std::vector<Animation> moves;
	 Movements iCurMove = Movements::Stand;
	 VecF2 pos;
	 static float constexpr speed = 200.0f;
	 VecF2 vel = { 0.0f,0.0f };
	 float timeJump = 0;
	 bool isJumping = false;

};


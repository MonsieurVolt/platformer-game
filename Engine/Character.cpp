#include "Character.h"

Character::Character(VecF2& pos):pos(pos)
{
	moves.push_back(Animation(0, 0, 64, 64, 4, sprite));
	moves.push_back(Animation(0, 64, 64, 64, 1, sprite));

}
void Character::SetDirection(VecF2& d,int X) {
	auto dir = VecF2(d.x + X,d.y);
	if (dir.x > 0) {
		iCurMove = Movements::Run;
	}
	else if (dir.x < 0) {
		iCurMove = Movements::Run;

	}
	else if (dir.y > 0) {
		iCurMove = Movements::Stand;
	}
	else if (dir.y < 0) {
		iCurMove = Movements::Stand;
	}
	else {
		iCurMove = Movements::Stand;
	}
}

void Character::Draw(Graphics& gfx) const
{
	moves[(int)iCurMove].Draw(pos, gfx);
}
void Character::Update(VecF2& dir, float dt) {
	if (isJumping) {
		timeJump += dt;
		if (timeJump > 0.3f) {
			isJumping = false;
			timeJump = 0;
		}
	}
	pos += dir;
	moves[(int)iCurMove].UpdateFrames(dt);
}

VecF2 Character::GetNextPos(VecF2& dir,float dt) const 
{
	return pos + dir * speed * dt;
}

VecF2 Character::GetPos() const
{
	return pos;
}

bool Character::IsJumping() const
{
	return isJumping;
}

float Character::GetTimeJump() const
{
	return timeJump;
}

void Character::SetJump(bool j)
{
	isJumping = j;
}

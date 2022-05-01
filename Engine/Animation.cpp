#include "Animation.h"
#include <iostream>
#include <sstream>
Animation::Animation(int x, int y, int width, int height, int nb, const Surface& s): surface(s) 
{
	for (int i = 0; i < nb; i++) {

		frames.emplace_back(RectI{ y,y + height,x + i*width,x + (i+1)*width });
	}
}

void Animation::Draw(const VecF2& pos,Graphics& gfx) const
{
	
	gfx.DrawSprite(pos.x,pos.y, frames[iCurFrame], surface);
}

void Animation::UpdateFrames(float dt)
{
	time += dt;
	while (time >= holdTime) {
		time -= holdTime;
		Advance();
	}
}

void Animation::Advance()
{
	if (++iCurFrame >= frames.size()) {
		
		iCurFrame = 0;
	}
}

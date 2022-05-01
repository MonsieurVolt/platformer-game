#pragma once
#include "Surface.h"
#include "Graphics.h"
#include <vector>


class Animation
{
public:
	Animation(int x, int y, int width, int height, int nb, const Surface& s);
	void Draw(const VecF2& pos,Graphics& gfx) const ;
	void UpdateFrames(float dt);
	void Advance();
	
private:
	int iCurFrame = 0;
	std::vector<RectI> frames;
	const Surface& surface;
	float time = 0;
	float holdTime = 0.16f;

};
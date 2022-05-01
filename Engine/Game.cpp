/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"


Game::Game(MainWindow& wnd)
    :
    wnd(wnd),
    gfx(wnd),
    map("blocks24.bmp", "map.txt", RectI{ 0,64,0,64 }),
    background("cloud (1).bmp", "background.txt", RectI{ 0,64,0,64 }),
    mario( VecF2(200.0f, 100.0f) )

{

}

void Game::Go()
{
    gfx.BeginFrame();
    float elapsedTime = ft.Mark();
    while (elapsedTime > 0.0f) {
        const float dt = std::min(0.05f, elapsedTime);
        UpdateModel(dt);
        elapsedTime -= dt;
    }

    ComposeFrame();
    gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
    
    VecF2 dir = { 0.0f,3.0f };
    if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
        dir.x += 1.0f;
    }
    if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
        dir.x -= 1.0f;

    }

    if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
        if (!mario.IsJumping())
        mario.SetJump(true);

    }
    if (mario.IsJumping()) {
        dir.y = -(0.3 - mario.GetTimeJump()) * 10.0f;
    }


    dir = mario.GetNextPos(dir, dt) - mario.GetPos();
    RectF persoPos = RectF(mario.GetPos(), 64, 64);
    map.HandleCharacter(persoPos, dir, i,mario);
    mario.SetDirection(dir,i);
    mario.Update(dir,dt);i += dt*speed;


}

void Game::ComposeFrame()
{

    background.DrawTiles(gfx, i);
    map.DrawTiles(gfx, i);
    map.DrawTiles(gfx, i);
    mario.Draw(gfx);
}
